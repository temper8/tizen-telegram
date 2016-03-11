/*
    This file is part of Telegram application for tizen

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <bundle.h>
#include "logger.h"
#include "tg_engine.h"
#include "server_response.h"
#include "tg_db_wrapper.h"
#include "tg_common.h"
#include "tg-engine-service.h"



Eina_Bool init_response(bundle *msg, tg_engine_data_s *tg_data, const char* command)
{
	if (!msg || !tg_data)
		return EINA_FALSE;

	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0) {
		ERR("Failed to add data by key to bundle");
		return EINA_FALSE;
	}

	if (bundle_add_str(msg, "command", command) != 0) {
		ERR("Failed to add data by key to bundle");
		return EINA_FALSE;
	}
	return EINA_TRUE;
}

Eina_Bool send_response(bundle *msg, tg_engine_data_s *tg_data)
{
	int result = SVC_RES_FAIL;
	if (!msg || !tg_data)
		return EINA_FALSE;

	result = tg_server_send_message(tg_data->tg_server, msg);
	if (result != SVC_RES_OK) {
		ERR("Cient not ready");
		bundle_free(msg);
		return EINA_FALSE;
	}

	bundle_free(msg);
	return EINA_TRUE;
}

void make_base_response(tg_engine_data_s *tg_data, const char* command)
{
	bundle *msg = bundle_create();
	if (!init_response(msg, tg_data, command)) {
		bundle_free(msg);
		return;
	}

	if (!send_response(msg, tg_data))
		return;
}

void make_arg1_response(tg_engine_data_s *tg_data, const char* command,
		const char* arg1_name, const char* arg1_value)
{
	bundle *msg = bundle_create();
	if (!init_response(msg, tg_data, command)) {
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, arg1_name, arg1_value) != 0) {
		ERR("Failed to add data by key to bundle1");
		bundle_free(msg);
	}

	if (!send_response(msg, tg_data))
		return;
}

void make_arg2_response(tg_engine_data_s *tg_data, const char* command,
		const char* arg1_name, const char* arg1_value,
		const char* arg2_name, const char* arg2_value)
{
	bundle *msg = bundle_create();
	if (!init_response(msg, tg_data, command)) {
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, arg1_name, arg1_value) != 0) {
		ERR("Failed to add data by key to bundle1");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, arg2_name, arg2_value) != 0) {
		ERR("Failed to add data by key to bundle2");
		bundle_free(msg);
	}

	if (!send_response(msg, tg_data))
		return;
}

void make_arg3_response(tg_engine_data_s *tg_data, const char* command,
		const char* arg1_name, const char* arg1_value,
		const char* arg2_name, const char* arg2_value,
		const char* arg3_name, const char* arg3_value)
{
	bundle *msg = bundle_create();
	if (!init_response(msg, tg_data, command)) {
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, arg1_name, arg1_value) != 0) {
		ERR("Failed to add data by key to bundle1");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, arg2_name, arg2_value) != 0) {
		ERR("Failed to add data by key to bundle2");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, arg3_name, arg3_value) != 0) {
		ERR("Failed to add data by key to bundle3");
		bundle_free(msg);
	}

	if (!send_response(msg, tg_data))
		return;
}

void make_arg4_response(tg_engine_data_s *tg_data, const char* command,
		const char* arg1_name, const char* arg1_value,
		const char* arg2_name, const char* arg2_value,
		const char* arg3_name, const char* arg3_value,
		const char* arg4_name, const char* arg4_value)
{
	bundle *msg = bundle_create();
	if (!init_response(msg, tg_data, command)) {
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, arg1_name, arg1_value) != 0) {
		ERR("Failed to add data by key to bundle1");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, arg2_name, arg2_value) != 0) {
		ERR("Failed to add data by key to bundle2");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, arg3_name, arg3_value) != 0) {
		ERR("Failed to add data by key to bundle3");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, arg4_name, arg4_value) != 0) {
		ERR("Failed to add data by key to bundle4");
		bundle_free(msg);
	}

	if (!send_response(msg, tg_data))
		return;
}

void make_arg5_response(tg_engine_data_s *tg_data, const char* command,
		const char* arg1_name, const char* arg1_value,
		const char* arg2_name, const char* arg2_value,
		const char* arg3_name, const char* arg3_value,
		const char* arg4_name, const char* arg4_value,
		const char* arg5_name, const char* arg5_value)
{
	bundle *msg = bundle_create();
	if (!init_response(msg, tg_data, command)) {
		bundle_free(msg);
		return;
	}

	if (bundle_add_str(msg, arg1_name, arg1_value) != 0) {
		ERR("Failed to add data by key to bundle1");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, arg2_name, arg2_value) != 0) {
		ERR("Failed to add data by key to bundle2");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, arg3_name, arg3_value) != 0) {
		ERR("Failed to add data by key to bundle3");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, arg4_name, arg4_value) != 0) {
		ERR("Failed to add data by key to bundle4");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, arg5_name, arg5_value) != 0) {
		ERR("Failed to add data by key to bundle5");
		bundle_free(msg);
	}

	if (!send_response(msg, tg_data))
		return;
}

void make_chat_response(tg_engine_data_s *tg_data, int chat_id, const char* command)
{
	char id_str[64];
	snprintf(id_str, sizeof(id_str), "%d", chat_id);
	make_arg1_response(tg_data, command, "chat_id", id_str);
}

void make_buddy_response(tg_engine_data_s *tg_data, int buddy_id, const char* command)
{
	char id_str[64];
	snprintf(id_str, sizeof(id_str), "%d", buddy_id);
	make_arg1_response(tg_data, command, "buddy_id", id_str);
}

void make_boolean_response(tg_engine_data_s *tg_data, Eina_Bool is_success, const char* command)
{
	make_arg1_response(tg_data, command, "is_success", is_success ? "true" : "false");
}

void process_registration_command(tg_engine_data_s *tg_data, char* phone_no, Eina_Bool trough_sms)
{
#if 0
	if (trough_sms && (tg_data->tg_state != TG_ENGINE_STATE_REGISTRATION || !phone_no))
		return;
#endif
	if (!tg_data || !tgl_engine_get_TLS())
		return;

	if (tg_data->phone_number)
		free(tg_data->phone_number);

	if (phone_no)
		tg_data->phone_number = strdup(phone_no);
	else
		tg_data->phone_number = NULL;

	if (!trough_sms) {
		request_for_code_via_call(tgl_engine_get_TLS(), phone_no, trough_sms);
		return;
	}

	if (tg_data->get_string)
		tg_data->get_string(tgl_engine_get_TLS(), tg_data->phone_number, tg_data->callback_arg);
}

void process_validation_command(tg_engine_data_s *tg_data, char* code)
{
	if (tg_data->tg_state != TG_ENGINE_STATE_CODE_REQUEST ||
			!code)
		return;

	if (!tg_data || !tgl_engine_get_TLS())
		return;

	tg_data->get_string(tgl_engine_get_TLS(), code, tg_data->callback_arg);
}

void process_logout_command(tg_engine_data_s *tg_data)
{
	if (!tg_data)
		return;

	logout_telegram(tg_data);
}

void process_forward_message_command(int to_id, int type_of_chat, int from_id, int message_id, int temp_message_id)
{
	if (!tgl_engine_get_TLS())
		return;

	forward_message_to_buddy(to_id, type_of_chat, from_id, message_id, temp_message_id);
}

void process_typing_status_to_buddy_command(int buddy_id, int type_of_chat, int typing_status)
{
	if (!tgl_engine_get_TLS())
		return;

	send_typing_status_to_buddy(buddy_id, type_of_chat, typing_status);
}

void process_send_message_command(int buddy_id, int message_id, int msg_type, char* msg_data, int type_of_chat)
{
	if (!msg_data || !tgl_engine_get_TLS())
		return;

	send_message_to_buddy(buddy_id, message_id, msg_type, msg_data, type_of_chat);
}

void process_delete_selected_group_chats_request(tg_engine_data_s* tg_data, Eina_List *sel_grp_chats)
{
	if (!tgl_engine_get_TLS())
		return;

	delete_selected_group_chat(tg_data, sel_grp_chats);
}

void process_delete_group_chat_request(tg_engine_data_s* tg_data, int chat_id)
{
	if (!tgl_engine_get_TLS())
		return;

	leave_group_chat(tg_data, chat_id);
}

void process_add_user_request(tg_engine_data_s* tg_data, int buddy_id, char *first_name, char *last_name, char *phone_num)
{
	if (!tgl_engine_get_TLS())
		return;

	do_add_buddy(buddy_id, first_name, last_name, phone_num);
}

void process_update_chat_request(tg_engine_data_s* tg_data, int chat_id)
{
	if (!tgl_engine_get_TLS())
		return;

	do_update_chat_info(chat_id);
}

void process_send_secret_chat_request(tg_engine_data_s* tg_data, int buddy_id)
{
	if (!tgl_engine_get_TLS())
		return;
	request_for_secret_chat(buddy_id);
}

void process_delete_user_request(tg_engine_data_s* tg_data, int buddy_id)
{
	if (!tgl_engine_get_TLS())
		return;

	do_delete_buddy(buddy_id);
}

void process_delete_message_request(tg_engine_data_s* tg_data, int buddy_id, int message_id)
{
	if (!tgl_engine_get_TLS())
		return;

	do_delete_message(buddy_id, message_id);
}

void process_block_user_request(tg_engine_data_s* tg_data, int buddy_id)
{
	if (!tgl_engine_get_TLS())
		return;

	do_block_buddy(buddy_id);
}

void process_unblock_user_request(tg_engine_data_s* tg_data, int buddy_id)
{
	if (!tgl_engine_get_TLS())
		return;

	do_unblock_buddy(buddy_id);
}

void process_delete_all_msgs_from_table_command(int buddy_id, int type_of_chat)
{
	if (!tgl_engine_get_TLS())
		return;

	delete_all_messages_from_chat(buddy_id, type_of_chat);
}

void process_marked_as_read_command(int buddy_id, int type_of_chat)
{
	if (!tgl_engine_get_TLS())
		return;

	send_do_mark_read_messages(buddy_id, type_of_chat);
}

void process_send_media_command(int buddy_id, int message_id, int media_id, int msg_type, char* file_path, int type_of_chat)
{
	if (!file_path || !tgl_engine_get_TLS())
		return;

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

void process_update_display_name_command(tg_engine_data_s *tg_data, int buddy_id, const char *first_name, const char *last_name)
{
	update_user_display_name(tg_data, buddy_id, first_name, last_name);
}

void process_set_username_command(tg_engine_data_s *tg_data, int buddy_id, const char *username)
{
	set_user_name(tg_data, buddy_id, username);
}

void send_request_phone_num_again(tg_engine_data_s *tg_data)
{
	make_arg1_response(tg_data, "request_phone_num_again", "phone_number", tg_data->phone_number);
}

void send_request_code_again(tg_engine_data_s *tg_data)
{
	make_arg1_response(tg_data, "request_reg_code_again", "phone_number", tg_data->phone_number);
}

void send_registration_response(tg_engine_data_s *tg_data, Eina_Bool is_success)
{
	make_arg2_response(tg_data, "registration_done", "phone_number", tg_data->phone_number, "is_success", is_success ? "true" : "false");
}

void send_new_group_added_response(tg_engine_data_s *tg_data, int chat_id)
{
	make_chat_response(tg_data, chat_id, "new_group_added");
}

void send_new_buddy_added_response(tg_engine_data_s *tg_data, int buddy_id)
{
	make_buddy_response(tg_data, buddy_id, "new_buddy_added");
}

void send_response_to_group_chat_updated_response(tg_engine_data_s *tg_data, int chat_id)
{
	make_chat_response(tg_data, chat_id, "response_group_chat_updated");
}

void send_group_chat_updated_response(tg_engine_data_s *tg_data, int chat_id, const char *type_of_change)
{
	char chat_id_str[50];
	snprintf(chat_id_str, sizeof(chat_id_str), "%d", chat_id);
	make_arg2_response(tg_data, "group_chat_updated", "chat_id", chat_id_str, "type_of_change", type_of_change);
}

void send_chat_profile_pic_updated_response(tg_engine_data_s *tg_data, int chat_id, char* filename)
{
	char chat_id_str[50];
	snprintf(chat_id_str, sizeof(chat_id_str), "%d", chat_id);
	make_arg2_response(tg_data, "new_group_icon_added", "chat_id", chat_id_str, "chat_icon_path", filename);
}

void send_name_registration_response(tg_engine_data_s *tg_data)
{
	make_base_response(tg_data, "name_registration_request");
}

void send_add_contacts_request(tg_engine_data_s *tg_data)
{
	make_base_response(tg_data, "add_contacts_request");
}

void send_server_not_initialized_response(tg_engine_data_s *tg_data)
{
	make_base_response(tg_data, "server_not_initialized");
}

void send_contacts_and_chats_load_done_response(tg_engine_data_s *tg_data, Eina_Bool is_success)
{
	make_boolean_response(tg_data, is_success, "contacts_and_chats_load_done");
}

void send_self_profile_name_updated_response(tg_engine_data_s *tg_data, char *first_name, char *last_name, Eina_Bool is_success)
{
	make_arg3_response(tg_data, "self_profile_name_updated", "first_name", first_name, "last_name", last_name, "is_success", is_success ? "true" : "false");
}

void send_self_user_name_updated_response(tg_engine_data_s *tg_data, char *username, Eina_Bool is_success)
{
	make_arg2_response(tg_data, "self_username_updated", "username", username, "is_success", is_success ? "true" : "false");
}

void send_self_profile_picture_updated_response(tg_engine_data_s *tg_data, char *file_path, Eina_Bool is_success)
{
	make_arg2_response(tg_data, "self_profile_picture_updated", "file_path", file_path, "is_success", is_success ? "true" : "false");
}

void send_contacts_load_done_response(tg_engine_data_s *tg_data, Eina_Bool is_success)
{
	make_boolean_response(tg_data, is_success, "contacts_load_done");
}

void send_buddy_profile_pic_updated_response(tg_engine_data_s *tg_data, int buddy_id, char* file_path)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	make_arg2_response(tg_data, "buddy_profile_pic_updated", "user_id", usr_id_str, "file_path", file_path);
}


void send_message_with_date_received_response(tg_engine_data_s *tg_data, int from_id, int to_id, long long message_id, int date_id, int type_of_chat)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0)	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "message_received_with_date") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char from_id_str[50];
	snprintf(from_id_str, sizeof(from_id_str), "%d", from_id);

	if (bundle_add_str(msg, "from_id", from_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char to_id_str[50];
	snprintf(to_id_str, sizeof(to_id_str), "%d", to_id);

	if (bundle_add_str(msg, "to_id", to_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char msg_id_str[50];
	snprintf(msg_id_str, sizeof(msg_id_str), "%lld", message_id);

	if (bundle_add_str(msg, "message_id", msg_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char date_id_str[50];
	snprintf(date_id_str, sizeof(date_id_str), "%d", date_id);

	if (bundle_add_str(msg, "date_id", date_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char type_of_chat_str[50];
	snprintf(type_of_chat_str, sizeof(type_of_chat_str), "%d", type_of_chat);

	if (bundle_add_str(msg, "type_of_chat", type_of_chat_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (SVC_RES_OK != tg_server_send_message(tg_data->tg_server, msg))
		display_new_message_badge(get_number_of_unread_messages(), tg_data);

	bundle_free(msg);
}

void send_message_received_response(tg_engine_data_s *tg_data, int from_id, int to_id, long long message_id, int type_of_chat)
{
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "app_name", "Tizen Telegram") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (bundle_add_str(msg, "command", "message_received") != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char from_id_str[64];
	snprintf(from_id_str, sizeof(from_id_str), "%d", from_id);

	if (bundle_add_str(msg, "from_id", from_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char to_id_str[64];
	snprintf(to_id_str, sizeof(to_id_str), "%d", to_id);

	if (bundle_add_str(msg, "to_id", to_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char msg_id_str[64];
	snprintf(msg_id_str, sizeof(msg_id_str), "%lld", message_id);

	if (bundle_add_str(msg, "message_id", msg_id_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	char type_of_chat_str[64];
	snprintf(type_of_chat_str, sizeof(type_of_chat_str), "%d", type_of_chat);

	if (bundle_add_str(msg, "type_of_chat", type_of_chat_str) != 0) {
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	if (SVC_RES_OK != tg_server_send_message(tg_data->tg_server, msg))
		display_new_message_badge(get_number_of_unread_messages(), tg_data);

	bundle_free(msg);
}

void send_message_read_by_buddy_response(tg_engine_data_s *tg_data, int buddy_id, int message_id, char* table_name, char* phone, int type_of_chat)
{
	char usr_id_str[64];
	char msg_id_str[64];
	char type_of_chat_str[64];

	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	snprintf(msg_id_str, sizeof(msg_id_str), "%d", message_id);
	snprintf(type_of_chat_str, sizeof(type_of_chat_str), "%d", type_of_chat);

	make_arg5_response(tg_data, "message_read_by_buddy", "buddy_id", usr_id_str, "message_id", msg_id_str,
			"table_name", table_name ? table_name : "", "phone_number", phone ? phone : "", "type_of_chat", type_of_chat_str);
}

void send_group_chat_delete_buddy_response(tg_engine_data_s *tg_data, int peer_id, Eina_Bool is_success)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", peer_id);
	make_arg2_response(tg_data, "group_chat_buddy_deleted_response", "buddy_id", usr_id_str, "is_success", is_success ? "true" : "false");
}

void send_group_chat_new_buddy_response(tg_engine_data_s *tg_data, int peer_id, Eina_Bool is_success)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", peer_id);
	make_arg2_response(tg_data, "group_chat_new_buddy_added_response", "buddy_id", usr_id_str, "is_success", is_success ? "true" : "false");
}

void send_group_chat_rename_response(tg_engine_data_s *tg_data, int peer_id, Eina_Bool is_success)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", peer_id);
	make_arg2_response(tg_data, "group_chat_rename_response", "buddy_id", usr_id_str, "is_success", is_success ? "true" : "false");
}

void send_new_contact_added_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	make_arg2_response(tg_data, "new_contact_added", "buddy_id", usr_id_str, "is_success", is_success ? "true" : "false");
}

void send_buddy_readded_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	make_arg2_response(tg_data, "buddy_readded", "buddy_id", usr_id_str, "is_success", is_success ? "true" : "false");
}

void send_buddy_deleted_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	make_arg2_response(tg_data, "buddy_deleted", "buddy_id", usr_id_str, "is_success", is_success ? "true" : "false");
}

void send_message_deleted_response(tg_engine_data_s *tg_data, int buddy_id, int message_id, Eina_Bool is_success)
{
	char usr_id_str[64];
	char msg_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	snprintf(msg_id_str, sizeof(msg_id_str), "%d", message_id);
	make_arg3_response(tg_data, "message_deleted", "buddy_id", usr_id_str, "message_id", msg_id_str, "is_success", is_success ? "true" : "false");
}


void send_buddy_blocked_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	make_arg2_response(tg_data, "buddy_blocked", "buddy_id", usr_id_str, "is_success", is_success ? "true" : "false");
}

void send_buddy_unblocked_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	make_arg2_response(tg_data, "buddy_unblocked", "buddy_id", usr_id_str, "is_success", is_success ? "true" : "false");
}

void send_selected_group_chats_deleted_response(tg_engine_data_s *tg_data)
{
	make_base_response(tg_data, "selected_group_chats_deleted_response");
}

void send_group_chat_deleted_response(tg_engine_data_s *tg_data, int chat_id, Eina_Bool is_success)
{
	char chat_id_str[64];
	snprintf(chat_id_str, sizeof(chat_id_str), "%d", chat_id);
	make_arg2_response(tg_data, "group_chat_deleted_response", "chat_id", chat_id_str, "is_success", is_success ? "true" : "false");
}

void send_message_sent_to_buddy_response(tg_engine_data_s *tg_data, int buddy_id, int message_id, char* table_name, Eina_Bool is_success, int type_of_chat)
{
	char usr_id_str[64];
	char msg_id_str[64];
	char type_of_chat_str[64];

	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	snprintf(msg_id_str, sizeof(msg_id_str), "%d", message_id);
	snprintf(type_of_chat_str, sizeof(type_of_chat_str), "%d", type_of_chat);

	make_arg5_response(tg_data, "message_sent_to_buddy", "buddy_id", usr_id_str, "message_id", msg_id_str,
			"table_name", table_name, "is_success", is_success ? "true" : "false", "type_of_chat", type_of_chat_str);
}

void send_video_thumb_download_completed_response(tg_engine_data_s *tg_data, int buddy_id, int to_id, long long media_id, const char* filename, const char* caption)
{
	char usr_id_str[64];
	char to_id_str[64];
	char media_id_str[64];

	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	snprintf(to_id_str, sizeof(to_id_str), "%d", to_id);
	snprintf(media_id_str, sizeof(media_id_str), "%lld", media_id);

	make_arg5_response(tg_data, "video_thumb_download_completed", "buddy_id", usr_id_str,
			"to_peer_id", to_id_str, "media_id", media_id_str, "file_name", filename ? filename : "failed_to_load", "caption", caption ? caption : "");
}

void send_media_download_completed_response(tg_engine_data_s *tg_data, int buddy_id, int to_id, long long media_id, const char* filename, const char *caption)
{
	char usr_id_str[64];
		char to_id_str[64];
		char media_id_str[64];

		snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
		snprintf(to_id_str, sizeof(to_id_str), "%d", to_id);
		snprintf(media_id_str, sizeof(media_id_str), "%lld", media_id);

		make_arg5_response(tg_data, "media_download_completed", "buddy_id", usr_id_str,
				"to_peer_id", to_id_str, "media_id", media_id_str, "file_name", filename ? filename : "failed_to_load", "caption", caption ? caption : "");
}

void send_contact_updated_response(tg_engine_data_s *tg_data, int buddy_id, char* update_message)
{
	if (!update_message)
		return;
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	make_arg2_response(tg_data, "contact_updated", "buddy_id", usr_id_str, "update_message", update_message);
}

void send_buddy_status_updated_response(tg_engine_data_s *tg_data, int buddy_id)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	make_arg1_response(tg_data, "buddy_status_updated", "buddy_id", usr_id_str);
}

void send_buddy_status_notification_response(tg_engine_data_s *tg_data, int buddy_id, char* budy_name, int online)
{
	char usr_id_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	make_arg3_response(tg_data, "user_status_updated", "buddy_id", usr_id_str, "buddy_name", budy_name, "user_status", online ? "online" : "offline");
}

void send_buddy_type_notification_response(tg_engine_data_s *tg_data, int buddy_id, char* budy_name, int type_status)
{
	char usr_id_str[64];
	char type_status_str[64];
	snprintf(usr_id_str, sizeof(usr_id_str), "%d", buddy_id);
	snprintf(type_status_str, sizeof(type_status_str), "%d", type_status);
	make_arg3_response(tg_data, "type_status_updated", "buddy_id", usr_id_str, "buddy_name", budy_name, "type_status", type_status_str);
}

void send_response_for_logout(tg_engine_data_s *tg_data)
{
	make_base_response(tg_data, "logout_completed");
}

void send_server_restart_notification(tg_engine_data_s *tg_data)
{
	make_base_response(tg_data, "server_restart_notification");
}

void send_response_for_server_connection_status(tg_engine_data_s *tg_data, Eina_Bool connection_status)
{
	make_arg1_response(tg_data, "server_connection_status", "connection_status", connection_status ? "true" : "false");
}

void send_server_connection_failed_response(tg_engine_data_s *tg_data)
{
	make_base_response(tg_data, "server_connection_failed");
}

