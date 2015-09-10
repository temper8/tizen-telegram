/**
 * @file tg_db_wrapper.c
 * @date Jun 26, 2015
 * @author sandeep
 */

#include "tg_db_wrapper.h"

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

	Eina_Bool ret = create_table(table_name, col_names, col_types);
	if (!ret) {
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

	ret = create_table(table_name, col_names, col_types);
	if(!ret) {
		// error occured
	}

	eina_list_free(col_names);
	eina_list_free(col_types);

}

Eina_List* get_all_peer_details()
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

	//peer_details = get_values_from_table_sync(db, table_name, col_names, col_types, NULL);
	peer_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, PEER_INFO_TABLE_LAST_MESSAGE_DATE, EINA_FALSE, NULL);

	eina_list_free(col_names);
	eina_list_free(col_types);

	return peer_details;
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


	char* where_clause = (char*)malloc(strlen(BUDDY_INFO_TABLE_REAL_FIRST_NAME) + strlen(" <> ") + strlen("'Telegram'") + 1);
	strcpy(where_clause, BUDDY_INFO_TABLE_REAL_FIRST_NAME);
	strcat(where_clause, " <> ");
	strcat(where_clause, "'Telegram'");


	//user_details = get_values_from_table_sync(db, table_name, col_names, col_types, NULL);
	user_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, BUDDY_INFO_TABLE_PRINT_NAME, EINA_TRUE, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);

	return user_details;
}

char* get_profile_pic_path(int buddy_id)
{
	Eina_List* buddy_details_array = NULL;
	char* profile_pic_path = NULL;

	char* table_name = BUDDY_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, BUDDY_INFO_TABLE_PHOTO_PATH);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);


	char buddy_id_str[50];
	sprintf(buddy_id_str, "%d", buddy_id);

	char* where_clause = (char*)malloc(strlen(BUDDY_INFO_TABLE_BUDDY_ID) + strlen(" = ") + strlen(buddy_id_str) + 1);
	strcpy(where_clause, BUDDY_INFO_TABLE_BUDDY_ID);
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

			for (int i = 0 ; i < eina_list_count(buddy_details_array); i++) {
				void* val = eina_list_nth(buddy_details, i);
				free(val);
			}
			eina_list_free(buddy_details);
		}
		eina_list_free(buddy_details_array);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);

	return profile_pic_path;
}

Eina_List* get_buddy_info(int buddy_id)
{
	Eina_List* user_details = NULL;

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

	where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_UNREAD) + strlen(" = ") + strlen(unread_str) + strlen(" AND ") + strlen(MESSAGE_INFO_TABLE_OUT_MSG) + strlen(" = ") + strlen(out_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_UNREAD);
	strcat(where_clause, " = ");
	strcat(where_clause, unread_str);
	strcat(where_clause, " AND ");
	strcat(where_clause, MESSAGE_INFO_TABLE_OUT_MSG);
	strcat(where_clause, " = ");
	strcat(where_clause, out_str);
	num_of_rows = get_number_of_rows(table_name, where_clause);
	free(where_clause);

	return num_of_rows;
}


tg_message_s* get_latest_message_from_message_table(char* table_name)
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

	message_details = get_values_from_table_sync_order_by(table_name, col_names, col_types, MESSAGE_INFO_TABLE_DATE, EINA_FALSE, NULL);

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

	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		//("error: database creation failed");
	} else {

	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

void insert_media_info_to_db(tg_message_s *M, char* file_path, int width, int height, int size)
{
	if(!M || !file_path) {
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


	int media_type = M->media_type;

	if (media_type == tgl_message_media_photo) {

		col_values = eina_list_append(col_values,M->media_id);
		col_values = eina_list_append(col_values, &(media_type));

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

		double longitude = 0.0f;
		double latitude = 0.0f;

		char long_str[50];
		sprintf(long_str,"%lf",longitude);

		char lat_str[50];
		sprintf(lat_str,"%lf",latitude);

		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, long_str);



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
		col_values = eina_list_append(col_values, &(temp_val));
		col_values = eina_list_append(col_values, &(temp_val));


		col_values = eina_list_append(col_values, "");

		double longitude = 0.0f;
		double latitude = 0.0f;

		char long_str[50];
		sprintf(long_str,"%lf",longitude);

		char lat_str[50];
		sprintf(lat_str,"%lf",latitude);

		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, long_str);
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

	col_values = eina_list_append(col_values, "");

	col_values = eina_list_append(col_values, "");

	col_values = eina_list_append(col_values, "");

	col_values = eina_list_append(col_values, file_path);

	Eina_Bool ret = insert_table(table_name, col_names, col_types,col_values);
	if(!ret) {
		//("error: database creation failed");
	} else {

	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

char* get_image_path_from_db(long long media_id)
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

	vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	eina_list_free(col_types);
	eina_list_free(col_names);

	return vals;
}


