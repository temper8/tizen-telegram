/**
 * @file tg_db_manager.c
 * @date Jun 1, 2015
 * @author sandeep
 */

#include "tg_db_manager.h"
#include <string.h>


Eina_Bool create_table(sqlite3* db, const char* table_name, Eina_List* column_names, Eina_List* column_types)
{
	if(!db || !table_name || ! column_names || !column_types) {
		return EINA_FALSE;
	}

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

	ret = sqlite3_exec(db,var_query, NULL,(void*)db, &err_msg);
	if( ret != SQLITE_OK ){
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;
}

Eina_Bool insert_table(sqlite3* db, const char* table_name, Eina_List* column_names, Eina_List* column_types, Eina_List* column_values)
{
	if(!db || !table_name || ! column_names || !column_types || !column_values) {
		return EINA_FALSE;
	}

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

	ret = sqlite3_exec(db,var_query, NULL,(void*)db, &err_msg);
	if( ret != SQLITE_OK ){
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;

}


Eina_Bool update_table(sqlite3* db, const char* table_name, Eina_List* column_names, Eina_List* column_types, Eina_List* column_values, const char* where_clause)
{
	if(!db || !table_name || ! column_names || !column_types || !column_values) {
		return EINA_FALSE;
	}

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

	ret = sqlite3_exec(db,var_query, NULL,(void*)db, &err_msg);
	if( ret != SQLITE_OK ){
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}
	return EINA_TRUE;

}

Eina_Bool get_values_from_table(sqlite3* db, const char* table_name, Eina_List* column_names, int (*callback)(void*,int,char**,char**), const char* where_clause, void* data_to_callback)
{
	if (!db || !table_name) {
		return EINA_FALSE;
	}

	/*****No rows identification*****/

	char* row_cnt_qry = (char*)malloc(strlen("SELECT COUNT(*) FROM ") + strlen(table_name) + strlen(";") +1);
	strcpy(row_cnt_qry, "SELECT COUNT(*) FROM ");
	strcat(row_cnt_qry, table_name);
	strcat(row_cnt_qry, ";");

	int no_of_rows = 0;
	//ret = sqlite3_exec(db,var_query, callback,(void*)db, &err_msg);

	sqlite3_stmt *stmt;
	if (sqlite3_prepare_v2(db, row_cnt_qry, -1, &stmt, NULL) == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ERROR) {
			no_of_rows = 0;
		} else {
			no_of_rows = sqlite3_column_int(stmt, 0);
		}
		sqlite3_finalize(stmt);
	}

	free(row_cnt_qry);
	if(no_of_rows <= 0) {
		return EINA_FALSE;
	}

	/********************************/

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
	if( ret != SQLITE_OK ){
		sqlite3_free(err_msg);
		return EINA_FALSE;
	}

	free(var_query);
	return EINA_TRUE;
}

Eina_List *get_values_from_table_sync(sqlite3* db, const char* table_name, Eina_List* column_names, Eina_List* column_types, const char* where_clause)
{
	Eina_List* query_vals = NULL;

	if (!db || !table_name) {
		return (Eina_List *)NULL;
	}

	/*****No rows identification*****/

	char* row_cnt_qry = (char*)malloc(strlen("SELECT COUNT(*) FROM ") + strlen(table_name) + strlen(";") +1);
	strcpy(row_cnt_qry, "SELECT COUNT(*) FROM ");
	strcat(row_cnt_qry, table_name);
	strcat(row_cnt_qry, ";");

	int no_of_rows = 0;
	//ret = sqlite3_exec(db,var_query, callback,(void*)db, &err_msg);

	sqlite3_stmt *stmt;
	if (sqlite3_prepare_v2(db, row_cnt_qry, -1, &stmt, NULL) == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ERROR) {
			no_of_rows = 0;
		} else {
			no_of_rows = sqlite3_column_int(stmt, 0);
		}
		sqlite3_finalize(stmt);
	}

	free(row_cnt_qry);
	if(no_of_rows <= 0) {
		return (Eina_List *)NULL;
	}

	/********************************/

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
				char* val_text = strdup(sqlite3_column_text(stmt, col));
				row_vals = eina_list_append(row_vals, val_text);
			}
		}
		query_vals = eina_list_append(query_vals, row_vals);
	}

	free(var_query);
	return query_vals;
}

