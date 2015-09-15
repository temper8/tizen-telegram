/**
 * @file tg_db_manager.c
 * @date Jun 1, 2015
 * @author sandeep
 */

#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include <sqlite3.h>

#include "tgl.h"
#include "tgl-layout.h"
#include "tg_common.h"
#include "tg_db_manager.h"

int errno;

static struct _info {
	sqlite3 *db;
	const char *database_name;
} s_info = {
	.db = NULL,
	.database_name = DEFAULT_TG_DATABASE_PATH,
};

sqlite3* create_database(char* database_name)
{
	if(!database_name)
		return NULL;

	int ret;
	sqlite3 *db;
	ret = sqlite3_open(database_name, &db);
	//ret = sqlite3_open_v2(database_name, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
	if(ret) {
		return NULL;
	}
	return db;
}

Eina_Bool close_database(sqlite3* db)
{
	if(db) {
		sqlite3_close(db);
		return EINA_TRUE;
	}
	return EINA_FALSE;
}

int tg_db_init(void)
{
	int ret;

	if (s_info.db) {
		return EINA_TRUE;
	}

	ret = sqlite3_open(s_info.database_name, &s_info.db);
	if(ret != SQLITE_OK) {
		return EINA_FALSE;
	}

	return EINA_TRUE;

}

int tg_db_fini(void)
{
	if (!s_info.db) {
		return EINA_FALSE;
	}

	sqlite3_close(s_info.db);
	s_info.db = NULL;
	return EINA_TRUE;
}

static inline int create_table_query_to_db(const char *ddl, const char *table_name)
{
	sqlite3_stmt *stmt;
	int ret;

	ret = sqlite3_prepare_v2(s_info.db, ddl, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return -EIO;
	}

	sqlite3_finalize(stmt);
	return 0;
}

int tg_db_create_table_user_info(const char *table_name)
{
	const char *ddl;

	ddl = "CREATE TABLE ? (" \
			"user_id INTEGER PRIMARY KEY NOT NULL," \
			"print_name TEXT," \
			"structure_version INTEGER," \
			"photo_path TEXT," \
			"photo_id INTEGER," \
			"first_name TEXT," \
			"last_name TEXT," \
			"phone TEXT," \
			"access_hash INTEGER," \
			"real_first_name TEXT," \
			"real_last_name TEXT," \
			"username TEXT," \
			"online INTEGER," \
			"last_seen INTEGER)";

	return create_table_query_to_db(ddl, table_name);
}

int tg_db_create_table_media_info(const char *table_name)
{
	const char *ddl;
	ddl = "CREATE TABLE ? (" \
			"media_id TEXT," \
			"media_type INTEGER," \
			"access_hash TEXT," \
			"user_id INTEGER," \
			"date INTEGER," \
			"caption TEXT," \
			"longitude TEXT," \
			"latitude TEXT," \
			"sizes_num INTEGER," \
			"photo_type1 TEXT," \
			"photo_loc_dc1 INTEGER," \
			"photo_loc_vol1 TEXT," \
			"photo_loc_id1 INTEGER," \
			"photo_loc_secret1 TEXT," \
			"photo_width1 INTEGER," \
			"photo_height1 INTEGER," \
			"photo_size1 INTEGER," \
			"photo_data1 TEXT," \
			"photo_type2 TEXT," \
			"photo_loc_dc2 INTEGER," \
			"photo_loc_vol2 TEXT," \
			"photo_loc_id2 INTEGER," \
			"photo_loc_secret2 TEXT," \
			"photo_width2 INTEGER," \
			"photo_height2 INTEGER," \
			"photo_size2 INTEGER," \
			"photo_data2 TEXT," \
			"photo_type3 TEXT," \
			"photo_loc_dc3 INTEGER," \
			"photo_loc_vol3 TEXT," \
			"photo_loc_id3 INTEGER," \
			"photo_loc_secret3 TEXT," \
			"photo_width3 INTEGER," \
			"photo_height3 INTEGER," \
			"photo_size3 INTEGER," \
			"photo_data3 TEXT," \
			"photo_type4 TEXT," \
			"photo_loc_dc4 INTEGER," \
			"photo_loc_vol4 TEXT," \
			"photo_loc_id4 INTEGER," \
			"photo_loc_secret4 TEXT," \
			"photo_width4 INTEGER," \
			"photo_height4 INTEGER," \
			"photo_size4 INTEGER," \
			"photo_data4 TEXT," \
			"phone TEXT," \
			"first_name TEXT," \
			"last_name TEXT," \
			"file_path TEXT)";
	return create_table_query_to_db(ddl, table_name);
}

int tg_db_update_media_info_filepath(const char *table_name, long long media_id, const char *filepath)
{
	const char *dml;
	const char *id_str;
	int ret;
	sqlite3_stmt *stmt;

	dml = "UPDATE ? SET file_path = ? WHERE media_id = ?";

	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_text(stmt, 2, filepath, -1, SQLITE_TRANSIENT);
	id_str = tg_common_to_string("%lld", media_id);
	ret = sqlite3_bind_text(stmt, 3, id_str, -1, SQLITE_TRANSIENT);
	ret = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	return 0;
}

