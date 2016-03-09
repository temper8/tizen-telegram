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

#include "tg_db_wrapper.h"
#include "tg_common.h"
#include "tgl-layout.h"
#include "logger.h"

static const int g_zero_int = 0;
static const int g_base_int = -1;
static const char *g_empty_char = "";
static const char *g_zero_fchar = "0.0";
static const char *g_type_image = "image";
static const char *g_type_audio = "audio";
static const char *g_type_video = "video";
static const char *g_type_sticker = "sticker";
static const char *g_type_doc = "document";
static const char *g_type_none = "none";


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
	if (!ret)
		ERR("Table (%s) creation error!, %d", table_name, ret);

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
	if (!ret)
		ERR("Table (%s) creation error!, %d", table_name, ret);

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
	if (!ret)
		ERR("Table (%s) creation error!, %d", table_name, ret);

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
	if (!ret)
		ERR("Table (%s) creation error!, %d", table_name, ret);

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
	if (!ret)
		ERR("Table (%s) creation error!, %d", table_name, ret);

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
	if (!ret)
		ERR("Table (%s) creation error!, %d", table_name, ret);

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
	if (!ret)
		ERR("Table (%s) creation error!, %d", table_name, ret);

	eina_list_free(col_names);
	eina_list_free(col_types);
}


void delete_message_from_unsent_db(int message_id)
{
	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MESSAGE_TRANSPORT_TABLE_MESSAGE_ID " = %d", message_id);
	delete_record(MESSAGE_TRANSPORT_TABLE_NAME, where_clause);
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

	Eina_List* ts_msg = NULL;
	EINA_LIST_FREE(unsent_msg_details, ts_msg) {

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
	return ret_msg_details;
}

void delete_media_from_unsent_db(int message_id)
{
	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MEDIA_TRANSPORT_TABLE_MESSAGE_ID " = %d", message_id);
	delete_record(MEDIA_TRANSPORT_TABLE_NAME, where_clause);
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

	Eina_List* ts_msg = NULL;
	EINA_LIST_FREE(unsent_msg_details, ts_msg) {
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

	return ret_msg_details;
}


void create_buddy_msg_table(const char* table_name)
{
	if (!table_name)
		return;

	/* create user info table */
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

	Eina_Bool ret = create_table(table_name, col_names, col_types);
	if (!ret)
		ERR("Table (%s) creation error!, %d", table_name, ret);

	eina_list_free(col_names);
	eina_list_free(col_types);
}

void init_date_msg(struct tgl_message *date_msg, int cur_time, long long id)
{
	if (!date_msg)
		return;

	char res[256];
	snprintf(res, sizeof(res), "%d", cur_time);

	memset(date_msg, 0, sizeof(struct tgl_message));

	date_msg->id = id;
	date_msg->media.type = tgl_message_media_none;
	date_msg->date = cur_time;
	date_msg->message = strdup(res);
	date_msg->message_len = strlen(res);
	date_msg->service = 2;
	date_msg->unread = 0;
	date_msg->out = 0;
	date_msg->is_marked_for_delete = 0;
}

int set_date_item_to_table(char* tb_name, int recent_msg_date)
{
	recent_msg_date = recent_msg_date - 1;
	time_t t = recent_msg_date;

	struct tgl_message* last_msg = get_latest_message_from_message_table(tb_name);
	if (!last_msg) {
		struct tgl_message date_msg;
		init_date_msg(&date_msg, recent_msg_date, recent_msg_date);
		insert_msg_into_db(&date_msg, tb_name, t);
		if (date_msg.message)
			free(date_msg.message);
		return date_msg.id;
	}

	int old_date = last_msg->date;
	time_t old_t = old_date;

	free(last_msg->message);
	free(last_msg);

	struct tm old_lt;
	(void) localtime_r(&old_t, &old_lt);

	struct tm new_lt;
	(void) localtime_r(&t, &new_lt);

	if (old_lt.tm_mday == new_lt.tm_mday &&
			old_lt.tm_mon == new_lt.tm_mon &&
			old_lt.tm_year == new_lt.tm_year)
		return -1;

	struct tgl_message date_msg;
	init_date_msg(&date_msg, recent_msg_date, recent_msg_date);
	insert_msg_into_db(&date_msg, tb_name, t);
	if (date_msg.message)
		free(date_msg.message);
	return date_msg.id;
}


int update_current_date_to_table(char* tb_name, int recent_msg_date)
{
	recent_msg_date = recent_msg_date -1;
	time_t t = recent_msg_date;

	struct tgl_message* last_msg = get_latest_message_from_message_table(tb_name);
	if (!last_msg) {
			struct tgl_message date_msg;
			init_date_msg(&date_msg, recent_msg_date, recent_msg_date);
			insert_msg_into_db(&date_msg, tb_name, t);
			if (date_msg.message)
				free(date_msg.message);
			return date_msg.id;
	}

	int old_date = last_msg->date;
	time_t old_t = old_date;

	free(last_msg->message);
	free(last_msg);

	struct tm old_lt;
	(void) localtime_r(&old_t, &old_lt);

	struct tm new_lt;
	(void) localtime_r(&t, &new_lt);

	if (old_lt.tm_mday == new_lt.tm_mday &&
			old_lt.tm_mon == new_lt.tm_mon &&
			old_lt.tm_year == new_lt.tm_year)
		return -1;

	struct tgl_message date_msg;
	init_date_msg(&date_msg, recent_msg_date, recent_msg_date);
	insert_msg_into_db(&date_msg, tb_name, t);
	if (date_msg.message)
		free(date_msg.message);
	return date_msg.id;
}


int insert_current_date_to_table(char* tb_name)
{
	int cur_time = time(NULL) - 1;
	time_t t = cur_time;

	struct tgl_message* last_msg = get_latest_message_from_message_table(tb_name);
	if (!last_msg) {
			struct tgl_message date_msg;
			init_date_msg(&date_msg, cur_time, get_time_stamp_in_macro());
			insert_msg_into_db(&date_msg, tb_name, t);
			if (date_msg.message)
				free(date_msg.message);
			if (date_msg.id < 0)
				date_msg.id = -1 * date_msg.id;
			return date_msg.id;
	}
	int old_date = last_msg->date;
	time_t old_t = old_date;

	free(last_msg->message);
	free(last_msg);

	struct tm old_lt;
	(void) localtime_r(&old_t, &old_lt);

	struct tm new_lt;
	(void) localtime_r(&t, &new_lt);

	if (old_lt.tm_mday == new_lt.tm_mday &&
			old_lt.tm_mon == new_lt.tm_mon &&
			old_lt.tm_year == new_lt.tm_year)
		return -1;

	struct tgl_message date_msg;
	init_date_msg(&date_msg, cur_time, get_time_stamp_in_macro());
	insert_msg_into_db(&date_msg, tb_name, t);
	if (date_msg.message)
		free(date_msg.message);

	if (date_msg.id < 0)
		date_msg.id = -1 * date_msg.id;
	return date_msg.id;
}

Eina_Bool insert_buddy_msg_to_db(struct tgl_message *M)
{
	int t = 0;
	int user_id = 0;
	if (tgl_get_peer_type(M->to_id) == TGL_PEER_USER)
		user_id = M->from_id.id;
	else if (tgl_get_peer_type(M->to_id) == TGL_PEER_CHAT)
		user_id = M->to_id.id;

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

	Eina_List* ts_msg = NULL;
	if (message_details && eina_list_count(message_details) > 0) {
		ts_msg = eina_list_nth(message_details, 0);

		message = (struct tgl_message*)malloc(sizeof(struct tgl_message));
		memset(message, 0, sizeof(struct tgl_message));

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
		/* to do, get media id based on media type */
	}

	EINA_LIST_FREE(message_details, ts_msg) {
		eina_list_free(ts_msg);
	}

	return message;
}


Eina_List* get_all_message_ids_from_table(char *table_name)
{
	if (!table_name)
		return NULL;

	Eina_List *msg_ids = NULL;
	Eina_List *message_details = NULL;
	Eina_List *col_names = NULL;
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ID);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MESSAGE_INFO_TABLE_MARKED_FOR_DELETE " = %d", 1);
	message_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);

	Eina_List* ts_msg = NULL;
	Eina_Bool got_id = false;
	EINA_LIST_FREE(message_details, ts_msg) {
		int *temp_msg_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_msg_id) {
			msg_ids = eina_list_append(msg_ids, (void*)temp_msg_id);
			got_id = true;
		}
		/* there will be only one item in ts_msg. */
		eina_list_free(ts_msg);
	}
	if (got_id)
		return msg_ids;
	else
		return NULL;
}

