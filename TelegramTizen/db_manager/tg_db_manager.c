/**
 * @file tg_db_manager.c
 * @date Jun 1, 2015
 * @auhtor sandeep
 */

#include "tg_db_manager.h"
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include "tg_common.h"

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

Eina_Bool create_table(const char* table_name, Eina_List* column_names, Eina_List* column_types)
{
	if(!table_name || ! column_names || !column_types) {
		return EINA_FALSE;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	int ret = 0 ;
	char* err_msg = 0;
	int col_count = eina_list_count(column_names);

	int str_len = strlen("CREATE TABLE IF NOT EXISTS ") + strlen(table_name) + strlen("(") + 1;
	char* var_query = (char*)malloc(str_len);
	strcpy(var_query,"CREATE TABLE IF NOT EXISTS ");
	strcat(var_query, table_name);
	strcat(var_query, "(");

	for(int col = 0; col < col_count ; col++) {
		char* col_name = eina_list_nth(column_names, col);
		var_query = realloc(var_query, strlen(var_query)+strlen(col_name) + 1);
		strcat(var_query, col_name);
		var_query = realloc(var_query, strlen(var_query)+strlen(" ") + 1);
		strcat(var_query, " ");
		char* col_type = eina_list_nth(column_types, col);
		var_query = realloc(var_query, strlen(var_query)+strlen(col_type) + 1);
		strcat(var_query, col_type);
		if(col < col_count - 1){
			var_query = realloc(var_query, strlen(var_query) + 2);
			strcat(var_query, ",");
		} else {
			var_query = realloc(var_query, strlen(var_query) + 3);
			strcat(var_query, ");");
		}
	}

	ret = sqlite3_exec(db,var_query, NULL, NULL, &err_msg);
	close_database(db);
	if( ret != SQLITE_OK ){
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;
}

Eina_Bool insert_table(const char* table_name, Eina_List* column_names, Eina_List* column_types, Eina_List* column_values)
{
	if( !table_name || ! column_names || !column_types || !column_values) {
		return EINA_FALSE;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	int ret = 0 ;
	char* err_msg = 0;
	int col_count = eina_list_count(column_names);

	int str_len = strlen("INSERT INTO ") + strlen(table_name) + strlen("(") + 1;
	char* var_query = (char*)malloc(str_len);
	strcpy(var_query,"INSERT INTO ");
	strcat(var_query, table_name);
	strcat(var_query, "(");

	for(int col = 0; col < col_count ; col++) {

		char* col_name = eina_list_nth(column_names, col);
		var_query = realloc(var_query, strlen(var_query)+strlen(col_name) + 1);
		strcat(var_query, col_name);

		if(col < col_count - 1){
			var_query = realloc(var_query, strlen(var_query) + 2);
			strcat(var_query, ",");
		} else {
			var_query = realloc(var_query, strlen(var_query) + strlen(") VALUES (") + 1);
			strcat(var_query, ") VALUES (");
		}
	}

	int col_val_count = eina_list_count(column_values);

	for(int col = 0; col < col_val_count ; col++) {

		char* col_type = eina_list_nth(column_types, col);
		char* col_value = NULL;
		if(!strcmp(col_type, "INTEGER") || !strcmp(col_type, "INTEGER PRIMARY KEY NOT NULL")) {
			int* tmp_value = eina_list_nth(column_values, col);

#if 0
			long long val = *tmp_value;
			col_value = (char*)malloc(50);
			//sprintf(col_value, "%lld", *tmp_value);
			sprintf(col_value, "%lld", val);
#endif

			int act_val = (*tmp_value);
			col_value = (char*)malloc(50);
			sprintf(col_value, "%d", act_val);

			var_query = realloc(var_query, strlen(var_query)+strlen(col_value) + 1);
			strcat(var_query, col_value);

		} else if(!strcmp(col_type, "TEXT") || !strcmp(col_type, "TEXT PRIMARY KEY NOT NULL")) {
			char* tmp_value = eina_list_nth(column_values, col);
			col_value = (char*)malloc(strlen(tmp_value) + 1);
			strcpy(col_value,tmp_value);

			var_query = realloc(var_query, strlen(var_query)+strlen("'") + 1);
			strcat(var_query, "'");

			var_query = realloc(var_query, strlen(var_query)+strlen(col_value) + 1);
			strcat(var_query, col_value);

			var_query = realloc(var_query, strlen(var_query)+strlen("'") + 1);
			strcat(var_query, "'");
		}

		if(col < col_count - 1){
			var_query = realloc(var_query, strlen(var_query) + 3);
			strcat(var_query, ", ");
		} else {
			var_query = realloc(var_query, strlen(var_query) + 3);
			strcat(var_query, ");");
		}
		free(col_value);
	}

	ret = sqlite3_exec(db,var_query, NULL, NULL, &err_msg);
	close_database(db);
	if( ret != SQLITE_OK ){
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;

}


Eina_Bool update_table(const char* table_name, Eina_List* column_names, Eina_List* column_types, Eina_List* column_values, const char* where_clause)
{
	if(!table_name || ! column_names || !column_types || !column_values) {
		return EINA_FALSE;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	int ret = 0 ;
	char* err_msg = 0;
	int col_count = eina_list_count(column_names);

	int str_len = strlen("UPDATE ") + strlen(table_name) + strlen(" SET ") + 1;
	char* var_query = (char*)malloc(str_len);
	strcpy(var_query,"UPDATE ");
	strcat(var_query, table_name);
	strcat(var_query, " SET ");


	int col_val_count = eina_list_count(column_values);

	for(int col = 0; col < col_val_count ; col++) {
		char* col_name = eina_list_nth(column_names, col);
		char* col_type = eina_list_nth(column_types, col);

		char* col_value = NULL;
		if(!strcmp(col_type, "INTEGER") || !strcmp(col_type, "INTEGER PRIMARY KEY NOT NULL")) {
			int* tmp_value = eina_list_nth(column_values, col);

			int act_val = (*tmp_value);
			col_value = (char*)malloc(50);
			sprintf(col_value, "%d", act_val);

			var_query = realloc(var_query, strlen(var_query) + strlen(col_name) + strlen(" = ") + strlen(col_value) + 1);
			strcat(var_query, col_name);
			strcat(var_query, " = ");
			strcat(var_query, col_value);

		} else if(!strcmp(col_type, "TEXT") || !strcmp(col_type, "TEXT PRIMARY KEY NOT NULL")) {

			char* tmp_value = eina_list_nth(column_values, col);
			col_value = (char*)malloc(strlen(tmp_value) + 1);
			strcpy(col_value,tmp_value);

			var_query = realloc(var_query, strlen(var_query)+ strlen(col_name) + strlen(" = ")+strlen("'") + 1);
			strcat(var_query, col_name);
			strcat(var_query, " = ");
			strcat(var_query, "'");

			var_query = realloc(var_query, strlen(var_query)+strlen(col_value) + 1);
			strcat(var_query, col_value);

			var_query = realloc(var_query, strlen(var_query)+strlen("'") + 1);
			strcat(var_query, "'");
		}

		if(col < col_count - 1){
			var_query = realloc(var_query, strlen(var_query) + 3);
			strcat(var_query, ", ");
		} else {
			var_query = realloc(var_query, strlen(var_query) + 2);
			strcat(var_query, " ");
		}
		free(col_value);
	}

	var_query = realloc(var_query, strlen(var_query) + strlen(" WHERE ") + strlen(where_clause) + 2);
	strcat(var_query, " WHERE ");
	strcat(var_query, where_clause);
	strcat(var_query, ";");

	ret = sqlite3_exec(db, var_query, NULL, NULL, &err_msg);

	close_database(db);

	if( ret != SQLITE_OK ){
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;

}

Eina_Bool get_values_from_table(const char* table_name, Eina_List* column_names, int (*callback)(void*,int,char**,char**), const char* where_clause, void* data_to_callback)
{
	if (!table_name) {
		return EINA_FALSE;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	/*****No rows identification*****/

	char* row_cnt_qry = (char*)malloc(strlen("SELECT COUNT(*) FROM ") + strlen(table_name) + strlen(";") +1);
	strcpy(row_cnt_qry, "SELECT COUNT(*) FROM ");
	strcat(row_cnt_qry, table_name);
	strcat(row_cnt_qry, ";");

	int no_of_rows = 0;
	//ret = sqlite3_exec(s_info.db,var_query, callback,(void*)s_info.db, &err_msg);

	sqlite3_stmt *stmt;
	if (sqlite3_prepare_v2(db, row_cnt_qry, -1, &stmt, NULL) == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ERROR) {
			no_of_rows = 0;
		} else {
			no_of_rows = sqlite3_column_int(stmt, 0);
		}
		sqlite3_finalize(stmt);
	}
	close_database(db);
	free(row_cnt_qry);
	if(no_of_rows <= 0) {
		return EINA_FALSE;
	}

	/********************************/
	db = create_database(DEFAULT_TG_DATABASE_PATH);
	int ret = 0 ;
	char* err_msg = 0;
	//int col_count = eina_list_count(column_names);

	int str_len = strlen("SELECT ") + 1;
	char* var_query = (char*)malloc(str_len);
	strcpy(var_query,"SELECT ");
	if(!column_names) {
		var_query = realloc(var_query, strlen(var_query) + 3);
		strcat(var_query, "* ");
	} else {

		int col_count = eina_list_count(column_names);
		char* col_name = NULL;
		for(int col = 0; col < col_count ; col++) {
			col_name = eina_list_nth(column_names, col);
			var_query = realloc(var_query, strlen(var_query)+strlen(col_name) + 1);
			strcat(var_query, col_name);
			col_name = NULL;
			var_query = realloc(var_query, strlen(var_query)+strlen(" ") + 1);

			if(col < col_count - 1){
				var_query = realloc(var_query, strlen(var_query) + 3);
				strcat(var_query, ", ");
			} else {
				var_query = realloc(var_query, strlen(var_query) + 2);
				strcat(var_query, " ");
			}
		}

	}

	var_query = realloc(var_query, strlen(var_query) + strlen("FROM ") + 2);
	strcat(var_query, "FROM ");
	var_query = realloc(var_query, strlen(var_query) + strlen(table_name) + 1);
	strcat(var_query, table_name);

	if (where_clause) {
		var_query = realloc(var_query, strlen(var_query)+strlen(" WHERE ") + 1);
		strcat(var_query, " WHERE ");
		var_query = realloc(var_query, strlen(var_query)+strlen(where_clause) + 1);
		strcat(var_query, where_clause);
	}

	var_query = realloc(var_query, strlen(var_query) + 2);
	strcat(var_query, ";");


	ret = sqlite3_exec(db,var_query, callback,(void*)data_to_callback, &err_msg);
	close_database(db);
	if( ret != SQLITE_OK ){
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}

	free(var_query);
	return EINA_TRUE;
}

int get_number_of_rows(char* table_name, char* where_clause)
{
	int no_of_rows = 0;
	if (!table_name) {
		return no_of_rows;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	char* row_cnt_qry = (char*)malloc(strlen("SELECT COUNT(*) FROM ") + strlen(table_name) + 1);
	strcpy(row_cnt_qry, "SELECT COUNT(*) FROM ");
	strcat(row_cnt_qry, table_name);

	if (where_clause) {
		row_cnt_qry = realloc(row_cnt_qry, strlen(row_cnt_qry)+strlen(" WHERE ") + 1);
		strcat(row_cnt_qry, " WHERE ");
		row_cnt_qry = realloc(row_cnt_qry, strlen(row_cnt_qry)+strlen(where_clause) + 1);
		strcat(row_cnt_qry, where_clause);
	}
	row_cnt_qry = realloc(row_cnt_qry, strlen(row_cnt_qry) + 2);
	strcat(row_cnt_qry, ";");

	sqlite3_stmt *stmt;
	if (sqlite3_prepare_v2(db, row_cnt_qry, -1, &stmt, NULL) == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ERROR) {
			no_of_rows = 0;
		} else {
			no_of_rows = sqlite3_column_int(stmt, 0);
		}
		sqlite3_finalize(stmt);
	}
	close_database(db);
	free(row_cnt_qry);
	return no_of_rows;
}

Eina_List* get_values_from_table_sync_order_by(const char* table_name, Eina_List* column_names, Eina_List* column_types, const char* order_column, Eina_Bool is_asc, const char* where_clause)
{
	Eina_List* query_vals = NULL;

	if (!table_name) {
		return NULL;
	}
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	/*****No rows identification*****/

	char* row_cnt_qry = (char*)malloc(strlen("SELECT COUNT(*) FROM ") + strlen(table_name) + strlen(";") +1);
	strcpy(row_cnt_qry, "SELECT COUNT(*) FROM ");
	strcat(row_cnt_qry, table_name);
	strcat(row_cnt_qry, ";");

	int no_of_rows = 0;
	//ret = sqlite3_exec(s_info.db,var_query, callback,(void*)s_info.db, &err_msg);

	sqlite3_stmt *stmt;
	if (sqlite3_prepare_v2(db, row_cnt_qry, -1, &stmt, NULL) == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ERROR) {
			no_of_rows = 0;
		} else {
			no_of_rows = sqlite3_column_int(stmt, 0);
		}
		sqlite3_finalize(stmt);
	}
	close_database(db);
	free(row_cnt_qry);
	if(no_of_rows <= 0) {
		return NULL;
	}

	/********************************/
	db = create_database(DEFAULT_TG_DATABASE_PATH);
	int ret = 0 ;
	char* err_msg = 0;
	//int col_count = eina_list_count(column_names);

	int str_len = strlen("SELECT ") + 1;
	char* var_query = (char*)malloc(str_len);
	strcpy(var_query,"SELECT ");
	if(!column_names) {
		var_query = realloc(var_query, strlen(var_query) + 3);
		strcat(var_query, "* ");
	} else {

		int col_count = eina_list_count(column_names);
		char* col_name = NULL;
		for(int col = 0; col < col_count ; col++) {
			col_name = eina_list_nth(column_names, col);
			var_query = realloc(var_query, strlen(var_query)+strlen(col_name) + 1);
			strcat(var_query, col_name);
			col_name = NULL;
			var_query = realloc(var_query, strlen(var_query)+strlen(" ") + 1);

			if(col < col_count - 1){
				var_query = realloc(var_query, strlen(var_query) + 3);
				strcat(var_query, ", ");
			} else {
				var_query = realloc(var_query, strlen(var_query) + 2);
				strcat(var_query, " ");
			}
		}

	}

	var_query = realloc(var_query, strlen(var_query) + strlen("FROM ") + 2);
	strcat(var_query, "FROM ");
	var_query = realloc(var_query, strlen(var_query) + strlen(table_name) + 1);
	strcat(var_query, table_name);

	if (where_clause) {
		var_query = realloc(var_query, strlen(var_query)+strlen(" WHERE ") + 1);
		strcat(var_query, " WHERE ");
		var_query = realloc(var_query, strlen(var_query)+strlen(where_clause) + 1);
		strcat(var_query, where_clause);
	}

	if (order_column) {
		var_query = realloc(var_query, strlen(var_query)+strlen(" ORDER BY ") + 1);
		strcat(var_query, " ORDER BY ");
		var_query = realloc(var_query, strlen(var_query)+strlen(order_column) + 1);
		strcat(var_query, order_column);
		if (is_asc) {
			var_query = realloc(var_query, strlen(var_query)+strlen(" ASC ") + 1);
			strcat(var_query, " ASC ");
		} else {
			var_query = realloc(var_query, strlen(var_query)+strlen(" DESC ") + 1);
			strcat(var_query, " DESC ");
		}
	}



	var_query = realloc(var_query, strlen(var_query) + 2);
	strcat(var_query, ";");


	ret = sqlite3_prepare_v2(db, var_query, -1, &stmt, 0);
	if( ret != SQLITE_OK ){
		sqlite3_free(err_msg);
		return NULL;
	}

	while(sqlite3_step(stmt) == SQLITE_ROW) {
		int col_val_count = eina_list_count(column_names);
		Eina_List* row_vals = NULL;
		for(int col = 0; col < col_val_count ; col++) {
			char* col_type = eina_list_nth(column_types, col);
			if(!strcmp(col_type, "INTEGER") || !strcmp(col_type, "INTEGER PRIMARY KEY NOT NULL")) {
				int temp = sqlite3_column_int64(stmt, col);
				int* val_int = (int*)malloc(sizeof(int));
				*val_int = temp;
				row_vals = eina_list_append(row_vals, val_int);
			} else if(!strcmp(col_type, "TEXT") || !strcmp(col_type, "TEXT PRIMARY KEY NOT NULL")) {
				char* val_text = strdup((const char *)sqlite3_column_text(stmt, col));
				row_vals = eina_list_append(row_vals, val_text);
			}
		}
		query_vals = eina_list_append(query_vals, row_vals);
	}
    close_database(db);
	free(var_query);
	return query_vals;

}

Eina_List* get_values_from_table_sync(const char* table_name, Eina_List* column_names, Eina_List* column_types, const char* wc)
{
	sqlite3_stmt *stmt;
	const char *name;
	int query_len;
	Eina_List *l;
	Eina_List *result = NULL;
	Eina_List *record;
	char *query;
	char *ptr;
	int ret;
	const char *type;
	int col;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	char* where_clause = NULL;

	if (wc) {
		where_clause = (char*)malloc(strlen("WHERE ") + strlen(wc) + 1);
		strcpy(where_clause, "WHERE ");
		strcat(where_clause, wc);
	}


	if (!table_name || !column_names) {
		return NULL;
	}

	query_len = strlen("SELECT ");
	EINA_LIST_FOREACH(column_names, l, name) {
		query_len += strlen(name) + 2; /* ", " */
	}

	query_len += strlen(" FROM ");
	query_len += strlen(table_name) + 1;
	query_len += (where_clause ? strlen(where_clause) : 0);
	query_len += 2;

	query = malloc(query_len);
	if (!query) {
		return NULL;
	}

	strcpy(query, "SELECT ");
	ptr = query +strlen("SELECT ");

	if (column_names) {
		EINA_LIST_FOREACH(column_names, l, name) {
			ptr += sprintf(ptr, "%s, ", name);
		}
		ptr -= 2; /* Delete last two characters, ", " */
	} else {
		strcpy(ptr, "*");
		ptr++;
	}

	ptr += sprintf(ptr, " FROM %s %s;", table_name, where_clause ? where_clause : "");

	LOGD("Query: %s", query);

	ret = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	free(query);
	if (ret != SQLITE_OK) {
		close_database(db);
		return NULL;
	}


	while(sqlite3_step(stmt) == SQLITE_ROW) {
		col = 0;
		record = NULL;
		EINA_LIST_FOREACH(column_types, l, type) {
			if (!type) {
				/**
				 * @note
				 * Not possible
				 */
				continue;
			}

			if (!strncmp(type, "INTEGER", strlen("INTEGER"))) {
				int temp;
				int *val;

				temp = sqlite3_column_int64(stmt, col);
				val = malloc(sizeof(int));
				if (!val) {
					/**
					 * @todo
					 * Handling exceptional cases.
					 */
				}
				*val = temp;

				record = eina_list_append(record, val);
			} else if (!strncmp(type, "TEXT", strlen("TEXT"))) {
				char *val;
				const char *text;

				text = (const char *)sqlite3_column_text(stmt, col);
				if (!text || text[0] == '\0') {
					val = strdup("_null_");
				} else {
					val = strdup(text);
				}
				if (!val) {
					/**
					 * @todo
					 * Handling exceptional cases
					 */
				} else {
					record = eina_list_append(record, val);
				}
			}
			col++;
		}
		result = eina_list_append(result, record);
	}

	sqlite3_finalize(stmt);

	if (where_clause) {
		free(where_clause);
		where_clause = NULL;
	}
	close_database(db);
	return result;
}


int tg_db_init(void)
{
	int ret;

	if (s_info.db) {
		LOGD("Already initialized");
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


Eina_List *tg_db_get_user_info(tgl_peer_id_t *user_id)
{
	user_data_s *info;
	Eina_List *result;
	sqlite3_stmt *stmt;
	int ret;
	const char *val_text;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	ret = sqlite3_prepare_v2(db, "SELECT " \
				"print_name, structure_version, " \
				"photo_path, photo_id, " \
				"first_name, last_name, " \
				"phone, access_hash, " \
				"real_first_name, real_last_name, " \
				"username, online, last_seen " \
				"FROM user_info_table WHERE user_id = ?", -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return NULL;
	}

	ret = sqlite3_bind_int(stmt, 1, user_id->id);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	result = NULL;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		info = calloc(1, sizeof(*info));
		if (!info) {
			/**
			 * @todo
			 * Handling the OOM
			 */
			LOGE("calloc: %d", errno);
			continue;
		}

		val_text = (const char *)sqlite3_column_text(stmt, 0);
		if (val_text && val_text[0] != '\0') {
			info->print_name = strdup(val_text);
			if (!info->print_name) {
				LOGE("strdup: %d", errno);
			}
		}

		info->structure_version = sqlite3_column_int(stmt, 1);
		val_text = (const char *)sqlite3_column_text(stmt, 2);
		if (val_text && val_text[0] != '\0') {
			info->photo_path = strdup(val_text);
			if (!info->photo_path) {
				LOGE("strdup: %d", errno);
			}
		}

		info->photo_id = sqlite3_column_int(stmt, 3);

		val_text = (const char *)sqlite3_column_text(stmt, 4);
		if (val_text && val_text[0] != '\0') {
			info->first_name = strdup(val_text);
			if (!info->first_name) {
				LOGE("strdup: %d", errno);
			}
		}

		val_text = (const char *)sqlite3_column_text(stmt, 5);
		if (val_text && val_text[0] != '\0') {
			info->last_name = strdup(val_text);
			if (!info->last_name) {
				LOGE("strdup: %d", errno);
			}
		}

		val_text = (const char *)sqlite3_column_text(stmt, 6);
		if (val_text && val_text[0] != '\0') {
			info->phone = strdup(val_text);
			if (!info->phone) {
				LOGE("strdup: %d", errno);
			}
		}

		info->access_hash = sqlite3_column_int(stmt, 7);

		val_text = (const char *)sqlite3_column_text(stmt, 8);
		if (val_text && val_text[0] != '\0') {
			info->real_first_name = strdup(val_text);
			if (!info->real_first_name) {
				LOGE("strdup: %d", errno);
			}
		}

		val_text = (const char *)sqlite3_column_text(stmt, 9);
		if (val_text && val_text[0] != '\0') {
			info->real_last_name = strdup(val_text);
			if (!info->real_last_name) {
				LOGE("strdup: %d", errno);
			}
		}

		val_text = (const char *)sqlite3_column_text(stmt, 10);
		if (val_text && val_text[0] != '\0') {
			info->username = strdup(val_text);
			if (!info->username) {
				LOGE("strdup: %d", errno);
			}
		}

		info->online = sqlite3_column_int(stmt, 11);
		info->last_seen = sqlite3_column_int(stmt, 12);

		memcpy(&info->user_id, user_id, sizeof(*user_id));

		result = eina_list_append(result, info);
	}
	close_database(db);
	sqlite3_finalize(stmt);
	return result;
}

Eina_List *tg_db_get_chat_info(const char *table_name)
{
	Eina_List *result = NULL;
	tg_chat_info_s *info;
	sqlite3_stmt *stmt;
	const char *tmp;
	int ret;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	ret = sqlite3_prepare_v2(db, "SELECT chat_id, " \
			"flags, print_title, struct_version, " \
			"photo_id, photo_path, " \
			"title, " \
			"users_num, user_list_size, user_list_version, " \
			"inviter_id, chat_users, date, version, admin_id FROM ?", -1, &stmt, NULL);

	if (ret != SQLITE_OK) {
		LOGE("Failed to create a stmt");
		return NULL;
	}

	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		LOGE("Failed to bind a text");
		return NULL;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		info = calloc(1, sizeof(*info));
		if (!info) {
			LOGE("calloc: %d", errno);
			continue;
		}
		info->chat_id = sqlite3_column_int(stmt, 0);
		info->flags = sqlite3_column_int(stmt, 1);
		tmp = (const char *)sqlite3_column_text(stmt, 2);
		if (tmp && tmp[0] != '\0') {
			info->print_title = strdup(tmp);
			if (!info->print_title) {
				LOGE("strdup: %d", errno);
			}
		}
		info->struct_version = sqlite3_column_int(stmt, 3);
		info->photo_id = sqlite3_column_int64(stmt, 4);
		tmp = (const char *)sqlite3_column_text(stmt, 5);
		if (tmp && tmp[0] != '\0') {
			info->photo_path = strdup(tmp);
			if (!info->photo_path) {
				LOGE("strdup: %d", errno);
			}
		}
		tmp = (const char *)sqlite3_column_text(stmt, 6);
		if (tmp && tmp[0] != '\0') {
			info->title = strdup(tmp);
			if (!info->title) {
				LOGE("strdup: %d", errno);
			}
		}
		info->users_num = sqlite3_column_int(stmt, 7);
		info->user_list_size = sqlite3_column_int(stmt, 8);
		info->user_list_version = sqlite3_column_int(stmt, 9);
		info->inviter_id = sqlite3_column_int(stmt, 10);

		tmp = (const char *)sqlite3_column_text(stmt, 11);
		if (tmp && tmp[0] != '\0') {
			char *ptr;

			ptr = strdup(tmp);
			if (ptr) {
				char *tmp_ptr;
				int i;

				for (i = 0; i < info->users_num && *ptr && i < (sizeof(info->chat_users) / sizeof(int)); i++) {
					tmp_ptr = ptr;

					while (*tmp_ptr != ',' && *tmp_ptr != '\0') {
						tmp_ptr++;
					}
					*tmp_ptr = '\0';

					info->chat_users[i] = atoi(ptr);
					ptr = tmp_ptr + 1;
				}

				if (i != info->users_num) {
					/**
					 * There is some problem.
					 * The count of loaded user is not correct.
					 * Fix it forcely.
					 */
					LOGD("Update user_num: %d -> %d", info->users_num, i);
					info->users_num = i;
				}

				free(ptr);
			}
		}

		info->date = sqlite3_column_int(stmt, 12);
		info->version = sqlite3_column_int(stmt, 13);
		info->admin_id = sqlite3_column_int(stmt, 14);
		result = eina_list_append(result, info);
	}

	sqlite3_finalize(stmt);
	close_database(db);
	return result;
}

tg_peer_info_s *tg_db_get_peer_info(const char *table, int peer_id)
{
	tg_peer_info_s *info;
	sqlite3_stmt *stmt;
	const char *tmp;
	int ret;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	ret = sqlite3_prepare_v2(db, "SELECT peer_type, flags, last_msg_id, last_msg_date, print_name, struct_version, no_of_unread_msgs, last_seen_time, photo_path, photo_id FROM ? WHERE peer_id = ?", -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return NULL;
	}

	ret = sqlite3_bind_text(stmt, 1, table, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	ret = sqlite3_bind_int(stmt, 2, peer_id);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	if (sqlite3_step(stmt) != SQLITE_ROW) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	info = calloc(1, sizeof(*info));
	if (!info) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	info->peer_id = peer_id;
	info->peer_type = sqlite3_column_int(stmt, 0);
	info->flags = sqlite3_column_int(stmt, 1);
	info->last_msg_id = sqlite3_column_int64(stmt, 2);
	info->last_msg_date = sqlite3_column_int(stmt, 3);
	tmp = (const char *)sqlite3_column_text(stmt, 4);
	if (tmp && tmp[0] != '\0') {
		info->print_name = strdup(tmp);
		if (!info->print_name) {
			LOGE("strdup: %d", errno);
		}
	}
	info->struct_version = sqlite3_column_int(stmt, 5);
	info->no_of_unread_msgs = sqlite3_column_int(stmt, 6);
	info->last_seen_time = sqlite3_column_int(stmt, 7);

	tmp = (const char *)sqlite3_column_text(stmt, 8);
	if (tmp && tmp[0] != '\0') {
		info->photo_path = strdup(tmp);
		if (!info->photo_path) {
			LOGE("strdup: %d\n", errno);
		}
	}

	info->photo_id = sqlite3_column_int64(stmt, 9);

	sqlite3_finalize(stmt);
	close_database(db);
	return info;
}

Eina_List *tg_db_get_messages(const char *table_name)
{
	Eina_List *result;
	tg_message_s *info;
	sqlite3_stmt *stmt;
	const char *tmp;
	int ret;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	ret = sqlite3_prepare_v2(db, "SELECT msg_id, flags, fwd_from_id, fwd_date, from_id, to_id, out, unread, date, service, message, msg_state, message_len, media_type, media_id, unique_id FROM ?", -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		return NULL;
	}

	ret = sqlite3_bind_text(stmt, 1, table_name, -1, SQLITE_TRANSIENT);
	if (ret != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return NULL;
	}

	result = NULL;
	while (sqlite3_step(stmt) == SQLITE_OK) {
		info = calloc(1, sizeof(*info));
		if (!info) {
			LOGE("calloc: %d", errno);
			continue;
		}

		info->msg_id = sqlite3_column_int(stmt, 0);
		info->flags = sqlite3_column_int(stmt, 1);
		info->fwd_from_id = sqlite3_column_int(stmt, 2);
		info->fwd_date = sqlite3_column_int(stmt, 3);
		info->from_id = sqlite3_column_int(stmt, 4);
		info->to_id = sqlite3_column_int(stmt, 5);
		info->out = sqlite3_column_int(stmt, 6);
		info->unread = sqlite3_column_int(stmt, 7);
		info->date = sqlite3_column_int(stmt, 8);
		info->service = sqlite3_column_int(stmt, 9);
		tmp = (const char *)sqlite3_column_text(stmt, 10);
		if (tmp && tmp[0] != '\0') {
			info->message = strdup(tmp);
			if (!info->message) {
				LOGE("strdup: %d", errno);
			}
		}
		info->msg_state = sqlite3_column_int(stmt, 11);
		info->message_len = sqlite3_column_int(stmt, 12);
		info->media_type = sqlite3_column_int(stmt, 13);
		tmp = (const char *)sqlite3_column_text(stmt, 14);
		if (tmp && tmp[0] != '\0') {
			info->media_id = strdup(tmp);
			if (!info->media_id) {
				LOGE("strdup: %d", errno);
			}
		}
		info->unique_id = sqlite3_column_int(stmt, 15);
		result = eina_list_append(result, info);

	}
	sqlite3_finalize(stmt);
	close_database(db);
	return result;
}

char *tg_db_get_image_path_from_db(int media_id)
{
	return NULL;
}
