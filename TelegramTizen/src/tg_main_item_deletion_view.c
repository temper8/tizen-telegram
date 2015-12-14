/*
 * tg_main_item_deletion_view.c
 *
 *  Created on: Oct 19, 2015
 *      Author: sandeep
 */

#include "tg_main_item_deletion_view.h"
#include "tg_user_main_view.h"
#include "tg_db_manager.h"
#include "server_requests.h"

static Evas_Object* create_image_object_from_file(const char *icon_name, Evas_Object *parent)
{
	Evas_Object *icon = elm_image_add(parent);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_image_file_set(icon, icon_name, NULL);
	evas_object_show(icon);
	return icon;
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


void change_main_item_selection_state(appdata_s *ad, Evas_Object *gen_list, Eina_Bool checked, int org_id)
{
	if (!ad || !gen_list) {
		return;
	}
	if (ad->main_list && eina_list_count(ad->main_list) > 0) {

		if (org_id ==0) {
			Eina_Bool all_items_selected = checked;
			evas_object_data_set(gen_list, "all_selected", (void *)((int)all_items_selected));
			for (int i = 0 ; i < eina_list_count(ad->main_list) ; i++) {
				tg_main_list_item_s *item = eina_list_nth(ad->main_list, i);
				item->is_selected = checked;
				Elm_Object_Item* list_item = elm_genlist_nth_item_get(gen_list, i + 1);
				if (list_item) {
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, checked);
				}
			}
		} else {
			tg_main_list_item_s *item = eina_list_nth(ad->main_list, org_id - 1);
			item->is_selected = checked;
			if (!checked) {
				Elm_Object_Item* list_item = elm_genlist_nth_item_get(gen_list, 0);
				if (list_item) {
					Eina_Bool all_items_selected = checked;
					evas_object_data_set(gen_list, "all_selected", (void *)((int)all_items_selected));
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, EINA_FALSE);
				}
			} else {
				Eina_Bool all_items_selected = EINA_TRUE;
				for (int i = 0 ; i < eina_list_count(ad->main_list) ; i++) {
					tg_main_list_item_s *item = eina_list_nth(ad->main_list, i);
					if (!item->is_selected) {
						all_items_selected = EINA_FALSE;
					}
				}
				if (all_items_selected) {
					Elm_Object_Item* list_item = elm_genlist_nth_item_get(gen_list, 0);
					if (list_item) {
						elm_genlist_item_selected_set(list_item, EINA_TRUE);
						Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
						Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
						elm_check_state_set(lcheckbox, EINA_TRUE);
						evas_object_data_set(gen_list, "all_selected", (void *)((int)all_items_selected));
					}
				}
			}
		}

#if 0
		if (org_id ==0) {
			for (int i = 0 ; i < eina_list_count(ad->main_list) ; i++) {
				tg_main_list_item_s *item = eina_list_nth(ad->main_list, i);
				item->is_selected = checked;
				Eina_Bool all_items_selected = checked;
				evas_object_data_set(gen_list, "all_selected", (void *)((int)all_items_selected));
				Elm_Object_Item* list_item = elm_genlist_nth_item_get(gen_list, i + 1);
				if (list_item) {
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, checked);
				}
			}
		} else {
			tg_main_list_item_s *item = eina_list_nth(ad->main_list, org_id - 1);
			item->is_selected = checked;

			if (!checked) {
				Elm_Object_Item* list_item = elm_genlist_nth_item_get(gen_list, 0);
				if (list_item) {
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, EINA_FALSE);
				}
			} else {
				Eina_Bool all_items_selected = EINA_TRUE;
				for (int i = 0 ; i < eina_list_count(ad->main_list) ; i++) {
					tg_main_list_item_s *item = eina_list_nth(ad->main_list, i);
					if (!item->is_selected) {
						all_items_selected = EINA_FALSE;
						break;
					}
				}
				Elm_Object_Item* list_item = elm_genlist_nth_item_get(gen_list, 0);
				if (list_item) {
					elm_genlist_item_selected_set(list_item, EINA_FALSE);
					Evas_Object *llayout = elm_object_item_part_content_get(list_item, "elm.swallow.end");
					Evas_Object *lcheckbox = elm_object_part_content_get(llayout, "elm.swallow.content");
					elm_check_state_set(lcheckbox, all_items_selected);
				}
			}
		}
