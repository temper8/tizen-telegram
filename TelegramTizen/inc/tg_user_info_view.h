/*
 * tg_user_info_view.h
 *
 *  Created on: Oct 2, 2015
 *      Author: sandeep
 */

#ifndef TG_USER_INFO_VIEW_H_
#define TG_USER_INFO_VIEW_H_


#include "tg_common.h"

extern void launch_user_info_screen(appdata_s* ad, int peer_id);
extern void on_user_block_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success);
extern void on_user_unblock_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success);
extern void on_user_deleted_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success);
extern void on_user_added_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success);

#endif /* TG_USER_INFO_VIEW_H_ */
