/*
 * tg_db_wrapper.c
 *
 *  Created on: Jun 26, 2015
 *      Author: sandeep
 */

#include "tg_db_wrapper.h"
#include "tg_common.h"
#include "tgl-layout.h"

void create_data_base_tables()
{
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		char* table_name = USER_INFO_TABLE_NAME;
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, USER_INFO_TABLE_USER_ID);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PRINT_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_STRUCTURE_VERSION);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_ID);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_FIRST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_LAST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PHONE_NO);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_ACCESS_HASH);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_REAL_FIRST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_REAL_LAST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_USER_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_ONLINE_STATUS);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_LAST_SEEN_TIME);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		Eina_Bool ret = create_table(db, table_name, col_names, col_types);
		if(!ret) {
			// error occured
		}
		eina_list_free(col_names);
		eina_list_free(col_types);

		table_name = BUDDY_INFO_TABLE_NAME;
		col_names = NULL;
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_BUDDY_ID);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PRINT_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_STRUCTURE_VERSION);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHOTO_PATH);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHOTO_ID);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_FIRST_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_LAST_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHONE_NO);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_ACCESS_HASH);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_REAL_FIRST_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_REAL_LAST_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_BUDDY_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_ONLINE_STATUS);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_LAST_SEEN_TIME);

		col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		ret = create_table(db, table_name, col_names, col_types);
		if(!ret) {
			// error occured
		}

		eina_list_free(col_names);
		eina_list_free(col_types);

		table_name = MEDIA_INFO_TABLE_NAME;
		col_names = NULL;
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MEDIA_ID);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MEDIA_TYPE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_ACCESS_HASH);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_USER_ID);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DATE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_CAPTION);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LONGITUDE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LATITUDE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_SIZES_NUM);


		/********************************************************************/

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA1);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA2);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA3);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA4);


		/********************************************************************/

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHONE_NO);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FIRST_NAME);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LAST_NAME);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FILE_PATH);

		col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);


		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		ret = create_table(db, table_name, col_names, col_types);
		if(!ret) {
			// error occured
		}

		eina_list_free(col_names);
		eina_list_free(col_types);

		table_name = CHAT_INFO_TABLE_NAME;
		col_names = NULL;
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_CHAT_ID);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_FLAGS);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PRINT_TITLE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_STRUCT_VERSION);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PHOTO_ID);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PHOTO_PATH);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_TITLE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_NO_OF_USERS);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_USER_LIST_SIZE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_USER_LIST_VERSION);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_INVITER_ID);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_CHAT_USERS);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_DATE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_VERSION);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_ADMIN_ID);

		col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		ret = create_table(db, table_name, col_names, col_types);
		if(!ret) {
			// error occured
		}

		eina_list_free(col_names);
		eina_list_free(col_types);

		table_name = PEER_INFO_TABLE_NAME;
		col_names = NULL;
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_CHAT_ID);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_PEER_TYPE);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_FLAGS);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_LAST_MESSAGE_ID);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_LAST_MESSAGE_DATE);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_PRINT_NAME);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_STRUCT_VERSION);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_NO_OF_UNREAD_MESSAGES);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_LAST_SEEN_TIME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHOTO_PATH);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHOTO_ID);

		col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		ret = create_table(db, table_name, col_names, col_types);
		if(!ret) {
			// error occured
		}

		eina_list_free(col_names);
		eina_list_free(col_types);

		close_database(db);
	}
}

void create_buddy_msg_table(const char* table_name)
{
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db && table_name) {
		// create user info table
		Eina_List* col_names = NULL;

		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FLAGS);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FWD_FROM_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FWD_DATE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FROM_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_TO_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_OUT_MSG);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNREAD);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_DATE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_SERVICE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_LENGTH);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_TYPE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNIQUE_ID);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		Eina_Bool ret = create_table(db, table_name, col_names, col_types);
		if(!ret) {
			//("error: database creation failed");
		}
		eina_list_free(col_names);
		eina_list_free(col_types);
		close_database(db);
	}
}

void insert_buddy_msg_to_db(struct tgl_message *M)
{
	// get user name using id from buddy_info_table
	int t = 0;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
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

		Eina_List* vals = get_values_from_table_sync(db, table_name, col_names, col_types, where_clause);
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
}

void insert_peer_into_database(tgl_peer_t* UC, int last_msg_id, int unread_count)
{
	if (!UC) {
		return;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if (db) {
		char* table_name = PEER_INFO_TABLE_NAME;
		Eina_List* col_names = NULL;
		col_names = NULL;
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_CHAT_ID);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_PEER_TYPE);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_FLAGS);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_LAST_MESSAGE_ID);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_LAST_MESSAGE_DATE);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_PRINT_NAME);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_STRUCT_VERSION);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_NO_OF_UNREAD_MESSAGES);
		col_names = eina_list_append(col_names, PEER_INFO_TABLE_LAST_SEEN_TIME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHOTO_PATH);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHOTO_ID);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);


		Eina_List* col_values = NULL;
		col_values = eina_list_append(col_values, &(UC->id.id));
		col_values = eina_list_append(col_values, &(UC->id.type));
		col_values = eina_list_append(col_values, &(UC->flags));
		char last_msg_id_str[50];
		sprintf(last_msg_id_str, "%d", last_msg_id);
		col_values = eina_list_append(col_values, last_msg_id_str);

		// last message date
		if (UC->last) {
			col_values = eina_list_append(col_values, &(UC->last->date));
		} else {
			int last_msg_date = 0;
			col_values = eina_list_append(col_values, &(last_msg_date));
		}

		if (UC->print_name) {
			col_values = eina_list_append(col_values, UC->print_name);
		} else {
			col_values = eina_list_append(col_values, "");
		}

		col_values = eina_list_append(col_values, &(UC->structure_version));

		col_values = eina_list_append(col_values, &(unread_count));

		if (UC->id.type == TGL_PEER_USER ) {
			col_values = eina_list_append(col_values, &(UC->user.status.when));
		} else if (UC->id.type == TGL_PEER_CHAT ) {
			col_values = eina_list_append(col_values, &(UC->chat.date));
		} else {
			int last_seen = 0;
			col_values = eina_list_append(col_values, &(last_seen));
		}

		col_values = eina_list_append(col_values, "");



		struct tgl_photo* photo = &(UC->photo);
		int photo_id = -1;
		if (photo) {
			photo_id = photo->id;
		}
		col_values = eina_list_append(col_values, &(photo_id));

		Eina_Bool ret = insert_table(db, table_name, col_names, col_types,col_values);
		if(!ret) {
			//("error: database creation failed");
		} else {

		}
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
		close_database(db);
	}
}

