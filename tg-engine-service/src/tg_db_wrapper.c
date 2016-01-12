/**
 * @file tg_db_wrapper.c
 * @date Jun 26, 2015
 * @author sandeep
 */

#include "tg_db_wrapper.h"
#include "tg_common.h"
#include "tgl-layout.h"

void create_data_base_tables()
{
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
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_BLOCKED);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_DELETED);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_DEFAULT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_DEFAULT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_DEFAULT);

	Eina_Bool ret = create_table(table_name, col_names, col_types);
	if(!ret) {
		// error occured
	}
	eina_list_free(col_names);
	eina_list_free(col_types);

	table_name = BUDDY_INFO_TABLE_NAME;
	col_names = NULL;
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
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_BLOCKED);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_DELETED);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_DEFAULT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_DEFAULT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_DEFAULT);

	ret = create_table(table_name, col_names, col_types);
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

	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MIME_TYPE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_TYPE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_WIDTH);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_HEIGHT);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_DURATION);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_SIZE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_DC);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_THUMB_FILE);

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

	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	ret = create_table(table_name, col_names, col_types);
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

	ret = create_table(table_name, col_names, col_types);
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
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_ID);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	ret = create_table(table_name, col_names, col_types);
	if(!ret) {
		// error occured
	}

	eina_list_free(col_names);
	eina_list_free(col_types);


	/****************************************************/

	table_name = MESSAGE_TRANSPORT_TABLE_NAME;
	col_names = NULL;
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_ROW_ID);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_APP_NAME);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_COMMAND);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_BUDDY_ID);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_MESSAGE_ID);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_MESSAGE_TYPE);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_MESSAGE_DATA);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_TYPE_OF_CHAT);

	col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_AUTO_INC_KEY);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	ret = create_table(table_name, col_names, col_types);
	if(!ret) {
		// error occured
	}

	eina_list_free(col_names);
	eina_list_free(col_types);


	table_name = MEDIA_TRANSPORT_TABLE_NAME;
	col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_ROW_ID);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_APP_NAME);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_COMMAND);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_BUDDY_ID);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_MESSAGE_ID);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_MEDIA_ID);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_MESSAGE_TYPE);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_FILE_PATH);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_TYPE_OF_CHAT);

	col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_AUTO_INC_KEY);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	ret = create_table(table_name, col_names, col_types);
	if(!ret) {
		// error occured
	}

	eina_list_free(col_names);
	eina_list_free(col_types);
}


void delete_message_from_unsent_db(int message_id)
{
	char* where_clause = NULL;
	char msg_id_str[50];
	sprintf(msg_id_str,"%d", message_id);
	where_clause = (char*)malloc(strlen(MESSAGE_TRANSPORT_TABLE_MESSAGE_ID) + strlen(" = ") + strlen(msg_id_str) + 1);
	strcpy(where_clause, MESSAGE_TRANSPORT_TABLE_MESSAGE_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, msg_id_str);
	Eina_Bool ret = delete_record(MESSAGE_TRANSPORT_TABLE_NAME, where_clause);
	free(where_clause);
	if(!ret) {
		//("error: database creation failed");
	} else {

	}
}

Eina_List* get_all_unsent_text_messages()
{
	Eina_List* unsent_msg_details = NULL;
	Eina_List* ret_msg_details = NULL;
	char* table_name = MESSAGE_TRANSPORT_TABLE_NAME;
	Eina_List* col_names = NULL;

	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_APP_NAME);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_COMMAND);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_BUDDY_ID);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_MESSAGE_ID);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_MESSAGE_TYPE);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_MESSAGE_DATA);
	col_names = eina_list_append(col_names, MESSAGE_TRANSPORT_TABLE_TYPE_OF_CHAT);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	unsent_msg_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, MESSAGE_TRANSPORT_TABLE_ROW_ID, EINA_TRUE, NULL);

	eina_list_free(col_names);
	eina_list_free(col_types);

	if (unsent_msg_details) {
		for (int i = 0; i < eina_list_count(unsent_msg_details) ; i++) {
			Eina_List* ts_msg = eina_list_nth(unsent_msg_details, i);
			sent_message_data_s* msg_info = (sent_message_data_s*)malloc(sizeof(sent_message_data_s));

			char *temp_app_name = (char*)eina_list_nth(ts_msg, 0);
			if (temp_app_name) {
				msg_info->app_name  = strdup(temp_app_name);
				free(temp_app_name);
			} else {
				msg_info->app_name = NULL;
			}

			char *temp_command = (char*)eina_list_nth(ts_msg, 1);
			if (temp_command) {
				msg_info->command  = strdup(temp_command);
				free(temp_command);
			} else {
				msg_info->command = NULL;
			}

			char *temp_buddy_id = (char*)eina_list_nth(ts_msg, 2);
			if (temp_buddy_id) {
				msg_info->buddy_id  = strdup(temp_buddy_id);
				free(temp_buddy_id);
			} else {
				msg_info->buddy_id = NULL;
			}

			char *temp_msg_id = (char*)eina_list_nth(ts_msg, 3);
			if (temp_msg_id) {
				msg_info->message_id  = strdup(temp_msg_id);
				free(temp_msg_id);
			} else {
				msg_info->message_id = NULL;
			}

			char *temp_msg_type = (char*)eina_list_nth(ts_msg, 4);
			if (temp_msg_type) {
				msg_info->message_type  = strdup(temp_msg_type);
				free(temp_msg_type);
			} else {
				msg_info->message_type = NULL;
			}

			char *temp_msg_data = (char*)eina_list_nth(ts_msg, 5);
			if (temp_msg_data) {
				msg_info->message_data  = strdup(temp_msg_data);
				free(temp_msg_data);
			} else {
				msg_info->message_data = NULL;
			}

			char *temp_type_of_chat = (char*)eina_list_nth(ts_msg, 6);
			if (temp_type_of_chat) {
				msg_info->type_of_chat  = strdup(temp_type_of_chat);
				free(temp_type_of_chat);
			} else {
				msg_info->type_of_chat = NULL;
			}
			ret_msg_details = eina_list_append(ret_msg_details, msg_info);
			eina_list_free(ts_msg);
		}

		eina_list_free(unsent_msg_details);
	}
	return ret_msg_details;
}

void delete_media_from_unsent_db(int message_id)
{
	char* where_clause = NULL;
	char msg_id_str[50];
	sprintf(msg_id_str,"%d", message_id);
	where_clause = (char*)malloc(strlen(MEDIA_TRANSPORT_TABLE_MESSAGE_ID) + strlen(" = ") + strlen(msg_id_str) + 1);
	strcpy(where_clause, MEDIA_TRANSPORT_TABLE_MESSAGE_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, msg_id_str);
	Eina_Bool ret = delete_record(MEDIA_TRANSPORT_TABLE_NAME, where_clause);
	free(where_clause);
	if(!ret) {
		//("error: database creation failed");
	} else {

	}
}

Eina_List* get_all_unsent_media_messages()
{
	Eina_List* unsent_msg_details = NULL;
	Eina_List* ret_msg_details = NULL;
	char* table_name = MEDIA_TRANSPORT_TABLE_NAME;
	Eina_List* col_names = NULL;

	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_APP_NAME);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_COMMAND);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_BUDDY_ID);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_MESSAGE_ID);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_MEDIA_ID);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_MESSAGE_TYPE);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_FILE_PATH);
	col_names = eina_list_append(col_names, MEDIA_TRANSPORT_TABLE_TYPE_OF_CHAT);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	unsent_msg_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, MEDIA_TRANSPORT_TABLE_ROW_ID, EINA_TRUE, NULL);

	eina_list_free(col_names);
	eina_list_free(col_types);

	if (unsent_msg_details) {
		for (int i = 0; i < eina_list_count(unsent_msg_details) ; i++) {
			Eina_List* ts_msg = eina_list_nth(unsent_msg_details, i);
			sent_media_data_s* msg_info = (sent_media_data_s*)malloc(sizeof(sent_media_data_s));

			char *temp_app_name = (char*)eina_list_nth(ts_msg, 0);
			if (temp_app_name) {
				msg_info->app_name  = strdup(temp_app_name);
				free(temp_app_name);
			} else {
				msg_info->app_name = NULL;
			}

			char *temp_command = (char*)eina_list_nth(ts_msg, 1);
			if (temp_command) {
				msg_info->command  = strdup(temp_command);
				free(temp_command);
			} else {
				msg_info->command = NULL;
			}

			char *temp_buddy_id = (char*)eina_list_nth(ts_msg, 2);
			if (temp_buddy_id) {
				msg_info->buddy_id  = strdup(temp_buddy_id);
				free(temp_buddy_id);
			} else {
				msg_info->buddy_id = NULL;
			}

			char *temp_msg_id = (char*)eina_list_nth(ts_msg, 3);
			if (temp_msg_id) {
				msg_info->message_id  = strdup(temp_msg_id);
				free(temp_msg_id);
			} else {
				msg_info->message_id = NULL;
			}

			char *temp_media_id = (char*)eina_list_nth(ts_msg, 4);
			if (temp_media_id) {
				msg_info->media_id  = strdup(temp_media_id);
				free(temp_media_id);
			} else {
				msg_info->media_id = NULL;
			}

			char *temp_msg_type = (char*)eina_list_nth(ts_msg, 5);
			if (temp_msg_type) {
				msg_info->message_type  = strdup(temp_msg_type);
				free(temp_msg_type);
			} else {
				msg_info->message_type = NULL;
			}

			char *temp_file_path = (char*)eina_list_nth(ts_msg, 6);
			if (temp_file_path) {
				msg_info->file_path  = strdup(temp_file_path);
				free(temp_file_path);
			} else {
				msg_info->file_path = NULL;
			}

			char *temp_type_of_chat = (char*)eina_list_nth(ts_msg, 7);
			if (temp_type_of_chat) {
				msg_info->type_of_chat  = strdup(temp_type_of_chat);
				free(temp_type_of_chat);
			} else {
				msg_info->type_of_chat = NULL;
			}
			ret_msg_details = eina_list_append(ret_msg_details, msg_info);
			eina_list_free(ts_msg);
		}

		eina_list_free(unsent_msg_details);
	}
	return ret_msg_details;
}


void create_buddy_msg_table(const char* table_name)
{
	if(!table_name) {
		return;
	}
	// create user info table
	Eina_List* col_names = NULL;
	//col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ROW_ID);
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
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_STATE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_LENGTH);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_TYPE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNIQUE_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MARKED_FOR_DELETE);


	Eina_List* col_types = NULL;
	//col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_AUTO_INC_KEY);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_Bool ret = create_table(table_name, col_names, col_types);
	if(!ret) {
		//("error: database creation failed");
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
}


int set_date_item_to_table(char* tb_name, int recent_msg_date)
{
	struct tgl_message* last_msg = get_latest_message_from_message_table(tb_name);
	recent_msg_date = recent_msg_date - 1;
	if (last_msg) {
		int old_date = last_msg->date;
		time_t old_t = old_date;

		struct tm old_lt;
		(void) localtime_r(&old_t, &old_lt);


		int cur_time = recent_msg_date;
		time_t new_t = cur_time;

		struct tm new_lt;
		(void) localtime_r(&new_t, &new_lt);

		if (old_lt.tm_mday == new_lt.tm_mday && old_lt.tm_mon == new_lt.tm_mon && old_lt.tm_year == new_lt.tm_year) {
			// no need of new date
			if (last_msg->message) {
				free(last_msg->message);
			}
			free(last_msg);

			return -1;
		} else {
			int cur_time = recent_msg_date;
			time_t t = cur_time;
			char res[256];
			sprintf(res, "%d", cur_time);

			struct tgl_message date_msg;
			date_msg.id = recent_msg_date;
			date_msg.media.type = tgl_message_media_none;
			date_msg.date = recent_msg_date;
			date_msg.message = res;
			date_msg.message_len = strlen(res);
			date_msg.service = 2;
			date_msg.unread = 0;
			date_msg.out = 0;
			date_msg.is_marked_for_delete = 0;
			insert_msg_into_db(&date_msg, tb_name, t);

			if (last_msg->message) {
				free(last_msg->message);
			}
			free(last_msg);

			return date_msg.id;
		}

	} else {
		int cur_time = recent_msg_date;
		time_t t = cur_time;
		char res[256];
		sprintf(res, "%d", cur_time);

		struct tgl_message date_msg;
		date_msg.id = recent_msg_date;
		date_msg.media.type = tgl_message_media_none;
		date_msg.date = recent_msg_date;
		date_msg.message = res;
		date_msg.message_len = strlen(res);
		date_msg.service = 2;
		date_msg.unread = 0;
		date_msg.out = 0;
		date_msg.is_marked_for_delete = 0;
		insert_msg_into_db(&date_msg, tb_name, t);
		return date_msg.id;
	}
	return -1;
}


