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

#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include "tg_db_manager.h"
#include "tg_common.h"
#include "tg_engine.h"
#include "logger.h"

static const Eina_Bool is_use_persistent_db_open = EINA_FALSE;

static struct _info {
	sqlite3 *db;
} tg_db_info = {
		.db = NULL,
};

sqlite3 *create_database()
{
	int ret;
	sqlite3 *db = NULL;
	static char dbfile[PATH_MAX];

	snprintf(dbfile, sizeof(dbfile), "%s" DB_FILENAME, app_get_data_path());
	if (is_use_persistent_db_open) {
		if (tg_db_info.db)
			return tg_db_info.db;

		ret = sqlite3_open(dbfile, &tg_db_info.db);
		if (ret) {
			LOGE("DB creation failed in the persistent connection");
			return tg_db_info.db = NULL;
		}
	} else {
		ret = sqlite3_open(dbfile, &db);
		sqlite3_busy_timeout(db, 3000);
		if (ret) {
			LOGE("DB creation failed");
			return NULL;
		}
	}

	if (is_use_persistent_db_open)
		return tg_db_info.db;
	else
		return db;
}

void close_database(sqlite3 *db)
{
	if (!is_use_persistent_db_open)
		if (db)
			sqlite3_close(db);
}

int tg_db_init(void)
{
	if (is_use_persistent_db_open)
		create_database();
	return EINA_TRUE;
}

void tg_db_fini(void)
{
	if (is_use_persistent_db_open) {
		if (tg_db_info.db)
			sqlite3_close(tg_db_info.db);
		tg_db_info.db = NULL;
	}
}