struct tgl_message* get_message_from_message_tableby_message_id(char *table_name, int msg_id)
{
	if (!table_name)
		return NULL;

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

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MESSAGE_INFO_TABLE_MESSAGE_ID " = %d", msg_id);
	message_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);

	Eina_List* ts_msg;
	if (message_details && eina_list_count(message_details) > 0) {
		ts_msg = eina_list_nth(message_details, 0);
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
		/* to do, get media id based on media type */
	}

	EINA_LIST_FREE(message_details, ts_msg) {
		eina_list_free(ts_msg);
	}
	return message;
}



void update_peer_info_database(tgl_peer_t* UC, int is_unknown)
{
	if (!UC)
		return;

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

	if (UC->last) {
		col_values = eina_list_append(col_values, &(UC->last->date));
	} else {
		int last_msg_date = 0;
		col_values = eina_list_append(col_values, &(last_msg_date));
	}

	col_values = eina_list_append(col_values, UC->print_name ? UC->print_name : g_empty_char);
	col_values = eina_list_append(col_values, &(UC->structure_version));


	if (UC->id.type == TGL_PEER_USER) {
		col_values = eina_list_append(col_values, &(UC->user.status.when));
	} else if (UC->id.type == TGL_PEER_CHAT) {
		col_values = eina_list_append(col_values, &(UC->chat.date));
	} else {
		int last_seen = 0;
		col_values = eina_list_append(col_values, &(last_seen));
	}

	col_values = eina_list_append(col_values, g_empty_char);

	struct tgl_photo* photo = &(UC->photo);
	int photo_id = -1;
	if (photo)
		photo_id = photo->id;

	col_values = eina_list_append(col_values, &(photo_id));
	col_values = eina_list_append(col_values, &(is_unknown));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,  col_values);
	if (!ret) {
		/* already exist. So update the table */
		char where_clause[1024];
		snprintf(where_clause, sizeof(where_clause), PEER_INFO_TABLE_CHAT_ID " = %d", UC->id.id);
		ret = update_table(table_name, col_names, col_types, col_values, where_clause);
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

void delete_chat_from_db(int peer_id)
{
	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), PEER_INFO_TABLE_CHAT_ID " = %d", peer_id);
	delete_record(PEER_INFO_TABLE_NAME, where_clause);
}

void delete_buddy_from_db(int peer_id)
{
	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), USER_INFO_TABLE_USER_ID " = %d", peer_id);
	delete_record(BUDDY_INFO_TABLE_NAME, where_clause);
}

void init_insert_peer_into_database(tgl_peer_t* UC, int last_msg_id, int unread_count, int is_unknown)
{
	if (!UC)
		return;

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
	snprintf(last_msg_id_str, sizeof(last_msg_id_str), "%d", last_msg_id);
	col_values = eina_list_append(col_values, last_msg_id_str);

	if (UC->last) {
		col_values = eina_list_append(col_values, &(UC->last->date));
	} else {
		int last_msg_date = 0;
		col_values = eina_list_append(col_values, &(last_msg_date));
	}

	col_values = eina_list_append(col_values, UC->print_name ? UC->print_name : g_empty_char);
	col_values = eina_list_append(col_values, &(UC->structure_version));
	col_values = eina_list_append(col_values, &(unread_count));

	if (UC->id.type == TGL_PEER_USER) {
		col_values = eina_list_append(col_values, &(UC->user.status.when));
	} else if (UC->id.type == TGL_PEER_CHAT) {
		col_values = eina_list_append(col_values, &(UC->chat.date));
	} else {
		int last_seen = 0;
		col_values = eina_list_append(col_values, &(last_seen));
	}

	col_values = eina_list_append(col_values, g_empty_char);

	struct tgl_photo* photo = &(UC->photo);
	int photo_id = -1;
	if (photo)
		photo_id = photo->id;

	col_values = eina_list_append(col_values, &(photo_id));
	col_values = eina_list_append(col_values, &(is_unknown));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,  col_values);
	if (!ret) {
		/* already exist. So update the table */
		char where_clause[1024];
		snprintf(where_clause, sizeof(where_clause), PEER_INFO_TABLE_CHAT_ID " = %d", UC->id.id);
		ret = update_table(table_name, col_names, col_types, col_values, where_clause);
	}

	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}


void insert_peer_into_database(tgl_peer_t* UC, int last_msg_id, int unread_count, int is_unknown)
{
	if (!UC)
		return;

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
	snprintf(last_msg_id_str, sizeof(last_msg_id_str), "%d", last_msg_id);
	col_values = eina_list_append(col_values, last_msg_id_str);

	if (UC->last) {
		col_values = eina_list_append(col_values, &(UC->last->date));
	} else {
		int last_msg_date = 0;
		col_values = eina_list_append(col_values, &(last_msg_date));
	}

	col_values = eina_list_append(col_values, UC->print_name ? UC->print_name : g_empty_char);
	col_values = eina_list_append(col_values, &(UC->structure_version));
	col_values = eina_list_append(col_values, &(unread_count));

	if (UC->id.type == TGL_PEER_USER) {
		col_values = eina_list_append(col_values, &(UC->user.status.when));
	} else if (UC->id.type == TGL_PEER_CHAT) {
		col_values = eina_list_append(col_values, &(UC->chat.date));
	} else {
		int last_seen = 0;
		col_values = eina_list_append(col_values, &(last_seen));
	}

	col_values = eina_list_append(col_values, g_empty_char);

	struct tgl_photo* photo = &(UC->photo);
	int photo_id = -1;
	if (photo)
		photo_id = photo->id;

	col_values = eina_list_append(col_values, &(photo_id));
	col_values = eina_list_append(col_values, &(is_unknown));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,  col_values);
	if (!ret) {
		/* already exist. So update the table */
		char where_clause[1024];
		snprintf(where_clause, sizeof(where_clause), PEER_INFO_TABLE_CHAT_ID " = %d", UC->id.id);
		ret = update_table(table_name, col_names, col_types, col_values, where_clause);
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

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MESSAGE_INFO_TABLE_MESSAGE_ID " = %lld", msg_id);
	message_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);

	Eina_List* ts_msg;
	if (message_details && eina_list_count(message_details) > 0) {
		ts_msg = eina_list_nth(message_details, 0);
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
		if (message->media.type == tgl_message_media_photo) {
			if (temp_media_id) {
				message->media.photo.id  = strtoll(temp_media_id, &eptr, 10);
				free(temp_media_id);
			}
		} else if (message->media.type == tgl_message_media_document) {
			if (temp_media_id) {
				message->media.document.id  = strtoll(temp_media_id, &eptr, 10);
				free(temp_media_id);
			}
		} else if (message->media.type == tgl_message_media_photo_encr) {
			if (temp_media_id) {
				message->media.encr_photo.id  = strtoll(temp_media_id, &eptr, 10);
				free(temp_media_id);
			}
		} else if (message->media.type == tgl_message_media_document_encr) {
			if (temp_media_id) {
				message->media.encr_document.id  = strtoll(temp_media_id, &eptr, 10);
				free(temp_media_id);
			}
		} else  {
			if (temp_media_id)
				free(temp_media_id);
		}
		int *temp_unique_id = (int*)eina_list_nth(ts_msg, 15);
		if (temp_unique_id)
			free(temp_unique_id);
	}

	EINA_LIST_FREE(message_details, ts_msg) {
		eina_list_free(ts_msg);
	}
	return message;
}

Eina_Bool insert_msg_into_db(struct tgl_message *M, char* table_name, int unique_id)
{
	if (!M)
		return EINA_FALSE;

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

	col_values = eina_list_append(col_values, M->message ? M->message : g_empty_char);
	col_values = eina_list_append(col_values, &(M->msg_state));
	col_values = eina_list_append(col_values, &(M->message_len));
	col_values = eina_list_append(col_values, &(M->media.type));

	char temp_media_id[50];
	if (M->media.type == tgl_message_media_none) {
		col_values = eina_list_append(col_values, (g_empty_char));
	} else if (M->media.type == tgl_message_media_photo) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%lld", M->media.photo.id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else if (M->media.type == tgl_message_media_document) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%lld", M->media.document.id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else if (M->media.type == tgl_message_media_geo) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%lld", M->media.document.id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else if (M->media.type == tgl_message_media_contact) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%d", M->media.user_id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else if (M->media.type == tgl_message_media_unsupported) {
		col_values = eina_list_append(col_values, (g_empty_char));
	} else if (M->media.type == tgl_message_media_photo_encr) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%lld", M->media.encr_photo.id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else if (M->media.type == tgl_message_media_document_encr) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%lld", M->media.encr_document.id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else  {
		col_values = eina_list_append(col_values, g_empty_char);
	}

	col_values = eina_list_append(col_values, &unique_id);
	col_values = eina_list_append(col_values, &(M->is_marked_for_delete));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,  col_values);

	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
	return ret;
}

