/*
 * tg_user_main_view.c
 *
 *  Created on: Aug 20, 2015
 *      Author: sandeep
 */

#include "tg_user_main_view.h"
#include "tg_start_messaging_view.h"



static void on_new_message_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	launch_start_messaging_view(ad);
}

static char* on_menu_item_name_get_cb(void *data, Evas_Object *obj, const char *part)
{
		if (!strcmp(part,"elm.text"))
		{
			int id = (int) data;

			char temp_text[256];
			sprintf(temp_text, "<font=Tizen:style=Italic color=#000000 align=left><font_size=30>%s</font_size></font>", main_view_menu_items[id][0]);

			return strdup(temp_text);
		}
		else return NULL;
}

static Evas_Object* on_menu_item_image_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int)data;
	if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *img = elm_image_add(obj);
		elm_image_file_set(img, ui_utils_get_resource(main_view_menu_items[id][1]), NULL);
		evas_object_size_hint_min_set(img, ELM_SCALE_SIZE(36), ELM_SCALE_SIZE(36));
		return img;
	}
	return NULL;
}

static void on_menu_item_selected(void *data, Evas_Object *obj, void *event_info)
{
	int index = (int)data;
}


Evas_Object* create_side_panel_list(appdata_s* ad, Evas_Object *parent)
{

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "user_main_screen_side_panel");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);


	Evas_Object* user_info_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(user_info_layout, edj_path, "menu_user_layout");
	evas_object_size_hint_weight_set(user_info_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(user_info_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(user_info_layout);
	elm_object_part_content_set(layout, "main_box", user_info_layout);


	/*********** user info ********************/

	Evas_Object* profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_PROFILE_PIC), ad->nf);


	Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(user_pic_layout, edj_path, "circle_layout");
	evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(user_pic_layout);
	elm_object_part_content_set(user_pic_layout, "content", profile_pic);

	elm_object_part_content_set(user_info_layout, "user_photo_box", user_pic_layout);


	char* full_name = (char*)malloc(strlen(ad->current_user_data.first_name) + strlen(" ") + strlen(ad->current_user_data.last_name) + 1);
	strcpy(full_name, ad->current_user_data.first_name);
	strcat(full_name, " ");
	strcat(full_name, ad->current_user_data.last_name);


	char* phone_no = (char*)malloc(strlen(ad->current_user_data.phone) + strlen("+") + 1);
	strcpy(phone_no, "+");
	strcat(phone_no, ad->current_user_data.phone);

	char temp_full_name[256];
	sprintf(temp_full_name, "<font=Tizen:style=Bold color=#000000 align=center><font_size=30>%s</font_size></font>", full_name);


	char temp_phone_no[256];
	sprintf(temp_phone_no, "<font=Tizen:style=Bold color=#000000 align=center><font_size=30>%s</font_size></font>", phone_no);


	Evas_Object* user_name = elm_label_add(ad->nf);
	elm_object_text_set(user_name, temp_full_name);
	elm_label_ellipsis_set(user_name, EINA_TRUE);
	evas_object_show(user_name);
	elm_object_part_content_set(user_info_layout, "user_name_box", user_name);

	Evas_Object* phone_no_lbl = elm_label_add(ad->nf);
	elm_object_text_set(phone_no_lbl, temp_phone_no);
	elm_label_ellipsis_set(phone_no_lbl, EINA_TRUE);
	evas_object_show(phone_no_lbl);
	elm_object_part_content_set(user_info_layout, "phone_number_box", phone_no_lbl);


	free(full_name);
	free(phone_no);


	/*********** user info ********************/


	Evas_Object* menu_gen_list = elm_genlist_add(parent);
	elm_list_mode_set(menu_gen_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(menu_gen_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(menu_gen_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(menu_gen_list, EVAS_HINT_FILL, EVAS_HINT_FILL);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "type1";
	itc.func.text_get = on_menu_item_name_get_cb;
	itc.func.content_get = on_menu_item_image_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (int i = 0; i < NUMBER_OF_MENU_ITEMS; i++) {
		elm_genlist_item_append(menu_gen_list, &itc, (void *)i, NULL, ELM_GENLIST_ITEM_NONE, on_menu_item_selected, (void*)i);
	}
	evas_object_show(menu_gen_list);
	elm_object_part_content_set(layout, "options_box", menu_gen_list);
	evas_object_smart_callback_add(menu_gen_list, "selected", on_menu_list_clicked_cb, ad);
	return scroller;

}


void on_side_panel_scroll_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Panel_Scroll_Info *ev = event_info;
	Evas_Object *bg = data;
	int col = 127 * ev->rel_x;
	evas_object_color_set(bg, 0, 0, 0, col);
}

void on_side_list_back_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *panel = data;
	elm_panel_hidden_set(panel, EINA_TRUE);
}

