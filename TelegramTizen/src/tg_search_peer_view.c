/*
 * tg_search_peer_view.c
 *
 *  Created on: Sep 18, 2015
 *      Author: sandeep
 */

#include "tg_search_peer_view.h"
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

char* on_peer_list_name_requested(void *data, Evas_Object *obj, const char *part)
{

	int id = (int) data;

	appdata_s* ad = evas_object_data_get(obj, "app_data");

	int size = eina_list_count(ad->search_peer_list);

	if (size <= 0) {
		if (!strcmp(part,"elm.text")){
			char buf[512] = {'\0'};
			snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", "No Items");
			return strdup(buf);

		} else if (!strcmp(part, "elm.text.sub")) {
			return NULL;
		}
	}

	peer_with_pic_s* item = eina_list_nth(ad->search_peer_list, id);
	tg_peer_info_s* user = item->use_data;

	if (!strcmp(part,"elm.text")){
		char* user_name = replace(user->print_name, '_', " ");
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", user_name);
		free(user_name);
		return strdup(buf);

	} else if (!strcmp(part, "elm.text.sub")) {
		if (user->peer_type == TGL_PEER_USER) {
			char* last_seen = get_budy_state(ad, user->peer_id);
			if (last_seen) {
				return last_seen;
			}
		}
	}

	return NULL;
}

void on_peer_icon_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	peer_with_pic_s *item  = data;
	item->contact_icon = NULL;
}

Evas_Object* on_peer_list_image_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.swallow.icon")) {

		int id = (int) data;
		appdata_s* ad = evas_object_data_get(obj, "app_data");
		int size = eina_list_count(ad->search_peer_list);
		if (size <= 0) {
			return eo;
		}
		peer_with_pic_s* item = eina_list_nth(ad->search_peer_list, id);
		tg_peer_info_s* user = item->use_data;
		Evas_Object *profile_pic = NULL;
		if (user->photo_path && strcmp(user->photo_path, "") != 0) {
			profile_pic = create_image_object_from_file(user->photo_path, obj);
		} else {
			profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_PROFILE_PIC), obj);
		}

		item->contact_icon = profile_pic;
		evas_object_event_callback_add(item->contact_icon, EVAS_CALLBACK_DEL, on_peer_icon_deleted, item);

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
	}
	return eo;
}

static void clear_search_list(appdata_s *ad)
{
	if (ad->search_peer_list) {
		for (int i = 0; i < eina_list_count(ad->search_peer_list) ; i++) {
			peer_with_pic_s* pic_item = eina_list_nth(ad->search_peer_list, i);
			tg_peer_info_s* item = pic_item->use_data;
			if (item) {
				if (item->print_name) {
					free(item->print_name);
					item->print_name = NULL;
				}
				if (item->photo_path) {
					free(item->photo_path);
					item->photo_path = NULL;
				}
				pic_item->contact_icon = NULL;
				pic_item->msg_object = NULL;
				pic_item->name_object = NULL;
				free(item);
			}
			free(pic_item);
		}
		eina_list_free(ad->search_peer_list);
	}
	ad->search_peer_list = NULL;
}

static void on_peer_item_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	int item_id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");

	peer_with_pic_s* sel_pic_item = eina_list_nth(ad->search_peer_list, item_id);
	tg_peer_info_s* sel_item = sel_pic_item->use_data;


	ad->buddy_in_cahtting_data = NULL;
	ad->peer_in_cahtting_data = NULL;
	int buddy_id = -1;
	if (sel_item) {
		if (sel_item->peer_type == TGL_PEER_USER) {
			for (int i = 0; i < eina_list_count(ad->buddy_list); i++) {
				user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
				user_data_s* user_data = item->use_data;

				if (user_data->user_id.id == sel_item->peer_id) {
					ad->buddy_in_cahtting_data = item;
					break;
				}
			}
		}

		for (int i = 0; i < eina_list_count(ad->peer_list); i++) {
			peer_with_pic_s* pic_item = eina_list_nth(ad->peer_list, i);
			tg_peer_info_s* item = pic_item->use_data;

			if (item->peer_id == sel_item->peer_id) {
				ad->peer_in_cahtting_data = pic_item;
				buddy_id = i;
				break;
			}
		}

		for (int i = 0; i < eina_list_count(ad->main_list); i++) {
			tg_main_list_item_s* item = eina_list_nth(ad->main_list, i);

			if (item->peer_id == sel_item->peer_id) {
				ad->main_item_in_cahtting_data = item;
				break;
			}
		}

		elm_naviframe_item_pop(ad->nf);
		clear_search_list(ad);
		launch_messaging_view_cb(ad, buddy_id);
	}
}

