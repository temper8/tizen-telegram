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

#include "tg_search_message_view.h"
#include "tg_user_main_view.h"
#include "tg_start_messaging_view.h"
#include "tg_messaging_view.h"
#include "contact_selection_view.h"
#include "tg_search_peer_view.h"
#include "tg_settings_view.h"
#include "tg_db_manager.h"
#include "server_requests.h"
#include "tg_db_wrapper.h"
#include "ucol.h"

static Evas_Object* create_image_object_from_file(const char *icon_name, Evas_Object *parent)
{
	Evas_Object *icon = elm_image_add(parent);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_image_file_set(icon, icon_name, NULL);
	evas_object_show(icon);
	return icon;
}

static void on_buddy_date_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	tg_main_list_item_s *item  = data;
	item->date_lbl = NULL;
}

static void on_main_chat_item_selected(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	appdata_s* ad = evas_object_data_get(obj, "app_data");
	Eina_List *list = evas_object_data_get(obj, "result_list");
	int item_id = (int) data;

	tg_main_list_item_s* sel_item = eina_list_nth(list, item_id);
	ad->buddy_in_cahtting_data = NULL;
	ad->peer_in_cahtting_data = NULL;
	int buddy_id = -1;
	if (!sel_item) {
		return;
	}

	if (sel_item->peer_type == TGL_PEER_CHAT) {
		tg_chat_info_s* chat_info = get_chat_info(sel_item->peer_id);
		if (!chat_info) {
			show_loading_popup(ad);
			send_update_chat_request(ad, ad->service_client, sel_item->peer_id);
			return;
		}
	}

	Eina_List *l = NULL;
	if (sel_item->peer_type == TGL_PEER_USER) {
		user_data_with_pic_s *item = NULL;
		EINA_LIST_FOREACH(ad->buddy_list, l, item) {
			user_data_s* user_data = item->use_data;
			if (user_data->user_id.id == sel_item->peer_id) {
				ad->buddy_in_cahtting_data = item;
				break;
			}
		}

		if (ad->buddy_in_cahtting_data == NULL) {
			l = NULL;
			user_data_with_pic_s *item = NULL;
			EINA_LIST_FOREACH(ad->unknown_buddy_list, l, item) {
				user_data_s* user_data = item->use_data;
				if (user_data->user_id.id == sel_item->peer_id) {
					ad->buddy_in_cahtting_data = item;
					break;
				}
			}
		}
	}

	l = NULL;
	peer_with_pic_s *pic_item = NULL;
	int pos = 0;
	EINA_LIST_FOREACH(ad->peer_list, l, pic_item) {
		tg_peer_info_s* item = pic_item->use_data;
		if (item->peer_id == sel_item->peer_id) {
			ad->peer_in_cahtting_data = pic_item;
			buddy_id = pos;
			break;
		}
		pos++;
	}

	ad->main_item_in_cahtting_data = sel_item;
	elm_naviframe_item_pop(ad->nf);
	delete_floating_button(ad);
	launch_messaging_view_cb(ad, buddy_id);
}