void update_msg_into_db(struct tgl_message *M, char* table_name, int unique_id)
{
	if (!M)
		return;

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
	if (unique_id != -1)
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
	if (unique_id != -1)
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


	col_values = eina_list_append(col_values, M->message ? M->message : g_empty_char);
	col_values = eina_list_append(col_values, &(M->msg_state));
	col_values = eina_list_append(col_values, &(M->message_len));
	col_values = eina_list_append(col_values, &(M->media.type));

	char temp_media_id[50];
	if (M->media.type == tgl_message_media_none) {
		col_values = eina_list_append(col_values, (g_empty_char));
	} else if (M->media.type == tgl_message_media_photo) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%lld", M->media.photo.id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else if (M->media.type == tgl_message_media_document) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%lld", M->media.document.id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else if (M->media.type == tgl_message_media_geo) {
		col_values = eina_list_append(col_values, (g_empty_char));
	} else if (M->media.type == tgl_message_media_contact) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%d", M->media.user_id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else if (M->media.type == tgl_message_media_unsupported) {
		col_values = eina_list_append(col_values, (g_empty_char));
	} else if (M->media.type == tgl_message_media_photo_encr) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%lld", M->media.encr_photo.id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else if (M->media.type == tgl_message_media_document_encr) {
		snprintf(temp_media_id, sizeof(temp_media_id), "%lld", M->media.document.id);
		col_values = eina_list_append(col_values, temp_media_id);
	} else  {
		col_values = eina_list_append(col_values, (g_empty_char));
	}

	if (unique_id != -1) {
		int u_id = unique_id;
		col_values = eina_list_append(col_values, &u_id);
	}
	char where_clause[1024];
	if (unique_id > 0)
		snprintf(where_clause, sizeof(where_clause), MESSAGE_INFO_TABLE_UNIQUE_ID " = %d", unique_id);
	else
		snprintf(where_clause, sizeof(where_clause), MESSAGE_INFO_TABLE_MESSAGE_ID " = %lld", M->id);
	update_table(table_name, col_names, col_types, col_values, where_clause);

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
	char* table_name = CHAT_INFO_TABLE_NAME;
	int is_exists = EINA_FALSE;

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), CHAT_INFO_TABLE_CHAT_ID " = %d", chat_info->id.id);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, CHAT_INFO_TABLE_TITLE);

	Eina_List* vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	char* chat_name = NULL;

	if (!vals) {
		/* DB error */
		return is_exists;
	} else {
		Eina_List* row_vals = NULL;
		void *val = NULL;
		EINA_LIST_FREE(vals, row_vals) {
			chat_name = (char*)eina_list_nth(row_vals, 0);
			if (!chat_name) {
				/* DB error */
				is_exists = EINA_FALSE;
			} else {
				is_exists = EINA_TRUE;
			}
			val = NULL;
			EINA_LIST_FREE(row_vals, val) {
				if (val) {
					free(val);
					val = NULL;
				}
			}
		}
	}

	if (chat_name)
		free(chat_name);

	return is_exists;
}

void init_insert_buddy_into_db(char* table_name, struct tgl_user* U)
{
	if (!U)
		return;

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
	col_values = eina_list_append(col_values, U->print_name ? U->print_name : g_empty_char);
	col_values = eina_list_append(col_values, &(U->structure_version));
	col_values = eina_list_append(col_values, &(U->photo_id));
	col_values = eina_list_append(col_values, U->first_name ? U->first_name : g_empty_char);
	col_values = eina_list_append(col_values, U->last_name ? U->last_name : g_empty_char);

	char phone_num[256];
	if (U->phone) {
		if (strstr(U->phone, "+") == NULL) {
			strcpy(phone_num, "+");
			strcat(phone_num, U->phone);
		} else {
			strcpy(phone_num, phone_num);
		}
		col_values = eina_list_append(col_values, phone_num);
	} else {
		col_values = eina_list_append(col_values, g_empty_char);
	}

	col_values = eina_list_append(col_values, &(U->access_hash));

	col_values = eina_list_append(col_values, U->real_first_name ? U->real_first_name : g_empty_char);
	col_values = eina_list_append(col_values, U->real_last_name ? U->real_last_name : g_empty_char);
	col_values = eina_list_append(col_values, U->username ? U->username : g_empty_char);
	col_values = eina_list_append(col_values, &(U->status.online));
	col_values = eina_list_append(col_values, &(U->status.when));
	col_values = eina_list_append(col_values, &(U->blocked));
	col_values = eina_list_append(col_values, &(U->is_unknown));

	Eina_Bool ret = insert_table(table_name, col_names, col_types,  col_values);
	if (!ret) {
		/* already exist. So update the table */
		char where_clause[1024];
		snprintf(where_clause, sizeof(where_clause), USER_INFO_TABLE_USER_ID " = %d", U->id.id);
		ret = update_table(table_name, col_names, col_types, col_values, where_clause);
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

void update_buddy_into_db(char* table_name, struct tgl_user* U)
{
	if (!U)
		return;

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

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, &(U->id.id));
	col_values = eina_list_append(col_values, U->print_name ? U->print_name : g_empty_char);
	col_values = eina_list_append(col_values, &(U->structure_version));
	col_values = eina_list_append(col_values, &(U->photo_id));
	col_values = eina_list_append(col_values, U->first_name ? U->first_name : g_empty_char);
	col_values = eina_list_append(col_values, U->last_name ? U->last_name : g_empty_char);

	char phone_num[256];
	if (U->phone) {
		if (strstr(U->phone, "+") == NULL) {
			strcpy(phone_num, "+");
			strcat(phone_num, U->phone);
		} else {
			strcpy(phone_num, phone_num);
		}
		col_values = eina_list_append(col_values, phone_num);
	} else {
		col_values = eina_list_append(col_values, g_empty_char);
	}

	col_values = eina_list_append(col_values, &(U->access_hash));
	col_values = eina_list_append(col_values, U->real_first_name ? U->real_first_name : g_empty_char);
	col_values = eina_list_append(col_values, U->real_last_name ? U->real_last_name : g_empty_char);
	col_values = eina_list_append(col_values, U->username ? U->username : g_empty_char);
	col_values = eina_list_append(col_values, &(U->status.online));
	col_values = eina_list_append(col_values, &(U->status.when));
	col_values = eina_list_append(col_values, &(U->blocked));

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), USER_INFO_TABLE_USER_ID " = %d", U->id.id);
	update_table(table_name, col_names, col_types, col_values, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

void insert_chat_info_to_db(struct tgl_chat *chat_info, char* photo_path)
{
	if (!chat_info)
		return;

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

	col_values = eina_list_append(col_values, chat_info->print_title ? chat_info->print_title : g_empty_char);
	col_values = eina_list_append(col_values, &(chat_info->structure_version));

	long long photo_id = chat_info->photo.id;

	char photo_id_str[50];
	snprintf(photo_id_str, sizeof(photo_id_str), "%lld", photo_id);
	col_values = eina_list_append(col_values, photo_id_str);
	col_values = eina_list_append(col_values, photo_path ? photo_path : g_empty_char);
	col_values = eina_list_append(col_values, chat_info->title ? chat_info->title : g_empty_char);
	col_values = eina_list_append(col_values, &(chat_info->users_num));
	col_values = eina_list_append(col_values, &(chat_info->user_list_size));
	col_values = eina_list_append(col_values, &(chat_info->user_list_version));

	int inventor_id = 0;
	if (chat_info->user_list)
		inventor_id = chat_info->user_list[0].inviter_id;

	col_values = eina_list_append(col_values, &(inventor_id));

	/****** add chat users list ********/
	char* full_ids = NULL;
	if (chat_info->user_list) {
		char* chat_user_ids[chat_info->user_list_size];
		int total_len = 0;
		for (int i = 0; i < chat_info->user_list_size; i++) {
			char temp_user_id[15];
			int temp_id = chat_info->user_list[i].user_id;
			snprintf(temp_user_id, sizeof(temp_user_id), "%d", temp_id);
			chat_user_ids[i] = (char*)malloc(strlen(temp_user_id) + 1);
			strcpy(chat_user_ids[i], temp_user_id);
			total_len = total_len + strlen(temp_user_id);
			total_len = total_len + 1; /* delimitor */
		}

		full_ids = (char*)malloc(total_len);
		for (int i = 0; i < chat_info->user_list_size; i++) {
			if (i == 0)
				strcpy(full_ids, chat_user_ids[i]);
			else
				strcat(full_ids, chat_user_ids[i]);

			if (i < chat_info->user_list_size - 1)
				strcat(full_ids, ",");
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

	Eina_Bool ret = insert_table(table_name, col_names, col_types, col_values);
	if (!ret) {
		char where_clause[1024];
		snprintf(where_clause, sizeof(where_clause), CHAT_INFO_TABLE_CHAT_ID " = %d", chat_info->id.id);
		ret = update_table(table_name, col_names, col_types, col_values, where_clause);
	}
	free(full_ids);
	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

Eina_Bool update_chat_info_to_db(struct tgl_chat *chat_info, char* photo_path)
{
	if (!chat_info || !photo_path)
		return EINA_FALSE;

	char* table_name = CHAT_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, CHAT_INFO_TABLE_PHOTO_PATH);
	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, photo_path);

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), CHAT_INFO_TABLE_CHAT_ID " = %d", chat_info->id.id);
	Eina_Bool ret = update_table(table_name, col_names, col_types, col_values, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

	if (!ret)
		return EINA_FALSE;

	return EINA_TRUE;
}

void update_buddy_pic_db(char* file_path, char* table_name, int id)
{
	if (!file_path || !table_name)
		return;

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_PHOTO_PATH);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, file_path);

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), USER_INFO_TABLE_USER_ID " = %d", id);
	update_table(table_name, col_names, col_types, col_values, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

void update_buddy_block_db(char* table_name, int id, int block)
{
	if (!table_name)
		return;

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_BLOCKED);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, &block);

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), USER_INFO_TABLE_USER_ID " = %d", id);
	update_table(table_name, col_names, col_types, col_values, where_clause);


	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

