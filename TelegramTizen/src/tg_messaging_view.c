/*
 * tg_messaging_view.c
 *
 *  Created on: Aug 22, 2015
 *      Author: sandeep
 */

#include "tg_messaging_view.h"
#include "tg_db_wrapper.h"
#include "server_requests.h"
#include <attach_panel.h>
#include <mime_type.h>
#include <Elementary.h>
#include "tg_user_info_view.h"
#include "tg_chat_info_view.h"

/************************ Menu Handler ********************/

void on_messaging_menu_option_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	int id = (int)elm_object_item_data_get(it);


	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	tg_peer_info_s *user_data = sel_item->use_data;

	if (!sel_item || !user_data) {
		show_toast(ad, "There are no messages to delete.");
		if (ad->msg_popup) {
			evas_object_del(ad->msg_popup);
			ad->msg_popup = NULL;
		}
		return;
	}


	if (get_buddy_unknown_status(user_data->peer_id) && user_data->peer_type == TGL_PEER_USER) {

		if (id == 0) {
			show_toast(ad, "Add contact to ur buddies");
		} else if (id == 1) {
			char* tablename = get_table_name_from_number(user_data->peer_id);
			delete_all_records(tablename);
			free(tablename);

			// clear all messages
			Evas_Object *genlist = evas_object_data_get(ad->nf, "chat_list");
			elm_genlist_clear(genlist);

			// remove main item from main list
			if (ad->main_item_in_cahtting_data) {
				tg_main_list_item_s* old_item = ad->main_item_in_cahtting_data;
				if (old_item->peer_print_name) {
					free(old_item->peer_print_name);
					old_item->peer_print_name = NULL;
				}
				if (old_item->last_message) {
					free(old_item->last_message);
					old_item->last_message = NULL;
				}
				if (old_item->profile_pic_path) {
					free(old_item->profile_pic_path);
					old_item->profile_pic_path = NULL;
				}
				old_item->date_lbl = NULL;
				old_item->msg_status_lbl = NULL;
				old_item->main_item_layout = NULL;
				old_item->profile_pic = NULL;
				old_item->profile_pic_path = NULL;
				old_item->status_lbl = NULL;
				old_item->user_name_lbl = NULL;
				ad->main_list = eina_list_remove(ad->main_list,  ad->main_item_in_cahtting_data);

				ad->main_item_in_cahtting_data = NULL;
			}
			ad->is_last_msg_changed = EINA_FALSE;
		} else {
			char* tablename = get_table_name_from_number(user_data->peer_id);
			delete_all_records(tablename);
			free(tablename);

			// clear all messages
			Evas_Object *genlist = evas_object_data_get(ad->nf, "chat_list");
			elm_genlist_clear(genlist);

			// remove main item from main list
			if (ad->main_item_in_cahtting_data) {
				tg_main_list_item_s* old_item = ad->main_item_in_cahtting_data;
				if (old_item->peer_print_name) {
					free(old_item->peer_print_name);
					old_item->peer_print_name = NULL;
				}
				if (old_item->last_message) {
					free(old_item->last_message);
					old_item->last_message = NULL;
				}
				if (old_item->profile_pic_path) {
					free(old_item->profile_pic_path);
					old_item->profile_pic_path = NULL;
				}
				old_item->date_lbl = NULL;
				old_item->msg_status_lbl = NULL;
				old_item->main_item_layout = NULL;
				old_item->profile_pic = NULL;
				old_item->profile_pic_path = NULL;
				old_item->status_lbl = NULL;
				old_item->user_name_lbl = NULL;
				ad->main_list = eina_list_remove(ad->main_list,  ad->main_item_in_cahtting_data);

				ad->main_item_in_cahtting_data = NULL;
			}

			ad->is_last_msg_changed = EINA_FALSE;


			app_nf_back_cb(ad, NULL, NULL);
		}
		if (ad->msg_popup) {
			evas_object_del(ad->msg_popup);
			ad->msg_popup = NULL;
		}
		return;
	}


	if (id == 0) {
		if (user_data->peer_type == TGL_PEER_USER || user_data->peer_type == TGL_PEER_CHAT) {
			char* tablename = get_table_name_from_number(user_data->peer_id);
			delete_all_records(tablename);
			free(tablename);

			// clear all messages
			Evas_Object *genlist = evas_object_data_get(ad->nf, "chat_list");
			elm_genlist_clear(genlist);

			// remove main item from main list
			if (ad->main_item_in_cahtting_data) {
				tg_main_list_item_s* old_item = ad->main_item_in_cahtting_data;
				if (old_item->peer_print_name) {
					free(old_item->peer_print_name);
					old_item->peer_print_name = NULL;
				}
				if (old_item->last_message) {
					free(old_item->last_message);
					old_item->last_message = NULL;
				}
				if (old_item->profile_pic_path) {
					free(old_item->profile_pic_path);
					old_item->profile_pic_path = NULL;
				}
				old_item->date_lbl = NULL;
				old_item->msg_status_lbl = NULL;
				old_item->main_item_layout = NULL;
				old_item->profile_pic = NULL;
				old_item->profile_pic_path = NULL;
				old_item->status_lbl = NULL;
				old_item->user_name_lbl = NULL;
				ad->main_list = eina_list_remove(ad->main_list,  ad->main_item_in_cahtting_data);

				ad->main_item_in_cahtting_data = NULL;
			}

			ad->is_last_msg_changed = EINA_FALSE;

		} else {

		}

	} else if (id == 1) {
		if (user_data->peer_type == TGL_PEER_USER) {
			char* tablename = get_table_name_from_number(user_data->peer_id);
			delete_all_records(tablename);
			free(tablename);

			// clear all messages
			Evas_Object *genlist = evas_object_data_get(ad->nf, "chat_list");
			elm_genlist_clear(genlist);

			// remove main item from main list
			if (ad->main_item_in_cahtting_data) {
				tg_main_list_item_s* old_item = ad->main_item_in_cahtting_data;
				if (old_item->peer_print_name) {
					free(old_item->peer_print_name);
					old_item->peer_print_name = NULL;
				}
				if (old_item->last_message) {
					free(old_item->last_message);
					old_item->last_message = NULL;
				}
				if (old_item->profile_pic_path) {
					free(old_item->profile_pic_path);
					old_item->profile_pic_path = NULL;
				}
				old_item->date_lbl = NULL;
				old_item->msg_status_lbl = NULL;
				old_item->main_item_layout = NULL;
				old_item->profile_pic = NULL;
				old_item->profile_pic_path = NULL;
				old_item->status_lbl = NULL;
				old_item->user_name_lbl = NULL;
				ad->main_list = eina_list_remove(ad->main_list,  ad->main_item_in_cahtting_data);

				ad->main_item_in_cahtting_data = NULL;
			}

			ad->is_last_msg_changed = EINA_FALSE;


			app_nf_back_cb(ad, NULL, NULL);


		} else if (user_data->peer_type == TGL_PEER_CHAT) {

			//send group chat delete request
			show_loading_popup(ad);
			send_delete_group_chat_request(ad->service_client, user_data->peer_id);

		} else {

		}
	} else {

	}
	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
}


char* on_messaging_menu_group_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	if (id == 0) {
		return strdup("Clear history");
	} else {
		return strdup("Delete and exit");
	}
}

char* on_messaging_menu_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	appdata_s *ad = evas_object_data_get(obj, "app_data");
	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	tg_peer_info_s *user_data = sel_item->use_data;
	if ((user_data->peer_type == TGL_PEER_USER) && get_buddy_unknown_status(user_data->peer_id)) {
	    if (id == 0) {
	    	return strdup("Add to contacts");
	    } else if (id == 1) {
			return strdup("Clear history");
		} else {
			return strdup("Delete");
		}
	} else {
		if (id == 0) {
			return strdup("Clear history");
		} else {
			return strdup("Delete");
		}
	}
}

void on_msg_popup_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
}

void on_messaging_menu_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (ad->msg_popup || ad->current_app_state != TG_CHAT_MESSAGING_VIEW_STATE) {
		return;
	}

	static Elm_Genlist_Item_Class itc;
	//Evas_Object *popup;
	Evas_Object *box;
	Evas_Object *genlist;
	int i;
	Evas_Object *win = ad->win;

	ad->msg_popup = elm_popup_add(win);
	elm_popup_align_set(ad->msg_popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(ad->msg_popup, EEXT_CALLBACK_BACK, on_msg_popup_back_cb, ad);
	evas_object_size_hint_weight_set(ad->msg_popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_data_set(ad->msg_popup, "app_data", ad);
	box = elm_box_add(ad->msg_popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	evas_object_data_set(genlist, "app_data", ad);

	itc.item_style = "default";
	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	if (sel_item->use_data->peer_type == TGL_PEER_USER) {
		itc.func.text_get = on_messaging_menu_text_get_cb;
	} else if (sel_item->use_data->peer_type == TGL_PEER_CHAT) {
		itc.func.text_get = on_messaging_menu_group_text_get_cb;
	} else {

	}

	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	tg_peer_info_s *user_data = sel_item->use_data;
	if ((user_data->peer_type == TGL_PEER_USER) && get_buddy_unknown_status(user_data->peer_id)) {
		for (i = 0; i < 3; i++) {
			elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_messaging_menu_option_selected_cb, ad);
		}
		evas_object_size_hint_min_set(box, -1, 345);
	} else {
		for (i = 0; i < 2; i++) {
			elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_messaging_menu_option_selected_cb, ad);
		}
		evas_object_size_hint_min_set(box, -1, 230);
	}
	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);

	elm_object_content_set(ad->msg_popup, box);
	evas_object_show(ad->msg_popup);
}


/************************ Menu Handler ********************/




static Evas_Object *create_image_object_from_file(const char *icon_name, Evas_Object *parent)
{
	Evas_Object *icon = elm_image_add(parent);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_image_file_set(icon, icon_name, NULL);
	evas_object_show(icon);
	return icon;
}

void on_chat_profile_pic_changed(appdata_s *ad, char *file_path)
{
	if (!ad || !file_path) {
		return;
	}

	Evas_Object *profile_image = evas_object_data_get(ad->nf, "profile_picture");
	if (profile_image) {
		elm_image_file_set(profile_image, file_path, NULL);
	}

}

