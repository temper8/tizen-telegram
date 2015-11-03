/*
 * server_response.h
 *
 *  Created on: Jun 26, 2015
 *      Author: sandeep
 */

#ifndef SERVER_RESPONSE_H_
#define SERVER_RESPONSE_H_



extern void process_registration_command(tg_engine_data_s *tg_data, char *phone_no, Eina_Bool trough_sms);
extern void process_validation_command(tg_engine_data_s *tg_data, char *code);
extern void process_logout_command(tg_engine_data_s *tg_data);
extern void process_send_message_command(int buddy_id, int message_id, int msg_type, char* msg_data, int type_of_chat);
extern void process_marked_as_read_command(int buddy_id, int type_of_chat);
extern void process_delete_group_chat_request(tg_engine_data_s* tg_data, int chat_id);
extern void process_delete_selected_group_chats_request(tg_engine_data_s* tg_data, Eina_List *sel_grp_chats);
extern void process_add_user_request(tg_engine_data_s* tg_data, int buddy_id, char *first_name, char *last_name, char *phone_num);
extern void process_update_chat_request(tg_engine_data_s* tg_data, int chat_id);
extern void process_delete_user_request(tg_engine_data_s* tg_data, int buddy_id);
extern void process_send_secret_chat_request(tg_engine_data_s* tg_data, int buddy_id);
extern void process_block_user_request(tg_engine_data_s* tg_data, int buddy_id);
extern void process_unblock_user_request(tg_engine_data_s* tg_data, int buddy_id);
extern void process_send_media_command(int buddy_id, int message_id, int media_id, int msg_type, char* file_path, int type_of_chat);
extern void process_media_download_command(tg_engine_data_s *tg_data, int buddy_id, long long media_id);
extern void process_add_contacts_command(tg_engine_data_s *tg_data, int size, Eina_List* contact_list);
extern void process_new_group_create_command(tg_engine_data_s *tg_data, Eina_List* buddy_ids, const char* group_name, const char* group_icon);
extern void process_set_profile_pic_command(tg_engine_data_s *tg_data, int buddy_id, const char *file_path);
extern void process_set_group_chat_new_title_command(tg_engine_data_s *tg_data, int buddy_id, const char *new_title);
extern void process_add_new_buddy_to_chat_command(tg_engine_data_s *tg_data, int s_buddy_id, int s_chat_id);
extern void process_remove_buddy_from_chat_command(tg_engine_data_s *tg_data, int s_buddy_id, int s_chat_id);
extern void process_set_group_chat_profile_pic_command(tg_engine_data_s *tg_data, int buddy_id, const char *file_path);
extern void process_set_username_command(tg_engine_data_s *tg_data, int buddy_id, const char *username);
extern void process_update_display_name_command(tg_engine_data_s *tg_data, int buddy_id, const char *first_name, const char *last_name);

extern void send_add_contacts_request(tg_engine_data_s *tg_data);
extern void send_server_not_initialized_response(tg_engine_data_s *tg_data);
extern void send_registration_response(tg_engine_data_s *tg_data, Eina_Bool is_success);
extern void send_request_code_again(tg_engine_data_s *tg_data);
extern void send_request_phone_num_again(tg_engine_data_s *tg_data);
extern void send_name_registration_response(tg_engine_data_s *tg_data);
extern void send_contacts_load_done_response(tg_engine_data_s *tg_data, Eina_Bool is_success);
extern void send_self_profile_picture_updated_response(tg_engine_data_s *tg_data, char *file_path, Eina_Bool is_success);
extern void send_self_user_name_updated_response(tg_engine_data_s *tg_data, char *username, Eina_Bool is_success);
extern void send_contacts_and_chats_load_done_response(tg_engine_data_s *tg_data, Eina_Bool is_success);
extern void send_buddy_profile_pic_updated_response(tg_engine_data_s *tg_data, int buddy_id, char* file_path);
extern void send_message_received_response(tg_engine_data_s *tg_data, int from_id, int to_id, long long message_id, int type_of_chat);
extern void send_message_sent_to_buddy_response(tg_engine_data_s *tg_data, int buddy_id, int message_id, char* table_name, Eina_Bool is_success, int type_of_chat);
extern void send_group_chat_deleted_response(tg_engine_data_s *tg_data, int chat_id, Eina_Bool is_success);
extern void send_selected_group_chats_deleted_response(tg_engine_data_s *tg_data);
extern void send_message_read_by_buddy_response(tg_engine_data_s *tg_data, int buddy_id, int message_id, char* table_name, char* phone, int type_of_chat);
extern void send_media_download_completed_response(tg_engine_data_s *tg_data, int buddy_id, int to_id, long long media_id, const char* filename);
extern void send_video_thumb_download_completed_response(tg_engine_data_s *tg_data, int buddy_id, int to_id, long long media_id, const char* filename);
extern void send_new_group_added_response(tg_engine_data_s *tg_data, int chat_id);
extern void send_new_buddy_added_response(tg_engine_data_s *tg_data, int buddy_id);
extern void send_group_chat_updated_response(tg_engine_data_s *tg_data, int chat_id, const char *type_of_change);
extern void send_chat_profile_pic_updated_response(tg_engine_data_s *tg_data, int chat_id, char* filename);
extern void send_contact_updated_response(tg_engine_data_s *tg_data, int buddy_id, char* update_message);
extern void send_buddy_status_updated_response(tg_engine_data_s *tg_data, int buddy_id);
extern void send_buddy_status_updated_response(tg_engine_data_s *tg_data, int buddy_id);
extern void send_buddy_type_notification_response(tg_engine_data_s *tg_data, int buddy_id, char* budy_name, int type_status);
extern void send_buddy_status_notification_response(tg_engine_data_s *tg_data, int buddy_id, char* budy_name, int online);

extern void send_group_chat_rename_response(tg_engine_data_s *tg_data, int peer_id, Eina_Bool is_success);
extern void send_buddy_readded_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success);
extern void send_buddy_deleted_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success);
extern void send_buddy_blocked_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success);
extern void send_buddy_unblocked_response(tg_engine_data_s *tg_data, int buddy_id, Eina_Bool is_success);
extern void send_group_chat_new_buddy_response(tg_engine_data_s *tg_data, int peer_id, Eina_Bool is_success);
extern void send_group_chat_delete_buddy_response(tg_engine_data_s *tg_data, int peer_id, Eina_Bool is_success);
extern void send_response_for_server_connection_status(tg_engine_data_s *tg_data, Eina_Bool connection_status);
extern void send_response_for_logout(tg_engine_data_s *tg_data);

extern void send_self_profile_name_updated_response(tg_engine_data_s *tg_data, char *first_name, char *last_name, Eina_Bool is_success);
extern void send_response_to_group_chat_updated_response(tg_engine_data_s *tg_data, int chat_id);
extern void send_server_connection_failed_response(tg_engine_data_s *tg_data);
#endif /* SERVER_RESPONSE_H_ */
