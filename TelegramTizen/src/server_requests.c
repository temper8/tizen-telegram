/**
 * @file server_requests.c
 * @date Jun 26, 2015
 * @author sandeep
 */

#include "server_requests.h"
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

void send_request_for_marked_as_read(service_client* service_client, const int buddy_id, const int type_of_chat)
{
	bundle *msg;
	char type_of_chat_str[50];
	char buddy_id_str[50];
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

	snprintf(buddy_id_str, sizeof(buddy_id_str) - 1, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", buddy_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(type_of_chat_str, sizeof(type_of_chat_str) - 1, "%d", type_of_chat);
	if (bundle_add_str(msg, "type_of_chat", type_of_chat_str) != 0)	{
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

void send_request_for_message_transport(service_client* service_client, const int buddy_id, const int message_id, const int msg_type, const char* data, const int type_of_chat)
{
	char buddy_id_str[50];
	bundle *msg;
	char message_id_str[50];
	char msg_type_str[10];
	char type_of_chat_str[50];
	int result;

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

	snprintf(buddy_id_str, sizeof(buddy_id_str), "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", buddy_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(message_id_str, sizeof(message_id_str) - 1, "%d", message_id);

	if (bundle_add_str(msg, "message_id", message_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(msg_type_str, sizeof(msg_type_str) - 1, "%d", msg_type);

	if (bundle_add_str(msg, "message_type", msg_type_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "message_data", data) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}


	snprintf(type_of_chat_str, sizeof(type_of_chat_str), "%d", type_of_chat);

	if (bundle_add_str(msg, "type_of_chat", type_of_chat_str) != 0)	{
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

void send_request_for_media_transport(service_client* service_client, const int buddy_id, const int message_id, const int media_id,  const int msg_type, const char* file_path, const int type_of_chat)
{
	bundle *msg;
	char buddy_id_str[50];
	char message_id_str[50];
	char media_id_str[50];
	char msg_type_str[10];
	char type_of_chat_str[50];
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

	if (bundle_add_str(msg, "command", "media_transport") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(buddy_id_str, sizeof(buddy_id_str) - 1, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", buddy_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(message_id_str, sizeof(message_id_str) - 1, "%d", message_id);

	if (bundle_add_str(msg, "message_id", message_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(media_id_str, sizeof(media_id_str) - 1, "%d", media_id);
	if (bundle_add_str(msg, "media_id", media_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	sprintf(msg_type_str, "%d", msg_type);

	if (bundle_add_str(msg, "message_type", msg_type_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "file_path", file_path) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(type_of_chat_str, sizeof(type_of_chat_str) - 1, "%d", type_of_chat);

	if (bundle_add_str(msg, "type_of_chat", type_of_chat_str) != 0)	{
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


void send_request_for_image_downloading(service_client* service_client, const int buddy_id, const long long  media_id)
{
	bundle *msg;
	char buddy_id_str[50];
	char media_id_str[50];
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

	if (bundle_add_str(msg, "command", "media_download_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	snprintf(buddy_id_str, sizeof(buddy_id_str) - 1, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", buddy_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}


	snprintf(media_id_str, sizeof(media_id_str) - 1, "%lld", media_id);
	if (bundle_add_str(msg, "media_id", media_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	result = service_client_send_message(service_client, msg);
	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_contacts_list_to_server(service_client* service_client, Eina_List* contacts_list)
{
	bundle *msg;
	int count;
	char count_str[50];
	char first_name_key[20];
	char last_name_key[20];
	char phone_number_key[20];
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

	snprintf(count_str, sizeof(count_str) - 1, "%d", count);

	if (bundle_add_str(msg, "count", count_str) != 0) {
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

		snprintf(first_name_key, sizeof(first_name_key) - 1, "first_name_%d", i);
		snprintf(last_name_key, sizeof(last_name_key) - 1, "last_name_%d", i);
		snprintf(phone_number_key, sizeof(phone_number_key) - 1, "phone_number_%d", i);

		if (bundle_add_str(msg, first_name_key, first_name) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
			return;
		}

		if (bundle_add_str(msg, last_name_key, last_name) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
			return;
		}

		if (bundle_add_str(msg, phone_number_key, phone_number) != 0) {
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
	char count_str[50];
	user_data_with_pic_s *item;
	user_data_s *contact_data;
	Eina_List *l;
	int i;
	char buddy_id_str[50];
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
	snprintf(count_str, sizeof(count_str) - 1, "%d", count);

	if (bundle_add_str(msg, "count", count_str) != 0) {
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

		snprintf(buddy_id_str, sizeof(buddy_id_str) - 1, "%d", contact_data->user_id.id);
		snprintf(buddy_id_key, sizeof(buddy_id_key) - 1, "buddy_id_%d", i);

		if (bundle_add_str(msg, buddy_id_key, buddy_id_str) != 0) {
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