void on_group_chat_info_changed(appdata_s *ad, char *type_of_change)
{
	if (!ad || !type_of_change) {
		return;
	}
	if (strstr(type_of_change, "edit_title") != NULL) {
		peer_with_pic_s *sel_item = ad->peer_in_cahtting_data;
		if (sel_item) {
			tg_peer_info_s* user = sel_item->use_data;
			char* user_name = replace(sel_item->use_data->print_name, '_', " ");
			char temp_name[512] = {'\0'};
			snprintf(temp_name, 512, "<font=Tizen:style=Italic color=#000000 align=left><font_size=30>%s</font_size></font>", user_name);
			free(user_name);
			Evas_Object *profile_name = evas_object_data_get(ad->nf, "profile_title");
			elm_object_text_set(profile_name,temp_name);
		}
	} else if (strstr(type_of_change, "delete_photo") != NULL) {

	} else if (strstr(type_of_change, "add_user") != NULL) {
		peer_with_pic_s *sel_item = ad->peer_in_cahtting_data;
		if (sel_item) {
			on_user_presence_state_changed(ad, sel_item->use_data->peer_id);
		}
	} else if (strstr(type_of_change, "delete_user") != NULL) {
		peer_with_pic_s *sel_item = ad->peer_in_cahtting_data;
		if (sel_item) {
			on_user_presence_state_changed(ad, sel_item->use_data->peer_id);
		}
	} else {

	}
}

void on_sent_media_item_clicked(void* data, Evas_Object* layout, void* event_info)
{
	appdata_s* ad = evas_object_data_get(layout, "app_data");
	char* media_type_str = evas_object_data_get(layout, "media_type");
	char* media_file = evas_object_data_get(layout, "media_file");

	if( access (media_file, F_OK) != -1 ) {

	} else {
		media_file = NULL;
	}

	if (media_file && strlen(media_file) > 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image");
			return;
		}
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_VIEW);
		if (strstr(media_type_str, "video") != NULL) {
			app_control_set_mime(app_control,"video/*");
		} else if (strstr(media_type_str, "audio") != NULL) {
			app_control_set_mime(app_control,"audio/*");
		} else {
			app_control_set_mime(app_control,"image/*");
		}
		app_control_set_uri(app_control, media_file);

		app_control_send_launch_request(app_control, NULL, NULL);
		app_control_destroy(app_control);
	}
}