int update_current_date_to_table(char* tb_name, int recent_msg_date)
{
	struct tgl_message* last_msg = get_latest_message_from_message_table(tb_name);
	recent_msg_date = recent_msg_date -1;
	if (last_msg) {
		int old_date = last_msg->date;
		time_t old_t = old_date;

		struct tm old_lt;
		(void) localtime_r(&old_t, &old_lt);

		time_t new_t = recent_msg_date;

		struct tm new_lt;
		(void) localtime_r(&new_t, &new_lt);

		if (old_lt.tm_mday == new_lt.tm_mday && old_lt.tm_mon == new_lt.tm_mon && old_lt.tm_year == new_lt.tm_year) {
			// no need of new date
			if (last_msg->message) {
				free(last_msg->message);
			}
			free(last_msg);

			return -1;
		} else {

			time_t t = recent_msg_date;
			char res[256];
			sprintf(res, "%d", recent_msg_date);

			struct tgl_message date_msg;
			date_msg.id = recent_msg_date;
			date_msg.media.type = tgl_message_media_none;
			date_msg.date = recent_msg_date;
			date_msg.message = res;
			date_msg.message_len = strlen(res);
			date_msg.service = 2;
			date_msg.unread = 0;
			date_msg.out = 0;
			date_msg.is_marked_for_delete = 0;
			insert_msg_into_db(&date_msg, tb_name, t);
			if (last_msg->message) {
				free(last_msg->message);
			}
			free(last_msg);

			return date_msg.id;
		}

	} else {

		time_t t = recent_msg_date;
		char res[256];
		sprintf(res, "%d", recent_msg_date);

		struct tgl_message date_msg;
		date_msg.id = recent_msg_date;
		date_msg.media.type = tgl_message_media_none;
		date_msg.date = recent_msg_date;
		date_msg.message = res;
		date_msg.message_len = strlen(res);
		date_msg.service = 2;
		date_msg.unread = 0;
		date_msg.out = 0;
		date_msg.is_marked_for_delete = 0;
		insert_msg_into_db(&date_msg, tb_name, t);
		return date_msg.id;
	}
	return -1;
}



int insert_current_date_to_table(char* tb_name)
{
	struct tgl_message* last_msg = get_latest_message_from_message_table(tb_name);
	if (last_msg) {
		int old_date = last_msg->date;
		time_t old_t = old_date;

		struct tm old_lt;
		(void) localtime_r(&old_t, &old_lt);


		int cur_time = time(NULL);
		time_t new_t = cur_time;

		struct tm new_lt;
		(void) localtime_r(&new_t, &new_lt);

		if (old_lt.tm_mday == new_lt.tm_mday && old_lt.tm_mon == new_lt.tm_mon && old_lt.tm_year == new_lt.tm_year) {
			// no need of new date
			if (last_msg->message) {
				free(last_msg->message);
			}
			free(last_msg);

			return -1;
		} else {
			int cur_time = time(NULL);
			time_t t = cur_time;
#if 0
			char *format = NULL;
			format = "%a, %d%b. %Y";

			struct tm lt;
			char res[256];
			(void) localtime_r(&t, &lt);

			if (strftime(res, sizeof(res), format, &lt) == 0) {
				(void) fprintf(stderr,  "strftime(3): cannot format supplied "
						"date/time into buffer of size %u "
						"using: '%s'\n",
						sizeof(res), format);
			}
#else
			// convert time to string
			char res[256];
			sprintf(res, "%d", cur_time);
#endif
			struct tgl_message date_msg;
			date_msg.id = get_time_stamp_in_macro();
			date_msg.media.type = tgl_message_media_none;
			date_msg.date = cur_time;
			date_msg.message = res;
			date_msg.message_len = strlen(res);
			date_msg.service = 2;
			date_msg.unread = 0;
			date_msg.out = 0;
			date_msg.is_marked_for_delete = 0;
			insert_msg_into_db(&date_msg, tb_name, t);
			if (last_msg->message) {
				free(last_msg->message);
			}
			free(last_msg);
			if (date_msg.id < 0) {
				date_msg.id = -1 * date_msg.id;
			}
			return date_msg.id;
		}

	} else {
		int cur_time = time(NULL);
		time_t t = cur_time;
#if 0
		char *format = NULL;
		format = "%a, %d%b. %Y";

		struct tm lt;
		char res[256];
		(void) localtime_r(&t, &lt);

		if (strftime(res, sizeof(res), format, &lt) == 0) {
			(void) fprintf(stderr,  "strftime(3): cannot format supplied "
					"date/time into buffer of size %u "
					"using: '%s'\n",
					sizeof(res), format);
		}
#else
		// convert time to string
		char res[256];
		sprintf(res, "%d", cur_time);
#endif
		struct tgl_message date_msg;
		date_msg.id = get_time_stamp_in_macro();
		date_msg.media.type = tgl_message_media_none;
		date_msg.date = cur_time;
		date_msg.message = res;
		date_msg.message_len = strlen(res);
		date_msg.service = 2;
		date_msg.unread = 0;
		date_msg.out = 0;
		date_msg.is_marked_for_delete = 0;
		insert_msg_into_db(&date_msg, tb_name, t);
		if (date_msg.id < 0) {
			date_msg.id = -1 * date_msg.id;
		}
		return date_msg.id;
	}
	return -1;
}

Eina_Bool insert_buddy_msg_to_db(struct tgl_message *M)
{
	// get user name using id from buddy_info_table
	int t = 0;
	int user_id = 0;
	if (tgl_get_peer_type(M->to_id) == TGL_PEER_USER) {
		user_id = M->from_id.id;
	} else if (tgl_get_peer_type(M->to_id) == TGL_PEER_CHAT) {
		user_id = M->to_id.id;
	}
	M->is_marked_for_delete = 0;
	char* tb_name = get_table_name_from_number(user_id);
	Eina_Bool ret = insert_msg_into_db(M, tb_name, t);
	free(tb_name);
	return ret;
}


struct tgl_message* get_latest_message_from_message_table(char* table_name)
{

	struct tgl_message* message = NULL;

	Eina_List* message_details = NULL;

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
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_STATE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_LENGTH);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_TYPE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNIQUE_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MARKED_FOR_DELETE);


	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	message_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, MESSAGE_INFO_TABLE_DATE, EINA_FALSE, NULL);

	eina_list_free(col_names);
	eina_list_free(col_types);


	if (message_details && eina_list_count(message_details) > 0) {
		Eina_List* ts_msg = eina_list_nth(message_details, 0);

		message = (struct tgl_message*)malloc(sizeof(struct tgl_message));


		int *temp_msg_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_msg_id) {
			message->id  = *temp_msg_id;
			free(temp_msg_id);
		}

		int *temp_flags = (int*)eina_list_nth(ts_msg, 1);
		if (temp_flags) {
			message->flags  = *temp_flags;
			free(temp_flags);
		}

		int *temp_fwd_from_id = (int*)eina_list_nth(ts_msg, 2);
		if (temp_fwd_from_id) {
			message->fwd_from_id.id  = *temp_fwd_from_id;
			free(temp_fwd_from_id);
		}

		int *temp_fwd_date = (int*)eina_list_nth(ts_msg, 3);
		if (temp_fwd_date) {
			message->fwd_date  = *temp_fwd_date;
			free(temp_fwd_date);
		}


		int *temp_from_id = (int*)eina_list_nth(ts_msg, 4);
		if (temp_from_id) {
			message->from_id.id  = *temp_from_id;
			free(temp_from_id);
		}

		int *temp_to_id = (int*)eina_list_nth(ts_msg, 5);
		if (temp_to_id) {
			message->to_id.id  = *temp_to_id;
			free(temp_to_id);
		}

		int *temp_out = (int*)eina_list_nth(ts_msg, 6);
		if (temp_out) {
			message->out  = *temp_out;
			free(temp_out);
		}

		int *temp_unread = (int*)eina_list_nth(ts_msg, 7);
		if (temp_unread) {
			message->unread  = *temp_unread;
			free(temp_unread);
		}

		int *temp_date = (int*)eina_list_nth(ts_msg, 8);
		if (temp_date) {
			message->date  = *temp_date;
			free(temp_date);
		}

		int *temp_service = (int*)eina_list_nth(ts_msg, 9);
		if (temp_service) {
			message->service  = *temp_service;
			free(temp_service);
		}

		char *temp_msg = (char*)eina_list_nth(ts_msg, 10);
		if (temp_msg) {
			message->message  = strdup(temp_msg);
			free(temp_msg);
		}

		int *temp_message_state = (int*)eina_list_nth(ts_msg, 11);
		if (temp_message_state) {
			message->msg_state  = *temp_message_state;
			free(temp_message_state);
		}

		int *temp_message_len = (int*)eina_list_nth(ts_msg, 12);
		if (temp_message_len) {
			message->message_len  = *temp_message_len;
			free(temp_message_len);
		}

		int *temp_media_type = (int*)eina_list_nth(ts_msg, 13);
		if (temp_media_type) {
			message->media.type  = *temp_media_type;
			free(temp_media_type);
		}

		int *temp_delete_marked = (int*)eina_list_nth(ts_msg, 14);
		if (temp_delete_marked) {
			message->is_marked_for_delete  = *temp_delete_marked;
			free(temp_delete_marked);
		}

		// to do, get media id based on media type
	}
	return message;
}


Eina_List* get_all_message_ids_from_table(char *table_name)
{
	if (!table_name) {
		return NULL;
	}

	Eina_List *msg_ids = NULL;
	Eina_List *message_details = NULL;
	Eina_List *col_names = NULL;
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ID);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	char* where_clause = NULL;
	char delete_str[50];
	sprintf(delete_str,"%d",1);
	where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_MARKED_FOR_DELETE) + strlen(" = ") + strlen(delete_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_MARKED_FOR_DELETE);
	strcat(where_clause, " = ");
	strcat(where_clause, delete_str);

	message_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	free(where_clause);
	eina_list_free(col_names);
	eina_list_free(col_types);

	if (msg_ids) {
		for (int i = 0; i < eina_list_count(msg_ids); i++) {
			Eina_List* ts_msg = eina_list_nth(message_details, 0);
			int *temp_msg_id = (int*)eina_list_nth(ts_msg, 0);
			if (temp_msg_id) {
				int msg_id  = *temp_msg_id;
				msg_ids = eina_list_append(msg_ids, (void*)msg_id);
				free(temp_msg_id);
			}
		}
	}
	return msg_ids;
}

struct tgl_message* get_message_from_message_tableby_message_id(char *table_name, int msg_id)
{
	if (!table_name) {
		return NULL;
	}
	struct tgl_message *message = NULL;
	Eina_List *message_details = NULL;