void insert_msg_into_db(struct tgl_message *M, char* table_name, int unique_id)
{
	if(!M) {
		return;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FLAGS);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FWD_FROM_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FWD_DATE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FROM_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_TO_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_OUT_MSG);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNREAD);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_DATE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_SERVICE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_LENGTH);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_TYPE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNIQUE_ID);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		Eina_List* col_values = NULL;
		col_values = eina_list_append(col_values, &(M->id));
		col_values = eina_list_append(col_values, &(M->flags));
		col_values = eina_list_append(col_values, &(M->fwd_from_id.id));
		col_values = eina_list_append(col_values, &(M->fwd_date));
		col_values = eina_list_append(col_values, &(M->from_id.id));
		col_values = eina_list_append(col_values, &(M->to_id.id));
		col_values = eina_list_append(col_values, &(M->out));
		col_values = eina_list_append(col_values, &(M->unread));
		col_values = eina_list_append(col_values, &(M->date));
		col_values = eina_list_append(col_values, &(M->service));

		if(M->message)
			col_values = eina_list_append(col_values, M->message);
		else
			col_values = eina_list_append(col_values, " ");

		col_values = eina_list_append(col_values, &(M->message_len));
		col_values = eina_list_append(col_values, &(M->media.type));

		char* dummy_val = "";
		if(M->media.type == tgl_message_media_none) {
			col_values = eina_list_append(col_values, (dummy_val));
		} else if(M->media.type == tgl_message_media_photo) {

			char* temp_media_id[50];
			sprintf(temp_media_id, "%lld", M->media.photo.id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_document) {

			char* temp_media_id[50];
			sprintf(temp_media_id, "%lld", M->media.document.dc_id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_geo) {
			col_values = eina_list_append(col_values, (dummy_val));
		} else if(M->media.type == tgl_message_media_contact) {

			char* temp_media_id[50];
			sprintf(temp_media_id, "%lld",M->media.user_id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_unsupported) {
			col_values = eina_list_append(col_values, (dummy_val));
		} else if(M->media.type == tgl_message_media_photo_encr) {

			char* temp_media_id[50];
			sprintf(temp_media_id, "%lld",M->media.encr_photo.id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_document_encr) {

			char* temp_media_id[50];
			sprintf(temp_media_id, "%lld",M->media.document.id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else  {
			col_values = eina_list_append(col_values, (dummy_val));
		}

		col_values = eina_list_append(col_values, &unique_id);

		Eina_Bool ret = insert_table(db, table_name, col_names, col_types,col_values);
		if(!ret) {
			//("error: database creation failed");
		} else {

		}
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
		close_database(db);
	}
}


void update_msg_into_db(struct tgl_message *M, char* table_name, int unique_id)
{
	if(!M) {
		return;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FLAGS);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FWD_FROM_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FWD_DATE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FROM_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_TO_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_OUT_MSG);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNREAD);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_DATE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_SERVICE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_LENGTH);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_TYPE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_ID);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNIQUE_ID);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		Eina_List* col_values = NULL;
		col_values = eina_list_append(col_values, &(M->id));
		col_values = eina_list_append(col_values, &(M->flags));
		col_values = eina_list_append(col_values, &(M->fwd_from_id.id));
		col_values = eina_list_append(col_values, &(M->fwd_date));
		col_values = eina_list_append(col_values, &(M->from_id.id));
		col_values = eina_list_append(col_values, &(M->to_id.id));
		col_values = eina_list_append(col_values, &(M->out));
		col_values = eina_list_append(col_values, &(M->unread));
		col_values = eina_list_append(col_values, &(M->date));
		col_values = eina_list_append(col_values, &(M->service));

		if(M->message)
			col_values = eina_list_append(col_values, M->message);
		else
			col_values = eina_list_append(col_values, " ");

		col_values = eina_list_append(col_values, &(M->message_len));
		col_values = eina_list_append(col_values, &(M->media.type));

		char* dummy_val = "";
		if(M->media.type == tgl_message_media_none) {
			col_values = eina_list_append(col_values, (dummy_val));
		} else if(M->media.type == tgl_message_media_photo) {

			char* temp_media_id[50];
			sprintf(temp_media_id, "%lld", M->media.photo.id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_document) {

			char* temp_media_id[50];
			sprintf(temp_media_id, "%lld", M->media.document.dc_id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_geo) {
			col_values = eina_list_append(col_values, (dummy_val));
		} else if(M->media.type == tgl_message_media_contact) {

			char* temp_media_id[50];
			sprintf(temp_media_id, "%lld",M->media.user_id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_unsupported) {
			col_values = eina_list_append(col_values, (dummy_val));
		} else if(M->media.type == tgl_message_media_photo_encr) {

			char* temp_media_id[50];
			sprintf(temp_media_id, "%lld",M->media.encr_photo.id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_document_encr) {

			char* temp_media_id[50];
			sprintf(temp_media_id, "%lld",M->media.document.id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else  {
			col_values = eina_list_append(col_values, (dummy_val));
		}

		int u_id = 0;
		col_values = eina_list_append(col_values, &u_id);


		char* where_clause = NULL;

		if (unique_id > 0) {

			char usr_str[50];
			sprintf(usr_str,"%d",unique_id);
			where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_UNIQUE_ID) + strlen(" = ") + strlen(usr_str) + 1);
			strcpy(where_clause, MESSAGE_INFO_TABLE_UNIQUE_ID);
			strcat(where_clause, " = ");
			strcat(where_clause, usr_str);

		} else {

			char usr_str[50];
			sprintf(usr_str,"%d",M->id);
			where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_MESSAGE_ID) + strlen(" = ") + strlen(usr_str) + 1);
			strcpy(where_clause, MESSAGE_INFO_TABLE_MESSAGE_ID);
			strcat(where_clause, " = ");
			strcat(where_clause, usr_str);

		}

		Eina_Bool ret = update_table(db, table_name, col_names, col_types, col_values, where_clause);

		if(!ret) {
			//("error: database creation failed");
		} else {

		}
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
		close_database(db);
	}
}


