/*
 * tg_buddy_list.c
 *
 *  Created on: May 21, 2015
 *      Author: sandeep
 */
#include "tg_buddy_list.h"
#include "tg_chat_conv_view.h"
#include "contact_selection_view.h"


Evas_Object *on_list_main_icon_get(const char *icon_name, Evas_Object *parent)
{
    Evas_Object *icon = elm_image_add(parent);
    elm_object_focus_set(icon, EINA_FALSE);
    elm_image_file_set(icon, icon_name, NULL);
    evas_object_show(icon);
    return icon;
}

char* on_list_text_get_cb(void *data, Evas_Object *obj, const char *part)
{

	int id = (int) data;

	appdata_s* ad = evas_object_data_get(obj, "app_data");

	int size = eina_list_count(ad->peer_list);

	if (size <= 0) {
		if (!strcmp(part,"elm.text")){
			char buf[512] = {'\0'};
			snprintf(buf, 512, "<align=left><font_size=30><color=#000000>%s</color></font_size></align>", "No Items");
			return strdup(buf);

		} else if (!strcmp(part, "elm.text.sub")) {
			return NULL;
		}
	}

	peer_with_pic_s* item = eina_list_nth(ad->peer_list, id);
	tg_peer_info_s* user = item->use_data;

	if (!strcmp(part,"elm.text")){
		//return strdup(user->print_name);
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=30><color=#000000>%s</color></font_size></align>", user->print_name);
		return strdup(buf);

	} else if (!strcmp(part, "elm.text.sub")) {
		time_t t = user->last_seen_time;
		const char *format = "last seen %b %d %Y at %H:%M";
		struct tm lt;
		char res[32];
		(void) localtime_r(&t, &lt);

        if (strftime(res, sizeof(res), format, &lt) == 0) {
                (void) fprintf(stderr,  "strftime(3): cannot format supplied "
                                        "date/time into buffer of size %u "
                                        "using: '%s'\n",
                                        sizeof(res), format);
                exit(0);
        }

        char buf[512] = {'\0'};
        snprintf(buf, 512, "<align=center><font_size=25><color=#000000>%s</color></font_size></align>", res);

        return strdup(buf);
	}

	return NULL;
}
/***************** side panel *******************************/

void list_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Elm_Object_Item *it = (Elm_Object_Item *) elm_list_selected_item_get(obj);
	if(it == NULL) return;
	elm_object_item_part_text_set(elm_naviframe_top_item_get(ad->nf), NULL, elm_object_item_part_text_get(it, "default"));
	elm_list_item_selected_set(it, EINA_FALSE);
}

void list_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *panel = data;
	elm_panel_hidden_set(panel, EINA_TRUE);
}


void on_new_group_chat_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	evas_object_hide(ad->panel);
	elm_panel_hidden_set(ad->panel, EINA_TRUE);
	launch_contact_selction_view(ad);
}

Evas_Object* create_panel_list(appdata_s* ad, Evas_Object *parent)
{
	Evas_Object *list;
	list = elm_list_add(parent);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);

	char* full_name = (char*)malloc(strlen(ad->current_user_data.first_name) + strlen(" ") + strlen(ad->current_user_data.last_name) + 1);
	strcpy(full_name, ad->current_user_data.first_name);
	strcat(full_name, " ");
	strcat(full_name, ad->current_user_data.last_name);
	elm_list_item_append(list, full_name, NULL, NULL, NULL, NULL);
	free(full_name);

	char* phone_no = (char*)malloc(strlen(ad->current_user_data.phone) + strlen("+") + 1);
	strcpy(phone_no, "+");
	strcat(phone_no, ad->current_user_data.phone);
	elm_list_item_append(list, phone_no, NULL, NULL, NULL, NULL);
	free(phone_no);

	elm_list_item_append(list, "New Group", NULL, NULL, on_new_group_chat_clicked, ad);
	elm_list_item_append(list, "New secret Chat", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "New Broadcast list", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Contacts", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "Invite Friends", NULL, NULL, NULL, NULL);
	elm_list_item_append(list, "settings", NULL, NULL, NULL, NULL);
	evas_object_show(list);
	return list;
}


void panel_scroll_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Panel_Scroll_Info *ev = event_info;
	Evas_Object *bg = data;
	int col = 127 * ev->rel_x;
	evas_object_color_set(bg, 0, 0, 0, col);
}

Evas_Object* create_panel(Evas_Object *parent)
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

	evas_object_smart_callback_add(panel, "scroll", panel_scroll_cb, bg);
	evas_object_show(panel);

	return panel;
}

