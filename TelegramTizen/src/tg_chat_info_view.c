/*
 * tg_chat_info_view.c
 *
 *  Created on: Oct 3, 2015
 *      Author: sandeep
 */

#include "tg_chat_info_view.h"
#include "tg_db_wrapper.h"
#include "server_requests.h"
#include "tg_select_buddy_from_list.h"

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

static Eina_Bool on_view_deleteion_requested(void *data)
{
	appdata_s *ad = data;
	if (ad) {
		elm_naviframe_item_pop(ad->nf);
		ad->current_app_state = TG_USER_MAIN_VIEW_STATE;
		hide_loading_popup(ad);
	}
    return ECORE_CALLBACK_CANCEL;
}

void on_group_chat_deleted(appdata_s *ad, int chat_id)
{
	if (!ad) {
		return;
	}
	ad->peer_in_cahtting_data = NULL;
	ad->main_item_in_cahtting_data = NULL;
	show_loading_popup(ad);
	elm_naviframe_item_pop(ad->nf);
	ad->current_app_state = TG_SET_CHAT_INFO_STATE;
	ecore_timer_add(2, on_view_deleteion_requested, ad);
}

Evas_Object* on_chat_info_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *profile_pic = NULL;

		if (ad->peer_in_cahtting_data->use_data->photo_path && strlen(ad->peer_in_cahtting_data->use_data->photo_path) > 0 && strstr(ad->peer_in_cahtting_data->use_data->photo_path, "_null_") == NULL) {
			profile_pic = get_image_from_path(ad->peer_in_cahtting_data->use_data->photo_path, ad->nf);
		} else  {
			profile_pic = get_image_from_path(ui_utils_get_resource(DEFAULT_PROFILE_PIC), ad->nf);
		}
		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(user_pic_layout, edj_path, "circle_layout");
		evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(user_pic_layout);
		elm_object_part_content_set(user_pic_layout, "content", profile_pic);

		evas_object_data_set(ad->nf, "user_chat_profile_pic", profile_pic);

		eo = elm_layout_add(obj);
		elm_layout_theme_set(eo, "layout", "list/C/type.1", "default");
		elm_layout_content_set(eo, "elm.swallow.content", user_pic_layout);
	} else if (!strcmp(part, "elm.swallow.icon.0")) {
		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		Evas_Object* user_status_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(user_status_layout, edj_path, "main_list_name_status_item");
		evas_object_size_hint_weight_set(user_status_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(user_status_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(user_status_layout);


		char* user_name = replace(ad->peer_in_cahtting_data->use_data->print_name, '_', " ");
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<font=Tizen:style=Bold color=#FFFFFF align=left><font_size=40>%s</font_size></font>", user_name);
		free(user_name);

		Evas_Object*  name_lbl = elm_label_add(ad->nf);
		elm_object_text_set(name_lbl, buf);
		evas_object_size_hint_weight_set(name_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(name_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(name_lbl);

		elm_object_part_content_set(user_status_layout, "swallow.name", name_lbl);

		evas_object_data_set(ad->nf, "chat_info_name", name_lbl);

		Evas_Object *profile_time = evas_object_data_get(ad->nf, "profile_time");
		char *online_status = "";
		if (profile_time) {
			online_status = elm_entry_markup_to_utf8(elm_object_text_get(profile_time));
		}

		//char* user_status = "online";
		char status_buf[126] = {'\0'};
		sprintf(status_buf, "<font=Tizen:style=Italic color=#FFFFFF align=left><font_size=35>%s</font_size></font>", online_status);

		Evas_Object*  status_lbl = elm_label_add(ad->nf);
		elm_object_text_set(status_lbl, status_buf);
		evas_object_size_hint_weight_set(status_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(status_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(status_lbl);
		evas_object_data_set(ad->nf, "chat_info_status", status_lbl);
		elm_object_part_content_set(user_status_layout, "swallow.status", status_lbl);
		return user_status_layout;
	} else {

	}
	return eo;
}



char* on_chat_info_buddy_name_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int)data;
	Eina_List* selected_buddies = evas_object_data_get(obj, "selected_buddies");


	int size = eina_list_count(selected_buddies);
	if (size <= 0) {
		if (!strcmp(part,"elm.text")){
			char buf[512] = {'\0'};
			snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", "No Items");
			return strdup(buf);

		} else if (!strcmp(part, "elm.text.sub")) {
			return NULL;
		}
	}

	user_data_s *user = eina_list_nth(selected_buddies, id);
	if (!user)
		return NULL;

	if (!strcmp(part,"elm.text")){
		char* user_name = replace(user->print_name, '_', " ");
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", user_name);
		free(user_name);
		return strdup(buf);

	}

	return NULL;
}

Evas_Object* on_chat_info_buddy_selection_part_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.swallow.icon")) {

		int id = (int) data;
		Eina_List* selected_buddies = evas_object_data_get(obj, "selected_buddies");
		int size = eina_list_count(selected_buddies);
		if (size <= 0) {
			return eo;
		}
		user_data_s *user = eina_list_nth(selected_buddies, id);
		Evas_Object *profile_pic = NULL;
		if (user->photo_path && strcmp(user->photo_path, "") != 0) {
			profile_pic = get_image_from_path(user->photo_path, obj);
		} else {
			profile_pic = get_image_from_path(ui_utils_get_resource(DEFAULT_PROFILE_PIC), obj);
		}

		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		Evas_Object* user_pic_layout = elm_layout_add(obj);
		elm_layout_file_set(user_pic_layout, edj_path, "circle_layout");
		evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(user_pic_layout);
		elm_object_part_content_set(user_pic_layout, "content", profile_pic);

		eo = elm_layout_add(obj);
		elm_layout_theme_set(eo, "layout", "list/C/type.3", "default");
		elm_layout_content_set(eo, "elm.swallow.content", user_pic_layout);
	}
	return eo;

}


void on_chat_image_select_result_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);

		for(int i = 0 ; i < array_length ; i++) {
			file_path = path_arryay[i];
			if (file_path) {
				appdata_s *ad = (appdata_s*)user_data;
				if (ad) {
					Evas_Object *profile_pic = evas_object_data_get(ad->nf, "user_chat_profile_pic");
					if (profile_pic) {
						elm_image_file_set(profile_pic, file_path, NULL);
						send_set_group_chat_profile_pic_request(ad, ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id, file_path);
					}
				}
				break;
			}
		}
	}
}


