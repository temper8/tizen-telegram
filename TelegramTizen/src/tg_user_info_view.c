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

#include "tg_user_info_view.h"
#include "server_requests.h"
#include "tg_user_main_view.h"
#include "tg_add_contact.h"
#include "tg_db_wrapper.h"
#include "tg_search_peer_view.h"

static Evas_Object* get_image_from_path(const char* path, Evas_Object* parent)
{
	if (!path || !parent)
		return NULL;

	Evas_Object *media_image = elm_image_add(parent);
	elm_image_aspect_fixed_set(media_image, EINA_FALSE);
	elm_image_file_set(media_image, path, NULL);
	evas_object_size_hint_weight_set(media_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(media_image, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(media_image);
	return media_image;
}

void on_user_added_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success)
{
	if (!is_success || !ad->buddy_in_cahtting_data || !ad->peer_in_cahtting_data || ad->peer_in_cahtting_data->use_data->peer_id != buddy_id) {
		show_toast(ad, "Failed to add user.");
		return;
	}

	ad->buddy_in_cahtting_data->use_data->is_deleted = 0;
	load_buddy_list_data(ad);
	load_unknown_buddy_list_data(ad);
	load_peer_data(ad);
	load_main_list_data(ad);
	refresh_main_list_view(ad, EINA_FALSE);

	Eina_List *l = NULL;
	user_data_with_pic_s *item = NULL;
	EINA_LIST_FOREACH(ad->buddy_list, l, item) {
		user_data_s* user_data = item->use_data;
		if (user_data->user_id.id == buddy_id) {
			ad->buddy_in_cahtting_data = item;
			break;
		}
	}

	if (ad->buddy_in_cahtting_data == NULL) {
		l = NULL;
		user_data_with_pic_s *item = NULL;
		EINA_LIST_FOREACH(ad->unknown_buddy_list, l, item) {
			user_data_s* user_data = item->use_data;
			if (user_data->user_id.id == buddy_id) {
				ad->buddy_in_cahtting_data = item;
				break;
			}
		}
	}
	l = NULL;
	peer_with_pic_s* pic_item = NULL;
	int pos = 0;
	EINA_LIST_FOREACH(ad->peer_list, l, pic_item) {
		tg_peer_info_s* item = pic_item->use_data;
		if (item->peer_id == buddy_id) {
			ad->peer_in_cahtting_data = pic_item;
			buddy_id = pos;
			break;
		}
		pos++;
	}

	show_toast(ad, "User added successfully");
}

void on_user_deleted_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success)
{
	if (!is_success || !ad->buddy_in_cahtting_data || !ad->peer_in_cahtting_data || ad->peer_in_cahtting_data->use_data->peer_id != buddy_id) {
		show_toast(ad, "Failed to delete user.");
		return;
	}

	ad->buddy_in_cahtting_data->use_data->is_deleted = 1;
	load_buddy_list_data(ad);
	load_unknown_buddy_list_data(ad);
	load_peer_data(ad);
	load_main_list_data(ad);
	refresh_main_list_view(ad, EINA_FALSE);

	Eina_List *l = NULL;
	user_data_with_pic_s *item = NULL;
	EINA_LIST_FOREACH(ad->buddy_list, l, item) {
		user_data_s* user_data = item->use_data;
		if (user_data->user_id.id == buddy_id) {
			ad->buddy_in_cahtting_data = item;
			break;
		}
	}

	if (ad->buddy_in_cahtting_data == NULL) {
		l = NULL;
		user_data_with_pic_s *item = NULL;
		EINA_LIST_FOREACH(ad->unknown_buddy_list, l, item) {
			user_data_s* user_data = item->use_data;
			if (user_data->user_id.id == buddy_id) {
				ad->buddy_in_cahtting_data = item;
				break;
			}
		}
	}

	l = NULL;
	peer_with_pic_s* pic_item = NULL;
	int pos = 0;
	EINA_LIST_FOREACH(ad->peer_list, l, pic_item) {
		tg_peer_info_s* item = pic_item->use_data;
		if (item->peer_id == buddy_id) {
			ad->peer_in_cahtting_data = pic_item;
			buddy_id = pos;
			break;
		}
		pos++;
	}

	show_toast(ad, "User deleted successfully");

}

void on_user_block_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success)
{
	if (!is_success || !ad->buddy_in_cahtting_data || !ad->peer_in_cahtting_data || ad->peer_in_cahtting_data->use_data->peer_id != buddy_id) {
		show_toast(ad, "Failed to block user.");
	}
	ad->buddy_in_cahtting_data->use_data->is_blocked = 1;
	show_toast(ad, "User blocked successfully");
}