Evas_Object* create_side_panel(Evas_Object *parent)
{
	Evas_Object *panel, *bg;

	panel = elm_panel_add(parent);
	elm_panel_scrollable_set(panel, EINA_TRUE);
	elm_panel_hidden_set(panel, EINA_TRUE);
	elm_panel_orient_set(panel, ELM_PANEL_ORIENT_LEFT);

	bg = evas_object_rectangle_add(evas_object_evas_get(parent));
	evas_object_color_set(bg, 0, 0, 0, 0);
	elm_object_part_content_set(parent, "elm.swallow.bg", bg);
	evas_object_show(bg);

	evas_object_smart_callback_add(panel, "scroll", on_side_panel_scroll_clicked, bg);
	evas_object_show(panel);

	return panel;
}

void on_side_panel_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Elm_Object_Item *it = (Elm_Object_Item *) elm_list_selected_item_get(obj);
	if(it == NULL) return;
	elm_object_item_part_text_set(elm_naviframe_top_item_get(ad->nf), NULL, elm_object_item_part_text_get(it, "default"));
	elm_list_item_selected_set(it, EINA_FALSE);
}


void create_side_main_view(appdata_s *ad)
{
	if (ad->panel) {
		Evas_Object *panel_list = evas_object_data_get(ad->panel, "panel_list");
		if (panel_list) {
			evas_object_del(panel_list);
		}
		evas_object_del(ad->panel);
		ad->panel = NULL;
	}

	ad->panel = create_side_panel(ad->layout);
	elm_object_part_content_set(ad->layout, "elm.swallow.left", ad->panel);
	Evas_Object *panel_list = create_side_panel_list(ad, ad->panel);
	evas_object_size_hint_weight_set(panel_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(panel_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(panel_list, "selected", on_side_panel_clicked, ad);
	eext_object_event_callback_add(panel_list, EEXT_CALLBACK_BACK, on_side_list_back_clicked, ad->panel);
	elm_object_content_set(ad->panel, panel_list);
	evas_object_data_set(ad->panel, "panel_list", panel_list);
	return;
}

void on_side_panel_requested(void *data, Evas_Object * obj, void *event_info)
{
	appdata_s *ad = data;

	if (!ad)
		return;

	if (!elm_object_disabled_get(ad->panel))
		elm_panel_toggle(ad->panel);

	return;
}

static void on_buddy_item_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	int item_id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");

	tg_main_list_item_s* sel_item = eina_list_nth(ad->main_list, item_id);
	// launch chat view
}

char* on_buddy_name_requested(void *data, Evas_Object *obj, const char *part)
{
	int item_id = (int) data;

	appdata_s* ad = evas_object_data_get(obj, "app_data");

	int size = eina_list_count(ad->main_list);

	if (size <= 0) {
		if (!strcmp(part,"elm.text")){
			char buf[512] = {'\0'};
			snprintf(buf, 512, "<font=Tizen:style=Bold color=#000000 align=left><font_size=30>%s</font_size></font>", "No Items");
			return strdup(buf);

		} else if (!strcmp(part, "elm.text.sub")) {
			return NULL;
		}
	}

	tg_main_list_item_s* item = eina_list_nth(ad->main_list, item_id);


	if (!strcmp(part,"elm.text")){
		char* user_name = replace(item->peer_print_name, '_', " ");
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<font=Tizen:style=Bold color=#000000 align=left><font_size=30>%s</font_size></font>", user_name);
		free(user_name);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.sub")) {
        char* res = NULL;
        if (item->last_message) {
        	res = item->last_message;
        } else {
        	res = " ";
        }
        char buf[512] = {'\0'};
        snprintf(buf, 512, "<font=Tizen:style=Italic color=#A4A4A4 align=left><font_size=25>%s</font_size></font>", res);
        return strdup(buf);
	}
	return NULL;
}

void on_buddy_icon_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	tg_main_list_item_s *item  = data;
	item->profile_pic = NULL;
}

