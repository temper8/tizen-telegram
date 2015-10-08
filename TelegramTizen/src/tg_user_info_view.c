/*
 * tg_user_info_view.c
 *
 *  Created on: Oct 2, 2015
 *      Author: sandeep
 */

#include "tg_user_info_view.h"
#include "server_requests.h"
#include "tg_user_main_view.h"

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
#if 0
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
#endif
void on_user_added_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success)
{
	if (is_success) {
		if (ad->peer_in_cahtting_data->use_data->peer_id == buddy_id) {
			if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->user_id.id == buddy_id) {
				ad->buddy_in_cahtting_data->use_data->is_deleted = 0;
				show_toast(ad, "User added successfully");
			}
		}
	} else {
		show_toast(ad, "Failed to add user.");
	}
}

void on_user_deleted_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success)
{
#if 0
	if (is_success) {
		if (ad->peer_in_cahtting_data->use_data->peer_id == buddy_id) {
			if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->user_id.id == buddy_id) {

				show_toast(ad, "User deleted successfully");

				if(ad->peer_list) {
					int size = eina_list_count(ad->peer_list);
					for (int i = 0 ; i < size ; i++) {
						peer_with_pic_s *item = eina_list_nth(ad->peer_list, i);
						if (item->use_data->peer_id == buddy_id) {
							ad->peer_list = eina_list_remove(ad->peer_list, item);
							break;
						}
					}
				}

				if(ad->main_list) {
					int size = eina_list_count(ad->main_list);
					for (int i = 0 ; i < size ; i++) {
						tg_main_list_item_s *item = eina_list_nth(ad->main_list, i);
						if (item->peer_id == buddy_id) {
							ad->main_list = eina_list_remove(ad->main_list, item);
							break;
						}
					}
				}

				if(ad->buddy_list) {
					int size = eina_list_count(ad->buddy_list);
					for (int i = 0 ; i < size ; i++) {
						user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
						user_data_s* user = item->use_data;

						if (user->user_id.id == buddy_id) {
							ad->buddy_list = eina_list_remove(ad->buddy_list, item);
							break;
						}
					}
				}

				refresh_main_list_view(ad, EINA_FALSE);
				ad->peer_in_cahtting_data = NULL;
				ad->main_item_in_cahtting_data = NULL;

				elm_naviframe_item_pop(ad->nf);
				ad->current_app_state = TG_CHAT_MESSAGING_VIEW_STATE;
				/*
				elm_naviframe_item_pop(ad->nf);
				ad->current_app_state = TG_USER_MAIN_VIEW_STATE;
				 */
				show_loading_popup(ad);
				ecore_timer_add(2, on_view_deleteion_requested, ad);
			}
		}
	} else {
		show_toast(ad, "Failed to delete user.");
	}
#else
	if (is_success) {
		if (ad->peer_in_cahtting_data->use_data->peer_id == buddy_id) {
			if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->user_id.id == buddy_id) {
				ad->buddy_in_cahtting_data->use_data->is_deleted = 1;
				show_toast(ad, "User deleted successfully");
			}
		}
	} else {
		show_toast(ad, "Failed to delete user.");
	}
#endif
}

void on_user_block_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success)
{
	if (is_success) {
		if (ad->peer_in_cahtting_data->use_data->peer_id == buddy_id) {
			if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->user_id.id == buddy_id) {
				ad->buddy_in_cahtting_data->use_data->is_blocked = 1;
				show_toast(ad, "User blocked successfully");
			}
		}
	} else {
		show_toast(ad, "Failed to block user.");
	}
}

void on_user_unblock_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success)
{
	if (is_success) {
		if (ad->peer_in_cahtting_data->use_data->peer_id == buddy_id) {
			if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->user_id.id == buddy_id) {
				ad->buddy_in_cahtting_data->use_data->is_blocked = 0;
				show_toast(ad, "User unblocked successfully");
			}
		}
	} else {
		show_toast(ad, "Failed to unblock user.");
	}
}


static void on_userinfo_menu_canceled(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = evas_object_data_get(obj, "app_data");
	Evas_Object *popup = evas_object_data_get(obj, "popup");
	evas_object_del(popup);
}

static void on_user_block_ok_selected(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = evas_object_data_get(obj, "app_data");
	Evas_Object *popup = evas_object_data_get(obj, "popup");

	if (ad->peer_in_cahtting_data && ad->peer_in_cahtting_data->use_data) {
		show_loading_popup(ad);
		if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->is_blocked == 1) {
			send_unblock_buddy_request(ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id);
		} else {
			send_block_buddy_request(ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id);
		}
	}

	evas_object_del(popup);
}