Eina_List* get_registered_user_info()
{
	Eina_List* user_details = NULL;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		char* table_name = USER_INFO_TABLE_NAME;
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, USER_INFO_TABLE_USER_ID);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PRINT_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_STRUCTURE_VERSION);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_ID);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_FIRST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_LAST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PHONE_NO);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_ACCESS_HASH);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_REAL_FIRST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_REAL_LAST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_USER_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_ONLINE_STATUS);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_LAST_SEEN_TIME);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		user_details = get_values_from_table_sync(db, table_name, col_names, col_types, NULL);

		eina_list_free(col_names);
		eina_list_free(col_types);
	}
	return user_details;
}

Eina_Bool is_chat_id_already_exists(struct tgl_chat *chat_info)
{
	// get chat name chat id from chat_info_table
	int t = 0;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		char* table_name = CHAT_INFO_TABLE_NAME;

		int chat_id = chat_info->id.id;
		char chat_str[50];
		sprintf(chat_str,"%d",chat_id);

		char* where_clause = (char*)malloc(strlen(CHAT_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(chat_str));
		strcpy(where_clause, CHAT_INFO_TABLE_CHAT_ID);
		strcat(where_clause, " = ");
		strcat(where_clause, chat_str);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_TITLE);

		Eina_List* vals = get_values_from_table_sync(db, table_name, col_names, col_types, where_clause);
		close_database(db);

		char* chat_name = NULL;

		if(!vals) {
			//("DB error");
			return EINA_FALSE;
		} else {
			int row_count = eina_list_count(vals);

			for (int i = 0 ; i < row_count ; i++) {
				Eina_List* row_vals = eina_list_nth(vals, i);
				chat_name = (char*)eina_list_nth(row_vals, 0);
				if(!chat_name) {
					//("DB Error");
					return EINA_FALSE;
				} else {
					break;
				}
				eina_list_free(row_vals);
			}
			eina_list_free(vals);
		}

		if(chat_name) {
			free(chat_name);
			return EINA_TRUE;
		}
	}
	return EINA_FALSE;
}

void insert_buddy_into_db(char* table_name, struct tgl_user* U)
{
	if(!U) {
		return;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, USER_INFO_TABLE_USER_ID);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PRINT_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_STRUCTURE_VERSION);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_ID);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_FIRST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_LAST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PHONE_NO);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_ACCESS_HASH);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_REAL_FIRST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_REAL_LAST_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_USER_NAME);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_ONLINE_STATUS);
		col_names = eina_list_append(col_names, USER_INFO_TABLE_LAST_SEEN_TIME);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		Eina_List* col_values = NULL;
		col_values = eina_list_append(col_values, &(U->id.id));
		if(U->print_name)
			col_values = eina_list_append(col_values, U->print_name);
		else
			col_values = eina_list_append(col_values, "");

		col_values = eina_list_append(col_values, &(U->structure_version));
		col_values = eina_list_append(col_values, "");
		col_values = eina_list_append(col_values, &(U->photo_id));

		if(U->first_name)
			col_values = eina_list_append(col_values, U->first_name);
		else
			col_values = eina_list_append(col_values, "");
		if(U->last_name)
			col_values = eina_list_append(col_values, U->last_name);
		else
			col_values = eina_list_append(col_values, "");

		if(U->phone)
			col_values = eina_list_append(col_values, U->phone);
		else
			col_values = eina_list_append(col_values, "");

		col_values = eina_list_append(col_values, &(U->access_hash));

		if(U->real_first_name)
			col_values = eina_list_append(col_values, U->real_first_name);
		else
			col_values = eina_list_append(col_values, "");

		if(U->real_last_name)
			col_values = eina_list_append(col_values, U->real_last_name);
		else
			col_values = eina_list_append(col_values, "");

		if(U->username)
			col_values = eina_list_append(col_values, U->username);
		else
			col_values = eina_list_append(col_values, "");

		col_values = eina_list_append(col_values, &(U->status.online));
		col_values = eina_list_append(col_values, &(U->status.when));

		Eina_Bool ret = insert_table(db, table_name, col_names, col_types,col_values);
		if(!ret) {
			// already exist. So update the table
			char* where_clause = NULL;
			char user_id_str[50];
			sprintf(user_id_str,"%d",U->id.id);
			where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(user_id_str) + 1);
			strcpy(where_clause, USER_INFO_TABLE_USER_ID);
			strcat(where_clause, " = ");
			strcat(where_clause, user_id_str);
			ret = update_table(db, table_name, col_names, col_types, col_values, where_clause);
		} else {
			// successfully inserted.
		}
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
		close_database(db);
	}
}

