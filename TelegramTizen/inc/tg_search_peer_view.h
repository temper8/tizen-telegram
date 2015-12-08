/*
 * tg_search_peer_view.h
 *
 *  Created on: Sep 18, 2015
 *      Author: sandeep
 */

#ifndef TG_SEARCH_PEER_VIEW_H_
#define TG_SEARCH_PEER_VIEW_H_

#include "tg_common.h"

extern void launch_start_peer_search_view(appdata_s* ad);
extern int on_create_new_contact(appdata_s* ad);
extern void on_new_contact_added_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success);

#endif /* TG_SEARCH_PEER_VIEW_H_ */
