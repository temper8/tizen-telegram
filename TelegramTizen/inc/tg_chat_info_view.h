/*
 * tg_chat_info_view.h
 *
 *  Created on: Oct 3, 2015
 *      Author: sandeep
 */

#ifndef TG_CHAT_INFO_VIEW_H_
#define TG_CHAT_INFO_VIEW_H_

#include "tg_common.h"

extern void launch_chat_info_screen(appdata_s* ad, int peer_id);
extern void on_group_chat_info_updated(appdata_s *ad, char *type_of_change);
extern void on_group_chat_deleted(appdata_s *ad, int chat_id);

#endif /* TG_CHAT_INFO_VIEW_H_ */
