/**
 * @file tg_db_wrapper.c
 * @date Jun 26, 2015
 * @author sandeep
 */

#include "tg_db_wrapper.h"
#include <mime_type.h>
#include <utils_i18n.h>

void create_data_base_tables()
{
#if 0
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_Bool ret = create_table(table_name, col_names, col_types);
	if (!ret) {
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	ret = create_table(table_name, col_names, col_types);
	if (!ret) {
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
	if (!ret) {
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
	if (!ret) {
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

	table_name = TG_SETTINGS_TABLE_NAME;
	col_names = NULL;
	col_names = eina_list_append(col_names, TG_SETTINGS_ROW_ID);
	col_names = eina_list_append(col_names, TG_SETTINGS_CHAT_BG);

	col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER_PRIMARY_AUTO_INC_KEY);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
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
#endif
}


Eina_Bool insert_unsent_message_to_db(const char *app_name, const char *command, const char *buddy_id, const char *msg_id, const char *msg_type, const char * msg_data, const char *type_of_chat)
{
	Eina_Bool ret = EINA_FALSE;
	if (!app_name || !command || !buddy_id || !msg_id || !msg_type || !msg_data || !type_of_chat) {
		return ret;
	}

	char* table_name = MESSAGE_TRANSPORT_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = NULL;
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


	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, app_name);
	col_values = eina_list_append(col_values, command);
	col_values = eina_list_append(col_values,buddy_id);
	col_values = eina_list_append(col_values, msg_id);
	col_values = eina_list_append(col_values, msg_type);
	col_values = eina_list_append(col_values, msg_data);
	col_values = eina_list_append(col_values, type_of_chat);


	ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		ret = EINA_FALSE;
	} else {
		ret = EINA_TRUE;
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
	return ret;
}

Eina_Bool insert_unsent_media_message_to_db(const char *app_name, const char *command, const char *buddy_id, const char *msg_id, const char *media_id, const char *msg_type, const char *file_path, const char *type_of_chat)
{
	Eina_Bool ret = EINA_FALSE;

	if (!app_name || !command || !buddy_id || !msg_id || !media_id || !msg_type || !file_path || !type_of_chat) {
		return ret;
	}


	char* table_name = MEDIA_TRANSPORT_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = NULL;
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

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, app_name);
	col_values = eina_list_append(col_values, command);
	col_values = eina_list_append(col_values, buddy_id);
	col_values = eina_list_append(col_values, msg_id);
	col_values = eina_list_append(col_values, media_id);
	col_values = eina_list_append(col_values, msg_type);
	col_values = eina_list_append(col_values, file_path);
	col_values = eina_list_append(col_values, type_of_chat);

	ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		ret = EINA_FALSE;
	} else {
		ret = EINA_TRUE;
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
	return ret;
}


Eina_List* get_all_peer_details(char* start_name)
{
	Eina_List* peer_details = NULL;
	char* table_name = PEER_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;

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

	//peer_details = get_values_from_table_sync(db, table_name, col_names, col_types, NULL);
	char *where_clause = NULL;
	if (start_name) {
		where_clause = (char *)malloc(strlen(PEER_INFO_TABLE_PRINT_NAME) + strlen(" LIKE '") + strlen(start_name) + strlen("%'") + 1);
		strcpy(where_clause, PEER_INFO_TABLE_PRINT_NAME);
		strcat(where_clause, " LIKE '");
		strcat(where_clause, start_name);
		strcat(where_clause, "%'");
	}

	peer_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, PEER_INFO_TABLE_LAST_MESSAGE_DATE, EINA_FALSE, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);
	if (where_clause) {
		free(where_clause);
		where_clause = NULL;
	}

	return peer_details;
}

peer_with_pic_s* get_peer_info(int peer_id)
{
	Eina_List* peer_details = NULL;
	char* table_name = PEER_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;

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


	char chat_id_str[50];
	sprintf(chat_id_str, "%d", peer_id);

	char* where_clause = (char*)malloc(strlen(PEER_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(chat_id_str) + 1);
	strcpy(where_clause, PEER_INFO_TABLE_CHAT_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, chat_id_str);

	peer_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, PEER_INFO_TABLE_LAST_MESSAGE_DATE, EINA_FALSE, where_clause);

	free(where_clause);

	peer_with_pic_s *item = NULL;


	for (int i = 0; i < eina_list_count(peer_details) ; i++) {
		Eina_List* ts_msg = eina_list_nth(peer_details, i);
		tg_peer_info_s* peer_info = (tg_peer_info_s*)malloc(sizeof(tg_peer_info_s));

		int *temp_peer_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_peer_id) {
			peer_info->peer_id  = *temp_peer_id;
			free(temp_peer_id);
		}

		int *temp_peer_type = (int*)eina_list_nth(ts_msg, 1);
		if (temp_peer_type) {
			peer_info->peer_type  = *temp_peer_type;
			free(temp_peer_type);
		}

		int *temp_flags = (int*)eina_list_nth(ts_msg, 2);
		if (temp_flags) {
			peer_info->flags = *temp_flags;
			free(temp_flags);
		}

		char *temp_msg_id = (char*)eina_list_nth(ts_msg, 3);
		if (temp_msg_id) {
			peer_info->last_msg_id  = atoll(temp_msg_id);
			free(temp_msg_id);
		} else {
			peer_info->last_msg_id = 0;
		}

		int *temp_last_msg_date = (int*)eina_list_nth(ts_msg, 4);
		if (temp_last_msg_date) {
			peer_info->last_msg_date = *temp_last_msg_date;
			free(temp_last_msg_date);
		}

		char *temp_print_name = (char*)eina_list_nth(ts_msg, 5);
		if (temp_print_name) {
			peer_info->print_name  = strdup(temp_print_name);
			free(temp_print_name);
		} else {
			peer_info->print_name = NULL;
		}

		int *temp_struct_ver = (int*)eina_list_nth(ts_msg, 6);
		if (temp_struct_ver) {
			peer_info->struct_version = *temp_struct_ver;
			free(temp_struct_ver);
		}

		int *temp_no_unread = (int*)eina_list_nth(ts_msg, 7);
		if (temp_no_unread) {
			peer_info->no_of_unread_msgs = *temp_no_unread;
			free(temp_no_unread);
		}

		int *temp_last_seen = (int*)eina_list_nth(ts_msg, 8);
		if (temp_last_seen) {
			peer_info->last_seen_time = *temp_last_seen;
			free(temp_last_seen);
		}

		char *temp_pic_path = (char*)eina_list_nth(ts_msg, 9);
		if (temp_pic_path) {
			peer_info->photo_path = strdup(temp_pic_path);
			free(temp_pic_path);
		} else {
			peer_info->photo_path = NULL;
		}

		int *temp_pic_id = (int*)eina_list_nth(ts_msg, 10);
		if (temp_pic_id) {
			peer_info->photo_id = *temp_pic_id;
			free(temp_pic_id);
		}
		int *temp_unknown = (int*)eina_list_nth(ts_msg, 11);
		if (temp_unknown) {
			peer_info->is_unknown = *temp_unknown;
			free(temp_unknown);
		}

		eina_list_free(ts_msg);

		item = (peer_with_pic_s*) malloc(sizeof (peer_with_pic_s));
		item->use_data = peer_info;
		item->contact_icon = NULL;

		break;

	}
	eina_list_free(peer_details);



	eina_list_free(col_names);
	eina_list_free(col_types);

	return item;
}

