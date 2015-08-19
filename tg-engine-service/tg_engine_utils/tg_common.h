/*
 * tg_common.h
 *
 *  Created on: May 19, 2015
 *      Author: sandeep
 */

#ifndef TG_COMMON_H_
#define TG_COMMON_H_


#include <Elementary.h>

#define DEFAULT_TELEGRAM_PATH "/opt/usr/media/telegram/"
#define DEFAULT_TG_DATABASE_PATH "/opt/usr/media/telegram/tg_data_base.db"

typedef enum MESSAGE_STATE {
	TG_MESSAGE_STATE_SENDING = 1,
	TG_MESSAGE_STATE_SENT,
	TG_MESSAGE_STATE_DELIVERED,
	TG_MESSAGE_STATE_FAILED,
	TG_MESSAGE_STATE_RECEIVED,
	TG_MESSAGE_STATE_READ,
	TG_MESSAGE_STATE_UNKNOWN
} TG_MESSAGE_STATE;



//static char* get_table_name_from_number(const char* phone_no)
static char* get_table_name_from_number(const int id)
{
	char id_str[50];
	sprintf(id_str, "%d", id);
	char* msg_table = (char*)malloc(strlen("tg_") + strlen(id_str) + strlen("_msg") + 1);
	strcpy(msg_table, "tg_");
	strcat(msg_table, id_str);
	strcat(msg_table, "_msg");
	return msg_table;
}

#endif /* TG_COMMON_H_ */
