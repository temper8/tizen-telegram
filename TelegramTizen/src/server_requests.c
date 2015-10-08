/**
 * @file server_requests.c
 * @date Jun 26, 2015
 * @author sandeep
 */

#include "server_requests.h"
#include "tg_db_wrapper.h"
#include "device_contacts_manager.h"

void send_request_for_registration(service_client* service_client, const char* phone_number, Eina_Bool through_sms)
{
	bundle *msg;
	int result;

	if (!service_client || !phone_number) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		LOGE("Failed to create a bundle");
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "registration") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "phone_number", phone_number) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "through_sms", (through_sms) ? "true" : "false") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
		LOGE("Failed to send a service message");
	}

	bundle_free(msg);
}

void send_request_for_profile_registration(service_client* service_client, const char* first_name, const char* last_name)
{
	bundle *msg;
	int result;

	if (!service_client || !first_name || !last_name) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "profile_registration") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "first_name", first_name) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "last_name", last_name) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_request_for_validation(service_client* service_client, const char* sms_code)
{
	bundle *msg;
	int result;

	if (!service_client || !sms_code) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "code_validation") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "sms_code", sms_code) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if (result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_add_buddy_request(service_client* service_client, const int buddy_id)
{
	if (!service_client) {
		// error
		return;
	}
	bundle *msg;
	char tmp[50];
	int result;
	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "add_buddy") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}
	snprintf(tmp, sizeof(tmp) - 1, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_update_chat_request(service_client* service_client, const int chat_id)
{
	if (!service_client) {
		// error
		return;
	}
	bundle *msg;
	char tmp[50];
	int result;
	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "update_chat_info") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}
	snprintf(tmp, sizeof(tmp) - 1, "%d", chat_id);

	if (bundle_add_str(msg, "chat_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}


void send_delete_buddy_request(service_client* service_client, const int buddy_id)
{
	if (!service_client) {
		// error
		return;
	}
	bundle *msg;
	char tmp[50];
	int result;
	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "delete_buddy") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}
	snprintf(tmp, sizeof(tmp) - 1, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}


void send_block_buddy_request(service_client* service_client, const int buddy_id)
{
	if (!service_client) {
		// error
		return;
	}
	bundle *msg;
	char tmp[50];
	int result;
	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "block_buddy") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}
	snprintf(tmp, sizeof(tmp) - 1, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_unblock_buddy_request(service_client* service_client, const int buddy_id)
{
	if (!service_client) {
		// error
		return;
	}
	bundle *msg;
	char tmp[50];
	int result;
	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "unblock_buddy") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}
	snprintf(tmp, sizeof(tmp) - 1, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}