void on_chat_image_request_option_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;
	int id = 0;
	Elm_Object_Item *item = event_info;

	id = (int)elm_object_item_data_get(item);
	app_control_h app_control;
	int ret = app_control_create(&app_control);


	appdata_s *ad = evas_object_data_get(popup, "app_data");

	if(ret != APP_CONTROL_ERROR_NONE) {
		show_toast(ad, "Error: Can not load image picker");
		return;
	}

	if (id  == 0) {
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);
		app_control_set_mime(app_control, "image/jpg");
		app_control_send_launch_request(app_control, &on_chat_image_select_result_cb, ad);
	} else {
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);
		app_control_set_mime(app_control,"image/*");
		app_control_send_launch_request(app_control, &on_chat_image_select_result_cb, ad);
	}

	app_control_destroy(app_control);
	evas_object_del(popup);
}

char* on_chat_camera_load_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	if (id == 0) {
		return strdup("Camera");
	} else {
		return strdup("Gallery");
	}
}

void on_chat_camera_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* cam_icon =  data;
	appdata_s* ad = evas_object_data_get(data, "app_data");
	static Elm_Genlist_Item_Class itc;
	Evas_Object *popup;
	Evas_Object *box;
	Evas_Object *genlist;
	int i;
	Evas_Object *win = ad->win;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	elm_object_part_text_set(popup, "title,text", "Load image from");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_data_set(popup, "cam_icon", cam_icon);
	evas_object_data_set(popup, "app_data", ad);
	/* box */
	box = elm_box_add(popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* genlist */
	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	itc.item_style = "default";
	itc.func.text_get = on_chat_camera_load_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < 2; i++) {
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_chat_image_request_option_selected_cb, popup);
	}
	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);
	evas_object_size_hint_min_set(box, -1, 230);
	elm_object_content_set(popup, box);

	evas_object_show(popup);
}


