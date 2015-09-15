#include <tizen.h>
#include <service_app.h>
#include "tg-engine-service.h"
#include "tg_engine.h"
#include "tg_server.h"
#include "logger.h"
#include "server_response.h"
#include <net_connection.h>
#include "tg_db_wrapper.h"

static void registration_handler(bundle *rec_msg, void *data)
{
	tg_engine_data_s *tg_data = data;
	Eina_Bool th_sms = EINA_TRUE;
	char *ph_no_key_val = NULL;
	char *sms_key_val = NULL;
	int result;

	result = bundle_get_str(rec_msg, "phone_number", &ph_no_key_val);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	result = bundle_get_str(rec_msg, "through_sms", &sms_key_val);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	th_sms = !strcmp(sms_key_val, "true");

	process_registration_command(tg_data, ph_no_key_val, th_sms);
}

static void code_validation_handler(bundle *rec_msg, void *data)
{
	int result;
	tg_engine_data_s *tg_data = data;
	char* sms_code_val = NULL;

	result = bundle_get_str(rec_msg, "sms_code", &sms_code_val);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	process_validation_command(tg_data, sms_code_val);
}

static void message_transport_handler(bundle *rec_msg, void *data)
{
	char *tmp = NULL;
	char* msg_data_str = NULL;
	int message_id;
	int buddy_id;
	int result;
	int msg_type;
	int type_of_chat;

	result = bundle_get_str(rec_msg, "buddy_id", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	buddy_id = atoi(tmp);

	result = bundle_get_str(rec_msg, "message_id", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	message_id = atoi(tmp);

	result = bundle_get_str(rec_msg, "message_type", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	msg_type = atoi(tmp);

	result = bundle_get_str(rec_msg, "message_data", &msg_data_str);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	result = bundle_get_str(rec_msg, "type_of_chat", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	type_of_chat = atoi(tmp);

	process_send_message_command(buddy_id, message_id, msg_type, msg_data_str, type_of_chat);
}

static void marked_as_read_handler(bundle *rec_msg, void *data)
{
	int result;
	int buddy_id;
	char *tmp;
	int type_of_chat;

	result = bundle_get_str(rec_msg, "buddy_id", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	buddy_id = atoi(tmp);

	result = bundle_get_str(rec_msg, "type_of_chat", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	type_of_chat = atoi(tmp);
	process_marked_as_read_command(buddy_id, type_of_chat);
}

static void media_download_request_handler(bundle *rec_msg, void *data)
{
	tg_engine_data_s *tg_data = data;
	int result;
	char *tmp;
	int buddy_id;
	long long media_id;

	result = bundle_get_str(rec_msg, "buddy_id", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	buddy_id = atoi(tmp);

	result = bundle_get_str(rec_msg, "media_id", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	media_id = atoll(tmp);

	process_media_download_command(tg_data, buddy_id, media_id);
}

static void media_transport_handler(bundle *rec_msg, void *data)
{
	int result;
	int buddy_id;
	int message_id;
	int media_id;
	int msg_type;
	char *tmp;
	char *file_path_str = NULL;
	int type_of_chat;

	result = bundle_get_str(rec_msg, "buddy_id", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	buddy_id = atoi(tmp);

	result = bundle_get_str(rec_msg, "message_id", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	message_id = atoi(tmp);

	result = bundle_get_str(rec_msg, "media_id", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	media_id = atoi(tmp);

	result = bundle_get_str(rec_msg, "message_type", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	msg_type = atoi(tmp);

	result = bundle_get_str(rec_msg, "file_path", &file_path_str);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	result = bundle_get_str(rec_msg, "type_of_chat", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	type_of_chat = atoi(tmp);

	process_send_media_command(buddy_id, message_id, media_id, msg_type, file_path_str, type_of_chat);
}

static void profile_registration_handler(bundle *rec_msg, void *data)
{
	int result;
	tg_engine_data_s *tg_data = data;
	char* first_name = NULL;
	char* last_name = NULL;

	result = bundle_get_str(rec_msg, "first_name", &first_name);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	tg_data->first_name = strdup(first_name);

	result = bundle_get_str(rec_msg, "last_name", &last_name);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	tg_data->last_name = strdup(last_name);

	if (tg_data->tg_state == TG_ENGINE_STATE_PROFILE_FIRST_NAME_REGISTRATION && tg_data->get_string) {
		tg_data->get_string(tgl_engine_get_TLS(), tg_data->first_name, tg_data->callback_arg);
	}
}

static void device_contact_list_handler(bundle *rec_msg, void *data)
{
	int result;
	tg_engine_data_s *tg_data = data;
	char *tmp = NULL;
	int size;
	int count;
	Eina_List* contact_list = NULL;
	contact_data_s *contact;

	result = bundle_get_str(rec_msg, "count", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}

	size = atoi(tmp);

	for (count = 0 ; count < size; count++) {
		contact = (contact_data_s *)malloc(sizeof(*contact));
		if (!contact) {
			break;
		}

		contact->first_name = NULL;
		contact->last_name = NULL;
		contact->phone_number = NULL;

		tmp = (char *)tg_common_to_string("first_name_%d", count);
		result = bundle_get_str(rec_msg, tmp, &tmp);
		if (result == BUNDLE_ERROR_NONE) {
			contact->first_name = strdup(tmp);
		}

		tmp = (char *)tg_common_to_string("last_name_%d", count);
		result = bundle_get_str(rec_msg, tmp, &tmp);
		if (result == BUNDLE_ERROR_NONE) {
			contact->last_name = strdup(tmp);
		}

		tmp = (char *)tg_common_to_string("phone_number_%d", count);
		result = bundle_get_str(rec_msg, tmp, &tmp);
		if (result == BUNDLE_ERROR_NONE) {
			contact->phone_number = strdup(tmp);
		}

		contact_list = eina_list_append(contact_list, contact);
	}

	process_add_contacts_command(tg_data, size, contact_list);
}

static void group_creation_request_handler(bundle *rec_msg, void *data)
{
	int result;
	tg_engine_data_s *tg_data = data;
	char *tmp = NULL;
	int size;
	int count;
	Eina_List* buddy_ids = NULL;
	char *group_name;
	char *group_image;

	result = bundle_get_str(rec_msg, "count", &tmp);
	if (result != BUNDLE_ERROR_NONE) {
		return;
	}
	size = atoi(tmp);

	for (count = 0 ; count < size; count++) {
		tmp = (char *)tg_common_to_string("buddy_id_%d", count);
		result = bundle_get_str(rec_msg, tmp, &tmp);
		if (result != BUNDLE_ERROR_NONE) {
			goto out;
		}
		buddy_ids = eina_list_append(buddy_ids, strdup(tmp));
	}

	result = bundle_get_str(rec_msg, "group_name", &group_name);
	if (result != BUNDLE_ERROR_NONE) {
		goto out;
	}

	result = bundle_get_str(rec_msg, "group_image", &group_image);
	if (result != BUNDLE_ERROR_NONE) {
		goto out;
	}

	process_new_group_create_command(tg_data, buddy_ids, group_name, group_image);

out:
	EINA_LIST_FREE(buddy_ids, tmp) {
		free(tmp);
	}
}

static int _on_tg_server_msg_received_cb(void *data, bundle * const rec_msg)
{
	int i;
	int result = SVC_RES_FAIL;
	RETVM_IF(!data, result, "Data is NULL");
	char *cmd_key_val = NULL;
	struct _msg_handler {
		const char *key;
		void (*handler)(bundle *, void *);
	} msg_handlers[] = {
		[0] = {
			.key = "registration",
			.handler = registration_handler,
		},
		[1] = {
			.key = "code_validation",
			.handler = code_validation_handler,
		},
		[2] = {
			.key = "message_transport",
			.handler = message_transport_handler,
		},
		[3] = {
			.key = "marked_as_read",
			.handler = marked_as_read_handler,
		},
		[4] = {
			.key = "media_download_request",
			.handler = media_download_request_handler,
		},
		[5] = {
			.key = "media_transport",
			.handler = media_transport_handler,
		},
		[6] = {
			.key = "profile_registration",
			.handler = profile_registration_handler,
		},
		[7] = {
			.key = "device_contact_list",
			.handler = device_contact_list_handler,
		},
		[8] = {
			.key = "group_creation_request",
			.handler = group_creation_request_handler,
		},
		[9] = {
			.key = NULL,
			.handler = NULL,
		},
	};

	result = bundle_get_str(rec_msg, "command", &cmd_key_val);
	if (result != BUNDLE_ERROR_NONE) {
		return result;
	}

	for (i = 0; msg_handlers[i].key; i++) {
		if (strcmp(msg_handlers[i].key, cmd_key_val)) {
			continue;
		}

		if (!msg_handlers[i].handler) {
			break;
		}

		msg_handlers[i].handler(rec_msg, data);
	}

	return 0;
}

Eina_Bool event_idler_cb(void *data)
{
	tg_engine_data_s *tg_data = data;

	init_tl_engine(data);
	tgl_login(tgl_engine_get_TLS());

	tg_data->lazy_init_idler = NULL;
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

	/**
	 * @note
	 * We should find a gorgeous way to initialize the Telegram Service.
	 */
	if (tg_data->is_network_connected && !tg_data->is_login_activated) {

		if (!tg_data->lazy_init_idler) {
			tg_data->lazy_init_idler = ecore_idler_add(event_idler_cb, tg_data);
		}
	}
}

bool service_app_create(void *data)
{
	int result;

	tg_engine_data_s *tg_data = data;
	RETVM_IF(!tg_data, SVC_RES_FAIL, "Application data is NULL");

	tg_db_init();
	tg_data->tg_state = TG_ENGINE_STATE_REGISTRATION;
	tg_data->tg_server = tg_server_create();
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

	// if wi-fi or data is on
	create_data_base_tables();

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

void service_app_terminate(void *data)
{
	tg_engine_data_s* tg_data = data;
	struct tgl_state *TLS;

	TLS = tgl_engine_get_TLS();
	if (TLS) {
		tgl_engine_destroy_TLS();
	}

	if (tg_data->tg_server) {
		tg_server_destroy(tg_data->tg_server);
		tg_data->tg_server = NULL;
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

static void service_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	return;
}

static void service_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void service_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void service_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void service_app_low_memory(app_event_info_h event_info, void *user_data)
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