	Eina_List *col_names = NULL;
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
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_STATE);
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	char* where_clause = NULL;
	char msg_id_str[50];
	sprintf(msg_id_str,"%d",msg_id);
	where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_MESSAGE_ID) + strlen(" = ") + strlen(msg_id_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_MESSAGE_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, msg_id_str);

	//message_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, MESSAGE_INFO_TABLE_DATE, EINA_FALSE, where_clause);
	message_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);
	free(where_clause);

	if (message_details && eina_list_count(message_details) > 0) {
		Eina_List* ts_msg = eina_list_nth(message_details, 0);

		message = (struct tgl_message*)malloc(sizeof(struct tgl_message));


		int *temp_msg_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_msg_id) {
			message->id  = *temp_msg_id;
			free(temp_msg_id);
		}

		int *temp_flags = (int*)eina_list_nth(ts_msg, 1);
		if (temp_flags) {
			message->flags  = *temp_flags;
			free(temp_flags);
		}


		int *temp_fwd_from_id = (int*)eina_list_nth(ts_msg, 2);
		if (temp_fwd_from_id) {
			message->fwd_from_id.id  = *temp_fwd_from_id;
			free(temp_fwd_from_id);
		}


		int *temp_fwd_date = (int*)eina_list_nth(ts_msg, 3);
		if (temp_fwd_date) {
			message->fwd_date  = *temp_fwd_date;
			free(temp_fwd_date);
		}


		int *temp_from_id = (int*)eina_list_nth(ts_msg, 4);
		if (temp_from_id) {
			message->from_id.id  = *temp_from_id;
			free(temp_from_id);
		}

		int *temp_to_id = (int*)eina_list_nth(ts_msg, 5);
		if (temp_to_id) {
			message->to_id.id  = *temp_to_id;
			free(temp_to_id);
		}

		int *temp_out = (int*)eina_list_nth(ts_msg, 6);
		if (temp_out) {
			message->out  = *temp_out;
			free(temp_out);
		}

		int *temp_unread = (int*)eina_list_nth(ts_msg, 7);
		if (temp_unread) {
			message->unread  = *temp_unread;
			free(temp_unread);
		}

		int *temp_date = (int*)eina_list_nth(ts_msg, 8);
		if (temp_date) {
			message->date  = *temp_date;
			free(temp_date);
		}

		int *temp_service = (int*)eina_list_nth(ts_msg, 9);
		if (temp_service) {
			message->service  = *temp_service;
			free(temp_service);
		}

		char *temp_msg = (char*)eina_list_nth(ts_msg, 10);
		if (temp_msg) {
			message->message  = strdup(temp_msg);
			free(temp_msg);
		}

		int *temp_message_state = (int*)eina_list_nth(ts_msg, 11);
		if (temp_message_state) {
			message->msg_state  = *temp_message_state;
			free(temp_message_state);
		}

		int *temp_message_len = (int*)eina_list_nth(ts_msg, 12);
		if (temp_message_len) {
			message->message_len  = *temp_message_len;
			free(temp_message_len);
		}

		int *temp_media_type = (int*)eina_list_nth(ts_msg, 13);
		if (temp_media_type) {
			message->media.type  = *temp_media_type;
			free(temp_media_type);
		}
		// to do, get media id based on media type
	}
	return message;

}



void update_peer_info_database(tgl_peer_t* UC, int is_unknown)
{
	if (!UC) {
		return;
	}

	char* table_name = PEER_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = NULL;
	col_names = eina_list_append(col_names, PEER_INFO_TABLE_CHAT_ID);
	col_names = eina_list_append(col_names, PEER_INFO_TABLE_PEER_TYPE);
	col_names = eina_list_append(col_names, PEER_INFO_TABLE_FLAGS);

	col_names = eina_list_append(col_names, PEER_INFO_TABLE_LAST_MESSAGE_DATE);
	col_names = eina_list_append(col_names, PEER_INFO_TABLE_PRINT_NAME);
	col_names = eina_list_append(col_names, PEER_INFO_TABLE_STRUCT_VERSION);

	col_names = eina_list_append(col_names, PEER_INFO_TABLE_LAST_SEEN_TIME);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_ID);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, &(UC->id.id));
	col_values = eina_list_append(col_values, &(UC->id.type));
	col_values = eina_list_append(col_values, &(UC->flags));


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
	col_values = eina_list_append(col_values, &(is_unknown));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		// already exist. So update the table
		char* where_clause = NULL;
		char user_id_str[50];
		sprintf(user_id_str,"%d",UC->id.id);
		where_clause = (char*)malloc(strlen(PEER_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(user_id_str) + 1);
		strcpy(where_clause, PEER_INFO_TABLE_CHAT_ID);
		strcat(where_clause, " = ");
		strcat(where_clause, user_id_str);
		ret = update_table(table_name, col_names, col_types, col_values, where_clause);
		free(where_clause);
	} else {

	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

void delete_chat_from_db(int peer_id)
{
	char* where_clause = NULL;
	char user_id_str[50];
	sprintf(user_id_str,"%d", peer_id);
	where_clause = (char*)malloc(strlen(PEER_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(user_id_str) + 1);
	strcpy(where_clause, PEER_INFO_TABLE_CHAT_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, user_id_str);
	Eina_Bool ret = delete_record(PEER_INFO_TABLE_NAME, where_clause);
	free(where_clause);
	if(!ret) {
		//("error: database creation failed");
	} else {

	}
}

void delete_buddy_from_db(int peer_id)
{
	char* where_clause = NULL;
	char user_id_str[50];
	sprintf(user_id_str,"%d", peer_id);
	where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(user_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, user_id_str);
	Eina_Bool ret = delete_record(BUDDY_INFO_TABLE_NAME, where_clause);
	free(where_clause);
	if(!ret) {
		//("error: database creation failed");
	} else {

	}
}

void init_insert_peer_into_database(tgl_peer_t* UC, int last_msg_id, int unread_count, int is_unknown)
{
	if (!UC) {
		return;
	}

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
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_ID);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

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
	col_values = eina_list_append(col_values, &(is_unknown));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {

	} else {

	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}


void insert_peer_into_database(tgl_peer_t* UC, int last_msg_id, int unread_count, int is_unknown)
{
	if (!UC) {
		return;
	}

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
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_ID);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

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
	col_values = eina_list_append(col_values, &(is_unknown));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		// already exist. So update the table
		char* where_clause = NULL;
		char user_id_str[50];
		sprintf(user_id_str,"%d",UC->id.id);
		where_clause = (char*)malloc(strlen(PEER_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(user_id_str) + 1);
		strcpy(where_clause, PEER_INFO_TABLE_CHAT_ID);
		strcat(where_clause, " = ");
		strcat(where_clause, user_id_str);
		ret = update_table(table_name, col_names, col_types, col_values, where_clause);
	} else {

	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

struct tgl_message* get_message_from_message_table(long long msg_id, char* table_name)
{
	struct tgl_message* message = NULL;

	Eina_List* message_details = NULL;
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
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_STATE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_LENGTH);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_TYPE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNIQUE_ID);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	char *where_clause = NULL;
	char msg_id_str[50];
	sprintf(msg_id_str, "%lld", msg_id);
	where_clause = (char *)malloc(strlen(MESSAGE_INFO_TABLE_MESSAGE_ID) + strlen(" = ") + strlen(msg_id_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_MESSAGE_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, msg_id_str);

	message_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	free(where_clause);
	eina_list_free(col_names);
	eina_list_free(col_types);

	if (message_details && eina_list_count(message_details) > 0) {
		Eina_List* ts_msg = eina_list_nth(message_details, 0);

		message = (struct tgl_message*)malloc(sizeof(struct tgl_message));


		int *temp_msg_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_msg_id) {
			message->id  = *temp_msg_id;
			free(temp_msg_id);
		}

		int *temp_flags = (int*)eina_list_nth(ts_msg, 1);
		if (temp_flags) {
			message->flags  = *temp_flags;
			free(temp_flags);
		}


		int *temp_fwd_from_id = (int*)eina_list_nth(ts_msg, 2);
		if (temp_fwd_from_id) {
			message->fwd_from_id.id  = *temp_fwd_from_id;
			free(temp_fwd_from_id);
		}


		int *temp_fwd_date = (int*)eina_list_nth(ts_msg, 3);
		if (temp_fwd_date) {
			message->fwd_date  = *temp_fwd_date;
			free(temp_fwd_date);
		}


		int *temp_from_id = (int*)eina_list_nth(ts_msg, 4);
		if (temp_from_id) {
			message->from_id.id  = *temp_from_id;
			free(temp_from_id);
		}

		int *temp_to_id = (int*)eina_list_nth(ts_msg, 5);
		if (temp_to_id) {
			message->to_id.id  = *temp_to_id;
			free(temp_to_id);
		}

		int *temp_out = (int*)eina_list_nth(ts_msg, 6);
		if (temp_out) {
			message->out  = *temp_out;
			free(temp_out);
		}

		int *temp_unread = (int*)eina_list_nth(ts_msg, 7);
		if (temp_unread) {
			message->unread  = *temp_unread;
			free(temp_unread);
		}

		int *temp_date = (int*)eina_list_nth(ts_msg, 8);
		if (temp_date) {
			message->date  = *temp_date;
			free(temp_date);
		}

		int *temp_service = (int*)eina_list_nth(ts_msg, 9);
		if (temp_service) {
			message->service  = *temp_service;
			free(temp_service);
		}

		char *temp_msg = (char*)eina_list_nth(ts_msg, 10);
		if (temp_msg) {
			message->message  = strdup(temp_msg);
			free(temp_msg);
		}

		int *temp_message_state = (int*)eina_list_nth(ts_msg, 11);
		if (temp_message_state) {
			message->msg_state  = *temp_message_state;
			free(temp_message_state);
		}

		int *temp_message_len = (int*)eina_list_nth(ts_msg, 12);
		if (temp_message_len) {
			message->message_len  = *temp_message_len;
			free(temp_message_len);
		}

		int *temp_media_type = (int*)eina_list_nth(ts_msg, 13);
		if (temp_media_type) {
			message->media.type  = *temp_media_type;
			free(temp_media_type);
		}

		char *temp_media_id = (char*)eina_list_nth(ts_msg, 14);

		char *eptr;
		if(message->media.type == tgl_message_media_none) {

			if (temp_media_id) {
				free(temp_media_id);
			}

		} else if(message->media.type == tgl_message_media_photo) {

			if (temp_media_id) {
				message->media.photo.id  = strtoll(temp_media_id, &eptr, 10);
				free(temp_media_id);
			}

		} else if(message->media.type == tgl_message_media_document) {

			if (temp_media_id) {
				message->media.document.id  = strtoll(temp_media_id, &eptr, 10);
				free(temp_media_id);
			}

		} else if(message->media.type == tgl_message_media_geo) {

			if (temp_media_id) {
				free(temp_media_id);
			}

		} else if(message->media.type == tgl_message_media_contact) {

			if (temp_media_id) {
				free(temp_media_id);
			}

		} else if(message->media.type == tgl_message_media_unsupported) {

			if (temp_media_id) {
				free(temp_media_id);
			}

		} else if(message->media.type == tgl_message_media_photo_encr) {

			if (temp_media_id) {
				message->media.encr_photo.id  = strtoll(temp_media_id, &eptr, 10);
				free(temp_media_id);
			}

		} else if(message->media.type == tgl_message_media_document_encr) {

			if (temp_media_id) {
				message->media.encr_document.id  = strtoll(temp_media_id, &eptr, 10);
				free(temp_media_id);
			}

		} else  {
			if (temp_media_id) {
				free(temp_media_id);
			}
		}
		int *temp_unique_id = (int*)eina_list_nth(ts_msg, 15);
		if (temp_unique_id) {
			free(temp_unique_id);
		}
	}
	return message;
}

Eina_Bool insert_msg_into_db(struct tgl_message *M, char* table_name, int unique_id)
{
	if(!M) {
		return EINA_FALSE;
	}

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
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_STATE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_LENGTH);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_TYPE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNIQUE_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MARKED_FOR_DELETE);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
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
		col_values = eina_list_append(col_values, "");

	col_values = eina_list_append(col_values, &(M->msg_state));
	col_values = eina_list_append(col_values, &(M->message_len));
	col_values = eina_list_append(col_values, &(M->media.type));

	char *dummy_val = "";
	if(M->media.type == tgl_message_media_none) {
		col_values = eina_list_append(col_values, (dummy_val));
	} else if(M->media.type == tgl_message_media_photo) {

		char temp_media_id[50];
		sprintf(temp_media_id, "%lld", M->media.photo.id);

		col_values = eina_list_append(col_values, temp_media_id);
	} else if(M->media.type == tgl_message_media_document) {

		char temp_media_id[50];
		sprintf(temp_media_id, "%lld", M->media.document.id);

		col_values = eina_list_append(col_values, temp_media_id);
	} else if(M->media.type == tgl_message_media_geo) {
		char temp_media_id[50];
		sprintf(temp_media_id, "%lld", M->media.document.id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else if(M->media.type == tgl_message_media_contact) {

		char temp_media_id[50];
		sprintf(temp_media_id, "%d",M->media.user_id);

		col_values = eina_list_append(col_values, temp_media_id);
	} else if(M->media.type == tgl_message_media_unsupported) {
		col_values = eina_list_append(col_values, (dummy_val));
	} else if(M->media.type == tgl_message_media_photo_encr) {

		char temp_media_id[50];
		sprintf(temp_media_id, "%lld",M->media.encr_photo.id);

		col_values = eina_list_append(col_values, temp_media_id);
	} else if(M->media.type == tgl_message_media_document_encr) {

		char temp_media_id[50];
		sprintf(temp_media_id, "%lld",M->media.encr_document.id);

		col_values = eina_list_append(col_values, temp_media_id);
	} else  {
		col_values = eina_list_append(col_values, (dummy_val));
	}

	col_values = eina_list_append(col_values, &unique_id);
	col_values = eina_list_append(col_values, &(M->is_marked_for_delete));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		//("error: database creation failed");
	} else {

	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
	return ret;
}

void update_msg_into_db(struct tgl_message *M, char* table_name, int unique_id)
{
	if(!M) {
		return;
	}

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
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_STATE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_LENGTH);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_TYPE);
		col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_ID);
		if (unique_id != -1) {
			col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNIQUE_ID);
		}

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
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
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
		if (unique_id != -1) {
			col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
		}

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

		col_values = eina_list_append(col_values, &(M->msg_state));
		col_values = eina_list_append(col_values, &(M->message_len));
		col_values = eina_list_append(col_values, &(M->media.type));

		char *dummy_val = "";
		if(M->media.type == tgl_message_media_none) {
			col_values = eina_list_append(col_values, (dummy_val));
		} else if(M->media.type == tgl_message_media_photo) {

			char temp_media_id[50];
			sprintf(temp_media_id, "%lld", M->media.photo.id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_document) {

			char temp_media_id[50];
			sprintf(temp_media_id, "%lld", M->media.document.id);
			col_values = eina_list_append(col_values, temp_media_id);

		} else if(M->media.type == tgl_message_media_geo) {
			col_values = eina_list_append(col_values, (dummy_val));
		} else if(M->media.type == tgl_message_media_contact) {

			char temp_media_id[50];
			sprintf(temp_media_id, "%d",M->media.user_id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_unsupported) {
			col_values = eina_list_append(col_values, (dummy_val));
		} else if(M->media.type == tgl_message_media_photo_encr) {

			char temp_media_id[50];
			sprintf(temp_media_id, "%lld",M->media.encr_photo.id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else if(M->media.type == tgl_message_media_document_encr) {

			char temp_media_id[50];
			sprintf(temp_media_id, "%lld",M->media.document.id);

			col_values = eina_list_append(col_values, temp_media_id);
		} else  {
			col_values = eina_list_append(col_values, (dummy_val));
		}

		if (unique_id != -1) {
			int u_id = unique_id;
			col_values = eina_list_append(col_values, &u_id);
		}


		char *where_clause = NULL;

		if (unique_id > 0) {

			char usr_str[50];
			sprintf(usr_str,"%d",unique_id);
			where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_UNIQUE_ID) + strlen(" = ") + strlen(usr_str) + 1);
			strcpy(where_clause, MESSAGE_INFO_TABLE_UNIQUE_ID);
			strcat(where_clause, " = ");
			strcat(where_clause, usr_str);

		} else {

			char usr_str[50];
			sprintf(usr_str,"%lld", M->id);
			where_clause = (char *)malloc(strlen(MESSAGE_INFO_TABLE_MESSAGE_ID) + strlen(" = ") + strlen(usr_str) + 1);
			strcpy(where_clause, MESSAGE_INFO_TABLE_MESSAGE_ID);
			strcat(where_clause, " = ");
			strcat(where_clause, usr_str);

		}

		Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);

		if(!ret) {
			//("error: database creation failed");
		} else {

		}
		eina_list_free(col_names);
		eina_list_free(col_types);
		eina_list_free(col_values);
}