Eina_Bool create_table(const char *table_name, Eina_List *column_names, Eina_List *column_types)
{
	if (!table_name || ! column_names || !column_types)
		return EINA_FALSE;

	sqlite3 *db = create_database();
	if (!db)
		return EINA_FALSE;

	int ret = 0 ;
	char *err_msg = 0;
	int col_count = eina_list_count(column_names);

	int str_len = strlen("CREATE TABLE IF NOT EXISTS ") + strlen(table_name) + strlen("(") + 1;
	char *var_query = (char*)malloc(str_len);
	if (!var_query) {
		close_database(db);
		return EINA_FALSE;
	}

	strcpy(var_query, "CREATE TABLE IF NOT EXISTS ");
	strcat(var_query, table_name);
	strcat(var_query, "(");

	for (int col = 0; col < col_count; col++) {
		char *col_name = eina_list_nth(column_names, col);
		var_query = realloc(var_query, strlen(var_query)+strlen(col_name) + 1);
		strcat(var_query, col_name);
		var_query = realloc(var_query, strlen(var_query)+strlen(" ") + 1);
		strcat(var_query, " ");
		char *col_type = eina_list_nth(column_types, col);
		var_query = realloc(var_query, strlen(var_query)+strlen(col_type) + 1);
		strcat(var_query, col_type);
		if (col < col_count - 1) {
			var_query = realloc(var_query, strlen(var_query) + 2);
			strcat(var_query, ",");
		} else {
			var_query = realloc(var_query, strlen(var_query) + 3);
			strcat(var_query, ");");
		}
	}

	ret = sqlite3_exec(db, var_query, NULL, NULL, &err_msg);
	close_database(db);
	free(var_query);
	if (ret != SQLITE_OK) {
		LOGE("DB Error : %s", err_msg);
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;
}

Eina_Bool insert_table(const char *table_name, Eina_List *column_names, Eina_List *column_types, Eina_List *column_values)
{
	if (!table_name || ! column_names || !column_types || !column_values)
		return EINA_FALSE;

	sqlite3 *db = create_database();
	if (!db)
		return EINA_FALSE;

	int ret = 0 ;
	char *err_msg = 0;
	int col_count = eina_list_count(column_names);

	int str_len = strlen("INSERT INTO ") + strlen(table_name) + strlen("(") + 1;
	char *var_query = (char*)malloc(str_len);
	if (!var_query) {
		close_database(db);
		return EINA_FALSE;
	}

	strcpy(var_query, "INSERT INTO ");
	strcat(var_query, table_name);
	strcat(var_query, "(");

	for (int col = 0; col < col_count; col++) {

		char *col_name = eina_list_nth(column_names, col);
		var_query = realloc(var_query, strlen(var_query)+strlen(col_name) + 1);
		strcat(var_query, col_name);

		if (col < col_count - 1) {
			var_query = realloc(var_query, strlen(var_query) + 2);
			strcat(var_query, ",");
		} else {
			var_query = realloc(var_query, strlen(var_query) + strlen(") VALUES (") + 1);
			strcat(var_query, ") VALUES (");
		}
	}

	int col_val_count = eina_list_count(column_names);

	for (int col = 0; col < col_val_count; col++) {

		char *col_type = eina_list_nth(column_types, col);
		char *col_value = NULL;
		if (!strcmp(col_type, "INTEGER") || !strcmp(col_type, "INTEGER PRIMARY KEY NOT NULL")) {
			int *tmp_value = eina_list_nth(column_values, col);

			int act_val = (*tmp_value);
			col_value = (char*)malloc(50);
			snprintf(col_value, 50, "%d", act_val);

			var_query = realloc(var_query, strlen(var_query)+strlen(col_value) + 1);
			strcat(var_query, col_value);

		} else if (!strcmp(col_type, "TEXT") || !strcmp(col_type, "TEXT PRIMARY KEY NOT NULL")) {
			char *tmp_value = eina_list_nth(column_values, col);
			col_value = (char*)malloc(strlen(tmp_value) + 1);
			strcpy(col_value, tmp_value);

			var_query = realloc(var_query, strlen(var_query)+strlen("'") + 1);
			strcat(var_query, "'");

			var_query = realloc(var_query, strlen(var_query)+strlen(col_value) + 1);
			strcat(var_query, col_value);

			var_query = realloc(var_query, strlen(var_query)+strlen("'") + 1);
			strcat(var_query, "'");
		}

		if (col < col_count - 1) {
			var_query = realloc(var_query, strlen(var_query) + 3);
			strcat(var_query, ", ");
		} else {
			var_query = realloc(var_query, strlen(var_query) + 3);
			strcat(var_query, ");");
		}
		free(col_value);
	}

	ret = sqlite3_exec(db, var_query, NULL, NULL, &err_msg);
	close_database(db);
	free(var_query);
	if (ret != SQLITE_OK) {
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;

}


Eina_Bool update_table(const char *table_name, Eina_List *column_names, Eina_List *column_types, Eina_List *column_values, const char *where_clause)
{
	if (!table_name || ! column_names || !column_types || !column_values)
		return EINA_FALSE;

	sqlite3 *db = create_database();
	if (!db)
		return EINA_FALSE;

	int ret = 0 ;
	char *err_msg = 0;
	int col_count = eina_list_count(column_names);

	int str_len = strlen("UPDATE ") + strlen(table_name) + strlen(" SET ") + 1;
	char *var_query = (char*)malloc(str_len);
	if (!var_query) {
		close_database(db);
		return EINA_FALSE;
	}

	strcpy(var_query, "UPDATE ");
	strcat(var_query, table_name);
	strcat(var_query, " SET ");


	int col_val_count = eina_list_count(column_names);

	for (int col = 0; col < col_val_count; col++) {
		char *col_name = eina_list_nth(column_names, col);
		char *col_type = eina_list_nth(column_types, col);

		char *col_value = NULL;
		if (!strcmp(col_type, "INTEGER") || !strcmp(col_type, "INTEGER PRIMARY KEY NOT NULL")) {
			int *tmp_value = eina_list_nth(column_values, col);

			int act_val = (*tmp_value);
			col_value = (char*)malloc(50);
			sprintf(col_value, "%d", act_val);

			var_query = realloc(var_query, strlen(var_query) + strlen(col_name) + strlen(" = ") + strlen(col_value) + 1);
			strcat(var_query, col_name);
			strcat(var_query, " = ");
			strcat(var_query, col_value);

		} else if (!strcmp(col_type, "TEXT") || !strcmp(col_type, "TEXT PRIMARY KEY NOT NULL")) {

			char *tmp_value = eina_list_nth(column_values, col);
			col_value = (char*)malloc(strlen(tmp_value) + 1);
			strcpy(col_value, tmp_value);

			var_query = realloc(var_query, strlen(var_query) + strlen(col_name) + strlen(" = ")+strlen("'") + 1);
			strcat(var_query, col_name);
			strcat(var_query, " = ");
			strcat(var_query, "'");

			var_query = realloc(var_query, strlen(var_query)+strlen(col_value) + 1);
			strcat(var_query, col_value);

			var_query = realloc(var_query, strlen(var_query)+strlen("'") + 1);
			strcat(var_query, "'");
		}

		if (col < col_count - 1) {
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
	free(var_query);
	if (ret != SQLITE_OK) {
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;

}

Eina_Bool get_values_from_table(const char *table_name, Eina_List *column_names, int (*callback)(void*, int, char**, char**), const char *where_clause, void *data_to_callback)
{
	if (!table_name)
		return EINA_FALSE;

	sqlite3 *db = create_database();
	if (!db)
		return EINA_FALSE;

	/*****No rows identification*****/

	char *row_cnt_qry = (char*)malloc(strlen("SELECT COUNT(*) FROM ") + strlen(table_name) + strlen(";") +1);
	if (!row_cnt_qry) {
		close_database(db);
		return EINA_FALSE;
	}

	strcpy(row_cnt_qry, "SELECT COUNT(*) FROM ");
	strcat(row_cnt_qry, table_name);
	strcat(row_cnt_qry, ";");

	int no_of_rows = 0;
	sqlite3_stmt *stmt;
	if (sqlite3_prepare_v2(db, row_cnt_qry, -1, &stmt, NULL) == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ERROR)
			no_of_rows = 0;
		else
			no_of_rows = sqlite3_column_int(stmt, 0);

		sqlite3_finalize(stmt);
	}

	free(row_cnt_qry);
	if (no_of_rows <= 0) {
		close_database(db);
		return EINA_FALSE;
	}
	close_database(db);
	/********************************/

	int ret = 0 ;
	char *err_msg = 0;

	db = create_database();
	if (!db)
		return EINA_FALSE;

	int str_len = strlen("SELECT ") + 1;
	char *var_query = (char*)malloc(str_len);
	if (!var_query) {
		close_database(db);
		return EINA_FALSE;
	}

	strcpy(var_query, "SELECT ");
	if (!column_names) {
		var_query = realloc(var_query, strlen(var_query) + 3);
		strcat(var_query, " *");
	} else {

		int col_count = eina_list_count(column_names);
		char *col_name = NULL;
		for (int col = 0; col < col_count; col++) {
			col_name = eina_list_nth(column_names, col);
			var_query = realloc(var_query, strlen(var_query)+strlen(col_name) + 1);
			strcat(var_query, col_name);
			col_name = NULL;
			var_query = realloc(var_query, strlen(var_query)+strlen(" ") + 1);

			if (col < col_count - 1) {
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


	ret = sqlite3_exec(db, var_query, callback, (void*)data_to_callback, &err_msg);
	close_database(db);
	free(var_query);

	if (ret != SQLITE_OK) {
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}

	return EINA_TRUE;
}

Eina_List *get_values_from_table_sync(const char *table_name, Eina_List *column_names, Eina_List *column_types, const char *where_clause)
{
	Eina_List *query_vals = NULL;

	if (!table_name)
		return (Eina_List *)NULL;

	sqlite3 *db = create_database();
	if (!db)
		return NULL;
	/*****No rows identification*****/

	char *row_cnt_qry = (char *)malloc(strlen("SELECT COUNT(*) FROM ") + strlen(table_name) + strlen(";") +1);
	if (!row_cnt_qry) {
		close_database(db);
		return NULL;
	}

	strcpy(row_cnt_qry, "SELECT COUNT(*) FROM ");
	strcat(row_cnt_qry, table_name);
	strcat(row_cnt_qry, ";");

	int no_of_rows = 0;
	sqlite3_stmt *stmt;
	if (sqlite3_prepare_v2(db, row_cnt_qry, -1, &stmt, NULL) == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ERROR)
			no_of_rows = 0;
		else
			no_of_rows = sqlite3_column_int(stmt, 0);

		sqlite3_finalize(stmt);
	}
	close_database(db);
	db = NULL;
	free(row_cnt_qry);
	if (no_of_rows <= 0)
		return (Eina_List *)NULL;

	/********************************/
	db = create_database();
	if (!db)
		return NULL;

	int ret = 0 ;
	char *err_msg = 0;
	int str_len = strlen("SELECT ") + 1;
	char *var_query = (char*)malloc(str_len);
	if (!var_query) {
		close_database(db);
		return NULL;
	}

	strcpy(var_query, "SELECT ");
	if (!column_names) {
		var_query = realloc(var_query, strlen(var_query) + 3);
		strcat(var_query, " *");
	} else {

		int col_count = eina_list_count(column_names);
		char *col_name = NULL;
		for (int col = 0; col < col_count; col++) {
			col_name = eina_list_nth(column_names, col);
			var_query = realloc(var_query, strlen(var_query)+strlen(col_name) + 1);
			strcat(var_query, col_name);
			col_name = NULL;
			var_query = realloc(var_query, strlen(var_query)+strlen(" ") + 1);

			if (col < col_count - 1) {
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


	ret = sqlite3_prepare_v2(db, var_query, -1, &stmt, 0);
	close_database(db);
	db = NULL;
	free(var_query);
	if (ret != SQLITE_OK) {
		sqlite3_free(err_msg);
		return NULL;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int col_val_count = eina_list_count(column_names);
		Eina_List *row_vals = NULL;
		for (int col = 0; col < col_val_count; col++) {
			char *col_type = eina_list_nth(column_types, col);
			if (!strcmp(col_type, "INTEGER") || !strcmp(col_type, "INTEGER PRIMARY KEY NOT NULL")) {
				long long temp = sqlite3_column_int64(stmt, col);
				int *val_int = (int *)malloc(sizeof(int));
				*val_int = temp;
				row_vals = eina_list_append(row_vals, val_int);
			} else if (!strcmp(col_type, "TEXT") || !strcmp(col_type, "TEXT PRIMARY KEY NOT NULL")) {
				const char *text = (const char *)sqlite3_column_text(stmt, col);
				char *val_text;

				val_text = strdup(text);
				if (!val_text) {
					/**
					 *Handling me.
					 */
				} else {
					row_vals = eina_list_append(row_vals, val_text);
				}
			}
		}
		query_vals = eina_list_append(query_vals, row_vals);
	}

	return query_vals;
}

Eina_List *get_values_from_table_sync_order_by(const char *table_name, Eina_List *column_names, Eina_List *column_types, const char *order_column, Eina_Bool is_asc, const char *where_clause)
{
	Eina_List *query_vals = NULL;

	if (!table_name)
		return NULL;

	sqlite3 *db = create_database();
	if (!db)
		return NULL;

	char *row_cnt_qry = (char*)malloc(strlen("SELECT COUNT(*) FROM ") + strlen(table_name) + strlen(";") +1);
	if (!row_cnt_qry) {
		close_database(db);
		return NULL;
	}

	strcpy(row_cnt_qry, "SELECT COUNT(*) FROM ");
	strcat(row_cnt_qry, table_name);
	strcat(row_cnt_qry, ";");

	int no_of_rows = 0;
	sqlite3_stmt *stmt;
	if (sqlite3_prepare_v2(db, row_cnt_qry, -1, &stmt, NULL) == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ERROR)
			no_of_rows = 0;
		else
			no_of_rows = sqlite3_column_int(stmt, 0);

		sqlite3_finalize(stmt);
	}
	close_database(db);
	free(row_cnt_qry);
	if (no_of_rows <= 0)
		return NULL;

	/********************************/
	db = create_database();
	if (!db)
		return NULL;
	int ret = 0 ;

	int str_len = strlen("SELECT ") + 1;
	char *var_query = (char*)malloc(str_len);
	if (!var_query) {
		close_database(db);
		return NULL;
	}

	strcpy(var_query, "SELECT ");
	if (!column_names) {
		var_query = realloc(var_query, strlen(var_query) + 3);
		strcat(var_query, " *");
	} else {

		int col_count = eina_list_count(column_names);
		char *col_name = NULL;
		for (int col = 0; col < col_count; col++) {
			col_name = eina_list_nth(column_names, col);
			var_query = realloc(var_query, strlen(var_query)+strlen(col_name) + 1);
			strcat(var_query, col_name);
			col_name = NULL;
			var_query = realloc(var_query, strlen(var_query)+strlen(" ") + 1);

			if (col < col_count - 1) {
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
	close_database(db);
	free(var_query);
	if (ret != SQLITE_OK)
		return NULL;

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int col_val_count = eina_list_count(column_names);
		Eina_List *row_vals = NULL;
		for (int col = 0; col < col_val_count; col++) {
			char *col_type = eina_list_nth(column_types, col);
			if (!strcmp(col_type, "INTEGER") || !strcmp(col_type, "INTEGER PRIMARY KEY NOT NULL")) {
				long long temp = sqlite3_column_int64(stmt, col);
				int *val_int = (int*)malloc(sizeof(int));
				*val_int = temp;
				row_vals = eina_list_append(row_vals, val_int);
			} else if (!strcmp(col_type, "TEXT") || !strcmp(col_type, "TEXT PRIMARY KEY NOT NULL")) {
				char *val_text = strdup((const char *)sqlite3_column_text(stmt, col));
				row_vals = eina_list_append(row_vals, val_text);
			}
		}
		query_vals = eina_list_append(query_vals, row_vals);
	}
	return query_vals;
}

Eina_Bool delete_record(char *tablename, const char *where_clause)
{
	if (!tablename)
		return EINA_FALSE;

	sqlite3 *db = create_database();
	if (!db)
		return EINA_FALSE;

	char *var_query = (char*)malloc(strlen("DELETE FROM ") + strlen(tablename) + 1);
	if (!var_query) {
		close_database(db);
		return EINA_FALSE;
	}

	strcpy(var_query, "DELETE FROM ");
	strcat(var_query, tablename);

	if (where_clause) {
		var_query = realloc(var_query, strlen(var_query)+strlen(" WHERE ") + 1);
		strcat(var_query, " WHERE ");
		var_query = realloc(var_query, strlen(var_query)+strlen(where_clause) + 1);
		strcat(var_query, where_clause);
	}

	var_query = realloc(var_query, strlen(var_query) + 2);
	strcat(var_query, ";");

	int ret;
	char *err_msg = 0;
	ret = sqlite3_exec(db, var_query, NULL, NULL, &err_msg);
	close_database(db);
	free(var_query);
	if (ret != SQLITE_OK) {
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;
}

Eina_Bool drop_table(char *tablename)
{
	if (!tablename)
		return EINA_FALSE;

	sqlite3 *db = create_database();
	if (!db)
		return EINA_FALSE;

	char *var_query = (char*)malloc(strlen("DROP TABLE ") + strlen(tablename) + strlen(";") + 1);
	if (!var_query) {
		close_database(db);
		return EINA_FALSE;
	}

	strcpy(var_query, "DROP TABLE ");
	strcat(var_query, tablename);
	strcat(var_query, ";");
	int ret;
	char *err_msg = 0;
	ret = sqlite3_exec(db, var_query, NULL, NULL, &err_msg);
	close_database(db);
	free(var_query);
	if (ret != SQLITE_OK) {
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;
}

int get_number_of_rows(char *table_name, char *where_clause)
{
	int no_of_rows = 0;
	if (!table_name || !where_clause)
		return no_of_rows;

	sqlite3 *db = create_database();
	if (!db)
		return EINA_FALSE;

	char *row_cnt_qry = (char*)malloc(strlen("SELECT COUNT(*) FROM ") + strlen(table_name) + 1);
	if (!row_cnt_qry) {
		close_database(db);
		return EINA_FALSE;
	}

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
		if (sqlite3_step(stmt) == SQLITE_ERROR)
			no_of_rows = 0;
		else
			no_of_rows = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
	}
	close_database(db);
	free(row_cnt_qry);
	return no_of_rows;
}
