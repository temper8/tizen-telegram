#include <tizen.h>
#include <service_app.h>
#include "tg-engine-service.h"
#include "tg_engine.h"
#include "tg_server.h"
#include "logger.h"
#include "server_response.h"
#include <net_connection.h>
#include "tg_db_wrapper.h"
#include <badge.h>

static void free_connection(tg_engine_data_s* tg_data);
static Eina_Bool on_restart_service_requested(void *data);
static int _on_tg_server_msg_received_cb(void *data, bundle *const rec_msg)
{
	tg_engine_data_s *tg_data = data;
	int result = SVC_RES_OK;
	RETVM_IF(!tg_data, result, "Data is NULL");
	char *cmd_key_val = NULL;

	int res = bundle_get_str(rec_msg, "command", &cmd_key_val);

	if (strcmp(cmd_key_val, "registration") == 0) {
		char *ph_no_key_val = NULL;
		char *sms_key_val = NULL;
		res = bundle_get_str(rec_msg, "phone_number", &ph_no_key_val);
		res = bundle_get_str(rec_msg, "through_sms", &sms_key_val);

		if (tg_data->tg_state != TG_ENGINE_STATE_NONE && tg_data->tg_state != TG_ENGINE_STATE_REGISTRATION) {
			on_restart_service_requested(tg_data);
		}

		Eina_Bool th_sms = EINA_TRUE;

		if (strcmp(sms_key_val, "true") == 0) {
			th_sms = EINA_TRUE;
		} else {
			th_sms = EINA_FALSE;
		}

		process_registration_command(tg_data, ph_no_key_val, th_sms);
		return result;

	}

	if (strcmp(cmd_key_val, "code_validation") == 0) {

		char* sms_code_val = NULL;
		res = bundle_get_str(rec_msg, "sms_code", &sms_code_val);
		process_validation_command(tg_data, sms_code_val);
		return result;
	}

	if (strcmp(cmd_key_val, "profile_registration") == 0) {

		char* first_name = NULL;
		char* last_name = NULL;

		res = bundle_get_str(rec_msg, "first_name", &first_name);
		if (res == BUNDLE_ERROR_NONE && first_name) {
			tg_data->first_name = strdup(first_name);
		}

		res = bundle_get_str(rec_msg, "last_name", &last_name);
		if (res == BUNDLE_ERROR_NONE && last_name) {
			tg_data->last_name = strdup(last_name);
		}

		if (tg_data->tg_state == TG_ENGINE_STATE_PROFILE_FIRST_NAME_REGISTRATION && tg_data->get_string) {
			tg_data->get_string(tgl_engine_get_TLS(), tg_data->first_name, tg_data->callback_arg);
		}
		return result;
	}

	if (!tg_data->is_login_activated) {
		send_server_not_initialized_response(tg_data);
		return result;
	}

	if (strcmp(cmd_key_val, "logout_telegram") == 0) {

		//process_logout_command(tg_data);

		// delete all data.


		tg_data->is_login_activated = EINA_FALSE;
		tg_data->is_network_connected = EINA_FALSE;
		if (tg_data->phone_number) {
			free(tg_data->phone_number);
			tg_data->phone_number = NULL;
		}

		if (tg_data->sms_code) {
			free(tg_data->sms_code);
			tg_data->sms_code = NULL;
		}

		if (tg_data->first_name) {
			free(tg_data->first_name);
			tg_data->first_name = NULL;
		}

		if (tg_data->last_name) {
			free(tg_data->last_name);
			tg_data->last_name = NULL;
		}

		if (tg_data->contact_list_to_add) {
			free_contact_data(tg_data->contact_list_to_add);
			tg_data->contact_list_to_add = NULL;
		}

		if (tg_data->chat_list) {
			eina_list_free(tg_data->chat_list);
			tg_data->chat_list = NULL;
		}

		if (tg_data->buddy_list) {
			eina_list_free(tg_data->buddy_list);
			tg_data->buddy_list = NULL;
		}

		tgl_engine_var_free();

		tg_db_fini();

#if 0
		char *cmd = (char*)malloc(strlen("rm -r ") + strlen(DEFAULT_TELEGRAM_PATH) + 1);
		strcpy(cmd, "rm -r ");
		strcat(cmd, DEFAULT_TELEGRAM_PATH);
		int ret = system(cmd);
		free(cmd);
#else
		int ret = recursive_dir_delete(DEFAULT_TELEGRAM_PATH);
#endif
		send_response_for_logout(tg_data);
		tgl_engine_var_init();
		tg_db_init();
		tg_data->tg_state = TG_ENGINE_STATE_NONE;
		tg_data->first_name = NULL;
		tg_data->last_name = NULL;
		tg_data->phone_number = NULL;
		tg_data->sms_code = NULL;
		tg_data->contact_list_to_add = NULL;
		tg_data->new_group_icon = NULL;
		tg_data->mhash = NULL;
		tg_data->lazy_init_idler = NULL;
		tg_data->code_response_timer = NULL;

		init_tl_engine(data);
		tgl_login(tgl_engine_get_TLS());

		tg_data->lazy_init_idler = NULL;
		tg_data->code_response_timer = NULL;

		//send event to application


	} else if (strcmp(cmd_key_val, "restart_server") == 0) {
		on_restart_service_requested(tg_data);
	} else if (strcmp(cmd_key_val, "message_transport") == 0) {

		char* buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
		int buddy_id = atoi(buddy_id_str);

		char* message_id_str = NULL;
		res = bundle_get_str(rec_msg, "message_id", &message_id_str);
		int message_id = atoi(message_id_str);

		char* msg_type_str = NULL;
		res = bundle_get_str(rec_msg, "message_type", &msg_type_str);
		int msg_type = atoi(msg_type_str);

		char* msg_data_str = NULL;
		res = bundle_get_str(rec_msg, "message_data", &msg_data_str);

		char* type_of_chat_str = NULL;
		res = bundle_get_str(rec_msg, "type_of_chat", &type_of_chat_str);
		int type_of_chat = atoi(type_of_chat_str);

		process_send_message_command(buddy_id, message_id, msg_type, msg_data_str, type_of_chat);

    } else if (strcmp(cmd_key_val, "marked_as_read") == 0) {
    	char* buddy_id_str = NULL;
    	res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
    	int buddy_id = atoi(buddy_id_str);

    	char* type_of_chat_str = NULL;
    	res = bundle_get_str(rec_msg, "type_of_chat", &type_of_chat_str);
    	int type_of_chat = atoi(type_of_chat_str);
    	process_marked_as_read_command(buddy_id, type_of_chat);

    } else if (strcmp(cmd_key_val, "delete_group_chat_request") == 0) {

    	char* chat_id_str = NULL;
    	res = bundle_get_str(rec_msg, "chat_id", &chat_id_str);
    	int chat_id = atoi(chat_id_str);

    	process_delete_group_chat_request(tg_data, chat_id);

	} else if (strcmp(cmd_key_val, "delete_selected_group_chats_request") == 0) {

		char* count_str = NULL;
		res = bundle_get_str(rec_msg, "list_size", &count_str);
		int size = atoi(count_str);
		Eina_List* chat_id_list = NULL;

		for (int count = 0 ; count < size ; count++) {
			char count_str[10];
			sprintf(count_str, "%d", count);

			char chat_id_key[20];
			strcpy(chat_id_key, "chat_id_");
			strcat(chat_id_key, count_str);

			char* chat_id_str = NULL;
			res = bundle_get_str(rec_msg, chat_id_key, &chat_id_str);


			int chat_id = atoi(chat_id_str);
			chat_id_list = eina_list_append(chat_id_list, chat_id);
		}

		if (chat_id_list && eina_list_count(chat_id_list) > 0) {
			process_delete_selected_group_chats_request(tg_data, chat_id_list);
		}

    } else if (strcmp(cmd_key_val, "add_buddy") == 0) {

    	char* buddy_id_str = NULL;
    	res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
    	int buddy_id = atoi(buddy_id_str);

    	char* first_name = NULL;
    	res = bundle_get_str(rec_msg, "first_name", &first_name);

    	char* last_name = NULL;
    	res = bundle_get_str(rec_msg, "last_name", &last_name);

    	char* phone_number = NULL;
    	res = bundle_get_str(rec_msg, "phone_number", &phone_number);

    	process_add_user_request(tg_data, buddy_id, first_name, last_name, phone_number);
    } else if (strcmp(cmd_key_val, "update_chat_info") == 0) {

    	char* chat_id_str = NULL;
    	res = bundle_get_str(rec_msg, "chat_id", &chat_id_str);
    	int chat_id = atoi(chat_id_str);

    	process_update_chat_request(tg_data, chat_id);

    } else if (strcmp(cmd_key_val, "start_secret_chat") == 0) {

    	char* buddy_id_str = NULL;
    	res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
    	int buddy_id = atoi(buddy_id_str);

    	process_send_secret_chat_request(tg_data, buddy_id);


    } else if (strcmp(cmd_key_val, "delete_buddy") == 0) {

    	char* buddy_id_str = NULL;
    	res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
    	int buddy_id = atoi(buddy_id_str);

    	process_delete_user_request(tg_data, buddy_id);

    } else if (strcmp(cmd_key_val, "delete_message") == 0) {

    	char* buddy_id_str = NULL;
    	res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
    	int buddy_id = atoi(buddy_id_str);

    	char* message_id_str = NULL;
    	res = bundle_get_str(rec_msg, "message_id", &message_id_str);
    	int message_id = atoi(message_id_str);

    	process_delete_message_request(tg_data, buddy_id, message_id);

    } else if (strcmp(cmd_key_val, "block_buddy") == 0) {

    	char* buddy_id_str = NULL;
    	res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
    	int buddy_id = atoi(buddy_id_str);

    	process_block_user_request(tg_data, buddy_id);

    } else if (strcmp(cmd_key_val, "unblock_buddy") == 0) {

    	char* buddy_id_str = NULL;
    	res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
    	int buddy_id = atoi(buddy_id_str);

    	process_unblock_user_request(tg_data, buddy_id);

	} else if (strcmp(cmd_key_val, "media_download_request") == 0) {

		char* buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
		int buddy_id = atoi(buddy_id_str);

		char* media_id_str = NULL;
		res = bundle_get_str(rec_msg, "media_id", &media_id_str);
		long long media_id = atoll(media_id_str);
		process_media_download_command(tg_data, buddy_id, media_id);

	} else if (strcmp(cmd_key_val, "media_transport") == 0) {

		char* buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
		int buddy_id = atoi(buddy_id_str);

		char* message_id_str = NULL;
		res = bundle_get_str(rec_msg, "message_id", &message_id_str);
		int message_id = atoi(message_id_str);

		char* media_id_str = NULL;
		res = bundle_get_str(rec_msg, "media_id", &media_id_str);
		int media_id = atoi(media_id_str);

		char* msg_type_str = NULL;
		res = bundle_get_str(rec_msg, "message_type", &msg_type_str);
		int msg_type = atoi(msg_type_str);

		char* file_path_str = NULL;
		res = bundle_get_str(rec_msg, "file_path", &file_path_str);

		char* type_of_chat_str = NULL;
		res = bundle_get_str(rec_msg, "type_of_chat", &type_of_chat_str);
		int type_of_chat = atoi(type_of_chat_str);

		process_send_media_command(buddy_id, message_id, media_id, msg_type, file_path_str, type_of_chat);

	} else if (strcmp(cmd_key_val, "device_contact_list") == 0) {

		char* count_str = NULL;
		res = bundle_get_str(rec_msg, "count", &count_str);
		int size = atoi(count_str);
		Eina_List* contact_list = NULL;

		for (int count = 0 ; count < size ; count++) {
			contact_data_s* contact = (contact_data_s*)malloc(sizeof(contact_data_s));
			contact->first_name = NULL;
			contact->last_name = NULL;
			contact->phone_number = NULL;

			char count_str[10];
			sprintf(count_str, "%d", count);

			char first_name_key[20];
			strcpy(first_name_key, "first_name_");
			strcat(first_name_key, count_str);

			char last_name_key[20];
			strcpy(last_name_key, "last_name_");
			strcat(last_name_key, count_str);

			char phone_number_key[20];
			strcpy(phone_number_key, "phone_number_");
			strcat(phone_number_key, count_str);

			char* first_name = NULL;
			res = bundle_get_str(rec_msg, first_name_key, &first_name);

			if (first_name) {
				contact->first_name = strdup(first_name);
			}

			char* last_name = NULL;
			res = bundle_get_str(rec_msg, last_name_key, &last_name);

			if (last_name) {
				contact->last_name = strdup(last_name);
			}

			char* phone_number = NULL;
			res = bundle_get_str(rec_msg, phone_number_key, &phone_number);

			if (phone_number) {
				contact->phone_number = strdup(phone_number);
			}
			contact_list = eina_list_append(contact_list, contact);
		}

		process_add_contacts_command(tg_data, size, contact_list);

	} else if (strcmp(cmd_key_val, "group_creation_request") == 0) {
		char* count_str = NULL;
		res = bundle_get_str(rec_msg, "count", &count_str);
		int size = atoi(count_str);
		Eina_List* buddy_ids = NULL;

		for (int count = 0 ; count < size ; count++) {
			char count_str[10];
			sprintf(count_str, "%d", count);

			char buddy_id_key[20];
			strcpy(buddy_id_key, "buddy_id_");
			strcat(buddy_id_key, count_str);

			char* buddy_id = NULL;
			res = bundle_get_str(rec_msg, buddy_id_key, &buddy_id);

			buddy_ids = eina_list_append(buddy_ids, buddy_id);
		}

		char* temp_group_name = NULL;
		res = bundle_get_str(rec_msg, "group_name", &temp_group_name);
		char* group_name = strdup(temp_group_name);

		char* temp_group_image = NULL;
		res = bundle_get_str(rec_msg, "group_image", &temp_group_image);
		char* group_image = strdup(temp_group_image);

		process_new_group_create_command(tg_data, buddy_ids, group_name, group_image);
	} else if (strcmp(cmd_key_val, "remove_buddy_from_chat_request") == 0) {

		char *buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);

		int buddy_id = 0;
		if (buddy_id_str) {
			buddy_id = atoi(buddy_id_str);
		}

		char *chat_id_str = NULL;
		res = bundle_get_str(rec_msg, "chat_id", &chat_id_str);

		int chat_id = 0;
		if (chat_id_str) {
			chat_id = atoi(chat_id_str);
		}
		process_remove_buddy_from_chat_command(tg_data, buddy_id, chat_id);

	} else if (strcmp(cmd_key_val, "add_new_buddy_to_chat_request") == 0) {

		char *buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);

		int buddy_id = 0;
		if (buddy_id_str) {
			buddy_id = atoi(buddy_id_str);
		}

		char *chat_id_str = NULL;
		res = bundle_get_str(rec_msg, "chat_id", &chat_id_str);

		int chat_id = 0;
		if (chat_id_str) {
			chat_id = atoi(chat_id_str);
		}
		process_add_new_buddy_to_chat_command(tg_data, buddy_id, chat_id);

	} else if (strcmp(cmd_key_val, "set_group_chat_new_title_request") == 0) {

		char *buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);

		int buddy_id = 0;
		if (buddy_id_str) {
			buddy_id = atoi(buddy_id_str);
		}

		char *new_title = NULL;
		res = bundle_get_str(rec_msg, "new_title", &new_title);
		process_set_group_chat_new_title_command(tg_data, buddy_id, new_title);

	} else if (strcmp(cmd_key_val, "set_group_chat_profile_pic_request") == 0) {

		char *buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);

		int buddy_id = 0;
		if (buddy_id_str) {
			buddy_id = atoi(buddy_id_str);
		}

		char *file_path = NULL;
		res = bundle_get_str(rec_msg, "file_path", &file_path);
		process_set_group_chat_profile_pic_command(tg_data, buddy_id, file_path);

	} else if (strcmp(cmd_key_val, "set_profile_pic_request") == 0) {

		char *buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);

		int buddy_id = 0;
		if (buddy_id_str) {
			buddy_id = atoi(buddy_id_str);
		}

		char *file_path = NULL;
		res = bundle_get_str(rec_msg, "file_path", &file_path);
		process_set_profile_pic_command(tg_data, buddy_id, file_path);

	} else if (strcmp(cmd_key_val, "update_display_name_request") == 0) {

		char *buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);

		int buddy_id = 0;
		if (buddy_id_str) {
			buddy_id = atoi(buddy_id_str);
		}

		char *first_name = NULL;
		res = bundle_get_str(rec_msg, "first_name", &first_name);

		char *last_name = NULL;
		res = bundle_get_str(rec_msg, "last_name", &last_name);

		process_update_display_name_command(tg_data, buddy_id, first_name, last_name);

	} else if (strcmp(cmd_key_val, "set_username_request") == 0) {

		char *buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);

		int buddy_id = 0;
		if (buddy_id_str) {
			buddy_id = atoi(buddy_id_str);
		}

		char *username = NULL;
		res = bundle_get_str(rec_msg, "username", &username);
		process_set_username_command(tg_data, buddy_id, username);

	} else if (strcmp(cmd_key_val, "delete_all_notifications") == 0) {
		if(tg_data->s_notififcation) {
			notification_delete_all(NOTIFICATION_TYPE_NOTI);
			tg_data->s_notififcation = NULL;
		}
	} else if (strcmp(cmd_key_val, "server_connection_status") == 0) {
		send_response_for_server_connection_status(tg_data, tg_data->is_login_activated);
	} else {

	}

	return result;
}