Eina_List* get_group_chat_details()
{
	Eina_List* chat_details = NULL;
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

	chat_details = get_values_from_table_sync(table_name, col_names, col_types, NULL);

	eina_list_free(col_names);
	eina_list_free(col_types);

	return chat_details;
}

tg_chat_info_s* get_chat_info(int chat_id)
{
	Eina_List* chat_details = NULL;

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

	char chat_id_str[50];
	sprintf(chat_id_str, "%d", chat_id);

	char* where_clause = (char*)malloc(strlen(CHAT_INFO_TABLE_CHAT_ID) + strlen(" = ") + strlen(chat_id_str) + 1);
	strcpy(where_clause, CHAT_INFO_TABLE_CHAT_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, chat_id_str);

	chat_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);

	tg_chat_info_s* chat_info = NULL;

	if (chat_details && eina_list_count(chat_details) > 0) {
		Eina_List* ts_msg = eina_list_nth(chat_details, 0);

		chat_info = (tg_chat_info_s*)malloc(sizeof(tg_chat_info_s));

		int *temp_chat_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_chat_id) {
			chat_info->chat_id  = *temp_chat_id;
			free(temp_chat_id);
		}

		int *temp_flags = (int*)eina_list_nth(ts_msg, 1);
		if (temp_flags) {
			chat_info->flags  = *temp_flags;
			free(temp_flags);
		}

		char *temp_print_title = (char*)eina_list_nth(ts_msg, 2);
		if (temp_print_title) {
			chat_info->print_title  = strdup(temp_print_title);
			free(temp_print_title);
		}

		int *temp_struct_ver = (int*)eina_list_nth(ts_msg, 3);
		if (temp_struct_ver) {
			chat_info->struct_version  = *temp_struct_ver;
			free(temp_struct_ver);
		}

		char *temp_photo_id = (char*)eina_list_nth(ts_msg, 4);
		if (temp_photo_id) {
			chat_info->photo_id  = atoll(temp_photo_id);
			free(temp_photo_id);
		}

		char *temp_photo_path = (char*)eina_list_nth(ts_msg, 5);
		if (temp_photo_path) {
			chat_info->photo_path  = strdup(temp_photo_path);
			free(temp_photo_path);
		}

		char *temp_title = (char*)eina_list_nth(ts_msg, 6);
		if (temp_title) {
			chat_info->title  = strdup(temp_title);
			free(temp_title);
		}

		int *temp_users_num = (int*)eina_list_nth(ts_msg, 7);
		if (temp_users_num) {
			chat_info->users_num  = *temp_users_num;
			free(temp_users_num);
		}

		int *temp_user_list_size = (int*)eina_list_nth(ts_msg, 8);
		if (temp_user_list_size) {
			chat_info->user_list_size  = *temp_user_list_size;
			free(temp_user_list_size);
		}

		int *temp_user_list_version = (int*)eina_list_nth(ts_msg, 9);
		if (temp_user_list_version) {
			chat_info->user_list_version  = *temp_user_list_version;
			free(temp_user_list_version);
		}

		int *temp_inviter_id = (int*)eina_list_nth(ts_msg, 10);
		if (temp_inviter_id) {
			chat_info->inviter_id  = *temp_inviter_id;
			free(temp_inviter_id);
		}

		char *temp_full_ids = (char*)eina_list_nth(ts_msg, 11);
		if (temp_full_ids) {
			char* item = strtok(temp_full_ids, ",");
			int count = 0;
			chat_info->chat_users[count] = atoi(item);

			while (item != NULL) {
				count++;
				item = strtok(NULL, ",");
				if (item != NULL) {
					chat_info->chat_users[count] = atoi(item);
				}
			}
			free(temp_full_ids);
		}

		int *temp_date = (int*)eina_list_nth(ts_msg, 12);
		if (temp_date) {
			chat_info->date  = *temp_date;
			free(temp_date);
		}

		int *temp_version = (int*)eina_list_nth(ts_msg, 13);
		if (temp_version) {
			chat_info->version  = *temp_version;
			free(temp_version);
		}

		int *temp_admin_id = (int*)eina_list_nth(ts_msg, 14);
		if (temp_admin_id) {
			chat_info->admin_id  = *temp_admin_id;
			free(temp_admin_id);
		}
		eina_list_free(ts_msg);
		eina_list_free(chat_details);
	}
	return chat_info;
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

	user_details = get_values_from_table_sync(table_name, col_names, col_types, NULL);

	eina_list_free(col_names);
	eina_list_free(col_types);

	return user_details;
}

Eina_List* get_buddy_list_info()
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	int unknown = 0;
	char unknown_str[50];
	sprintf(unknown_str, "%d", unknown);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_IS_UNKNOWN_PEER) + strlen(" = ") + strlen(unknown_str) + strlen(" AND ") + strlen(USER_INFO_TABLE_IS_DELETED) + strlen(" = ") + strlen(unknown_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_IS_UNKNOWN_PEER);
	strcat(where_clause, " = ");
	strcat(where_clause, unknown_str);
	strcat(where_clause, " OR ");
	strcat(where_clause, USER_INFO_TABLE_IS_DELETED);
	strcat(where_clause, " = ");
	strcat(where_clause, unknown_str);

	user_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, USER_INFO_TABLE_FIRST_NAME, EINA_TRUE, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);
	free(where_clause);

	return user_details;
}

Eina_List* get_unknown_buddy_list_info()
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	int unknown = 1;
	char unknown_str[50];
	sprintf(unknown_str, "%d", unknown);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_IS_UNKNOWN_PEER) + strlen(" = ") + strlen(unknown_str) + strlen(" AND ") + strlen(USER_INFO_TABLE_IS_DELETED) + strlen(" = ") + strlen(unknown_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_IS_UNKNOWN_PEER);
	strcat(where_clause, " = ");
	strcat(where_clause, unknown_str);
	strcat(where_clause, " OR ");
	strcat(where_clause, USER_INFO_TABLE_IS_DELETED);
	strcat(where_clause, " = ");
	strcat(where_clause, unknown_str);

	user_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, USER_INFO_TABLE_PRINT_NAME, EINA_TRUE, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);
	free(where_clause);

	return user_details;
}