static Evas_Object* get_image_from_path(const char* path, Evas_Object* parent)
{
	if (!path || !parent) {
		return NULL;
	}
	Evas_Object *media_image = elm_image_add(parent);
	elm_image_aspect_fixed_set(media_image, EINA_FALSE);
	elm_image_file_set(media_image, path, NULL);
	evas_object_size_hint_weight_set(media_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(media_image, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(media_image);
	return media_image;
}

int get_image_size(long long media_id)
{
	Eina_List* media_sizes = get_image_sizes_from_db(media_id);
	int row_count = eina_list_count(media_sizes);
	int size1 = 0;
	int size2 = 0;
	int size3 = 0;
	int size4 = 0;
	int media_size = 0;
	for (int i = 0 ; i < row_count ; i++) {
		Eina_List* row_vals = eina_list_nth(media_sizes, i);
		int* temp_size1 = (int*)eina_list_nth(row_vals, 0);
		if(temp_size1) {
			size1 = *temp_size1;
			free(temp_size1);
		}
		int* temp_size2 = (int*)eina_list_nth(row_vals, 3);
		if(temp_size2) {
			size2 = *temp_size2;
			free(temp_size2);
		}
		int* temp_size3 = (int*)eina_list_nth(row_vals, 6);
		if(temp_size3) {
			size3 = *temp_size3;
			free(temp_size3);
		}
		int* temp_size4 = (int*)eina_list_nth(row_vals, 9);
		if(temp_size4) {
			size4 = *temp_size4;
			free(temp_size4);
		}
		eina_list_free(row_vals);
		break;
	}
	eina_list_free(media_sizes);

	if (size1 > 0) {
		media_size = size1;
	} else if (size2 > 0) {
		media_size = size2;
	} else if (size3 > 0) {
		media_size = size3;
	} else if (size4 > 0) {
		media_size = size4;
	} else {

	}
	return media_size;
}



void on_media_chat_item_clicked(void* data, Evas_Object *entry, void* event_info)
{
	Evas_Object *button = evas_object_data_get(entry, "button_object");
	if (button) {
		char* img_state = evas_object_data_get(button, "image_state");
		if (img_state && strstr(img_state, "download_in_progress") != NULL) {
			return;
		}
	}

	appdata_s* ad = evas_object_data_get(entry, "app_data");
	char *temp_media_id = evas_object_data_get(entry, "media_id");
	char *media_type_str = evas_object_data_get(entry, "media_type");

	if (strstr(media_type_str, "location") != NULL) {
		char *url = evas_object_data_get(entry, "location_url");
		launch_app_control(ad, media_type_str, url);
		return;
	}


	long long media_id = atoll(temp_media_id);

	char *media_file = get_media_path_from_db(media_id);


	if( access (media_file, F_OK) != -1 ) {

	} else {
		media_file = NULL;
	}

	if (!media_file || strlen(media_file) <= 0) {

		Eina_Bool ret = send_request_for_media_downloading(ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id, media_id);
		if (!ret) {
			show_toast(ad, "Please check your network connection.");
			return;
		}

		// show progress bar
		char temp_msg[256] = {0,};
	    snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Bold color=#008000 align=center><font_size=15>%s</font_size></font>", "Downloading...");
		elm_object_text_set(button, temp_msg);

		Evas_Object* progressbar = elm_progressbar_add(button);
		elm_object_style_set(progressbar, "process_small");
		evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_color_set(progressbar, 255, 255, 255, 255);
		elm_progressbar_pulse(progressbar, EINA_TRUE);
		evas_object_show(progressbar);

		Evas_Object* old_content = elm_object_content_get(button);
		if (old_content) {
			evas_object_del(old_content);
		}

		elm_object_content_set(button, progressbar);
		evas_object_data_set(button, "image_state", "download_in_progress");

	} else {
		launch_app_control(ad, media_type_str, media_file);
	}
}

static void on_video_play_pressed(void *data, Evas_Object *obj, void *event_info)
{
	if (!data)
		return;
	elm_image_file_set(data, ui_utils_get_resource(TG_PLAY_PRESS_ICON), NULL);
}

static void on_video_play_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	if (!data)
		return;
	elm_image_file_set(data, ui_utils_get_resource(TG_PLAY_NORMAL_ICON), NULL);
}

static Evas_Object* get_video_paly_icon(Evas_Object *parent)
{
	Evas_Object* play_pause_btn = elm_button_add(parent);
	elm_object_style_set(play_pause_btn, "transparent");
	evas_object_size_hint_align_set(play_pause_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(play_pause_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	Evas_Object* play_pause_icon = elm_image_add(parent);
	evas_object_size_hint_align_set(play_pause_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(play_pause_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	elm_image_file_set(play_pause_icon, ui_utils_get_resource(TG_PLAY_NORMAL_ICON), NULL);

	elm_image_resizable_set(play_pause_icon, EINA_TRUE, EINA_TRUE);
	evas_object_show(play_pause_icon);

	elm_object_content_set(play_pause_btn, play_pause_icon);

	evas_object_smart_callback_add(play_pause_btn, "pressed", on_video_play_pressed, play_pause_icon);
	evas_object_smart_callback_add(play_pause_btn, "unpressed", on_video_play_unpressed, play_pause_icon);
	return play_pause_btn;
}

static Evas_Object *get_media_layout_with_play(char *img_path, Evas_Object *parent, Eina_Bool show_play_icon)
{
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
	Evas_Object *rec_video_layout = elm_layout_add(parent);
	elm_layout_file_set(rec_video_layout, edj_path, "bubble_video_item_layout");
	evas_object_size_hint_weight_set(rec_video_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(rec_video_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(rec_video_layout);

	Evas_Object *vid_thumb_icon = get_image_from_path(img_path, parent);
	elm_object_part_content_set(rec_video_layout, "swallow.video_thumb_item", vid_thumb_icon);

	if (show_play_icon) {
/*		Evas_Object* play_img = get_image_from_path(ui_utils_get_resource(MEDIA_PLAY_ICON), parent);
		elm_object_part_content_set(rec_video_layout, "swallow.play_btn", play_img);*/

		Evas_Object* play_pause_btn = get_video_paly_icon(parent);
		elm_object_part_content_set(rec_video_layout, "swallow.play_btn", play_pause_btn);
	}

	return rec_video_layout;
}
static Evas_Object * item_provider(void *data, Evas_Object *entry, const char *item)
{

	Evas_Object *layout = NULL;

	if (!strcmp(item, "itemprovider")) {

		Evas_Object* chat_list = data;
		appdata_s* ad = evas_object_data_get(chat_list, "app_data");
		int user_id = (int)evas_object_data_get(chat_list, "user_id");
		int message_id = (int)evas_object_data_get(chat_list, "message_id");

		peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
		int buddy_id = sel_item->use_data->peer_id;

		char* tablename = get_table_name_from_number(buddy_id);
		tg_message_s* msg = get_message_from_message_table(message_id, tablename);
		free(tablename);
		if (!msg) {
			return NULL;
		}

		Evas_Object *item_to_display = NULL;
		tgl_media_s *media_msg = NULL;
		if (msg->media_type == tgl_message_media_photo || msg->media_type == tgl_message_media_document) {

			Eina_Bool is_blur_image = EINA_FALSE;
			char* img_path = NULL;
			img_path = get_video_thumb_path_from_db(atoll(msg->media_id));
			if (img_path == NULL || strlen(img_path) == 0 || strstr(img_path, "_null_") != NULL) {
				img_path = get_media_path_from_db(atoll(msg->media_id));
			}
			if (img_path == NULL || strlen(img_path) == 0 || strstr(img_path, "_null_") != NULL) {
				const char *tmp;
				tmp = ui_utils_get_resource(BLUR_BG);
				img_path = strdup(tmp);
				is_blur_image = EINA_TRUE;
			}


			if (msg->media_type == tgl_message_media_document) {
				media_msg = get_media_details_from_db(atoll(msg->media_id));

				if (media_msg && strstr(media_msg->doc_type, "video") != NULL) {
					if (img_path == NULL || strlen(img_path) == 0) {
						img_path = strdup(ui_utils_get_resource(TG_VIDEO_ICON));
					}
				}
				if (media_msg && strstr(media_msg->doc_type, "audio") != NULL) {
					if (img_path) {
						free(img_path);
						img_path = NULL;
					}
					img_path = strdup(ui_utils_get_resource(TG_AUDIO_ICON));
				}
				char* media_file = get_media_path_from_db(atoll(msg->media_id));
				if (!media_file || !strcmp(media_file, "_null_") || strlen(media_file) <= 0 ||  access(media_file, F_OK) == -1) {
					is_blur_image = EINA_TRUE;
				}
				free(media_file);

			}

			if (msg->out) {
				if (msg->media_type == tgl_message_media_photo) {
					item_to_display = get_image_from_path(img_path, entry);
				} else {
					if ((media_msg && strstr(media_msg->doc_type, "video") != NULL )|| (media_msg && strstr(media_msg->doc_type, "audio") != NULL)) {
						item_to_display = get_media_layout_with_play(img_path, entry, EINA_TRUE);
					} else {

					}
				}
			} else {
				if (!is_blur_image) {

					if (msg->media_type == tgl_message_media_photo) {
						item_to_display = get_image_from_path(img_path, entry);
						evas_object_data_set(entry, "image_object", (void*)item_to_display);
					} else {
						if ((media_msg && strstr(media_msg->doc_type, "video") != NULL )|| (media_msg && strstr(media_msg->doc_type, "audio") != NULL)) {
							item_to_display = get_media_layout_with_play(img_path, entry, EINA_TRUE);
						} else {

						}
					}

				} else {
					char edj_path[PATH_MAX] = {0, };
					app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
					Evas_Object *rec_img_layout = elm_layout_add(entry);
					elm_layout_file_set(rec_img_layout, edj_path, "bubble_received_media_layout");
					evas_object_size_hint_weight_set(rec_img_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
					evas_object_size_hint_align_set(rec_img_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
					evas_object_show(rec_img_layout);
					Evas_Object *img_item = NULL;


					if (msg->media_type == tgl_message_media_photo) {
						img_item = get_image_from_path(img_path, entry);
					} else {
						if ((media_msg && strstr(media_msg->doc_type, "video") != NULL )|| (media_msg && strstr(media_msg->doc_type, "audio") != NULL)) {
							img_item = get_media_layout_with_play(img_path, entry, EINA_FALSE);
						} else {

						}
					}
					elm_object_part_content_set(rec_img_layout, "swallow.image_item", img_item);

					int media_size = 0;
					if (msg->media_type == tgl_message_media_photo) {
						media_size = get_image_size(atoll(msg->media_id));
					} else {
						if (media_msg && strstr(media_msg->doc_type, "video") != NULL) {
							media_size = get_media_size_from_db(atoll(msg->media_id));
						} else if (media_msg && strstr(media_msg->doc_type, "audio") != NULL) {
							media_size = get_media_size_from_db(atoll(msg->media_id));
						} else {

						}
					}


					int media_size_kbs = (media_size < (1 << 20)); //convert to kbs
					char media_size_str[10] = { 0, };
					if (media_size_kbs > 0) {
						sprintf(media_size_str, "%dKiB", media_size_kbs);
					} else {
						sprintf(media_size_str, "%dB", media_size);
					}


					Evas_Object *size_btn = elm_button_add(entry);
					char temp_msg[256] = {0,};
					snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Bold color=#008000 align=center><font_size=30>%s</font_size></font>", media_size_str);
					elm_object_text_set(size_btn, temp_msg);
					evas_object_size_hint_weight_set(size_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
					evas_object_size_hint_align_set(size_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
					evas_object_show(size_btn);

					evas_object_data_set(size_btn, "image_state", "ready_to_download");

					Evas_Object* download_img = get_image_from_path(ui_utils_get_resource(MEDIA_DOWNLOAD_ICON), entry);
					elm_object_content_set(size_btn, download_img);

					elm_object_part_content_set(rec_img_layout, "swallow.download_btn", size_btn);

					evas_object_data_set(entry, "image_object", (void*)img_item);
					evas_object_data_set(entry, "button_object", (void*)size_btn);
					evas_object_data_set(entry, "image_size", (void*)strdup(media_size_str));

					ad->loaded_msg_list = eina_list_append(ad->loaded_msg_list, entry);

					item_to_display = rec_img_layout;
				}
			}

			if (img_path) {
				free(img_path);
				img_path = NULL;
			}
			// delete media details

		}

		evas_object_data_set(entry, "chat_list", (void*)chat_list);
		evas_object_data_set(entry, "message_id", (void*)message_id);
		evas_object_data_set(entry, "app_data", (void*)ad);


		if (msg->media_type == tgl_message_media_photo) {
			evas_object_data_set(entry, "media_type", (void*)strdup("image"));
		} else if (msg->media_type == tgl_message_media_geo) {
			evas_object_data_set(entry, "media_type", (void*)strdup("location"));
		} else {
			if (media_msg && strstr(media_msg->doc_type, "video") != NULL) {
				evas_object_data_set(entry, "media_type", (void*)strdup("video"));
			} else if (media_msg && strstr(media_msg->doc_type, "audio") != NULL) {
				evas_object_data_set(entry, "media_type", (void*)strdup("audio"));
			} else {

			}
		}

		evas_object_data_set(entry, "media_id", (void*)strdup(msg->media_id));

		evas_object_smart_callback_add(entry, "clicked", on_media_chat_item_clicked, NULL);
		if (item_to_display) {

			char edj_path[PATH_MAX] = {0, };
			app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
			layout = elm_layout_add(entry);
			elm_layout_file_set(layout, edj_path, "chat_image_layout");
			evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(layout);

			Evas_Object *rounded_layout = elm_layout_add(entry);
			elm_layout_file_set(rounded_layout, edj_path, "rounded_corner_layout");
			evas_object_size_hint_weight_set(rounded_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(rounded_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(rounded_layout);
			elm_object_part_content_set(rounded_layout, "content", item_to_display);

			elm_object_part_content_set(layout, "swallow.chat_image", rounded_layout);
		}

		if(msg->message) {
			free(msg->message);
			msg->message = NULL;
		}

		if(msg->media_id) {
			free(msg->media_id);
			msg->media_id = NULL;
		}

		free(msg);
		free_media_details(media_msg);
	}

	return layout;
}


Evas_Object *on_message_item_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *layout;
	layout = elm_layout_add(obj);
	if (!strcmp(part, "elm.icon.entry")) {

		int message_id = (int)data;
		Evas_Object *chat_list = obj;
		appdata_s* ad = evas_object_data_get(chat_list, "app_data");

		Evas_Object *no_msg_lbl = evas_object_data_get(ad->nf, "chat_list_no_msg_text");
		if (no_msg_lbl) {
			evas_object_del(no_msg_lbl);
			evas_object_data_set(ad->nf, "chat_list_no_msg_text", NULL);
		}

		int user_id = (int)evas_object_data_get(chat_list, "user_id");
		evas_object_data_set(chat_list, "message_id", data);


		peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
		int buddy_id = sel_item->use_data->peer_id;

		char* tablename = get_table_name_from_number(buddy_id);
		tg_message_s* msg = get_message_from_message_table(message_id, tablename);
		//Eina_Bool is_blur_image = EINA_FALSE;

		if (msg) {
			if (msg->unread) {
				msg->unread = 0;
				update_msg_into_db(msg, tablename);
				ad->is_last_msg_changed = EINA_TRUE;
			}
			if (msg->out) {

			} else {
				// update un read

			}

			if (msg->service == 2) {
				char edj_path[PATH_MAX] = {0, };
				app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

				layout = elm_layout_add(obj);
				elm_layout_file_set(layout, edj_path, "chat_date_item");
				evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_show(layout);

				Evas_Object *ser_lbl = elm_label_add(obj);
				char temp_msg[4*256] = {0,};
				snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Bold color=#808080 align=center><font_size=27>%s</font_size></font>", msg->message);
				elm_object_text_set(ser_lbl, temp_msg);
				elm_label_ellipsis_set(ser_lbl, EINA_TRUE);
				//evas_object_resize(ser_lbl, 200, 15);
				evas_object_show(ser_lbl);

				elm_object_part_content_set(layout, "elm.text", ser_lbl);
				return layout;
			} else if (msg->service == 1) {
				char edj_path[PATH_MAX] = {0, };
				app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

				layout = elm_layout_add(obj);
				elm_layout_file_set(layout, edj_path, "chat_service_item_box");
				evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_show(layout);

				Evas_Object* ser_lbl = elm_label_add(obj);
				char temp_msg[4*256] = {0,};
				snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Bold color=#666666 align=center><font_size=30>%s</font_size></font>", msg->message);
				elm_object_text_set(ser_lbl, temp_msg);
				elm_label_ellipsis_set(ser_lbl, EINA_TRUE);
				evas_object_resize(ser_lbl, 200, 15);
				evas_object_show(ser_lbl);

				elm_object_part_content_set(layout, "swallow.chat_service_text", ser_lbl);

				return layout;
			}

			Evas_Object *entry = elm_entry_add(obj);
			evas_object_data_set(entry, "chat_list", (void*)chat_list);
			evas_object_data_set(entry, "message_id", (void*)message_id);

			elm_entry_editable_set(entry, EINA_FALSE);
			elm_entry_context_menu_disabled_set(entry, EINA_TRUE);

			//elm_entry_magnifier_disabled_set(entry, EINA_TRUE);
			// FIXME: Deprecated API
			//elm_entry_selection_handler_disabled_set(entry, EINA_TRUE);

			//elm_object_theme_set(layout, ad->theme);

			char *sender_name = NULL;
			if(msg->out) {
				elm_layout_theme_set(layout, "layout", "bubble", "sentmessage1/default");
				elm_object_style_set(entry, "sentmessage1");
				sender_name = replace(ad->current_user_data->print_name, '_', " ");
			} else {
				elm_layout_theme_set(layout, "layout", "bubble", "readmessage1/default");
				elm_object_style_set(entry, "readmessage1");

				if (sel_item->use_data->peer_type == TGL_PEER_USER) {
					sender_name = replace(sel_item->use_data->print_name, '_', " ");
				} else if (sel_item->use_data->peer_type == TGL_PEER_CHAT) {
					int from_id = msg->from_id;
					// get name of buddy
					char* buddy_name = get_buddy_name_from_id(from_id);
					if (buddy_name) {
						sender_name = replace(buddy_name, '_', " ");
						free(buddy_name);
					}
				} else {
					sender_name = replace(sel_item->use_data->print_name, '_', " ");
				}

			}

			elm_entry_input_panel_enabled_set(entry, EINA_FALSE);
			evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(layout);

			// To be handled for group chat
#if 0
			char temp_name[256] = {0,};
			snprintf(temp_name, sizeof(temp_name), "<font=Tizen:style=Regular color=#f16745 align=left><font_size=12>%s</br></font_size></font>", sender_name);
#endif
			Eina_Strbuf *buf = eina_strbuf_new();
			eina_strbuf_append(buf, "");

			if (sender_name) {
				free(sender_name);
				sender_name = NULL;
			}

			if (msg->media_type == tgl_message_media_none) {
				char temp_msg[4*256] = {0,};
				snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Regular color=#ffffff align=left><font_size=15>%s</font_size></font>", msg->message);
				eina_strbuf_append(buf, temp_msg);
				elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
				eina_strbuf_free(buf);

			} else if(msg->media_type == tgl_message_media_photo || msg->media_type == tgl_message_media_document) {
				elm_entry_item_provider_append(entry, item_provider, chat_list);

				tgl_media_s *media_msg = get_media_details_from_db(atoll(msg->media_id));
				if (msg->out) {
					eina_strbuf_append(buf, "<item size=147x147 vsize=full href=itemprovider></item>");
				} else {
					eina_strbuf_append(buf, "<item size=100x147 vsize=full href=itemprovider></item>");
				}
				free_media_details(media_msg);
				elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
				eina_strbuf_free(buf);
			} else if(msg->media_type == tgl_message_media_geo) {

				tgl_media_s *media_msg = get_media_details_from_db(atoll(msg->media_id));
				char loc_url[4*256] = {0,};
				if (media_msg) {
					snprintf(loc_url, sizeof(loc_url), "https://maps.google.com/?q=%s,%s", media_msg->latitude, media_msg->longitude);
					char temp_msg[4*256] = {0,};
					snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Italic|underline color=#0000FF align=left><font_size=15>%s</font_size></font>", loc_url);
					eina_strbuf_append(buf, temp_msg);
					elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
					eina_strbuf_free(buf);
				}

				free_media_details(media_msg);
				evas_object_data_set(entry, "media_type", (void*)strdup("location"));
				evas_object_data_set(entry, "location_url", (void*)strdup(loc_url));
				evas_object_smart_callback_add(entry, "clicked", on_media_chat_item_clicked, NULL);

			} else if(msg->media_type == tgl_message_media_contact) {

				tgl_media_s *media_msg = get_media_details_from_db(atoll(msg->media_id));

				if (media_msg) {
					char temp_msg[4*256] = {0,};
					snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Italic|underline color=#000000 align=left><font_size=15>%s %s, %s</font_size></font>", media_msg->first_name, media_msg->last_name, media_msg->phone_no);
					eina_strbuf_append(buf, temp_msg);
					elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
					eina_strbuf_free(buf);
					free_media_details(media_msg);
				}

			} else if(msg->media_type == tgl_message_media_unsupported) {

			} else if(msg->media_type == tgl_message_media_photo_encr) {

			} else if(msg->media_type == tgl_message_media_document_encr) {

			} else  {

			}

			elm_object_part_content_set(layout, "elm.icon", entry );
			ad->loaded_msg_list = eina_list_append(ad->loaded_msg_list, entry);

			//set time
			time_t t = msg->date;
			const char *format = "%I:%M %p";
			struct tm lt;
			char res[32];
			(void) localtime_r(&t, &lt);

			if (strftime(res, sizeof(res), format, &lt) == 0) {
				(void) fprintf(stderr,  "strftime(3): cannot format supplied "
						"date/time into buffer of size %u "
						"using: '%s'\n",
						sizeof(res), format);
			}

			char time_str[20]={0,};
			snprintf(time_str, sizeof(time_str) - 1, "%s", res);
			elm_object_part_text_set(entry, "time", time_str);

			Evas_Object *status_obj;
			status_obj = elm_icon_add(entry);
			evas_object_size_hint_weight_set(status_obj, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(status_obj, EVAS_HINT_FILL, EVAS_HINT_FILL);

			if(msg->msg_state == TG_MESSAGE_STATE_SENDING) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENDING_ICON), NULL);
			} else if(msg->msg_state == TG_MESSAGE_STATE_SENT) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENT_ICON), NULL);
			} else if(msg->msg_state == TG_MESSAGE_STATE_DELIVERED) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_DELIVERED_ICON), NULL);
			} else if(msg->msg_state == TG_MESSAGE_STATE_RECEIVED) {

			} else if(msg->msg_state == TG_MESSAGE_STATE_FAILED) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_FAILED_ICON), NULL);
			} else if(msg->msg_state == TG_MESSAGE_STATE_READ) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_READ_ICON), NULL);
			} else if(msg->msg_state == TG_MESSAGE_STATE_UNKNOWN) {

			}

			elm_object_part_content_set(entry, "status_icon", status_obj);
			evas_object_show(status_obj);

			free(tablename);
			if(msg->message) {
				free(msg->message);
				msg->message = NULL;
			}

			if(msg->media_id) {
				free(msg->media_id);
				msg->media_id = NULL;
			}

			free(msg);
		}