Eina_Bool on_code_request_timer_expired(void *data)
{
	tg_engine_data_s *tg_data = data;

	if (tg_data->code_response_timer == NULL) {
		return ECORE_CALLBACK_CANCEL;
	}

	if (tg_data->code_response_timer) {
		ecore_timer_del(tg_data->code_response_timer);
		tg_data->code_response_timer = NULL;
	}
	send_server_connection_failed_response(tg_data);
	on_restart_service_requested(tg_data);
	return ECORE_CALLBACK_CANCEL;
}


Eina_Bool event_idler_cb(void *data)
{
	tg_engine_data_s *tg_data = data;

	init_tl_engine(data);
	tgl_login(tgl_engine_get_TLS());

	tg_data->lazy_init_idler = NULL;
	return ECORE_CALLBACK_CANCEL;
}

static Eina_Bool on_start_service_requested(void *data)
{
	tg_engine_data_s *tg_data = data;

	init_tl_engine(data);
	tgl_login(tgl_engine_get_TLS());

	tg_data->lazy_init_idler = NULL;
	return ECORE_CALLBACK_CANCEL;
}

Eina_Bool on_restart_service_requested(void *data)
{
	tg_engine_data_s *tg_data = data;


	free_connection(tg_data);
	tgl_engine_var_init();
	tg_db_init();
	tg_data->tg_state = TG_ENGINE_STATE_NONE;
	tg_data->tg_server = tg_server_create();
	tg_data->first_name = NULL;
	tg_data->last_name = NULL;
	tg_data->phone_number = NULL;
	tg_data->sms_code = NULL;
	tg_data->contact_list_to_add = NULL;
	tg_data->new_group_icon = NULL;
	tg_data->mhash = NULL;
	tg_data->lazy_init_idler = NULL;
	tg_data->code_response_timer = NULL;

	init_tl_engine(data);
	tgl_login(tgl_engine_get_TLS());

	tg_data->lazy_init_idler = NULL;
	tg_data->code_response_timer = NULL;
	return ECORE_CALLBACK_CANCEL;
}