int tg_db_update_media_info_by_id(const char *table_name, struct tgl_message *msg, long long id)
{
	const char *dml;
	const char *tmp;
	int ret;
	sqlite3_stmt *stmt;
	int i;

	dml = "UPDATE ? SET media_id = ?, "
			"media_type = ?, "
			"access_hash = ?, "
			"user_id = ?, "
			"date = ?, "
			"caption = ?, "
			"longitude = ?, "
			"latitude = ?, "
			"sizes_num = ?, "
			"photo_type1 = ?," \
			"photo_loc_dc1 = ?," \
			"photo_loc_vol1 = ?," \
			"photo_loc_id1 = ?," \
			"photo_loc_secret1 = ?," \
			"photo_width1 = ?," \
			"photo_height1 = ?," \
			"photo_size1 = ?," \
			"photo_data1 = ?," \
			"photo_type2 = ?," \
			"photo_loc_dc2 = ?," \
			"photo_loc_vol2 = ?," \
			"photo_loc_id2 = ?," \
			"photo_loc_secret2 = ?," \
			"photo_width2 = ?," \
			"photo_height2 = ?," \
			"photo_size2 = ?," \
			"photo_data2 = ?," \
			"photo_type3 = ?," \
			"photo_loc_dc3 = ?," \
			"photo_loc_vol3 = ?," \
			"photo_loc_id3 = ?," \
			"photo_loc_secret3 = ?," \
			"photo_width3 = ?," \
			"photo_height3 = ?," \
			"photo_size3 = ?," \
			"photo_data3 = ?," \
			"photo_type4 = ?," \
			"photo_loc_dc4 = ?," \
			"photo_loc_vol4 = ?," \
			"photo_loc_id4 = ?," \
			"photo_loc_secret4 = ?," \
			"photo_width4 = ?," \
			"photo_height4 = ?," \
			"photo_size4 = ?," \
			"photo_data4 = ?," \
			"phone = ?," \
			"first_name = ?," \
			"last_name = ? WHERE media_id = ?";
			/* Except filename */
	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	switch (msg->media.type) {
	case tgl_message_media_photo:
		tmp = tg_common_to_string("%lld", msg->media.photo.id);
		ret = sqlite3_bind_text(stmt, 2, tmp, -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int(stmt, 3, msg->media.type);
		ret = sqlite3_bind_int64(stmt, 4, msg->media.photo.access_hash);
		ret = sqlite3_bind_int(stmt, 5, msg->media.photo.user_id);
		ret = sqlite3_bind_int(stmt, 6, msg->media.photo.date);
		ret = sqlite3_bind_text(stmt, 7, msg->media.photo.caption, -1, SQLITE_TRANSIENT);

		tmp = tg_common_to_string("%lf", msg->media.photo.geo.longitude);
		ret = sqlite3_bind_text(stmt, 8, tmp, -1, SQLITE_TRANSIENT);

		tmp = tg_common_to_string("%lf", msg->media.photo.geo.latitude);
		ret = sqlite3_bind_text(stmt, 9, tmp, -1, SQLITE_TRANSIENT);

		ret = sqlite3_bind_int(stmt, 10, msg->media.photo.sizes_num);
		for (i = 0; i < 4; i++) {
			if (i < msg->media.photo.sizes_num) {
				ret = sqlite3_bind_text(stmt, 11 + (i * 9), msg->media.photo.sizes[i].type, -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 12 + (i * 9), msg->media.photo.sizes[i].loc.dc);
				tmp = tg_common_to_string("%lld", msg->media.photo.sizes[i].loc.volume);
				ret = sqlite3_bind_text(stmt, 13 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 14 + (i * 9), msg->media.photo.sizes[i].loc.local_id);
				tmp = tg_common_to_string("%lld", msg->media.photo.sizes[i].loc.secret);
				ret = sqlite3_bind_text(stmt, 15 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 16 + (i * 9), msg->media.photo.sizes[i].w);
				ret = sqlite3_bind_int(stmt, 17 + (i * 9), msg->media.photo.sizes[i].h);
				ret = sqlite3_bind_int(stmt, 18 + (i * 9), msg->media.photo.sizes[i].size);
				ret = sqlite3_bind_text(stmt, 19 + (i * 9), msg->media.photo.sizes[i].data, -1, SQLITE_TRANSIENT);
			} else {
				ret = sqlite3_bind_text(stmt, 11 + (i * 9), " ", -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 12 + (i * 9), 0);
				tmp = tg_common_to_string("%lld", 0);
				ret = sqlite3_bind_text(stmt, 13 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 14 + (i * 9), 0);
				tmp = tg_common_to_string("%lld", 0);
				ret = sqlite3_bind_text(stmt, 15 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 16 + (i * 9), 0);
				ret = sqlite3_bind_int(stmt, 17 + (i * 9), 0);
				ret = sqlite3_bind_int(stmt, 18 + (i * 9), 0);
				ret = sqlite3_bind_text(stmt, 19 + (i * 9), " ", -1, SQLITE_TRANSIENT);
			}
		}
		break;
	case tgl_message_media_document:
		tmp = tg_common_to_string("%lld", msg->media.document.id);
		ret = sqlite3_bind_text(stmt, 2, tmp, -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int(stmt, 3, msg->media.type);
		ret = sqlite3_bind_int64(stmt, 4, msg->media.document.access_hash);
		ret = sqlite3_bind_int(stmt, 5, msg->media.document.user_id);
		ret = sqlite3_bind_int(stmt, 6, msg->media.document.date);
		ret = sqlite3_bind_text(stmt, 7, msg->media.document.caption, -1, SQLITE_TRANSIENT);
		tmp = tg_common_to_string("%lf", 0.0f);
		ret = sqlite3_bind_text(stmt, 8, tmp, -1, SQLITE_TRANSIENT);
		tmp = tg_common_to_string("%lf", 0.0f);
		ret = sqlite3_bind_text(stmt, 9, tmp, -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int(stmt, 10, msg->media.document.size);
		for (i = 0; i < 4; i++) {
			ret = sqlite3_bind_text(stmt, 11 + (i * 9), " ", -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 12 + (i * 9), 0);
			tmp = tg_common_to_string("%lld", 0);
			ret = sqlite3_bind_text(stmt, 13 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 14 + (i * 9), 0);
			tmp = tg_common_to_string("%lld", 0);
			ret = sqlite3_bind_text(stmt, 15 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 16 + (i * 9), 0);
			ret = sqlite3_bind_int(stmt, 17 + (i * 9), 0);
			ret = sqlite3_bind_int(stmt, 18 + (i * 9), 0);
			ret = sqlite3_bind_text(stmt, 19 + (i * 9), " ", -1, SQLITE_TRANSIENT);
		}
		break;
	default:
		tmp = tg_common_to_string("%lld", 0);
		ret = sqlite3_bind_text(stmt, 2, tmp, -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int(stmt, 3, msg->media.type);
		ret = sqlite3_bind_int64(stmt, 4, 0);
		ret = sqlite3_bind_int(stmt, 5, 0);
		ret = sqlite3_bind_int(stmt, 6, 0);
		ret = sqlite3_bind_text(stmt, 7, " ", -1, SQLITE_TRANSIENT);
		tmp = tg_common_to_string("%lf", 0.0f);
		ret = sqlite3_bind_text(stmt, 8, tmp, -1, SQLITE_TRANSIENT);
		tmp = tg_common_to_string("%lf", 0.0f);
		ret = sqlite3_bind_text(stmt, 9, tmp, -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int(stmt, 10, 0);
		for (i = 0; i < 4; i++) {
			ret = sqlite3_bind_text(stmt, 11 + (i * 9), " ", -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 12 + (i * 9), 0);
			tmp = tg_common_to_string("%lld", 0);
			ret = sqlite3_bind_text(stmt, 13 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 14 + (i * 9), 0);
			tmp = tg_common_to_string("%lld", 0);
			ret = sqlite3_bind_text(stmt, 15 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 16 + (i * 9), 0);
			ret = sqlite3_bind_int(stmt, 17 + (i * 9), 0);
			ret = sqlite3_bind_int(stmt, 18 + (i * 9), 0);
			ret = sqlite3_bind_text(stmt, 19 + (i * 9), " ", -1, SQLITE_TRANSIENT);
		}
		break;
	}

	ret = sqlite3_bind_text(stmt, 46, msg->media.phone, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_text(stmt, 47, msg->media.first_name, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_text(stmt, 48, msg->media.last_name, -1, SQLITE_TRANSIENT);
	tmp = tg_common_to_string("%lld", id);
	ret = sqlite3_bind_text(stmt, 49, tmp, -1, SQLITE_TRANSIENT);

	ret = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (ret != SQLITE_DONE) {
		return -EIO;
	}

	return 0;
}

void *tg_db_get_media_info(const char *table_name, long long id, int *media_type)
{
	void *info = NULL;
	const char *dml;
	sqlite3_stmt *stmt;
	const char *tmp;
	int ret;
	int i;

	if (!media_type || !table_name) {
		return NULL;
	}

	dml = "SELECT * FROM ? WHERE media_id = ?";

	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	tmp = tg_common_to_string("%lld", id);
	ret = sqlite3_bind_text(stmt, 2, tmp, -1, SQLITE_TRANSIENT);
	ret = sqlite3_step(stmt);
	if (ret != SQLITE_ROW) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	*media_type = sqlite3_column_int(stmt, 1);
	if (*media_type == tgl_message_media_photo) {
		struct tgl_photo *photo;
		const char *tmp;

		photo = calloc(1, sizeof(*photo));
		if (!photo) {
			sqlite3_finalize(stmt);
			return NULL;
		}

		tmp = (const char *)sqlite3_column_text(stmt, 0);
		if (tmp && tmp[0] != '\0') {
			if (sscanf(tmp, "%lld", &photo->id) != 1) {

			}
		}

		photo->access_hash = sqlite3_column_int(stmt, 2);
		photo->user_id = sqlite3_column_int(stmt, 3);
		photo->date = sqlite3_column_int(stmt, 4);
		tmp = (const char *)sqlite3_column_text(stmt, 5);
		if (tmp && tmp[0] != '\0') {
			photo->caption = strdup(tmp);
		}

		tmp = (const char *)sqlite3_column_text(stmt, 6);
		if (tmp && tmp[0] != '\0') {
			if (sscanf(tmp, "%lf", &photo->geo.longitude) != 1) {

			}
		}

		tmp = (const char *)sqlite3_column_text(stmt, 7);
		if (tmp && tmp[0] != '\0') {
			if (sscanf(tmp, "%lf", &photo->geo.latitude) != 1) {

			}
		}

		photo->sizes_num = sqlite3_column_int(stmt, 8);
		photo->sizes = calloc(4, sizeof(*photo->sizes));
		for (i = 0; i < photo->sizes_num; i++) {
			if (i < photo->sizes_num) {
				tmp = (const char *)sqlite3_column_text(stmt, 9 + (i * 9));
				if (tmp && tmp[0] != '\0') {
					photo->sizes[i].type = strdup(tmp);
				}
				photo->sizes[i].loc.dc = sqlite3_column_int(stmt, 10 + (i * 9));
				tmp = (const char *)sqlite3_column_text(stmt, 11 + (i * 9));
				if (tmp && tmp[0] != '\0') {
					if (sscanf(tmp, "%lld", &photo->sizes[i].loc.volume) != 1) {

					}
				}
				photo->sizes[i].loc.local_id = sqlite3_column_int(stmt, 12);
				tmp = (const char *)sqlite3_column_text(stmt, 13 + (i * 9));
				if (tmp && tmp[0] != '\0') {
					if (sscanf(tmp, "%lld", &photo->sizes[i].loc.secret) != 1) {

					}
				}
				photo->sizes[i].w = sqlite3_column_int(stmt, 14 + (i * 9));
				photo->sizes[i].h = sqlite3_column_int(stmt, 15 + (i * 9));
				photo->sizes[i].size = sqlite3_column_int(stmt, 16 + (i * 9));

				tmp = (const char *)sqlite3_column_text(stmt, 17 + (i * 9));
				if (tmp && tmp[0] != '\0') {
					photo->sizes[i].data = strdup(tmp);
				}
			}
		}

		// 45: phone
		// 46: first_name
		// 47: last_name
		// 48: file_path
		info = photo;
	} else if (*media_type == tgl_message_media_document) {
		struct tgl_document *document;

		document = calloc(1, sizeof(*document));
		if (!document) {
			sqlite3_finalize(stmt);
			return NULL;
		}

		tmp = (const char *)sqlite3_column_text(stmt, 0);
		if (tmp && tmp[0] != '\0') {
			if (sscanf(tmp, "%lld", &document->id) != 1) {

			}
		}

		tmp = (const char *)sqlite3_column_text(stmt, 2);
		if (tmp && tmp[0] != '\0') {
			if (sscanf(tmp, "%lld", &document->access_hash) != 1) {

			}
		}

		document->user_id = sqlite3_column_int(stmt, 3);
		document->date = sqlite3_column_int(stmt, 4);

		tmp = (const char *)sqlite3_column_text(stmt, 5);
		if (tmp && tmp[0] != '\0') {
			document->caption = strdup(tmp);
		}

		// 6: "longitude TEXT,"
		// 7: "latitude TEXT,"
		// 9 ~ 44: Photo informations

		document->size = sqlite3_column_int(stmt, 8);

		// 45 "phone TEXT,"
		// 46 "first_name TEXT,"
		// 47 "last_name TEXT,"
		// 48 "file_path TEXT)"

		info = document;
	} else {
		/**
		 * @todo
		 * Handles me
		 */
	}

	sqlite3_finalize(stmt);
	return info;
}

int tg_db_insert_media_info(const char *table_name, struct tgl_message *msg, const char *filename)
{
	const char *dml;
	const char *tmp;
	int ret;
	sqlite3_stmt *stmt;
	int i;

	dml = "INSERT INTO ? VALUES (" \
			"?, ?, ?, ?, ?, " \
			"?, ?, ?, ?, ?, " \
			"?, ?, ?, ?, ?, " \
			"?, ?, ?, ?, ?, " \
			"?, ?, ?, ?, ?, " \
			"?, ?, ?, ?, ?, " \
			"?, ?, ?, ?, ?, " \
			"?, ?, ?, ?, ?, " \
			"?, ?, ?, ?, ?, " \
			"?, ?, ?, ?)";
	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);

	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);

	switch (msg->media.type) {
	case tgl_message_media_photo:
		tmp = tg_common_to_string("%lld", msg->media.photo.id);
		ret = sqlite3_bind_text(stmt, 2, tmp, -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int(stmt, 3, msg->media.type);
		ret = sqlite3_bind_int64(stmt, 4, msg->media.photo.access_hash);
		ret = sqlite3_bind_int(stmt, 5, msg->media.photo.user_id);
		ret = sqlite3_bind_int(stmt, 6, msg->media.photo.date);
		ret = sqlite3_bind_text(stmt, 7, msg->media.photo.caption, -1, SQLITE_TRANSIENT);

		tmp = tg_common_to_string("%lf", msg->media.photo.geo.longitude);
		ret = sqlite3_bind_text(stmt, 8, tmp, -1, SQLITE_TRANSIENT);

		tmp = tg_common_to_string("%lf", msg->media.photo.geo.latitude);
		ret = sqlite3_bind_text(stmt, 9, tmp, -1, SQLITE_TRANSIENT);

		ret = sqlite3_bind_int(stmt, 10, msg->media.photo.sizes_num);
		for (i = 0; i < 4; i++) {
			if (i < msg->media.photo.sizes_num) {
				ret = sqlite3_bind_text(stmt, 11 + (i * 9), msg->media.photo.sizes[i].type, -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 12 + (i * 9), msg->media.photo.sizes[i].loc.dc);
				tmp = tg_common_to_string("%lld", msg->media.photo.sizes[i].loc.volume);
				ret = sqlite3_bind_text(stmt, 13 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 14 + (i * 9), msg->media.photo.sizes[i].loc.local_id);
				tmp = tg_common_to_string("%lld", msg->media.photo.sizes[i].loc.secret);
				ret = sqlite3_bind_text(stmt, 15 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 16 + (i * 9), msg->media.photo.sizes[i].w);
				ret = sqlite3_bind_int(stmt, 17 + (i * 9), msg->media.photo.sizes[i].h);
				ret = sqlite3_bind_int(stmt, 18 + (i * 9), msg->media.photo.sizes[i].size);
				ret = sqlite3_bind_text(stmt, 19 + (i * 9), msg->media.photo.sizes[i].data, -1, SQLITE_TRANSIENT);
			} else {
				ret = sqlite3_bind_text(stmt, 11 + (i * 9), " ", -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 12 + (i * 9), 0);
				tmp = tg_common_to_string("%lld", 0);
				ret = sqlite3_bind_text(stmt, 13 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 14 + (i * 9), 0);
				tmp = tg_common_to_string("%lld", 0);
				ret = sqlite3_bind_text(stmt, 15 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
				ret = sqlite3_bind_int(stmt, 16 + (i * 9), 0);
				ret = sqlite3_bind_int(stmt, 17 + (i * 9), 0);
				ret = sqlite3_bind_int(stmt, 18 + (i * 9), 0);
				ret = sqlite3_bind_text(stmt, 19 + (i * 9), " ", -1, SQLITE_TRANSIENT);
			}
		}
		break;
	case tgl_message_media_document:
		tmp = tg_common_to_string("%lld", msg->media.document.id);
		ret = sqlite3_bind_text(stmt, 2, tmp, -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int(stmt, 3, msg->media.type);
		ret = sqlite3_bind_int64(stmt, 4, msg->media.document.access_hash);
		ret = sqlite3_bind_int(stmt, 5, msg->media.document.user_id);
		ret = sqlite3_bind_int(stmt, 6, msg->media.document.date);
		ret = sqlite3_bind_text(stmt, 7, msg->media.document.caption, -1, SQLITE_TRANSIENT);
		tmp = tg_common_to_string("%lf", 0.0f);
		ret = sqlite3_bind_text(stmt, 8, tmp, -1, SQLITE_TRANSIENT);
		tmp = tg_common_to_string("%lf", 0.0f);
		ret = sqlite3_bind_text(stmt, 9, tmp, -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int(stmt, 10, msg->media.document.size);
		for (i = 0; i < 4; i++) {
			ret = sqlite3_bind_text(stmt, 11 + (i * 9), " ", -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 12 + (i * 9), 0);
			tmp = tg_common_to_string("%lld", 0);
			ret = sqlite3_bind_text(stmt, 13 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 14 + (i * 9), 0);
			tmp = tg_common_to_string("%lld", 0);
			ret = sqlite3_bind_text(stmt, 15 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 16 + (i * 9), 0);
			ret = sqlite3_bind_int(stmt, 17 + (i * 9), 0);
			ret = sqlite3_bind_int(stmt, 18 + (i * 9), 0);
			ret = sqlite3_bind_text(stmt, 19 + (i * 9), " ", -1, SQLITE_TRANSIENT);
		}
		break;
	default:
		tmp = tg_common_to_string("%lld", 0);
		ret = sqlite3_bind_text(stmt, 2, tmp, -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int(stmt, 3, msg->media.type);
		ret = sqlite3_bind_int64(stmt, 4, 0);
		ret = sqlite3_bind_int(stmt, 5, 0);
		ret = sqlite3_bind_int(stmt, 6, 0);
		ret = sqlite3_bind_text(stmt, 7, " ", -1, SQLITE_TRANSIENT);
		tmp = tg_common_to_string("%lf", 0.0f);
		ret = sqlite3_bind_text(stmt, 8, tmp, -1, SQLITE_TRANSIENT);
		tmp = tg_common_to_string("%lf", 0.0f);
		ret = sqlite3_bind_text(stmt, 9, tmp, -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int(stmt, 10, 0);
		for (i = 0; i < 4; i++) {
			ret = sqlite3_bind_text(stmt, 11 + (i * 9), " ", -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 12 + (i * 9), 0);
			tmp = tg_common_to_string("%lld", 0);
			ret = sqlite3_bind_text(stmt, 13 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 14 + (i * 9), 0);
			tmp = tg_common_to_string("%lld", 0);
			ret = sqlite3_bind_text(stmt, 15 + (i * 9), tmp, -1, SQLITE_TRANSIENT);
			ret = sqlite3_bind_int(stmt, 16 + (i * 9), 0);
			ret = sqlite3_bind_int(stmt, 17 + (i * 9), 0);
			ret = sqlite3_bind_int(stmt, 18 + (i * 9), 0);
			ret = sqlite3_bind_text(stmt, 19 + (i * 9), " ", -1, SQLITE_TRANSIENT);
		}
		break;
	}

	ret = sqlite3_bind_text(stmt, 46, msg->media.phone, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_text(stmt, 47, msg->media.first_name, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_text(stmt, 48, msg->media.last_name, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_text(stmt, 49, filename, -1, SQLITE_TRANSIENT);

	ret = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	if (ret != SQLITE_DONE) {
		return -EIO;
	}

	return 0;
}

int tg_db_create_table_chat_info(const char *table_name)
{
	const char *ddl;
	ddl = "CREATE TABLE ? (" \
			"chat_id INTEGER PRIMARY KEY NOT NULL," \
			"flags INTEGER," \
			"print_title TEXT," \
			"struct_version INTEGER," \
			"photo_id TEXT," \
			"photo_path TEXT," \
			"title TEXT," \
			"users_num INTEGER," \
			"user_list_size INTEGER," \
			"user_list_version INTEGER," \
			"inviter_id INTEGER," \
			"chat_users TEXT," \
			"date INTEGER," \
			"version INTEGER," \
			"admin_id INTEGER)";
	return create_table_query_to_db(ddl, table_name);
}

int tg_db_count_chat_info(const char *table_name, struct tgl_chat *chat)
{
	const char *dml;
	sqlite3_stmt *stmt;
	int ret;

	dml = "SELECT COUNT(*) FROM ? WHERE chat_id = ?";

	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int(stmt, 2, chat->id.id);
	ret = sqlite3_step(stmt);
	ret = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return ret;
}

int tg_db_update_chat_info(const char *table_name, struct tgl_chat *chat, char *photo)
{
	const char *dml;
	int ret;
	sqlite3_stmt *stmt;
	const char *tmp;
	char *str;
	int i;
	int str_len;
	int str_size;

	dml = "UPDATE ? SET " \
			"chat_id = ?, " \
			"flags = ?, " \
			"print_title = ?, " \
			"struct_version = ?, " \
			"photo_id = ?, " \
			"photo_path = ?, " \
			"title = ?, " \
			"users_num = ?, " \
			"user_list_size = ?, " \
			"user_list_version = ?, " \
			"inviter_id = ?, " \
			"chat_users = ?, " \
			"date = ?, " \
			"version = ?, " \
			"admin_id = ? " \
			"WHERE chat_id = ?";

	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int(stmt, 2, chat->id.id);
	ret = sqlite3_bind_int(stmt, 3, chat->flags);
	ret = sqlite3_bind_text(stmt, 4, chat->print_title, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int(stmt, 5, chat->structure_version);
	tmp = tg_common_to_string("%lld", chat->photo.id);
	ret = sqlite3_bind_text(stmt, 6, tmp, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_text(stmt, 7, photo, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_text(stmt, 8, chat->title, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int(stmt, 9, chat->users_num);
	ret = sqlite3_bind_int(stmt, 10, chat->user_list_size);
	ret = sqlite3_bind_int(stmt, 11, chat->user_list_version);
	ret = sqlite3_bind_int(stmt, 12, chat->user_list[0].inviter_id);

	str_size = 64;
	str_len = 0;
	str = malloc(str_size);
	for (i = 0; i < chat->user_list_size; i++) {
		str_len += snprintf(str + str_len, str_size - str_len - 1, "%d, ", chat->user_list[i].user_id);
		if (str_size - str_len < 32) {
			char *ptr;
			str_size <<= 1; /* doulbing current size */
			ptr = realloc(str, str_size);
			if (!ptr) {
				break;
			}
			str = ptr;
		}
	}
	/* Cut off the last colon */
	str[str_len - 2] = '\0';
	ret = sqlite3_bind_text(stmt, 13, str, str_len - 2, SQLITE_TRANSIENT);
	free(str);
	ret = sqlite3_bind_int(stmt, 14, chat->date);
	ret = sqlite3_bind_int(stmt, 15, chat->version);
	ret = sqlite3_bind_int(stmt, 16, chat->admin_id);
	ret = sqlite3_bind_int(stmt, 17, chat->id.id);

	ret = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	return 0;
}

int tg_db_insert_chat_info(const char *table_name, struct tgl_chat *chat, char *photo_path)
{
	const char *dml;
	int ret;
	sqlite3_stmt *stmt;
	const char *tmp;
	char *str;
	int i;
	int str_len;
	int str_size;

	dml = "INSERT INTO ? VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int(stmt, 2, chat->id.id);
	ret = sqlite3_bind_text(stmt, 3, chat->print_title, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int(stmt, 4, chat->structure_version);
	tmp = tg_common_to_string("%lld", chat->photo.id);
	ret = sqlite3_bind_text(stmt, 5, tmp, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_text(stmt, 6, photo_path, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_text(stmt, 7, chat->title, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int(stmt, 8, chat->users_num);
	ret = sqlite3_bind_int(stmt, 9, chat->user_list_size);
	ret = sqlite3_bind_int(stmt, 10, chat->user_list_version);
	if (chat->user_list) {
		ret = sqlite3_bind_int(stmt, 11, chat->user_list[0].inviter_id);
	} else {
		ret = sqlite3_bind_int(stmt, 11, 0);
	}

	if (chat->user_list_size > 0) {
		str_size = 64;
		str_len = 0;
		str = malloc(str_size);
		for (i = 0; i < chat->user_list_size; i++) {
			str_len += snprintf(str + str_len, str_size - str_len - 1, "%d, ", chat->user_list[i].user_id);
			if (str_size - str_len < 32) {
				char *ptr;
				str_size <<= 1; /* doulbing current size */
				ptr = realloc(str, str_size);
				if (!ptr) {
					break;
				}
				str = ptr;
			}
		}
		/* Cut off the last colon */
		str[str_len - 2] = '\0';
		ret = sqlite3_bind_text(stmt, 12, str, str_len - 2, SQLITE_TRANSIENT);
		free(str);
	} else {
		ret = sqlite3_bind_text(stmt, 12, "", -1, SQLITE_TRANSIENT);
	}
	ret = sqlite3_bind_int(stmt, 13, chat->date);
	ret = sqlite3_bind_int(stmt, 14, chat->version);
	ret = sqlite3_bind_int(stmt, 15, chat->admin_id);

	ret = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	return 0;
}

int tg_db_create_table_message(const char *table_name)
{
	const char *ddl;

	ddl = "CREATE TABLE ? (" \
			"msg_id INTEGER," \
			"flags INTEGER," \
			"fwd_from_id INTEGER," \
			"fwd_date INTEGER," \
			"from_id INTEGER," \
			"to_id INTEGER," \
			"out INTEGER," \
			"unread INTEGER," \
			"date INTEGER," \
			"service INTEGER," \
			"message TEXT," \
			"message_state INTEGER," \
			"message_len INTEGER," \
			"media_type INTEGER," \
			"media_id TEXT," \
			"unique_id INTEGER)";

	return create_table_query_to_db(ddl, table_name);
}

struct tgl_message *tg_db_get_message(const char *table_name, long long id)
{
	struct tgl_message *msg;
	int ret;
	sqlite3_stmt *stmt;
	const char *dml;
	const char *tmp;

	dml = "SELECT * FROM ? WHERE msg_id = ?";

	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return NULL;
	}

	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	ret = sqlite3_bind_int64(stmt, 2, id);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_ROW) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	msg = calloc(1, sizeof(*msg));
	if (!msg) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	msg->id = id;
	msg->flags = sqlite3_column_int(stmt, 1);
	msg->fwd_from_id.id = sqlite3_column_int(stmt, 2);
	msg->fwd_date = sqlite3_column_int(stmt, 3);
	msg->from_id.id = sqlite3_column_int(stmt, 4);
	msg->to_id.id = sqlite3_column_int(stmt, 5);
	msg->out = sqlite3_column_int(stmt, 6);
	msg->unread = sqlite3_column_int(stmt, 7);
	msg->date = sqlite3_column_int(stmt, 8);
	msg->service = sqlite3_column_int(stmt, 9);
	tmp = (const char *)sqlite3_column_text(stmt, 10);
	if (tmp && tmp[0] != '\0') {
		msg->message = strdup(tmp);
		if (!msg->message) {
			/*
			 * @todo
			 */
		}
	}
	msg->msg_state = sqlite3_column_int(stmt, 11);
	msg->message_len = sqlite3_column_int(stmt, 12);
	msg->media.type = sqlite3_column_int(stmt, 13);
	if (msg->media.type == tgl_message_media_photo) {
		msg->media.photo.id = sqlite3_column_int64(stmt, 14);
	} else if (msg->media.type == tgl_message_media_document) {
		msg->media.document.id = sqlite3_column_int64(stmt, 14);
	} else {
		// 14
	}
	//msg->id = sqlite3_column_int64(stmt, 15);
	sqlite3_finalize(stmt);
	return msg;
}

int tg_db_update_message(const char *table_name, struct tgl_message *M, long long unique_id)
{
	int ret;
	sqlite3_stmt *stmt;
	const char *dml;
	dml = "UPDATE ? SET " \
		"msg_id = ?, " \
		"flags = ?, " \
		"fwd_from_id = ?, " \
		"fwd_date = ?, " \
		"from_id = ?, " \
		"to_id = ?, " \
		"out = ?, " \
		"unread = ?, " \
		"date = ?, " \
		"service = ?, " \
		"message = ?, " \
		"message_state = ?, " \
		"message_len = ?, " \
		"media_type = ?, " \
		"media_id = ?, " \
		"WHERE ? = ?";

	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int64(stmt, 2, M->id);
	ret = sqlite3_bind_int(stmt, 3, M->flags);
	ret = sqlite3_bind_int(stmt, 4, M->fwd_from_id.id);
	ret = sqlite3_bind_int(stmt, 5, M->fwd_date);
	ret = sqlite3_bind_int(stmt, 6, M->from_id.id);
	ret = sqlite3_bind_int(stmt, 7, M->to_id.id);
	ret = sqlite3_bind_int(stmt, 8, M->out);
	ret = sqlite3_bind_int(stmt, 9, M->unread);
	ret = sqlite3_bind_int(stmt, 10, M->date);
	ret = sqlite3_bind_int(stmt, 11, M->service);
	ret = sqlite3_bind_text(stmt, 12, M->message, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int(stmt, 13, M->msg_state);
	ret = sqlite3_bind_int(stmt, 14, M->message_len);
	ret = sqlite3_bind_int(stmt, 15, M->media.type);
	if (M->media.type == tgl_message_media_photo) {
		ret = sqlite3_bind_int64(stmt, 16, M->media.photo.id);
	} else if (M->media.type == tgl_message_media_document) {
		ret = sqlite3_bind_int64(stmt, 16, M->media.document.id);
	} else {
		ret = sqlite3_bind_int64(stmt, 17, 0);
	}
	if (unique_id > 0) {
		ret = sqlite3_bind_text(stmt, 18, "unique_id", -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int64(stmt, 19, unique_id);
	} else {
		ret = sqlite3_bind_text(stmt, 18, "msg_id", -1, SQLITE_TRANSIENT);
		ret = sqlite3_bind_int64(stmt, 19, M->id);
	}
	ret = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	return 0;
}

int tg_db_insert_message(const char *table_name, struct tgl_message *M, long long unique_id)
{
	int ret;
	sqlite3_stmt *stmt;
	const char *dml;

	dml = "INSERT INTO ? VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int(stmt, 2, M->id);
	ret = sqlite3_bind_int(stmt, 3, M->flags);
	ret = sqlite3_bind_int(stmt, 4, M->fwd_from_id.id);
	ret = sqlite3_bind_int(stmt, 5, M->fwd_date);
	ret = sqlite3_bind_int(stmt, 6, M->from_id.id);
	ret = sqlite3_bind_int(stmt, 7, M->to_id.id);
	ret = sqlite3_bind_int(stmt, 8, M->out);
	ret = sqlite3_bind_int(stmt, 9, M->unread);
	ret = sqlite3_bind_int(stmt, 10, M->date);
	ret = sqlite3_bind_int(stmt, 11, M->service);
	ret = sqlite3_bind_text(stmt, 12, M->message, -1, SQLITE_TRANSIENT);
	ret = sqlite3_bind_int(stmt, 13, M->msg_state);
	ret = sqlite3_bind_int(stmt, 14, M->message_len);
	ret = sqlite3_bind_int(stmt, 15, M->media.type);
	if (M->media.type == tgl_message_media_photo) {
		ret = sqlite3_bind_int64(stmt, 16, M->media.photo.id);
	} else if (M->media.type == tgl_message_media_document) {
		ret = sqlite3_bind_int64(stmt, 16, M->media.document.id);
	} else {
		ret = sqlite3_bind_int64(stmt, 16, 0);
	}
	ret = sqlite3_bind_int64(stmt, 17, unique_id);

	ret = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	return ret == SQLITE_DONE ? 0 : -EIO;
}

int tg_db_create_table_peer_info(const char *table_name)
{
	const char *ddl;
	ddl = "CREATE TABLE ? (" \
			"user_id INTEGER PRIMARY KEY NOT NULL," \
			"peer_type INTEGER," \
			"flags INTEGER," \
			"message_id TEXT," \
			"message_date INTEGER," \
			"print_name TEXT," \
			"struct_version INTEGER," \
			"unread_message_count INTEGER," \
			"last_seen INTEGER," \
			"photo_path TEXT," \
			"photo_id INTEGER)";
	return create_table_query_to_db(ddl, table_name);
}

int tg_db_update_peer_info(const char *tablename, tgl_peer_t *UC, int last_msg_id, int unread_count)
{
	const char *dml;
	sqlite3_stmt *stmt;
	const char *str;
	int ret;

	dml = "UPDATE ? SET " \
			"peer_type = ?," \
			"flags = ?," \
			"message_id = ?," \
			"message_data = ?," \
			"print_name = ?," \
			"struct_version = ?," \
			"unread_message_count = ?," \
			"last_seen = ?," \
			"photo_path = ?," \
			"photo_id = ? WHERE user_id = ?";

	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 1, tablename, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 2, UC->id.type);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 3, UC->flags);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	str = tg_common_to_string("%d", last_msg_id);
	ret = sqlite3_bind_text(stmt, 4, str, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 5, UC->last ? UC->last->date : 0);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 6, UC->print_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 7, UC->structure_version);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 8, unread_count);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	if (UC->id.type == TGL_PEER_USER ) {
		ret = sqlite3_bind_int(stmt, 9, UC->user.status.when);
	} else if (UC->id.type == TGL_PEER_CHAT ) {
		ret = sqlite3_bind_int(stmt, 9, UC->chat.date);
	} else {
		ret = sqlite3_bind_int(stmt, 9, 0);
	}
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 10, "", -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 11, UC->photo.id);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 12, UC->id.id);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return -EIO;
	}

	sqlite3_finalize(stmt);
	return 0;
}

int tg_db_insert_peer_info(const char *tablename, tgl_peer_t *UC, int last_msg_id, int unread_count)
{
	const char *dml;
	sqlite3_stmt *stmt;
	const char *str;
	int ret;

	dml = "INSERT INTO ? ("
			"user_id,peer_type,flags,message_id,message_date," \
			"print_name,struct_version,unread_message_count,last_seen," \
			"photo_path,photo_id) VALUES (?,?,?,?,?,?,?,?,?,?,?)";

	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 1, tablename, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 2, UC->id.id);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 3, UC->id.type);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 4, UC->flags);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	str = tg_common_to_string("%d", last_msg_id);
	ret = sqlite3_bind_text(stmt, 5, str, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 6, UC->last ? UC->last->date : 0);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 7, UC->print_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 8, UC->structure_version);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 9, unread_count);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	if (UC->id.type == TGL_PEER_USER ) {
		ret = sqlite3_bind_int(stmt, 10, UC->user.status.when);
	} else if (UC->id.type == TGL_PEER_CHAT ) {
		ret = sqlite3_bind_int(stmt, 10, UC->chat.date);
	} else {
		ret = sqlite3_bind_int(stmt, 10, 0);
	}
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 11, "", -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 12, UC->photo.id);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	sqlite3_finalize(stmt);
	return 0;
}

int tg_db_update_user_info(const char *tablename, struct tgl_user *U)
{
	const char *dml;
	sqlite3_stmt *stmt;
	int ret;

	dml = "UPDATE ? SET print_name = ?, structure_version = ?, first_name = ?, last_name = ?, phone = ?, access_hash = ?, real_first_name = ?, real_last_name = ?, username = ?, online = ?, last_seen = ? WHERE user_id = ?";
	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 1, tablename, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 2, U->print_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 3, U->structure_version);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 4, U->first_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 5, U->last_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 6, U->phone, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 7, U->access_hash);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 8, U->real_first_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 9, U->real_last_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 10, U->username, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 11, U->status.online);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 12, U->last->date);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 13, U->id.id);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	sqlite3_finalize(stmt);
	return 0;
}

int tg_db_update_user_photo(const char *tablename, int uid, const char *photo, int photo_id)
{
	const char *dml;
	int ret;
	sqlite3_stmt *stmt;
	int idx;

	if (photo_id < 0) {
		dml = "UPDATE ? SET photo = ?, photo_id = ? WHERE user_id = ?";
	} else {
		dml = "UPDATE ? SET photo = ? WHERE user_id = ?";
	}

	idx = 1;

	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, idx++, tablename, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, idx++, photo, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	if (photo_id >= 0) {
		ret = sqlite3_bind_int(stmt, idx++, photo_id);
	}

	ret = sqlite3_bind_int(stmt, idx++, uid);
	ret = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (ret != SQLITE_DONE) {
		return -EIO;
	}

	return 0;
}

int tg_db_insert_user_info(const char *tablename, struct tgl_user *U)
{
	const char *dml;
	sqlite3_stmt *stmt;
	int ret;

	dml = "INSERT (user_id, print_name, structure_version, first_name, last_name, phone, access_hash, real_first_name, real_last_name, username, online, last_seen) INTO ? VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 1, U->id.id);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 2, U->print_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 3, U->structure_version);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 4, U->first_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 5, U->last_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 6, U->phone, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 7, U->access_hash);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 8, U->real_first_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 9, U->real_last_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_text(stmt, 10, U->username, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 11, U->status.online);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_bind_int(stmt, 12, U->last ? U->last->date : 0);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return -EFAULT;
	}

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return 0;
	}

	sqlite3_finalize(stmt);
	return 0;
}

struct tgl_user *tg_db_get_user_info(const char *table_name, int uid)
{
	const char *dml;
	sqlite3_stmt *stmt;
	int ret;
	struct tgl_user *user_info;
	const char *tmp;

	dml = "SELECT * FROM ?";
	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return NULL;
	}

	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	if ((ret = sqlite3_step(stmt)) != SQLITE_ROW) {
		sqlite3_finalize(stmt);
		return NULL;
	}
	user_info = calloc(1, sizeof(*user_info));
	if (!user_info) {
		/**
		 * @note
		 * Unable to get the record of user info
		 */
		sqlite3_finalize(stmt);
		return NULL;
	}

	user_info->id.id = sqlite3_column_int(stmt, 0);

	tmp = (const char *)sqlite3_column_text(stmt, 1);
	if (tmp && tmp[0] != '\0') {
		user_info->print_name = strdup(tmp);
	}

	user_info->structure_version = sqlite3_column_int(stmt, 2);

	/**
	 * Getting the photo_path. but how can I store this? to where?
	 */
	tmp = (const char *)sqlite3_column_text(stmt, 3);
	if (tmp && tmp[0] != '\0') {
		/*
		 * Where can I get this photo path?
		 */
	}

	user_info->photo_id = sqlite3_column_int(stmt, 4);
	tmp = (const char *)sqlite3_column_text(stmt, 5);
	if (tmp && tmp[0] != '\0') {
		user_info->first_name = strdup(tmp);
	}

	tmp = (const char *)sqlite3_column_text(stmt, 6);
	if (tmp && tmp[0] != '\0') {
		user_info->last_name = strdup(tmp);
	}

	tmp = (const char *)sqlite3_column_text(stmt, 7);
	if (tmp && tmp[0] != '\0') {
		user_info->phone = strdup(tmp);
	}

	user_info->access_hash = sqlite3_column_int(stmt, 8);

	tmp = (const char *)sqlite3_column_text(stmt, 9);
	if (tmp && tmp[0] != '\0') {
		user_info->real_first_name = strdup(tmp);
	}

	tmp = (const char *)sqlite3_column_text(stmt, 10);
	if (tmp && tmp[0] != '\0') {
		user_info->real_last_name = strdup(tmp);
	}

	tmp = (const char *)sqlite3_column_text(stmt, 11);
	if (tmp && tmp[0] != '\0') {
	user_info->username = strdup(tmp);
	}

	sqlite3_finalize(stmt);
	return user_info;
}

Eina_List *tg_db_get_user_list(const char *table_name)
{
	const char *dml;
	sqlite3_stmt *stmt;
	int ret;
	Eina_List *user_list;
	struct tgl_user *user_info;
	const char *tmp;

	dml = "SELECT * FROM ?";
	ret = sqlite3_prepare_v2(s_info.db, dml, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return NULL;
	}

	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	user_list = NULL;
	while ((ret = sqlite3_step(stmt)) == SQLITE_ROW) {
		user_info = calloc(1, sizeof(*user_info));
		if (!user_info) {
			/**
			 * @note
			 * Unable to get the record of user info
			 */
			continue;
		}

		user_info->id.id = sqlite3_column_int(stmt, 0);

		tmp = (const char *)sqlite3_column_text(stmt, 1);
		if (tmp && tmp[0] != '\0') {
			user_info->print_name = strdup(tmp);
		}

		user_info->structure_version = sqlite3_column_int(stmt, 2);

		/**
		 * Getting the photo_path. but how can I store this? to where?
		 */
		tmp = (const char *)sqlite3_column_text(stmt, 3);
		if (tmp && tmp[0] != '\0') {
			/*
			 * Where can I get this photo path?
			 */
		}

		user_info->photo_id = sqlite3_column_int(stmt, 4);
		tmp = (const char *)sqlite3_column_text(stmt, 5);
		if (tmp && tmp[0] != '\0') {
			user_info->first_name = strdup(tmp);
		}

		tmp = (const char *)sqlite3_column_text(stmt, 6);
		if (tmp && tmp[0] != '\0') {
			user_info->last_name = strdup(tmp);
		}

		tmp = (const char *)sqlite3_column_text(stmt, 7);
		if (tmp && tmp[0] != '\0') {
			user_info->phone = strdup(tmp);
		}

		user_info->access_hash = sqlite3_column_int(stmt, 8);

		tmp = (const char *)sqlite3_column_text(stmt, 9);
		if (tmp && tmp[0] != '\0') {
			user_info->real_first_name = strdup(tmp);
		}

		tmp = (const char *)sqlite3_column_text(stmt, 10);
		if (tmp && tmp[0] != '\0') {
			user_info->real_last_name = strdup(tmp);
		}

		tmp = (const char *)sqlite3_column_text(stmt, 11);
		if (tmp && tmp[0] != '\0') {
			user_info->username = strdup(tmp);
		}

		user_list = eina_list_append(user_list, user_info);
	}

	sqlite3_finalize(stmt);
	return user_list;
}