#if 0
		if (chat_list) {
			int size = elm_genlist_items_count(chat_list);
			if (size > 0) {
				Elm_Object_Item *litem = elm_genlist_nth_item_get(chat_list, size -1);
				elm_genlist_item_show(litem, ELM_GENLIST_ITEM_SCROLLTO_TOP);
			}
		}
#endif
	}
	return layout;
}

void on_text_message_clicked(void *data, Evas_Object *obj, void *event_info)
{

}

void on_text_message_received_from_buddy(appdata_s* ad, long long message_id, int type_of_chat)
{
	if (!ad) {
		return;
	}
	peer_with_pic_s* pic_peer_item = ad->peer_in_cahtting_data;
	tg_peer_info_s* peer_item = pic_peer_item->use_data;
	char* tablename = get_table_name_from_number(peer_item->peer_id);
	tg_message_s* msg = get_message_from_message_table(message_id, tablename);
	if (msg) {
			// update peer table
			if (peer_item) {
				peer_item->last_msg_id = msg->msg_id;
				peer_item->last_msg_date =  msg->date;
				insert_or_update_peer_into_database(peer_item);
			}

		if(msg->message) {
			free(msg->message);
			msg->message = NULL;
		}

		if(msg->media_id) {
			free(msg->media_id);
			msg->media_id = NULL;
		}

		free(msg);
	}
	free(tablename);

	Evas_Object* chat_list = evas_object_data_get(ad->nf, "chat_list");
	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void *)message_id, NULL, ELM_GENLIST_ITEM_NONE, on_text_message_clicked, (void*)message_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);

	int user_id = (int)evas_object_data_get(chat_list, "user_id");
	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	send_request_for_marked_as_read(ad->service_client, sel_item->use_data->peer_id, sel_item->use_data->peer_type);
	ad->is_last_msg_changed = EINA_TRUE;
	on_user_presence_state_changed(ad, sel_item->use_data->peer_id);
}


void on_media_download_completed(appdata_s* ad, int buddy_id, long long media_id, const char* file_path)
{
	if (!ad)
		return;

	if (ad->loaded_msg_list && eina_list_count(ad->loaded_msg_list) > 0) {
		for (int i = eina_list_count(ad->loaded_msg_list) - 1 ; i >= 0; i--) {
			Evas_Object* entry = eina_list_nth(ad->loaded_msg_list, i);
			if (entry) {

				char* media_type_str = evas_object_data_get(entry, "media_type");
				char* media_id_str = evas_object_data_get(entry, "media_id");
				char* media_size_str = evas_object_data_get(entry, "image_size");
				Evas_Object *img_item = evas_object_data_get(entry, "image_object");
				Evas_Object *size_btn = evas_object_data_get(entry, "button_object");

				if (media_id_str) {

					long long lmedia_id = atoll(media_id_str);

					if (media_id == lmedia_id) {
						if (img_item) {

							if (strstr(file_path, "failed_to_load") != NULL) {
								// download failed.
								if (size_btn) {

									Evas_Object* progress = elm_object_content_get(size_btn);
									if (progress) {
										evas_object_del(progress);
									}
									Evas_Object* download_img = get_image_from_path(ui_utils_get_resource(MEDIA_DOWNLOAD_ICON), size_btn);
									elm_object_content_set(size_btn, download_img);
									evas_object_data_set(size_btn, "image_state", "ready_to_download");
									char temp_msg[256] = {0,};
									snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Bold color=#008000 align=center><font_size=30>%s</font_size></font>", media_size_str);
									elm_object_text_set(size_btn, temp_msg);
								}


							} else {
								if (size_btn) {
									evas_object_del(size_btn);
								}

								if ((strstr(media_type_str, "video") != NULL) || (strstr(media_type_str, "audio") != NULL)) {
									Evas_Object* play_img = get_video_paly_icon(img_item);
									//Evas_Object* play_img = get_image_from_path(ui_utils_get_resource(MEDIA_PLAY_ICON), img_item);
									elm_object_part_content_set(img_item, "swallow.play_btn", play_img);
								} else if (strstr(media_type_str, "image") != NULL) {
									elm_image_file_set(img_item, file_path, NULL);
								}
							}

						}
						break;
					}

				}
			}
		}
	}
}

//elm_object_part_content_set(comp_img_layout, "swallow.chat_send_image", image);

void on_video_thumb_download_completed(appdata_s* ad, int buddy_id, long long media_id, const char* file_path)
{
	on_media_download_completed(ad, buddy_id, media_id, file_path);
}

void on_text_message_state_changed(appdata_s* ad, tg_message_s *msg, int type_of_chat)
{
	if (!ad)
		return;

#if 0
	peer_with_pic_s* pic_peer_item = ad->peer_in_cahtting_data;
	if (pic_peer_item) {
		tg_peer_info_s* peer_item = pic_peer_item->use_data;
		// update peer table
		if (peer_item) {
			peer_item->last_msg_id = msg->msg_id;
			peer_item->last_msg_date =  msg->date;
			insert_or_update_peer_into_database(peer_item);
		}
	}
#endif
	if (ad->loaded_msg_list && eina_list_count(ad->loaded_msg_list) > 0) {
		for (int i = eina_list_count(ad->loaded_msg_list) - 1 ; i >= 0; i--) {
			Evas_Object* entry = eina_list_nth(ad->loaded_msg_list, i);

			if (entry) {
				int message_id = (int)evas_object_data_get(entry, "message_id");
				if (message_id == msg->msg_id || message_id == msg->unique_id) {

					evas_object_data_set(entry, "media_id", (void*)strdup(msg->media_id));
					evas_object_data_set(entry, "message_id", (void*)message_id);

					Evas_Object* status_obj = elm_object_part_content_get(entry, "status_icon");
					if (status_obj) {
						if(msg->msg_state == TG_MESSAGE_STATE_SENDING) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENDING_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_SENT) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENT_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_DELIVERED) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_DELIVERED_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_RECEIVED) {

						} else if(msg->msg_state == TG_MESSAGE_STATE_FAILED) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_FAILED_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_READ) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_READ_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_UNKNOWN) {

						}
					}
					return;
				}
			}
		}
	}
}