Eina_List* get_registered_user_info()
{
	Eina_List* user_details = NULL;

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
		col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

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
		col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

		user_details = get_values_from_table_sync(table_name, col_names, col_types, NULL);

		eina_list_free(col_names);
		eina_list_free(col_types);
	return user_details;
}

Eina_Bool is_chat_id_already_exists(struct tgl_chat *chat_info)
{
	// get chat name chat id from chat_info_table

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

	Eina_List* vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

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

	return EINA_FALSE;
}

void init_insert_buddy_into_db(char* table_name, struct tgl_user* U)
{
	if(!U) {
		return;
	}
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_USER_ID);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PRINT_NAME);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_STRUCTURE_VERSION);
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
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_BLOCKED);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, &(U->id.id));
	if(U->print_name)
		col_values = eina_list_append(col_values, U->print_name);
	else
		col_values = eina_list_append(col_values, "");

	col_values = eina_list_append(col_values, &(U->structure_version));
	col_values = eina_list_append(col_values, &(U->photo_id));

	if(U->first_name)
		col_values = eina_list_append(col_values, U->first_name);
	else
		col_values = eina_list_append(col_values, "");
	if(U->last_name)
		col_values = eina_list_append(col_values, U->last_name);
	else
		col_values = eina_list_append(col_values, "");

	char phone_num[256];
	if(U->phone) {
		if (strstr(U->phone, "+") == NULL) {
			strcpy(phone_num, "+");
			strcat(phone_num, U->phone);
		} else {
			strcpy(phone_num, phone_num);
		}
		col_values = eina_list_append(col_values, phone_num);
	} else {
		col_values = eina_list_append(col_values, "");
	}

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
	col_values = eina_list_append(col_values, &(U->blocked));
	col_values = eina_list_append(col_values, &(U->is_unknown));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		// already exist. So update the table
		char* where_clause = NULL;
		char user_id_str[50];
		sprintf(user_id_str,"%d",U->id.id);
		where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(user_id_str) + 1);
		strcpy(where_clause, USER_INFO_TABLE_USER_ID);
		strcat(where_clause, " = ");
		strcat(where_clause, user_id_str);
		ret = update_table(table_name, col_names, col_types, col_values, where_clause);
	} else {
		// successfully inserted.
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

void update_buddy_into_db(char* table_name, struct tgl_user* U)
{
	if(!U) {
		return;
	}

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_USER_ID);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PRINT_NAME);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_STRUCTURE_VERSION);
	//col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);
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
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_BLOCKED);
	//col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	//col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	//col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, &(U->id.id));
	if(U->print_name)
		col_values = eina_list_append(col_values, U->print_name);
	else
		col_values = eina_list_append(col_values, "");

	col_values = eina_list_append(col_values, &(U->structure_version));
	//col_values = eina_list_append(col_values, "");
	col_values = eina_list_append(col_values, &(U->photo_id));

	if(U->first_name)
		col_values = eina_list_append(col_values, U->first_name);
	else
		col_values = eina_list_append(col_values, "");
	if(U->last_name)
		col_values = eina_list_append(col_values, U->last_name);
	else
		col_values = eina_list_append(col_values, "");

	char phone_num[256];
	if(U->phone) {
		if (strstr(U->phone, "+") == NULL) {
			strcpy(phone_num, "+");
			strcat(phone_num, U->phone);
		} else {
			strcpy(phone_num, phone_num);
		}
		col_values = eina_list_append(col_values, phone_num);
	} else {
		col_values = eina_list_append(col_values, "");
	}

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
	col_values = eina_list_append(col_values, &(U->blocked));
	//col_values = eina_list_append(col_values, &(U->is_unknown));

#if 0
	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
#endif
		// already exist. So update the table
		char* where_clause = NULL;
		char user_id_str[50];
		sprintf(user_id_str,"%d",U->id.id);
		where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(user_id_str) + 1);
		strcpy(where_clause, USER_INFO_TABLE_USER_ID);
		strcat(where_clause, " = ");
		strcat(where_clause, user_id_str);
		Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);
#if 0
	} else {
		// successfully inserted.
	}
#endif
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

void insert_chat_info_to_db(struct tgl_chat *chat_info, char* photo_path)
{
	if (!chat_info) {
		return;
	}
	char* table_name = CHAT_INFO_TABLE_NAME;
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
		col_values = eina_list_append(col_values, "");
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

	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		// already exist. So update the table
		char* where_clause = NULL;
		char chat_id_str[50];
		sprintf(chat_id_str,"%d", chat_info->id.id);
		where_clause = (char*)malloc(strlen(CHAT_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(chat_id_str) + 1);
		strcpy(where_clause, CHAT_INFO_TABLE_CHAT_ID);
		strcat(where_clause, " = ");
		strcat(where_clause, chat_id_str);
		ret = update_table(table_name, col_names, col_types, col_values, where_clause);
	} else {

	}
	free(full_ids);
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

Eina_Bool update_chat_info_to_db(struct tgl_chat *chat_info, char* photo_path)
{
	if (!chat_info || !photo_path) {
		return EINA_FALSE;
	}

#if 0
	char* table_name = CHAT_INFO_TABLE_NAME;
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

	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);

	if(!ret) {
		// error handling
	} else {

	}

	free(full_ids);
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
#else
	char* table_name = CHAT_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PHOTO_PATH);
	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, photo_path);


	char chat_id_str[50];
	sprintf(chat_id_str,"%d",chat_info->id.id);
	char* where_clause = (char*)malloc(strlen(CHAT_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(chat_id_str) + 1);
	strcpy(where_clause, CHAT_INFO_TABLE_CHAT_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, chat_id_str);

	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);


	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
	free(where_clause);
	if(!ret) {
		return EINA_FALSE;
	}
	return EINA_TRUE;

#endif
}

void update_buddy_pic_db(char* file_path, char* table_name, int id)
{
	if (!file_path || !table_name) {
		return;
	}

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

	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);

	if(!ret) {
		// error handling
	} else {

	}
	free(where_clause);
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

void update_buddy_block_db(char* table_name, int id, int block)
{
	if (!table_name) {
		return;
	}

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_BLOCKED);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, &block);

	char* where_clause = NULL;

	char usr_str[50];
	sprintf(usr_str,"%d",id);
	where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(usr_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, usr_str);

	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);

	if(!ret) {
		// error handling
	} else {

	}
	free(where_clause);
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

void update_buddy_delete_db(char* table_name, int id, int delete_item)
{
	if (!table_name) {
		return;
	}

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_DELETED);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, &delete_item);

	char* where_clause = NULL;

	char usr_str[50];
	sprintf(usr_str,"%d",id);
	where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(usr_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, usr_str);

	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);

	if(!ret) {
		// error handling
	} else {

	}
	free(where_clause);
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}


Eina_List* get_buddy_info(int buddy_id)
{
	Eina_List* user_details = NULL;

	char* table_name = BUDDY_INFO_TABLE_NAME;
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
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(buddy_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, buddy_id_str);

	user_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);

	return user_details;
}

void update_receive_media_info_in_db(long long media_id, char* file_path)
{
	if(!file_path) {
		return;
	}
	char* table_name = MEDIA_INFO_TABLE_NAME;
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

	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);

	if(!ret) {
		// error handling
	} else {

	}
	free(where_clause);
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

