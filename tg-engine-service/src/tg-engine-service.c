#include <tizen.h>
#include <service_app.h>
#include "tg-engine-service.h"
#include "tg_engine.h"
#include "tg_server.h"
#include "logger.h"
#include "server_response.h"
#include <net_connection.h>
#include "tg_db_wrapper.h"

static int _on_tg_server_msg_received_cb(void *data, bundle *const rec_msg)
{
	int result = SVC_RES_FAIL;
	RETVM_IF(!data, result, "Data is NULL");

	// tg_engine_data_s* app = (tg_engine_data_s*)data;

	char *cmd_key_val = NULL;

	int res = bundle_get_str(rec_msg, "command", &cmd_key_val);


	if (strcmp(cmd_key_val, "registration") == 0) {
		char *ph_no_key_val = NULL;
		char *sms_key_val = NULL;
		res = bundle_get_str(rec_msg, "phone_number", &ph_no_key_val);
		res = bundle_get_str(rec_msg, "through_sms", &sms_key_val);

		Eina_Bool th_sms = EINA_TRUE;

		if (strcmp(sms_key_val, "true") == 0) {
			th_sms = EINA_TRUE;
		} else {
			th_sms = EINA_FALSE;
		}

		process_registration_command(ph_no_key_val, th_sms);

	} else if (strcmp(cmd_key_val, "code_validation") == 0) {

		char* sms_code_val = NULL;
		res = bundle_get_str(rec_msg, "sms_code", &sms_code_val);
		process_validation_command(sms_code_val);

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
	} else if (strcmp(cmd_key_val, "media_download_request") == 0) {

		char* buddy_id_str = NULL;
		res = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
		int buddy_id = atoi(buddy_id_str);

		char* media_id_str = NULL;
		res = bundle_get_str(rec_msg, "media_id", &media_id_str);
		long long media_id = atoll(media_id_str);
		process_media_download_command(buddy_id, media_id);

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

	} else if (strcmp(cmd_key_val, "profile_registration") == 0) {

		char* first_name = NULL;
		res = bundle_get_str(rec_msg, "first_name", &first_name);
		tg_data->first_name = strdup(first_name);

		char* last_name = NULL;
		res = bundle_get_str(rec_msg, "last_name", &last_name);
		tg_data->last_name = strdup(last_name);

		if (tg_data->tg_state == TG_ENGINE_STATE_PROFILE_FIRST_NAME_REGISTRATION && tg_data->get_string) {
			tg_data->get_string(TLS, tg_data->first_name, tg_data->callback_arg);
		}

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

		process_add_contacts_command(size, contact_list);

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

		process_new_group_create_command(buddy_ids, group_name, group_image);

	} else {

	}

	return result;
}

Eina_Bool event_idler_cb(void *data)
{
	init_tl_engine();
	tgl_login(TLS);
	return ECORE_CALLBACK_CANCEL;
}

