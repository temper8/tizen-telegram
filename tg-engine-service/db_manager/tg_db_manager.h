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

#ifndef TG_DB_MANAGER_H_
#define TG_DB_MANAGER_H_

#include "tg_common.h"
#include <sqlite3.h>

extern int tg_db_fini(void);
extern int tg_db_init(void);
extern sqlite3* create_database();
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
