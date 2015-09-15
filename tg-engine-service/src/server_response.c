/**
 * @file server_response.c
 * @date Jun 26, 2015
 * @file sandeep
 */

#include <bundle.h>
#include "logger.h"
#include "tg_engine.h"
#include "server_response.h"
#include "tg_common.h"


void process_registration_command(tg_engine_data_s *tg_data, char* phone_no, Eina_Bool trough_sms)
{
	if (tg_data->tg_state != TG_ENGINE_STATE_REGISTRATION || !phone_no) {
		return;
	}

	if (!tg_data || !tgl_engine_get_TLS()) {
		// service not running. error handling
		return;
	}

	if (tg_data->phone_number) {
		free(tg_data->phone_number);
	}
	if (phone_no) {
		tg_data->phone_number = strdup(phone_no);
	} else {
		tg_data->phone_number = NULL;
	}

	if (tg_data->get_string) {
		tg_data->get_string(tgl_engine_get_TLS(), tg_data->phone_number, tg_data->callback_arg);
	}
}

void process_validation_command(tg_engine_data_s *tg_data, char* code)
{
	if (tg_data->tg_state != TG_ENGINE_STATE_CODE_REQUEST || !code) {
		return;
	}

	if (!tg_data || !tgl_engine_get_TLS()) {
		// service not running. error handling
		return;
	}
	tg_data->get_string(tgl_engine_get_TLS(), code, tg_data->callback_arg);
}

void process_send_message_command(int buddy_id, int message_id, int msg_type, char* msg_data, int type_of_chat)
{
	if (!msg_data || !tgl_engine_get_TLS()) {
		return;
	}
	send_message_to_buddy(buddy_id, message_id, msg_type, msg_data, type_of_chat);
}

void process_marked_as_read_command(int buddy_id, int type_of_chat)
{
	if (!tgl_engine_get_TLS()) {
		return;
	}
	send_do_mark_read_messages(buddy_id, type_of_chat);
}

void process_send_media_command(int buddy_id, int message_id, int media_id, int msg_type, char* file_path, int type_of_chat)
{
	if (!file_path || !tgl_engine_get_TLS()) {
		return;
	}
	send_media_to_buddy(buddy_id, message_id, media_id, msg_type, file_path, type_of_chat);
}


void process_media_download_command(tg_engine_data_s *tg_data, int buddy_id, long long media_id)
{
	media_download_request(tg_data, buddy_id, media_id);
}

void process_add_contacts_command(tg_engine_data_s *tg_data, int size, Eina_List* contact_list)
{
	add_contacts_to_user(tg_data, size, contact_list);
}

void process_new_group_create_command(tg_engine_data_s *tg_data, Eina_List* buddy_ids, const char* group_name, const char* group_icon)
{
	create_new_group(tg_data, buddy_ids, group_name, group_icon);
}

