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

#ifndef SERVER_REQUESTS_H_
#define SERVER_REQUESTS_H_

#include "tg_common.h"

void send_request_for_restart_server(appdata_s *ad, service_client* service_client);
void send_request_for_logout(appdata_s *ad, service_client* service_client);
void send_request_for_registration(appdata_s *ad, service_client* service_client, const char* phone_number, Eina_Bool through_sms);
void send_request_for_profile_registration(appdata_s *ad, service_client* service_client, const char* first_name, const char* last_name);
void send_request_for_validation(appdata_s *ad, service_client* service_client, const char* sms_code);
// type_of_chat 0-buddy, 1-group_chat 2-encrpted_chat
void send_request_for_message_transport(appdata_s *ad, service_client* service_client, const int buddy_id, const int message_id, const int msg_type, const char* data, const int type_of_chat);
void send_request_for_marked_as_read(appdata_s *ad, service_client* service_client, const int buddy_id, const int type_of_chat);
void send_delete_all_messages_request(appdata_s *ad, service_client* service_client, const int buddy_id, const int type_of_chat);
void send_delete_selected_group_chats_request(appdata_s *ad, service_client* service_client, Eina_List *sel_grp_chats);
void send_delete_group_chat_request(appdata_s *ad, service_client* service_client, const int chat_id);
void send_add_buddy_request(appdata_s *ad, service_client* service_client, const int buddy_id, const char *first_name, const char *last_name, const char *phone_number);
void send_start_secret_chat_request(appdata_s *ad, service_client* service_client, const int buddy_id);
void send_delete_buddy_request(appdata_s *ad, service_client* service_client, const int buddy_id);
void send_block_buddy_request(appdata_s *ad, service_client* service_client, const int buddy_id);
void send_unblock_buddy_request(appdata_s *ad, service_client* service_client, const int buddy_id);
Eina_Bool send_request_for_media_downloading(appdata_s *ad, service_client* service_client, const int buddy_id, const long long media_id);
void send_request_for_media_transport(appdata_s *ad, service_client* service_client, const int buddy_id, const int message_id, const int media_id,  const int msg_type, const char* file_path, const int type_of_chat);
void send_group_creation_request_to_server(appdata_s *ad, service_client* service_client, Eina_List *buddy_list, const char* group_name, const char* group_image);

void send_add_buddy_to_group_chat_request(appdata_s *ad, service_client* service_client, int user_id, int chat_id);
void send_set_group_chat_new_title_request(appdata_s *ad, service_client* service_client, int user_id, const char* new_title);
void send_set_group_chat_profile_pic_request(appdata_s *ad, service_client* service_client, int user_id, const char* file_path);
void send_set_profile_pic_request(appdata_s *ad, service_client* service_client, int user_id, const char* file_path);
void send_set_username_request(appdata_s *ad, service_client* service_client, int user_id, const char* username);
void send_remove_buddy_from_group_chat_request(appdata_s *ad, service_client* service_client, int user_id, int chat_id);
void send_request_for_delete_notifications(appdata_s *ad, service_client* service_client);
void send_request_for_server_connection_status(appdata_s *ad, service_client* service_client);
void send_update_chat_request(appdata_s *ad, service_client* service_client, const int chat_id);
void send_update_display_name_request(appdata_s *ad, service_client* service_client, int user_id, const char* first_name, const char* last_name);

#endif /* SERVER_REQUESTS_H_ */