void update_buddy_delete_db(char* table_name, int id, int delete_item)
{
	if (!table_name)
		return;

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, USER_INFO_TABLE_IS_UNKNOWN_PEER);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, &delete_item);

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), USER_INFO_TABLE_USER_ID " = %d", id);
	update_table(table_name, col_names, col_types, col_values, where_clause);


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

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), USER_INFO_TABLE_USER_ID " = %d", buddy_id);
	user_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);

	return user_details;
}

void update_receive_media_info_in_db(long long media_id, char* file_path)
{
	if (!file_path)
		return;

	char* table_name = MEDIA_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_FILE_PATH);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, file_path);

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MEDIA_INFO_TABLE_MEDIA_ID " = '%lld'", media_id);
	update_table(table_name, col_names, col_types, col_values, where_clause);


	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

void insert_media_info_to_db(struct tgl_message *M, char* file_path)
{
	if (!M)
		return;

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
	int number_of_media = 0;

	char access_hash_str[256];
	char photo_id_str[256];
	char doc_id_str[256];

	char long_str[50];
	char lat_str[50];
	char photo_loc_vol_str[50];
	char photo_loc_sec_str[50];

	char default_id_str[256];

	if (media_type == tgl_message_media_photo) {
		snprintf(photo_id_str, sizeof(photo_id_str), "%lld", M->media.photo.id);

		col_values = eina_list_append(col_values, photo_id_str);
		col_values = eina_list_append(col_values, &media_type);

		snprintf(access_hash_str, sizeof(access_hash_str), "%lld", M->media.photo.access_hash);

		col_values = eina_list_append(col_values, access_hash_str);
		col_values = eina_list_append(col_values, &(M->media.photo.user_id));
		col_values = eina_list_append(col_values, &(M->media.photo.date));
		col_values = eina_list_append(col_values, M->media.photo.caption ? M->media.photo.caption : g_empty_char);

		snprintf(long_str, sizeof(long_str), "%lf", M->media.photo.geo.longitude);
		snprintf(lat_str, sizeof(lat_str), "%lf", M->media.photo.geo.latitude);

		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, lat_str);
		number_of_media = (M->media.photo.sizes_num <= 4) ? M->media.photo.sizes_num : 4;
		col_values = eina_list_append(col_values, &number_of_media);

		int i = 0;
		/* TODO
		 * for (i = 0; i < M->media.photo.sizes_num; i++) {
		 */
		for (i = 0; i < number_of_media; i++) {

			col_values = eina_list_append(col_values, M->media.photo.sizes[i].type ? M->media.photo.sizes[i].type : g_empty_char);
			col_values = eina_list_append(col_values, &(M->media.photo.sizes[i].loc.dc));

			snprintf(photo_loc_vol_str, sizeof(photo_loc_vol_str), "%lld", M->media.photo.sizes[i].loc.volume);
			col_values = eina_list_append(col_values, photo_loc_vol_str);
			col_values = eina_list_append(col_values, &(M->media.photo.sizes[i].loc.local_id));

			snprintf(photo_loc_sec_str, sizeof(photo_loc_sec_str), "%lld", M->media.photo.sizes[i].loc.secret);
			col_values = eina_list_append(col_values, photo_loc_sec_str);
			col_values = eina_list_append(col_values, &(M->media.photo.sizes[i].w));
			col_values = eina_list_append(col_values, &(M->media.photo.sizes[i].h));
			col_values = eina_list_append(col_values, &(M->media.photo.sizes[i].size));
			col_values = eina_list_append(col_values, M->media.photo.sizes[i].data ? M->media.photo.sizes[i].data : g_empty_char);
		}

		int j = i;
		for (j = i; j < 4; j++) {
			col_values = eina_list_append(col_values, g_empty_char); /* photo_type */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_dc */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_id */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_width */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_height */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_size */
			col_values = eina_list_append(col_values, g_empty_char); /* photo_data */
		}
	} else if (media_type == tgl_message_media_document) {

		snprintf(doc_id_str, sizeof(doc_id_str), "%lld", M->media.document.id);

		col_values = eina_list_append(col_values, doc_id_str);
		col_values = eina_list_append(col_values, &(media_type));

		snprintf(access_hash_str, sizeof(access_hash_str), "%lld", M->media.document.access_hash);

		col_values = eina_list_append(col_values, access_hash_str);

		col_values = eina_list_append(col_values, &(M->media.document.user_id));
		col_values = eina_list_append(col_values, &(M->media.document.date));
		col_values = eina_list_append(col_values, M->media.document.caption ? M->media.document.caption : g_empty_char);

		snprintf(long_str, sizeof(long_str), "%lf", M->media.photo.geo.longitude);
		snprintf(lat_str, sizeof(lat_str), "%lf", M->media.photo.geo.latitude);

		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, lat_str);
		col_values = eina_list_append(col_values, &(M->media.document.size));

		col_values = eina_list_append(col_values, M->media.document.thumb.type ? M->media.document.thumb.type : g_empty_char);
		col_values = eina_list_append(col_values, &(M->media.document.thumb.loc.dc));

		snprintf(photo_loc_vol_str, sizeof(photo_loc_vol_str), "%lld", M->media.document.thumb.loc.volume);

		col_values = eina_list_append(col_values, photo_loc_vol_str);
		col_values = eina_list_append(col_values, &(M->media.document.thumb.loc.local_id));

		snprintf(photo_loc_sec_str, sizeof(photo_loc_sec_str), "%lld", M->media.document.thumb.loc.secret);

		col_values = eina_list_append(col_values, photo_loc_sec_str);
		col_values = eina_list_append(col_values, &(M->media.document.thumb.w));
		col_values = eina_list_append(col_values, &(M->media.document.thumb.h));
		col_values = eina_list_append(col_values, &(M->media.document.thumb.size));
		col_values = eina_list_append(col_values, M->media.document.thumb.data ? M->media.document.thumb.data : g_empty_char);

		for (int j = 1; j < 4; j++) {
			col_values = eina_list_append(col_values, g_empty_char); /* photo_type */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_dc */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_id */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_width */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_height */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_size */
			col_values = eina_list_append(col_values, g_empty_char); /* photo_data */
		}
	} else if (media_type == tgl_message_media_geo) {
		/* To be checked */
		snprintf(doc_id_str, sizeof(doc_id_str), "%lld", M->media.document.id);
		col_values = eina_list_append(col_values, doc_id_str);
		col_values = eina_list_append(col_values, &(media_type));
		col_values = eina_list_append(col_values, g_empty_char);
		col_values = eina_list_append(col_values, &(g_base_int));
		col_values = eina_list_append(col_values, &(g_base_int));
		col_values = eina_list_append(col_values, g_empty_char);

		snprintf(long_str, sizeof(long_str), "%2.15f", M->media.geo.longitude);
		snprintf(lat_str, sizeof(lat_str), "%2.15f", M->media.geo.latitude);

		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, lat_str);
		col_values = eina_list_append(col_values, &(g_base_int));

		for (int j = 0; j < 4; j++) {
			col_values = eina_list_append(col_values, g_empty_char); /* photo_type */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_dc */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_id */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_width */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_height */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_size */
			col_values = eina_list_append(col_values, g_empty_char); /* photo_data */
		}
	} else {
		/* To be checked */
		int default_id = time(NULL);
		snprintf(default_id_str, sizeof(default_id_str), "%d", default_id);

		col_values = eina_list_append(col_values, default_id_str);
		col_values = eina_list_append(col_values, &(media_type));
		col_values = eina_list_append(col_values, g_empty_char);
		col_values = eina_list_append(col_values, &(g_base_int));
		col_values = eina_list_append(col_values, &(g_base_int));
		col_values = eina_list_append(col_values, g_empty_char);
		col_values = eina_list_append(col_values, g_zero_fchar);
		col_values = eina_list_append(col_values, g_zero_fchar);
		col_values = eina_list_append(col_values, &(g_base_int));

		for (int j = 0; j < 4; j++) {
			col_values = eina_list_append(col_values, g_empty_char); /* photo_type */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_dc */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_id */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_width */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_height */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_size */
			col_values = eina_list_append(col_values, g_empty_char); /* photo_data */
		}
	}

	/* col_values = eina_list_append(col_values, M->media.phone); */
	col_values = eina_list_append(col_values, g_empty_char);
	/* col_values = eina_list_append(col_values, M->media.first_name); */
	col_values = eina_list_append(col_values, g_empty_char);
	/* col_values = eina_list_append(col_values, M->media.last_name); */
	col_values = eina_list_append(col_values, g_empty_char);
	col_values = eina_list_append(col_values, file_path ? file_path : g_empty_char);

	if (M->media.type == tgl_message_media_document) {
		col_values = eina_list_append(col_values, M->media.document.mime_type ? M->media.document.mime_type : g_empty_char);

		const char * doc_type = NULL;
		if (M->media.document.flags & FLAG_DOCUMENT_IMAGE)
			doc_type = g_type_image;
		else if (M->media.document.flags & FLAG_DOCUMENT_AUDIO)
			doc_type = g_type_audio;
		else if (M->media.document.flags & FLAG_DOCUMENT_VIDEO)
			doc_type = g_type_video;
		else if (M->media.document.flags & FLAG_DOCUMENT_STICKER)
			doc_type = g_type_sticker;
		else
			doc_type = g_type_doc;

		col_values = eina_list_append(col_values, doc_type);
		col_values = eina_list_append(col_values, &(M->media.document.w));
		col_values = eina_list_append(col_values, &(M->media.document.h));
		col_values = eina_list_append(col_values, &(M->media.document.duration));
		col_values = eina_list_append(col_values, &(M->media.document.size));
		col_values = eina_list_append(col_values, &(M->media.document.dc_id));

	} else if (M->media.type == tgl_message_media_document_encr) {
		col_values = eina_list_append(col_values, M->media.encr_document.mime_type ? M->media.encr_document.mime_type : g_empty_char);

		const char * doc_type = NULL;
		if (M->media.encr_document.flags & FLAG_DOCUMENT_IMAGE)
			doc_type = g_type_image;
		else if (M->media.encr_document.flags & FLAG_DOCUMENT_AUDIO)
			doc_type = g_type_audio;
		else if (M->media.encr_document.flags & FLAG_DOCUMENT_VIDEO)
			doc_type = g_type_video;
		else if (M->media.encr_document.flags & FLAG_DOCUMENT_STICKER)
			doc_type = g_type_sticker;
		else
			doc_type = g_type_doc;

		col_values = eina_list_append(col_values, doc_type);
		col_values = eina_list_append(col_values, &(M->media.encr_document.w));
		col_values = eina_list_append(col_values, &(M->media.encr_document.h));
		col_values = eina_list_append(col_values, &(M->media.encr_document.duration));
		col_values = eina_list_append(col_values, &(M->media.encr_document.size));
		col_values = eina_list_append(col_values, &(M->media.encr_document.dc_id));

	} else {
		col_values = eina_list_append(col_values, g_empty_char);

		if (M->media.type == tgl_message_media_photo)
			col_values = eina_list_append(col_values, g_type_image);
		else
			col_values = eina_list_append(col_values, g_type_none);

		col_values = eina_list_append(col_values, &g_zero_int);
		col_values = eina_list_append(col_values, &g_zero_int);
		col_values = eina_list_append(col_values, &g_zero_int);
		col_values = eina_list_append(col_values, &g_zero_int);
		col_values = eina_list_append(col_values, &g_zero_int);
	}

	col_values = eina_list_append(col_values, g_empty_char);

	insert_table(table_name, col_names, col_types,  col_values);

	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