void insert_media_info_to_db(struct tgl_message *M, char* file_path)
{
	if(!M) {
		return;
	}

	char* table_name = MEDIA_INFO_TABLE_NAME;


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

	/****************************NEW****************************************/

	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MIME_TYPE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_TYPE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_WIDTH);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_HEIGHT);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_DURATION);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_SIZE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_DC);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_THUMB_FILE);

	/****************************NEW****************************************/

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

	/****************************NEW****************************************/

	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	/****************************NEW****************************************/

	Eina_List* col_values = NULL;

	int media_type = M->media.type;
	char access_hash_str[256] = {'\0'};
	char photo_id_str[256] = {'\0'};
	char doc_id_str[256] = {'\0'};
	if (media_type == tgl_message_media_photo) {

		sprintf(photo_id_str, "%lld", M->media.photo.id);

		col_values = eina_list_append(col_values, photo_id_str);
		col_values = eina_list_append(col_values, &(media_type));



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


		sprintf(doc_id_str, "%lld", M->media.document.id);

		col_values = eina_list_append(col_values, doc_id_str);
		col_values = eina_list_append(col_values, &(media_type));



		sprintf(access_hash_str, "%lld", M->media.document.access_hash);

		col_values = eina_list_append(col_values, access_hash_str);

		col_values = eina_list_append(col_values, &(M->media.document.user_id));
		col_values = eina_list_append(col_values, &(M->media.document.date));

		if(M->media.document.caption)
			col_values = eina_list_append(col_values, M->media.document.caption);
		else
			col_values = eina_list_append(col_values, "");


		double longitude = M->media.geo.longitude;
		double latitude =  M->media.geo.latitude;

		char long_str[50];
		sprintf(long_str,"%lf",longitude);

		char lat_str[50];
		sprintf(lat_str,"%lf",latitude);

		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, &(M->media.document.size));

		char* photo_type = M->media.document.thumb.type;
		if(photo_type) {
			col_values = eina_list_append(col_values, photo_type);
		} else {
			col_values = eina_list_append(col_values, "");
		}

		int photo_loc_dc = M->media.document.thumb.loc.dc;
		col_values = eina_list_append(col_values, &photo_loc_dc);



		char photo_loc_vol_str[50];
		sprintf(photo_loc_vol_str, "%lld", M->media.document.thumb.loc.volume);

		col_values = eina_list_append(col_values, photo_loc_vol_str);

		int photo_loc_id = M->media.document.thumb.loc.local_id;
		col_values = eina_list_append(col_values, &photo_loc_id);


		char photo_loc_sec_str[50];
		sprintf(photo_loc_sec_str, "%lld", M->media.document.thumb.loc.secret);

		col_values = eina_list_append(col_values, photo_loc_sec_str);

		int photo_width = M->media.document.thumb.w;
		col_values = eina_list_append(col_values, &photo_width);

		int photo_height = M->media.document.thumb.h;
		col_values = eina_list_append(col_values, &photo_height);

		int pic_size = M->media.document.thumb.size;
		col_values = eina_list_append(col_values, &pic_size);

		char* photo_data = M->media.document.thumb.data;
		if (photo_data) {
			col_values = eina_list_append(col_values, photo_data);
		} else {
			col_values = eina_list_append(col_values, "");
		}


		for (int j = 1; j < 4; j++) {

			char* photo_type = "";
			col_values = eina_list_append(col_values, photo_type);

			int photo_loc_dc = -1;
			col_values = eina_list_append(col_values, &photo_loc_dc);

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
	} else if (media_type == tgl_message_media_geo) {
			// To be checked
			int dummy = 0;
			//col_values = eina_list_append(col_values, &(dummy));
			char doc_id_str[256];
			snprintf(doc_id_str, sizeof(doc_id_str), "%lld", M->media.document.id);
			col_values = eina_list_append(col_values, doc_id_str);
			col_values = eina_list_append(col_values, &(media_type));
			col_values = eina_list_append(col_values, &(dummy));
			col_values = eina_list_append(col_values, &(dummy));
			col_values = eina_list_append(col_values, &(dummy));

			col_values = eina_list_append(col_values, "");


			char long_str[50];
			sprintf(long_str,"%2.15f",M->media.geo.longitude);

			char lat_str[50];
			sprintf(lat_str,"%2.15f",M->media.geo.latitude);

			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, long_str);
			col_values = eina_list_append(col_values, &(dummy));

			for (int j = 0; j < 4; j++) {

				char* photo_type = strdup(" ");
				int *photo_loc_dc = malloc(sizeof(*photo_loc_dc));
				int *photo_loc_vol = malloc(sizeof(*photo_loc_vol));
				int *photo_loc_id = malloc(sizeof(*photo_loc_id));
				int *photo_width = malloc(sizeof(*photo_width));
				int *photo_height = malloc(sizeof(*photo_height));
				int *photo_size = malloc(sizeof(*photo_size));
				char* photo_data = strdup(" ");

				*photo_loc_dc = -1;
				*photo_loc_vol = -1;
				*photo_loc_id = -1;
				*photo_width = -1;
				*photo_height = -1;
				*photo_size = -1;

				col_values = eina_list_append(col_values, photo_type);
				col_values = eina_list_append(col_values, photo_loc_dc);
				col_values = eina_list_append(col_values, strdup(" "));
				col_values = eina_list_append(col_values, photo_loc_id);
				col_values = eina_list_append(col_values, strdup(" "));
				col_values = eina_list_append(col_values, photo_width);
				col_values = eina_list_append(col_values, photo_height);
				col_values = eina_list_append(col_values, photo_size);
				col_values = eina_list_append(col_values, photo_data);
			}
	} else {
		// To be checked
		int dummy = 0;
		//col_values = eina_list_append(col_values, &(dummy));
		char default_id_str[256];
		int default_id = time(NULL);
		snprintf(default_id_str, sizeof(default_id_str), "%d", default_id);
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

			char* photo_type = strdup(" ");
			int *photo_loc_dc = malloc(sizeof(*photo_loc_dc));
			int *photo_loc_vol = malloc(sizeof(*photo_loc_vol));
			int *photo_loc_id = malloc(sizeof(*photo_loc_id));
			int *photo_width = malloc(sizeof(*photo_width));
			int *photo_height = malloc(sizeof(*photo_height));
			int *photo_size = malloc(sizeof(*photo_size));
			char* photo_data = strdup(" ");

			*photo_loc_dc = -1;
			*photo_loc_vol = -1;
			*photo_loc_id = -1;
			*photo_width = -1;
			*photo_height = -1;
			*photo_size = -1;

			col_values = eina_list_append(col_values, photo_type);
			col_values = eina_list_append(col_values, photo_loc_dc);
			col_values = eina_list_append(col_values, strdup(" "));
			col_values = eina_list_append(col_values, photo_loc_id);
			col_values = eina_list_append(col_values, strdup(" "));
			col_values = eina_list_append(col_values, photo_width);
			col_values = eina_list_append(col_values, photo_height);
			col_values = eina_list_append(col_values, photo_size);
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

	if (M->media.type == tgl_message_media_document) {
		if (M->media.document.mime_type) {
			col_values = eina_list_append(col_values, M->media.document.mime_type);
		} else {
			col_values = eina_list_append(col_values, "");
		}

		char * doc_type = NULL;
		if (M->media.document.flags & FLAG_DOCUMENT_IMAGE) {
			doc_type = "image";
		} else if (M->media.document.flags & FLAG_DOCUMENT_AUDIO) {
			doc_type = "audio";
		} else if (M->media.document.flags & FLAG_DOCUMENT_VIDEO) {
			doc_type = "video";
		} else if (M->media.document.flags & FLAG_DOCUMENT_STICKER) {
			doc_type = "sticker";
		} else {
			doc_type = "document";
		}
		col_values = eina_list_append(col_values, doc_type);

		int doc_width = M->media.document.w;
		col_values = eina_list_append(col_values, &doc_width);

		int doc_height = M->media.document.h;
		col_values = eina_list_append(col_values, &doc_height);

		int doc_duration = M->media.document.duration;
		col_values = eina_list_append(col_values, &doc_duration);

		int doc_size = M->media.document.size;
		col_values = eina_list_append(col_values, &doc_size);

		int doc_dc = M->media.document.dc_id;
		col_values = eina_list_append(col_values, &doc_dc);

	} else 	if (M->media.type == tgl_message_media_document_encr) {
		if (M->media.encr_document.mime_type) {
			col_values = eina_list_append(col_values, M->media.encr_document.mime_type);
		} else {
			col_values = eina_list_append(col_values, "");
		}

		char * doc_type = NULL;
		if (M->media.encr_document.flags & FLAG_DOCUMENT_IMAGE) {
			doc_type = "image";
		} else if (M->media.encr_document.flags & FLAG_DOCUMENT_AUDIO) {
			doc_type = "audio";
		} else if (M->media.encr_document.flags & FLAG_DOCUMENT_VIDEO) {
			doc_type = "video";
		} else if (M->media.encr_document.flags & FLAG_DOCUMENT_STICKER) {
			doc_type = "sticker";
		} else {
			doc_type = "document";
		}
		col_values = eina_list_append(col_values, doc_type);

		int doc_width = M->media.encr_document.w;
		col_values = eina_list_append(col_values, &doc_width);

		int doc_height = M->media.encr_document.h;
		col_values = eina_list_append(col_values, &doc_height);

		int doc_duration = M->media.encr_document.duration;
		col_values = eina_list_append(col_values, &doc_duration);

		int doc_size = M->media.encr_document.size;
		col_values = eina_list_append(col_values, &doc_size);

		int doc_dc = M->media.encr_document.dc_id;
		col_values = eina_list_append(col_values, &doc_dc);

	} else {

		col_values = eina_list_append(col_values, "");

		if (M->media.type == tgl_message_media_photo) {
			char * doc_type = "image";
			col_values = eina_list_append(col_values, doc_type);
		} else {
			char * doc_type = "none";
			col_values = eina_list_append(col_values, doc_type);
		}

		int doc_width = 0;
		col_values = eina_list_append(col_values, &doc_width);

		int doc_height = 0;
		col_values = eina_list_append(col_values, &doc_height);

		int doc_duration = 0;
		col_values = eina_list_append(col_values, &doc_duration);

		int doc_size = 0;
		col_values = eina_list_append(col_values, &doc_size);

		int doc_dc = 0;
		col_values = eina_list_append(col_values, &doc_dc);
	}

	col_values = eina_list_append(col_values, "");

	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		//("error: database creation failed");
	} else {

	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

void update_video_thumb_in_db(long long media_id, char* thumb_file)
{
	if (!thumb_file) {
		return;
	}
	char* table_name = MEDIA_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_THUMB_FILE);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, thumb_file);

	char usr_str[50];
	sprintf(usr_str,"%lld",media_id);
	char *where_clause = (char*)malloc(strlen(MEDIA_INFO_TABLE_MEDIA_ID) + strlen(" = '") + strlen(usr_str) + strlen("'") + 1);
	strcpy(where_clause, MEDIA_INFO_TABLE_MEDIA_ID);
	strcat(where_clause, " = '");
	strcat(where_clause, usr_str);
	strcat(where_clause, "'");

	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);

	if(!ret) {
		//("error: database creation failed");
	} else {

	}
	free(where_clause);
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