user_data_with_pic_s* is_present_in_buddy_list(appdata_s* ad, int buddy_id)
{
	if (ad->buddy_list) {
		for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
			user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
			user_data_s* user = item->use_data;
			if (user->user_id.id == buddy_id) {
				return item;
			}
		}
	}
	return NULL;
}

user_data_with_pic_s* is_present_in_unknown_buddy_list(appdata_s* ad, int buddy_id)
{
	if (ad->unknown_buddy_list) {
		for (int i = 0 ; i < eina_list_count(ad->unknown_buddy_list) ; i++) {
			user_data_with_pic_s *item = eina_list_nth(ad->unknown_buddy_list, i);
			user_data_s* user = item->use_data;
			if (user->user_id.id == buddy_id) {
				return item;
			}
		}
	}
	return NULL;
}


/************************* menu *************************/


/************ edit name ***************/


void on_group_chat_info_updated(appdata_s *ad, char *type_of_change)
{
	if (!ad || !type_of_change) {
		return;
	}
	if (strstr(type_of_change, "edit_title") != NULL) {
		peer_with_pic_s *sel_item = ad->peer_in_cahtting_data;
		if (sel_item) {
			char* user_name = replace(sel_item->use_data->print_name, '_', " ");
			char temp_name[512] = {'\0'};
			snprintf(temp_name, 512, "<font=Tizen:style=Italic color=#000000 align=left><font_size=30>%s</font_size></font>", user_name);
			free(user_name);
			Evas_Object *profile_name = evas_object_data_get(ad->nf, "chat_info_name");
			if (profile_name) {
				elm_object_text_set(profile_name,temp_name);
			}
		}
	} else if (strstr(type_of_change, "delete_photo") != NULL) {

	} else if (strstr(type_of_change, "add_user") != NULL || strstr(type_of_change, "delete_user") != NULL) {
		Evas_Object *status_lbl = evas_object_data_get(ad->nf, "chat_info_status");
		if (status_lbl) {
			Evas_Object *profile_time = evas_object_data_get(ad->nf, "profile_time");
			char *online_status = "";
			if (profile_time) {
				online_status = elm_entry_markup_to_utf8(elm_object_text_get(profile_time));
			}

			//char* user_status = "online";
			char status_buf[126] = {'\0'};
			sprintf(status_buf, "<font=Tizen:style=Italic color=#FFFFFF align=left><font_size=35>%s</font_size></font>", online_status);
			elm_object_text_set(status_lbl, status_buf);
		}


		Evas_Object *users_list = evas_object_data_get(ad->nf, "group_chat_user_list");
		if (users_list) {

			Eina_List* selected_buddies = evas_object_data_get(users_list, "selected_buddies");
			if (selected_buddies) {
				eina_list_free(selected_buddies);
				selected_buddies = NULL;
			}

			elm_genlist_clear(users_list);
			static Elm_Genlist_Item_Class sitc;
			sitc.item_style = "default_style";
			sitc.func.text_get = on_chat_info_buddy_name_get_cb;
			sitc.func.content_get = on_chat_info_buddy_selection_part_content_get_cb;
			sitc.func.state_get = NULL;
			sitc.func.del = NULL;

			/************** selected buddies **************/
			tg_chat_info_s* chat_info = get_chat_info(ad->peer_in_cahtting_data->use_data->peer_id);
			if (chat_info) {
				int mem_cnt = 0;
				selected_buddies = eina_list_append(selected_buddies, ad->current_user_data);
				mem_cnt++;
				int user_list_size = chat_info->user_list_size;

				for (int i = 0; i < user_list_size; i++) {
					user_data_with_pic_s *item = is_present_in_buddy_list(ad, chat_info->chat_users[i]);
					if (item) {
						selected_buddies = eina_list_append(selected_buddies, item->use_data);
						mem_cnt++;
					} else {
						user_data_with_pic_s *item = is_present_in_unknown_buddy_list(ad, chat_info->chat_users[i]);
						if (item) {
							selected_buddies = eina_list_append(selected_buddies, item->use_data);
							mem_cnt++;
						}
					}
				}

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


				for (int i = 0 ; i < mem_cnt; i++) {
					elm_genlist_item_append(users_list, &sitc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
				}
			}

			/************** selected buddies **************/

			evas_object_show(users_list);
			evas_object_data_set(users_list, "selected_buddies", (void*)selected_buddies);
		}

	}  else {

	}
}

static void on_entry_pop_up_ok_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;

	appdata_s *ad = evas_object_data_get(popup, "app_data");
	Evas_Object *entry = evas_object_data_get(popup, "title_entry");

	if (entry) {
		char *new_title = elm_entry_markup_to_utf8(elm_object_text_get(entry));
		if (new_title) {
			//send request to server.
			int chat_id = ad->peer_in_cahtting_data->use_data->peer_id;
			send_set_group_chat_new_title_request(ad, ad->service_client, chat_id, new_title);
		}
	}
	evas_object_del(popup);
}

