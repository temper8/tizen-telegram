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

#include "contact_selection_view.h"
#include "group_chat_entry_view.h"
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
		if (id == 0) {
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

				Eina_List *l = NULL;
				user_data_with_pic_s *item = NULL;
				EINA_LIST_FOREACH(ad->buddy_list, l, item) {
					if (!item)
						continue;
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
	Eina_List *list = evas_object_data_get(obj, "result_list");

	if (!list) {
		list = ad->buddy_list;
	}

	if (list && eina_list_count(list) > 0) {
		if (!strcmp(part, "elm.text")) {
			if (id == 0) {
				char buf[512] = { 0, };
				snprintf(buf, 512, "%s", i18n_get_text("IDS_TGRAM_MBODY_SELECT_ALL"));
				return strdup(buf);
			}

			user_data_with_pic_s* item = eina_list_nth(list, id - 1);
			user_data_s* user = item->use_data;

			if (user && user->print_name) {
				char* user_name = replace(user->print_name, '_', " ");
				char buf[512] = {'\0'};
				snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", user_name);
				free(user_name);
				return strdup(buf);
			}
		}
	}

	return NULL;
}

void on_item_checkbox_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
	int id = (int)data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	Eina_Bool checked = elm_check_state_get(obj);
	Evas_Object* buddy_gen_list = evas_object_data_get(obj, "buddy_gen_list");
	Eina_List *list = evas_object_data_get(buddy_gen_list, "result_list");

	if (!list) {
		list = ad->buddy_list;
	}
	if (ad && list && eina_list_count(list) > 0) {
		if (id == 0) {
			for (int i = 0 ; i < eina_list_count(list) ; i++) {
				user_data_with_pic_s *item = eina_list_nth(list, i);
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
			user_data_with_pic_s *item = eina_list_nth(list, id - 1);
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
				Eina_List *l = NULL;
				user_data_with_pic_s *item = NULL;
				EINA_LIST_FOREACH(list, l, item) {
					if (!item)
						continue;
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
	appdata_s *ad;
	int id;

	id = (int)data;

	ad = evas_object_data_get(obj, "app_data");
	if (!ad) {
		return NULL;
	}

	Eina_List *list = evas_object_data_get(obj, "result_list");

	if (!list) {
		list = ad->buddy_list;
	}

	if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *image = NULL;

		if (id == 0 && list && eina_list_count(list) > 0) {
			return eo;
		}

		user_data_with_pic_s *item = eina_list_nth(list, id - 1);
		user_data_s* user = item->use_data;

		if (user->photo_path && strcmp(user->photo_path, "") != 0) {
			image = create_image_object_from_file(user->photo_path, obj);
		} else {
			image = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC), obj);
			evas_object_color_set(image, 45, 165, 224, 255);
		}

		item->contact_icon = image;
		//evas_object_event_callback_add(item->contact_icon, EVAS_CALLBACK_DEL, buddy_icon_del_cb, item);

		if (image) {
			char edj_path[PATH_MAX] = {0, };
			app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
			Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
			elm_layout_file_set(user_pic_layout, edj_path, "search_circle_layout");
			evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(user_pic_layout);
			elm_object_part_content_set(user_pic_layout, "content", item->contact_icon);

			eo = elm_layout_add(obj);
			elm_layout_theme_set(eo, "layout", "list/B/type.2", "default");
			elm_layout_content_set(eo, "elm.swallow.content", user_pic_layout);

		}
	} else if (!strcmp(part, "elm.swallow.end")) {
		if (id == 0 && list && eina_list_count(list) > 0) {

			Eina_Bool all_items_selected = (Eina_Bool)evas_object_data_get(obj, "all_selected");

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

		user_data_with_pic_s *item = eina_list_nth(list, id - 1);
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
		// elm_naviframe_item_pop(ad->nf);
		// Load chat name entry view
		launch_group_chat_name_entry_view(ad);
	} else {
		show_toast(ad, "Select at least 2 buddies.");
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
	ad->current_app_state = TG_PEER_SEARCH_VIEW_STATE;
	evas_object_show(ad->panel);
}

#if 0
static char* _util_get_first_char(char *input_text)
{	/*
	int unicode_len = eina_unicode_utf8_get_len(input_text);
	int str_len = strlen(input_text);
	int lang_byte = str_len / unicode_len + (str_len % unicode_len > 0 ? 1 : 0);

	first_char = strndup(input_text, lang_byte);
	*/
	char *first_char = NULL;
	int count;
	int flag;
	unsigned char mask = 0x80;

	count = 0;
	while (*input_text & mask) {
		mask = mask >> 1;
		count++;
	}

	count = count == 0 ? 1 : count;
	first_char = strndup(input_text, count);

	return first_char;
}

static void _update_index_item(void *data, void *item_data, int id, Eina_List *list)
{
	appdata_s* ad = data;
	if (id == 0) {
		return;
	}
	user_data_with_pic_s* item = eina_list_nth(list, id-1);
	user_data_s* user = item->use_data;

	Evas_Object *index = evas_object_data_get(ad->nf, "fs_index");

	/*
	char *index_text = NULL;
	int unicode_len = eina_unicode_utf8_get_len(user->print_name);
	int str_len = strlen(user->print_name);
	int lang_byte = str_len / unicode_len + (str_len % unicode_len > 0 ? 1 : 0);

	index_text = strndup(user->print_name, lang_byte);
	*/

	char *index_text = _util_get_first_char(user->print_name);

	Elm_Object_Item *it = elm_index_item_append(index, index_text, NULL, NULL);

	elm_object_item_data_set(it, item_data);

}
#endif

static void _append_peer_item(Evas_Object *genlist, appdata_s *ad, Eina_List *item_list)
{
	int i;
	static Elm_Genlist_Item_Class itc;
	Elm_Object_Item* item = NULL;

	itc.item_style = "type1";
	itc.func.text_get = on_buddy_name_get_cb;
	itc.func.content_get = on_buddy_selection_part_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	int count = eina_list_count(item_list);

	evas_object_data_set(genlist, "result_list", item_list);

	if (count > 0) {
		for (i = 0; i < count+1; i++) {
			item = elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_buddy_selected, (void*) i);
			//_update_index_item(ad, item, i, item_list);
		}
	} else {
		i = 1;
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
	}
}

static void _on_search_entry_changed(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	char* entry_text = NULL;

	Evas_Object *buddy_list = evas_object_data_get(ad->nf, "buddy_list");
	Evas_Object *main_layout = evas_object_data_get(ad->nf, "main_layout");
	Evas_Object *index = evas_object_data_get(ad->nf, "fs_index");

	user_data_with_pic_s *item;
	user_data_s* user; // = item->use_data;

	if (!buddy_list) {
		DBG("buddy_list is null");
		return;
	}

	elm_genlist_clear(buddy_list);
	//elm_index_item_clear(index);

	entry_text = trim(elm_entry_markup_to_utf8(elm_object_text_get(obj)));

	Eina_List *result_list = NULL;
	Eina_List *l = NULL;

	if (ucol_is_jamo(entry_text)) {
		LOGD("entry_text is jamo, %s", entry_text);
		EINA_LIST_FOREACH(ad->buddy_list, l, item) {
			int result;
			user = item->use_data;
			result = ucol_compare_first_letters(user->print_name, entry_text);
			if (result == 0) {
				result_list = eina_list_append(result_list, item);
			}
		}
	} else {
		LOGD("entry_text is not jamo, %s", entry_text);
		EINA_LIST_FOREACH(ad->buddy_list, l, item) {
			user = item->use_data;

			if (ucol_search(user->print_name, entry_text) != -ENOENT) {
				result_list = eina_list_append(result_list, item);
			}
		}
	}

	if ((entry_text == NULL || strlen(entry_text) == 0) && result_list == NULL) {
		result_list = ad->buddy_list;
	}

	LOGD("count of result_list is %d", eina_list_count(result_list));

	if (result_list) {
		Evas_Object *fs_layout = evas_object_data_get(ad->nf, "fs_layout");
		_append_peer_item(buddy_list, data, result_list);
		Evas_Object *content = elm_object_part_content_unset(main_layout, "elm.swallow.content");
		if (evas_object_data_get(ad->nf, "no_contents_layout") == content) {
			evas_object_hide(content);
		}
		elm_object_part_content_set(main_layout, "elm.swallow.content", fs_layout);

	} else {
		Evas_Object *no_contents = evas_object_data_get(ad->nf, "no_contents_layout");

		elm_object_part_content_unset(main_layout, "elm.swallow.content");
		elm_object_part_content_set(main_layout, "elm.swallow.content", no_contents);
	}

	elm_index_level_go(index, 0);
	elm_genlist_realized_items_update(buddy_list);
	if (entry_text) {
		free(entry_text);
	}
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

static Evas_Object *create_searchbar(Evas_Object* parent, void* data)
{
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* layout = elm_layout_add(parent);
	elm_layout_file_set(layout, edj_path, "");

	/* edit field layout */
	Evas_Object* searchbar_layout = elm_layout_add(parent);
	elm_layout_theme_set(searchbar_layout, "layout", "searchfield", "singleline");
	evas_object_size_hint_align_set(searchbar_layout, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(searchbar_layout, EVAS_HINT_EXPAND, 0.0);
	//evas_object_event_callback_add(searchbar_layout, EVAS_CALLBACK_DEL, _searchbar_layout_del_cb, NULL);

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

static void _index_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object *buddy_list = evas_object_data_get(ad->nf, "buddy_list");
	//Elm_Object_Item *gl_item = elm_genlist_first_item_get(search_list);

	user_data_with_pic_s* gl_item = NULL;//eina_list_nth(ad->search_peer_list, 0);

	//tg_peer_info_s* user = item->use_data;
	Eina_List *list = ad->buddy_list;
	int index = 0;
	Eina_List *l;

	EINA_LIST_FOREACH(list, l, gl_item) {
		if (ucol_compare_first_letters(gl_item->use_data->print_name, elm_index_item_letter_get(event_info)) == 0) {
			break;
		}
		index++;
	}

	if (eina_list_count(list) == index) {
		return;
	}

	Elm_Object_Item *item = elm_genlist_nth_item_get(buddy_list, ++index);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
}

static Evas_Object* create_fastscroll(appdata_s *ad)
{
	Evas_Object *parent = ad->nf;
	Evas_Object *index;
	int i = 0, j, len;
	char *str;
	char buf[PATH_MAX] = {0, };

	index = elm_index_add(parent);
	elm_object_part_content_set(parent, "elm.swallow.fastscroll", index);
	elm_index_autohide_disabled_set(index, EINA_TRUE);
	elm_index_omit_enabled_set(index, EINA_TRUE);

	/* 1. Special character & Numbers */
	elm_index_item_append(index, "#", NULL, NULL);

	/* 2. Local language */
	str = i18n_get_text("IDS_COM_BODY_ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	len = strlen(str);

	while (i < len) {
		j = i;
		eina_unicode_utf8_next_get(str, &i);
		snprintf(buf, i - j + 1, "%s", str + j);
		buf[i - j + 1] = 0;

		elm_index_item_append(index, buf, NULL, NULL);
	}
	elm_index_level_go(index, 0);

	evas_object_smart_callback_add(index, "selected", _index_selected_cb, ad);
	//evas_object_smart_callback_add(index, "changed", _index_changed_cb, NULL);
	//evas_object_smart_callback_add(index, "language,changed", _index_language_changed_cb, NULL);

	return index;
}

void launch_contact_selction_view(void *data)
{
	appdata_s* ad = data;
	ad->current_app_state = TG_BUDDY_LIST_SELECTION_STATE;

	if (ad->panel) {
		evas_object_hide(ad->panel);
		elm_panel_hidden_set(ad->panel, EINA_TRUE);
	}

	elm_layout_theme_set(ad->layout, "layout", "application", "default");

	/* Modified */
	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_theme_set(layout, "layout", "application", "searchbar_base");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);

	Evas_Object* searchbar_layout = create_searchbar(layout, ad);
	elm_object_part_content_set(layout, "searchbar", searchbar_layout);

	Evas_Object* fs_layout = elm_layout_add(layout);
	elm_layout_theme_set(fs_layout, "layout", "application", "fastscroll");
	elm_object_part_content_set(layout, "elm.swallow.content", fs_layout);

	Evas_Object* index = create_fastscroll(ad);
	elm_object_part_content_set(fs_layout, "elm.swallow.fastscroll", index);

	Evas_Object* buddy_gen_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(buddy_gen_list, ELM_LIST_COMPRESS);

	// FIXME: Deprecated API
	// elm_genlist_decorate_mode_set(buddy_gen_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(buddy_gen_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(buddy_gen_list, EVAS_HINT_FILL, EVAS_HINT_FILL);

	evas_object_data_set(buddy_gen_list, "app_data", ad);
	elm_object_part_content_set(fs_layout, "elm.swallow.content", buddy_gen_list);

	Eina_Bool all_items_selected = EINA_FALSE;
	evas_object_data_set(buddy_gen_list, "all_selected", (void *)((int)all_items_selected));
#if 0
	static Elm_Genlist_Item_Class itc;

	itc.item_style = "type1";
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
#endif
	evas_object_show(buddy_gen_list);

	_append_peer_item(buddy_gen_list, ad, ad->buddy_list);

	/* no contents */
	Evas_Object *nocontents = elm_layout_add(ad->nf);
	elm_layout_theme_set(nocontents, "layout", "nocontents", "default");
	evas_object_size_hint_weight_set(nocontents, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(nocontents, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_text_set(nocontents, "elm.text", _("IDS_TGRAM_NPBODY_NO_RESULTS_FOUND_ABB"));
	evas_object_data_set(ad->nf, "no_contents_layout", nocontents);

	evas_object_data_set(ad->nf, "fs_layout", fs_layout);
	evas_object_data_set(ad->nf, "fs_index", index);
	evas_object_data_set(ad->nf, "main_layout", layout);
	evas_object_data_set(ad->nf, "buddy_list", buddy_gen_list);

	Evas_Object* done_btn = elm_button_add(ad->layout);
	elm_object_style_set(done_btn, "naviframe/title_right");
	evas_object_smart_callback_add(done_btn, "clicked", on_done_buton_clicked, ad);
	elm_object_text_set(done_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_DONE_ABB"));
	evas_object_show(done_btn);

	Evas_Object* cancel_btn = elm_button_add(ad->layout);
	elm_object_style_set(cancel_btn, "naviframe/title_left");
	evas_object_smart_callback_add(cancel_btn, "clicked", on_cancel_buton_clicked, ad);
	elm_object_text_set(cancel_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_CANCEL_ABB"));
	evas_object_show(cancel_btn);

	Elm_Object_Item* buddy_sel_nav_item = NULL;
	buddy_sel_nav_item = elm_naviframe_item_push(ad->nf, i18n_get_text("IDS_TGRAM_TMBODY_SELECT_CONTACTS_ABB"), NULL, NULL, layout, NULL);
	elm_object_item_part_content_set(buddy_sel_nav_item, "title_right_btn", done_btn);
	elm_object_item_part_content_set(buddy_sel_nav_item, "title_left_btn", cancel_btn);

}