void update_sent_media_info_in_db(struct tgl_message *M, long long unique_val)
{
	if(!M) {
		return;
	}

	char* table_name = MEDIA_INFO_TABLE_NAME;


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

	/****************************NEW****************************************/

	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MIME_TYPE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_TYPE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_WIDTH);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_HEIGHT);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_DURATION);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_SIZE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_DC);
	//col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_THUMB_FILE);

	/****************************NEW****************************************/

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

	/****************************NEW****************************************/

	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	//col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	/****************************NEW****************************************/


	Eina_List* col_values = NULL;

	int media_type = M->media.type;

	if (media_type == tgl_message_media_photo) {

		char photo_id_str[256];
		sprintf(photo_id_str, "%lld", M->media.photo.id);

		col_values = eina_list_append(col_values, photo_id_str);
		col_values = eina_list_append(col_values, &(media_type));


		char access_hash_str[256];
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

		if (M->media.photo.sizes_num > 4) {
			M->media.photo.sizes_num = 4;
		}

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

		char doc_id_str[256];
		sprintf(doc_id_str, "%lld", M->media.document.id);

		col_values = eina_list_append(col_values, doc_id_str);
		col_values = eina_list_append(col_values, &(media_type));

		char access_hash_str[256];
		sprintf(access_hash_str, "%lld", M->media.document.access_hash);

		col_values = eina_list_append(col_values, access_hash_str);
		col_values = eina_list_append(col_values, &(M->media.document.user_id));
		col_values = eina_list_append(col_values, &(M->media.document.date));

		if(M->media.document.caption)
			col_values = eina_list_append(col_values, M->media.document.caption);
		else
			col_values = eina_list_append(col_values, "");


		double longitude = M->media.geo.longitude;
		double latitude =  M->media.geo.latitude;

		char long_str[50];
		sprintf(long_str,"%lf",longitude);

		char lat_str[50];
		sprintf(lat_str,"%lf",latitude);

		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, &(M->media.document.size));

		char* photo_type = M->media.document.thumb.type;
		if(photo_type) {
			col_values = eina_list_append(col_values, photo_type);
		} else {
			col_values = eina_list_append(col_values, "");
		}

		int photo_loc_dc = M->media.document.thumb.loc.dc;
		col_values = eina_list_append(col_values, &photo_loc_dc);



		char photo_loc_vol_str[50];
		sprintf(photo_loc_vol_str, "%lld", M->media.document.thumb.loc.volume);

		col_values = eina_list_append(col_values, photo_loc_vol_str);

		int photo_loc_id = M->media.document.thumb.loc.local_id;
		col_values = eina_list_append(col_values, &photo_loc_id);


		char photo_loc_sec_str[50];
		sprintf(photo_loc_sec_str, "%lld", M->media.document.thumb.loc.secret);

		col_values = eina_list_append(col_values, photo_loc_sec_str);

		int photo_width = M->media.document.thumb.w;
		col_values = eina_list_append(col_values, &photo_width);

		int photo_height = M->media.document.thumb.h;
		col_values = eina_list_append(col_values, &photo_height);

		int pic_size = M->media.document.thumb.size;
		col_values = eina_list_append(col_values, &pic_size);

		char* photo_data = M->media.document.thumb.data;
		if (photo_data) {
			col_values = eina_list_append(col_values, photo_data);
		} else {
			col_values = eina_list_append(col_values, "");
		}


		for (int j = 1; j < 4; j++) {

			char* photo_type = "";
			col_values = eina_list_append(col_values, photo_type);

			int photo_loc_dc = -1;
			col_values = eina_list_append(col_values, &photo_loc_dc);

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

			char* photo_type = strdup(" ");
			int *photo_loc_dc = malloc(sizeof(*photo_loc_dc));
			int *photo_loc_vol = malloc(sizeof(*photo_loc_vol));
			int *photo_loc_id = malloc(sizeof(*photo_loc_id));
			int *photo_width = malloc(sizeof(*photo_width));
			int *photo_height = malloc(sizeof(*photo_height));
			int *photo_size = malloc(sizeof(*photo_size));
			char* photo_data = strdup(" ");

			*photo_loc_dc = -1;
			*photo_loc_vol = -1;
			*photo_loc_id = -1;
			*photo_width = -1;
			*photo_height = -1;
			*photo_size = -1;

			col_values = eina_list_append(col_values, photo_type);
			col_values = eina_list_append(col_values, photo_loc_dc);
			col_values = eina_list_append(col_values, strdup(" "));
			col_values = eina_list_append(col_values, photo_loc_id);
			col_values = eina_list_append(col_values, strdup(" "));
			col_values = eina_list_append(col_values, photo_width);
			col_values = eina_list_append(col_values, photo_height);
			col_values = eina_list_append(col_values, photo_size);
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


	if (M->media.type == tgl_message_media_document) {
		if (M->media.document.mime_type) {
			col_values = eina_list_append(col_values, M->media.document.mime_type);
		} else {
			col_values = eina_list_append(col_values, "");
		}

		char * doc_type = NULL;
		if (M->media.document.flags & FLAG_DOCUMENT_IMAGE) {
			doc_type = "image";
		} else if (M->media.document.flags & FLAG_DOCUMENT_AUDIO) {
			doc_type = "audio";
		} else if (M->media.document.flags & FLAG_DOCUMENT_VIDEO) {
			doc_type = "video";
		} else if (M->media.document.flags & FLAG_DOCUMENT_STICKER) {
			doc_type = "sticker";
		} else {
			doc_type = "document";
		}
		col_values = eina_list_append(col_values, doc_type);

		int doc_width = M->media.document.w;
		col_values = eina_list_append(col_values, &doc_width);

		int doc_height = M->media.document.h;
		col_values = eina_list_append(col_values, &doc_height);

		int doc_duration = M->media.document.duration;
		col_values = eina_list_append(col_values, &doc_duration);

		int doc_size = M->media.document.size;
		col_values = eina_list_append(col_values, &doc_size);

		int doc_dc = M->media.document.dc_id;
		col_values = eina_list_append(col_values, &doc_dc);

	} else 	if (M->media.type == tgl_message_media_document_encr) {
		if (M->media.encr_document.mime_type) {
			col_values = eina_list_append(col_values, M->media.encr_document.mime_type);
		} else {
			col_values = eina_list_append(col_values, "");
		}

		char * doc_type = NULL;
		if (M->media.encr_document.flags & FLAG_DOCUMENT_IMAGE) {
			doc_type = "image";
		} else if (M->media.encr_document.flags & FLAG_DOCUMENT_AUDIO) {
			doc_type = "audio";
		} else if (M->media.encr_document.flags & FLAG_DOCUMENT_VIDEO) {
			doc_type = "video";
		} else if (M->media.encr_document.flags & FLAG_DOCUMENT_STICKER) {
			doc_type = "sticker";
		} else {
			doc_type = "document";
		}
		col_values = eina_list_append(col_values, doc_type);

		int doc_width = M->media.encr_document.w;
		col_values = eina_list_append(col_values, &doc_width);

		int doc_height = M->media.encr_document.h;
		col_values = eina_list_append(col_values, &doc_height);

		int doc_duration = M->media.encr_document.duration;
		col_values = eina_list_append(col_values, &doc_duration);

		int doc_size = M->media.encr_document.size;
		col_values = eina_list_append(col_values, &doc_size);

		int doc_dc = M->media.encr_document.dc_id;
		col_values = eina_list_append(col_values, &doc_dc);

	} else {

		col_values = eina_list_append(col_values, "");

		if (M->media.type == tgl_message_media_photo) {
			char * doc_type = "image";
			col_values = eina_list_append(col_values, doc_type);
		} else {
			char * doc_type = "none";
			col_values = eina_list_append(col_values, doc_type);
		}

		int doc_width = 0;
		col_values = eina_list_append(col_values, &doc_width);

		int doc_height = 0;
		col_values = eina_list_append(col_values, &doc_height);

		int doc_duration = 0;
		col_values = eina_list_append(col_values, &doc_duration);

		int doc_size = 0;
		col_values = eina_list_append(col_values, &doc_size);

		int doc_dc = M->media.encr_document.dc_id;
		col_values = eina_list_append(col_values, &doc_dc);
	}

	//col_values = eina_list_append(col_values, "");

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

	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);

	if(!ret) {
		//("error: database creation failed");
	} else {

	}
	free(where_clause);
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

struct tgl_media* get_media_details_from_db(long long media_id)
{
	Eina_List* img_details = get_image_details_from_db(media_id);

	if (!img_details) {
		return NULL;
	}

	struct tgl_media* media_info = (struct tgl_media*)malloc(sizeof(struct tgl_media));

	Eina_List* row_vals = eina_list_nth(img_details, 0);

	char *temp_media_id = (char *)eina_list_nth(row_vals, 0);

	if(temp_media_id) {
		media_info->media_id = atoll(temp_media_id);
		free(temp_media_id);
	} else {
		media_info->media_id = 0;
	}

	int* temp_media_type = (int*)eina_list_nth(row_vals, 1);

	if(temp_media_type) {
		media_info->media_type = *temp_media_type;
		free(temp_media_type);
	} else {
		media_info->media_type = -1;
	}

	char *temp_access_hash = (char *)eina_list_nth(row_vals, 2);

	if(temp_access_hash) {
		media_info->access_hash = atoll(temp_access_hash);
		free(temp_access_hash);
	} else {
		media_info->access_hash = 0;
	}

	int* temp_user_id = (int*)eina_list_nth(row_vals, 3);

	if(temp_user_id) {
		media_info->user_id = *temp_user_id;
		free(temp_user_id);
	} else {
		media_info->user_id = 0;
	}

	int* temp_date = (int*)eina_list_nth(row_vals, 4);

	if(temp_date) {
		media_info->date = *temp_date;
		free(temp_date);
	} else {
		media_info->date = 0;
	}

	char *temp_caption = (char *)eina_list_nth(row_vals, 5);

	if(temp_caption) {
		media_info->caption = strdup(temp_caption);
		free(temp_caption);
	}

	char *temp_longitude = (char *)eina_list_nth(row_vals, 6);

	if(temp_longitude) {
		media_info->longitude = strdup(temp_longitude);
		free(temp_longitude);
	} else {
		media_info->longitude = 0;
	}

	char *temp_latitude = (char *)eina_list_nth(row_vals, 7);

	if(temp_latitude) {
		media_info->latitude = strdup(temp_latitude);
		free(temp_latitude);
	} else {
		media_info->latitude = 0;
	}

	int* temp_sizes = (int*)eina_list_nth(row_vals, 8);

	if(temp_sizes) {
		media_info->sizes = *temp_sizes;
		free(temp_sizes);
	} else {
		media_info->sizes = 0;
	}

	/***************************************************************/

	char *temp_photo_type1 = (char *)eina_list_nth(row_vals, 9);
	if (temp_photo_type1 && strlen(temp_photo_type1) > 0) {
		media_info->photo_type1 =strdup(temp_photo_type1);
		free(temp_photo_type1);
	} else {
		media_info->photo_type1 = 0;
	}


	int* temp_photo_loc_dc1 = (int*)eina_list_nth(row_vals, 10);
	if (temp_photo_loc_dc1) {
		media_info->photo_loc_dc1 = *temp_photo_loc_dc1;
		free(temp_photo_loc_dc1);
	} else {
		media_info->photo_loc_dc1 = 0;
	}


	char *temp_photo_loc_vol1 = (char *)eina_list_nth(row_vals, 11);
	if(temp_photo_loc_vol1 && strlen(temp_photo_loc_vol1) > 0) {
		media_info->photo_loc_vol1 = atoll(temp_photo_loc_vol1);
		free(temp_photo_loc_vol1);
	} else {
		media_info->photo_loc_vol1 = 0;
	}


	int* temp_photo_loc_id1 = (int*)eina_list_nth(row_vals, 12);
	if (temp_photo_loc_id1) {
		media_info->photo_loc_id1 = *temp_photo_loc_id1;
		free(temp_photo_loc_id1);
	} else {
		media_info->photo_loc_id1 = 0;
	}

	char *temp_photo_loc_sec1 = (char *)eina_list_nth(row_vals, 13);
	if(temp_photo_loc_sec1 && strlen(temp_photo_loc_sec1) > 0) {
		media_info->photo_loc_sec1 = atoll(temp_photo_loc_sec1);
		free(temp_photo_loc_sec1);
	} else {
		media_info->photo_loc_sec1 = 0;
	}


	int* temp_photo_width1 = (int*)eina_list_nth(row_vals, 14);
	if(temp_photo_width1) {
		media_info->photo_width1 = *temp_photo_width1;
		free(temp_photo_width1);
	} else {
		media_info->photo_width1 = 0;
	}


	int* temp_photo_height1 = (int*)eina_list_nth(row_vals, 15);
	if(temp_photo_height1) {
		media_info->photo_height1 = *temp_photo_height1;
		free(temp_photo_height1);
	} else {
		media_info->photo_height1 = 0;
	}

	int* temp_photo_size1 = (int*)eina_list_nth(row_vals, 16);
	if(temp_photo_size1) {
		media_info->photo_size1 = *temp_photo_size1;
		free(temp_photo_size1);
	} else {
		media_info->photo_size1 = 0;
	}


	char *temp_photo_data1 = (char *)eina_list_nth(row_vals, 17);
	if(temp_photo_data1 && strlen(temp_photo_data1) > 0) {
		media_info->photo_data1 = strdup(temp_photo_data1);
		free(temp_photo_data1);
	} else {
		media_info->photo_data1 = 0;
	}