static void on_block_selected_cb(appdata_s *ad)
{
	Evas_Object *popup, *btn;

	/* popup */
	popup = elm_popup_add(ad->nf);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);


	if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->is_blocked == 1) {
		elm_object_text_set(popup,"Are you sure want to unblock this contact?");
	} else {
		elm_object_text_set(popup,"Are you sure want to block this contact?");
	}

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", on_user_block_ok_selected, ad);
	evas_object_data_set(btn, "app_data", ad);
	evas_object_data_set(btn, "popup", popup);

	/* cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", on_userinfo_menu_canceled, ad);
	evas_object_data_set(btn, "app_data", ad);
	evas_object_data_set(btn, "popup", popup);

	evas_object_show(popup);
}

/************************ delete user *****************************/

static void on_user_delete_ok_selected(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = evas_object_data_get(obj, "app_data");
	Evas_Object *popup = evas_object_data_get(obj, "popup");

	if (ad->peer_in_cahtting_data && ad->peer_in_cahtting_data->use_data) {
		show_loading_popup(ad);

		if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->is_deleted == 1) {
			send_add_buddy_request(ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id);
		} else {
			send_delete_buddy_request(ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id);
		}

	}
	evas_object_del(popup);
}



static void on_delete_selected_cb(appdata_s *ad)
{
	Evas_Object *popup, *btn;

	/* popup */
	popup = elm_popup_add(ad->nf);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);



	if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->is_deleted == 1) {
		elm_object_text_set(popup,"Are you sure want to add this contact?");
	} else {
		elm_object_text_set(popup,"Are you sure want to delete this contact?");
	}


	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", on_user_delete_ok_selected, ad);
	evas_object_data_set(btn, "app_data", ad);
	evas_object_data_set(btn, "popup", popup);

	/* cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", on_userinfo_menu_canceled, ad);
	evas_object_data_set(btn, "app_data", ad);
	evas_object_data_set(btn, "popup", popup);

	evas_object_show(popup);
}



/************************ delete user *****************************/

/************************ Menu Handler ********************/

void on_user_info_menu_option_selected_cb(void *data, Evas_Object *obj, void *event_info)
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

		if (id == 0) {
			on_block_selected_cb(ad);
		} else if (id == 1) {
			on_delete_selected_cb(ad);
		} else {

		}

	} else if (user_data->peer_type == TGL_PEER_CHAT) {


	}

	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
}


char* on_user_info_menu_group_text_get_cb(void *data, Evas_Object *obj, const char *part)
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

char* on_user_info_menu_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;

	appdata_s *ad = evas_object_data_get(obj, "app_data");

	if (id == 0) {
		if (ad && ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->is_blocked == 1) {
			return strdup("UnBlock");
		} else {
			return strdup("Block");
		}

	} else {
		if (ad && ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->is_deleted == 1) {
			return strdup("Add");
		} else {
			return strdup("Delete");
		}
	}
}

void on_user_info_msg_popup_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
}

void on_user_info_menu_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (ad->msg_popup || ad->current_app_state != TG_SET_USER_INFO_STATE) {
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
	eext_object_event_callback_add(ad->msg_popup, EEXT_CALLBACK_BACK, on_user_info_msg_popup_back_cb, ad);
	evas_object_size_hint_weight_set(ad->msg_popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_data_set(ad->msg_popup, "app_data", ad);
	box = elm_box_add(ad->msg_popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	itc.item_style = "default";
	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	if (sel_item->use_data->peer_type == TGL_PEER_USER) {
		itc.func.text_get = on_user_info_menu_text_get_cb;

		itc.func.content_get = NULL;
		itc.func.state_get = NULL;
		itc.func.del = NULL;

		for (i = 0; i < 2; i++) {
			elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_user_info_menu_option_selected_cb, ad);
		}

	} else if (sel_item->use_data->peer_type == TGL_PEER_CHAT) {
		itc.func.text_get = on_user_info_menu_group_text_get_cb;

		itc.func.content_get = NULL;
		itc.func.state_get = NULL;
		itc.func.del = NULL;

		for (i = 0; i < 3; i++) {
			elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_user_info_menu_option_selected_cb, ad);
		}

	} else {

	}
	evas_object_data_set(genlist, "app_data", ad);

	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);
	evas_object_size_hint_min_set(box, -1, 230);
	elm_object_content_set(ad->msg_popup, box);
	evas_object_show(ad->msg_popup);
}


/************************ Menu Handler ********************/




