/*
    This file is part of Telegram application for tizen

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "tg_start_messaging_view.h"
#include "tg_db_wrapper.h"
#include "tg_messaging_view.h"

static Evas_Object* create_image_object_from_file(const char *icon_name, Evas_Object *parent)
{
	Evas_Object *icon = elm_image_add(parent);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_image_file_set(icon, icon_name, NULL);
	evas_object_show(icon);
	return icon;
}

static void on_new_msg_menu_item_selected(void *data, Evas_Object *obj, void *event_info)
{
	// int index = (int)data;
}

static char* on_new_msg_menu_item_name_get_cb(void *data, Evas_Object *obj, const char *part)
{
	if (strcmp(part, "elm.text")) {
		return NULL;
	}
	int id = (int) data;

	char temp_text[256];
	sprintf(temp_text, "<font=Tizen:style=Normal color=#000000 align=left><font_size=30>%s</font_size></font>", main_view_menu_items[id][0]);
	return strdup(temp_text);
}

static Evas_Object* on_new_msg_menu_item_image_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int)data;
	if (strcmp(part, "elm.swallow.icon")) {
		return NULL;
	}
	Evas_Object *img = elm_image_add(obj);
	elm_image_file_set(img, ui_utils_get_resource(main_view_menu_items[id][1]), NULL);
	evas_object_size_hint_min_set(img, ELM_SCALE_SIZE(36), ELM_SCALE_SIZE(36));
	return img;
}

static void on_buddy_item_clicked(void *data, Evas_Object *obj, void *event_info)
{
	int peer_id = -1;
	Eina_List *l = NULL;
	peer_with_pic_s* pic_item = NULL;
	int pos = 0;
	int item_id = (int) data;
	tg_main_list_item_s *item = NULL;

	appdata_s* ad = evas_object_data_get(obj, "app_data");
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	user_data_with_pic_s* sel_item = eina_list_nth(ad->buddy_list, item_id);
	ad->buddy_in_cahtting_data = sel_item;

	EINA_LIST_FOREACH(ad->peer_list, l, pic_item) {
		tg_peer_info_s* item = pic_item->use_data;
		if (item->peer_id == sel_item->use_data->user_id.id) {
			ad->peer_in_cahtting_data = pic_item;
			peer_id = pos;
			break;
		}
		pos++;
	}

	if (peer_id == -1) {
		ad->peer_in_cahtting_data = NULL;
		ad->buddy_in_cahtting_data = NULL;
		show_toast(ad, "Unable to retrieve buddy details");
		return;
	}

	ad->main_item_in_cahtting_data = NULL;
	l = NULL;
	EINA_LIST_FOREACH(ad->main_list, l, item) {
		if (item->peer_id == sel_item->use_data->user_id.id) {
			ad->main_item_in_cahtting_data = item;
			break;
		}
	}
	elm_naviframe_item_pop(ad->nf);
	launch_messaging_view_cb(ad, peer_id);
}

char* on_buddy_list_name_requested(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	int size = eina_list_count(ad->buddy_list);

	if (size <= 0) {
		if (!strcmp(part, "elm.text")) {
			char buf[512] = {'\0'};
			snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", "No Items");
			return strdup(buf);

		} else if (!strcmp(part, "elm.text.sub")) {
			return NULL;
		}
	}
	user_data_with_pic_s* item = eina_list_nth(ad->buddy_list, id);
	user_data_s* user = item->use_data;
	if (!strcmp(part, "elm.text")) {
		char* user_name = replace(user->print_name, '_', " ");
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", user_name);
		free(user_name);
		return strdup(buf);

	} else if (!strcmp(part, "elm.text.sub")) {
		char* last_seen = get_budy_state(ad, user->user_id.id);
		if (last_seen)
			return last_seen;
	}
	return NULL;
}

void on_chat_icon_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	user_data_with_pic_s *item  = data;
	item->contact_icon = NULL;
}

Evas_Object* on_buddy_list_image_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (strcmp(part, "elm.swallow.icon")) {
		return eo;
	}

	int id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	int size = eina_list_count(ad->buddy_list);
	if (size <= 0)
		return eo;

	user_data_with_pic_s* item = eina_list_nth(ad->buddy_list, id);
	user_data_s* user = item->use_data;
	Evas_Object *profile_pic = NULL;

	if (user->photo_path && strcmp(user->photo_path, "") != 0) {
		profile_pic = create_image_object_from_file(user->photo_path, obj);
	} else {
		profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_PROFILE_PIC), obj);
	}

	item->contact_icon = profile_pic;

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

	return eo;
}


static void on_user_list_search_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	show_toast(ad, "search clicked");
}

static void on_menu_list_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
}

static void on_search_icon_pressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(TG_SEARCH_PRESSED_ICON), NULL);
}

static void on_search_icon_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(TG_SEARCH_ICON), NULL);
}

void launch_start_messaging_view(appdata_s* ad)
{
	if (!ad)
		return;

	ad->current_app_state = TG_START_MESSAGING_VIEW_STATE;
	ad->buddy_in_cahtting_data = NULL;
	ad->peer_in_cahtting_data = NULL;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "start_messaging_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);

	/******************* menu items ****************************/
	Evas_Object* menu_gen_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(menu_gen_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(menu_gen_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(menu_gen_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(menu_gen_list, EVAS_HINT_FILL, EVAS_HINT_FILL);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "type1";
	itc.func.text_get = on_new_msg_menu_item_name_get_cb;
	itc.func.content_get = on_new_msg_menu_item_image_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (int i = 0; i < 2; i++) {
		elm_genlist_item_append(menu_gen_list, &itc, (void *)i, NULL, ELM_GENLIST_ITEM_NONE, on_new_msg_menu_item_selected, (void*)i);
	}
	evas_object_show(menu_gen_list);
	elm_object_part_content_set(layout, "menu_layout", menu_gen_list);
	evas_object_smart_callback_add(menu_gen_list, "selected", on_menu_list_clicked_cb, ad);
	/******************* menu items ****************************/

	/***************** contacts header *************************/
	Evas_Object* contact_lbl = elm_label_add(ad->nf);
	evas_object_show(contact_lbl);
	evas_object_size_hint_weight_set(contact_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(contact_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(contact_lbl, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=45>&nbsp;&nbsp;Contacts</font_size></font>");
	elm_object_part_content_set(layout, "contacts_header", contact_lbl);
	/***************** contacts header *************************/
	/***************** contacts list *************************/
	int i;
	static Elm_Genlist_Item_Class itc1;
	Evas_Object *buddy_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(buddy_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(buddy_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(buddy_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(buddy_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_data_set(buddy_list, "app_data", ad);

	itc1.item_style = "double_label";
	itc1.func.text_get = on_buddy_list_name_requested;
	itc1.func.content_get = on_buddy_list_image_requested;
	itc1.func.state_get = NULL;
	itc1.func.del = NULL;

	int size = 0;
	if (ad->buddy_list)
		size = eina_list_count(ad->buddy_list);

	if (size > 0) {
		for (i = 0; i < size; i++) {
			elm_genlist_item_append(buddy_list, &itc1, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_buddy_item_clicked, (void*) i);
		}
	} else {
		i = 1;
		elm_genlist_item_append(buddy_list, &itc1, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
	}

	evas_object_show(buddy_list);
	elm_object_part_content_set(layout, "contacts_layout", buddy_list);
	/***************** contacts list *************************/

	Evas_Object* search_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(search_layout, edj_path, "title_search_layout");
	evas_object_size_hint_weight_set(search_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(search_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(search_layout);

	Evas_Object *search_btn = elm_button_add(layout);
	elm_object_style_set(search_btn, "transparent");
	evas_object_size_hint_align_set(search_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(search_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	Evas_Object *search_icon = elm_image_add(layout);
	elm_image_file_set(search_icon, ui_utils_get_resource(TG_SEARCH_ICON), NULL);
	evas_object_show(search_icon);

	elm_object_content_set(search_btn, search_icon);

	elm_object_part_content_set(search_layout, "search_box", search_btn);
	evas_object_smart_callback_add(search_icon, "clicked", on_user_list_search_clicked, ad);
	evas_object_smart_callback_add(search_btn, "pressed", on_search_icon_pressed, search_icon);
	evas_object_smart_callback_add(search_btn, "unpressed", on_search_icon_unpressed, search_icon);

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "<font=Tizen:style=Regular color=#ffffff align=left><font_size=40>New Message</font_size></font>", NULL, NULL, scroller, NULL);
	elm_object_item_part_content_set(navi_item, "title_right_btn", search_layout);

}