#if 0
void set_chat_bg(char *file_path)
{
	if (!file_path) {
		return;
	}
	char* table_name = TG_SETTINGS_TABLE_NAME;

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, TG_SETTINGS_CHAT_BG);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, file_path);

	// already exist. So update the table
	char* where_clause = NULL;
	char user_id_str[50];
	sprintf(user_id_str,"%d",1);
	where_clause = (char*)malloc(strlen(TG_SETTINGS_ROW_ID) + strlen(" = ") + strlen(user_id_str) + 1);
	strcpy(where_clause, TG_SETTINGS_ROW_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, user_id_str);
	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);
	free(where_clause);

	if(!ret) {
		ret = insert_table(table_name, col_names, col_types,col_values);
	} else {

	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

char* get_chat_bg()
{
	char* table_name = TG_SETTINGS_TABLE_NAME;

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, TG_SETTINGS_CHAT_BG);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List *settings_array = NULL;
	char *chat_bg = NULL;
	char* where_clause = NULL;
	char user_id_str[50];
	sprintf(user_id_str,"%d",1);
	where_clause = (char*)malloc(strlen(TG_SETTINGS_ROW_ID) + strlen(" = ") + strlen(user_id_str) + 1);
	strcpy(where_clause, TG_SETTINGS_ROW_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, user_id_str);
	settings_array = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);
	if (settings_array && eina_list_count(settings_array) > 0) {
		Eina_List* settings_details = eina_list_nth(settings_array, 0);
		if (settings_details && eina_list_count(settings_details) > 0) {
			char* pic_path = (char*)eina_list_nth(settings_details, 0);

			if (pic_path && strlen(pic_path) > 0) {
				chat_bg = strdup(pic_path);
			}
			free(pic_path);
			eina_list_free(settings_details);
		}
		eina_list_free(settings_array);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);

	return chat_bg;

}
#endif
char* get_profile_pic_path(int buddy_id)
{
	Eina_List* buddy_details_array = NULL;
	char* profile_pic_path = NULL;

	char* table_name = BUDDY_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);


	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(buddy_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, buddy_id_str);

	buddy_details_array = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);



	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {
			char* pic_path = (char*)eina_list_nth(buddy_details, 0);

			if (pic_path && strlen(pic_path) > 0) {
				profile_pic_path = strdup(pic_path);
			}
			free(pic_path);
			eina_list_free(buddy_details);
		}
		eina_list_free(buddy_details_array);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);

	return profile_pic_path;
}


char* get_buddy_name_from_id(int buddy_id)
{
	Eina_List* buddy_details_array = NULL;
	char* profile_name = NULL;

	char* table_name = BUDDY_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PRINT_NAME);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);


	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(buddy_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, buddy_id_str);

	buddy_details_array = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);



	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {
			char* name = (char*)eina_list_nth(buddy_details, 0);

			if (name && strlen(name) > 0) {
				profile_name = strdup(name);
			}
			free(name);
			eina_list_free(buddy_details);
		}

		eina_list_free(buddy_details_array);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);

	return profile_name;
}

Eina_Bool is_phone_number_exists_in_buddy_list(const char *phone_num)
{
	Eina_Bool is_exist = EINA_FALSE;
	if (!phone_num)
		return is_exist;

	char* table_name = BUDDY_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHONE_NO);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	char *where_clause = NULL;
	where_clause = (char *)malloc(strlen(USER_INFO_TABLE_PHONE_NO) + strlen(" LIKE '") + strlen("%") + strlen(phone_num) + strlen("%'") + 1);
	strcpy(where_clause, USER_INFO_TABLE_PHONE_NO);
	strcat(where_clause, " LIKE '");
	strcat(where_clause, "%");
	strcat(where_clause, phone_num);
	strcat(where_clause, "%'");

	Eina_List* buddy_details_array = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);

	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {
			char* name = (char*)eina_list_nth(buddy_details, 0);

			if (name && strlen(name) > 0) {
				is_exist = EINA_TRUE;
			}
			free(name);
			eina_list_free(buddy_details);
		}

		eina_list_free(buddy_details_array);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);
	return is_exist;
}

char* get_buddy_phone_num_from_id(int buddy_id)
{
	Eina_List* buddy_details_array = NULL;
	char* phone_num = NULL;

	char* table_name = BUDDY_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHONE_NO);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);


	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(buddy_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, buddy_id_str);

	buddy_details_array = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);

	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {
			char* name = (char*)eina_list_nth(buddy_details, 0);

			if (name && strlen(name) > 0) {
				phone_num = strdup(name);
			}
			free(name);
			eina_list_free(buddy_details);
		}

		eina_list_free(buddy_details_array);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);

	return phone_num;
}

int  get_buddy_block_status(int buddy_id)
{
	Eina_List* buddy_details_array = NULL;

	char* table_name = BUDDY_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_BLOCKED);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);


	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(buddy_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, buddy_id_str);

	buddy_details_array = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);

	int is_unknown = 0;

	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {

			int *temp_unknown_status = (int*)eina_list_nth(buddy_details, 0);
			if(temp_unknown_status) {
				is_unknown = *temp_unknown_status;
				free(temp_unknown_status);
			}
			eina_list_free(buddy_details);
		}
		eina_list_free(buddy_details_array);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);

	return is_unknown;
}

int  get_buddy_delete_status(int buddy_id)
{
	Eina_List* buddy_details_array = NULL;

	char* table_name = BUDDY_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_DELETED);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);


	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(buddy_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, buddy_id_str);

	buddy_details_array = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);

	int is_unknown = 0;

	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {

			int *temp_unknown_status = (int*)eina_list_nth(buddy_details, 0);
			if(temp_unknown_status) {
				is_unknown = *temp_unknown_status;
				free(temp_unknown_status);
			}
			eina_list_free(buddy_details);
		}
		eina_list_free(buddy_details_array);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);

	return is_unknown;
}

int  get_buddy_unknown_status(int buddy_id)
{
	Eina_List* buddy_details_array = NULL;

	char* table_name = BUDDY_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);


	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(buddy_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, buddy_id_str);

	buddy_details_array = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);

	int is_unknown = 0;

	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {

			int *temp_unknown_status = (int*)eina_list_nth(buddy_details, 0);
			if(temp_unknown_status) {
				is_unknown = *temp_unknown_status;
				free(temp_unknown_status);
			}
			eina_list_free(buddy_details);
		}
		eina_list_free(buddy_details_array);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);

	return is_unknown;
}

int  get_buddy_online_status(int buddy_id)
{
	Eina_List* buddy_details_array = NULL;

	char* table_name = BUDDY_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_ONLINE_STATUS);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);


	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	char* where_clause = (char*)malloc(strlen(USER_INFO_TABLE_USER_ID) + strlen(" = ") + strlen(buddy_id_str) + 1);
	strcpy(where_clause, USER_INFO_TABLE_USER_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, buddy_id_str);

	buddy_details_array = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	free(where_clause);

	int is_online = -1;

	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {

			int *temp_online_status = (int*)eina_list_nth(buddy_details, 0);
			if(temp_online_status) {
				is_online = *temp_online_status;
				free(temp_online_status);
			}
			eina_list_free(buddy_details);
		}
		eina_list_free(buddy_details_array);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);

	return is_online;
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

	char out_str[50];
	sprintf(out_str, "%d", 0);