void send_registration_response(tg_engine_data_s *tg_data, Eina_Bool is_success)
{
	bundle *msg;
	int result;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != BUNDLE_ERROR_NONE)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "registration_done") != BUNDLE_ERROR_NONE) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "phone_number", tg_data->phone_number) != BUNDLE_ERROR_NONE)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "is_success", is_success ? "true" : "false") != BUNDLE_ERROR_NONE) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_new_group_added_response(tg_engine_data_s *tg_data, int chat_id)
{
	int result;
	bundle *msg;
	const char *str;

	msg = bundle_create();
	if (!msg) {
		ERR("Unable to create the bundle");
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "new_group_added") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", chat_id);
	if (bundle_add_str(msg, "chat_id", str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_chat_profile_pic_updated_response(tg_engine_data_s *tg_data, int chat_id, char* filename)
{
	int result;
	bundle *msg;
	const char *str;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "new_group_icon_added") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", chat_id);
	if (bundle_add_str(msg, "chat_id", str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}
	if (bundle_add_str(msg, "chat_icon_path", filename) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_name_registration_response(tg_engine_data_s *tg_data)
{
	int result;
	bundle *msg;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "name_registration_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_add_contacts_request(tg_engine_data_s *tg_data)
{
	bundle *msg;
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

	if (bundle_add_str(msg, "command", "add_contacts_request") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_contacts_and_chats_load_done_response(tg_engine_data_s *tg_data, Eina_Bool is_success)
{
	int result;
	bundle *msg;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "contacts_and_chats_load_done") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "is_success", is_success ? "true" : "false") != BUNDLE_ERROR_NONE) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}


	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_contacts_load_done_response(tg_engine_data_s *tg_data, Eina_Bool is_success)
{
	bundle *msg;
	int result;

	msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "contacts_load_done") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "is_success", is_success ? "true" : "false") != BUNDLE_ERROR_NONE) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}


	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);
	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_buddy_profile_pic_updated_response(tg_engine_data_s *tg_data, int buddy_id, char* file_path)
{
	bundle *msg;
	int result;
	const char *str;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "buddy_profile_pic_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", buddy_id);
	if (bundle_add_str(msg, "user_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "file_path", file_path) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_message_received_response(tg_engine_data_s *tg_data, int from_id, int to_id, long long message_id, int type_of_chat)
{
	int result;
	bundle *msg;
	const char *str;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "message_received") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", from_id);
	if (bundle_add_str(msg, "from_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", to_id);
	if (bundle_add_str(msg, "to_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%lld", message_id);
	if (bundle_add_str(msg, "message_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", type_of_chat);
	if (bundle_add_str(msg, "type_of_chat", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_message_read_by_buddy_response(tg_engine_data_s *tg_data, int buddy_id, int message_id, char* table_name, char* phone, int type_of_chat)
{
	bundle *msg;
	int result;
	const char *str;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "message_read_by_buddy") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", buddy_id);
	if (bundle_add_str(msg, "buddy_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	str = tg_common_to_string("%d", message_id);
	if (bundle_add_str(msg, "message_id", str) != 0) {
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

	str = tg_common_to_string("%d", type_of_chat);
	if (bundle_add_str(msg, "type_of_chat", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_message_sent_to_buddy_response(tg_engine_data_s *tg_data, int buddy_id, int message_id, char* table_name, Eina_Bool is_success, int type_of_chat)
{
	bundle *msg;
	const char *str;
	int result;

	msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "message_sent_to_buddy") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", buddy_id);
	if (bundle_add_str(msg, "buddy_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", message_id);
	if (bundle_add_str(msg, "message_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "table_name", table_name) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "is_success", is_success ? "true" : "false") != BUNDLE_ERROR_NONE) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", type_of_chat);
	if (bundle_add_str(msg, "type_of_chat", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);
	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_media_download_completed_response(tg_engine_data_s *tg_data, int buddy_id, int to_id, long long media_id, const char* filename)
{
	bundle *msg;
	int result;
	const char *str;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "media_download_completed") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", buddy_id);
	if (bundle_add_str(msg, "buddy_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", to_id);
	if (bundle_add_str(msg, "to_peer_id", to_id_str) != BUNDLE_ERROR_NONE) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%lld", media_id);
	if (bundle_add_str(msg, "media_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "file_name", filename ? filename : "failed_to_load") != BUNDLE_ERROR_NONE) {
		bundle_free(msg);
		return;
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);
	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_contact_updated_response(tg_engine_data_s *tg_data, int buddy_id, char* update_message)
{
	int result;
	const char *str;
	bundle *msg;

	if (!update_message) {
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

	if (bundle_add_str(msg, "command", "contact_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", buddy_id);
	if (bundle_add_str(msg, "buddy_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "update_message", update_message) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);
	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_buddy_status_updated_response(tg_engine_data_s *tg_data, int buddy_id)
{
	bundle *msg;
	int result;
	const char *str;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "buddy_status_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	str = tg_common_to_string("%d", buddy_id);
	if (bundle_add_str(msg, "buddy_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);
	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_buddy_status_notification_response(tg_engine_data_s *tg_data, int buddy_id, char* budy_name, int online)
{
	bundle *msg;
	const char *tmp;
	int result = SVC_RES_FAIL;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "user_status_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	tmp = tg_common_to_string("%d", buddy_id);
	if (bundle_add_str(msg, "buddy_id", tmp) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "buddy_name", budy_name) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "user_status", online ? "online" : "offline") != BUNDLE_ERROR_NONE) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);
	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}

void send_buddy_type_notification_response(tg_engine_data_s *tg_data, int buddy_id, char* budy_name, int type_status)
{
	bundle *msg;
	int result;
	const char *str;

	msg = bundle_create();
	if (!msg) {
		return;
	}

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "command", "type_status_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", buddy_id);
	if (bundle_add_str(msg, "buddy_id", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, "buddy_name", buddy_name) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	str = tg_common_to_string("%d", type_status);
	if (bundle_add_str(msg, "type_status", str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	result = tg_server_send_message(tg_data->tg_server, msg);
	bundle_free(msg);
	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
}
