/**
 * @file server_requests.c
 * @date Jun 26, 2015
 * @author sandeep
 */

#include "server_requests.h"
#include "device_contacts_manager.h"

void send_request_for_registration(service_client* service_client, const char* phone_number, Eina_Bool through_sms)
{
	if (!service_client || !phone_number) {
		// error
		return;
	}

	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "registration") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "phone_number", phone_number) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char* sms_req = NULL;

	if (through_sms) {
		sms_req = "true";
	} else {
		sms_req = "false";
	}

	if (bundle_add_str(msg, "through_sms", sms_req) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	int result = SVC_RES_FAIL;
	result = service_client_send_message(service_client, msg);

	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_request_for_profile_registration(service_client* service_client, const char* first_name, const char* last_name)
{
	if (!service_client || !first_name || !last_name) {
		// error
		return;
	}

	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "profile_registration") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "first_name", first_name) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "last_name", last_name) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	int result = SVC_RES_FAIL;
	result = service_client_send_message(service_client, msg);

	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_request_for_validation(service_client* service_client, const char* sms_code)
{
	if (!service_client || !sms_code) {
		// error
		return;
	}

	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "code_validation") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "sms_code", sms_code) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	int result = SVC_RES_FAIL;
	result = service_client_send_message(service_client, msg);

	if (result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_request_for_message_transport(service_client* service_client, const int buddy_id, const int message_id, const int msg_type, const char* data, const int type_of_chat)
{
	if (!service_client || !data) {
		// error
		return;
	}

	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "message_transport") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", buddy_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char message_id_str[50];
	sprintf(message_id_str, "%d", message_id);

	if (bundle_add_str(msg, "message_id", message_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char msg_type_str[10];
	sprintf(msg_type_str, "%d", msg_type);

	if (bundle_add_str(msg, "message_type", msg_type_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "message_data", data) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char type_of_chat_str[50];
	sprintf(type_of_chat_str, "%d", type_of_chat);

	if (bundle_add_str(msg, "type_of_chat", type_of_chat_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	int result = SVC_RES_FAIL;
	result = service_client_send_message(service_client, msg);

	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_request_for_media_transport(service_client* service_client, const int buddy_id, const int message_id, const int media_id,  const int msg_type, const char* file_path, const int type_of_chat)
{
	if (!service_client || !file_path) {
		// error
		return;
	}

	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "media_transport") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", buddy_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char message_id_str[50];
	sprintf(message_id_str, "%d", message_id);

	if (bundle_add_str(msg, "message_id", message_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char media_id_str[50];
	sprintf(media_id_str, "%d", media_id);

	if (bundle_add_str(msg, "media_id", media_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char msg_type_str[10];
	sprintf(msg_type_str, "%d", msg_type);

	if (bundle_add_str(msg, "message_type", msg_type_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "file_path", file_path) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char type_of_chat_str[50];
	sprintf(type_of_chat_str, "%d", type_of_chat);

	if (bundle_add_str(msg, "type_of_chat", type_of_chat_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	int result = SVC_RES_FAIL;
	result = service_client_send_message(service_client, msg);

	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}


void send_request_for_image_downloading(service_client* service_client, const int buddy_id, const long long  media_id)
{
	if (!service_client) {
		// error
		return;
	}

	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "media_download_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	if (bundle_add_str(msg, "buddy_id", buddy_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char media_id_str[50];
	sprintf(media_id_str, "%lld", media_id);

	if (bundle_add_str(msg, "media_id", media_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	int result = SVC_RES_FAIL;
	result = service_client_send_message(service_client, msg);

	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);
}

void send_contacts_list_to_server(service_client* service_client, Eina_List* contacts_list)
{
	if (!service_client || !contacts_list) {
		// error
		return;
	}

	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "device_contact_list") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	int count = eina_list_count(contacts_list);
	char count_str[50];
	sprintf(count_str, "%d", count);

	if (bundle_add_str(msg, "count", count_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	for (int i = 0; i < count ; i++) {
		contact_data_s* contact_data = eina_list_nth(contacts_list, i);

		char* first_name = contact_data->first_name;
		if (!first_name) {
			first_name = contact_data->display_name;
		}
		if (!first_name) {
			first_name = "";
		}

		char* last_name = contact_data->last_name;
		if (!last_name) {
			last_name = "";
		}

		char* phone_number = contact_data->phone_number;
		if (!phone_number) {
			// error.
			continue;
		}

		char count_str[10];
		sprintf(count_str, "%d", i);

		char first_name_key[20];
		strcpy(first_name_key, "first_name_");
		strcat(first_name_key, count_str);

		char last_name_key[20];
		strcpy(last_name_key, "last_name_");
		strcat(last_name_key, count_str);

		char phone_number_key[20];
		strcpy(phone_number_key, "phone_number_");
		strcat(phone_number_key, count_str);

		if (bundle_add_str(msg, first_name_key, first_name) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}

		if (bundle_add_str(msg, last_name_key, last_name) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}

		if (bundle_add_str(msg, phone_number_key, phone_number) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
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
	if (!service_client || !buddy_list || !group_name) {
		// error
		return;
	}

	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "group_creation_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	int count = eina_list_count(buddy_list);
	char count_str[50];
	sprintf(count_str, "%d", count);

	if (bundle_add_str(msg, "count", count_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	for (int i = 0; i < count ; i++) {
		user_data_with_pic_s *item = eina_list_nth(buddy_list, i);
		user_data_s* contact_data = item->use_data;

		int buddy_id = contact_data->user_id.id;
		char buddy_id_str[50];
		sprintf(buddy_id_str, "%d", buddy_id);

		char count_str[10];
		sprintf(count_str, "%d", i);

		char buddy_id_key[20];
		strcpy(buddy_id_key, "buddy_id_");
		strcat(buddy_id_key, count_str);

		if (bundle_add_str(msg, buddy_id_key, buddy_id_str) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	}

	if (bundle_add_str(msg, "group_name", group_name) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (group_image) {
		if (bundle_add_str(msg, "group_image", group_image) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	} else {
		if (bundle_add_str(msg, "group_image", "") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	}

	int result = SVC_RES_FAIL;
	result = service_client_send_message(service_client, msg);

	if(result != SVC_RES_OK) {
		// error
	}
	bundle_free(msg);

}