#if 0
	char service_str[50];
	sprintf(service_str, "%d", 1);

	where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_UNREAD) + strlen(" = ") + strlen(unread_str) + strlen(" AND ") + strlen(MESSAGE_INFO_TABLE_OUT_MSG) + strlen(" = ") + strlen(out_str) + strlen(" OR ") + strlen(MESSAGE_INFO_TABLE_SERVICE) + strlen(" = ") + strlen(service_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_UNREAD);
	strcat(where_clause, " = ");
	strcat(where_clause, unread_str);
	strcat(where_clause, " AND ");
	strcat(where_clause, MESSAGE_INFO_TABLE_OUT_MSG);
	strcat(where_clause, " = ");
	strcat(where_clause, out_str);
	strcat(where_clause, " OR ");
	strcat(where_clause, MESSAGE_INFO_TABLE_SERVICE);
	strcat(where_clause, " = ");
	strcat(where_clause, service_str);
#endif

	where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_UNREAD) + strlen(" = ") + strlen(unread_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_UNREAD);
	strcat(where_clause, " = ");
	strcat(where_clause, unread_str);

	num_of_rows = get_number_of_rows(table_name, where_clause);
	free(where_clause);

	return num_of_rows;
}


tg_message_s* get_latest_message_from_message_table(char* table_name, Eina_Bool is_for_date)
{
	tg_message_s* message = NULL;

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

	char service_str[50];
	sprintf(service_str, "%d", 2);

	char marked_del_str[50];
	sprintf(marked_del_str, "%d", 1);
	char* where_clause = NULL;
	if (!is_for_date) {
		where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_SERVICE) + strlen(" != ") + strlen(service_str) + strlen(" AND ") + strlen(MESSAGE_INFO_TABLE_MARKED_FOR_DELETE)+ strlen(" != ")+ strlen(marked_del_str) + 1);
		strcpy(where_clause, MESSAGE_INFO_TABLE_SERVICE);
		strcat(where_clause, " != ");
		strcat(where_clause, service_str);
		strcat(where_clause, " AND ");
		strcat(where_clause, MESSAGE_INFO_TABLE_MARKED_FOR_DELETE);
		strcat(where_clause, " != ");
		strcat(where_clause, marked_del_str);
	}

	message_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, MESSAGE_INFO_TABLE_DATE, EINA_FALSE, where_clause);
	if (where_clause) {
		free(where_clause);
		where_clause = NULL;
	}

	eina_list_free(col_names);
	eina_list_free(col_types);


	if (message_details && eina_list_count(message_details) > 0) {
		Eina_List* ts_msg = eina_list_nth(message_details, 0);

		message = (tg_message_s*)malloc(sizeof(tg_message_s));


		int *temp_msg_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_msg_id) {
			message->msg_id  = *temp_msg_id;
			free(temp_msg_id);
		}

		int *temp_flags = (int*)eina_list_nth(ts_msg, 1);
		if (temp_flags) {
			message->flags  = *temp_flags;
			free(temp_flags);
		}


		int *temp_fwd_from_id = (int*)eina_list_nth(ts_msg, 2);
		if (temp_fwd_from_id) {
			message->fwd_from_id  = *temp_fwd_from_id;
			free(temp_fwd_from_id);
		}


		int *temp_fwd_date = (int*)eina_list_nth(ts_msg, 3);
		if (temp_fwd_date) {
			message->fwd_date  = *temp_fwd_date;
			free(temp_fwd_date);
		}


		int *temp_from_id = (int*)eina_list_nth(ts_msg, 4);
		if (temp_from_id) {
			message->from_id  = *temp_from_id;
			free(temp_from_id);
		}

		int *temp_to_id = (int*)eina_list_nth(ts_msg, 5);
		if (temp_to_id) {
			message->to_id  = *temp_to_id;
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
			message->media_type  = *temp_media_type;
			free(temp_media_type);
		}

		char *temp_media_id = (char*)eina_list_nth(ts_msg, 14);
		if (temp_media_id) {
			message->media_id  = strdup(temp_media_id);
			free(temp_media_id);
		}

		int *temp_unique_id = (int*)eina_list_nth(ts_msg, 15);
		if (temp_unique_id) {
			message->unique_id  = *temp_unique_id;
			free(temp_unique_id);
		}
	}
	return message;
}

Eina_Bool set_all_rows_read(const char *table_name)
{
	if (!table_name)
		return EINA_FALSE;

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNREAD);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_values = NULL;
	int un_read_res = 0;
	col_values = eina_list_append(col_values, &(un_read_res));

	char* where_clause = NULL;
	char usr_str[50];
	int un_read = 1;
	sprintf(usr_str,"%d", un_read);
	where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_UNREAD) + strlen(" = ") + strlen(usr_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_UNREAD);
	strcat(where_clause, " = ");
	strcat(where_clause, usr_str);

	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);

	if(!ret) {
		//("error: database creation failed");
	} else {

	}

	free(where_clause);
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

	return EINA_TRUE;
}

void update_msg_into_db(tg_message_s *M, char* table_name)
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

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, &(M->msg_id));
	col_values = eina_list_append(col_values, &(M->flags));
	col_values = eina_list_append(col_values, &(M->fwd_from_id));
	col_values = eina_list_append(col_values, &(M->fwd_date));
	col_values = eina_list_append(col_values, &(M->from_id));
	col_values = eina_list_append(col_values, &(M->to_id));
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
	col_values = eina_list_append(col_values, &(M->media_type));

	col_values = eina_list_append(col_values, (M->media_id));


	char* where_clause = NULL;

	char usr_str[50];
	sprintf(usr_str,"%d",M->msg_id);
	where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_MESSAGE_ID) + strlen(" = ") + strlen(usr_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_MESSAGE_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, usr_str);

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

int insert_current_date_to_table(char* tb_name)
{
	tg_message_s* last_msg = get_latest_message_from_message_table(tb_name, EINA_TRUE);
	if (last_msg) {
		int old_date = last_msg->date;
		time_t old_t = old_date;

		struct tm old_lt;
		(void) localtime_r(&old_t, &old_lt);

		time_t new_t = time(NULL);

		struct tm new_lt;
		(void) localtime_r(&new_t, &new_lt);

		if (old_lt.tm_mday == new_lt.tm_mday && old_lt.tm_mon == new_lt.tm_mon && old_lt.tm_year == new_lt.tm_year) {
			// no need of new date
			return -1;
		} else {
			tg_message_s date_msg;
			date_msg.msg_id = get_time_stamp_in_macro();
			date_msg.media_type = tgl_message_media_none;

			int cur_time = time(NULL);
			cur_time = cur_time - 10;
			// convert time to string
			char res[256];
			sprintf(res, "%d", cur_time);

			date_msg.date = cur_time;
			date_msg.message = res;
			date_msg.message_len = strlen(res);
			date_msg.service = 2;
			date_msg.unread = 0;
			date_msg.out = 0;
			date_msg.media_id = "";
			date_msg.is_marked_for_delete = 0;
			insert_msg_into_db(&date_msg, tb_name, date_msg.msg_id);
			return date_msg.msg_id;
		}

	} else {
		tg_message_s date_msg;
		date_msg.msg_id = get_time_stamp_in_macro();
		date_msg.media_type = tgl_message_media_none;

		int cur_time = time(NULL);
		cur_time = cur_time - 10;
		// convert time to string
		char res[256];
		sprintf(res, "%d", cur_time);
		date_msg.date = cur_time;
		date_msg.message = res;
		date_msg.message_len = strlen(res);
		date_msg.service = 2;
		date_msg.unread = 0;
		date_msg.out = 0;
		date_msg.media_id = "";
		date_msg.is_marked_for_delete = 0;
		insert_msg_into_db(&date_msg, tb_name, date_msg.msg_id);
		return date_msg.msg_id;
	}
	return -1;
}