void create_main_view(appdata_s *ad)
{
	if (ad->panel) {
		Evas_Object *panel_list = evas_object_data_get(ad->panel, "panel_list");
		if (panel_list) {
			evas_object_del(panel_list);
		}
		evas_object_del(ad->panel);
		ad->panel = NULL;
	}

	ad->panel = create_panel(ad->layout);
	elm_object_part_content_set(ad->layout, "elm.swallow.left", ad->panel);
	Evas_Object *panel_list = create_panel_list(ad, ad->panel);
	evas_object_size_hint_weight_set(panel_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(panel_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(panel_list, "selected", list_clicked_cb, ad);
	eext_object_event_callback_add(panel_list, EEXT_CALLBACK_BACK, list_back_cb, ad->panel);
	elm_object_content_set(ad->panel, panel_list);
	evas_object_data_set(ad->panel, "panel_list", panel_list);
	return;
}
/***************** side panel *******************************/

void icon_del_cb(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	peer_with_pic_s *item  = data;
	item->contact_icon = NULL;
}

Evas_Object* on_list_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *image = NULL;
		int id = (int) data;
		appdata_s* ad = evas_object_data_get(obj, "app_data");

		int size = eina_list_count(ad->peer_list);

		if (size <= 0) {
			return eo;
		}


		peer_with_pic_s* item = eina_list_nth(ad->peer_list, id);
		tg_peer_info_s* user = item->use_data;

		if (user->photo_path && strcmp(user->photo_path, "") != 0) {
			image = on_list_main_icon_get(user->photo_path, obj);
		} else {
			image = on_list_main_icon_get(ui_utils_get_resource(FM_ICON_ROBO_BUDDY), obj);
		}

		item->contact_icon = image;
		evas_object_event_callback_add(item->contact_icon, EVAS_CALLBACK_DEL, icon_del_cb, item);

		if(image) {
			eo = elm_layout_add(obj);
			elm_layout_theme_set(eo, "layout", "list/C/type.3", "default");
			elm_layout_content_set(eo, "elm.swallow.content", image);
		}
	}
	return eo;
}

static void on_buddy_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	int item_id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");

	peer_with_pic_s* sel_item = eina_list_nth(ad->peer_list, item_id);

	ad->buddy_in_cahtting_data = sel_item->use_data;
	launch_chat_conv_view_cb(ad, item_id);
}

void on_search_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	refresh_buddy_list(ad);
}

Evas_Object* create_button(Evas_Object *parent, char *style, char *text)
{
	Evas_Object *button;

	button = elm_button_add(parent);
	if (style)
		elm_object_style_set(button, style);
	if (text)
		elm_object_text_set(button, text);
	evas_object_show(button);

	return button;
}

void left_panel_button_clicked_cb(void *data, Evas_Object * obj, void *event_info)
{
	appdata_s *ad = data;
	if (!elm_object_disabled_get(ad->panel)) elm_panel_toggle(ad->panel);
}

void buddylist_naviframe_more_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!elm_object_disabled_get(ad->panel)) elm_panel_toggle(ad->panel);
}

void refresh_buddy_list(void *data)
{
	appdata_s* ad = data;
	Evas_Object *buddy_list = evas_object_data_get(ad->nf, "buddy_list");
	if (buddy_list) {

		elm_genlist_clear(buddy_list);

		load_buddy_list_data(ad);
		load_group_chat_data(ad);
		load_peer_data(ad);

		int i = 0;
		static Elm_Genlist_Item_Class itc;
		itc.item_style = "double_label";
		itc.func.text_get = on_list_text_get_cb;
		itc.func.content_get = on_list_content_get_cb;
		itc.func.state_get = NULL;
		itc.func.del = NULL;

		int size = eina_list_count(ad->peer_list);
		if(size > 0) {
			for (i = 0; i < size; i++) {
				elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_buddy_clicked, (void*) i);
			}
		} else {
			i = 1;
			elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_buddy_clicked, (void*) i);
		}
		evas_object_show(buddy_list);

	}
}

void launch_buddy_list_cb(void *data)
{
	appdata_s* ad = data;

	Evas_Object *nf = ad->nf;
	Elm_Object_Item* detail_nav_item = NULL;

	ad->current_app_state = TG_BUDDY_LIST_STATE;
	elm_layout_theme_set(ad->layout, "layout", "drawer", "panel");
	create_main_view(ad);

	int i;
	static Elm_Genlist_Item_Class itc;
	Evas_Object *buddy_list = NULL;

	buddy_list = elm_genlist_add(nf);
	elm_list_mode_set(buddy_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(buddy_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(buddy_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(buddy_list, EVAS_HINT_FILL, EVAS_HINT_FILL);


	evas_object_data_set(buddy_list, "app_data", ad);

	itc.item_style = "double_label";
	itc.func.text_get = on_list_text_get_cb;
	itc.func.content_get = on_list_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	int size = eina_list_count(ad->peer_list);

	if(size > 0) {
		for (i = 0; i < size; i++) {
			elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_buddy_clicked, (void*) i);
		}
	} else {
		i = 1;
		elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_buddy_clicked, (void*) i);
	}

	evas_object_show(buddy_list);
	//elm_box_pack_end(nf, buddy_list);

    Evas_Object *left_button = elm_button_add(ad->layout);
    elm_object_style_set(left_button, "naviframe/title_icon");
    Evas_Object *licon = elm_image_add(ad->layout);
    elm_image_file_set(licon, ui_utils_get_resource(SEARCH_ICON), NULL);

    elm_image_resizable_set(licon, EINA_TRUE, EINA_TRUE);

    evas_object_smart_callback_add(left_button, "clicked", on_search_clicked, ad);
    elm_object_content_set(left_button, licon);
    evas_object_show(left_button);

    detail_nav_item = elm_naviframe_item_push(nf, "Buddy List", NULL, NULL, buddy_list, NULL);
    elm_object_item_part_content_set(detail_nav_item, "title_right_btn", left_button);

	/* left panel toggle button */
    Evas_Object *btn1 = create_button(ad->nf, "naviframe/drawers", NULL);
	evas_object_smart_callback_add(btn1, "clicked", left_panel_button_clicked_cb, ad);
	elm_object_item_part_content_set(detail_nav_item, "title_left_btn", btn1);

	evas_object_data_set(nf, "buddy_list", buddy_list);

    eext_object_event_callback_add(nf, EEXT_CALLBACK_MORE, buddylist_naviframe_more_cb, ad);

}