void insert_chat_info_to_db(struct tgl_chat *chat_info, char* photo_path)
{
	if (!chat_info) {
		return;
	}
	char* table_name = CHAT_INFO_TABLE_NAME;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_CHAT_ID);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_FLAGS);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PRINT_TITLE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_STRUCT_VERSION);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PHOTO_ID);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PHOTO_PATH);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_TITLE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_NO_OF_USERS);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_USER_LIST_SIZE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_USER_LIST_VERSION);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_INVITER_ID);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_CHAT_USERS);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_DATE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_VERSION);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_ADMIN_ID);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		Eina_List* col_values = NULL;
		col_values = eina_list_append(col_values, &(chat_info->id.id));
		col_values = eina_list_append(col_values, &(chat_info->flags));

		if(chat_info->print_title)
			col_values = eina_list_append(col_values, chat_info->print_title);
		else
			col_values = eina_list_append(col_values, "");

		col_values = eina_list_append(col_values, &(chat_info->structure_version));

		long long photo_id = chat_info->photo.id;

		char photo_id_str[50];
		sprintf(photo_id_str, "%lld", photo_id);
		col_values = eina_list_append(col_values, photo_id_str);

		if (photo_path) {
			col_values = eina_list_append(col_values, photo_path);
		} else {
			col_values = eina_list_append(col_values, " ");
		}

		if(chat_info->title)
			col_values = eina_list_append(col_values, chat_info->title);
		else
			col_values = eina_list_append(col_values, "");

		col_values = eina_list_append(col_values, &(chat_info->users_num));
		col_values = eina_list_append(col_values, &(chat_info->user_list_size));
		col_values = eina_list_append(col_values, &(chat_info->user_list_version));

		int inventor_id = 0;
		if (chat_info->user_list) {
			inventor_id = chat_info->user_list[0].inviter_id;
		}

		col_values = eina_list_append(col_values, &(inventor_id));

		/****** add chat users list ********/
		char* full_ids = NULL;
		if (chat_info->user_list) {
			char* chat_user_ids[chat_info->user_list_size];
			int total_len = 0;
			for (int i = 0; i < chat_info->user_list_size; i++) {
				char temp_user_id[15];
				int temp_id = chat_info->user_list[i].user_id;
				sprintf(temp_user_id,"%d",temp_id);
				chat_user_ids[i] = (char*)malloc(strlen(temp_user_id) + 1);
				strcpy(chat_user_ids[i], temp_user_id);
				total_len = total_len + strlen(temp_user_id);
				total_len = total_len + 1; // delimitor
			}

			full_ids = (char*)malloc(total_len);
			for (int i = 0; i < chat_info->user_list_size; i++) {
				if (i == 0) {
					strcpy(full_ids, chat_user_ids[i]);
				} else {
					strcat(full_ids, chat_user_ids[i]);
				}
				if (i < chat_info->user_list_size - 1) {
					strcat(full_ids, ",");
				}
				free(chat_user_ids[i]);
			}
		} else {
			full_ids = (char*)malloc(2);
			strcpy(full_ids, " ");
		}

		col_values = eina_list_append(col_values, full_ids);
		/****** add chat users list ********/

		col_values = eina_list_append(col_values, &(chat_info->date));
		col_values = eina_list_append(col_values, &(chat_info->version));
		col_values = eina_list_append(col_values, &(chat_info->admin_id));

		Eina_Bool ret = insert_table(db, table_name, col_names, col_types,col_values);
		if(!ret) {
			// already exist. So update the table
			char* where_clause = NULL;
			char chat_id_str[50];
			sprintf(chat_id_str,"%d", chat_info->id.id);
			where_clause = (char*)malloc(strlen(CHAT_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(chat_id_str) + 1);
			strcpy(where_clause, CHAT_INFO_TABLE_CHAT_ID);
			strcat(where_clause, " = ");
			strcat(where_clause, chat_id_str);
			ret = update_table(db, table_name, col_names, col_types, col_values, where_clause);
		} else {

		}
		free(full_ids);
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
		close_database(db);
	}
}

void update_chat_info_to_db(struct tgl_chat *chat_info, char* photo_path)
{
	if (!chat_info) {
		return;
	}
	char* table_name = CHAT_INFO_TABLE_NAME;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_CHAT_ID);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_FLAGS);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PRINT_TITLE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_STRUCT_VERSION);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PHOTO_ID);
		if (photo_path) {
			col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PHOTO_PATH);
		}
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_TITLE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_NO_OF_USERS);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_USER_LIST_SIZE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_USER_LIST_VERSION);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_INVITER_ID);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_CHAT_USERS);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_DATE);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_VERSION);
		col_names = eina_list_append(col_names, CHAT_INFO_TABLE_ADMIN_ID);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		if (photo_path) {
			col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		}
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		Eina_List* col_values = NULL;
		col_values = eina_list_append(col_values, &(chat_info->id.id));
		col_values = eina_list_append(col_values, &(chat_info->flags));

		if(chat_info->print_title)
			col_values = eina_list_append(col_values, chat_info->print_title);
		else
			col_values = eina_list_append(col_values, "");

		col_values = eina_list_append(col_values, &(chat_info->structure_version));

		long long photo_id = chat_info->photo.id;

		char photo_id_str[50];
		sprintf(photo_id_str, "%lld", photo_id);
		col_values = eina_list_append(col_values, photo_id_str);

		if (photo_path) {
			col_values = eina_list_append(col_values, photo_path);
		}

		if(chat_info->title)
			col_values = eina_list_append(col_values, chat_info->title);
		else
			col_values = eina_list_append(col_values, "");

		col_values = eina_list_append(col_values, &(chat_info->users_num));
		col_values = eina_list_append(col_values, &(chat_info->user_list_size));
		col_values = eina_list_append(col_values, &(chat_info->user_list_version));

		int inventor_id = 0;
		if (chat_info->user_list) {
			inventor_id = chat_info->user_list[0].inviter_id;
		}

		col_values = eina_list_append(col_values, &(inventor_id));

		/****** add chat users list ********/
		char* full_ids = NULL;
		if (chat_info->user_list) {
			char* chat_user_ids[chat_info->user_list_size];
			int total_len = 0;
			for (int i = 0; i < chat_info->user_list_size; i++) {
				char temp_user_id[15];
				int temp_id = chat_info->user_list[i].user_id;
				sprintf(temp_user_id,"%d",temp_id);
				chat_user_ids[i] = (char*)malloc(strlen(temp_user_id) + 1);
				strcpy(chat_user_ids[i], temp_user_id);
				total_len = total_len + strlen(temp_user_id);
				total_len = total_len + 1; // delimitor
			}

			full_ids = (char*)malloc(total_len);
			for (int i = 0; i < chat_info->user_list_size; i++) {
				if (i == 0) {
					strcpy(full_ids, chat_user_ids[i]);
				} else {
					strcat(full_ids, chat_user_ids[i]);
				}
				if (i < chat_info->user_list_size - 1) {
					strcat(full_ids, ",");
				}
			}
		} else {
			full_ids = (char*)malloc(2);
			strcpy(full_ids, " ");
		}

		col_values = eina_list_append(col_values, full_ids);
		/****** add chat users list ********/

		col_values = eina_list_append(col_values, &(chat_info->date));
		col_values = eina_list_append(col_values, &(chat_info->version));
		col_values = eina_list_append(col_values, &(chat_info->admin_id));

		char* where_clause = NULL;

		char chat_id_str[50];
		sprintf(chat_id_str,"%d",chat_info->id.id);
		where_clause = (char*)malloc(strlen(CHAT_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(chat_id_str) + 1);
		strcpy(where_clause, CHAT_INFO_TABLE_CHAT_ID);
		strcat(where_clause, " = ");
		strcat(where_clause, chat_id_str);

		Eina_Bool ret = update_table(db, table_name, col_names, col_types, col_values, where_clause);

		if(!ret) {
			// error handling
		} else {

		}

		free(full_ids);
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
		close_database(db);
	}
}