tg_message_s* get_message_from_message_table(long long msg_id, char* table_name)
{
	tg_message_s* message = NULL;

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

	char* where_clause = NULL;
	char msg_id_str[50];

	sprintf(msg_id_str, "%lld", msg_id);

	where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_MESSAGE_ID) + strlen(" = ") + strlen(msg_id_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_MESSAGE_ID);
	strcat(where_clause, " = ");
	strcat(where_clause, msg_id_str);

	message_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	free(where_clause);
	eina_list_free(col_names);
	eina_list_free(col_types);


	if (message_details && eina_list_count(message_details) > 0) {
		Eina_List* ts_msg = eina_list_nth(message_details, 0);

		message = (tg_message_s*)malloc(sizeof(tg_message_s));


		int *temp_msg_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_msg_id) {
			message->msg_id  = *temp_msg_id;
			free(temp_msg_id);
		}

		int *temp_flags = (int*)eina_list_nth(ts_msg, 1);
		if (temp_flags) {
			message->flags  = *temp_flags;
			free(temp_flags);
		}


		int *temp_fwd_from_id = (int*)eina_list_nth(ts_msg, 2);
		if (temp_fwd_from_id) {
			message->fwd_from_id  = *temp_fwd_from_id;
			free(temp_fwd_from_id);
		}


		int *temp_fwd_date = (int*)eina_list_nth(ts_msg, 3);
		if (temp_fwd_date) {
			message->fwd_date  = *temp_fwd_date;
			free(temp_fwd_date);
		}


		int *temp_from_id = (int*)eina_list_nth(ts_msg, 4);
		if (temp_from_id) {
			message->from_id  = *temp_from_id;
			free(temp_from_id);
		}

		int *temp_to_id = (int*)eina_list_nth(ts_msg, 5);
		if (temp_to_id) {
			message->to_id  = *temp_to_id;
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
			message->media_type  = *temp_media_type;
			free(temp_media_type);
		}

		char *temp_media_id = (char*)eina_list_nth(ts_msg, 14);
		if (temp_media_id) {
			message->media_id  = strdup(temp_media_id);
			free(temp_media_id);
		}

		int *temp_unique_id = (int*)eina_list_nth(ts_msg, 15);
		if (temp_unique_id) {
			message->unique_id  = *temp_unique_id;
			free(temp_unique_id);
		}
	}
	return message;
}



void insert_or_update_peer_into_database(tg_peer_info_s* UC)
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
	col_values = eina_list_append(col_values, &(UC->peer_id));
	col_values = eina_list_append(col_values, &(UC->peer_type));
	col_values = eina_list_append(col_values, &(UC->flags));
	char last_msg_id_str[50];
	sprintf(last_msg_id_str, "%lld", UC->last_msg_id);
	col_values = eina_list_append(col_values, last_msg_id_str);

	// last message date

	col_values = eina_list_append(col_values, &(UC->last_msg_date));


	if (UC->print_name) {
		col_values = eina_list_append(col_values, UC->print_name);
	} else {
		col_values = eina_list_append(col_values, "");
	}

	col_values = eina_list_append(col_values, &(UC->struct_version));
	col_values = eina_list_append(col_values, &(UC->no_of_unread_msgs));
	col_values = eina_list_append(col_values, &(UC->last_seen_time));
	col_values = eina_list_append(col_values, UC->photo_path);

	col_values = eina_list_append(col_values, &(UC->photo_id));
	col_values = eina_list_append(col_values, &(UC->is_unknown));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		// already exist. So update the table
		char* where_clause = NULL;
		char user_id_str[50];
		sprintf(user_id_str,"%d",UC->peer_id);
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

void insert_msg_into_db(tg_message_s *M, char* table_name, int unique_id)
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
	col_values = eina_list_append(col_values, &(M->msg_id));
	col_values = eina_list_append(col_values, &(M->flags));
	col_values = eina_list_append(col_values, &(M->fwd_from_id));
	col_values = eina_list_append(col_values, &(M->fwd_date));
	col_values = eina_list_append(col_values, &(M->from_id));
	col_values = eina_list_append(col_values, &(M->to_id));
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
	col_values = eina_list_append(col_values, &(M->media_type));

	col_values = eina_list_append(col_values, M->media_id);

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

}