void update_video_thumb_in_db(long long media_id, char* thumb_file)
{
	if (!thumb_file)
		return;

	char* table_name = MEDIA_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_THUMB_FILE);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_values = NULL;
	col_values = eina_list_append(col_values, thumb_file);

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MEDIA_INFO_TABLE_MEDIA_ID " = '%lld'", media_id);
	update_table(table_name, col_names, col_types, col_values, where_clause);


	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);
}

void update_sent_media_info_in_db(struct tgl_message *M, long long unique_val)
{
	if (!M)
		return;

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

	/****************************NEW****************************************/

	Eina_List* col_values = NULL;
	int media_type = M->media.type;
	int number_of_media = 0;

	char photo_id_str[256];
	char access_hash_str[256];
	char long_str[50];
	char lat_str[50];
	char photo_loc_vol_str[50];
	char photo_loc_sec_str[50];
	char doc_id_str[256];

	if (media_type == tgl_message_media_photo) {

		snprintf(photo_id_str, sizeof(photo_id_str), "%lld", M->media.photo.id);

		col_values = eina_list_append(col_values, photo_id_str);
		col_values = eina_list_append(col_values, &(media_type));

		snprintf(access_hash_str, sizeof(access_hash_str), "%lld", M->media.photo.access_hash);

		col_values = eina_list_append(col_values, access_hash_str);
		col_values = eina_list_append(col_values, &(M->media.photo.user_id));
		col_values = eina_list_append(col_values, &(M->media.photo.date));
		col_values = eina_list_append(col_values, M->media.photo.caption ? M->media.photo.caption : g_empty_char);

		snprintf(long_str, sizeof(long_str), "%lf", M->media.photo.geo.longitude);
		snprintf(lat_str, sizeof(lat_str), "%lf", M->media.photo.geo.latitude);

		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, lat_str);

		number_of_media = (M->media.photo.sizes_num <= 4) ? M->media.photo.sizes_num : 4;
		col_values = eina_list_append(col_values, &number_of_media);

		int i = 0;
		/* TODO
		 * for (i = 0; i < M->media.photo.sizes_num; i++) {
		 */
		for (i = 0; i < number_of_media; i++) {
			col_values = eina_list_append(col_values, M->media.photo.sizes[i].type ? M->media.photo.sizes[i].type : g_empty_char);
			col_values = eina_list_append(col_values, &(M->media.photo.sizes[i].loc.dc));
			snprintf(photo_loc_vol_str, sizeof(photo_loc_vol_str), "%lld", M->media.photo.sizes[i].loc.volume);
			col_values = eina_list_append(col_values, photo_loc_vol_str);
			col_values = eina_list_append(col_values, &(M->media.photo.sizes[i].loc.local_id));
			snprintf(photo_loc_sec_str, sizeof(photo_loc_sec_str), "%lld", M->media.photo.sizes[i].loc.secret);
			col_values = eina_list_append(col_values, photo_loc_sec_str);
			col_values = eina_list_append(col_values, &(M->media.photo.sizes[i].w));
			col_values = eina_list_append(col_values, &(M->media.photo.sizes[i].h));
			col_values = eina_list_append(col_values, &(M->media.photo.sizes[i].size));
			col_values = eina_list_append(col_values, M->media.photo.sizes[i].data ? M->media.photo.sizes[i].data : g_empty_char);
		}

		int j = i;
		for (j = i; j < 4; j++) {
			col_values = eina_list_append(col_values, g_empty_char); /* photo_type */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_dc */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_id */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_width */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_height */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_size */
			col_values = eina_list_append(col_values, g_empty_char); /* photo_data */
		}
	} else if (media_type == tgl_message_media_document) {

		snprintf(doc_id_str, sizeof(doc_id_str), "%lld", M->media.document.id);
		col_values = eina_list_append(col_values, doc_id_str);
		col_values = eina_list_append(col_values, &(media_type));
		snprintf(access_hash_str, sizeof(access_hash_str), "%lld", M->media.document.access_hash);

		col_values = eina_list_append(col_values, access_hash_str);
		col_values = eina_list_append(col_values, &(M->media.document.user_id));
		col_values = eina_list_append(col_values, &(M->media.document.date));
		col_values = eina_list_append(col_values, M->media.document.caption ? M->media.document.caption : g_empty_char);

		snprintf(long_str, sizeof(long_str), "%lf", M->media.geo.longitude);
		snprintf(lat_str, sizeof(lat_str), "%lf", M->media.geo.latitude);

		col_values = eina_list_append(col_values, long_str);
		col_values = eina_list_append(col_values, lat_str);
		col_values = eina_list_append(col_values, &(M->media.document.size));
		col_values = eina_list_append(col_values, M->media.document.thumb.type ? M->media.document.thumb.type : g_empty_char);
		col_values = eina_list_append(col_values, &(M->media.document.thumb.loc.dc));

		snprintf(photo_loc_vol_str, sizeof(photo_loc_vol_str), "%lld", M->media.document.thumb.loc.volume);
		col_values = eina_list_append(col_values, photo_loc_vol_str);
		col_values = eina_list_append(col_values, &(M->media.document.thumb.loc.local_id));

		snprintf(photo_loc_sec_str, sizeof(photo_loc_sec_str), "%lld", M->media.document.thumb.loc.secret);
		col_values = eina_list_append(col_values, photo_loc_sec_str);

		col_values = eina_list_append(col_values, &(M->media.document.thumb.w));
		col_values = eina_list_append(col_values, &(M->media.document.thumb.h));
		col_values = eina_list_append(col_values, &(M->media.document.thumb.size));
		col_values = eina_list_append(col_values, M->media.document.thumb.data ? M->media.document.thumb.data : g_empty_char);

		for (int j = 1; j < 4; j++) {
			col_values = eina_list_append(col_values, g_empty_char); /* photo_type */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_dc */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_id */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_width */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_height */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_size */
			col_values = eina_list_append(col_values, g_empty_char); /* photo_data */
		}
	} else {
		/* To be checked */
		col_values = eina_list_append(col_values, &(g_base_int));
		col_values = eina_list_append(col_values, &(media_type));
		col_values = eina_list_append(col_values, &(g_base_int));
		col_values = eina_list_append(col_values, &(g_base_int));
		col_values = eina_list_append(col_values, &(g_base_int));
		col_values = eina_list_append(col_values, g_empty_char);
		col_values = eina_list_append(col_values, g_zero_fchar);
		col_values = eina_list_append(col_values, g_zero_fchar);
		col_values = eina_list_append(col_values, &(g_base_int));

		for (int j = 0; j < 4; j++) {
			col_values = eina_list_append(col_values, g_empty_char); /* photo_type */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_dc */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_loc_id */
			col_values = eina_list_append(col_values, g_empty_char); /*  */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_width */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_height */
			col_values = eina_list_append(col_values, &g_base_int); /* photo_size */
			col_values = eina_list_append(col_values, g_empty_char); /* photo_data */
		}
	}

	/* col_values = eina_list_append(col_values, M->media.phone); */
	col_values = eina_list_append(col_values, g_empty_char);
	/* col_values = eina_list_append(col_values, M->media.first_name); */
	col_values = eina_list_append(col_values, g_empty_char);
	/* col_values = eina_list_append(col_values, M->media.last_name); */
	col_values = eina_list_append(col_values, g_empty_char);

	if (M->media.type == tgl_message_media_document) {
		col_values = eina_list_append(col_values, M->media.document.mime_type ? M->media.document.mime_type : g_empty_char);

		const char * doc_type = NULL;
		if (M->media.document.flags & FLAG_DOCUMENT_IMAGE)
			doc_type = g_type_image;
		else if (M->media.document.flags & FLAG_DOCUMENT_AUDIO)
			doc_type = g_type_audio;
		else if (M->media.document.flags & FLAG_DOCUMENT_VIDEO)
			doc_type = g_type_video;
		else if (M->media.document.flags & FLAG_DOCUMENT_STICKER)
			doc_type = g_type_sticker;
		else
			doc_type = g_type_doc;

		col_values = eina_list_append(col_values, doc_type);
		col_values = eina_list_append(col_values, &(M->media.document.w));
		col_values = eina_list_append(col_values, &(M->media.document.h));
		col_values = eina_list_append(col_values, &(M->media.document.duration));
		col_values = eina_list_append(col_values, &(M->media.document.size));
		col_values = eina_list_append(col_values, &(M->media.document.dc_id));

	} else if (M->media.type == tgl_message_media_document_encr) {
		col_values = eina_list_append(col_values, M->media.encr_document.mime_type ? M->media.encr_document.mime_type : g_empty_char);

		const char * doc_type = NULL;
		if (M->media.encr_document.flags & FLAG_DOCUMENT_IMAGE)
			doc_type = g_type_image;
		else if (M->media.encr_document.flags & FLAG_DOCUMENT_AUDIO)
			doc_type = g_type_audio;
		else if (M->media.encr_document.flags & FLAG_DOCUMENT_VIDEO)
			doc_type = g_type_video;
		else if (M->media.encr_document.flags & FLAG_DOCUMENT_STICKER)
			doc_type = g_type_sticker;
		else
			doc_type = g_type_doc;

		col_values = eina_list_append(col_values, doc_type);
		col_values = eina_list_append(col_values, &(M->media.document.w));
		col_values = eina_list_append(col_values, &(M->media.document.h));
		col_values = eina_list_append(col_values, &(M->media.document.duration));
		col_values = eina_list_append(col_values, &(M->media.document.size));
		col_values = eina_list_append(col_values, &(M->media.document.dc_id));

	} else {

		col_values = eina_list_append(col_values, g_empty_char);

		if (M->media.type == tgl_message_media_photo)
			col_values = eina_list_append(col_values, g_type_image);
		else
			col_values = eina_list_append(col_values, g_type_none);

		col_values = eina_list_append(col_values, &(g_zero_int));
		col_values = eina_list_append(col_values, &(g_zero_int));
		col_values = eina_list_append(col_values, &(g_zero_int));
		col_values = eina_list_append(col_values, &(g_zero_int));
		col_values = eina_list_append(col_values, &(M->media.document.dc_id));
	}

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MEDIA_INFO_TABLE_MEDIA_ID " = '%lld'", unique_val ? unique_val : M->media.photo.id);
	update_table(table_name, col_names, col_types, col_values, where_clause);

	eina_list_free(col_names);
	eina_list_free(col_types);
	eina_list_free(col_values);

}