Eina_Bool add_date_item_to_chat(void *data)
{
	Evas_Object *chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	char* msg_table = get_table_name_from_number(sel_item->use_data->peer_id);
	create_buddy_msg_table(msg_table);
	int msg_id = insert_current_date_to_table(msg_table);
	free(msg_table);

	if (msg_id > 0) {
		// send request to service
		static Elm_Genlist_Item_Class itc;
		itc.item_style = "entry";
		itc.func.text_get = NULL;
		itc.func.content_get = on_message_item_content_get_cb;
		itc.func.state_get = NULL;
		itc.func.del = NULL;
		Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void *)msg_id, NULL, ELM_GENLIST_ITEM_NONE, on_text_message_clicked, (void*)msg_id);
		elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
		ad->is_last_msg_changed = EINA_TRUE;
		return EINA_TRUE;
	}
	return EINA_FALSE;
}



static Eina_Bool on_new_text_message_send_cb(void *data)
{
	Evas_Object *chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");
	Evas_Object *text_entry = evas_object_data_get(chat_list, "text_entry");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	const char* text_to_send = elm_entry_entry_get(text_entry);
	if (!text_to_send || (strlen(text_to_send) == 0))
		return ECORE_CALLBACK_CANCEL;

	ad->msg_count = ad->msg_count + 1001;
	int unique_id = time(NULL) + ad->msg_count;
	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = 0;
	msg.message = (char*)text_to_send;
	msg.message_len = strlen(text_to_send);
	msg.media_type = tgl_message_media_none;
	msg.media_id = "";
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;
	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	free(msg_table);

	peer_with_pic_s* pic_peer_item = ad->peer_in_cahtting_data;
	if (pic_peer_item) {
		tg_peer_info_s* peer_item = pic_peer_item->use_data;
		// update peer table
		if (peer_item) {
			peer_item->last_msg_id = msg.msg_id;
			peer_item->last_msg_date =  msg.date;
			insert_or_update_peer_into_database(peer_item);
		}
	}

	// send request to service
	send_request_for_message_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, tgl_message_media_none, text_to_send, sel_item->use_data->peer_type);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void *)unique_id, NULL, ELM_GENLIST_ITEM_NONE, on_text_message_clicked, (void*)unique_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	elm_entry_entry_set(text_entry, "");
	ad->is_last_msg_changed = EINA_TRUE;
	return ECORE_CALLBACK_CANCEL;
}

static void on_text_message_send_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");
	Evas_Object* text_entry = evas_object_data_get(chat_list, "text_entry");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	const char* text_to_send = elm_entry_entry_get(text_entry);
	if (!text_to_send || (strlen(text_to_send) == 0))
		return;

	if(add_date_item_to_chat(data)) {
		ecore_timer_add(1, on_new_text_message_send_cb, chat_list);
		return;
	}
	ad->msg_count = ad->msg_count + 1001;
	int unique_id = time(NULL) + ad->msg_count;
	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = 0;
	msg.message = (char*)text_to_send;
	msg.message_len = strlen(text_to_send);
	msg.media_type = tgl_message_media_none;
	msg.media_id = "";
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;
	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	free(msg_table);

	peer_with_pic_s* pic_peer_item = ad->peer_in_cahtting_data;
	if (pic_peer_item) {
		tg_peer_info_s* peer_item = pic_peer_item->use_data;
		// update peer table
		if (peer_item) {
			peer_item->last_msg_id = msg.msg_id;
			peer_item->last_msg_date =  msg.date;
			insert_or_update_peer_into_database(peer_item);
		}
	}

	// send request to service
	send_request_for_message_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, tgl_message_media_none, text_to_send, sel_item->use_data->peer_type);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void *)unique_id, NULL, ELM_GENLIST_ITEM_NONE, on_text_message_clicked, (void*)unique_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	elm_entry_entry_set(text_entry, "");
	ad->is_last_msg_changed = EINA_TRUE;
}

void on_user_status_changed(appdata_s* ad, char* status)
{
	if (!ad || !status)
		return;

	Evas_Object* profile_time = evas_object_data_get(ad->nf, "profile_time");
	char status_str[256]={0,};
	snprintf(status_str, sizeof(status_str) - 1, "<font=Tizen:style=Italic color=#000000 align=left><font_size=30>%s</font_size></font>", status);
	elm_object_text_set(profile_time,status_str);
}

void on_user_presence_state_changed(appdata_s* ad, int buddy_id)
{
	if (!ad)
		return;
	int type_of_chat = ad->peer_in_cahtting_data->use_data->peer_type;

	if (type_of_chat == TGL_PEER_USER) {

		Eina_List* buddy_details_array = get_buddy_info(buddy_id);
		if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
			Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
			if (buddy_details && eina_list_count(buddy_details) > 0) {
				int* temp_online = (int*)eina_list_nth(buddy_details, 12);
				int is_online = *temp_online;
				int* temp_last_seen = (int*)eina_list_nth(buddy_details, 13);
				int last_seen = *temp_last_seen;

				Evas_Object* profile_time = evas_object_data_get(ad->nf, "profile_time");

				char *format = NULL;
				Eina_Bool is_today = compare_date_with_current_date(last_seen);

				if (is_online > 0) {
					char status_str[256]={0,};
					snprintf(status_str, sizeof(status_str) - 1, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=30>%s</font_size></font>", "online");
					elm_object_text_set(profile_time,status_str);
				} else {
					time_t t = last_seen;

					if (is_today) {
						format = "Last seen %I:%M %p";
					} else {
						format = "Last seen %b %d, %I:%M %P";
					}

					struct tm lt;
					char res[256];
					(void) localtime_r(&t, &lt);

					if (strftime(res, sizeof(res), format, &lt) == 0) {
						(void) fprintf(stderr,  "strftime(3): cannot format supplied "
								"date/time into buffer of size %u "
								"using: '%s'\n",
								sizeof(res), format);
					}

					char time_str[256]={0,};
					snprintf(time_str, sizeof(time_str) - 1, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=30>%s</font_size></font>", res);

					elm_object_text_set(profile_time,time_str);
				}

				for (int i = 0 ; i < eina_list_count(buddy_details_array); i++) {
					void* val = eina_list_nth(buddy_details, i);
					free(val);
				}
				eina_list_free(buddy_details);
			}
			eina_list_free(buddy_details_array);
		}

	} else if (type_of_chat == TGL_PEER_CHAT) {

		Evas_Object *profile_time = evas_object_data_get(ad->nf, "profile_time");
		if (!profile_time) {
			return;
		}
		tg_chat_info_s* chat_info = get_chat_info(buddy_id);
		if (!chat_info) {
			char status_str[256]={0,};
			snprintf(status_str, sizeof(status_str) - 1, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=30>Unidentified.</font_size></font>");
			elm_object_text_set(profile_time,status_str);
			return;
		}

		int user_list_size = chat_info->user_list_size;
		int online_members = 0;

		for (int i = 0; i < user_list_size; i++) {
			int is_online = get_buddy_online_status(chat_info->chat_users[i]);
			if (is_online > 0) {
				online_members++;
			}
		}



		if (online_members == 0) {
			char status_str[256]={0,};
			snprintf(status_str, sizeof(status_str) - 1, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=30>%d members</font_size></font>", user_list_size);
			elm_object_text_set(profile_time,status_str);
		} else {
			char status_str[256]={0,};
			snprintf(status_str, sizeof(status_str) - 1, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=30>%d members, %d online</font_size></font>", user_list_size, online_members);
			elm_object_text_set(profile_time,status_str);
		}


		if (chat_info) {
			if(chat_info->print_title) {
				free(chat_info->print_title);
				chat_info->print_title = NULL;
			}
			if(chat_info->photo_path) {
				free(chat_info->photo_path);
				chat_info->photo_path = NULL;
			}
			if(chat_info->title) {
				free(chat_info->title);
				chat_info->title = NULL;
			}

		}
	}
}

static Eina_Bool on_change_input_type_requested(void *data)
{
	Evas_Object* text_entry = data;

	elm_entry_input_panel_layout_set(text_entry, ELM_INPUT_PANEL_LAYOUT_EMOTICON);
	elm_object_focus_set(text_entry, EINA_TRUE);
	elm_entry_input_panel_show(text_entry);

	return ECORE_CALLBACK_CANCEL;
}

static void on_message_smiley_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* text_entry = data;
	elm_object_focus_set(obj, EINA_FALSE);
	elm_object_focus_set(text_entry, EINA_FALSE);
	elm_entry_input_panel_hide(text_entry);
	ecore_timer_add(0.3, on_change_input_type_requested, text_entry);
	/*
	elm_entry_input_panel_layout_set(text_entry, ELM_INPUT_PANEL_LAYOUT_EMOTICON);
	elm_object_focus_set(text_entry, EINA_TRUE);
	elm_entry_input_panel_show(text_entry);*/
}

static void on_message_text_entry_clicked(void *data, Evas_Object *obj, void *event_info)
{
	elm_entry_input_panel_hide(obj);
	elm_entry_input_panel_layout_set(obj,ELM_INPUT_PANEL_LAYOUT_NORMAL);
	elm_entry_input_panel_show(obj);
}


Evas_Object* create_chat_genlist(Evas_Object *win)
{
    Evas_Object *genlist;
    Elm_Theme *theme = elm_theme_new();
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_GENLIST_THEME_EDJ, edj_path, (int)PATH_MAX);
	elm_theme_extension_add(theme, edj_path);
    genlist = elm_genlist_add(win);
    elm_object_theme_set(genlist, theme);
    elm_object_style_set(genlist, "telegram/default");
    evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);
    return genlist;
}

void on_list_media_item_clicked(void *data, Evas_Object *obj, void *event_info)
{

}

static Eina_Bool on_new_contact_message_send_cb(void *data)
{
	Evas_Object *chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	ad->msg_count = ad->msg_count + 1001;
	int unique_id = time(NULL) + ad->msg_count;

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = tgl_message_media_contact;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;


	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;

	char *first_name = evas_object_data_get(chat_list, "contact_first_name");
	char *last_name = evas_object_data_get(chat_list, "contact_last_name");
	char *phone_number = evas_object_data_get(chat_list, "contact_phone_number");

	insert_media_info_to_db(&msg, NULL, img_width, img_height, media_size, NULL, NULL, first_name, last_name, phone_number);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, tgl_message_media_contact, NULL, sel_item->use_data->peer_type);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void*)unique_id, NULL, ELM_GENLIST_ITEM_NONE, on_list_media_item_clicked, (void*)unique_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	free(msg.media_id);

	return ECORE_CALLBACK_CANCEL;

}