static Evas_Object *on_chat_item_load_requested(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	Eina_List *list = evas_object_data_get(obj, "result_list");
	if (list == NULL || eina_list_count(list) <= 0)
		return NULL;

	tg_main_list_item_s *item = eina_list_nth(list, id);
	if (!item)
		return NULL;

	Eina_Bool is_empty_msg = EINA_FALSE;
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
	Eina_Bool is_success =EINA_FALSE;

	if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *profile_pic = NULL;
		if (item->profile_pic_path && strcmp(item->profile_pic_path, "") != 0) {
			profile_pic = elm_image_add(obj);
			evas_object_size_hint_weight_set(profile_pic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(profile_pic, EVAS_HINT_FILL, EVAS_HINT_FILL);
			elm_object_focus_set(profile_pic, EINA_FALSE);
			is_success = elm_image_file_set(profile_pic, item->profile_pic_path, NULL);
		}
		if (!is_success || !item->profile_pic_path || strcmp(item->profile_pic_path, "") == 0) {
			if (item->peer_type == TGL_PEER_USER) {
				profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC), obj);
				// send download request again To-Do
			} else if (item->peer_type == TGL_PEER_CHAT) {
				profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_MULTI_PIC), obj);
				// send download request again To-Do
			} else {
				profile_pic = NULL;
			}
		}

		if (profile_pic) {
			evas_object_color_set(profile_pic, 45, 165, 224, 255);
			evas_object_show(profile_pic);
		}
		Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(user_pic_layout, edj_path, "circle_layout");
		evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_min_set(user_pic_layout, 98, 98);
		evas_object_show(user_pic_layout);
		elm_object_part_content_set(user_pic_layout, "content", profile_pic);

		return user_pic_layout;
	} else if (!strcmp(part, "elm.swallow.end")) {
		Evas_Object* item_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(item_layout, edj_path, "main_list_date");

		evas_object_size_hint_weight_set(item_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(item_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(item_layout);

		Eina_Bool is_today = compare_date_with_current_date(item->last_seen_time);
		Evas_Object* time_lbl = elm_label_add(ad->nf);
		char *format = NULL;
		time_t t = item->last_seen_time;
		struct tm lt;
		char res[28] = {'\0'};
		char time_str[128] = {0,};
		if (is_today) {
			format = "%I:%M %p";
		} else {
			format = "%b %d";
		}
		(void) localtime_r(&t, &lt);
		if (strftime(res, sizeof(res), format, &lt) == 0)
			snprintf(res, sizeof(res) - 1, "%s", "wrong time");

		sprintf(time_str, "<font=Tizen:style=Regular color=#666666 align=right><font_size=30>%s</font_size></font>", res);
		elm_object_text_set(time_lbl, time_str);

		evas_object_size_hint_weight_set(time_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(time_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(time_lbl);

		item->date_lbl = time_lbl;
		evas_object_event_callback_add(item->date_lbl, EVAS_CALLBACK_DEL, on_buddy_date_deleted, item);

		elm_object_part_content_set(item_layout, "swallow.date", time_lbl);

		/*************************** date ***************************************/

		/*************************** sent message status ***************************************/
		if (is_empty_msg) {
			return item_layout;
		}

		if (item->is_out_msg && !(item->last_msg_service)) {
			Evas_Object *status_obj;
			status_obj = elm_icon_add(obj);
			evas_object_size_hint_weight_set(status_obj, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(status_obj, EVAS_HINT_FILL, EVAS_HINT_FILL);

			if (item->last_msg_status == TG_MESSAGE_STATE_SENDING) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENDING_ICON), NULL);
			} else if (item->last_msg_status == TG_MESSAGE_STATE_SENT) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENT_ICON), NULL);
			} else if (item->last_msg_status == TG_MESSAGE_STATE_DELIVERED) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_DELIVERED_ICON), NULL);
			} else if (item->last_msg_status == TG_MESSAGE_STATE_RECEIVED) {

			} else if (item->last_msg_status == TG_MESSAGE_STATE_FAILED) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_FAILED_ICON), NULL);
			} else if (item->last_msg_status == TG_MESSAGE_STATE_READ) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_READ_ICON), NULL);
			} else if (item->last_msg_status == TG_MESSAGE_STATE_UNKNOWN) {

			}
			evas_object_color_set(status_obj, 75, 96, 178, 255);
			elm_object_part_content_set(item_layout, "swallow.read_unread_status", status_obj);
		} else {
			if (item->number_of_unread_msgs > 0) {
				char unread_msgs[256];
				sprintf(unread_msgs, "%d", item->number_of_unread_msgs);
				Evas_Object* msg_status = elm_layout_add(ad->nf);
				elm_layout_file_set(msg_status, edj_path, "count_bg_layout");
				evas_object_size_hint_weight_set(msg_status, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(msg_status, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_show(msg_status);
				elm_object_part_text_set(msg_status, "content", unread_msgs);
				elm_object_part_content_set(item_layout, "swallow.unread_count", msg_status);
			}
		}
		return item_layout;
	}
	return NULL;
}

