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

#ifndef TG_COMMON_H_
#define TG_COMMON_H_

#include <Elementary.h>
#include <app_control.h>
#include <notification.h>
#include "tg_engine.h"

#define TELEGRAM_APP_ID "org.tizen.telegram_tizen"

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

static uint64_t get_time_stamp_in_macro()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}

extern char *ui_utils_get_resource(const char *res_name);

extern char *get_table_name_from_number(const int id);

extern char *replace(const char *s, char ch, const char *repl);

extern void tg_notification_create(tg_engine_data_s* tg_data, char * icon_path, const char *title, char *content, char *sound_path, char *app_id);

extern int recursive_dir_delete(const char *dir);

#endif /* TG_COMMON_H_ */