Evas_Object* on_buddy_info_requested(void *data, Evas_Object *obj, const char *part)
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

		evas_object_data_set(ad->nf, "user_profile_pic", profile_pic);

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

		elm_object_part_content_set(user_status_layout, "swallow.status", status_lbl);
		return user_status_layout;
	} else {

	}
	return eo;
}

Evas_Object* on_buddy_phone_info_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	int id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	if (!strcmp(part, "elm.swallow.icon.0")) {
		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		Evas_Object* user_status_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(user_status_layout, edj_path, "main_list_name_status_item");
		evas_object_size_hint_weight_set(user_status_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(user_status_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(user_status_layout);


		char* first_text = NULL;
		char buf[512] = {'\0'};
		if (id == 0) {
			if (ad->buddy_in_cahtting_data->use_data->phone) {
				first_text = ad->buddy_in_cahtting_data->use_data->phone;
			} else {
				first_text = "";
			}
		} else {
			if (ad->buddy_in_cahtting_data->use_data->username && strlen(ad->buddy_in_cahtting_data->use_data->username) > 0 && strstr(ad->buddy_in_cahtting_data->use_data->username, "_null_") == NULL) {
				first_text = ad->buddy_in_cahtting_data->use_data->username;
			} else {
				first_text = "None";
			}
		}

		snprintf(buf, 512, "<font=Tizen:style=Bold color=#000000 align=left><font_size=40>%s</font_size></font>", first_text);

		Evas_Object*  name_lbl = elm_label_add(ad->nf);
		elm_object_text_set(name_lbl, buf);
		evas_object_size_hint_weight_set(name_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(name_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(name_lbl);

		if (id == 1) {
			evas_object_data_set(ad->nf, "settings_user_name_label", name_lbl);
		}

		elm_object_part_content_set(user_status_layout, "swallow.name", name_lbl);

		char* second_text = NULL;
		if (id == 0) {
			second_text = "Phone";
		} else {
			second_text = "Username";
		}
		char status_buf[126] = {'\0'};
		sprintf(status_buf, "<font=Tizen:style=Italic color=#808080 align=left><font_size=35>%s</font_size></font>", second_text);

		Evas_Object*  status_lbl = elm_label_add(ad->nf);
		elm_object_text_set(status_lbl, status_buf);
		evas_object_size_hint_weight_set(status_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(status_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(status_lbl);

		elm_object_part_content_set(user_status_layout, "swallow.status", status_lbl);
		return user_status_layout;
	}
	return eo;
}

void on_message_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (ad) {
		elm_naviframe_item_pop(ad->nf);
		ad->current_app_state = TG_CHAT_MESSAGING_VIEW_STATE;
	}
}

void launch_user_info_screen(appdata_s* ad, int peer_id)
{
	if (!ad) {
		return;
	}
	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}

	ad->current_app_state = TG_SET_USER_INFO_STATE;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "settings_screen");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);


	/**************** user info *********************/
	Evas_Object *pic_name_list = NULL;
	static Elm_Genlist_Item_Class itc;
	pic_name_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(pic_name_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(pic_name_list, ELM_LIST_COMPRESS);
	elm_object_style_set(pic_name_list, "solid/default");
	evas_object_size_hint_weight_set(pic_name_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(pic_name_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_data_set(pic_name_list, "app_data", ad);

	itc.item_style = "type1";
	itc.func.text_get = NULL;
	itc.func.content_get = on_buddy_info_requested;
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

	Evas_Object *phone_num_list = NULL;
	static Elm_Genlist_Item_Class sitc;
	phone_num_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(phone_num_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(phone_num_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(phone_num_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(phone_num_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_data_set(phone_num_list, "app_data", ad);

	sitc.item_style = "type1";
	sitc.func.text_get = NULL;
	sitc.func.content_get = on_buddy_phone_info_requested;
	sitc.func.state_get = NULL;
	sitc.func.del = NULL;
	for (int i = 0 ; i < 2; i++) {
		elm_genlist_item_append(phone_num_list, &sitc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
	}

	evas_object_show(phone_num_list);
	elm_object_part_content_set(layout, "phone_num_layout", phone_num_list);

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
	elm_image_file_set(msg_image, ui_utils_get_resource(FLOATING_MSG_ICON), NULL);
	evas_object_size_hint_weight_set(msg_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(msg_image, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(msg_image);
	elm_object_content_set(msg_btn, msg_image);

	elm_object_part_content_set(layout, "cam_layout", msg_btn);
	evas_object_smart_callback_add(msg_btn, "clicked", on_message_button_clicked, ad);
	evas_object_data_set(msg_btn, "app_data", ad);

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "User Info", NULL, NULL, scroller, NULL);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_MORE, on_user_info_menu_button_clicked, ad);

}

