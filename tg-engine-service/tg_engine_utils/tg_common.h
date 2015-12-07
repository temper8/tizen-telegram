/*
 * tg_common.h
 *
 *  Created on: May 19, 2015
 *      Author: sandeep
 */

#ifndef TG_COMMON_H_
#define TG_COMMON_H_

#include <Elementary.h>
#include <app_control.h>
#include <notification.h>
#include "tg_engine.h"

#define TELEGRAM_APP_ID "org.tizen.telegramtizen"

typedef enum MESSAGE_STATE {
	TG_MESSAGE_STATE_SENDING = 1,
	TG_MESSAGE_STATE_SENT,
	TG_MESSAGE_STATE_DELIVERED,
	TG_MESSAGE_STATE_FAILED,
	TG_MESSAGE_STATE_RECEIVED,
	TG_MESSAGE_STATE_READ,
	TG_MESSAGE_STATE_UNKNOWN
} TG_MESSAGE_STATE;

typedef struct msg_container {
	int buddy_id;
	int message_id;
} msg_container_s;

typedef struct msg_list_container {
	Eina_List *message_ids;
	int buddy_id;
	int current_message_id;
	int current_index;
} msg_list_container_s;

extern char *ui_utils_get_resource(const char *res_name);

extern char *get_table_name_from_number(const int id);

extern char *replace(const char *s, char ch, const char *repl);

extern void tg_notification_create(tg_engine_data_s* tg_data, char * icon_path, const char *title, char *content, char *sound_path, char *app_id);

extern int recursive_dir_delete(const char *dir);

#endif /* TG_COMMON_H_ */
