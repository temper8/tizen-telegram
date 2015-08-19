/*
 * contact_selection_view.c
 *
 *  Created on: Jul 9, 2015
 *      Author: sandeep
 */

#include "contact_selection_view.h"
#include "group_chat_entry_view.h"

void on_buddy_selected(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	Evas_Object *layout = elm_object_item_part_content_get(event_info, "elm.swallow.end");
    Evas_Object *checkbox = elm_object_part_content_get(layout, "elm.swallow.content");
    Eina_Bool checked = elm_check_state_get(checkbox);
    checked = !checked;
    elm_check_state_set(checkbox, checked);

    int id = (int)data;
    appdata_s* ad = evas_object_data_get(obj, "app_data");

    if (ad && ad->buddy_list && eina_list_count(ad->buddy_list) > 0) {
    	if(id == 0) {
    		for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
    			user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
    			user_data_s* user = item->use_data;
    			user->is_selected = checked;


				Elm_Object_Item* list_item = elm_genlist_nth_item_get(obj, i+1);
				if (list_item) {
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, checked);
				}
    		}
    	} else {
			user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, id - 1);
			user_data_s* user = item->use_data;
			user->is_selected = checked;

			if (!checked) {
				Elm_Object_Item* list_item = elm_genlist_nth_item_get(obj, 0);
				if (list_item) {
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, EINA_FALSE);
				}
			} else {
				Eina_Bool all_items_selected = EINA_TRUE;
				for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
					user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
					user_data_s* user = item->use_data;
					if (!user->is_selected) {
						all_items_selected = EINA_FALSE;
						break;
					}
				}
				Elm_Object_Item* list_item = elm_genlist_nth_item_get(obj, 0);
				if (list_item) {
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, all_items_selected);
				}
			}
    	}
    }
}

char* on_buddy_name_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int)data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");

	if (id == 0 && ad->buddy_list && eina_list_count(ad->buddy_list) > 0) {
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", "Select all");
		return strdup(buf);
	}

	user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, id - 1);
	user_data_s* user = item->use_data;
	if (!strcmp(part,"elm.text")){
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=30><color=#000000>%s</color></font_size></align>", user->print_name);
		return strdup(buf);
	}
	return NULL;
}

void on_item_checkbox_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
	int id = (int)data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	Eina_Bool checked = elm_check_state_get(obj);
	Evas_Object* buddy_gen_list = evas_object_data_get(obj, "buddy_gen_list");
    if (ad && ad->buddy_list && eina_list_count(ad->buddy_list) > 0) {
    	if(id == 0) {
    		for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
    			user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
    			user_data_s* user = item->use_data;
    			user->is_selected = checked;

				Elm_Object_Item* list_item = elm_genlist_nth_item_get(buddy_gen_list, i + 1);
				if (list_item) {
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, checked);
				}
    		}
    	} else {
			user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, id - 1);
			user_data_s* user = item->use_data;
			user->is_selected = checked;

			if (!checked) {
				Elm_Object_Item* list_item = elm_genlist_nth_item_get(buddy_gen_list, 0);
				if (list_item) {
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, EINA_FALSE);
				}
			} else {
				Eina_Bool all_items_selected = EINA_TRUE;
				for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
					user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
					user_data_s* user = item->use_data;
					if (!user->is_selected) {
						all_items_selected = EINA_FALSE;
						break;
					}
				}
				Elm_Object_Item* list_item = elm_genlist_nth_item_get(buddy_gen_list, 0);
				if (list_item) {
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, all_items_selected);
				}
			}
    	}
    }
}

Evas_Object* on_buddy_selection_part_content_get_cb(void *data, Evas_Object *obj, const char *part)
{

	Evas_Object *eo = NULL;

	if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *image = NULL;
		int id = (int) data;
		appdata_s* ad = evas_object_data_get(obj, "app_data");

		if (id == 0 && ad->buddy_list && eina_list_count(ad->buddy_list) > 0) {
			return eo;
		}

		user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, id - 1);
		user_data_s* user = item->use_data;

		if (user->photo_path && strcmp(user->photo_path, "") != 0) {
			image = create_image_object_from_file(user->photo_path, obj);
		} else {
			image = create_image_object_from_file(ui_utils_get_resource(FM_ICON_ROBO_BUDDY), obj);
		}

		item->contact_icon = image;
		evas_object_event_callback_add(item->contact_icon, EVAS_CALLBACK_DEL, buddy_icon_del_cb, item);

		if(image) {
			eo = elm_layout_add(obj);
			elm_layout_theme_set(eo, "layout", "list/C/type.3", "default");
			elm_layout_content_set(eo, "elm.swallow.content", image);
		}
	} else if (!strcmp(part, "elm.swallow.end")) {
		int id = (int) data;
		appdata_s* ad = evas_object_data_get(obj, "app_data");
		if (id == 0 && ad->buddy_list && eina_list_count(ad->buddy_list) > 0) {

			Eina_Bool all_items_selected = evas_object_data_get(obj, "all_selected");

			eo = elm_layout_add(obj);
			elm_layout_theme_set(eo, "layout", "list/C/type.2", "default");
			Evas_Object *check = elm_check_add(obj);
			elm_check_state_set(check, all_items_selected);
			elm_object_focus_set(check, EINA_FALSE);
			evas_object_propagate_events_set(check, EINA_FALSE);
			evas_object_data_set(check, "app_data", ad);
			evas_object_data_set(check, "buddy_gen_list", obj);
			evas_object_smart_callback_add(check, "changed", on_item_checkbox_sel_cb, data);
			elm_layout_content_set(eo, "elm.swallow.content", check);
			return eo;
		}

		user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, id - 1);
		user_data_s* user = item->use_data;

		eo = elm_layout_add(obj);
		elm_layout_theme_set(eo, "layout", "list/C/type.2", "default");
		Evas_Object *check = elm_check_add(obj);
		elm_check_state_set(check, user->is_selected);
		elm_check_state_pointer_set(check, &user->is_selected);
		elm_object_focus_set(check, EINA_FALSE);
		evas_object_propagate_events_set(check, EINA_FALSE);
		evas_object_data_set(check, "app_data", ad);
		evas_object_data_set(check, "buddy_gen_list", obj);
		evas_object_smart_callback_add(check, "changed", on_item_checkbox_sel_cb, data);
		elm_layout_content_set(eo, "elm.swallow.content", check);
		return eo;
	} else {

	}

	return eo;
}