void send_delete_group_chat_request(service_client* service_client, const int chat_id)
{
	if (!service_client) {
		// error
		return;
	}
	bundle *msg;
	char tmp[50];
	int result;
	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "delete_group_chat_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}
	snprintf(tmp, sizeof(tmp) - 1, "%d", chat_id);

	if (bundle_add_str(msg, "chat_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}


	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);

}

void send_request_for_marked_as_read(service_client* service_client, const int buddy_id, const int type_of_chat)
{
	bundle *msg;
	char tmp[50];
	int result;

	if (!service_client) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "marked_as_read") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", type_of_chat);
	if (bundle_add_str(msg, "type_of_chat", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_request_for_message_transport(appdata_s *ad, service_client* service_client, const int buddy_id, const int message_id, const int msg_type, const char* data, const int type_of_chat)
{
	char tmp[50];
	bundle *msg;
	int result;
	char *buddy_id_str = NULL;
	char *msg_id_str = NULL;
	char *msg_type_str = NULL;
	char *type_of_chat_str = NULL;
	if (!service_client || !data) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "message_transport") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp), "%d", buddy_id);
	buddy_id_str = strdup(tmp);
	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", message_id);
	msg_id_str = strdup(tmp);
	if (bundle_add_str(msg, "message_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", msg_type);
	msg_type_str = strdup(tmp);
	if (bundle_add_str(msg, "message_type", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "message_data", data) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}


	snprintf(tmp, sizeof(tmp) - 1, "%d", type_of_chat);
	type_of_chat_str = strdup(tmp);
	if (bundle_add_str(msg, "type_of_chat", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if (result != SVC_RES_OK || !ad->is_server_ready) {
		// error
		insert_unsent_message_to_db("Tizen Telegram", "message_transport", buddy_id_str, msg_id_str, msg_type_str, data, type_of_chat_str);
	}
	bundle_free(msg);

	if (buddy_id_str) {
		free(buddy_id_str);
		buddy_id_str = NULL;
	}

	if (msg_id_str) {
		free(msg_id_str);
		msg_id_str = NULL;
	}

	if (msg_type_str) {
		free(msg_type_str);
		msg_type_str = NULL;
	}

	if (type_of_chat_str) {
		free(type_of_chat_str);
		type_of_chat_str = NULL;
	}

}

void send_request_for_media_transport(appdata_s *ad, service_client* service_client, const int buddy_id, const int message_id, const int media_id,  const int msg_type, const char* file_path, const int type_of_chat)
{
	bundle *msg;
	char tmp[50];
	int result;
	char *buddy_id_str = NULL;
	char *msg_id_str = NULL;
	char *media_id_str = NULL;
	char *msg_type_str = NULL;
	char *type_of_chat_str = NULL;
	if (!service_client) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "media_transport") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", buddy_id);
	buddy_id_str = strdup(tmp);
	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", message_id);
	msg_id_str = strdup(tmp);
	if (bundle_add_str(msg, "message_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", media_id);
	media_id_str = strdup(tmp);
	if (bundle_add_str(msg, "media_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	sprintf(tmp, "%d", msg_type);
	msg_type_str = strdup(tmp);
	if (bundle_add_str(msg, "message_type", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (file_path) {
		if (bundle_add_str(msg, "file_path", file_path) != 0)	{
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
			return;
		}
	} else {
		if (bundle_add_str(msg, "file_path", "") != 0)	{
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
			return;
		}
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", type_of_chat);
	type_of_chat_str = strdup(tmp);
	if (bundle_add_str(msg, "type_of_chat", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if (result != SVC_RES_OK || !ad->is_server_ready) {
		insert_unsent_media_message_to_db("Tizen Telegram", "message_transport", buddy_id_str, msg_id_str, media_id_str, msg_type_str, file_path, type_of_chat_str);
	}
	bundle_free(msg);

	if(buddy_id_str) {
		free(buddy_id_str);
		buddy_id_str = NULL;
	}
	if(msg_id_str) {
		free(msg_id_str);
		msg_id_str = NULL;
	}
	if(media_id_str) {
		free(media_id_str);
		media_id_str = NULL;
	}
	if(msg_type_str) {
		free(msg_type_str);
		msg_type_str = NULL;
	}
	if(type_of_chat_str) {
		free(type_of_chat_str);
		type_of_chat_str = NULL;
	}
}


Eina_Bool send_request_for_media_downloading(service_client* service_client, const int buddy_id, const long long  media_id)
{
	bundle *msg;
	char tmp[50];
	int result;

	if (!service_client) {
		// error
		return EINA_FALSE;
	}

	msg = bundle_create();
	if (!msg) {
		return EINA_FALSE;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return EINA_FALSE;
	}

	if (bundle_add_str(msg, "command", "media_download_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return EINA_FALSE;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}


	snprintf(tmp, sizeof(tmp) - 1, "%lld", media_id);
	if (bundle_add_str(msg, "media_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		return EINA_FALSE;
	}
	bundle_free(msg);
	return EINA_TRUE;
}

void send_contacts_list_to_server(service_client* service_client, Eina_List* contacts_list)
{
	bundle *msg;
	int count;
	char tmp[50];
	char *first_name;
	char *last_name;
	char *phone_number;
	Eina_List *l;
	contact_data_s* contact_data;
	int i;

	if (!service_client || !contacts_list) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "device_contact_list") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	count = eina_list_count(contacts_list);
	snprintf(tmp, sizeof(tmp) - 1, "%d", count);

	if (bundle_add_str(msg, "count", tmp) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	i = 0;

	EINA_LIST_FOREACH(contacts_list, l, contact_data) {
		phone_number = contact_data->phone_number;
		if (!phone_number) {
			// error.
			LOGE("Phone number is not valid");
			continue;
		}

		first_name = contact_data->first_name;
		if (!first_name) {
			first_name = contact_data->display_name;
			if (!first_name) {
				first_name = "";
			}
		}

		last_name = contact_data->last_name;
		if (!last_name) {
			last_name = "";
		}

		snprintf(tmp, sizeof(tmp) - 1, "first_name_%d", i);
		if (bundle_add_str(msg, tmp, first_name) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
			return;
		}

		snprintf(tmp, sizeof(tmp) - 1, "last_name_%d", i);
		if (bundle_add_str(msg, tmp, last_name) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
			return;
		}

		snprintf(tmp, sizeof(tmp) - 1, "phone_number_%d", i);
		if (bundle_add_str(msg, tmp, phone_number) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
			return;
		}

		i++;
	}

	int result = SVC_RES_FAIL;
	result = service_client_send_message(service_client, msg);

	if(result != SVC_RES_OK) {
		// error
	}

	bundle_free(msg);

}

void send_group_creation_request_to_server(service_client* service_client, Eina_List* buddy_list, const char* group_name, const char* group_image)
{
	bundle *msg;
	int count;
	char tmp[50];
	user_data_with_pic_s *item;
	user_data_s *contact_data;
	Eina_List *l;
	int i;
	char buddy_id_key[20];
	int result;

	if (!service_client || !buddy_list || !group_name) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "group_creation_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	count = eina_list_count(buddy_list);
	snprintf(tmp, sizeof(tmp) - 1, "%d", count);

	if (bundle_add_str(msg, "count", tmp) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	i = 0;
	EINA_LIST_FOREACH(buddy_list, l, item) {
		contact_data = item->use_data;
		if (!contact_data) {
			LOGE("Invalid contact_data");
			continue;
		}

		snprintf(tmp, sizeof(tmp) - 1, "%d", contact_data->user_id.id);
		snprintf(buddy_id_key, sizeof(buddy_id_key) - 1, "buddy_id_%d", i);

		if (bundle_add_str(msg, buddy_id_key, tmp) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
			return;
		}

		i++;
	}

	if (bundle_add_str(msg, "group_name", group_name) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (group_image) {
		if (bundle_add_str(msg, "group_image", group_image) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
			return;
		}
	} else {
		if (bundle_add_str(msg, "group_image", "") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
			return;
		}
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);

}

void send_set_group_chat_new_title_request(service_client* service_client, int user_id, const char* new_title)
{
	bundle *msg;
	char tmp[50];
	int result;

	if (!service_client || !new_title) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "set_group_chat_new_title_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", user_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "new_title", new_title) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_remove_buddy_from_group_chat_request(service_client* service_client, int user_id, int chat_id)
{
	bundle *msg;
	char tmp[50];
	char ctmp[50];
	int result;

	if (!service_client) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "remove_buddy_from_chat_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", user_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	snprintf(ctmp, sizeof(ctmp) - 1, "%d", chat_id);

	if (bundle_add_str(msg, "chat_id", ctmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}


	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_add_buddy_to_group_chat_request(service_client* service_client, int user_id, int chat_id)
{
	bundle *msg;
	char tmp[50];
	char ctmp[50];
	int result;

	if (!service_client) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "add_new_buddy_to_chat_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", user_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	snprintf(ctmp, sizeof(ctmp) - 1, "%d", chat_id);

	if (bundle_add_str(msg, "chat_id", ctmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}


	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_set_group_chat_profile_pic_request(service_client* service_client, int user_id, const char* file_path)
{
	bundle *msg;
	char tmp[50];
	int result;

	if (!service_client || !file_path) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "set_group_chat_profile_pic_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", user_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "file_path", file_path) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_set_profile_pic_request(service_client* service_client, int user_id, const char* file_path)
{
	bundle *msg;
	char tmp[50];
	int result;

	if (!service_client || !file_path) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "set_profile_pic_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", user_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "file_path", file_path) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_set_username_request(service_client* service_client, int user_id, const char* username)
{
	bundle *msg;
	char tmp[50];
	int result;

	if (!service_client || !username) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "set_username_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(tmp, sizeof(tmp) - 1, "%d", user_id);

	if (bundle_add_str(msg, "buddy_id", tmp) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "username", username) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}


void send_request_for_delete_notifications(service_client* service_client)
{
	bundle *msg;
	int result;

	if (!service_client) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		LOGE("Failed to create a bundle");
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "delete_all_notifications") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
		LOGE("Failed to send a service message");
	}

	bundle_free(msg);
}

void send_request_for_server_connection_status(service_client* service_client)
{
	bundle *msg;
	int result;

	if (!service_client) {
		// error
		return;
	}

	msg = bundle_create();
	if (!msg) {
		LOGE("Failed to create a bundle");
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "server_connection_status") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
		LOGE("Failed to send a service message");
	}

	bundle_free(msg);
}