void on_connection_type_changed_cb(connection_type_e type, void *user_data)
{
	tg_engine_data_s *tg_data = user_data;
	int err_code;

	if (type == CONNECTION_TYPE_WIFI) {
		connection_wifi_state_e wifi_state;
		err_code = connection_get_wifi_state(tg_data->connection, &wifi_state);
		if (err_code == CONNECTION_ERROR_NONE) {
			switch (wifi_state)	{
			case CONNECTION_WIFI_STATE_CONNECTED:
				tg_data->is_network_connected = EINA_TRUE;
				break;
			case CONNECTION_WIFI_STATE_DEACTIVATED:
			case CONNECTION_WIFI_STATE_DISCONNECTED:
			default:
				tg_data->is_login_activated = EINA_FALSE;
				tg_data->is_network_connected = EINA_FALSE;
				send_response_for_server_connection_status(tg_data, tg_data->is_login_activated);
				break;
			}
		}
	} else if(type == CONNECTION_TYPE_CELLULAR) {
		connection_cellular_state_e cellular_state;

		err_code = connection_get_cellular_state(tg_data->connection, &cellular_state);
		if (err_code == CONNECTION_ERROR_NONE && cellular_state == CONNECTION_CELLULAR_STATE_CONNECTED) {
			tg_data->is_network_connected = EINA_TRUE;
		}
	} else {
		tg_data->is_login_activated = EINA_FALSE;
		tg_data->is_network_connected = EINA_FALSE;
		send_response_for_server_connection_status(tg_data, tg_data->is_login_activated);
	}

	/**
	 * @note
	 * We should find a gorgeous way to initialize the Telegram Service.
	 */
	if (tg_data->is_network_connected) {
		if (tg_data->is_login_activated) {
			tg_data->is_login_activated = EINA_FALSE;
			ecore_timer_add(30, on_restart_service_requested, tg_data);
		} else {
			ecore_timer_add(5, on_start_service_requested, tg_data);
		}
	}
}