	char *temp_photo_type2 = (char *)eina_list_nth(row_vals, 18);
	if (temp_photo_type2 && strlen(temp_photo_type2) > 0) {
		media_info->photo_type2 =strdup(temp_photo_type2);
		free(temp_photo_type2);
	} else {
		media_info->photo_type2 = 0;
	}


	int* temp_photo_loc_dc2 = (int*)eina_list_nth(row_vals, 19);
	if (temp_photo_loc_dc2) {
		media_info->photo_loc_dc2 = *temp_photo_loc_dc2;
		free(temp_photo_loc_dc2);
	} else {
		media_info->photo_loc_dc2 = 0;
	}


	char *temp_photo_loc_vol2 = (char *)eina_list_nth(row_vals, 20);
	if(temp_photo_loc_vol2 && strlen(temp_photo_loc_vol2) > 0) {
		media_info->photo_loc_vol2 = atoll(temp_photo_loc_vol2);
		free(temp_photo_loc_vol2);
	} else {
		media_info->photo_loc_vol2 = 0;
	}


	int* temp_photo_loc_id2 = (int*)eina_list_nth(row_vals, 21);
	if (temp_photo_loc_id2) {
		media_info->photo_loc_id2 = *temp_photo_loc_id2;
		free(temp_photo_loc_id2);
	} else {
		media_info->photo_loc_id2 = 0;
	}

	char *temp_photo_loc_sec2 = (char *)eina_list_nth(row_vals, 22);
	if(temp_photo_loc_sec2 && strlen(temp_photo_loc_sec2) > 0) {
		media_info->photo_loc_sec2 = atoll(temp_photo_loc_sec2);
		free(temp_photo_loc_sec2);
	} else {
		media_info->photo_loc_sec2 = 0;
	}


	int* temp_photo_width2 = (int*)eina_list_nth(row_vals, 23);
	if(temp_photo_width2) {
		media_info->photo_width2 = *temp_photo_width2;
		free(temp_photo_width2);
	} else {
		media_info->photo_width2 = 0;
	}


	int* temp_photo_height2 = (int*)eina_list_nth(row_vals, 24);
	if(temp_photo_height2) {
		media_info->photo_height2 = *temp_photo_height2;
		free(temp_photo_height2);
	} else {
		media_info->photo_height2 = 0;
	}

	int* temp_photo_size2 = (int*)eina_list_nth(row_vals, 25);
	if(temp_photo_size2) {
		media_info->photo_size2 = *temp_photo_size2;
		free(temp_photo_size2);
	} else {
		media_info->photo_size2 = 0;
	}


	char *temp_photo_data2 = (char *)eina_list_nth(row_vals, 26);
	if(temp_photo_data2 && strlen(temp_photo_data2) > 0) {
		media_info->photo_data2 = strdup(temp_photo_data2);
		free(temp_photo_data2);
	} else {
		media_info->photo_data2 = 0;
	}

	char *temp_photo_type3 = (char *)eina_list_nth(row_vals, 27);
	if (temp_photo_type3 && strlen(temp_photo_type3) > 0) {
		media_info->photo_type3 =strdup(temp_photo_type3);
		free(temp_photo_type3);
	} else {
		media_info->photo_type3 = 0;
	}


	int* temp_photo_loc_dc3 = (int*)eina_list_nth(row_vals, 28);
	if (temp_photo_loc_dc3) {
		media_info->photo_loc_dc3 = *temp_photo_loc_dc3;
		free(temp_photo_loc_dc3);
	} else {
		media_info->photo_loc_dc3 = 0;
	}


	char *temp_photo_loc_vol3 = (char *)eina_list_nth(row_vals, 29);
	if(temp_photo_loc_vol3 && strlen(temp_photo_loc_vol3) > 0) {
		media_info->photo_loc_vol3 = atoll(temp_photo_loc_vol3);
		free(temp_photo_loc_vol3);
	} else {
		media_info->photo_loc_vol3 = 0;
	}


	int* temp_photo_loc_id3 = (int*)eina_list_nth(row_vals, 30);
	if (temp_photo_loc_id3) {
		media_info->photo_loc_id3 = *temp_photo_loc_id3;
		free(temp_photo_loc_id3);
	} else {
		media_info->photo_loc_id3 = 0;
	}

	char *temp_photo_loc_sec3 = (char *)eina_list_nth(row_vals, 31);
	if(temp_photo_loc_sec3 && strlen(temp_photo_loc_sec3) > 0) {
		media_info->photo_loc_sec3 = atoll(temp_photo_loc_sec3);
		free(temp_photo_loc_sec3);
	} else {
		media_info->photo_loc_sec3 = 0;
	}


	int* temp_photo_width3 = (int*)eina_list_nth(row_vals, 32);
	if(temp_photo_width3) {
		media_info->photo_width3 = *temp_photo_width3;
		free(temp_photo_width3);
	} else {
		media_info->photo_width3 = 0;
	}


	int* temp_photo_height3 = (int*)eina_list_nth(row_vals, 33);
	if(temp_photo_height3) {
		media_info->photo_height3 = *temp_photo_height3;
		free(temp_photo_height3);
	} else {
		media_info->photo_height3 = 0;
	}

	int* temp_photo_size3 = (int*)eina_list_nth(row_vals, 34);
	if(temp_photo_size3) {
		media_info->photo_size3 = *temp_photo_size3;
		free(temp_photo_size3);
	} else {
		media_info->photo_size3 = 0;
	}


	char *temp_photo_data3 = (char *)eina_list_nth(row_vals, 35);
	if(temp_photo_data3 && strlen(temp_photo_data3) > 0) {
		media_info->photo_data3 = strdup(temp_photo_data3);
		free(temp_photo_data3);
	} else {
		media_info->photo_data3 = 0;
	}

	char *temp_photo_type4 = (char *)eina_list_nth(row_vals, 36);
	if (temp_photo_type4 && strlen(temp_photo_type4) > 0) {
		media_info->photo_type4 =strdup(temp_photo_type4);
		free(temp_photo_type4);
	} else {
		media_info->photo_type4 = 0;
	}


	int* temp_photo_loc_dc4 = (int*)eina_list_nth(row_vals, 37);
	if (temp_photo_loc_dc4) {
		media_info->photo_loc_dc4 = *temp_photo_loc_dc4;
		free(temp_photo_loc_dc4);
	} else {
		media_info->photo_loc_dc4 = 0;
	}


	char *temp_photo_loc_vol4 = (char *)eina_list_nth(row_vals, 38);
	if(temp_photo_loc_vol4 && strlen(temp_photo_loc_vol4) > 0) {
		media_info->photo_loc_vol4 = atoll(temp_photo_loc_vol4);
		free(temp_photo_loc_vol4);
	} else {
		media_info->photo_loc_vol4 = 0;
	}


	int* temp_photo_loc_id4 = (int*)eina_list_nth(row_vals, 39);
	if (temp_photo_loc_id4) {
		media_info->photo_loc_id4 = *temp_photo_loc_id4;
		free(temp_photo_loc_id4);
	} else {
		media_info->photo_loc_id4 = 0;
	}

	char *temp_photo_loc_sec4 = (char *)eina_list_nth(row_vals, 40);
	if(temp_photo_loc_sec4 && strlen(temp_photo_loc_sec4) > 0) {
		media_info->photo_loc_sec4 = atoll(temp_photo_loc_sec4);
		free(temp_photo_loc_sec4);
	} else {
		media_info->photo_loc_sec4 = 0;
	}


	int* temp_photo_width4 = (int*)eina_list_nth(row_vals, 41);
	if(temp_photo_width4) {
		media_info->photo_width4 = *temp_photo_width4;
		free(temp_photo_width4);
	} else {
		media_info->photo_width4 = 0;
	}


	int* temp_photo_height4 = (int*)eina_list_nth(row_vals, 42);
	if(temp_photo_height4) {
		media_info->photo_height4 = *temp_photo_height4;
		free(temp_photo_height4);
	} else {
		media_info->photo_height4 = 0;
	}

	int* temp_photo_size4 = (int*)eina_list_nth(row_vals, 43);
	if(temp_photo_size4) {
		media_info->photo_size4 = *temp_photo_size4;
		free(temp_photo_size4);
	} else {
		media_info->photo_size4 = 0;
	}


	char *temp_photo_data4 = (char *)eina_list_nth(row_vals, 44);
	if(temp_photo_data4 && strlen(temp_photo_data4) > 0) {
		media_info->photo_data4 = strdup(temp_photo_data4);
		free(temp_photo_data4);
	} else {
		media_info->photo_data4 = 0;
	}


	/**************************************************************/

	char *temp_phone_no = (char *)eina_list_nth(row_vals, 45);

	if(temp_phone_no && strlen(temp_phone_no) > 0) {
		media_info->phone_no = strdup(temp_phone_no);
		free(temp_phone_no);
	} else {
		media_info->phone_no = 0;
	}

	char *temp_first_name = (char *)eina_list_nth(row_vals, 46);

	if(temp_first_name && strlen(temp_first_name) > 0) {
		media_info->first_name = strdup(temp_first_name);
		free(temp_first_name);
	} else {
		media_info->first_name = 0;
	}

	char *temp_last_name = (char *)eina_list_nth(row_vals, 47);

	if(temp_last_name && strlen(temp_last_name) > 0) {
		media_info->last_name = strdup(temp_last_name);
		free(temp_last_name);
	} else {
		media_info->last_name = 0;
	}

	char *temp_file_path = (char *)eina_list_nth(row_vals, 48);

	if(temp_file_path && strlen(temp_file_path) > 0) {
		media_info->file_path = strdup(temp_file_path);
		free(temp_file_path);
	} else {
		media_info->file_path = 0;
	}

	char *temp_mime_type = (char *)eina_list_nth(row_vals, 49);

	if(temp_mime_type && strlen(temp_mime_type) > 0) {
		media_info->mime_type = strdup(temp_mime_type);
		free(temp_mime_type);
	} else {
		media_info->mime_type = 0;
	}

	char *temp_doc_type = (char *)eina_list_nth(row_vals, 50);

	if(temp_doc_type && strlen(temp_doc_type) > 0) {
		media_info->doc_type = strdup(temp_doc_type);
		free(temp_doc_type);
	} else {
		media_info->doc_type = 0;
	}

	int* temp_doc_width = (int*)eina_list_nth(row_vals, 51);
	if(temp_doc_width) {
		media_info->doc_width = *temp_doc_width;
		free(temp_doc_width);
	} else {
		media_info->doc_width = 0;
	}

	int* temp_doc_height = (int*)eina_list_nth(row_vals, 52);
	if(temp_doc_height) {
		media_info->doc_height = *temp_doc_height;
		free(temp_doc_height);
	} else {
		media_info->doc_height = 0;
	}

	int* temp_doc_duration = (int*)eina_list_nth(row_vals, 53);
	if(temp_doc_duration) {
		media_info->doc_duration = *temp_doc_duration;
		free(temp_doc_duration);
	} else {
		media_info->doc_duration = 0;
	}

	int* temp_doc_size = (int*)eina_list_nth(row_vals, 54);
	if(temp_doc_size) {
		media_info->doc_size = *temp_doc_size;
		free(temp_doc_size);
	} else {
		media_info->doc_size = 0;
	}

	int* temp_doc_dc = (int*)eina_list_nth(row_vals, 55);
	if(temp_doc_size) {
		media_info->doc_dc = *temp_doc_dc;
		free(temp_doc_dc);
	} else {
		media_info->doc_dc = 0;
	}

	char* temp_doc_thumb_path = (int*)eina_list_nth(row_vals, 56);
	if(temp_doc_thumb_path) {
		media_info->doc_thumb_path = strdup(temp_doc_thumb_path);
		free(temp_doc_thumb_path);
	} else {
		media_info->doc_thumb_path = 0;
	}

	eina_list_free(row_vals);

	return media_info;

}

Eina_List* get_image_details_from_db(long long media_id)
{
	Eina_List* vals = NULL;

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

	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
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

	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_MIME_TYPE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_TYPE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_WIDTH);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_HEIGHT);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_DURATION);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_SIZE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_DC);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_THUMB_FILE);

	vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	eina_list_free(col_types);
	eina_list_free(col_names);

	return vals;
}

