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

extern Eina_Bool create_table(const char* table_name, Eina_List* column_names, Eina_List* column_types);
extern Eina_Bool insert_table(const char* table_name, Eina_List* column_names, Eina_List* column_types, Eina_List* column_values);
extern Eina_Bool update_table(const char* table_name, Eina_List* column_names, Eina_List* column_types, Eina_List* column_values, const char* where_clause);
extern Eina_Bool get_values_from_table(const char* table_name, Eina_List* column_names, int (*callback)(void*,int,char**,char**), const char* where_clause, void* data_to_callback);
extern Eina_List* get_values_from_table_sync(const char* table_name, Eina_List* column_names, Eina_List* column_types, const char* where_clause);
extern Eina_List* get_values_from_table_sync_order_by(const char* table_name, Eina_List* column_names, Eina_List* column_types, const char* order_column, Eina_Bool is_asc, const char* where_clause);
extern int get_number_of_rows(const char *table_name, char *where_clause);
extern Eina_List *tg_db_get_user_info(tgl_peer_id_t *user_id);
extern Eina_List *tg_db_get_chat_info(const char *table_name);
extern tg_peer_info_s *tg_db_get_peer_info(const char *table, int peer_id);
extern Eina_List *tg_db_get_messages(const char *table_name);

extern int tg_db_init(void);
extern int tg_db_fini(void);

#endif /* TG_DB_MANAGER_H_ */
