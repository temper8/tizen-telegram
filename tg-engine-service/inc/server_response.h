/*
 * server_response.h
 *
 *  Created on: Jun 26, 2015
 *      Author: sandeep
 */

#ifndef SERVER_RESPONSE_H_
#define SERVER_RESPONSE_H_

#include "tg_engine.h"
#include <Elementary.h>
#include <efl_extension.h>

void process_registration_command(char* phone_no, Eina_Bool trough_sms);
void process_validation_command(char* code);
void process_send_message_command(int buddy_id, int msg_type, char* msg_data, int type_of_chat);
void process_send_media_command(int buddy_id, int msg_type, char* file_path);
void process_media_download_command(int buddy_id, long long media_id);
void process_add_contacts_command(int size, Eina_List* contact_list);
void process_new_group_create_command(Eina_List* buddy_ids, const char* group_name, const char* group_icon);

void send_add_contacts_request();
void send_registration_response(Eina_Bool is_success);
void send_name_registration_response();
void send_contacts_load_done_response(Eina_Bool is_success);
void send_contacts_and_chats_load_done_response(Eina_Bool is_success);
void send_buddy_profile_pic_updated_response(int buddy_id, char* file_path);
void send_message_received_response(int from_id, int to_id, long long message_id, int type_of_chat);
void send_message_sent_to_buddy_response(int buddy_id, int message_id, char* table_name, char* phone, int type_of_chat);
void send_message_read_by_buddy_response(int buddy_id, int message_id, char* table_name, char* phone, int type_of_chat);
void send_media_download_completed_response(int buddy_id, long long media_id, const char* filename);
void send_new_group_added_response(int chat_id);
void send_chat_profile_pic_updated_response(int chat_id, char* filename);
void send_contact_updated_response(int buddy_id, char* update_message);
void send_buddy_status_updated_response(int buddy_id);
void send_buddy_status_updated_response(int buddy_id);
void send_buddy_type_notification_response(int buddy_id, char* budy_name, int type_status);
#endif /* SERVER_RESPONSE_H_ */