void on_user_unblock_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success)
{
	if (!is_success || !ad->buddy_in_cahtting_data || !ad->peer_in_cahtting_data || ad->peer_in_cahtting_data->use_data->peer_id != buddy_id) {
		show_toast(ad, "Failed to unblock user.");
	}
	ad->buddy_in_cahtting_data->use_data->is_blocked = 0;
	show_toast(ad, "User unblocked successfully");
}


static void on_userinfo_menu_canceled(void *data, Evas_Object *obj, void *event_info)
{
	//appdata_s *ad = evas_object_data_get(obj, "app_data");
	Evas_Object *popup = evas_object_data_get(obj, "popup");
	evas_object_del(popup);
}

static void on_user_block_ok_selected(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = evas_object_data_get(obj, "app_data");
	Evas_Object *popup = evas_object_data_get(obj, "popup");

	if (ad->peer_in_cahtting_data && ad->peer_in_cahtting_data->use_data) {
		show_loading_popup(ad);
		peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
		if (get_buddy_block_status(sel_item->use_data->peer_id) == 1) {
			send_unblock_buddy_request(ad, ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id);
		} else {
			send_block_buddy_request(ad, ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id);
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

	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	if (get_buddy_block_status(sel_item->use_data->peer_id) == 1) {
		elm_object_text_set(popup, "Are you sure want to unblock this contact?");
	} else {
		elm_object_text_set(popup, "Are you sure want to block this contact?");
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
		peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
		if (get_buddy_delete_status(sel_item->use_data->peer_id) == 1 || get_buddy_unknown_status(sel_item->use_data->peer_id) == 1) {
			launch_add_contact_screen(ad);
			//send_add_buddy_request(ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id);
		} else {
			show_loading_popup(ad);
			send_delete_buddy_request(ad, ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id);
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
	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	if (get_buddy_delete_status(sel_item->use_data->peer_id) == 1 || get_buddy_unknown_status(sel_item->use_data->peer_id) == 1) {
		elm_object_text_set(popup, "Are you sure want to add this contact?");
	} else {
		elm_object_text_set(popup, "Are you sure want to delete this contact?");
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

	if(!ad || !it)
		return;

	elm_genlist_item_selected_set(it, EINA_FALSE);
	int id = (int)elm_object_item_data_get(it);

	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	tg_peer_info_s *user_data = sel_item->use_data;

	if (!sel_item || !user_data)
		return;


	switch(id) {
	case 0:
		if (user_data->peer_type == TGL_PEER_USER) {
			if (get_buddy_delete_status(sel_item->use_data->peer_id) == 1 || get_buddy_unknown_status(sel_item->use_data->peer_id) == 1) {
				// To-Do
			} else {
				on_delete_selected_cb(ad);
			}
		}
		break;
	case 1:
		ad->is_loading_from_profile_view = EINA_TRUE;
		on_create_new_contact(ad);
		break;
#if 0
	case 2:
		show_toast(ad, i18n_get_text("IDS_TGRAM_OPT_SHARE"));
		break;
	case 3:
#else
	case 2:
#endif
		if (user_data->peer_type == TGL_PEER_USER) {
			on_block_selected_cb(ad);
		}
		break;
	}
	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
}

char* on_user_info_menu_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	appdata_s *ad = evas_object_data_get(obj, "app_data");
	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;

	if (!ad || !sel_item)
		return NULL;

	switch(id) {
	case 0:
		if (get_buddy_delete_status(sel_item->use_data->peer_id) == 1 ||
				get_buddy_unknown_status(sel_item->use_data->peer_id) == 1)
			return strdup(i18n_get_text("IDS_TGRAM_OPT_ADD_TO_TELEGRAM"));
		else
			return strdup(i18n_get_text("IDS_TGRAM_OPT_DELETE"));

	case 1:
		if(!is_telegram_account(sel_item->use_data->peer_id))
			return strdup(i18n_get_text("IDS_TGRAM_OPT_EDIT"));
		else
			return NULL;
#if 0
	case 2:
		return strdup(i18n_get_text("IDS_TGRAM_OPT_SHARE"));

	case 3:
#else
	case 2:
#endif
		if (get_buddy_block_status(sel_item->use_data->peer_id) == 1)
			return strdup(i18n_get_text("IDS_TGRAM_OPT_UNBLOCK"));
		else
			return strdup(i18n_get_text("IDS_TGRAM_OPT_BLOCK"));
	}
	return NULL;
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
	if (ad->msg_popup || ad->current_app_state != TG_SET_USER_INFO_STATE)
		return;


	static Elm_Genlist_Item_Class itc;
	Evas_Object *genlist;
	Evas_Object *win = ad->win;

	ad->msg_popup = elm_popup_add(win);
	elm_popup_align_set(ad->msg_popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(ad->msg_popup, EEXT_CALLBACK_BACK, on_user_info_msg_popup_back_cb, ad);
	evas_object_size_hint_weight_set(ad->msg_popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_data_set(ad->msg_popup, "app_data", ad);

	genlist = elm_genlist_add(ad->msg_popup);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	evas_object_data_set(genlist, "app_data", ad);

	itc.item_style = "default";
	itc.func.text_get = on_user_info_menu_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	int number_of_menus = 3;
	Eina_Bool is_need_continue = EINA_FALSE;
	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	if(sel_item && is_telegram_account(sel_item->use_data->peer_id)) {
		number_of_menus = 2;
		is_need_continue = EINA_TRUE;
	}

	for (int i = 0; i < number_of_menus; i++) {
		if(is_need_continue && i == 1)
			continue;
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_user_info_menu_option_selected_cb, ad);
	}

	evas_object_show(genlist);
	elm_object_content_set(ad->msg_popup, genlist);
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
		if (profile_time)
			online_status = elm_entry_markup_to_utf8(elm_object_text_get(profile_time));

		char status_buf[126] = {'\0'};
		sprintf(status_buf, "<font=Tizen:style=Normal color=#FFFFFF align=left><font_size=35>%s</font_size></font>", online_status);

		Evas_Object*  status_lbl = elm_label_add(ad->nf);
		elm_object_text_set(status_lbl, status_buf);
		evas_object_size_hint_weight_set(status_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(status_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(status_lbl);

		elm_object_part_content_set(user_status_layout, "swallow.status", status_lbl);
		return user_status_layout;
	} else {
		// nothing to do
	}
	return eo;
}

Evas_Object* on_buddy_phone_info_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (strcmp(part, "elm.swallow.icon.0")) {
		return eo;
	}
	int id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");

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
		if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->phone) {
			first_text = ad->buddy_in_cahtting_data->use_data->phone;
		} else {
			char *phone_no = get_buddy_phone_num_from_id(ad->peer_in_cahtting_data->use_data->peer_id);
			if (phone_no) {
				first_text = phone_no;
			} else {
				first_text = "";
			}
		}
	} else {
		if (ad->buddy_in_cahtting_data && ad->buddy_in_cahtting_data->use_data->username && strlen(ad->buddy_in_cahtting_data->use_data->username) > 0 && strstr(ad->buddy_in_cahtting_data->use_data->username, "_null_") == NULL) {
			first_text = ad->buddy_in_cahtting_data->use_data->username;
		} else {
			first_text = "None";
		}
	}

	snprintf(buf, sizeof(buf) - 1, "<font=Tizen:style=Bold color=#000000 align=left><font_size=40>%s</font_size></font>", first_text);

	Evas_Object*  name_lbl = elm_label_add(ad->nf);
	elm_object_text_set(name_lbl, buf);
	evas_object_size_hint_weight_set(name_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(name_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(name_lbl);

	if (id == 1)
		evas_object_data_set(ad->nf, "settings_user_name_label", name_lbl);

	elm_object_part_content_set(user_status_layout, "swallow.name", name_lbl);

	char* second_text = NULL;
	if (id == 0) {
		second_text = "Phone";
	} else {
		second_text = "Username";
	}
	char status_buf[126] = {'\0'};
	sprintf(status_buf, "<font=Tizen:style=Normal color=#808080 align=left><font_size=35>%s</font_size></font>", second_text);

	Evas_Object*  status_lbl = elm_label_add(ad->nf);
	elm_object_text_set(status_lbl, status_buf);
	evas_object_size_hint_weight_set(status_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(status_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(status_lbl);

	elm_object_part_content_set(user_status_layout, "swallow.status", status_lbl);
	return user_status_layout;

}

void on_message_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad)
		return;

	elm_naviframe_item_pop(ad->nf);
	ad->current_app_state = TG_CHAT_MESSAGING_VIEW_STATE;
}

void on_userinfo_back_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad)
		return;

	app_nf_back_cb(data, obj, event_info);
}


static void on_user_info_icon_pressed(void *data, Evas_Object *obj, void *event_info)
{
	if (data)
		evas_object_color_set(data, 45, 165, 224, 178);
}

static void on_user_info_icon_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	if (data)
		evas_object_color_set(data, 45, 165, 224, 255);
}

static void on_user_info_msg_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad)
		return;
	elm_naviframe_item_pop(ad->nf);
	ad->current_app_state = TG_CHAT_MESSAGING_VIEW_STATE;
}

