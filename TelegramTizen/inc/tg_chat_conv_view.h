/*
 * tg_chat_conv_view.h
 *
 *  Created on: Jun 8, 2015
 *      Author: sandeep
 */

#ifndef TG_CHAT_CONV_VIEW_H_
#define TG_CHAT_CONV_VIEW_H_


#include "tg_common.h"

extern void launch_chat_conv_view_cb(void *data, int user_id);
extern void on_chat_buddy_msg_receive(tg_message_s *M, int type_of_chat);
extern void on_received_image_loaded(int buddy_id, long long media_id, const char* file_path);
extern void on_message_sent_to_buddy_successfully(appdata_s* ad, tg_message_s *M, int type_of_chat);
extern void on_message_read_by_buddy_successfully(appdata_s* ad, tg_message_s *M, int type_of_chat);

#endif /* TG_CHAT_CONV_VIEW_H_ */