void insert_media_info_to_db(tg_message_s *M, char *file_path, int width, int height, int size, char *latitude, char *longitude, char *first_name, char *last_name, char *phone_number)
{
	if (!M) {
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


	int media_type = M->media_type;

	col_values = eina_list_append(col_values,M->media_id);
	col_values = eina_list_append(col_values, &(media_type));

	if (media_type == tgl_message_media_photo) {

		long long temp_val = 0;
		char access_hash_str[50];

		/**
		 * @todo
		 * Should implement this to get the temp_val.
		 * Currently it is ZERO always.
		 */

		sprintf(access_hash_str, "%lld", temp_val);

		col_values = eina_list_append(col_values, access_hash_str);
		col_values = eina_list_append(col_values, &(temp_val));
		col_values = eina_list_append(col_values, &(M->date));

		col_values = eina_list_append(col_values, "");


		if (longitude) {
			col_values = eina_list_append(col_values, longitude);
		} else {
			col_values = eina_list_append(col_values, "0.000");
		}
		if (latitude) {
			col_values = eina_list_append(col_values, latitude);
		} else {
			col_values = eina_list_append(col_values, "0.000");
		}


		int temp_sizes = 4;
		col_values = eina_list_append(col_values, &temp_sizes);


		for (int j = 0; j < 4; j++) {

			char* photo_type = "";
			col_values = eina_list_append(col_values, photo_type);

			int photo_loc_dc = -1;
			col_values = eina_list_append(col_values, &photo_loc_dc);

			col_values = eina_list_append(col_values, "");

			int photo_loc_id = -1;
			col_values = eina_list_append(col_values, &photo_loc_id);


			col_values = eina_list_append(col_values, "");


			col_values = eina_list_append(col_values, &width);

			col_values = eina_list_append(col_values, &height);

			col_values = eina_list_append(col_values, &size);

			char* photo_data = "";
			col_values = eina_list_append(col_values, photo_data);

		}


	} else if (media_type == tgl_message_media_document) {

		int temp_val = 0;
		col_values = eina_list_append(col_values, &(temp_val));
		col_values = eina_list_append(col_values, &(temp_val));
		col_values = eina_list_append(col_values, &(temp_val));


		col_values = eina_list_append(col_values, "");

		if (longitude) {
			col_values = eina_list_append(col_values, longitude);
		} else {
			col_values = eina_list_append(col_values, "0.000");
		}
		if (latitude) {
			col_values = eina_list_append(col_values, latitude);
		} else {
			col_values = eina_list_append(col_values, "0.000");
		}
		col_values = eina_list_append(col_values, &(temp_val));


		for (int j = 0; j < 4; j++) {

			char* photo_type = "";
			col_values = eina_list_append(col_values, photo_type);

			int photo_loc_dc = -1;
			col_values = eina_list_append(col_values, &photo_loc_dc);

			col_values = eina_list_append(col_values, "");

			int photo_loc_id = -1;
			col_values = eina_list_append(col_values, &photo_loc_id);

			col_values = eina_list_append(col_values, "");

			col_values = eina_list_append(col_values, &width);

			col_values = eina_list_append(col_values, &height);

			col_values = eina_list_append(col_values, &size);

			char* photo_data = "";
			col_values = eina_list_append(col_values, photo_data);

		}
	} else if (media_type == tgl_message_media_geo) {
			// To be checked
			int dummy = 0;
			col_values = eina_list_append(col_values, &(dummy));
			col_values = eina_list_append(col_values, &(dummy));
			col_values = eina_list_append(col_values, &(dummy));

			col_values = eina_list_append(col_values, "");

			if (longitude) {
				col_values = eina_list_append(col_values, longitude);
			} else {
				col_values = eina_list_append(col_values, "0.000");
			}
			if (latitude) {
				col_values = eina_list_append(col_values, latitude);
			} else {
				col_values = eina_list_append(col_values, "0.000");
			}
			col_values = eina_list_append(col_values, &(dummy));

			for (int j = 0; j < 4; j++) {

				char* photo_type = "";
				col_values = eina_list_append(col_values, photo_type);

				int photo_loc_dc = -1;
				col_values = eina_list_append(col_values, &photo_loc_dc);

				col_values = eina_list_append(col_values, "");

				int photo_loc_id = -1;
				col_values = eina_list_append(col_values, &photo_loc_id);


				col_values = eina_list_append(col_values, "");

				col_values = eina_list_append(col_values, &width);

				col_values = eina_list_append(col_values, &height);

				col_values = eina_list_append(col_values, &size);

				char* photo_data = "";
				col_values = eina_list_append(col_values, photo_data);
			}
	} else {
		// To be checked
		int dummy = 0;
		col_values = eina_list_append(col_values, &(dummy));
		col_values = eina_list_append(col_values, &(dummy));
		col_values = eina_list_append(col_values, &(dummy));

		col_values = eina_list_append(col_values, "");

		if (longitude) {
			col_values = eina_list_append(col_values, longitude);
		} else {
			col_values = eina_list_append(col_values, "0.000");
		}
		if (latitude) {
			col_values = eina_list_append(col_values, latitude);
		} else {
			col_values = eina_list_append(col_values, "0.000");
		}
		col_values = eina_list_append(col_values, &(dummy));

		for (int j = 0; j < 4; j++) {

			char* photo_type = "";
			col_values = eina_list_append(col_values, photo_type);

			int photo_loc_dc = -1;
			col_values = eina_list_append(col_values, &photo_loc_dc);

			col_values = eina_list_append(col_values, "");

			int photo_loc_id = -1;
			col_values = eina_list_append(col_values, &photo_loc_id);


			col_values = eina_list_append(col_values, "");

			col_values = eina_list_append(col_values, &width);

			col_values = eina_list_append(col_values, &height);

			col_values = eina_list_append(col_values, &size);

			char* photo_data = "";
			col_values = eina_list_append(col_values, photo_data);
		}
	}

	if (phone_number) {
		col_values = eina_list_append(col_values, phone_number);
	} else {
		col_values = eina_list_append(col_values, "");
	}

	if (first_name) {
		col_values = eina_list_append(col_values, first_name);
	} else {
		col_values = eina_list_append(col_values, "");
	}

	if (last_name) {
		col_values = eina_list_append(col_values, last_name);
	} else {
		col_values = eina_list_append(col_values, "");
	}




	if (file_path) {
		col_values = eina_list_append(col_values, file_path);
	} else {
		col_values = eina_list_append(col_values, "");
	}


	/*****************************************/
	col_values = eina_list_append(col_values, "");

	char *mime_type = NULL;
	if (file_path) {
		char *extn = strrchr(file_path, '.');

		if (extn) {
			extn = replace(extn, '.', "");
		}


		if (extn) {
			mime_type_get_mime_type(extn, &mime_type);
		}
	}
	if (mime_type) {
		col_values = eina_list_append(col_values, mime_type);
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

	char *doc_thumb = NULL;
	get_thumbnail_from_video_url(file_path, &doc_thumb);

	if (!doc_thumb) {
		doc_thumb = "";
	}

	col_values = eina_list_append(col_values, doc_thumb);

	/*****************************************/



	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		//("error: database creation failed");
	} else {

	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

int get_media_size_from_db(long long media_id)
{
	int video_size = 0;
	char* table_name = MEDIA_INFO_TABLE_NAME;

	char usr_str[50];
	sprintf(usr_str, "%lld", media_id);
	char* where_clause = (char *)malloc(strlen(MEDIA_INFO_TABLE_MEDIA_ID) + strlen(" = '") + strlen(usr_str) + strlen("'") + 1);
	strcpy(where_clause, MEDIA_INFO_TABLE_MEDIA_ID);
	strcat(where_clause, " = '");
	strcat(where_clause, usr_str);
	strcat(where_clause, "'");

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_SIZE);

	Eina_List* vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	if (!vals) {
		//("DB error");
		eina_list_free(col_names);
		return 0;
	} else {
		int row_count = eina_list_count(vals);

		for (int i = 0 ; i < row_count ; i++) {
			Eina_List* row_vals = eina_list_nth(vals, i);
			int *temp_video_size = (int*)eina_list_nth(row_vals, 0);
			if (temp_video_size) {
				video_size  = *temp_video_size;
				free(temp_video_size);
			}
			eina_list_free(row_vals);
			break;
		}
		eina_list_free(vals);
	}
	eina_list_free(col_names);
	return video_size;
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

char* get_media_path_from_db(long long media_id)
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
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FILE_PATH);

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
			if (!file_path) {
				//("DB Error");
				eina_list_free(col_names);
				return NULL;
			} else {
				break;
			}
			eina_list_free(row_vals);
		}
		eina_list_free(vals);
	}
	eina_list_free(col_names);

	return file_path;
}

