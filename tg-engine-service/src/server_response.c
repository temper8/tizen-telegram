/**
 * @file server_response.c
 * @date Jun 26, 2015
 * @file sandeep
 */

#include <bundle.h>
#include "logger.h"
#include "tg_engine.h"
#include "server_response.h"
#include "tg_db_wrapper.h"
#include "tg_common.h"
#include <badge.h>

void process_registration_command(tg_engine_data_s *tg_data, char* phone_no, Eina_Bool trough_sms)
{
	if (trough_sms && (tg_data->tg_state != TG_ENGINE_STATE_REGISTRATION || !phone_no)) {
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

	if (!trough_sms) {
		request_for_code_via_call(tgl_engine_get_TLS(), phone_no, trough_sms);
		return;
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

void process_delete_selected_group_chats_request(tg_engine_data_s* tg_data, Eina_List *sel_grp_chats)
{
	if (!tgl_engine_get_TLS()) {
		return;
	}
	delete_selected_group_chat(tg_data, sel_grp_chats);
}

void process_delete_group_chat_request(tg_engine_data_s* tg_data, int chat_id)
{
	if (!tgl_engine_get_TLS()) {
		return;
	}
	leave_group_chat(tg_data, chat_id);
}

void process_add_user_request(tg_engine_data_s* tg_data, int buddy_id, char *first_name, char *last_name, char *phone_num)
{
	if (!tgl_engine_get_TLS()) {
		return;
	}
	do_add_buddy(buddy_id, first_name, last_name, phone_num);
}

void process_update_chat_request(tg_engine_data_s* tg_data, int chat_id)
{
	if (!tgl_engine_get_TLS()) {
		return;
	}
	do_update_chat_info(chat_id);
}


void process_delete_user_request(tg_engine_data_s* tg_data, int buddy_id)
{
	if (!tgl_engine_get_TLS()) {
		return;
	}
	do_delete_buddy(buddy_id);
}

void process_block_user_request(tg_engine_data_s* tg_data, int buddy_id)
{
	if (!tgl_engine_get_TLS()) {
		return;
	}
	do_block_buddy(buddy_id);
}

void process_unblock_user_request(tg_engine_data_s* tg_data, int buddy_id)
{
	if (!tgl_engine_get_TLS()) {
		return;
	}
	do_unblock_buddy(buddy_id);
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

void process_set_group_chat_new_title_command(tg_engine_data_s *tg_data, int buddy_id, const char *new_title)
{
	set_group_chat_new_title(tg_data, buddy_id, new_title);
}

void process_add_new_buddy_to_chat_command(tg_engine_data_s *tg_data, int s_buddy_id, int s_chat_id)
{
	set_group_chat_add_new_buddy(tg_data, s_buddy_id, s_chat_id);
}

void process_remove_buddy_from_chat_command(tg_engine_data_s *tg_data, int s_buddy_id, int s_chat_id)
{
	set_group_chat_remove_buddy(tg_data, s_buddy_id, s_chat_id);
}

void process_set_group_chat_profile_pic_command(tg_engine_data_s *tg_data, int buddy_id, const char *file_path)
{
	set_group_chat_profile_picture(tg_data, buddy_id, file_path);
}

void process_set_profile_pic_command(tg_engine_data_s *tg_data, int buddy_id, const char *file_path)
{
	set_profile_picture(tg_data, buddy_id, file_path);
}

void process_set_username_command(tg_engine_data_s *tg_data, int buddy_id, const char *username)
{
	set_user_name(tg_data, buddy_id, username);
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

	result = SVC_RES_FAIL;
	result = tg_server_send_message(tg_data->tg_server, msg);
	if(result != SVC_RES_OK) {
		// error: cient not ready
	}

	bundle_free(msg);
}

void send_new_group_added_response(tg_engine_data_s *tg_data, int chat_id)
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

void send_new_buddy_added_response(tg_engine_data_s *tg_data, int buddy_id)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "new_buddy_added") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char buddy_id_str[50];
	sprintf(buddy_id_str,"%d",buddy_id);
	if (bundle_add_str(msg, "buddy_id", buddy_id_str) != 0)	{
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

void send_response_to_group_chat_updated_response(tg_engine_data_s *tg_data, int chat_id)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "response_group_chat_updated") != 0) {
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

void send_group_chat_updated_response(tg_engine_data_s *tg_data, int chat_id, const char *type_of_change)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "group_chat_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char chat_id_str[50];
	sprintf(chat_id_str,"%d",chat_id);
	if (bundle_add_str(msg, "chat_id", chat_id_str) != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "type_of_change", type_of_change) != 0)	{
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

void send_chat_profile_pic_updated_response(tg_engine_data_s *tg_data, int chat_id, char* filename)
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

void send_name_registration_response(tg_engine_data_s *tg_data)
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

void send_add_contacts_request(tg_engine_data_s *tg_data)
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

void send_contacts_and_chats_load_done_response(tg_engine_data_s *tg_data, Eina_Bool is_success)
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

void send_self_user_name_updated_response(tg_engine_data_s *tg_data, char *username, Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "self_username_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "username", username) != 0) {
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

void send_self_profile_picture_updated_response(tg_engine_data_s *tg_data, char *file_path, Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "self_profile_picture_updated") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "file_path", file_path) != 0) {
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

void send_contacts_load_done_response(tg_engine_data_s *tg_data, Eina_Bool is_success)
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

void send_buddy_profile_pic_updated_response(tg_engine_data_s *tg_data, int buddy_id, char* file_path)
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

void send_message_received_response(tg_engine_data_s *tg_data, int from_id, int to_id, long long message_id, int type_of_chat)
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
		// send notification
		char *icon_path = ui_utils_get_resource(DEFAULT_TELEGRAM_ICON);
		char *title = "Telegram";
		char content[512];

		int unread_msg_cnt = get_number_of_unread_messages();
		sprintf(content, "%d new messages received.", unread_msg_cnt);

		char *sound_track = NULL;
		char *app_id = TELEGRAM_APP_ID;
		tg_notification_create(tg_data, icon_path, title, content, sound_track, app_id);

		int err = badge_set_count(TELEGRAM_APP_ID, unread_msg_cnt);
		if (BADGE_ERROR_NONE != err) {

		}
	}
	bundle_free(msg);
}

void send_message_read_by_buddy_response(tg_engine_data_s *tg_data, int buddy_id, int message_id, char* table_name, char* phone, int type_of_chat)
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
	sprintf(msg_id_str,"%d", message_id);

	if (bundle_add_str(msg, "message_id", msg_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (table_name) {
		if (bundle_add_str(msg, "table_name", table_name) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	} else {
		if (bundle_add_str(msg, "table_name", "") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	}

	if (phone) {
		if (bundle_add_str(msg, "phone_number", phone) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	} else {
		if (bundle_add_str(msg, "phone_number", "") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}

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

void send_group_chat_delete_buddy_response(tg_engine_data_s *tg_data, int peer_id, Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "group_chat_buddy_deleted_response") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",peer_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
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

void send_group_chat_new_buddy_response(tg_engine_data_s *tg_data, int peer_id, Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "group_chat_new_buddy_added_response") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",peer_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
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

void send_group_chat_rename_response(tg_engine_data_s *tg_data, int peer_id, Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "group_chat_rename_response") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",peer_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
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


void send_buddy_readded_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "buddy_readded") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
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

void send_buddy_deleted_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "buddy_deleted") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
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

void send_buddy_blocked_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "buddy_blocked") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
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

void send_buddy_unblocked_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "buddy_unblocked") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
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

void send_selected_group_chats_deleted_response(tg_engine_data_s *tg_data)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "selected_group_chats_deleted_response") != 0) {
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

void send_group_chat_deleted_response(tg_engine_data_s *tg_data, int chat_id, Eina_Bool is_success)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "group_chat_deleted_response") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",chat_id);

	if (bundle_add_str(msg, "chat_id", usr_id_str) != 0) {
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

void send_message_sent_to_buddy_response(tg_engine_data_s *tg_data, int buddy_id, int message_id, char* table_name, Eina_Bool is_success, int type_of_chat)
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
	sprintf(msg_id_str,"%d", message_id);

	if (bundle_add_str(msg, "message_id", msg_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "table_name", table_name) != 0) {
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

void send_video_thumb_download_completed_response(tg_engine_data_s *tg_data, int buddy_id, int to_id, long long media_id, const char* filename)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "video_thumb_download_completed") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char usr_id_str[50];
	sprintf(usr_id_str,"%d",buddy_id);

	if (bundle_add_str(msg, "buddy_id", usr_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char to_id_str[50];
	sprintf(to_id_str,"%d",to_id);

	if (bundle_add_str(msg, "to_peer_id", to_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char media_id_str[50];
	sprintf(media_id_str,"%lld",media_id);

	if (bundle_add_str(msg, "media_id", media_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (filename) {
		if (bundle_add_str(msg, "file_name", filename) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	} else  {
		if (bundle_add_str(msg, "file_name", "failed_to_load") != 0) {
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

void send_media_download_completed_response(tg_engine_data_s *tg_data, int buddy_id, int to_id, long long media_id, const char* filename)
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

	char to_id_str[50];
	sprintf(to_id_str,"%d",to_id);

	if (bundle_add_str(msg, "to_peer_id", to_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char media_id_str[50];
	sprintf(media_id_str,"%lld",media_id);

	if (bundle_add_str(msg, "media_id", media_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (filename) {
		if (bundle_add_str(msg, "file_name", filename) != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	} else  {
		if (bundle_add_str(msg, "file_name", "failed_to_load") != 0) {
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

void send_contact_updated_response(tg_engine_data_s *tg_data, int buddy_id, char* update_message)
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

void send_buddy_status_updated_response(tg_engine_data_s *tg_data, int buddy_id)
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

void send_buddy_status_notification_response(tg_engine_data_s *tg_data, int buddy_id, char* budy_name, int online)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "user_status_updated") != 0) {
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

	if (online) {
		if (bundle_add_str(msg, "user_status", "online") != 0) {
			ERR("Failed to add data by key to bundle");
			bundle_free(msg);
		}
	} else {
		if (bundle_add_str(msg, "user_status", "offline") != 0) {
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

void send_buddy_type_notification_response(tg_engine_data_s *tg_data, int buddy_id, char* budy_name, int type_status)
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

void send_response_for_server_connection_status(tg_engine_data_s *tg_data, Eina_Bool connection_status)
{
	bundle *msg;

	msg = bundle_create();
	if (!msg) {
		ERR("Failed to create a bundle");
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

	if (bundle_add_str(msg, "connection_status", connection_status ? "true" : "false") != BUNDLE_ERROR_NONE) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
		return;
	}

	int result = SVC_RES_FAIL;
	result = tg_server_send_message(tg_data->tg_server, msg);

	if(result != SVC_RES_OK) {
		// error: cient not ready
	}
	bundle_free(msg);
}