void update_buddy_pic_db(char* file_path, char* table_name, int id)
{
	if (!file_path || !table_name) {
		return;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		Eina_List* col_values = NULL;
		col_values = eina_list_append(col_values, file_path);

		char* where_clause = NULL;

		char usr_str[50];
		sprintf(usr_str,"%d",id);
		where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(usr_str) + 1);
		strcpy(where_clause, USER_INFO_TABLE_USER_ID);
		strcat(where_clause, " = ");
		strcat(where_clause, usr_str);

		Eina_Bool ret = update_table(db, table_name, col_names, col_types, col_values, where_clause);

		if(!ret) {
			// error handling
		} else {

		}
		free(where_clause);
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
		close_database(db);
	}
}

Eina_List* get_buddy_info(int buddy_id)
{
	Eina_List* user_details = NULL;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		char* table_name = BUDDY_INFO_TABLE_NAME;
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_BUDDY_ID);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PRINT_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_STRUCTURE_VERSION);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHOTO_PATH);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHOTO_ID);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_FIRST_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_LAST_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHONE_NO);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_ACCESS_HASH);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_REAL_FIRST_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_REAL_LAST_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_BUDDY_NAME);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_ONLINE_STATUS);
		col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_LAST_SEEN_TIME);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		char buddy_id_str[50];
		sprintf(buddy_id_str, "%d", buddy_id);

		char* where_clause = (char*)malloc(strlen(BUDDY_INFO_TABLE_BUDDY_ID) + strlen(" = ") + strlen(buddy_id_str) + 1);
		strcpy(where_clause, BUDDY_INFO_TABLE_BUDDY_ID);
		strcat(where_clause, " = ");
		strcat(where_clause, buddy_id_str);

		user_details = get_values_from_table_sync(db, table_name, col_names, col_types, where_clause);
		free(where_clause);

		eina_list_free(col_names);
		eina_list_free(col_types);
	}
	return user_details;
}

void update_receive_media_info_in_db(long long media_id, char* file_path)
{
	if(!file_path) {
		return;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	char* table_name = MEDIA_INFO_TABLE_NAME;

	if (db) {
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FILE_PATH);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		Eina_List* col_values = NULL;
		col_values = eina_list_append(col_values, file_path);

		char media_id_str[50];
		sprintf(media_id_str, "%lld", media_id);

		char* where_clause = (char*)malloc(strlen(MEDIA_INFO_TABLE_MEDIA_ID) + strlen(" = '") + strlen(media_id_str) + strlen("'") + 1);
		strcpy(where_clause, MEDIA_INFO_TABLE_MEDIA_ID);
		strcat(where_clause, " = '");
		strcat(where_clause, media_id_str);
		strcat(where_clause, "'");

		Eina_Bool ret = update_table(db, table_name, col_names, col_types, col_values, where_clause);

		if(!ret) {
			// error handling
		} else {

		}
		free(where_clause);
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
		close_database(db);
	}
}