struct tgl_media* get_media_details_from_db(long long media_id)
{
	Eina_List* img_details = get_image_details_from_db(media_id);
	if (!img_details)
		return NULL;

	struct tgl_media* media_info = (struct tgl_media*)malloc(sizeof(struct tgl_media));
	Eina_List* row_vals = eina_list_nth(img_details, 0);
	char *temp_media_id = (char *)eina_list_nth(row_vals, 0);

	if (temp_media_id) {
		media_info->media_id = atoll(temp_media_id);
		free(temp_media_id);
	} else {
		media_info->media_id = 0;
	}

	int* temp_media_type = (int*)eina_list_nth(row_vals, 1);
	if (temp_media_type) {
		media_info->media_type = *temp_media_type;
		free(temp_media_type);
	} else {
		media_info->media_type = -1;
	}

	char *temp_access_hash = (char *)eina_list_nth(row_vals, 2);
	if (temp_access_hash) {
		media_info->access_hash = atoll(temp_access_hash);
		free(temp_access_hash);
	} else {
		media_info->access_hash = 0;
	}

	int* temp_user_id = (int*)eina_list_nth(row_vals, 3);
	if (temp_user_id) {
		media_info->user_id = *temp_user_id;
		free(temp_user_id);
	} else {
		media_info->user_id = 0;
	}

	int* temp_date = (int*)eina_list_nth(row_vals, 4);
	if (temp_date) {
		media_info->date = *temp_date;
		free(temp_date);
	} else {
		media_info->date = 0;
	}

	char *temp_caption = (char *)eina_list_nth(row_vals, 5);
	if (temp_caption) {
		media_info->caption = strdup(temp_caption);
		free(temp_caption);
	}

	char *temp_longitude = (char *)eina_list_nth(row_vals, 6);
	if (temp_longitude) {
		media_info->longitude = strdup(temp_longitude);
		free(temp_longitude);
	} else {
		media_info->longitude = 0;
	}

	char *temp_latitude = (char *)eina_list_nth(row_vals, 7);
	if (temp_latitude) {
		media_info->latitude = strdup(temp_latitude);
		free(temp_latitude);
	} else {
		media_info->latitude = 0;
	}

	int* temp_sizes = (int*)eina_list_nth(row_vals, 8);
	if (temp_sizes) {
		media_info->sizes = *temp_sizes;
		free(temp_sizes);
	} else {
		media_info->sizes = 0;
	}

	/***************************************************************/