void send_contact_message_to_buddy(void *data, char *first_name, char *last_name, char *phone_number)
{
	Evas_Object *chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");

	if(add_date_item_to_chat(data)) {

		evas_object_data_set(chat_list, "contact_first_name", strdup(first_name));
		evas_object_data_set(chat_list, "contact_last_name", strdup(last_name));
		evas_object_data_set(chat_list, "contact_phone_number", strdup(phone_number));

		ecore_timer_add(1, on_new_contact_message_send_cb, chat_list);
		return;
	}


	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	ad->msg_count = ad->msg_count + 1001;
	int unique_id = time(NULL) + ad->msg_count;

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = tgl_message_media_contact;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;


	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;
	insert_media_info_to_db(&msg, NULL, img_width, img_height, media_size, NULL, NULL, first_name, last_name, phone_number);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, tgl_message_media_contact, NULL, sel_item->use_data->peer_type);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void*)unique_id, NULL, ELM_GENLIST_ITEM_NONE, on_list_media_item_clicked, (void*)unique_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	free(msg.media_id);
}

static Eina_Bool on_new_location_message_send_cb(void *data)
{
	Evas_Object *chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	ad->msg_count = ad->msg_count + 1001;
	int unique_id = time(NULL) + ad->msg_count;

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = tgl_message_media_geo;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;

	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;

	char *latitude = evas_object_data_get(chat_list, "contact_latitude");
	char *longitude = evas_object_data_get(chat_list, "contact_longitude");

	insert_media_info_to_db(&msg, NULL, img_width, img_height, media_size, latitude, longitude, NULL, NULL, NULL);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, tgl_message_media_geo, NULL, sel_item->use_data->peer_type);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void*)unique_id, NULL, ELM_GENLIST_ITEM_NONE, on_list_media_item_clicked, (void*)unique_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	free(msg.media_id);
	return ECORE_CALLBACK_CANCEL;
}

void send_location_message_to_buddy(void *data, char *latitude, char *longitude)
{
	Evas_Object *chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");

	if(add_date_item_to_chat(data)) {
		evas_object_data_set(chat_list, "contact_latitude", strdup(latitude));
		evas_object_data_set(chat_list, "contact_longitude", strdup(longitude));
		ecore_timer_add(1, on_new_location_message_send_cb, chat_list);
		return;
	}

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	ad->msg_count = ad->msg_count + 1001;
	int unique_id = time(NULL) + ad->msg_count;

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = tgl_message_media_geo;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;

	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;
	insert_media_info_to_db(&msg, NULL, img_width, img_height, media_size, latitude, longitude, NULL, NULL, NULL);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, tgl_message_media_geo, NULL, sel_item->use_data->peer_type);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void*)unique_id, NULL, ELM_GENLIST_ITEM_NONE, on_list_media_item_clicked, (void*)unique_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	free(msg.media_id);
}

static Eina_Bool on_new_media_message_send_cb(void *data)
{
	Evas_Object *chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	ad->msg_count = ad->msg_count + 1001;
	int unique_id = time(NULL) + ad->msg_count;

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	char *file_type_char = evas_object_data_get(chat_list, "file_type");
	int file_type = atoi(file_type_char);
	char *file_path = evas_object_data_get(chat_list, "file_path");

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = file_type;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;

	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;
	if (file_type == tgl_message_media_photo) {
		Evas_Object *img = create_image_object_from_file(file_path, chat_list);
		elm_image_object_size_get(img, &img_width, &img_height);
		struct stat st;
		stat(file_path, &st);
		media_size = st.st_size;
		evas_object_del(img);
	}

	insert_media_info_to_db(&msg, (char*)file_path, img_width, img_height, media_size, NULL, NULL , NULL, NULL, NULL);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, file_type, file_path, sel_item->use_data->peer_type);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void*)unique_id, NULL, ELM_GENLIST_ITEM_NONE, on_list_media_item_clicked, (void*)unique_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	free(msg.media_id);
	ad->is_last_msg_changed = EINA_TRUE;
	return ECORE_CALLBACK_CANCEL;
}

void send_media_message_to_buddy(void *data, const char* file_path, enum tgl_message_media_type file_type)
{
	Evas_Object *chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");
	if(add_date_item_to_chat(data)) {

		int temp_file_type = file_type;
		char file_type_char[10]= {0, };
		sprintf(file_type_char, "%d", temp_file_type);
		evas_object_data_set(chat_list, "file_type", strdup(file_type_char));
		evas_object_data_set(chat_list, "file_path", strdup(file_path));

		ecore_timer_add(1, on_new_media_message_send_cb, chat_list);
		return;
	}
	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	ad->msg_count = ad->msg_count + 1001;
	int unique_id = time(NULL) + ad->msg_count;

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = file_type;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;

	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;
	if (file_type == tgl_message_media_photo) {
		Evas_Object* img = create_image_object_from_file(file_path, chat_list);
		elm_image_object_size_get(img, &img_width, &img_height);
		struct stat st;
		stat(file_path, &st);
		media_size = st.st_size;
		evas_object_del(img);
	}

	insert_media_info_to_db(&msg, (char*)file_path, img_width, img_height, media_size, NULL, NULL , NULL, NULL, NULL);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, file_type, file_path, sel_item->use_data->peer_type);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void*)unique_id, NULL, ELM_GENLIST_ITEM_NONE, on_list_media_item_clicked, (void*)unique_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	free(msg.media_id);
	ad->is_last_msg_changed = EINA_TRUE;
}

static Eina_Bool on_timer_expired(void *data)
{
	Elm_Object_Item* last_item = data;
	if (last_item) {
		elm_genlist_item_show(last_item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	}
	return ECORE_CALLBACK_CANCEL;
}

Eina_Bool load_chat_history(Evas_Object *chat_list)
{
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
	int buddy_id = sel_item->use_data->peer_id;

	char* tablename = get_table_name_from_number(buddy_id);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ID);

	//Eina_List* vals = get_values_from_table_sync(tablename, col_names, col_types, NULL);
	Eina_List* vals = get_values_from_table_sync_order_by(tablename, col_names, col_types, MESSAGE_INFO_TABLE_DATE, EINA_TRUE, NULL);
	Elm_Object_Item* last_item = NULL;
	if(!vals) {
		// set no messages yet
		return EINA_FALSE;
	} else {
		int row_count = eina_list_count(vals);

		if (row_count <= 0) {
			// set no messages yet
			return EINA_FALSE;
		}

		for (int i = 0 ; i < row_count ; i++) {
			Eina_List* row_vals = eina_list_nth(vals, i);
			int* temp_message_id = (int*)eina_list_nth(row_vals, 0);
			int message_id = *temp_message_id;
			static Elm_Genlist_Item_Class itc;
			itc.item_style = "entry";
			itc.func.text_get = NULL;
			itc.func.content_get = on_message_item_content_get_cb;
			itc.func.state_get = NULL;
			itc.func.del = NULL;
			Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void *)message_id, NULL, ELM_GENLIST_ITEM_NONE, on_list_media_item_clicked, (void*)message_id);
			last_item = item;
			elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
			eina_list_free(row_vals);
		}
		eina_list_free(vals);
	}

	Ecore_Timer *timer = NULL;
	timer = ecore_timer_add(5, on_timer_expired, last_item);

	free(tablename);
	return EINA_TRUE;
}



void on_gallery_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		Evas_Object* chat_list = user_data;
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		int status;
		char* mime_type = NULL;
		appdata_s* ad = evas_object_data_get(chat_list, "app_data");

		status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);
		if (status != APP_CONTROL_ERROR_NONE) {
			status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_PATH, &path_arryay,  &array_length);
			if (status != APP_CONTROL_ERROR_NONE) {
				if (ad) {
					show_toast(ad, "Unable to get the result from attach panel");
				}
				return;
			}
		}

		status = app_control_get_mime(reply, &mime_type);
		if (status != APP_CONTROL_ERROR_NONE) {
			if (ad) {
				show_toast(ad, "Unable to get the mime type from attach panel");
			}
			return;
		}

		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);
			send_media_message_to_buddy(chat_list, file_path, tgl_message_media_photo);
			free(file_path);
			//break;
		}
	}
}

void on_location_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	Evas_Object* chat_list = user_data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		char *latitude = NULL;
		char *longitude = NULL;
		app_control_get_extra_data(reply, "latitude", &latitude);
		app_control_get_extra_data(reply, "longitude", &longitude);

		if (latitude && longitude) {
			send_location_message_to_buddy(chat_list, latitude, longitude);
		} else {
			//send_location_message_to_buddy(chat_list, "0.00000000000", "0.00000000000");
			show_toast(ad, "Unable to detect location values.");
		}
	} else {
		show_toast(ad, "Device does not support location feature.");
	}
}

void on_video_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {

		Evas_Object* chat_list = user_data;
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		int status;
		char* mime_type = NULL;
		appdata_s* ad = evas_object_data_get(chat_list, "app_data");

		status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);
		if (status != APP_CONTROL_ERROR_NONE) {
			status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_PATH, &path_arryay,  &array_length);
			if (status != APP_CONTROL_ERROR_NONE) {
				if (ad) {
					show_toast(ad, "Unable to get the result from attach panel");
				}
				return;
			}
		}

		status = app_control_get_mime(reply, &mime_type);
		if (status != APP_CONTROL_ERROR_NONE) {
			if (ad) {
				show_toast(ad, "Unable to get the mime type from attach panel");
			}
			return;
		}
		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);
			send_media_message_to_buddy(chat_list, file_path, tgl_message_media_document);
			free(file_path);
			//break;
		}
	}
}

void on_file_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {

		Evas_Object* chat_list = user_data;
		appdata_s* ad = evas_object_data_get(chat_list, "app_data");
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);

		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);

			// get mime type of the file

			char *mime_type = NULL;
			if (file_path) {
				char *extn = strrchr(file_path, '.');
				if (extn) {
					extn = replace(extn, '.', "");
				}
				if (extn) {
					mime_type_get_mime_type(extn, &mime_type);
				}
			}
			if (mime_type) {
				if (strstr(mime_type, "video") != NULL) {
					send_media_message_to_buddy(chat_list, file_path, tgl_message_media_document);
				} else if (strstr(mime_type, "audio") != NULL) {
					send_media_message_to_buddy(chat_list, file_path, tgl_message_media_document);
				} else if (strstr(mime_type, "image") != NULL) {
					send_media_message_to_buddy(chat_list, file_path, tgl_message_media_photo);
				} else {
					show_toast(ad, "Unsupported file.");
				}
			} else {
				show_toast(ad, "Unsupported file.");
			}
			free(file_path);
			break;
		}
	}
}