void on_done_buton_clicked(void *data, Evas_Object *object, void *event_info)
{
	int selected_item_count = 0;
	appdata_s* ad = data;
	if (ad && ad->buddy_list) {
		for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
			user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
			user_data_s* user = item->use_data;
			if (user->is_selected) {
				selected_item_count++;
			}
		}
	}

	if (selected_item_count > 1) {
		appdata_s* ad = data;
		elm_naviframe_item_pop(ad->nf);
		// Load chat name entry view
		launch_group_chat_name_entry_view(ad);
	} else {
		show_toast(ad, "Select atleast 2 buddies.");
	}
}

void on_cancel_buton_clicked(void *data, Evas_Object *object, void *event_info)
{
	appdata_s* ad = data;
	if (ad && ad->buddy_list) {
		for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
			user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
			user_data_s* user = item->use_data;
			user->is_selected = EINA_FALSE;
		}
	}
	elm_naviframe_item_pop(ad->nf);
	ad->current_app_state = TG_BUDDY_LIST_STATE;
	evas_object_show(ad->panel);
}

void launch_contact_selction_view(void *data)
{
	appdata_s* ad = data;
	ad->current_app_state = TG_BUDDY_LIST_SELECTION_STATE;
	elm_layout_theme_set(ad->layout, "layout", "application", "default");
	static Elm_Genlist_Item_Class itc;

	Evas_Object* buddy_gen_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(buddy_gen_list, ELM_LIST_COMPRESS);
	elm_genlist_decorate_mode_set(buddy_gen_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(buddy_gen_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(buddy_gen_list, EVAS_HINT_FILL, EVAS_HINT_FILL);

	evas_object_data_set(buddy_gen_list, "app_data", ad);
	Eina_Bool all_items_selected = EINA_FALSE;
	evas_object_data_set(buddy_gen_list, "all_selected", (void*)all_items_selected);

	itc.item_style = "default_style";
	itc.func.text_get = on_buddy_name_get_cb;
	itc.func.content_get = on_buddy_selection_part_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	int size = 0;
	if (ad->buddy_list) {
		size = eina_list_count(ad->buddy_list);
		size++;
	} else {
		size = 1; // no items
	}

	for (int i = 0; i < size; i++) {
		elm_genlist_item_append(buddy_gen_list, &itc, (void*)i, NULL, ELM_GENLIST_ITEM_NONE, on_buddy_selected, (void*)i);
	}

	evas_object_show(buddy_gen_list);

	Evas_Object* done_btn = elm_button_add(ad->layout);
	elm_object_style_set(done_btn, "naviframe/title_icon");
	Evas_Object* done_icon = elm_image_add(ad->layout);
	elm_image_file_set(done_icon, ui_utils_get_resource(FM_OK_BUTTON), NULL);
	evas_object_smart_callback_add(done_btn, "clicked", on_done_buton_clicked, ad);
	elm_object_content_set(done_btn, done_icon);
	evas_object_show(done_btn);

	Evas_Object* cancel_btn = elm_button_add(ad->layout);
	elm_object_style_set(cancel_btn, "naviframe/title_icon");
	Evas_Object* cancel_icon = elm_image_add(ad->layout);
	elm_image_file_set(cancel_icon, ui_utils_get_resource(FM_CANCEL_BUTTON), NULL);
	evas_object_smart_callback_add(cancel_btn, "clicked", on_cancel_buton_clicked, ad);
	elm_object_content_set(cancel_btn, cancel_icon);
	evas_object_show(cancel_btn);

	Elm_Object_Item* buddy_sel_nav_item = NULL;
	buddy_sel_nav_item = elm_naviframe_item_push(ad->nf, "Select friends", NULL, NULL, buddy_gen_list, NULL);
	elm_object_item_part_content_set(buddy_sel_nav_item, "title_right_btn", done_btn);
	elm_object_item_part_content_set(buddy_sel_nav_item, "title_left_btn", cancel_btn);

}