	char *temp_photo_type1 = (char *)eina_list_nth(row_vals, 9);
	if (temp_photo_type1 && strlen(temp_photo_type1) > 0) {
		media_info->photo_type1 = strdup(temp_photo_type1);
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
	if (temp_photo_loc_vol1 && strlen(temp_photo_loc_vol1) > 0) {
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
	if (temp_photo_loc_sec1 && strlen(temp_photo_loc_sec1) > 0) {
		media_info->photo_loc_sec1 = atoll(temp_photo_loc_sec1);
		free(temp_photo_loc_sec1);
	} else {
		media_info->photo_loc_sec1 = 0;
	}

	int* temp_photo_width1 = (int*)eina_list_nth(row_vals, 14);
	if (temp_photo_width1) {
		media_info->photo_width1 = *temp_photo_width1;
		free(temp_photo_width1);
	} else {
		media_info->photo_width1 = 0;
	}

	int* temp_photo_height1 = (int*)eina_list_nth(row_vals, 15);
	if (temp_photo_height1) {
		media_info->photo_height1 = *temp_photo_height1;
		free(temp_photo_height1);
	} else {
		media_info->photo_height1 = 0;
	}

	int* temp_photo_size1 = (int*)eina_list_nth(row_vals, 16);
	if (temp_photo_size1) {
		media_info->photo_size1 = *temp_photo_size1;
		free(temp_photo_size1);
	} else {
		media_info->photo_size1 = 0;
	}

	char *temp_photo_data1 = (char *)eina_list_nth(row_vals, 17);
	if (temp_photo_data1 && strlen(temp_photo_data1) > 0) {
		media_info->photo_data1 = strdup(temp_photo_data1);
		free(temp_photo_data1);
	} else {
		media_info->photo_data1 = 0;
	}

	char *temp_photo_type2 = (char *)eina_list_nth(row_vals, 18);
	if (temp_photo_type2 && strlen(temp_photo_type2) > 0) {
		media_info->photo_type2 = strdup(temp_photo_type2);
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
	if (temp_photo_loc_vol2 && strlen(temp_photo_loc_vol2) > 0) {
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
	if (temp_photo_loc_sec2 && strlen(temp_photo_loc_sec2) > 0) {
		media_info->photo_loc_sec2 = atoll(temp_photo_loc_sec2);
		free(temp_photo_loc_sec2);
	} else {
		media_info->photo_loc_sec2 = 0;
	}

	int* temp_photo_width2 = (int*)eina_list_nth(row_vals, 23);
	if (temp_photo_width2) {
		media_info->photo_width2 = *temp_photo_width2;
		free(temp_photo_width2);
	} else {
		media_info->photo_width2 = 0;
	}

	int* temp_photo_height2 = (int*)eina_list_nth(row_vals, 24);
	if (temp_photo_height2) {
		media_info->photo_height2 = *temp_photo_height2;
		free(temp_photo_height2);
	} else {
		media_info->photo_height2 = 0;
	}

	int* temp_photo_size2 = (int*)eina_list_nth(row_vals, 25);
	if (temp_photo_size2) {
		media_info->photo_size2 = *temp_photo_size2;
		free(temp_photo_size2);
	} else {
		media_info->photo_size2 = 0;
	}

	char *temp_photo_data2 = (char *)eina_list_nth(row_vals, 26);
	if (temp_photo_data2 && strlen(temp_photo_data2) > 0) {
		media_info->photo_data2 = strdup(temp_photo_data2);
		free(temp_photo_data2);
	} else {
		media_info->photo_data2 = 0;
	}

	char *temp_photo_type3 = (char *)eina_list_nth(row_vals, 27);
	if (temp_photo_type3 && strlen(temp_photo_type3) > 0) {
		media_info->photo_type3 = strdup(temp_photo_type3);
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
	if (temp_photo_loc_vol3 && strlen(temp_photo_loc_vol3) > 0) {
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
	if (temp_photo_loc_sec3 && strlen(temp_photo_loc_sec3) > 0) {
		media_info->photo_loc_sec3 = atoll(temp_photo_loc_sec3);
		free(temp_photo_loc_sec3);
	} else {
		media_info->photo_loc_sec3 = 0;
	}

	int* temp_photo_width3 = (int*)eina_list_nth(row_vals, 32);
	if (temp_photo_width3) {
		media_info->photo_width3 = *temp_photo_width3;
		free(temp_photo_width3);
	} else {
		media_info->photo_width3 = 0;
	}

	int* temp_photo_height3 = (int*)eina_list_nth(row_vals, 33);
	if (temp_photo_height3) {
		media_info->photo_height3 = *temp_photo_height3;
		free(temp_photo_height3);
	} else {
		media_info->photo_height3 = 0;
	}

	int* temp_photo_size3 = (int*)eina_list_nth(row_vals, 34);
	if (temp_photo_size3) {
		media_info->photo_size3 = *temp_photo_size3;
		free(temp_photo_size3);
	} else {
		media_info->photo_size3 = 0;
	}

	char *temp_photo_data3 = (char *)eina_list_nth(row_vals, 35);
	if (temp_photo_data3 && strlen(temp_photo_data3) > 0) {
		media_info->photo_data3 = strdup(temp_photo_data3);
		free(temp_photo_data3);
	} else {
		media_info->photo_data3 = 0;
	}

	char *temp_photo_type4 = (char *)eina_list_nth(row_vals, 36);
	if (temp_photo_type4 && strlen(temp_photo_type4) > 0) {
		media_info->photo_type4 = strdup(temp_photo_type4);
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
	if (temp_photo_loc_vol4 && strlen(temp_photo_loc_vol4) > 0) {
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
	if (temp_photo_loc_sec4 && strlen(temp_photo_loc_sec4) > 0) {
		media_info->photo_loc_sec4 = atoll(temp_photo_loc_sec4);
		free(temp_photo_loc_sec4);
	} else {
		media_info->photo_loc_sec4 = 0;
	}


	int* temp_photo_width4 = (int*)eina_list_nth(row_vals, 41);
	if (temp_photo_width4) {
		media_info->photo_width4 = *temp_photo_width4;
		free(temp_photo_width4);
	} else {
		media_info->photo_width4 = 0;
	}


	int* temp_photo_height4 = (int*)eina_list_nth(row_vals, 42);
	if (temp_photo_height4) {
		media_info->photo_height4 = *temp_photo_height4;
		free(temp_photo_height4);
	} else {
		media_info->photo_height4 = 0;
	}

	int* temp_photo_size4 = (int*)eina_list_nth(row_vals, 43);
	if (temp_photo_size4) {
		media_info->photo_size4 = *temp_photo_size4;
		free(temp_photo_size4);
	} else {
		media_info->photo_size4 = 0;
	}


	char *temp_photo_data4 = (char *)eina_list_nth(row_vals, 44);
	if (temp_photo_data4 && strlen(temp_photo_data4) > 0) {
		media_info->photo_data4 = strdup(temp_photo_data4);
		free(temp_photo_data4);
	} else {
		media_info->photo_data4 = 0;
	}

	/**************************************************************/

	char *temp_phone_no = (char *)eina_list_nth(row_vals, 45);

	if (temp_phone_no && strlen(temp_phone_no) > 0) {
		media_info->phone_no = strdup(temp_phone_no);
		free(temp_phone_no);
	} else {
		media_info->phone_no = 0;
	}

	char *temp_first_name = (char *)eina_list_nth(row_vals, 46);

	if (temp_first_name && strlen(temp_first_name) > 0) {
		media_info->first_name = strdup(temp_first_name);
		free(temp_first_name);
	} else {
		media_info->first_name = 0;
	}

	char *temp_last_name = (char *)eina_list_nth(row_vals, 47);

	if (temp_last_name && strlen(temp_last_name) > 0) {
		media_info->last_name = strdup(temp_last_name);
		free(temp_last_name);
	} else {
		media_info->last_name = 0;
	}

	char *temp_file_path = (char *)eina_list_nth(row_vals, 48);

	if (temp_file_path && strlen(temp_file_path) > 0) {
		media_info->file_path = strdup(temp_file_path);
		free(temp_file_path);
	} else {
		media_info->file_path = 0;
	}

	char *temp_mime_type = (char *)eina_list_nth(row_vals, 49);

	if (temp_mime_type && strlen(temp_mime_type) > 0) {
		media_info->mime_type = strdup(temp_mime_type);
		free(temp_mime_type);
	} else {
		media_info->mime_type = 0;
	}

	char *temp_doc_type = (char *)eina_list_nth(row_vals, 50);

	if (temp_doc_type && strlen(temp_doc_type) > 0) {
		media_info->doc_type = strdup(temp_doc_type);
		free(temp_doc_type);
	} else {
		media_info->doc_type = 0;
	}

	int* temp_doc_width = (int*)eina_list_nth(row_vals, 51);
	if (temp_doc_width) {
		media_info->doc_width = *temp_doc_width;
		free(temp_doc_width);
	} else {
		media_info->doc_width = 0;
	}

	int* temp_doc_height = (int*)eina_list_nth(row_vals, 52);
	if (temp_doc_height) {
		media_info->doc_height = *temp_doc_height;
		free(temp_doc_height);
	} else {
		media_info->doc_height = 0;
	}

	int* temp_doc_duration = (int*)eina_list_nth(row_vals, 53);
	if (temp_doc_duration) {
		media_info->doc_duration = *temp_doc_duration;
		free(temp_doc_duration);
	} else {
		media_info->doc_duration = 0;
	}

	int* temp_doc_size = (int*)eina_list_nth(row_vals, 54);
	if (temp_doc_size) {
		media_info->doc_size = *temp_doc_size;
		free(temp_doc_size);
	} else {
		media_info->doc_size = 0;
	}

	int* temp_doc_dc = (int*)eina_list_nth(row_vals, 55);
	if (temp_doc_size) {
		media_info->doc_dc = *temp_doc_dc;
		free(temp_doc_dc);
	} else {
		media_info->doc_dc = 0;
	}

	char* temp_doc_thumb_path = (char*)eina_list_nth(row_vals, 56);
	if (temp_doc_thumb_path) {
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
	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MEDIA_INFO_TABLE_MEDIA_ID " = %lld", media_id);

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
	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MEDIA_INFO_TABLE_MEDIA_ID " = '%lld'", media_id);

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
		/* "DB error" */
		eina_list_free(col_names);
		return;
	} else {
		Eina_List* row_vals = NULL;
		int pos = 0;
		void *val = NULL;
		EINA_LIST_FREE(vals, row_vals) {
			if (pos == 0) {
				char *temp_fname = (char*)eina_list_nth(row_vals, 0);
				*first_name = strdup(temp_fname);
				char *temp_lname = (char*)eina_list_nth(row_vals, 1);
				*last_name = strdup(temp_lname);
				char *temp_pnumber = (char*)eina_list_nth(row_vals, 2);
				*phone_number = strdup(temp_pnumber);
				eina_list_free(row_vals);
			}
			val = NULL;
			EINA_LIST_FREE(row_vals, val) {
				if (val) {
					free(val);
					val = NULL;
				}
			}
			pos++;
		}

	}
	eina_list_free(col_names);
	return;
}

void get_geo_location_from_db(long long media_id, char **latitude, char **longitude)
{
	char* file_path = NULL;
	char* table_name = MEDIA_INFO_TABLE_NAME;
	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MEDIA_INFO_TABLE_MEDIA_ID " = '%lld'", media_id);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LATITUDE);
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_LONGITUDE);

	Eina_List* vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	file_path = NULL;

	if (!vals) {
		/* "DB error" */
		eina_list_free(col_names);
		return;
	}
	Eina_List* row_vals = NULL;
	int pos = 0;
	void *val = NULL;
	EINA_LIST_FREE(vals, row_vals) {
		if (pos == 0) {
			char *temp_lat = (char*)eina_list_nth(row_vals, 0);
			if (temp_lat)
				*latitude = strdup(temp_lat);
			char *temp_long = (char*)eina_list_nth(row_vals, 1);
			if (temp_long)
				*longitude = strdup(temp_long);
		}
		EINA_LIST_FREE(row_vals, val) {
			if (val) {
				free(val);
				val = NULL;
			}
		}
		pos++;
	}

	eina_list_free(col_names);
	return;
}

char* get_video_thumb_path_from_db(long long media_id)
{
	char* file_path = NULL;
	char* table_name = MEDIA_INFO_TABLE_NAME;
	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MEDIA_INFO_TABLE_MEDIA_ID " = '%lld'", media_id);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_TEXT);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MEDIA_INFO_TABLE_DOCUMENT_THUMB_FILE);