static char* on_chat_text_load_requested(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	Eina_List *list = evas_object_data_get(obj, "result_list");
	if (list == NULL || eina_list_count(list) <= 0)
		return NULL;

	tg_main_list_item_s *item = eina_list_nth(list, id);
	if (!item)
		return NULL;

	if (!strcmp(part, "elm.text")) {
		char* user_name = NULL;
		if (item->highlight_text) {
			user_name = str_replace(item->highlight_text, "_null_", "");
		} else {
			user_name = str_replace(item->buddy_display_name, "_null_", "");
		}
		char buf[512] = {'\0'};
		snprintf(buf, sizeof(buf), "<font=Tizen:style=Large color=#000000 align=left><font_size=40>%s</font_size></font>", user_name);
		free(user_name);
		return strdup(buf);
	} else if (!strcmp(part, "elm.text.sub")) {
		char* org_msg = NULL;
		char status_buf[126] = {'\0'};
		if (item->last_message) {
			org_msg = str_replace(item->last_message, "<br/>", " ");
		} else {
			org_msg = strdup("");
		}
		if (item->last_msg_service) {
			snprintf(status_buf, sizeof(status_buf), "<font=Tizen:style=Bold color=#158CB0 align=left><font_size=28>%s</font_size></font>", org_msg);
		} else {
			snprintf(status_buf, sizeof(status_buf), "<font=Tizen:style=Bold color=#A4A4A4 align=left><font_size=28>%s</font_size></font>", org_msg);
		}
		free(org_msg);
		return strdup(status_buf);
	}
	return NULL;
}


static void _append_peer_item(Evas_Object *genlist, appdata_s *ad, Eina_List *item_list)
{
	int i;
	static Elm_Genlist_Item_Class itc;
	Elm_Object_Item* item = NULL;

	itc.item_style = "type1";
	itc.func.text_get = on_chat_text_load_requested;
	itc.func.content_get = on_chat_item_load_requested;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	int count = eina_list_count(item_list);

	evas_object_data_set(genlist, "result_list", item_list);

	if (count > 0) {
		for (i = 0; i < count; i++) {
			item = elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_main_chat_item_selected, (void*) i);
		}
	}
}

static void _on_search_entry_changed(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	char* entry_text = NULL;
	tg_main_list_item_s* item = NULL;
	Eina_List *result_list = NULL;
	Eina_List *l = NULL;

	Evas_Object *peer_list = evas_object_data_get(ad->nf, "peer_list");
	Evas_Object *main_layout = evas_object_data_get(ad->nf, "main_layout");
	if (!peer_list) {
		DBG("peer_list is null");
		return;
	}

	elm_genlist_clear(peer_list);
	entry_text = trim(elm_entry_markup_to_utf8(elm_object_text_get(obj)));

	if (ucol_is_jamo(entry_text)) {
		LOGD("entry_text is jamo, %s", entry_text);
		EINA_LIST_FOREACH(ad->main_list, l, item) {
			int result;
			result = ucol_compare_first_letters(item->peer_print_name, entry_text);
			if (result == 0)
				result_list = eina_list_append(result_list, item);
		}
	} else {
		LOGD("entry_text is not jamo, %s", entry_text);
		EINA_LIST_FOREACH(ad->main_list, l, item) {
			if (!item) continue;
			int select_start = -ENOENT;
			if (item->highlight_text) {
				free(item->highlight_text);
				item->highlight_text = NULL;
			}

			select_start = ucol_search(item->peer_print_name, entry_text);
			if (select_start != -ENOENT) {
				char *last_name = str_case_replace(item->buddy_display_name, entry_text, "<font=Tizen:style=Large color=#2da5e0 align=left>", "</font>");
				item->highlight_text = last_name;
				result_list = eina_list_append(result_list, item);
			}
		}
	}

	if ((entry_text == NULL || strlen(entry_text) == 0) && result_list == NULL)
		result_list = ad->main_list;

	LOGD("count of result_list is %d", eina_list_count(result_list));

	Evas_Object *no_contents = evas_object_data_get(ad->nf, "no_contents_layout");
	Evas_Object *content = elm_object_part_content_get(main_layout, "elm.swallow.content");

	if (result_list) {
		_append_peer_item(peer_list, data, result_list);

		if (no_contents == content) {
			elm_object_part_content_unset(main_layout, "elm.swallow.content");
			evas_object_hide(content);
		}
		elm_object_part_content_set(main_layout, "elm.swallow.content", peer_list);
	} else {
		if (content == peer_list) {
			elm_object_part_content_unset(main_layout, "elm.swallow.content");
			evas_object_hide(peer_list);
		}
		elm_object_part_content_set(main_layout, "elm.swallow.content", no_contents);
	}
	elm_genlist_realized_items_update(peer_list);
	if (entry_text)
		free(entry_text);
}

