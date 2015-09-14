/**
 * @file tg_db_wrapper.c
 * @date Jun 26, 2015
 * @author sandeep
 */

#include "tgl-layout.h"
#include "tg_common.h"
#include "tg_db_wrapper.h"

void create_data_base_tables()
{
	tg_db_create_table_user_info(USER_INFO_TABLE_NAME);
	tg_db_create_table_user_info(BUDDY_INFO_TABLE_NAME);
	tg_db_create_table_media_info(MEDIA_INFO_TABLE_NAME);
	tg_db_create_table_chat_info(CHAT_INFO_TABLE_NAME);
	tg_db_create_table_peer_info(PEER_INFO_TABLE_NAME);
}

void create_buddy_msg_table(const char* table_name)
{
	tg_db_create_table_message(table_name);
}

void insert_buddy_msg_to_db(struct tgl_message *M)
{
	// get user name using id from buddy_info_table
	int t = 0;
#if 0
	char* table_name = BUDDY_INFO_TABLE_NAME;

	int user_id = M->from_id.id;
	char usr_str[50];
	sprintf(usr_str,"%d",user_id);

	char* where_clause = (char*)malloc(strlen(BUDDY_INFO_TABLE_BUDDY_ID) + strlen(" = ") + strlen(usr_str));
	strcpy(where_clause, BUDDY_INFO_TABLE_BUDDY_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, usr_str);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHONE_NO);

	Eina_List* vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	close_database(db);

	char* phone_no = NULL;

	if(!vals) {
		//("DB error");
		return;
	} else {
		int row_count = eina_list_count(vals);

		for (int i = 0 ; i < row_count ; i++) {
			Eina_List* row_vals = eina_list_nth(vals, i);
			phone_no = (char*)eina_list_nth(row_vals, 0);
			if(!phone_no) {
				//("DB Error");
				return;
			} else {
				break;
			}
			eina_list_free(row_vals);
		}
		eina_list_free(vals);
	}

	if(phone_no) {
		char* tb_name = get_table_name_from_number(phone_no);
		insert_msg_into_db(M, tb_name, t);
		free(tb_name);
		free(phone_no);
	}
#else
	int user_id = 0;
	if (tgl_get_peer_type(M->to_id) == TGL_PEER_USER) {
		user_id = M->from_id.id;
	} else if (tgl_get_peer_type(M->to_id) == TGL_PEER_CHAT) {
		user_id = M->to_id.id;
	}
	char* tb_name = get_table_name_from_number(user_id);
	insert_msg_into_db(M, tb_name, t);
	free(tb_name);
#endif
}

void insert_peer_into_database(tgl_peer_t* UC, int last_msg_id, int unread_count)
{
	int ret;

	if (!UC) {
		return;
	}

	ret = tg_db_insert_peer_info(PEER_INFO_TABLE_NAME, UC, last_msg_id, unread_count);
	if (ret != 0) {
		ret = tg_db_update_peer_info(PEER_INFO_TABLE_NAME, UC, last_msg_id, unread_count);
	}

	return;
}

struct tgl_message* get_message_from_message_table(long long msg_id, char* table_name)
{
	struct tgl_message* message;
	message = tg_db_get_message(table_name, msg_id);
	return message;
}

void insert_msg_into_db(struct tgl_message *M, char* table_name, int unique_id)
{
	if(!M) {
		return;
	}

	tg_db_insert_message(table_name, M, (long long)unique_id);
}

void update_msg_into_db(struct tgl_message *M, char* table_name, int unique_id)
{
	if(!M) {
		return;
	}

	tg_db_update_message(table_name, M, unique_id);
}

Eina_Bool is_chat_id_already_exists(struct tgl_chat *chat_info)
{
	// get chat name chat id from chat_info_table

	int ret;
	ret = tg_db_count_chat_info(CHAT_INFO_TABLE_NAME, chat_info);
	return ret > 0 ? EINA_TRUE : EINA_FALSE;
}

void insert_buddy_into_db(char* table_name, struct tgl_user* U)
{
	int ret;

	if(!U) {
		return;
	}

	ret = tg_db_insert_user_info(table_name, U);
	if (ret != 0) {
		ret = tg_db_update_user_info(table_name, U);
		if (ret != 0) {

		}
	}
}

void insert_chat_info_to_db(struct tgl_chat *chat_info, char* photo_path)
{
	if (!chat_info) {
		return;
	}

	tg_db_insert_chat_info(CHAT_INFO_TABLE_NAME, chat_info, photo_path);
}

void update_chat_info_to_db(struct tgl_chat *chat_info, char *photo_path)
{
	if (!chat_info) {
		return;
	}

	tg_db_update_chat_info(CHAT_INFO_TABLE_NAME, chat_info, photo_path);
}

void update_buddy_pic_db(char* file_path, char* table_name, int id)
{
	if (!file_path || !table_name) {
		return;
	}

	tg_db_update_user_photo(table_name, id, file_path, -1);
}

/**
 * @note
 * This function is not used by tgl-service.
 * Do we have to keep this from here??
 */
struct tgl_user* get_buddy_info(int buddy_id)
{
	struct tgl_user *user_info;

	user_info = tg_db_get_user_info(BUDDY_INFO_TABLE_NAME, buddy_id);

	return user_info;
}

void update_receive_media_info_in_db(long long media_id, char* file_path)
{
	tg_db_update_media_info_filepath(MEDIA_INFO_TABLE_NAME, media_id, file_path);
}

void insert_media_info_to_db(struct tgl_message *M, char* file_path)
{
	if(!M) {
		return;
	}

	tg_db_insert_media_info(MEDIA_INFO_TABLE_NAME, M, file_path);
}

void update_sent_media_info_in_db(struct tgl_message *M, long long unique_val)
{
	long long id;
	if(!M) {
		return;
	}

	if (unique_val == 0) {
		switch (M->media.type) {
		case tgl_message_media_photo:
			id = M->media.photo.id;
			break;
		case tgl_message_media_document:
			id = M->media.document.id;
			break;
		default:
			/**
			 * @note
			 * To be handled.
			 */
			id = 0;
			break;
		}
	} else {
		id = unique_val;
	}

	tg_db_update_media_info_by_id(MEDIA_INFO_TABLE_NAME, M, id);
}
