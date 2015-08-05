/*
 * server_response.c
 *
 *  Created on: Jun 26, 2015
 *      Author: sandeep
 */

#include "server_response.h"
#include <bundle.h>
#include "logger.h"

void process_registration_command(char* phone_no, Eina_Bool trough_sms)
{
	if (tg_data->tg_state != TG_ENGINE_STATE_REGISTRATION || !phone_no) {
		return;
	}

	if (!tg_data || !TLS) {
		// service not running. error handling
		return;
	}

	if (tg_data ->phone_number) {
		free(tg_data->phone_number);
		tg_data->phone_number = NULL;
	}

	tg_data->phone_number = strdup(phone_no);
	if (tg_data->get_string) {
		tg_data->get_string(TLS, tg_data->phone_number, tg_data->callback_arg);
	}
}

void process_validation_command(char* code)
{
	if (tg_data->tg_state != TG_ENGINE_STATE_CODE_REQUEST || !code) {
		return;
	}

	if (!tg_data || !TLS) {
		// service not running. error handling
		return;
	}
	tg_data->get_string(TLS, code, tg_data->callback_arg);
}

void process_send_message_command(int buddy_id, int msg_type, char* msg_data, int type_of_chat)
{
	if (!msg_data || !TLS) {
		return;
	}
	send_message_to_buddy(buddy_id, msg_type, msg_data, type_of_chat);
}

void process_send_media_command(int buddy_id, int msg_type, char* file_path)
{
	if (!file_path || !TLS) {
		return;
	}
	send_media_to_buddy(buddy_id, msg_type, file_path);
}


void process_media_download_command(int buddy_id, long long media_id)
{
	media_download_request(buddy_id, media_id);
}

void process_add_contacts_command(int size, Eina_List* contact_list)
{
	add_contacts_to_user(size, contact_list);
}

void process_new_group_create_command(Eina_List* buddy_ids, const char* group_name, const char* group_icon)
{
	create_new_group(buddy_ids, group_name, group_icon);
}

void send_registration_response(Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "registration_done") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "phone_number", tg_data->phone_number) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (is_success) {
		if (bundle_add_str(msg, "is_success", "true") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	} else {
		if (bundle_add_str(msg, "is_success", "false") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}

	bundle_free(msg);
}

void send_new_group_added_response(int chat_id)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "new_group_added") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char chat_id_str[50];
	sprintf(chat_id_str,"%d",chat_id);
	if (bundle_add_str(msg, "chat_id", chat_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}
    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}

	bundle_free(msg);
}

void send_chat_profile_pic_updated_response(int chat_id, char* filename)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "new_group_icon_added") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char chat_id_str[50];
	sprintf(chat_id_str,"%d",chat_id);
	if (bundle_add_str(msg, "chat_id", chat_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}
	if (bundle_add_str(msg, "chat_icon_path", filename) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}
    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}

	bundle_free(msg);
}

void send_name_registration_response()
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "name_registration_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}
    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_add_contacts_request()
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "add_contacts_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}
    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_contacts_and_chats_load_done_response(Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "contacts_and_chats_load_done") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (is_success) {
		if (bundle_add_str(msg, "is_success", "true") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	} else {
		if (bundle_add_str(msg, "is_success", "false") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_contacts_load_done_response(Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "contacts_load_done") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (is_success) {
		if (bundle_add_str(msg, "is_success", "true") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	} else {
		if (bundle_add_str(msg, "is_success", "false") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_buddy_profile_pic_updated_response(int buddy_id, char* file_path)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "buddy_profile_pic_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "user_id", usr_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "file_path", file_path) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_message_received_response(int from_id, int to_id, long long message_id, int type_of_chat)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "message_received") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char from_id_str[50];
	sprintf(from_id_str,"%d",from_id);

	if (bundle_add_str(msg, "from_id", from_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char to_id_str[50];
	sprintf(to_id_str,"%d",to_id);

	if (bundle_add_str(msg, "to_id", to_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char msg_id_str[50];
	sprintf(msg_id_str,"%lld",message_id);

	if (bundle_add_str(msg, "message_id", msg_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char type_of_chat_str[50];
	sprintf(type_of_chat_str,"%d",type_of_chat);

	if (bundle_add_str(msg, "type_of_chat", type_of_chat_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_message_read_by_buddy_response(int buddy_id, int message_id, char* table_name, char* phone, int type_of_chat)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "message_read_by_buddy") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char msg_id_str[50];
	sprintf(msg_id_str,"%ld",message_id);

	if (bundle_add_str(msg, "message_id", msg_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "table_name", table_name) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "phone_number", phone) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char type_of_chat_str[50];
	sprintf(type_of_chat_str,"%d",type_of_chat);

	if (bundle_add_str(msg, "type_of_chat", type_of_chat_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_message_sent_to_buddy_response(int buddy_id, int message_id, char* table_name, char* phone, int type_of_chat)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "message_sent_to_buddy") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char msg_id_str[50];
	sprintf(msg_id_str,"%ld",message_id);

	if (bundle_add_str(msg, "message_id", msg_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "table_name", table_name) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "phone_number", phone) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char type_of_chat_str[50];
	sprintf(type_of_chat_str,"%d",type_of_chat);

	if (bundle_add_str(msg, "type_of_chat", type_of_chat_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_media_download_completed_response(int buddy_id, long long media_id, const char* filename)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "media_download_completed") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char media_id_str[50];
	sprintf(media_id_str,"%lld",media_id);

	if (bundle_add_str(msg, "media_id", media_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "file_name", filename) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_contact_updated_response(int buddy_id, char* update_message)
{
	if (!update_message) {
		return;
	}
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "contact_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "update_message", update_message) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_buddy_status_updated_response(int buddy_id)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "buddy_status_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}

void send_buddy_type_notification_response(int buddy_id, char* budy_name, int type_status)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "type_status_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "buddy_name", budy_name) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char type_status_str[50];
	sprintf(type_status_str,"%d",type_status);

	if (bundle_add_str(msg, "type_status", type_status_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

    int result = SVC_RES_FAIL;
    result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}