void get_contact_details_from_db(long long media_id, char **first_name, char **last_name, char **phone_number)
{
	char* file_path = NULL;
	char* table_name = MEDIA_INFO_TABLE_NAME;

	char usr_str[50];
	sprintf(usr_str, "%lld", media_id);
	char* where_clause = (char *)malloc(strlen(MEDIA_INFO_TABLE_MEDIA_ID) + strlen(" = '") + strlen(usr_str) + strlen("'") + 1);
	strcpy(where_clause, MEDIA_INFO_TABLE_MEDIA_ID);
	strcat(where_clause, " = '");
	strcat(where_clause, usr_str);
	strcat(where_clause, "'");

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FIRST_NAME);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LAST_NAME);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHONE_NO);

	Eina_List* vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	file_path = NULL;

	if (!vals) {
		//("DB error");
		eina_list_free(col_names);
		return;
	} else {
		int row_count = eina_list_count(vals);

		for (int i = 0 ; i < row_count ; i++) {
			Eina_List* row_vals = eina_list_nth(vals, i);
			char *temp_fname = (char*)eina_list_nth(row_vals, 0);
			*first_name = temp_fname;
			char *temp_lname = (char*)eina_list_nth(row_vals, 1);
			*last_name = temp_lname;
			char *temp_pnumber = (char*)eina_list_nth(row_vals, 2);
			*phone_number = temp_pnumber;
			eina_list_free(row_vals);
			break;
		}
		eina_list_free(vals);
	}
	eina_list_free(col_names);
	return;
}

void get_geo_location_from_db(long long media_id, char **latitude, char **longitude)
{
	char* file_path = NULL;
	char* table_name = MEDIA_INFO_TABLE_NAME;

	char usr_str[50];
	sprintf(usr_str, "%lld", media_id);
	char* where_clause = (char *)malloc(strlen(MEDIA_INFO_TABLE_MEDIA_ID) + strlen(" = '") + strlen(usr_str) + strlen("'") + 1);
	strcpy(where_clause, MEDIA_INFO_TABLE_MEDIA_ID);
	strcat(where_clause, " = '");
	strcat(where_clause, usr_str);
	strcat(where_clause, "'");

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LATITUDE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LONGITUDE);

	Eina_List* vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	file_path = NULL;

	if (!vals) {
		//("DB error");
		eina_list_free(col_names);
		return;
	} else {
		int row_count = eina_list_count(vals);

		for (int i = 0 ; i < row_count ; i++) {
			Eina_List* row_vals = eina_list_nth(vals, i);
			char *temp_lat = (char*)eina_list_nth(row_vals, 0);
			*latitude = temp_lat;
			char *temp_long = (char*)eina_list_nth(row_vals, 1);
			*longitude = temp_long;
			eina_list_free(row_vals);
			break;
		}
		eina_list_free(vals);
	}
	eina_list_free(col_names);
	return;
}

char* get_video_thumb_path_from_db(long long media_id)
{
	char* file_path = NULL;
	char* table_name = MEDIA_INFO_TABLE_NAME;

	char usr_str[50];
	sprintf(usr_str, "%lld", media_id);
	char* where_clause = (char *)malloc(strlen(MEDIA_INFO_TABLE_MEDIA_ID) + strlen(" = '") + strlen(usr_str) + strlen("'") + 1);
	strcpy(where_clause, MEDIA_INFO_TABLE_MEDIA_ID);
	strcat(where_clause, " = '");
	strcat(where_clause, usr_str);
	strcat(where_clause, "'");

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_THUMB_FILE);

	Eina_List* vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	file_path = NULL;

	if (!vals) {
		//("DB error");
		eina_list_free(col_names);
		return NULL;
	} else {
		int row_count = eina_list_count(vals);

		for (int i = 0 ; i < row_count ; i++) {
			Eina_List* row_vals = eina_list_nth(vals, i);
			file_path = (char*)eina_list_nth(row_vals, 0);
			eina_list_free(row_vals);
			if (!file_path) {
				//("DB Error");
				eina_list_free(col_names);
				return NULL;
			} else {
				break;
			}
		}
		eina_list_free(vals);
	}

	eina_list_free(col_names);
	return file_path;
}



void get_buddy_contact_details_from_db(int buddy_id, char **first_name, char **last_name, char **phone_number)
{
	char* file_path = NULL;
	char* table_name = BUDDY_INFO_TABLE_NAME;

	char usr_str[50];
	sprintf(usr_str, "%d", buddy_id);
	char* where_clause = (char *)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = '") + strlen(usr_str) + strlen("'") + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = '");
	strcat(where_clause, usr_str);
	strcat(where_clause, "'");

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_FIRST_NAME);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_LAST_NAME);
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHONE_NO);

	Eina_List* vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	file_path = NULL;

	if (!vals) {
		//("DB error");
		eina_list_free(col_names);
		return;
	} else {
		int row_count = eina_list_count(vals);

		for (int i = 0 ; i < row_count ; i++) {
			Eina_List* row_vals = eina_list_nth(vals, i);
			char *temp_fname = (char*)eina_list_nth(row_vals, 0);
			*first_name = temp_fname;
			char *temp_lname = (char*)eina_list_nth(row_vals, 1);
			*last_name = temp_lname;
			char *temp_pnumber = (char*)eina_list_nth(row_vals, 2);
			*phone_number = temp_pnumber;
			eina_list_free(row_vals);
			break;
		}
		eina_list_free(vals);
	}
	eina_list_free(col_names);
	return;
}


int get_unread_message_count(char* table_name)
{
	// number of rows, having out == 1 and unread == 0
	if (!table_name) {
		return 0;
	}
	int num_of_rows = 0;

	char* where_clause = NULL;
	char unread_str[50];
	sprintf(unread_str, "%d", 1);



	where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_UNREAD) + strlen(" = ") + strlen(unread_str) + strlen(" AND ") + strlen(MESSAGE_INFO_TABLE_OUT_MSG) + strlen(" = ") + strlen(unread_str) + strlen(" AND ") + strlen(MESSAGE_INFO_TABLE_SERVICE) + strlen(" = ") + strlen(unread_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_UNREAD);
	strcat(where_clause, " = ");
	strcat(where_clause, unread_str);
	strcat(where_clause, " AND ");
	strcat(where_clause, MESSAGE_INFO_TABLE_OUT_MSG);
	strcat(where_clause, " != ");
	strcat(where_clause, unread_str);
	strcat(where_clause, " AND ");
	strcat(where_clause, MESSAGE_INFO_TABLE_SERVICE);
	strcat(where_clause, " < ");
	strcat(where_clause, unread_str);


#if 0
	where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_UNREAD) + strlen(" = ") + strlen(unread_str) + strlen(" AND ") + strlen(MESSAGE_INFO_TABLE_OUT_MSG) + strlen(" != ") + strlen(unread_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_UNREAD);
	strcat(where_clause, " = ");
	strcat(where_clause, unread_str);
	strcat(where_clause, " AND ");
	strcat(where_clause, MESSAGE_INFO_TABLE_OUT_MSG);
	strcat(where_clause, " != ");
	strcat(where_clause, unread_str);
#endif

	num_of_rows = get_number_of_rows(table_name, where_clause);
	free(where_clause);
	return num_of_rows;
}

int get_number_of_messages(char* table_name)
{
	// number of rows, having out == 1 and unread == 0
	if (!table_name) {
		return 0;
	}
	int num_of_rows = 0;
	num_of_rows = get_number_of_rows(table_name, NULL);
	return num_of_rows;
}


Eina_List* get_all_peer_ids()
{
	Eina_List* peer_details = NULL;
	char* table_name = PEER_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;

	col_names = eina_list_append(col_names, PEER_INFO_TABLE_CHAT_ID);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_KEY);

	peer_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, PEER_INFO_TABLE_LAST_MESSAGE_DATE, EINA_FALSE, NULL);

	eina_list_free(col_names);
	eina_list_free(col_types);
	return peer_details;
}

int get_number_of_unread_messages()
{
	int no_of_unread = 0;
	Eina_List* peer_details = get_all_peer_ids();
	for (int i = 0; i < eina_list_count(peer_details) ; i++) {
		Eina_List* ts_msg = eina_list_nth(peer_details, i);
		int peer_id = 0;
		int *temp_peer_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_peer_id) {
			peer_id  = *temp_peer_id;
			free(temp_peer_id);
			temp_peer_id = NULL;
		}
		char *msg_table = get_table_name_from_number(peer_id);
		int count = 0;
		if (msg_table) {
			 count = get_unread_message_count(msg_table);
		}
		no_of_unread = no_of_unread + count;
		free(msg_table);
		eina_list_free(ts_msg);
	}
	eina_list_free(peer_details);
	return no_of_unread;
}

Eina_Bool is_user_present_buddy_table(int peer_id)
{
	Eina_Bool ret = EINA_FALSE;

	Eina_List* peer_details = NULL;
	char* table_name = BUDDY_INFO_TABLE_NAME;

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PRINT_NAME);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	char chat_id_str[50];
	sprintf(chat_id_str, "%d", peer_id);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(chat_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, chat_id_str);

	peer_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);
	if (peer_details) {
		for (int i = 0; i < eina_list_count(peer_details) ; i++) {
			Eina_List* ts_msg = eina_list_nth(peer_details, i);
			ret = EINA_TRUE;
			eina_list_free(ts_msg);
			break;
		}
		eina_list_free(peer_details);
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	return ret;
}

Eina_Bool is_user_present_peer_table(int peer_id)
{
	Eina_Bool ret = EINA_FALSE;

	Eina_List* peer_details = NULL;
	char* table_name = PEER_INFO_TABLE_NAME;

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PRINT_NAME);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	char chat_id_str[50];
	sprintf(chat_id_str, "%d", peer_id);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(chat_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, chat_id_str);

	peer_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);
	if (peer_details) {
		for (int i = 0; i < eina_list_count(peer_details) ; i++) {
			Eina_List* ts_msg = eina_list_nth(peer_details, i);
			ret = EINA_TRUE;
			eina_list_free(ts_msg);
			break;
		}
		eina_list_free(peer_details);
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	return ret;
}

Eina_Bool is_user_present_chat_table(int peer_id)
{
	Eina_Bool ret = EINA_FALSE;

	Eina_List* peer_details = NULL;
	char* table_name = CHAT_INFO_TABLE_NAME;

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PRINT_TITLE);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	char chat_id_str[50];
	sprintf(chat_id_str, "%d", peer_id);

	char* where_clause = (char*)malloc(strlen(CHAT_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(chat_id_str) + 1);
	strcpy(where_clause, CHAT_INFO_TABLE_CHAT_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, chat_id_str);

	peer_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);
	if (peer_details) {
		for (int i = 0; i < eina_list_count(peer_details) ; i++) {
			Eina_List* ts_msg = eina_list_nth(peer_details, i);
			ret = EINA_TRUE;
			eina_list_free(ts_msg);
			break;
		}
		eina_list_free(peer_details);
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	return ret;
}

Eina_Bool delete_message_from_table(char *tablename, int msg_id)
{
	if (!tablename) {
		return EINA_FALSE;
	}

	char* where_clause = NULL;
	char msg_id_str[50];
	sprintf(msg_id_str,"%d", msg_id);

	char *var_query = (char*)malloc(strlen("DELETE FROM ") + strlen(tablename) + strlen(" WHERE ") + strlen(MESSAGE_INFO_TABLE_MESSAGE_ID) + strlen(" = ") + strlen(msg_id_str) + strlen(";") + 1);
	strcpy(var_query, "DELETE FROM ");
	strcat(var_query, tablename);
	strcat(var_query, " WHERE ");
	strcat(var_query, MESSAGE_INFO_TABLE_MESSAGE_ID);
	strcat(var_query, " = ");
	strcat(var_query, msg_id_str);
	strcat(var_query, ";");
	int ret;
	char* err_msg = 0;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	ret = sqlite3_exec(db,var_query, NULL, NULL, &err_msg);
	close_database(db);
	if( ret != SQLITE_OK ){
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	free(var_query);
	return EINA_TRUE;
}

