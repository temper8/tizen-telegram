/*
 * tg_db_manager.h
 *
 *  Created on: Jun 1, 2015
 *      Author: sandeep
 */

#ifndef TG_DB_MANAGER_H_
#define TG_DB_MANAGER_H_

extern int tg_db_fini(void);
extern int tg_db_init(void);

extern int tg_db_create_table_peer_info(const char *table_name);
extern int tg_db_insert_peer_info(const char *tablename, tgl_peer_t *UC, int last_msg_id, int unread_count);
extern int tg_db_update_peer_info(const char *tablename, tgl_peer_t *UC, int last_msg_id, int unread_count);

extern int tg_db_create_table_message(const char *table_name);
extern struct tgl_message *tg_db_get_message(const char *table_name, long long id);
extern int tg_db_insert_message(const char *table_name, struct tgl_message *M, long long unique_id);
extern int tg_db_update_message(const char *table_name, struct tgl_message *M, long long unique_id);

extern int tg_db_create_table_buddy_info(const char *table_name);

extern int tg_db_create_table_chat_info(const char *table_name);
extern int tg_db_insert_chat_info(const char *table_name, struct tgl_chat *chat, char *photo_path);
extern int tg_db_update_chat_info(const char *table_name, struct tgl_chat *chat, char *photo);
extern int tg_db_count_chat_info(const char *table_name, struct tgl_chat *chat);

extern int tg_db_create_table_media_info(const char *table_name);
extern int tg_db_update_media_info_filepath(const char *table_name, long long media_id, const char *filepath);
extern int tg_db_update_media_info_by_id(const char *table_name, struct tgl_message *msg, long long id);
extern int tg_db_insert_media_info(const char *table_name, struct tgl_message *msg, const char *filename);
extern void *tg_db_get_media_info(const char *table_name, long long id, int *media_type);

extern int tg_db_create_table_user_info(const char *table_name);
extern Eina_List *tg_db_get_user_list(const char *table_name);
extern struct tgl_user *tg_db_get_user_info(const char *table_name, int uid);
extern int tg_db_insert_user_info(const char *tablename, struct tgl_user *U);
extern int tg_db_update_user_info(const char *tablename, struct tgl_user *U);
extern int tg_db_update_user_photo(const char *tablename, int uid, const char *photo, int photo_id);

#endif /* TG_DB_MANAGER_H_ */