void insert_media_info_to_db(struct tgl_message *M, char* file_path)
{
	if(!M) {
		return;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	char* table_name = MEDIA_INFO_TABLE_NAME;

	if(db) {
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MEDIA_ID);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MEDIA_TYPE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_ACCESS_HASH);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_USER_ID);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DATE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_CAPTION);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LONGITUDE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LATITUDE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_SIZES_NUM);


		/********************************************************************/

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA1);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA2);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA3);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA4);


		/********************************************************************/


		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHONE_NO);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FIRST_NAME);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LAST_NAME);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FILE_PATH);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);


		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		Eina_List* col_values = NULL;


		int media_type = M->media.type;

		if (media_type == tgl_message_media_photo) {

			char photo_id_str[50];
			sprintf(photo_id_str, "%lld", M->media.photo.id);

			col_values = eina_list_append(col_values, photo_id_str);
			col_values = eina_list_append(col_values, &(media_type));


			char access_hash_str[50];
			sprintf(access_hash_str, "%lld", M->media.photo.access_hash);

			col_values = eina_list_append(col_values, access_hash_str);
			col_values = eina_list_append(col_values, &(M->media.photo.user_id));
			col_values = eina_list_append(col_values, &(M->media.photo.date));

			if(M->media.photo.caption)
				col_values = eina_list_append(col_values, M->media.photo.caption);
			else
				col_values = eina_list_append(col_values, "");

			double longitude = M->media.photo.geo.longitude;
			double latitude = M->media.photo.geo.latitude;

			char long_str[50];
			sprintf(long_str,"%lf",longitude);

			char lat_str[50];
			sprintf(lat_str,"%lf",latitude);

			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, &(M->media.photo.sizes_num));


			int i = 0;
			for (i = 0; i < M->media.photo.sizes_num; i++) {
				//struct tgl_photo_size photo_size = M->media.photo->sizes[i];

				char* photo_type = M->media.photo.sizes[i].type;
				if(photo_type) {
					col_values = eina_list_append(col_values, photo_type);
				} else {
					col_values = eina_list_append(col_values, "");
				}

				int photo_loc_dc = M->media.photo.sizes[i].loc.dc;
				col_values = eina_list_append(col_values, &photo_loc_dc);



				char photo_loc_vol_str[50];
				sprintf(photo_loc_vol_str, "%lld", M->media.photo.sizes[i].loc.volume);

				col_values = eina_list_append(col_values, photo_loc_vol_str);

				int photo_loc_id = M->media.photo.sizes[i].loc.local_id;
				col_values = eina_list_append(col_values, &photo_loc_id);


				char photo_loc_sec_str[50];
				sprintf(photo_loc_sec_str, "%lld", M->media.photo.sizes[i].loc.secret);

				col_values = eina_list_append(col_values, photo_loc_sec_str);

				int photo_width = M->media.photo.sizes[i].w;
				col_values = eina_list_append(col_values, &photo_width);

				int photo_height = M->media.photo.sizes[i].h;
				col_values = eina_list_append(col_values, &photo_height);

				int pic_size = M->media.photo.sizes[i].size;
				col_values = eina_list_append(col_values, &pic_size);

				char* photo_data = M->media.photo.sizes[i].data;
				if (photo_data) {
					col_values = eina_list_append(col_values, photo_data);
				} else {
					col_values = eina_list_append(col_values, "");
				}
			}

			int j = i;
			for (j = i; j < 4; j++) {

				char* photo_type = "";
				col_values = eina_list_append(col_values, photo_type);

				int photo_loc_dc = -1;
				col_values = eina_list_append(col_values, &photo_loc_dc);

				int photo_loc_vol = -1;
				col_values = eina_list_append(col_values, "");

				int photo_loc_id = -1;
				col_values = eina_list_append(col_values, &photo_loc_id);


				col_values = eina_list_append(col_values, "");

				int photo_width = -1;
				col_values = eina_list_append(col_values, &photo_width);

				int photo_height = -1;
				col_values = eina_list_append(col_values, &photo_height);

				int photo_size = -1;
				col_values = eina_list_append(col_values, &photo_size);

				char* photo_data = "";
				col_values = eina_list_append(col_values, photo_data);

			}


		} else if (media_type == tgl_message_media_document) {

			col_values = eina_list_append(col_values, &(M->media.document.id));
			col_values = eina_list_append(col_values, &(media_type));
			col_values = eina_list_append(col_values, &(M->media.document.access_hash));
			col_values = eina_list_append(col_values, &(M->media.document.user_id));
			col_values = eina_list_append(col_values, &(M->media.document.date));

			if(M->media.document.caption)
				col_values = eina_list_append(col_values, M->media.document.caption);
			else
				col_values = eina_list_append(col_values, "");

			double longitude = 0.0f;
			double latitude = 0.0f;

			char long_str[50];
			sprintf(long_str,"%lf",longitude);

			char lat_str[50];
			sprintf(lat_str,"%lf",latitude);

			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, &(M->media.document.size));


			for (int j = 0; j < 4; j++) {

				char* photo_type = "";
				col_values = eina_list_append(col_values, photo_type);

				int photo_loc_dc = -1;
				col_values = eina_list_append(col_values, &photo_loc_dc);

				int photo_loc_vol = -1;
				col_values = eina_list_append(col_values, "");

				int photo_loc_id = -1;
				col_values = eina_list_append(col_values, &photo_loc_id);


				col_values = eina_list_append(col_values, "");

				int photo_width = -1;
				col_values = eina_list_append(col_values, &photo_width);

				int photo_height = -1;
				col_values = eina_list_append(col_values, &photo_height);

				int photo_size = -1;
				col_values = eina_list_append(col_values, &photo_size);

				char* photo_data = "";
				col_values = eina_list_append(col_values, photo_data);

			}
		} else {
			// To be checked
			int dummy = 0;
			col_values = eina_list_append(col_values, &(dummy));
			col_values = eina_list_append(col_values, &(media_type));
			col_values = eina_list_append(col_values, &(dummy));
			col_values = eina_list_append(col_values, &(dummy));
			col_values = eina_list_append(col_values, &(dummy));

			col_values = eina_list_append(col_values, "");

			double longitude = 0.0f;
			double latitude = 0.0f;

			char long_str[50];
			sprintf(long_str,"%lf",longitude);

			char lat_str[50];
			sprintf(lat_str,"%lf",latitude);

			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, &(dummy));

			for (int j = 0; j < 4; j++) {

				char* photo_type = "";
				col_values = eina_list_append(col_values, photo_type);

				int photo_loc_dc = -1;
				col_values = eina_list_append(col_values, &photo_loc_dc);

				int photo_loc_vol = -1;
				col_values = eina_list_append(col_values, "");

				int photo_loc_id = -1;
				col_values = eina_list_append(col_values, &photo_loc_id);


				col_values = eina_list_append(col_values, "");

				int photo_width = -1;
				col_values = eina_list_append(col_values, &photo_width);

				int photo_height = -1;
				col_values = eina_list_append(col_values, &photo_height);

				int photo_size = -1;
				col_values = eina_list_append(col_values, &photo_size);

				char* photo_data = "";
				col_values = eina_list_append(col_values, photo_data);
			}
		}

		if(M->media.phone) {
			//col_values = eina_list_append(col_values, M->media.phone);
			col_values = eina_list_append(col_values, "");
		} else {
			col_values = eina_list_append(col_values, "");
		}

		if(M->media.first_name) {
			//col_values = eina_list_append(col_values, M->media.first_name);
			col_values = eina_list_append(col_values, "");
		} else {
			col_values = eina_list_append(col_values, "");
		}

		if(M->media.last_name) {
			//col_values = eina_list_append(col_values, M->media.last_name);
			col_values = eina_list_append(col_values, "");
		} else {
			col_values = eina_list_append(col_values, "");
		}

		if(file_path) {
			col_values = eina_list_append(col_values, file_path);
		} else {
			col_values = eina_list_append(col_values, "");
		}

		Eina_Bool ret = insert_table(db, table_name, col_names, col_types,col_values);
		if(!ret) {
			//("error: database creation failed");
		} else {

		}
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
		close_database(db);
	}
}