bool service_app_create(void *data)
{
	int result;

	tg_engine_data_s *tg_data = data;
	RETVM_IF(!tg_data, SVC_RES_FAIL, "Application data is NULL");
	tgl_engine_var_init();
	tg_db_init();
	tg_data->tg_state = TG_ENGINE_STATE_NONE;
	tg_data->tg_server = tg_server_create();
	tg_data->first_name = NULL;
	tg_data->last_name = NULL;
	tg_data->phone_number = NULL;
	tg_data->sms_code = NULL;
	tg_data->contact_list_to_add = NULL;
	tg_data->new_group_icon = NULL;
	tg_data->mhash = NULL;
	tg_data->lazy_init_idler = NULL;
	tg_data->code_response_timer = NULL;
	tg_data->s_notififcation = NULL;
	tg_data->chat_list = NULL;
	tg_data->current_chat_index = 0;
	tg_data->buddy_list = NULL;
	tg_data->current_buddy_index = 0;
	//tg_data->is_loading_completed = EINA_FALSE;
	RETVM_IF(!tg_data->tg_server, SVC_RES_FAIL, "Failed to create proxy client");

	result = tg_server_register_port(tg_data->tg_server, TELEGRAM_SERVER_PORT_NAME);
	if (result != SVC_RES_OK) {
		ERR("Failed to register proxy client port");
		tg_server_destroy(tg_data->tg_server);
		tg_data->tg_server = NULL;
		tg_db_fini();
		return EINA_FALSE;
	}

	result = _tg_server_set_remote_data(tg_data->tg_server, TELEGRAM_CLIENT_APP_NAME, TELEGRAM_CLIENT_PORT_NAME);
	result = tg_server_register_msg_receive_callback(tg_data->tg_server, _on_tg_server_msg_received_cb, tg_data);

	int err = badge_new(TELEGRAM_APP_ID);
	if (BADGE_ERROR_NONE != err) {

	}

	result = connection_create(&(tg_data->connection));
	if (result == CONNECTION_ERROR_NONE) {
		connection_type_e net_state;

		result = connection_get_type(tg_data->connection, &net_state);
		if (result == CONNECTION_ERROR_NONE) {
			on_connection_type_changed_cb(net_state, tg_data);

			result = connection_set_type_changed_cb(tg_data->connection, on_connection_type_changed_cb, tg_data);
			if (result != CONNECTION_ERROR_NONE) {
				/**
				 * @note
				 * How can we handle this case?
				 */
			}
		}
	} else {
		ERR("Failed to initialize connection object");
		tg_server_destroy(tg_data->tg_server);
		tg_data->tg_server = NULL;
		tg_db_fini();
		return false;
	}

	return true;
}

