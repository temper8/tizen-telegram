/*
 * tg_main_item_deletion_view.c
 *
 *  Created on: Oct 19, 2015
 *      Author: sandeep
 */


#include "tg_main_item_deletion_view.h"

static Evas_Object* create_image_object_from_file(const char *icon_name, Evas_Object *parent)
{
	Evas_Object *icon = elm_image_add(parent);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_image_file_set(icon, icon_name, NULL);
	evas_object_show(icon);
	return icon;
}

static Evas_Object* create_check(Evas_Object *parent)
{
	Evas_Object *check;
	check = elm_check_add(parent);
	return check;
}

char* on_mainlist_title_requested(void *data, Evas_Object *obj, const char *part)
{

	int org_id = (int) data;
	if (org_id == 0) {
		if (!strcmp(part,"elm.text.main.left.top") || !strcmp(part,"elm.text")){
			return strdup(i18n_get_text("IDS_TGRAM_MBODY_SELECT_ALL"));
		}
		return NULL;
	}

	int id = org_id - 1;

	appdata_s* ad = evas_object_data_get(obj, "app_data");

	if (ad->main_list == NULL || eina_list_count(ad->main_list) <= 0) {
		return NULL;
	}
	tg_main_list_item_s* item = eina_list_nth(ad->main_list, id);
	if (!item) {
		return NULL;
	}
	if (!strcmp(part,"elm.text.main.left.top") || !strcmp(part,"elm.text")){
		char *full_name = replace(item->peer_print_name, '_', " ");
		return full_name;
	} else if (!strcmp(part, "elm.text.sub.left.bottom") || !strcmp(part,"elm.text.sub")) {
		char* org_msg = NULL;
		if (item->last_message) {
			org_msg = item->last_message;
		} else {
			org_msg = "";
		}
		return strdup(org_msg);
	} else {
		return NULL;
	}
}

Evas_Object* on_mainlist_content_requested(void *data, Evas_Object *obj, const char *part)
{
	int org_id = (int) data;

	if (!strcmp("elm.swallow.end", part)) {
		return create_check(obj);
	}

	if (org_id == 0) {
		return NULL;
	}

	int id = org_id - 1;

	appdata_s* ad = evas_object_data_get(obj, "app_data");

	if (ad->main_list == NULL || eina_list_count(ad->main_list) <= 0) {
		return NULL;
	}
	tg_main_list_item_s* item = eina_list_nth(ad->main_list, id);
	if (!item) {
		return NULL;
	}


	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.icon.left") || !strcmp(part, "elm.icon.1") || !strcmp(part, "elm.swallow.icon")) {
		//if (item->profile_pic == NULL) {
			Evas_Object *profile_pic = NULL;
			if (item->profile_pic_path && strcmp(item->profile_pic_path, "") != 0) {
				profile_pic = elm_image_add(obj);
				evas_object_size_hint_weight_set(profile_pic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(profile_pic, EVAS_HINT_FILL, EVAS_HINT_FILL);
				elm_object_focus_set(profile_pic, EINA_FALSE);

				Eina_Bool is_success = elm_image_file_set(profile_pic, item->profile_pic_path, NULL);

				if (!is_success) {
					if (item->peer_type == TGL_PEER_USER) {
						profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC), obj);
						// send download request again To-Do
					} else if (item->peer_type == TGL_PEER_CHAT) {
						profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_MULTI_PIC), obj);
						// send download request again To-Do
					} else {

					}
					evas_object_color_set(profile_pic, 45, 165, 224, 255);
				}
				evas_object_show(profile_pic);
			} else {

				if (item->peer_type == TGL_PEER_USER) {
					profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC), obj);
				} else if (item->peer_type == TGL_PEER_CHAT) {
					profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_MULTI_PIC), obj);
				} else {

				}
				evas_object_color_set(profile_pic, 45, 165, 224, 255);
			}
		//}
		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(user_pic_layout, edj_path, "search_circle_layout");
		evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(user_pic_layout);
		elm_object_part_content_set(user_pic_layout, "content", profile_pic);

		eo = elm_layout_add(obj);
		elm_layout_theme_set(eo, "layout", "list/B/type.2", "default");
		elm_layout_content_set(eo, "elm.swallow.content", user_pic_layout);
	}
	return eo;
}


void launch_main_item_deletion_view_cb(appdata_s* ad)
{
	if (!ad)
		return;

	ad->current_app_state = TG_USER_MAIN_VIEW_SELECTION_STATE;
	delete_floating_button(ad);
	ad->is_tg_initilized = EINA_TRUE;
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

	Evas_Object *buddy_list = NULL;
	Evas_Object* bg_box = elm_box_add(layout);
	evas_object_size_hint_weight_set(bg_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(bg_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(bg_box);
	elm_object_part_content_set(layout, "main_box", bg_box);

	if (ad->main_list == NULL || eina_list_count(ad->main_list) <= 0) {
		return;
	} else {
		int i;
		static Elm_Genlist_Item_Class itc;
		buddy_list = elm_genlist_add(ad->nf);
		elm_list_mode_set(buddy_list, ELM_LIST_COMPRESS);
		elm_genlist_mode_set(buddy_list, ELM_LIST_COMPRESS);
		evas_object_size_hint_weight_set(buddy_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(buddy_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_data_set(buddy_list, "app_data", ad);
		elm_genlist_homogeneous_set(buddy_list, EINA_TRUE);

		itc.item_style = "type1";
		itc.func.text_get = on_mainlist_title_requested;
		itc.func.content_get = on_mainlist_content_requested;
		itc.func.state_get = NULL;
		itc.func.del = NULL;

		int size = eina_list_count(ad->main_list);
		if(size > 0) {
			for (i = 0; i <= size; i++) {
				elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
			}
		} else {
			i = 1;
			elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
		}
		evas_object_show(buddy_list);
		elm_box_pack_end(bg_box, buddy_list);
	}
	evas_object_data_set(ad->nf, "main_list_box", bg_box);
	elm_naviframe_item_push(ad->nf, i18n_get_text("IDS_TGRAM_HEADER_SELECT_CHATS_ABB"), NULL, NULL, scroller, NULL);

}