void update_sent_media_info_in_db(struct tgl_message *M, long long unique_val)
{
	if(!M) {
		return;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	char* table_name = MEDIA_INFO_TABLE_NAME;

	if(db) {
		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MEDIA_ID);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MEDIA_TYPE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_ACCESS_HASH);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_USER_ID);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DATE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_CAPTION);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LONGITUDE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LATITUDE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_SIZES_NUM);


		/********************************************************************/

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA1);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA2);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA3);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA4);


		/********************************************************************/


		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHONE_NO);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FIRST_NAME);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LAST_NAME);


		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);


		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);


		Eina_List* col_values = NULL;


		int media_type = M->media.type;

		if (media_type == tgl_message_media_photo) {

			char photo_id_str[50];
			sprintf(photo_id_str, "%lld", M->media.photo.id);

			col_values = eina_list_append(col_values, photo_id_str);
			col_values = eina_list_append(col_values, &(media_type));


			char access_hash_str[50];
			sprintf(access_hash_str, "%lld", M->media.photo.access_hash);

			col_values = eina_list_append(col_values, access_hash_str);
			col_values = eina_list_append(col_values, &(M->media.photo.user_id));
			col_values = eina_list_append(col_values, &(M->media.photo.date));

			if(M->media.photo.caption)
				col_values = eina_list_append(col_values, M->media.photo.caption);
			else
				col_values = eina_list_append(col_values, "");

			double longitude = M->media.photo.geo.longitude;
			double latitude = M->media.photo.geo.latitude;

			char long_str[50];
			sprintf(long_str,"%lf",longitude);

			char lat_str[50];
			sprintf(lat_str,"%lf",latitude);

			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, &(M->media.photo.sizes_num));


			int i = 0;
			for (i = 0; i < M->media.photo.sizes_num; i++) {
				//struct tgl_photo_size photo_size = M->media.photo->sizes[i];

				char* photo_type = M->media.photo.sizes[i].type;
				if(photo_type) {
					col_values = eina_list_append(col_values, photo_type);
				} else {
					col_values = eina_list_append(col_values, "");
				}

				int photo_loc_dc = M->media.photo.sizes[i].loc.dc;
				col_values = eina_list_append(col_values, &photo_loc_dc);



				char photo_loc_vol_str[50];
				sprintf(photo_loc_vol_str, "%lld", M->media.photo.sizes[i].loc.volume);

				col_values = eina_list_append(col_values, photo_loc_vol_str);

				int photo_loc_id = M->media.photo.sizes[i].loc.local_id;
				col_values = eina_list_append(col_values, &photo_loc_id);


				char photo_loc_sec_str[50];
				sprintf(photo_loc_sec_str, "%lld", M->media.photo.sizes[i].loc.secret);

				col_values = eina_list_append(col_values, photo_loc_sec_str);

				int photo_width = M->media.photo.sizes[i].w;
				col_values = eina_list_append(col_values, &photo_width);

				int photo_height = M->media.photo.sizes[i].h;
				col_values = eina_list_append(col_values, &photo_height);

				int pic_size = M->media.photo.sizes[i].size;
				col_values = eina_list_append(col_values, &pic_size);

				char* photo_data = M->media.photo.sizes[i].data;
				if (photo_data) {
					col_values = eina_list_append(col_values, photo_data);
				} else {
					col_values = eina_list_append(col_values, "");
				}
			}

			int j = i;
			for (j = i; j < 4; j++) {

				char* photo_type = "";
				col_values = eina_list_append(col_values, photo_type);

				int photo_loc_dc = -1;
				col_values = eina_list_append(col_values, &photo_loc_dc);

				int photo_loc_vol = -1;
				col_values = eina_list_append(col_values, "");

				int photo_loc_id = -1;
				col_values = eina_list_append(col_values, &photo_loc_id);


				col_values = eina_list_append(col_values, "");

				int photo_width = -1;
				col_values = eina_list_append(col_values, &photo_width);

				int photo_height = -1;
				col_values = eina_list_append(col_values, &photo_height);

				int photo_size = -1;
				col_values = eina_list_append(col_values, &photo_size);

				char* photo_data = "";
				col_values = eina_list_append(col_values, photo_data);

			}


		} else if (media_type == tgl_message_media_document) {

			col_values = eina_list_append(col_values, &(M->media.document.id));
			col_values = eina_list_append(col_values, &(media_type));
			col_values = eina_list_append(col_values, &(M->media.document.access_hash));
			col_values = eina_list_append(col_values, &(M->media.document.user_id));
			col_values = eina_list_append(col_values, &(M->media.document.date));

			if(M->media.document.caption)
				col_values = eina_list_append(col_values, M->media.document.caption);
			else
				col_values = eina_list_append(col_values, "");

			double longitude = 0.0f;
			double latitude = 0.0f;

			char long_str[50];
			sprintf(long_str,"%lf",longitude);

			char lat_str[50];
			sprintf(lat_str,"%lf",latitude);

			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, &(M->media.document.size));


			for (int j = 0; j < 4; j++) {

				char* photo_type = "";
				col_values = eina_list_append(col_values, photo_type);

				int photo_loc_dc = -1;
				col_values = eina_list_append(col_values, &photo_loc_dc);

				int photo_loc_vol = -1;
				col_values = eina_list_append(col_values, "");

				int photo_loc_id = -1;
				col_values = eina_list_append(col_values, &photo_loc_id);


				col_values = eina_list_append(col_values, "");

				int photo_width = -1;
				col_values = eina_list_append(col_values, &photo_width);

				int photo_height = -1;
				col_values = eina_list_append(col_values, &photo_height);

				int photo_size = -1;
				col_values = eina_list_append(col_values, &photo_size);

				char* photo_data = "";
				col_values = eina_list_append(col_values, photo_data);

			}
		} else {
			// To be checked
			int dummy = 0;
			col_values = eina_list_append(col_values, &(dummy));
			col_values = eina_list_append(col_values, &(media_type));
			col_values = eina_list_append(col_values, &(dummy));
			col_values = eina_list_append(col_values, &(dummy));
			col_values = eina_list_append(col_values, &(dummy));

			col_values = eina_list_append(col_values, "");

			double longitude = 0.0f;
			double latitude = 0.0f;

			char long_str[50];
			sprintf(long_str,"%lf",longitude);

			char lat_str[50];
			sprintf(lat_str,"%lf",latitude);

			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, &(dummy));

			for (int j = 0; j < 4; j++) {

				char* photo_type = "";
				col_values = eina_list_append(col_values, photo_type);

				int photo_loc_dc = -1;
				col_values = eina_list_append(col_values, &photo_loc_dc);

				int photo_loc_vol = -1;
				col_values = eina_list_append(col_values, "");

				int photo_loc_id = -1;
				col_values = eina_list_append(col_values, &photo_loc_id);


				col_values = eina_list_append(col_values, "");

				int photo_width = -1;
				col_values = eina_list_append(col_values, &photo_width);

				int photo_height = -1;
				col_values = eina_list_append(col_values, &photo_height);

				int photo_size = -1;
				col_values = eina_list_append(col_values, &photo_size);

				char* photo_data = "";
				col_values = eina_list_append(col_values, photo_data);
			}
		}

		if(M->media.phone) {
			//col_values = eina_list_append(col_values, M->media.phone);
			col_values = eina_list_append(col_values, "");
		} else {
			col_values = eina_list_append(col_values, "");
		}

		if(M->media.first_name) {
			//col_values = eina_list_append(col_values, M->media.first_name);
			col_values = eina_list_append(col_values, "");
		} else {
			col_values = eina_list_append(col_values, "");
		}

		if(M->media.last_name) {
			//col_values = eina_list_append(col_values, M->media.last_name);
			col_values = eina_list_append(col_values, "");
		} else {
			col_values = eina_list_append(col_values, "");
		}


		char* where_clause = NULL;
		if(unique_val != 0 ) {
			char usr_str[50];
			sprintf(usr_str,"%lld",unique_val);
			where_clause = (char*)malloc(strlen(MEDIA_INFO_TABLE_MEDIA_ID) + strlen(" = '") + strlen(usr_str) + strlen("'") + 1);
			strcpy(where_clause, MEDIA_INFO_TABLE_MEDIA_ID);
			strcat(where_clause, " = '");
			strcat(where_clause, usr_str);
			strcat(where_clause, "'");
		} else {
			char usr_str[50];
			sprintf(usr_str,"%lld",M->media.photo.id);
			where_clause = (char*)malloc(strlen(MEDIA_INFO_TABLE_MEDIA_ID) + strlen(" = '") + strlen(usr_str) + strlen("'") + 1);
			strcpy(where_clause, MEDIA_INFO_TABLE_MEDIA_ID);
			strcat(where_clause, " = '");
			strcat(where_clause, usr_str);
			strcat(where_clause, "'");
		}

		Eina_Bool ret = update_table(db, table_name, col_names, col_types, col_values, where_clause);

		if(!ret) {
			//("error: database creation failed");
		} else {

		}
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
		close_database(db);
	}
}