static void on_search_content_changed(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	char buf[256] = {'\0',};
	snprintf(buf, sizeof(buf), "%s", elm_object_text_get(obj));
	char *org_name = trim(buf);
	if (strlen(org_name) > 0) {
		Evas_Object *search_list = evas_object_data_get(ad->nf, "search_list");
		if (search_list) {
			elm_genlist_clear(search_list);
			clear_search_list(ad);
			ad->search_peer_list = load_peer_data_by_name(org_name);
			int i = 0;
			static Elm_Genlist_Item_Class itc1;
			itc1.item_style = "double_label";
			itc1.func.text_get = on_peer_list_name_requested;
			itc1.func.content_get = on_peer_list_image_requested;
			itc1.func.state_get = NULL;
			itc1.func.del = NULL;

			int size = eina_list_count(ad->search_peer_list);

			if(size > 0) {
				for (i = 0; i < size; i++) {
					elm_genlist_item_append(search_list, &itc1, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_peer_item_clicked, (void*) i);
				}
			} else {
				i = 1;
				elm_genlist_item_append(search_list, &itc1, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
			}
			evas_object_show(search_list);
		}
	}
	else {
		Evas_Object *search_list = evas_object_data_get(ad->nf, "search_list");
		if (search_list) {
			elm_genlist_clear(search_list);
			clear_search_list(ad);
			ad->search_peer_list = load_peer_data_by_name(NULL);
			int i = 0;
			static Elm_Genlist_Item_Class itc1;
			itc1.item_style = "double_label";
			itc1.func.text_get = on_peer_list_name_requested;
			itc1.func.content_get = on_peer_list_image_requested;
			itc1.func.state_get = NULL;
			itc1.func.del = NULL;

			int size = eina_list_count(ad->search_peer_list);

			if(size > 0) {
				for (i = 0; i < size; i++) {
					elm_genlist_item_append(search_list, &itc1, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_peer_item_clicked, (void*) i);
				}
			} else {
				i = 1;
				elm_genlist_item_append(search_list, &itc1, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
			}
			evas_object_show(search_list);
		}
	}
	if (org_name) {
		free(org_name);
		org_name = NULL;
	}
}


void launch_start_peer_search_view(appdata_s* ad)
{
	if (!ad)
		return;

	ad->current_app_state = TG_PEER_SEARCH_VIEW_STATE;


	clear_search_list(ad);


	ad->search_peer_list = load_peer_data_by_name(NULL);

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "peer_search_main_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);

	Evas_Object* search_content = elm_entry_add(layout);
	elm_object_part_text_set(search_content, "elm.guide", "<font=Tizen:style=Regular color=#666362 align=left><font_size=36>Search contact</font_size></font>");
	elm_entry_cursor_end_set(search_content);
	evas_object_size_hint_weight_set(search_content, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(search_content, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(search_content,  EINA_TRUE);
	elm_entry_scrollable_set (search_content, EINA_FALSE);
	elm_entry_cnp_mode_set(search_content, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(search_content, EINA_TRUE);
	elm_entry_text_style_user_push(search_content, "DEFAULT='color=#000000'");
	evas_object_show(search_content);

	limit_filter_data.max_char_count = 255;
	elm_entry_markup_filter_append(search_content, elm_entry_filter_limit_size, &limit_filter_data);
	evas_object_smart_callback_add(search_content, "changed", on_search_content_changed, ad);
	elm_object_part_content_set(layout, "swallow.search_area", search_content);

	int i;
	static Elm_Genlist_Item_Class itc1;
	Evas_Object *peer_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(peer_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(peer_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(peer_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(peer_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_data_set(peer_list, "app_data", ad);

	itc1.item_style = "double_label";
	itc1.func.text_get = on_peer_list_name_requested;
	itc1.func.content_get = on_peer_list_image_requested;
	itc1.func.state_get = NULL;
	itc1.func.del = NULL;

	int size = eina_list_count(ad->search_peer_list);

	if(size > 0) {
		for (i = 0; i < size; i++) {
			elm_genlist_item_append(peer_list, &itc1, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_peer_item_clicked, (void*) i);
		}
	} else {
		i = 1;
		elm_genlist_item_append(peer_list, &itc1, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
	}

	evas_object_show(peer_list);
	elm_object_part_content_set(layout, "swallow.peerlist", peer_list);

	evas_object_data_set(ad->nf, "search_list", peer_list);

	//Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "<font=Tizen:style=Regular color=#ffffff align=left><font_size=40>Search contact</font_size></font>", NULL, NULL, scroller, NULL);
	elm_naviframe_item_simple_push(ad->nf, scroller);
}