static void on_entry_pop_up_cancel_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;
	evas_object_del(popup);
}


static void set_new_name_to_chat(appdata_s *ad)
{
	Evas_Object *popup, *btn;
	Evas_Object *entry;
	Evas_Object *layout;

	/* popup */
	popup = elm_popup_add(ad->nf);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(popup, "title,text", "Title");

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_POPUP_VIEW_EDJ, edj_path, (int)PATH_MAX);

	layout = elm_layout_add(popup);
	elm_layout_file_set(layout, edj_path, "popup_input_text");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(popup, layout);

	entry = elm_entry_add(layout);
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	eext_entry_selection_back_event_allow_set(entry, EINA_TRUE);
	elm_object_part_text_set(entry, "elm.guide", "New title");
	elm_object_part_content_set(layout, "elm.swallow.content" , entry);

	evas_object_data_set(popup, "app_data", ad);
	evas_object_data_set(popup, "title_entry", entry);


	/* Cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", on_entry_pop_up_cancel_clicked_cb, popup);

	/* Set button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Ok");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", on_entry_pop_up_ok_clicked_cb, popup);

	evas_object_show(popup);
}

/************ edit name ***************/


void on_chat_info_longpress_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;


	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	int id = (int)elm_object_item_data_get(it);


	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	tg_peer_info_s *user_data = sel_item->use_data;

	if (!sel_item || !user_data) {
		show_toast(ad, "Failed to get user info.");
		return;
	}

	if (user_data->peer_type == TGL_PEER_USER) {

	} else if (user_data->peer_type == TGL_PEER_CHAT) {
		if (id == 0) {
			if (ad->selected_buddy_item) {
				user_data_s *sel_user = ad->selected_buddy_item;
				show_loading_popup(ad);
				send_remove_buddy_from_group_chat_request(ad, ad->service_client, ad->selected_buddy_item->user_id.id, ad->peer_in_cahtting_data->use_data->peer_id);
			}
		}
	}

	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
}


char* on_chat_info_longpress_menu_group_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	if (id == 0) {
		return strdup("Add member");
	} else if (id == 1) {
		return strdup("Edit Name");
	} else {
		return strdup("Delete and leave group");
	}
}

void on_chat_info_msg_popup_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
}