void free_connection(tg_engine_data_s* tg_data)
{
	//struct tgl_state *TLS;

/*
	TLS = tgl_engine_get_TLS();
	if (TLS) {
		tgl_engine_destroy_TLS();
	}
*/
	tg_data->is_login_activated = EINA_FALSE;
	tg_data->is_network_connected = EINA_FALSE;
	send_response_for_server_connection_status(tg_data, tg_data->is_login_activated);
	if (tg_data->phone_number) {
		free(tg_data->phone_number);
		tg_data->phone_number = NULL;
	}

	if (tg_data->sms_code) {
		free(tg_data->sms_code);
		tg_data->sms_code = NULL;
	}

	if (tg_data->first_name) {
		free(tg_data->first_name);
		tg_data->first_name = NULL;
	}

	if (tg_data->last_name) {
		free(tg_data->last_name);
		tg_data->last_name = NULL;
	}

	if (tg_data->contact_list_to_add) {
		free_contact_data(tg_data->contact_list_to_add);
		tg_data->contact_list_to_add = NULL;
	}

	if (tg_data->chat_list) {
		eina_list_free(tg_data->chat_list);
		tg_data->chat_list = NULL;
	}

	if (tg_data->buddy_list) {
		eina_list_free(tg_data->buddy_list);
		tg_data->buddy_list = NULL;
	}

	tgl_engine_var_free();

	tg_db_fini();
}