Eina_List* get_image_details_from_db(long long media_id)
{
	Eina_List* vals = NULL;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		char* table_name = MEDIA_INFO_TABLE_NAME;

		char usr_str[50];
		sprintf(usr_str,"%lld",media_id);
		char* where_clause = (char*)malloc(strlen(MEDIA_INFO_TABLE_MEDIA_ID) + strlen(" = ") + strlen(usr_str) + 1);
		strcpy(where_clause, MEDIA_INFO_TABLE_MEDIA_ID);
		strcat(where_clause, " = ");
		strcat(where_clause, usr_str);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);


		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);


		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);


		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MEDIA_ID);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MEDIA_TYPE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_ACCESS_HASH);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_USER_ID);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DATE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_CAPTION);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LONGITUDE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LATITUDE);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_SIZES_NUM);

		/********************************************************************/

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE1);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA1);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE2);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA2);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE3);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA3);

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_TYPE4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_DC4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_VOL4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_ID4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_LOC_SECRET4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE4);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_DATA4);

		/********************************************************************/

		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHONE_NO);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FIRST_NAME);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LAST_NAME);
		col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FILE_PATH);

		vals = get_values_from_table_sync(db, table_name, col_names, col_types, where_clause);
		close_database(db);
		eina_list_free(col_types);
		eina_list_free(col_names);
	}
	return vals;
}