Eina_List* get_image_sizes_from_db(long long media_id)
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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE1);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH1);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT1);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE2);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH2);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT2);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE3);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH3);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT3);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_SIZE4);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_WIDTH4);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_PHOTO_HEIGHT4);
	vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	eina_list_free(col_types);
	eina_list_free(col_names);

	return vals;
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

Eina_List* get_all_buddy_details(char* start_name)
{

	Eina_List* user_details = NULL;
	if (!start_name)
	{
		start_name = "";
	}

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
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	int unknown = 0;
	char unknown_str[50];
	sprintf(unknown_str, "%d", unknown);

	char* where_clause = (char*)malloc(strlen(" ( ") + strlen(USER_INFO_TABLE_IS_UNKNOWN_PEER) + strlen(" = ") + strlen(unknown_str) + strlen(" AND ") + strlen(USER_INFO_TABLE_IS_DELETED) + strlen(" = ") + strlen(unknown_str) + strlen(" ) ") + strlen(" AND (") + strlen(USER_INFO_TABLE_PRINT_NAME) + strlen(" LIKE '") + strlen(start_name) + strlen("%' )") + 1);
	strcpy(where_clause, " ( ");
	strcat(where_clause, USER_INFO_TABLE_IS_UNKNOWN_PEER);
	strcat(where_clause, " = ");
	strcat(where_clause, unknown_str);
	strcat(where_clause, " AND ");
	strcat(where_clause, USER_INFO_TABLE_IS_DELETED);
	strcat(where_clause, " = ");
	strcat(where_clause, unknown_str);
	strcat(where_clause, " ) ");

	strcat(where_clause, " AND (");
	strcat(where_clause, USER_INFO_TABLE_PRINT_NAME);
	strcat(where_clause, " LIKE '");
	strcat(where_clause, start_name);
	strcat(where_clause, "%' )");

	user_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, USER_INFO_TABLE_FIRST_NAME, EINA_TRUE, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);
	free(where_clause);

	return user_details;

}

Eina_List* load_buddy_data_by_name(int current_user, char* name)
{
	Eina_List* buddy_list = NULL;
	Eina_List* user_info = get_all_buddy_details(name);

	if (!user_info) {
		return buddy_list;
	}

	int row_count = eina_list_count(user_info);

	for (int i = 0 ; i < row_count ; i++) {
		Eina_List* row_vals = eina_list_nth(user_info, i);

		int *temp_user_id = (int*)eina_list_nth(row_vals, 0);

		if (current_user == (*temp_user_id)) {
			for (int i = 0 ; i < eina_list_count(row_vals); i++) {
				void* val = eina_list_nth(row_vals, i);
				free(val);
			}
			continue;
		}

		user_data_s* user_data = (user_data_s*)malloc(sizeof(user_data_s));
		user_data->is_selected = EINA_FALSE;


		if (temp_user_id) {
			user_data->user_id.id = *temp_user_id;
			user_data->user_id.type = TGL_PEER_USER;
			free(temp_user_id);
		}

		char *print_name = (char*)eina_list_nth(row_vals, 1);
		if(print_name) {
			user_data->print_name = strdup(print_name);
			free(print_name);
		} else {
			user_data->print_name = NULL;
		}

		int *temp_struct_ver = (int*)eina_list_nth(row_vals, 2);
		if(temp_struct_ver) {
			user_data->structure_version = *temp_struct_ver;
			free(temp_struct_ver);
		}

		char *photo_path = (char*)eina_list_nth(row_vals, 3);
		if(photo_path) {
			user_data->photo_path = strdup(photo_path);
			free(photo_path);
		} else {
			user_data->photo_path = NULL;
		}


		int *temp_photo_id = (int*)eina_list_nth(row_vals, 4);
		if(temp_photo_id) {
			user_data->photo_id = *temp_photo_id;
			free(temp_photo_id);
		}

		char *first_name = (char*)eina_list_nth(row_vals, 5);
		if(first_name) {
			user_data->first_name = strdup(first_name);
			free(first_name);
		} else {
			user_data->first_name = NULL;
		}

		char *last_name = (char*)eina_list_nth(row_vals, 6);
		if(last_name) {
			user_data->last_name = strdup(last_name);
			free(last_name);
		} else {
			user_data->last_name = NULL;
		}

		char *phone_no = (char*)eina_list_nth(row_vals, 7);
		if(phone_no) {
			user_data->phone = strdup(phone_no);
			free(phone_no);
		} else {
			user_data->phone = NULL;
		}

		int *temp_access_hash = (int*)eina_list_nth(row_vals, 8);
		if(temp_access_hash) {
			user_data->access_hash = *temp_access_hash;
			free(temp_access_hash);
		}

		char *real_first_name = (char*)eina_list_nth(row_vals, 9);
		if(real_first_name) {
			user_data->real_first_name = strdup(real_first_name);
			free(real_first_name);
		} else {
			user_data->real_first_name = NULL;
		}

		char *real_last_name = (char*)eina_list_nth(row_vals, 10);
		if(real_last_name) {
			user_data->real_last_name = strdup(real_last_name);
			free(real_last_name);
		} else {
			user_data->real_last_name = NULL;
		}

		char *user_name = (char*)eina_list_nth(row_vals, 11);
		if(user_name) {
			user_data->username = strdup(user_name);
			free(user_name);
		} else {
			user_data->username = NULL;
		}

		int *temp_online_status = (int*)eina_list_nth(row_vals, 12);
		if(temp_online_status) {
			user_data->online = *temp_online_status;
			free(temp_online_status);
		}

		int *temp_last_seen = (int*)eina_list_nth(row_vals, 13);
		if(temp_last_seen) {
			user_data->last_seen = *temp_last_seen;
			free(temp_last_seen);
		}

		int *temp_is_blocked = (int*)eina_list_nth(row_vals, 14);
		if(temp_is_blocked) {
			user_data->is_blocked = *temp_is_blocked;
			free(temp_is_blocked);
		}

		int *temp_is_deleted = (int*)eina_list_nth(row_vals, 15);
		if(temp_is_deleted) {
			user_data->is_deleted = *temp_is_deleted;
			free(temp_is_deleted);
		}

		int *temp_is_unknown = (int*)eina_list_nth(row_vals, 16);
		if(temp_is_unknown) {
			user_data->is_unknown = *temp_is_unknown;
			free(temp_is_unknown);
		}

		user_data_with_pic_s *item = (user_data_with_pic_s*) malloc(sizeof (user_data_with_pic_s));
		item->use_data = user_data;
		//item->pic_file_location = NULL;
		item->contact_icon = NULL;
		buddy_list = eina_list_append(buddy_list, item);

		eina_list_free(row_vals);

	}
	eina_list_free(user_info);
	return buddy_list;
}