void on_chat_info_menu_option_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;


	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	int id = (int)elm_object_item_data_get(it);


	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	tg_peer_info_s *user_data = sel_item->use_data;

	if (!sel_item || !user_data) {
		show_toast(ad, "Failed to get user info.");
		return;
	}

	if (user_data->peer_type == TGL_PEER_USER) {



	} else if (user_data->peer_type == TGL_PEER_CHAT) {

		if (id == 0) {
			launch_select_buddy_view(ad);
		} else if (id == 1) {
			set_new_name_to_chat(ad);
		} else if (id == 2) {

			peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
			tg_peer_info_s *user_data = sel_item->use_data;
			show_loading_popup(ad);
			send_delete_group_chat_request(ad, ad->service_client, user_data->peer_id);
		} else {

		}

	}

	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
}

void on_chat_info_menu_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (ad->msg_popup || ad->current_app_state != TG_SET_CHAT_INFO_STATE) {
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
	eext_object_event_callback_add(ad->msg_popup, EEXT_CALLBACK_BACK, on_chat_info_msg_popup_back_cb, ad);
	evas_object_size_hint_weight_set(ad->msg_popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_data_set(ad->msg_popup, "app_data", ad);
	box = elm_box_add(ad->msg_popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	itc.item_style = "default";
	itc.func.text_get = on_chat_info_longpress_menu_group_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < 3; i++) {
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_chat_info_menu_option_selected_cb, ad);
	}

	evas_object_data_set(genlist, "app_data", ad);

	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);
	evas_object_size_hint_min_set(box, -1, 345);
	elm_object_content_set(ad->msg_popup, box);
	evas_object_show(ad->msg_popup);
}

char* on_chat_info_longpress_menu_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	if (id == 0) {
		return strdup("Remove from group");
	}
	return NULL;
}

static void on_user_list_longpress(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *item = event_info;
	int id = -1;
	id = (int)elm_object_item_data_get(item);

	if (id ==0) {
		return;
	}
	appdata_s *ad = data;
	Eina_List* selected_buddies = evas_object_data_get(obj, "selected_buddies");
	user_data_s *user = eina_list_nth(selected_buddies, id);

	ad->selected_buddy_item = user;

	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}

	if (ad->current_app_state != TG_SET_CHAT_INFO_STATE) {
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
	eext_object_event_callback_add(ad->msg_popup, EEXT_CALLBACK_BACK, on_chat_info_msg_popup_back_cb, ad);
	evas_object_size_hint_weight_set(ad->msg_popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_data_set(ad->msg_popup, "app_data", ad);
	box = elm_box_add(ad->msg_popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	itc.item_style = "default";
	itc.func.text_get = on_chat_info_longpress_menu_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < 1; i++) {
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_chat_info_longpress_clicked_cb, ad);
	}

	evas_object_data_set(genlist, "app_data", ad);

	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);
	evas_object_size_hint_min_set(box, -1, 115);
	elm_object_content_set(ad->msg_popup, box);
	evas_object_show(ad->msg_popup);
}

void on_user_list_item_selected(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
}

/************************* menu *************************/

