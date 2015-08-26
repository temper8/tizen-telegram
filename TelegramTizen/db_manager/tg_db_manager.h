/*
 * tg_db_manager.h
 *
 *  Created on: Jun 30, 2015
 *      Author: sandeep
 */

#ifndef TG_DB_MANAGER_H_
#define TG_DB_MANAGER_H_

#include "tg_common.h"
#include <sqlite3.h>

extern sqlite3* create_database(char* database_name);
extern Eina_Bool create_table(sqlite3* db, const char* table_name, Eina_List* column_names, Eina_List* column_types);
extern Eina_Bool insert_table(sqlite3* db, const char* table_name, Eina_List* column_names, Eina_List* column_types, Eina_List* column_values);
extern Eina_Bool update_table(sqlite3* db, const char* table_name, Eina_List* column_names, Eina_List* column_types, Eina_List* column_values, const char* where_clause);
extern Eina_Bool get_values_from_table(sqlite3* db, const char* table_name, Eina_List* column_names, int (*callback)(void*,int,char**,char**), const char* where_clause, void* data_to_callback);
extern Eina_List* get_values_from_table_sync(sqlite3* db, const char* table_name, Eina_List* column_names, Eina_List* column_types, const char* where_clause);
extern Eina_List* get_values_from_table_sync_order_by(sqlite3* db, const char* table_name, Eina_List* column_names, Eina_List* column_types, const char* order_column, Eina_Bool is_asc, const char* where_clause);
extern Eina_Bool close_database(sqlite3* db);



#endif /* TG_DB_MANAGER_H_ */