Eina_List* load_peer_data_by_name(char* name)
{
	Eina_List* peer_list = NULL;
	Eina_List* peer_details = get_all_peer_details(name);

	for (int i = 0; i < eina_list_count(peer_details) ; i++) {
		Eina_List* ts_msg = eina_list_nth(peer_details, i);
		tg_peer_info_s* peer_info = (tg_peer_info_s*)malloc(sizeof(tg_peer_info_s));

		int *temp_peer_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_peer_id) {
			peer_info->peer_id  = *temp_peer_id;
			free(temp_peer_id);
		}

		int *temp_peer_type = (int*)eina_list_nth(ts_msg, 1);
		if (temp_peer_type) {
			peer_info->peer_type  = *temp_peer_type;
			free(temp_peer_type);
		}

		int *temp_flags = (int*)eina_list_nth(ts_msg, 2);
		if (temp_flags) {
			peer_info->flags = *temp_flags;
			free(temp_flags);
		}

		char *temp_msg_id = (char*)eina_list_nth(ts_msg, 3);
		if (temp_msg_id) {
			peer_info->last_msg_id  = atoll(temp_msg_id);
			free(temp_msg_id);
		} else {
			peer_info->last_msg_id = 0;
		}

		int *temp_last_msg_date = (int*)eina_list_nth(ts_msg, 4);
		if (temp_last_msg_date) {
			peer_info->last_msg_date = *temp_last_msg_date;
			free(temp_last_msg_date);
		}

		char *temp_print_name = (char*)eina_list_nth(ts_msg, 5);
		if (temp_print_name) {
			peer_info->print_name  = strdup(temp_print_name);
			free(temp_print_name);
		} else {
			peer_info->print_name = NULL;
		}

		int *temp_struct_ver = (int*)eina_list_nth(ts_msg, 6);
		if (temp_struct_ver) {
			peer_info->struct_version = *temp_struct_ver;
			free(temp_struct_ver);
		}

		int *temp_no_unread = (int*)eina_list_nth(ts_msg, 7);
		if (temp_no_unread) {
			peer_info->no_of_unread_msgs = *temp_no_unread;
			free(temp_no_unread);
		}

		int *temp_last_seen = (int*)eina_list_nth(ts_msg, 8);
		if (temp_last_seen) {
			peer_info->last_seen_time = *temp_last_seen;
			free(temp_last_seen);
		}

		char *temp_pic_path = (char*)eina_list_nth(ts_msg, 9);
		if (temp_pic_path) {
			peer_info->photo_path = strdup(temp_pic_path);
			free(temp_pic_path);
		} else {
			peer_info->photo_path = NULL;
		}

		int *temp_pic_id = (int*)eina_list_nth(ts_msg, 10);
		if (temp_pic_id) {
			peer_info->photo_id = *temp_pic_id;
			free(temp_pic_id);
		}

		int *temp_unknown = (int*)eina_list_nth(ts_msg, 11);
		if (temp_unknown) {
			peer_info->is_unknown = *temp_unknown;
			free(temp_unknown);
		}

		eina_list_free(ts_msg);

		peer_with_pic_s *item = (peer_with_pic_s*) malloc(sizeof (peer_with_pic_s));
		item->use_data = peer_info;
		item->contact_icon = NULL;

		peer_list = eina_list_append(peer_list, item);

	}
	eina_list_free(peer_details);
	return peer_list;
}

void free_media_details(tgl_media_s *media_msg)
{
	if (media_msg) {
		if (media_msg->caption) {
			free(media_msg->caption);
		}
		if (media_msg->longitude) {
			free(media_msg->longitude);
		}
		if (media_msg->latitude) {
			free(media_msg->latitude);
		}
		if (media_msg->phone_no) {
			free(media_msg->phone_no);
		}
		if (media_msg->first_name) {
			free(media_msg->first_name);
		}
		if (media_msg->last_name) {
			free(media_msg->last_name);
		}
		if (media_msg->file_path) {
			free(media_msg->file_path);
		}
		if (media_msg->photo_type1) {
			free(media_msg->photo_type1);
		}
		if (media_msg->photo_data1) {
			free(media_msg->photo_data1);
		}
		if (media_msg->photo_type2) {
			free(media_msg->photo_type2);
		}
		if (media_msg->photo_data2) {
			free(media_msg->photo_data2);
		}
		if (media_msg->photo_type3) {
			free(media_msg->photo_type3);
		}
		if (media_msg->photo_data3) {
			free(media_msg->photo_data3);
		}
		if (media_msg->photo_type4) {
			free(media_msg->photo_type4);
		}
		if (media_msg->photo_data4) {
			free(media_msg->photo_data4);
		}
		if (media_msg->mime_type) {
			free(media_msg->mime_type);
		}
		if (media_msg->doc_type) {
			free(media_msg->doc_type);
		}
	}
}

tgl_media_s *get_media_details_from_db(long long media_id)
{
	Eina_List* img_details = get_image_details_from_db(media_id);

	if (!img_details) {
		return NULL;
	}

	tgl_media_s* media_info = (tgl_media_s*)malloc(sizeof(tgl_media_s));

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

	eina_list_free(row_vals);

	return media_info;

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


Eina_Bool mark_all_records_for_deletion(char *tablename)
{
	if (!tablename) {
		return EINA_FALSE;
	}
	char *var_query = (char*)malloc(strlen("UPDATE ") + strlen(tablename) + strlen(" SET ") + strlen(MESSAGE_INFO_TABLE_MARKED_FOR_DELETE) + strlen(" = ") + strlen("1") + strlen(" WHERE ") + strlen(MESSAGE_INFO_TABLE_MARKED_FOR_DELETE) + strlen(" = ") + strlen("0") + strlen(";") + 1);
	strcpy(var_query, "UPDATE ");
	strcat(var_query, tablename);
	strcat(var_query, " SET ");
	strcat(var_query, MESSAGE_INFO_TABLE_MARKED_FOR_DELETE);
	strcat(var_query, " = ");
	strcat(var_query, "1");
	strcat(var_query, " WHERE ");
	strcat(var_query, MESSAGE_INFO_TABLE_MARKED_FOR_DELETE);
	strcat(var_query, " = ");
	strcat(var_query, "0");
	strcat(var_query, ";");

	char* err_msg = 0;
	int ret;
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

Eina_Bool delete_date_messages_from_table(char *tablename)
{
	if (!tablename) {
		return EINA_FALSE;
	}

	char* where_clause = NULL;
	char service_id_str[50];
	sprintf(service_id_str,"%d", 2);

	char *var_query = (char*)malloc(strlen("DELETE FROM ") + strlen(tablename) + strlen(" WHERE ") + strlen(MESSAGE_INFO_TABLE_SERVICE) + strlen(" = ") + strlen(service_id_str) + strlen(";") + 1);
	strcpy(var_query, "DELETE FROM ");
	strcat(var_query, tablename);
	strcat(var_query, " WHERE ");
	strcat(var_query, MESSAGE_INFO_TABLE_SERVICE);
	strcat(var_query, " = ");
	strcat(var_query, service_id_str);
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