void launch_chat_info_screen(appdata_s* ad, int chat_id)
{
	if (!ad) {
		return;
	}
	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}

	ad->selected_buddy_item = NULL;
	ad->current_app_state = TG_SET_CHAT_INFO_STATE;

	load_unknown_buddy_list_data(ad);

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "chat_info_screen");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);


	/**************** user info *********************/
	Evas_Object *pic_name_list = NULL;

	pic_name_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(pic_name_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(pic_name_list, ELM_LIST_COMPRESS);
	elm_object_style_set(pic_name_list, "solid/default");
	evas_object_size_hint_weight_set(pic_name_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(pic_name_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_data_set(pic_name_list, "app_data", ad);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "type1";
	itc.func.text_get = NULL;
	itc.func.content_get = on_chat_info_requested;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	int i = 1;
	elm_genlist_item_append(pic_name_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);

	evas_object_show(pic_name_list);
	elm_object_part_content_set(layout, "pic_name_layout", pic_name_list);
	/******************* user Info **********************/


	Evas_Object* user_info_lbl = elm_label_add(ad->nf);
	evas_object_show(user_info_lbl);
	evas_object_size_hint_weight_set(user_info_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(user_info_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(user_info_lbl, "<font=Tizen:style=Bold color=#00FFFF align=left><font_size=45>&nbsp;&nbsp;Info</font_size></font>");
	elm_object_part_content_set(layout, "user_info", user_info_lbl);


	/******************** Phone num layout ********************/

	Evas_Object *users_list = NULL;

	users_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(users_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(users_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(users_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(users_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_data_set(users_list, "app_data", ad);

	static Elm_Genlist_Item_Class sitc;
	sitc.item_style = "default_style";
	sitc.func.text_get = on_chat_info_buddy_name_get_cb;
	sitc.func.content_get = on_chat_info_buddy_selection_part_content_get_cb;
	sitc.func.state_get = NULL;
	sitc.func.del = NULL;

	/************** selected buddies **************/
	Eina_List* selected_buddies = NULL;
	tg_chat_info_s* chat_info = get_chat_info(chat_id);
	if (chat_info) {
		int mem_cnt = 0;
		selected_buddies = eina_list_append(selected_buddies, ad->current_user_data);
		mem_cnt++;
		int user_list_size = chat_info->user_list_size;

		for (int i = 0; i < user_list_size; i++) {
			user_data_with_pic_s *item = is_present_in_buddy_list(ad, chat_info->chat_users[i]);
			if (item) {
				selected_buddies = eina_list_append(selected_buddies, item->use_data);
				mem_cnt++;
			} else {
				user_data_with_pic_s *item = is_present_in_unknown_buddy_list(ad, chat_info->chat_users[i]);
				if (item) {
					selected_buddies = eina_list_append(selected_buddies, item->use_data);
					mem_cnt++;
				}
			}
		}

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


		for (int i = 0 ; i < mem_cnt; i++) {
			elm_genlist_item_append(users_list, &sitc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
		}
	}


	evas_object_smart_callback_add(users_list, "longpressed", on_user_list_longpress, ad);
	evas_object_smart_callback_add(users_list, "selected", on_user_list_item_selected, ad);
	/************** selected buddies **************/

	evas_object_show(users_list);
	elm_object_part_content_set(layout, "phone_num_layout", users_list);
	evas_object_data_set(users_list, "app_data", ad);
	evas_object_data_set(users_list, "selected_buddies", (void*)selected_buddies);

	evas_object_data_set(ad->nf, "group_chat_user_list", users_list);

	/******************* Phone Num layout ************************/

	Evas_Object *settings_info_lbl_bg = elm_object_part_content_get(layout, "settings_info,bg");
	if (settings_info_lbl_bg) {
		evas_object_hide(settings_info_lbl_bg);
	}


	Evas_Object* msg_btn = elm_button_add(ad->layout);
	evas_object_size_hint_weight_set(msg_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(msg_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(msg_btn);


	Evas_Object *msg_image = elm_image_add(ad->layout);
	elm_image_file_set(msg_image, ui_utils_get_resource(CAMERA_ICON), NULL);
	evas_object_size_hint_weight_set(msg_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(msg_image, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(msg_image);
	elm_object_content_set(msg_btn, msg_image);

	elm_object_part_content_set(layout, "cam_layout", msg_btn);
	evas_object_smart_callback_add(msg_btn, "clicked", on_chat_camera_button_clicked, msg_btn);
	evas_object_data_set(msg_btn, "app_data", ad);

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "Chat Info", NULL, NULL, scroller, NULL);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_MORE, on_chat_info_menu_button_clicked, ad);

}