static void _on_search_entry_focused(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout = data;
	if (elm_object_focus_get(layout)) {
		elm_object_signal_emit(layout, "elm,state,focused", "");
	} else{
		elm_object_signal_emit(layout, "elm,state,unfocused", "");
	}
}

static Evas_Object *_create_searchbar(Evas_Object* parent, void* data)
{
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* layout = elm_layout_add(parent);
	elm_layout_file_set(layout, edj_path, "");

	/* editfield layout */
	Evas_Object* searchbar_layout = elm_layout_add(parent);
	elm_layout_theme_set(searchbar_layout, "layout", "searchfield", "singleline");
	evas_object_size_hint_align_set(searchbar_layout, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(searchbar_layout, EVAS_HINT_EXPAND, 0.0);

	/* entry */
	Evas_Object* searchbar_entry = elm_entry_add(searchbar_layout);
	elm_entry_cursor_end_set(searchbar_entry);
	evas_object_size_hint_weight_set(searchbar_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(searchbar_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(searchbar_entry,  EINA_TRUE);
	elm_entry_scrollable_set(searchbar_entry, EINA_FALSE);
	elm_entry_cnp_mode_set(searchbar_entry, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(searchbar_entry, EINA_TRUE);
	elm_object_part_text_set(searchbar_entry, "elm.guide", i18n_get_text("IDS_TGRAM_NPBODY_SEARCH"));
	elm_object_focus_set(searchbar_entry, EINA_FALSE);

	limit_filter_data.max_char_count = 255;
	elm_entry_markup_filter_append(searchbar_entry, elm_entry_filter_limit_size, &limit_filter_data);

	evas_object_smart_callback_add(searchbar_entry, "changed", _on_search_entry_changed, data);
	evas_object_smart_callback_add(searchbar_entry, "preedit,changed", _on_search_entry_changed, data);
	evas_object_smart_callback_add(searchbar_entry, "focused", _on_search_entry_focused, searchbar_layout);

	elm_object_part_content_set(searchbar_layout, "elm.swallow.content", searchbar_entry);
	return searchbar_layout;
}

static Evas_Object* create_genlist(appdata_s *ad, Evas_Object *layout)
{
	Evas_Object *list = elm_genlist_add(ad->nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(list);
	elm_object_focus_set(list, EINA_TRUE);
	return list;
}

void launch_search_message_view(appdata_s* ad)
{
	if (!ad)
		return;

	ad->current_app_state = TG_USER_MAIN_VIEW_SELECTION_STATE;

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_theme_set(layout, "layout", "application", "searchbar_base");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);

	Evas_Object* searchbar_layout = _create_searchbar(layout, ad);
	elm_object_part_content_set(layout, "searchbar", searchbar_layout);

	Evas_Object* peer_list = create_genlist(ad, layout);
	evas_object_data_set(peer_list, "app_data", ad);
	elm_object_part_content_set(layout, "elm.swallow.content", peer_list);

	_append_peer_item(peer_list, ad, ad->main_list);

	/* no contents */
	Evas_Object *nocontents = elm_layout_add(ad->nf);
	elm_layout_theme_set(nocontents, "layout", "nocontents", "default");
	evas_object_size_hint_weight_set(nocontents, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(nocontents, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_text_set(nocontents, "elm.text", _("IDS_TGRAM_NPBODY_NO_RESULTS_FOUND_ABB"));
	evas_object_hide(nocontents);

	evas_object_data_set(ad->nf, "no_contents_layout", nocontents);
	evas_object_data_set(ad->nf, "main_layout", layout);
	evas_object_data_set(ad->nf, "peer_list", peer_list);

	Elm_Object_Item *it = elm_naviframe_item_push(ad->nf, NULL, NULL, NULL, layout, NULL);
	elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);

}