Evas_Object* on_buddy_photo_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	int id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	tg_main_list_item_s* item = eina_list_nth(ad->main_list, id);

	if (!strcmp(part, "elm.swallow.icon")) {
		int size = eina_list_count(ad->main_list);
		if (size <= 0) {
			return eo;
		}

		Evas_Object *profile_pic = NULL;
		if (item->profile_pic_path && strcmp(item->profile_pic_path, "") != 0) {

			profile_pic = elm_image_add(obj);
			evas_object_size_hint_weight_set(profile_pic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(profile_pic, EVAS_HINT_FILL, EVAS_HINT_FILL);
			elm_object_focus_set(profile_pic, EINA_FALSE);

			Eina_Bool is_success = elm_image_file_set(profile_pic, item->profile_pic_path, NULL);

			if (!is_success) {
				create_image_object_from_file(ui_utils_get_resource(DEFAULT_PROFILE_PIC), obj);
				// send download request again
			}

			evas_object_show(profile_pic);

		} else {
			profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_PROFILE_PIC), obj);
		}

		item->profile_pic = profile_pic;
		evas_object_event_callback_add(item->profile_pic, EVAS_CALLBACK_DEL, on_buddy_icon_deleted, item);

		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(user_pic_layout, edj_path, "circle_layout");
		evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(user_pic_layout);
		elm_object_part_content_set(user_pic_layout, "content", profile_pic);

		eo = elm_layout_add(obj);
		elm_layout_theme_set(eo, "layout", "list/C/type.3", "default");
		elm_layout_content_set(eo, "elm.swallow.content", user_pic_layout);

	} else if (!strcmp(part, "elm.swallow.end")) {

		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		Evas_Object* user_status_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(user_status_layout, edj_path, "main_list_status_item");
		evas_object_size_hint_weight_set(user_status_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(user_status_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(user_status_layout);

		Eina_Bool is_today = compare_date_with_current_date(item->last_seen_time);

		Evas_Object* time_lbl = elm_label_add(ad->nf);
		if (is_today) {
			elm_object_text_set(time_lbl, "<font=Tizen:style=Italic color=#000000 align=center><font_size=25>Today</font_size></font>");
		} else {
			char *format = NULL;
			time_t t = item->last_seen_time;
			format = "%d/%b/%Y";
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
			snprintf(time_str, sizeof(time_str), "<font=Tizen:style=Italic color=#000000 align=center><font_size=25>%s</font_size></font>", res);

			elm_object_text_set(time_lbl,time_str);
		}

		evas_object_size_hint_weight_set(time_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(time_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(time_lbl);

		elm_object_part_content_set(user_status_layout, "swallow.date", time_lbl);

		if (item->is_out_msg) {
			Evas_Object *status_obj;
			status_obj = elm_icon_add(obj);
			evas_object_size_hint_weight_set(status_obj, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(status_obj, EVAS_HINT_FILL, EVAS_HINT_FILL);

			if(item->last_msg_status == TG_MESSAGE_STATE_SENDING) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENDING_ICON), NULL);
			} else if(item->last_msg_status == TG_MESSAGE_STATE_SENT) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENT_ICON), NULL);
			} else if(item->last_msg_status == TG_MESSAGE_STATE_DELIVERED) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_DELIVERED_ICON), NULL);
			} else if(item->last_msg_status == TG_MESSAGE_STATE_RECEIVED) {

			} else if(item->last_msg_status == TG_MESSAGE_STATE_FAILED) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_FAILED_ICON), NULL);
			} else if(item->last_msg_status == TG_MESSAGE_STATE_READ) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_READ_ICON), NULL);
			} else if(item->last_msg_status == TG_MESSAGE_STATE_UNKNOWN) {

			}

			Evas_Object* msg_status = elm_layout_add(ad->nf);
			elm_layout_file_set(msg_status, edj_path, "circle_layout");
			evas_object_size_hint_weight_set(msg_status, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(msg_status, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(msg_status);
			elm_object_part_content_set(msg_status, "content", status_obj);

			elm_object_part_content_set(user_status_layout, "swallow.status", msg_status);

		} else {
			Evas_Object* num_lbl = elm_label_add(ad->nf);
			elm_object_style_set(num_lbl, "transparent");
			char unread_msgs[256];
			sprintf(unread_msgs, "<font=Tizen:style=Bold color=#ffffff align=center><font_size=25>%d</font_size></font>", item->number_of_unread_msgs);
			elm_object_text_set(num_lbl, unread_msgs);
			evas_object_size_hint_weight_set(num_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(num_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(num_lbl);

			Evas_Object* msg_status = elm_layout_add(ad->nf);
			elm_layout_file_set(msg_status, edj_path, "circle_item");
			evas_object_size_hint_weight_set(msg_status, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(msg_status, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(msg_status);
			elm_object_part_content_set(msg_status, "content", num_lbl);

			elm_object_part_content_set(user_status_layout, "swallow.status", msg_status);
		}

		eo = elm_layout_add(obj);
		elm_layout_theme_set(eo, "layout", "list/C/type.3", "default");
		elm_layout_content_set(eo, "elm.swallow.content", user_status_layout);

	}
	return eo;
}


void launch_user_main_view_cb(appdata_s* ad)
{
	if (!ad)
		return;
	ad->current_app_state = TG_USER_MAIN_VIEW_STATE;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "user_main_screen_new");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);

	elm_layout_theme_set(ad->layout, "layout", "drawer", "panel");
	create_side_main_view(ad);

	/************** no chat item++ *********************/

	Evas_Object* bg_box = elm_box_add(layout);
	evas_object_size_hint_weight_set(bg_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(bg_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(bg_box);
	elm_object_part_content_set(layout, "main_box", bg_box);

	if (ad->main_list == NULL || eina_list_count(ad->main_list) <= 0) {
		Evas_Object* no_chat_img = create_image_object_from_file(ui_utils_get_resource(TG_NO_CHAT_LIST), layout);
		elm_box_pack_end(bg_box, no_chat_img);
	} else {
		int i;
		static Elm_Genlist_Item_Class itc;
		Evas_Object *buddy_list = elm_genlist_add(ad->nf);
		elm_list_mode_set(buddy_list, ELM_LIST_COMPRESS);
		elm_genlist_mode_set(buddy_list, ELM_LIST_COMPRESS);
		evas_object_size_hint_weight_set(buddy_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(buddy_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_data_set(buddy_list, "app_data", ad);

		itc.item_style = "type1";
		itc.func.text_get = on_buddy_name_requested;
		itc.func.content_get = on_buddy_photo_requested;
		itc.func.state_get = NULL;
		itc.func.del = NULL;

		int size = eina_list_count(ad->main_list);
		if(size > 0) {
			for (i = 0; i < size; i++) {
				elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_buddy_item_clicked, (void*) i);
			}
		} else {
			i = 1;
			elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_buddy_item_clicked, (void*) i);
		}
		evas_object_show(buddy_list);
		elm_box_pack_end(bg_box, buddy_list);
	}

	/************** no chat item-- *********************/

    Evas_Object *pencil_icon = elm_image_add(layout);
    elm_image_file_set(pencil_icon, ui_utils_get_resource(TG_ICON_FLOATING_PENCIL), NULL);
    evas_object_show(pencil_icon);

	Evas_Object* new_msg_btn = elm_button_add(layout);
	evas_object_size_hint_weight_set(new_msg_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(new_msg_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_content_set(new_msg_btn, pencil_icon);
	evas_object_show(new_msg_btn);
	evas_object_smart_callback_add(new_msg_btn, "clicked", on_new_message_clicked, ad);
	elm_object_part_content_set(layout, "new_chat_icon", new_msg_btn);

	Evas_Object* search_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(search_layout, edj_path, "title_search_layout");
	evas_object_size_hint_weight_set(search_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(search_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(search_layout);
    Evas_Object *search_icon = elm_image_add(layout);
    elm_image_file_set(search_icon, ui_utils_get_resource(TG_SEARCH_ICON), NULL);
    evas_object_show(search_icon);
    elm_object_part_content_set(search_layout, "search_box", search_icon);
    evas_object_smart_callback_add(search_icon, "clicked", on_user_list_search_clicked, ad);

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "<font=Tizen:style=Regular color=#ffffff align=left><font_size=40>Telegram</font_size></font>", NULL, NULL, scroller, NULL);
	elm_object_item_part_content_set(navi_item, "title_right_btn", search_layout);

	/* left panel toggle button */
    Evas_Object *panel_btn = create_button(ad->nf, "naviframe/drawers", NULL);
	evas_object_smart_callback_add(panel_btn, "clicked", on_side_panel_requested, ad);
	elm_object_item_part_content_set(navi_item, "title_left_btn", panel_btn);
}