void on_connection_type_changed_cb(connection_type_e type, void *user_data)
{
	int err_code;
	if (type == CONNECTION_TYPE_WIFI) {
		connection_wifi_state_e wifi_state;
		err_code = connection_get_wifi_state(tg_data->connection, &wifi_state);
		if (err_code == CONNECTION_ERROR_NONE) {
			switch (wifi_state)	{
			case CONNECTION_WIFI_STATE_DEACTIVATED:
				tg_data->is_network_connected = EINA_FALSE;
				break;
			case CONNECTION_WIFI_STATE_DISCONNECTED:
				tg_data->is_network_connected = EINA_FALSE;
				break;
			case CONNECTION_WIFI_STATE_CONNECTED:
				tg_data->is_network_connected = EINA_TRUE;
				break;
			default:
				tg_data->is_network_connected = EINA_FALSE;
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

	}

	if (tg_data->is_network_connected && !tg_data->is_login_activated) {
		Ecore_Idler *idler_for_event;
		idler_for_event = ecore_idler_add(event_idler_cb, NULL);
		if (!idler_for_event) {
			// error handling
		}
	}
}

bool service_app_create(void *data)
{
	int result;

	tg_db_init();

	tg_data->tg_state = TG_ENGINE_STATE_REGISTRATION;
	tg_data->phone_number = NULL;
	tg_data->first_name = NULL;
	tg_data->last_name = NULL;
	tg_data->sms_code = NULL;
	tg_data->get_string = NULL;
	tg_data->is_login_activated = EINA_FALSE;
	tg_data->is_group_creation_requested = EINA_FALSE;
	tg_data->new_group_icon = NULL;
	tg_data->is_first_time_registration = EINA_FALSE;

	tg_engine_data_s* ad = data;
	RETVM_IF(!ad, SVC_RES_FAIL, "Application data is NULL");

	ad->tg_server = tg_server_create();
	RETVM_IF(!ad->tg_server, SVC_RES_FAIL, "Failed to create proxy client");

	result = tg_server_register_port(ad->tg_server, TELEGRAM_SERVER_PORT_NAME);
	if (result != SVC_RES_OK) {
		ERR("Failed to register proxy client port");
		tg_server_destroy(ad->tg_server);
		ad->tg_server = NULL;
		return result;
	}

	result = _tg_server_set_remote_data(ad->tg_server, TELEGRAM_CLIENT_APP_NAME, TELEGRAM_CLIENT_PORT_NAME);

	result = tg_server_register_msg_receive_callback(ad->tg_server, _on_tg_server_msg_received_cb, ad);

	// if wi-fi or data is on
	int err_code;
	create_data_base_tables();
	err_code = connection_create(&(tg_data->connection));

	if (err_code == CONNECTION_ERROR_NONE) {
		connection_type_e net_state;
		connection_wifi_state_e wifi_state;

		err_code = connection_get_type(tg_data->connection, &net_state);
		if (err_code == CONNECTION_ERROR_NONE) {
			if (net_state == CONNECTION_TYPE_WIFI) {
				tg_data->is_network_connected = EINA_TRUE;
			} else if(net_state == CONNECTION_TYPE_CELLULAR) {
				tg_data->is_network_connected = EINA_TRUE;
			} else {
				tg_data->is_network_connected = EINA_FALSE;
			}
		}

		err_code = connection_get_wifi_state(tg_data->connection, &wifi_state);
		if (err_code == CONNECTION_ERROR_NONE) {
			switch (wifi_state)	{
			case CONNECTION_WIFI_STATE_DEACTIVATED:
				tg_data->is_network_connected = EINA_FALSE;
				break;
			case CONNECTION_WIFI_STATE_DISCONNECTED:
				tg_data->is_network_connected = EINA_FALSE;
				break;
			case CONNECTION_WIFI_STATE_CONNECTED:
				tg_data->is_network_connected = EINA_TRUE;
				break;
			default:
				tg_data->is_network_connected = EINA_FALSE;
				break;
			}
		}

		if (!tg_data->is_network_connected) {
			connection_cellular_state_e cellular_state;
			err_code = connection_get_cellular_state(tg_data->connection, &cellular_state);

			if (err_code == CONNECTION_ERROR_NONE && cellular_state == CONNECTION_CELLULAR_STATE_CONNECTED) {
				tg_data->is_network_connected = EINA_TRUE;
			}
		}

		err_code = connection_set_type_changed_cb(tg_data->connection, on_connection_type_changed_cb, NULL);
		if (err_code == CONNECTION_ERROR_NONE) {

		} else {

		}

	}

	if (tg_data->is_network_connected ) {
		Ecore_Idler *idler_for_event;
		idler_for_event = ecore_idler_add(event_idler_cb, NULL);
		if (!idler_for_event) {
			// error handling
		}
	}

	if (result != SVC_RES_OK)
	{
		ERR("Failed to register proxy client on message receive callback");
		tg_server_destroy(ad->tg_server);
		ad->tg_server = NULL;
		return result;
	}

	return true;
}

void service_app_terminate(void *data)
{
	tg_engine_data_s* ad = data;
	if (TLS) {
		free(TLS);
		TLS = NULL;
	}
	if (ad->tg_server) {
		tg_server_destroy(ad->tg_server);
		ad->tg_server = NULL;
	}
	connection_destroy(tg_data->connection);
	if (tg_data) {
		free(tg_data);
		tg_data = NULL;
	}

	tg_db_fini();
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
	tg_data = (tg_engine_data_s*)malloc(sizeof(tg_engine_data_s));
	service_app_lifecycle_callback_s event_callback;
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = service_app_create;
	event_callback.terminate = service_app_terminate;
	event_callback.app_control = service_app_control;

	service_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, service_app_low_battery, tg_data);
	service_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, service_app_low_memory, tg_data);
	service_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, service_app_orient_changed, tg_data);
	service_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, service_app_lang_changed, tg_data);
	service_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, service_app_region_changed, tg_data);

	return service_app_main(argc, argv, &event_callback, tg_data);
}