static void on_user_info_call_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad)
		return;

	app_control_h app_control;
	int ret = app_control_create(&app_control);
	if (ret != APP_CONTROL_ERROR_NONE)
		return;

	app_control_set_operation(app_control, APP_CONTROL_OPERATION_CALL);
	char phone_num[512] = {0,};
	strcpy(phone_num, "tel:");
	strcat(phone_num, ad->buddy_in_cahtting_data->use_data->phone);
	app_control_set_uri(app_control, phone_num);
	if (app_control_send_launch_request(app_control, NULL, NULL) == APP_CONTROL_ERROR_NONE) {
		// sms view launched
	}
	app_control_destroy(app_control);
}

static void compare_with_current_date(int rtime, Elm_Object_Item *nf_it)
{
	char time_str[256] = {0,};
	time_t local_t = time(NULL);
	int diff_sec = 0;
	int diff_min = 0;
	int diff_hour = 0;
	int diff_day = 0;

	diff_sec = local_t - rtime;
	diff_min = diff_sec / 60;
	diff_hour = diff_min / 60;
	diff_day = diff_hour / 24;
	LOGD("different : day : %d, hour = %d, min = %d, sec = %d", diff_day, diff_hour, diff_min, diff_sec);


	if (diff_day > 30) {
		snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_LONG_TIME_AGO_ABB"));
		goto OUT;
	}

	if (diff_day > 7) {
		snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_WITHIN_A_MONTH_ABB"));
		goto OUT;
	}
	if (diff_day > 1) {
		snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_WITHIN_A_WEEK_ABB"));
		goto OUT;
	}

	if (diff_hour > 1) {
		snprintf(time_str, sizeof(time_str) - 1, i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_PD_HOURS_AGO_ABB"), diff_hour);
		goto OUT;
	}

	if (diff_hour == 1) {
		snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_1_HOUR_AGO_ABB"));
		goto OUT;
	}
	if (diff_min > 1) {
		snprintf(time_str, sizeof(time_str) - 1, i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_PD_MINUTES_AGO_ABB"), diff_min);
		goto OUT;
	}
	if (diff_min == 1) {
		snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_1_MINUTE_AGO_ABB"));
		goto OUT;
	}
	snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_RECENTLY_ABB"));

	OUT:
	elm_object_item_part_text_set(nf_it, "subtitle", time_str);
}

void launch_user_info_screen(appdata_s* ad, int peer_id)
{
	if (!ad)
		return;

	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
	ad->current_app_state = TG_SET_USER_INFO_STATE;
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "buddy_info_screen");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);

	char temp_name[512] = {'\0'};
	char* user_name = replace(ad->peer_in_cahtting_data->use_data->print_name, '_', " ");
	snprintf(temp_name, 512, "%s", user_name);
	free(user_name);

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, temp_name, NULL, NULL, scroller, NULL);
	elm_object_item_part_text_set(navi_item, "subtitle", "Subtitle");

	/*********************** set last seen ******************************/

	Eina_List *buddy_details_array = get_buddy_info(ad->peer_in_cahtting_data->use_data->peer_id);
	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List *buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {
			int* temp_online = (int *)eina_list_nth(buddy_details, 12);
			int is_online = *temp_online;
			int* temp_last_seen = (int *)eina_list_nth(buddy_details, 13);
			int last_seen = *temp_last_seen;

			if (is_online > 0) {
				elm_object_item_part_text_set(navi_item, "subtitle", i18n_get_text("IDS_TGRAM_SBODY_ONLINE"));
			} else {
				compare_with_current_date(last_seen, navi_item);
			}

			void* val = NULL;
			EINA_LIST_FREE(buddy_details,val) {
				if (val)
					free(val);
			}
			eina_list_free(buddy_details);
		}
		eina_list_free(buddy_details_array);
	}

	Evas_Object *profile_pic = NULL;
	Evas_Object *image_layout = NULL;

	if (ad->peer_in_cahtting_data->use_data->photo_path && strlen(ad->peer_in_cahtting_data->use_data->photo_path) > 0 && strstr(ad->peer_in_cahtting_data->use_data->photo_path, "_null_") == NULL) {
		image_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(image_layout, edj_path, "contact_image_masking");
		evas_object_size_hint_weight_set(image_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(image_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(image_layout);
		profile_pic = get_image_from_path(ad->peer_in_cahtting_data->use_data->photo_path, ad->nf);
		elm_object_part_content_set(image_layout, "image", profile_pic);
	} else  {
		image_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(image_layout, edj_path, "contact_image_masking");
		evas_object_size_hint_weight_set(image_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(image_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(image_layout);
		profile_pic = get_image_from_path(ui_utils_get_resource(TG_CALLER_ID_IMAGE), ad->nf);
		evas_object_color_set(profile_pic, 45, 165, 224, 225);
		elm_object_part_content_set(image_layout, "image", profile_pic);
	}

	elm_object_part_content_set(layout, "swallow.profile_pic", image_layout);

	Evas_Object *info_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(info_layout, edj_path, "buddy_num_layout");
	evas_object_size_hint_weight_set(info_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(info_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(info_layout);
	elm_object_part_content_set(layout, "swallow.profile_info", info_layout);

	Evas_Object *phone_type = elm_label_add(ad->nf);
	elm_object_style_set(phone_type, "transparent");
	char phone_type_str[256];
	sprintf(phone_type_str, "<font=Tizen:style=Normal color=#A9A9A9 align=left><font_size=35>&nbsp;&nbsp;%s</font_size></font>", i18n_get_text("IDS_TGRAM_BODY_MOBILE_ABB"));
	elm_object_text_set(phone_type, phone_type_str);
	evas_object_size_hint_weight_set(phone_type, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(phone_type, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(phone_type);

	elm_object_part_content_set(info_layout, "swallow.phone_type", phone_type);

	if (ad->buddy_in_cahtting_data) {
		Evas_Object* msg_btn = elm_button_add(ad->nf);
		elm_object_style_set(msg_btn, "transparent");
		evas_object_size_hint_align_set(msg_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(msg_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

		Evas_Object* msg_icon = elm_image_add(ad->nf);
		evas_object_size_hint_align_set(msg_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(msg_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_image_file_set(msg_icon, ui_utils_get_resource(TG_USER_INFO_MESSAGE), NULL);
		evas_object_show(msg_icon);
		evas_object_color_set(msg_icon, 45, 165, 224, 255);
		elm_object_content_set(msg_btn, msg_icon);

		evas_object_smart_callback_add(msg_btn, "clicked", on_user_info_msg_clicked, ad);
		evas_object_smart_callback_add(msg_btn, "pressed", on_user_info_icon_pressed, msg_icon);
		evas_object_smart_callback_add(msg_btn, "unpressed", on_user_info_icon_unpressed, msg_icon);
		elm_object_part_content_set(info_layout, "swallow.phone_msg", msg_btn);

		Evas_Object* call_btn = elm_button_add(ad->nf);
		elm_object_style_set(call_btn, "transparent");
		evas_object_size_hint_align_set(call_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(call_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

		Evas_Object* call_icon = elm_image_add(ad->nf);
		evas_object_size_hint_align_set(call_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(call_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_image_file_set(call_icon, ui_utils_get_resource(TG_USER_INFO_CALL), NULL);
		evas_object_show(call_icon);
		evas_object_color_set(call_icon, 45, 165, 224, 255);
		elm_object_content_set(call_btn, call_icon);

		evas_object_smart_callback_add(call_btn, "clicked", on_user_info_call_clicked, ad);
		evas_object_smart_callback_add(call_btn, "pressed", on_user_info_icon_pressed, call_icon);
		evas_object_smart_callback_add(call_btn, "unpressed", on_user_info_icon_unpressed, call_icon);
		elm_object_part_content_set(info_layout, "swallow.phone_call", call_btn);

		Evas_Object *phone_num = elm_label_add(ad->nf);
		elm_object_style_set(phone_num, "transparent");
		char phone_num_str[256];
		sprintf(phone_num_str, "<font=Tizen:style=Bold color=#000000 align=left><font_size=40>&nbsp;&nbsp;%s</font_size></font>", ad->buddy_in_cahtting_data->use_data->phone);
		elm_object_text_set(phone_num, phone_num_str);
		evas_object_size_hint_weight_set(phone_num, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(phone_num, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(phone_num);
		elm_object_part_content_set(info_layout, "swallow.phone_number", phone_num);
	}
	Evas_Object *back_btn = create_button(ad->nf, "naviframe/back_btn/default", NULL);
	evas_object_smart_callback_add(back_btn, "clicked", on_userinfo_back_button_clicked, ad);
	elm_object_item_part_content_set(navi_item,  "elm.swallow.prev_btn", back_btn);

	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_MORE, on_user_info_menu_button_clicked, ad);
}

