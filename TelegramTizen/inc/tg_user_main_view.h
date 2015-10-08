/*
 * tg_user_main_view.h
 *
 *  Created on: Aug 20, 2015
 *      Author: sandeep
 */

#ifndef TG_USER_MAIN_VIEW_H_
#define TG_USER_MAIN_VIEW_H_

#include "tg_common.h"

extern void launch_user_main_view_cb(appdata_s* ad);
extern void refresh_main_list_view(appdata_s* ad, Eina_Bool is_new_item);
extern void reload_main_list_view(appdata_s* ad);

#endif /* TG_USER_MAIN_VIEW_H_ */