#endif
	}

}

void on_main_item_checkbox_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
	int org_id = (int) data;
	appdata_s *ad = evas_object_data_get(obj, "app_data");
	Evas_Object *gen_list = evas_object_data_get(obj, "selection_gen_list");
	Eina_Bool checked = elm_check_state_get(obj);
	change_main_item_selection_state(ad, gen_list, checked, org_id);
}

void on_main_item_selected(void *data, Evas_Object *obj, void *event_info)
{
	int org_id = (int) data;
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	Evas_Object *layout = elm_object_item_part_content_get(event_info, "elm.swallow.end");
	Evas_Object *checkbox = elm_object_part_content_get(layout, "elm.swallow.content");
	Eina_Bool checked = elm_check_state_get(checkbox);
	appdata_s *ad = evas_object_data_get(checkbox, "app_data");
	checked = !checked;
	elm_check_state_set(checkbox, checked);
	change_main_item_selection_state(ad, obj, checked, org_id);
}

Evas_Object* on_mainlist_content_requested(void *data, Evas_Object *obj, const char *part)
{
	int org_id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	Evas_Object *eo = NULL;
	int id = org_id - 1;
	if (ad->main_list == NULL || eina_list_count(ad->main_list) <= 0) {
		return NULL;
	}

	if (!strcmp("elm.swallow.end", part)) {
		eo = elm_layout_add(obj);
		elm_layout_theme_set(eo, "layout", "list/C/type.2", "default");
		Evas_Object *check = elm_check_add(obj);
		elm_object_focus_set(check, EINA_FALSE);
		evas_object_propagate_events_set(check, EINA_FALSE);
		evas_object_data_set(check, "app_data", ad);
		evas_object_data_set(check, "selection_gen_list", obj);
		evas_object_smart_callback_add(check, "changed", on_main_item_checkbox_sel_cb, data);
		elm_layout_content_set(eo, "elm.swallow.content", check);
		if (org_id == 0) {
			Eina_Bool all_items_selected = (Eina_Bool)evas_object_data_get(obj, "all_selected");
			elm_check_state_set(check, all_items_selected);
		} else {
			tg_main_list_item_s* item = eina_list_nth(ad->main_list, id);
			elm_check_state_set(check, item->is_selected);
		}
		return eo;
	}

	if (org_id == 0) {
		return NULL;
	}

	tg_main_list_item_s* item = eina_list_nth(ad->main_list, id);
	if (!item) {
		return NULL;
	}

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


void on_delete_selected_items_clicked(void *data, Evas_Object *object, void *event_info)
{
	appdata_s *ad = data;
	if (!ad)
		return;

	Eina_List *sel_grp_chat = NULL;
	int num_of_sel_items = 0;

	for (int i = 0; i < eina_list_count(ad->main_list); i++) {
		tg_main_list_item_s* sel_item = eina_list_nth(ad->main_list, i);
		if (sel_item && sel_item->is_selected) {
			if (sel_item->peer_type == TGL_PEER_USER) {
				char* tablename = get_table_name_from_number(sel_item->peer_id);
				delete_all_records(tablename);
				free(tablename);
#if 0
				// delete from main list
				if (sel_item->peer_print_name) {
					free(sel_item->peer_print_name);
					sel_item->peer_print_name = NULL;
				}
				if (sel_item->last_message) {
					free(sel_item->last_message);
					sel_item->last_message = NULL;
				}
				if (sel_item->profile_pic_path) {
					free(sel_item->profile_pic_path);
					sel_item->profile_pic_path = NULL;
				}
				sel_item->date_lbl = NULL;
				sel_item->msg_status_lbl = NULL;
				sel_item->main_item_layout = NULL;
				sel_item->profile_pic = NULL;
				sel_item->profile_pic_path = NULL;
				sel_item->status_lbl = NULL;
				sel_item->user_name_lbl = NULL;
				//ad->main_list
				ad->main_list = eina_list_remove(ad->main_list, sel_item);
#endif
			} else if (sel_item->peer_type == TGL_PEER_CHAT) {
				sel_grp_chat = eina_list_append(sel_grp_chat, sel_item);
			}
			num_of_sel_items++;
		}
	}




	if (num_of_sel_items <= 0) {
		show_toast(ad, "Select items to delete.");
		return;
	}

	if (sel_grp_chat && eina_list_count(sel_grp_chat) > 0) {
		show_loading_popup(ad);
		send_delete_selected_group_chats_request(ad, ad->service_client, sel_grp_chat);
	} else {
#if 0
		refresh_main_list_view(ad, EINA_FALSE);
		elm_naviframe_item_pop(ad->nf);
		ad->current_app_state = TG_USER_MAIN_VIEW_STATE;
		show_floating_button(ad);
		hide_loading_popup(ad);
#else
		show_loading_popup(ad);
		load_registered_user_data(ad);
		load_buddy_list_data(ad);
		load_unknown_buddy_list_data(ad);
		load_peer_data(ad);
		load_main_list_data(ad);
		if (ad->main_item) {
			elm_naviframe_item_pop_to(ad->main_item);
		}
		ecore_timer_add(1, on_load_main_view_requested, ad);
#endif
	}
}

void on_selection_cancel_clicked(void *data, Evas_Object *object, void *event_info)
{
	appdata_s *ad = data;
	if (!ad)
		return;

	elm_naviframe_item_pop(ad->nf);
	ad->current_app_state = TG_USER_MAIN_VIEW_STATE;
	show_floating_button(ad);
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

		evas_object_data_set(buddy_list, "app_data", ad);
		Eina_Bool all_items_selected = EINA_FALSE;
		evas_object_data_set(buddy_list, "all_selected", (void *)((int)all_items_selected));

		itc.item_style = "type1";
		itc.func.text_get = on_mainlist_title_requested;
		itc.func.content_get = on_mainlist_content_requested;
		itc.func.state_get = NULL;
		itc.func.del = NULL;

		int size = eina_list_count(ad->main_list);
		if(size > 0) {
			for (i = 0; i <= size; i++) {
				if (i < size) {
					tg_main_list_item_s *item = eina_list_nth(ad->main_list, i);
					item->is_selected = EINA_FALSE;
				}
				elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_main_item_selected, (void*) i);
			}
		} else {
			i = 1;
			elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
		}
		evas_object_show(buddy_list);
		elm_box_pack_end(bg_box, buddy_list);
	}
	evas_object_data_set(ad->nf, "main_list_box", bg_box);
	Elm_Object_Item* buddy_sel_nav_item = elm_naviframe_item_push(ad->nf, i18n_get_text("IDS_TGRAM_HEADER_SELECT_CHATS_ABB"), NULL, NULL, scroller, NULL);

	Evas_Object* delete_btn = elm_button_add(ad->layout);
	elm_object_style_set(delete_btn, "naviframe/title_left");
	evas_object_smart_callback_add(delete_btn, "clicked", on_delete_selected_items_clicked, ad);
	elm_object_text_set(delete_btn, i18n_get_text("IDS_TGRAM_OPT_DELETE"));
	evas_object_show(delete_btn);

	Evas_Object* cancel_btn = elm_button_add(ad->layout);
	elm_object_style_set(cancel_btn, "naviframe/title_right");
	evas_object_smart_callback_add(cancel_btn, "clicked", on_selection_cancel_clicked, ad);
	elm_object_text_set(cancel_btn, i18n_get_text("IDS_TGRAM_BUTTON_CANCEL_ABB5"));
	evas_object_show(cancel_btn);

	elm_object_item_part_content_set(buddy_sel_nav_item, "title_right_btn", delete_btn);
	elm_object_item_part_content_set(buddy_sel_nav_item, "title_left_btn", cancel_btn);
}

