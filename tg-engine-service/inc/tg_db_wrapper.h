/*
 * tg_db_wrapper.h
 *
 *  Created on: Jun 26, 2015
 *      Author: sandeep
 */

#ifndef TG_DB_WRAPPER_H_
#define TG_DB_WRAPPER_H_
#include "tg_db_manager.h"
#include "tg_engine.h"

#define USER_INFO_TABLE_NAME "user_info_table"
#define BUDDY_INFO_TABLE_NAME "buddy_info_table"
#define MEDIA_INFO_TABLE_NAME "media_info_table"

#define MESSAGE_INFO_TABLE_MESSAGE_ID "msg_id"
#define MESSAGE_INFO_TABLE_FLAGS "flags"
#define MESSAGE_INFO_TABLE_FWD_FROM_ID "fwd_from_id"
#define MESSAGE_INFO_TABLE_FWD_DATE "fwd_date"
#define MESSAGE_INFO_TABLE_FROM_ID "from_id"
#define MESSAGE_INFO_TABLE_TO_ID "to_id"
#define MESSAGE_INFO_TABLE_OUT_MSG "out"
#define MESSAGE_INFO_TABLE_UNREAD "unread"
#define MESSAGE_INFO_TABLE_DATE "date"
#define MESSAGE_INFO_TABLE_SERVICE "service"
#define MESSAGE_INFO_TABLE_MESSAGE "message"
#define MESSAGE_INFO_TABLE_MESSAGE_STATE "message_state"
#define MESSAGE_INFO_TABLE_MESSAGE_LENGTH "message_len"
#define MESSAGE_INFO_TABLE_MEDIA_TYPE "media_type"
#define MESSAGE_INFO_TABLE_MEDIA_ID "media_id"
#define MESSAGE_INFO_TABLE_UNIQUE_ID "unique_id"


#define CHAT_INFO_TABLE_NAME "chat_info_table"

#define CHAT_INFO_TABLE_CHAT_ID "chat_id"
#define CHAT_INFO_TABLE_FLAGS "flags"
#define CHAT_INFO_TABLE_PRINT_TITLE "print_title"
#define CHAT_INFO_TABLE_STRUCT_VERSION "struct_version"
#define CHAT_INFO_TABLE_PHOTO_ID "photo_id"
#define CHAT_INFO_TABLE_PHOTO_PATH "photo_path"
#define CHAT_INFO_TABLE_TITLE "title"
#define CHAT_INFO_TABLE_NO_OF_USERS "users_num"
#define CHAT_INFO_TABLE_USER_LIST_SIZE "user_list_size"
#define CHAT_INFO_TABLE_USER_LIST_VERSION "user_list_version"
#define CHAT_INFO_TABLE_INVITER_ID "inviter_id"
#define CHAT_INFO_TABLE_CHAT_USERS "chat_users"
#define CHAT_INFO_TABLE_DATE "date"
#define CHAT_INFO_TABLE_VERSION "version"
#define CHAT_INFO_TABLE_ADMIN_ID "admin_id"


#define PEER_INFO_TABLE_NAME "peer_info_table" //user or group chat or encrypted chat

#define PEER_INFO_TABLE_CHAT_ID "user_id"
#define PEER_INFO_TABLE_PEER_TYPE "peer_type"
#define PEER_INFO_TABLE_FLAGS "flags"
#define PEER_INFO_TABLE_LAST_MESSAGE_ID "message_id"
#define PEER_INFO_TABLE_LAST_MESSAGE_DATE "message_date"
#define PEER_INFO_TABLE_PRINT_NAME "print_name"
#define PEER_INFO_TABLE_STRUCT_VERSION "struct_version"
#define PEER_INFO_TABLE_NO_OF_UNREAD_MESSAGES "unread_message_count"
#define PEER_INFO_TABLE_LAST_SEEN_TIME "last_seen"


#define TG_DB_COLUMN_INTEGER "INTEGER"
#define TG_DB_COLUMN_INTEGER_PRIMARY_KEY "INTEGER PRIMARY KEY NOT NULL"
#define TG_DB_COLUMN_TEXT "TEXT"


void create_data_base_tables();

Eina_List* get_registered_user_info();

void insert_buddy_into_db(char* table_name, struct tgl_user* U);

void insert_peer_into_database(tgl_peer_t* UC, int last_msg_id, int unread_count);

void update_buddy_pic_db(char* file_path, char* table_name, int id);

void create_buddy_msg_table(const char* table_name);

void insert_buddy_msg_to_db(struct tgl_message *M);

struct tgl_message* get_message_from_message_table(long long msg_id, char* table_name);

void insert_msg_into_db(struct tgl_message *M, char* table_name, int unique_id);

void update_msg_into_db(struct tgl_message *M, char* table_name, int unique_id);

void insert_chat_info_to_db(struct tgl_chat *C, char* photo_path);

void update_chat_info_to_db(struct tgl_chat *chat_info, char* photo_path);

extern struct tgl_user* get_buddy_info(int buddy_id);

void insert_media_info_to_db(struct tgl_message *M, char* file_path);
void update_sent_media_info_in_db(struct tgl_message *M, long long unique_val);
void update_receive_media_info_in_db(long long media_id, char* file_path);

Eina_Bool is_chat_id_already_exists(struct tgl_chat *C);

#endif /* TG_DB_WRAPPER_H_ */