static void on_voice_record_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		Evas_Object* chat_list = user_data;

		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		int status;
		char* mime_type = NULL;
		appdata_s* ad = evas_object_data_get(chat_list, "app_data");

		status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);
		if (status != APP_CONTROL_ERROR_NONE) {
			status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_PATH, &path_arryay,  &array_length);
			if (status != APP_CONTROL_ERROR_NONE) {
				if (ad) {
					show_toast(ad, "Unable to get the result from attach panel");
				}
				return;
			}
		}

		status = app_control_get_mime(reply, &mime_type);
		if (status != APP_CONTROL_ERROR_NONE) {
			if (ad) {
				show_toast(ad, "Unable to get the mime type from attach panel");
			}
			return;
		}

		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);
			send_media_message_to_buddy(chat_list, file_path, tgl_message_media_document);
			free(file_path);
			//break;
		}
	}
}

void on_contact_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {

		Evas_Object* chat_list = user_data;
		char *contact_name = NULL;
		char *phone_number = NULL;
		app_control_get_extra_data(reply, "http://tizen.org/appcontrol/data/name", &contact_name);
		app_control_get_extra_data(reply, "http://tizen.org/appcontrol/data/phone", &phone_number);

	}
}

static void _result_cb(attach_panel_h attach_panel, attach_panel_content_category_e content_category, app_control_h result, app_control_result_e result_code, void *user_data)
{
	switch(content_category) {
	case ATTACH_PANEL_CONTENT_CATEGORY_IMAGE:
	case ATTACH_PANEL_CONTENT_CATEGORY_CAMERA:
		on_gallery_app_control_reply_cb(NULL, result, result_code, user_data);
		break;
	case ATTACH_PANEL_CONTENT_CATEGORY_VIDEO:
	case ATTACH_PANEL_CONTENT_CATEGORY_VIDEO_RECORDER:
		on_video_app_control_reply_cb(NULL, result, result_code, user_data);
		break;
	case ATTACH_PANEL_CONTENT_CATEGORY_VOICE:
		on_voice_record_reply_cb(NULL, result, result_code, user_data);
		break;
	case ATTACH_PANEL_CONTENT_CATEGORY_MYFILES:
	case ATTACH_PANEL_CONTENT_CATEGORY_AUDIO:
		on_file_app_control_reply_cb(NULL, result, result_code, user_data);
		break;
	case ATTACH_PANEL_CONTENT_CATEGORY_CONTACT:
		on_contact_app_control_reply_cb(NULL, result, result_code, user_data);
		break;
	default:
		break;
	}

}

void on_media_type_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	const char *label = elm_object_item_text_get((Elm_Object_Item *) event_info);
	if (strcasecmp(label, POPUP_TEXT_TAKE_GALLERY) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}

		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);

		app_control_set_mime(app_control,"image/*");
		app_control_add_extra_data(app_control, APP_CONTROL_DATA_SELECTION_MODE, "single");
		app_control_send_launch_request(app_control, &on_gallery_app_control_reply_cb, data);
		app_control_destroy(app_control);
	} else if (strcasecmp(label, POPUP_TEXT_TAKE_PHOTO) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);
		app_control_set_mime(app_control,"image/jpg");
		//app_control_add_extra_data(app_control, "crop", "caller_id");
		app_control_send_launch_request(app_control, &on_gallery_app_control_reply_cb, data);
		app_control_destroy(app_control);
	} else if (strcasecmp(label, POPUP_TEXT_TAKE_VIDEO) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}

		app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);

		int remain_byte_size = 10485760;
		int request_KB_size = 0;

		if (remain_byte_size >= 1024) {
			request_KB_size = remain_byte_size / 1024;
		} else {
			// TODO: Need to check minimum size for recording
			request_KB_size = 1;
		}

		char recording_size[128] = {0, };
		snprintf(recording_size, sizeof(recording_size), "%d", request_KB_size);
		app_control_set_mime(app_control,"video/3gp");
		app_control_add_extra_data(app_control, "LIMIT", recording_size);
		app_control_add_extra_data(app_control, "RESOLUTION", "VGA");
		app_control_add_extra_data(app_control, "CALLER", "telegram");

		app_control_send_launch_request(app_control, &on_video_app_control_reply_cb, data);
		app_control_destroy(app_control);
	} else if (strcasecmp(label, POPUP_TEXT_TAKE_AUDIO) == 0) {

		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}

		app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);

		int size = 10485760;

        int remain_byte_size = (int)size;
        int request_KB_size = 0;

        if (remain_byte_size >= 1024) {
                request_KB_size = remain_byte_size / 1024;
        } else {
                // TODO: Need to check minimum size for recording
                request_KB_size = 1;
        }

		char recording_size[128] = {0, };
		snprintf(recording_size, sizeof(recording_size), "%d", request_KB_size);
		app_control_add_extra_data(app_control, "SIZE", recording_size);
		app_control_set_mime(app_control,"audio/*");
		app_control_send_launch_request(app_control, &on_voice_record_reply_cb, data);
		app_control_destroy(app_control);

	} else if (strcasecmp(label, POPUP_TEXT_TAKE_FILE) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}

		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);

		app_control_set_mime(app_control,"*/*");
		app_control_add_extra_data(app_control, APP_CONTROL_DATA_SELECTION_MODE, "single");
		app_control_send_launch_request(app_control, &on_file_app_control_reply_cb, data);
		app_control_destroy(app_control);

	} else if (strcasecmp(label, POPUP_TEXT_TAKE_LOCATION) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load location picker");
			return;
		}
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);
		//app_control_set_app_id(app_control, "com.here.tizen.maps");
		app_control_set_uri(app_control, "geo");
		app_control_send_launch_request(app_control, &on_location_app_control_reply_cb, data);
		app_control_destroy(app_control);
	} else if (strcasecmp(label, POPUP_TEXT_TAKE_CONTACT) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load location picker");
			return;
		}
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);
		app_control_set_mime(app_control,"application/vnd.tizen.contact");
		app_control_add_extra_data(app_control, APP_CONTROL_DATA_SELECTION_MODE, "single");
		app_control_send_launch_request(app_control, &on_contact_app_control_reply_cb, data);
		app_control_destroy(app_control);
	}

	evas_object_del(obj);
}


void popup_move_dropdown(Evas_Object *ctxpopup, Evas_Object *btn)
{
	Evas_Coord x, y, w , h;
	evas_object_geometry_get(btn, &x, &y, &w, &h);
	evas_object_move(ctxpopup, x + (w / 2), y + h - 50);
}

void on_media_attach_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(obj);
}

static void on_media_attach_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* chat_list = data;
	appdata_s *ad = evas_object_data_get(chat_list, "app_data");
	attach_panel_h attach_panel = NULL;
	int ret;
	bool visible = false;

	attach_panel = evas_object_data_get(ad->conform, "attach_panel");
	if (attach_panel) {
			if (attach_panel_get_visibility(attach_panel, &visible) != ATTACH_PANEL_ERROR_NONE) {
				return;
			}
			if (!visible) {
				attach_panel_show(attach_panel);
			}
			return;
		}

	ret = attach_panel_create(ad->conform, &attach_panel);

	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_IMAGE, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_CAMERA, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_VOICE, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_VIDEO, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_AUDIO, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_CONTACT, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_VIDEO_RECORDER, NULL);
	attach_panel_set_result_cb(attach_panel, _result_cb, chat_list);

	attach_panel_show(attach_panel);
	evas_object_data_set(ad->conform, "attach_panel", attach_panel);

}

#if 0
static void on_text_message_send_pressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(SEND_UNPRESSED_ICON), NULL);
}

static void on_text_message_send_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(SEND_PRESSED_ICON), NULL);
}
#endif

static void on_message_smiley_pressed(void *data, Evas_Object *obj, void *event_info)
{
	if (data)
		evas_object_color_set(data, 45, 165, 224, 255);
}

static void on_message_smiley_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	if (data)
		evas_object_color_set(data, 45, 165, 224, 178);
}

void on_message_back_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad)
		return;

	app_nf_back_cb(data, obj, event_info);
}

void on_user_info_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;

	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	tg_peer_info_s *user_data = sel_item->use_data;

	if (!sel_item || !user_data) {
		show_toast(ad, "Can not display user info");
		return;
	}

	if (user_data->peer_type == TGL_PEER_USER) {
		launch_user_info_screen(ad, user_data->peer_id);
	} else if (user_data->peer_type == TGL_PEER_CHAT) {
		launch_chat_info_screen(ad, user_data->peer_id);
	} else {

	}
}

void refresh_messaging_view(appdata_s *ad)
{
	if (!ad)
		return;

	Evas_Object *chat_conv_list = evas_object_data_get(ad->nf, "chat_list");
	if (!chat_conv_list) {
		Evas_Coord w, h;
		elm_win_screen_size_get(ad->win, NULL, NULL, &w, &h);
		evas_object_size_hint_min_set(chat_conv_list, w, h);
	}
}

