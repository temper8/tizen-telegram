/*
 * tg_db_manager.h
 *
 *  Created on: Jun 1, 2015
 *      Author: sandeep
 */

#ifndef TG_DB_MANAGER_H_
#define TG_DB_MANAGER_H_

#include "tg_common.h"
#include <sqlite3.h>

extern int tg_db_fini(void);
extern int tg_db_init(void);
extern sqlite3* create_database(char* database_name);
extern Eina_Bool close_database(sqlite3* db);
extern Eina_Bool create_table(const char* table_name, Eina_List* column_names, Eina_List* column_types);
extern Eina_Bool insert_table(const char* table_name, Eina_List* column_names, Eina_List* column_types, Eina_List* column_values);
extern Eina_Bool update_table(const char* table_name, Eina_List* column_names, Eina_List* column_types, Eina_List* column_values, const char* where_clause);
extern Eina_Bool get_values_from_table(const char* table_name, Eina_List* column_names, int (*callback)(void*,int,char**,char**), const char* where_clause, void* data_to_callback);
extern Eina_List* get_values_from_table_sync(const char* table_name, Eina_List* column_names, Eina_List* column_types, const char* where_clause);
extern Eina_List* get_values_from_table_sync_order_by(const char* table_name, Eina_List* column_names, Eina_List* column_types, const char* order_column, Eina_Bool is_asc, const char* where_clause);
extern Eina_Bool delete_record(char *tablename, const char* where_clause);
extern Eina_Bool drop_table(char *tablename);
extern int get_number_of_rows(char* table_name, char* where_clause);
#endif /* TG_DB_MANAGER_H_ */
