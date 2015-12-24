/*
 * tg_messaging_view.h
 *
 *  Created on: Aug 22, 2015
 *      Author: sandeep
 */

#ifndef TG_MESSAGING_VIEW_H_
#define TG_MESSAGING_VIEW_H_

#include "tg_common.h"

extern void launch_messaging_view_cb(appdata_s* ad, int user_id);
extern void on_text_message_received_from_buddy(appdata_s* ad, long long message_id, int type_of_chat);
extern void on_text_message_state_changed(appdata_s* ad, tg_message_s *msg, int type_of_chat);
extern void on_video_thumb_download_completed(appdata_s* ad, int buddy_id, long long media_id, const char* file_path, const char *caption);
extern void on_media_download_completed(appdata_s* ad, int buddy_id, long long media_id, const char* file_path, const char *caption);
extern void on_user_presence_state_changed(appdata_s* ad, int buddy_id);
extern void on_user_status_changed(appdata_s* ad, char* status);
extern void on_group_chat_info_changed(appdata_s *ad, char *type_of_change);
extern void on_chat_profile_pic_changed(appdata_s *ad, char *file_path);
extern void on_messaging_menu_button_clicked(void *data, Evas_Object *obj, void *event_info);
extern void refresh_messaging_view(appdata_s *ad);
#endif /* TG_MESSAGING_VIEW_H_ */