void launch_messaging_view_cb(appdata_s* ad, int user_id)
{
	if (!ad)
		return;

	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}

	ad->current_app_state = TG_CHAT_MESSAGING_VIEW_STATE;
	ad->is_last_msg_changed = EINA_FALSE;
	send_request_for_server_connection_status(ad->service_client);
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* main_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(main_layout, edj_path, "main_list_custom_item");
	evas_object_size_hint_weight_set(main_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(main_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(main_layout);


	Evas_Object *layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "chat_messaging_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);



	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
	tg_peer_info_s* user = sel_item->use_data;


	/*************************** message list ************************************/

	Evas_Object* msg_box_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(msg_box_layout, edj_path, "custom_gen_list");
	evas_object_size_hint_weight_set(msg_box_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(msg_box_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(msg_box_layout);

	Evas_Object *list_bg = elm_image_add(msg_box_layout);
	evas_object_size_hint_align_set(list_bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(list_bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	if (ad->chat_background) {
		elm_image_file_set(list_bg, ad->chat_background, NULL);
	} else {
		elm_image_file_set(list_bg, ui_utils_get_resource(TG_CHAT_DEFAULT_BG), NULL);
	}
    elm_image_resizable_set(list_bg, EINA_TRUE, EINA_TRUE);
    elm_image_fill_outside_set(list_bg, EINA_TRUE);
    evas_object_show(list_bg);

    elm_object_part_content_set(msg_box_layout, "swallow.gen_list.bg", list_bg);
	Evas_Object *chat_conv_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(chat_conv_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(chat_conv_list, ELM_LIST_COMPRESS);
	elm_object_style_set(chat_conv_list, "solid/default");
	evas_object_size_hint_weight_set(chat_conv_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(chat_conv_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	// FIXME: Deprecated API
	//elm_genlist_realization_mode_set(chat_conv_list, EINA_TRUE);
	//evas_object_color_set(chat_conv_list, 255 , 255, 255, 255);

	evas_object_show(chat_conv_list);


	elm_object_part_content_set(msg_box_layout, "swallow.gen_list", chat_conv_list);


	elm_object_part_content_set(layout, "swallow.chat_box", msg_box_layout);

	/*************************** message list ************************************/


	/********************** title layout ******************************/

	Evas_Object *title_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(title_layout, edj_path, "message_title_box");
	evas_object_size_hint_weight_set(title_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(title_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(title_layout);

	Evas_Object *profile_pic = NULL;
	profile_pic = elm_image_add(layout);
	evas_object_size_hint_weight_set(profile_pic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(profile_pic, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_focus_set(profile_pic, EINA_FALSE);

	if (user->photo_path && strcmp(user->photo_path, "") != 0) {
		elm_image_file_set(profile_pic, user->photo_path, NULL);
	} else {
		if (user->peer_type == TGL_PEER_USER) {
			elm_image_file_set(profile_pic, ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC), NULL);
		} else if (user->peer_type == TGL_PEER_CHAT) {
			elm_image_file_set(profile_pic, ui_utils_get_resource(DEFAULT_LIST_THUMB_MULTI_PIC), NULL);
		} else {

		}
		evas_object_color_set(profile_pic, 45, 165, 224, 255);
	}

	elm_object_focus_set(profile_pic, EINA_FALSE);
	evas_object_show(profile_pic);
	Evas_Object *user_pic_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(user_pic_layout, edj_path, "msg_circle_layout");
	evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(user_pic_layout);
	elm_object_part_content_set(user_pic_layout, "content", profile_pic);
	evas_object_data_set(ad->nf, "profile_picture", (void*)profile_pic);
	elm_object_part_content_set(title_layout, "swallow.profile_pic", user_pic_layout);

	elm_object_part_content_set(main_layout, "swallow.item", title_layout);

	Evas_Object *back_btn = create_button(ad->nf, "naviframe/back_btn/default", NULL);
	evas_object_smart_callback_add(back_btn, "clicked", on_message_back_button_clicked, ad);
	elm_object_part_content_set(title_layout, "swallow.back_arrow", back_btn);



	Evas_Object *profile_name = elm_label_add(title_layout);
	if ((user->peer_type == TGL_PEER_USER) && get_buddy_unknown_status(user->peer_id)) {
		char temp_name[512] = {'\0'};
		snprintf(temp_name, 512, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=40>%s</font_size></font>", get_buddy_phone_num_from_id(sel_item->use_data->peer_id));
		elm_object_text_set(profile_name,temp_name);
	} else {
		char* user_name = replace(sel_item->use_data->print_name, '_', " ");
		char temp_name[512] = {'\0'};
		snprintf(temp_name, 512, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=40>%s</font_size></font>", user_name);
		free(user_name);
		elm_object_text_set(profile_name,temp_name);
	}

	evas_object_size_hint_align_set(profile_name, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(profile_name, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_style_set(profile_name, "transparent");
	evas_object_show(profile_name);
	elm_object_part_content_set(title_layout, "swallow.profile_name", profile_name);
	evas_object_data_set(ad->nf, "profile_title", (void*)profile_name);
	evas_object_smart_callback_add(profile_name, "clicked", on_user_info_button_clicked, ad);

	Evas_Object *profile_time = elm_label_add(title_layout);
	evas_object_size_hint_align_set(profile_time, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(profile_time, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(profile_time);
	elm_object_part_content_set(title_layout, "swallow.profile_time", profile_time);
	evas_object_data_set(ad->nf, "profile_time", (void*)profile_time);
	evas_object_smart_callback_add(profile_time, "clicked", on_user_info_button_clicked, ad);

	//elm_object_content_set(title_scroller, title_layout);

	on_user_presence_state_changed(ad, sel_item->use_data->peer_id);

	elm_object_part_content_set(layout, "swallow.title_box", main_layout);

	/********************** title layout ******************************/

	/********************** entry layout*******************************/
	Evas_Object* entry_box_layout = elm_layout_add(ad->win);
	elm_layout_file_set(entry_box_layout, edj_path, "chat_entry_box");
	evas_object_size_hint_align_set(entry_box_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(entry_box_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(entry_box_layout);


	Evas_Object* attach_btn = elm_button_add(entry_box_layout);
	elm_object_style_set(attach_btn, "transparent");
	evas_object_size_hint_align_set(attach_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(attach_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	Evas_Object* attach_icon = elm_image_add(entry_box_layout);
	evas_object_size_hint_align_set(attach_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(attach_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_image_file_set(attach_icon, ui_utils_get_resource(TG_ATTACH_ICON), NULL);
    evas_object_show(attach_icon);
    evas_object_color_set(attach_icon, 45, 165, 224, 178);

	Evas_Object* attach_pic_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(attach_pic_layout, edj_path, "circle_layout");
	evas_object_size_hint_weight_set(attach_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(attach_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(attach_pic_layout);
	elm_object_part_content_set(attach_pic_layout, "content", attach_icon);
    elm_object_content_set(attach_btn, attach_pic_layout);

    //evas_object_smart_callback_add(attach_btn, "clicked", on_media_attach_clicked, chat_conv_list);
    evas_object_smart_callback_add(attach_btn, "pressed", on_message_smiley_pressed, attach_icon);
    evas_object_smart_callback_add(attach_btn, "unpressed", on_message_smiley_unpressed, attach_icon);
	elm_object_part_content_set(entry_box_layout, "swallow.attach_icon", attach_btn);

	Evas_Object* text_entry = elm_entry_add(entry_box_layout);
	elm_object_part_text_set(text_entry, "elm.guide", "<font=Tizen:style=Italic color=#A8A8A8 valign=middle><font_size=35>Text message</font_size></font>");
	elm_entry_line_wrap_set(text_entry, EINA_TRUE);
	evas_object_size_hint_align_set(text_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(text_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(text_entry);
	elm_entry_scrollable_set(text_entry, EINA_TRUE);
	evas_object_smart_callback_add(text_entry, "clicked", on_message_text_entry_clicked, ad);
	elm_object_part_content_set(entry_box_layout, "swallow.text_entry", text_entry);

	elm_entry_text_style_user_push(text_entry, "DEFAULT='font_size=32 color=#000000 align=left font=Tizen:style=Italic'");

	//evas_object_data_set(chat_conv_list, "text_entry", (void*)text_entry);


	Evas_Object* smiley_btn = elm_button_add(entry_box_layout);
	elm_object_style_set(smiley_btn, "transparent");
	evas_object_size_hint_align_set(smiley_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(smiley_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	Evas_Object* smiley_icon = elm_image_add(entry_box_layout);
	evas_object_size_hint_align_set(smiley_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(smiley_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	elm_image_file_set(smiley_icon, ui_utils_get_resource(TG_SMILEY_ICON), NULL);

    elm_image_resizable_set(smiley_icon, EINA_TRUE, EINA_TRUE);
    evas_object_show(smiley_icon);
    evas_object_color_set(smiley_icon, 45, 165, 224, 178);

	Evas_Object* smiley_pic_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(smiley_pic_layout, edj_path, "circle_layout");
	evas_object_size_hint_weight_set(smiley_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(smiley_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(smiley_pic_layout);
	elm_object_part_content_set(smiley_pic_layout, "content", smiley_icon);

    elm_object_content_set(smiley_btn, smiley_pic_layout);

    evas_object_smart_callback_add(smiley_btn, "clicked", on_message_smiley_clicked, text_entry);


    evas_object_smart_callback_add(smiley_btn, "pressed", on_message_smiley_pressed, smiley_icon);
    evas_object_smart_callback_add(smiley_btn, "unpressed", on_message_smiley_unpressed, smiley_icon);


    elm_object_part_content_set(entry_box_layout, "swallow.smiely_icon", smiley_btn);

	Evas_Object* send_btn = elm_button_add(entry_box_layout);
	elm_object_style_set(send_btn, "transparent");
	evas_object_size_hint_align_set(send_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(send_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	Evas_Object* send_icon = elm_image_add(entry_box_layout);
	evas_object_size_hint_align_set(send_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(send_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_image_file_set(send_icon, ui_utils_get_resource(TG_SEND_ICON), NULL);
    evas_object_show(send_icon);
    evas_object_color_set(send_icon, 45, 165, 224, 178);
	Evas_Object* send_pic_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(send_pic_layout, edj_path, "circle_layout");
	evas_object_size_hint_weight_set(send_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(send_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(send_pic_layout);
	elm_object_part_content_set(send_pic_layout, "content", send_icon);

    elm_object_content_set(send_btn, send_pic_layout);

    evas_object_smart_callback_add(send_btn, "clicked", on_text_message_send_clicked, chat_conv_list);
    evas_object_smart_callback_add(send_btn, "pressed", on_message_smiley_pressed, send_icon);
    evas_object_smart_callback_add(send_btn, "unpressed", on_message_smiley_unpressed, send_icon);
	elm_object_part_content_set(entry_box_layout, "swallow.send_icon", send_btn);

	//elm_object_part_content_set(layout, "swallow.entry_box", entry_box_layout);
	/********************** entry layout*******************************/

	evas_object_data_set(ad->nf, "chat_list", (void*)chat_conv_list);
	evas_object_data_set(chat_conv_list, "app_data", ad);
	evas_object_data_set(chat_conv_list, "user_id", (void*)user_id);
	evas_object_data_set(chat_conv_list, "text_entry", (void*)text_entry);
	evas_object_data_set(chat_conv_list, "profile_time", (void*)profile_time);

	Elm_Object_Item *nf_it = elm_naviframe_item_simple_push(ad->nf, scroller);

	elm_object_item_part_content_set(nf_it, "toolbar", entry_box_layout);

	Eina_Bool ret = load_chat_history(chat_conv_list);

	if (!ret) {
		// show no messages
		Evas_Object *no_msg_lbl = elm_label_add(ad->nf);
		evas_object_size_hint_align_set(no_msg_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(no_msg_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_show(no_msg_lbl);
		char temp_msg[4*256] = {0,};
		snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Bold color=#000000 align=center><font_size=30>%s</font_size></font>", "No messages here yet...");
		elm_object_text_set(no_msg_lbl, temp_msg);
		elm_object_part_content_set(layout, "swallow.no_msg_text", no_msg_lbl);
		evas_object_data_set(ad->nf, "chat_list_no_msg_text", (void*)no_msg_lbl);
	}

	send_request_for_marked_as_read(ad->service_client, sel_item->use_data->peer_id, sel_item->use_data->peer_type);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_MORE, on_messaging_menu_button_clicked, ad);
}