void service_app_terminate(void *data)
{
	tg_engine_data_s* tg_data = data;
	if (tg_data->connection) {
		connection_destroy(tg_data->connection);
		tg_data->connection = NULL;
	}
	if (tg_data->tg_server) {
		tg_server_destroy(tg_data->tg_server);
		tg_data->tg_server = NULL;
	}
	if (tg_data && tg_data->s_notififcation) {
		notification_delete_all(NOTIFICATION_TYPE_NOTI);
		tg_data->s_notififcation = NULL;
	}

	free_connection(tg_data);
	return;
}

void service_app_control(app_control_h app_control, void *data)
{
	// Todo: add your code here.
	return;
}

static void
service_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	return;
}

static void
service_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
service_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
service_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
service_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int main(int argc, char* argv[])
{
	/**
	 * static type qualifier will initialize the tg_data.
	 * and the tg_data will be allocated in the DATA section.
	 * we can save more stack or heap area.
	 */
	static tg_engine_data_s tg_data;
	service_app_lifecycle_callback_s event_callback;
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = service_app_create;
	event_callback.terminate = service_app_terminate;
	event_callback.app_control = service_app_control;

	service_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, service_app_low_battery, &tg_data);
	service_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, service_app_low_memory, &tg_data);
	service_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, service_app_orient_changed, &tg_data);
	service_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, service_app_lang_changed, &tg_data);
	service_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, service_app_region_changed, &tg_data);

	return service_app_main(argc, argv, &event_callback, &tg_data);
}