	Eina_List* vals = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	file_path = NULL;

	if (!vals) {
		/* "DB error" */
		eina_list_free(col_names);
		return NULL;
	}
	Eina_List* row_vals = NULL;
	int pos = 0;
	void *val = NULL;
	EINA_LIST_FREE(vals, row_vals) {
		if (pos == 0) {
			char *temp_file_path = (char*)eina_list_nth(row_vals, 0);
			if (temp_file_path)
				file_path = strdup(temp_file_path);
		}

		EINA_LIST_FREE(row_vals, val) {
			if (val) {
				free(val);
				val = NULL;
			}
		}
		pos++;
	}

	eina_list_free(col_names);
	return file_path;
}



void get_buddy_contact_details_from_db(int buddy_id, char **first_name, char **last_name, char **phone_number)
{
	char* file_path = NULL;
	char* table_name = BUDDY_INFO_TABLE_NAME;
	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), USER_INFO_TABLE_USER_ID " = '%d'", buddy_id);

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
		/* "DB error" */
		eina_list_free(col_names);
		return;
	}
	Eina_List* row_vals = NULL;
	int pos = 0;
	void *val = NULL;
	EINA_LIST_FREE(vals, row_vals) {
		if (pos == 0) {
			char *temp_fname = (char*)eina_list_nth(row_vals, 0);
			if (temp_fname)
				*first_name = strdup(temp_fname);
			char *temp_lname = (char*)eina_list_nth(row_vals, 1);
			if (temp_lname)
				*last_name = strdup(temp_lname);
			char *temp_pnumber = (char*)eina_list_nth(row_vals, 2);
			if (temp_pnumber)
				*phone_number = strdup(temp_pnumber);
		}
		EINA_LIST_FREE(row_vals, val) {
			if (val) {
				free(val);
				val = NULL;
			}
		}
		pos++;
	}
	eina_list_free(col_names);
	return;
}


int get_unread_message_count(char* table_name)
{
	/* number of rows, having out == 1 and unread == 0 */
	if (!table_name)
		return 0;

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), MESSAGE_INFO_TABLE_UNREAD " = 1 AND " MESSAGE_INFO_TABLE_OUT_MSG " != 1 AND " MESSAGE_INFO_TABLE_SERVICE " < 1 AND "MESSAGE_INFO_TABLE_MARKED_FOR_DELETE " != 1");
	return get_number_of_rows(table_name, where_clause);;
}

int get_number_of_messages(char* table_name)
{
	if (!table_name)
		return 0;

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
	Eina_List* ts_msg = NULL;
	EINA_LIST_FREE(peer_details, ts_msg) {

		int *temp_peer_id = (int*)eina_list_nth(ts_msg, 0);
		if (!temp_peer_id)
			continue;

		int peer_id = *temp_peer_id;
		free(temp_peer_id);
		temp_peer_id = NULL;

		char *msg_table = get_table_name_from_number(peer_id);
		if (!msg_table)
			continue;

		no_of_unread += get_unread_message_count(msg_table);
		free(msg_table);
		eina_list_free(ts_msg);
	}
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

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), USER_INFO_TABLE_USER_ID " = %d", peer_id);
	peer_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	if (peer_details) {
		Eina_List* ts_msg = NULL;
		void *val = NULL;
		EINA_LIST_FREE(peer_details, ts_msg) {
			ret = EINA_TRUE;
			EINA_LIST_FREE(ts_msg, val) {
				if (val) {
					free(val);
					val = NULL;
				}
			}
		}
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	return ret;
}


Eina_List* get_chat_ids_to_be_deleted()
{
	Eina_List* peer_details = NULL;
	char *table_name = PEER_INFO_TABLE_NAME;
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, PEER_INFO_TABLE_CHAT_ID);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), PEER_INFO_TABLE_PEER_TYPE " = 2 AND " USER_INFO_TABLE_IS_UNKNOWN_PEER " = 1");
	peer_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);

	Eina_List *chat_id_list = NULL;

	if (peer_details) {
		Eina_List* id_list = NULL;
		EINA_LIST_FREE(peer_details, id_list) {
			int chat_id = -1;
			if (id_list && eina_list_count(id_list) > 0) {
				int *temp_msg_id = (int*)eina_list_nth(id_list, 0);
				if (temp_msg_id) {
					chat_id  = *temp_msg_id;
					chat_id_list = eina_list_append(chat_id_list, (void*)chat_id);
					free(temp_msg_id);
				}
				eina_list_free(id_list);
			}
		}
	}
	eina_list_free(col_names);
	eina_list_free(col_types);

	return chat_id_list;
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

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), USER_INFO_TABLE_USER_ID " = %d", peer_id);
	peer_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	if (peer_details) {
		Eina_List* ts_msg = NULL;
		void *val = NULL;
		EINA_LIST_FREE(peer_details, ts_msg) {
			ret = EINA_TRUE;
			EINA_LIST_FREE(ts_msg, val) {
				if (val) {
					free(val);
					val = NULL;
				}
			}
		}
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

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), CHAT_INFO_TABLE_CHAT_ID " = %d", peer_id);
	peer_details = get_values_from_table_sync(table_name, col_names, col_types, where_clause);
	if (peer_details) {
		Eina_List* ts_msg = NULL;
		void *val = NULL;
		EINA_LIST_FREE(peer_details, ts_msg) {
			ret = EINA_TRUE;
			EINA_LIST_FREE(ts_msg, val) {
				if (val) {
					free(val);
					val = NULL;
				}
			}
		}
	}
	eina_list_free(col_names);
	eina_list_free(col_types);
	return ret;
}

Eina_Bool delete_message_from_table(char *tablename, int msg_id)
{
	if (!tablename)
		return EINA_FALSE;

	char where_clause[1024];
	snprintf(where_clause, sizeof(where_clause), "DELETE FROM %s WHERE " MESSAGE_INFO_TABLE_MESSAGE_ID " = %d;", tablename, msg_id);
	int ret;
	char* err_msg = 0;
	sqlite3* db = create_database();
	ret = sqlite3_exec(db, where_clause, NULL, NULL, &err_msg);
	close_database(db);
	if (ret != SQLITE_OK) {
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;
}

