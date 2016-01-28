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

#include "tg_country_selection_view.h"
#include "tg_registration.h"
#include "ucol.h"

extern void append_country_item(Evas_Object *genlist, appdata_s *ad, Eina_List* country_name_list, Eina_List* country_code_list);
static void on_country_search_entry_focused(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout = data;
	if (elm_object_focus_get(layout)) {
		elm_object_signal_emit(layout, "elm,state,focused", "");
	} else{
		elm_object_signal_emit(layout, "elm,state,unfocused", "");
	}
}

static void on_country_search_entry_changed(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object *search_list;
	char *entry_text;
	Eina_List *name_result_list;
	Eina_List *code_result_list;
	Eina_List *l;
	char *name;
	int i;
	int result;

	search_list = evas_object_data_get(ad->nf, "search_list");
	if (!search_list)
		return;

	entry_text = elm_entry_markup_to_utf8(elm_object_text_get(obj));
	if (entry_text == NULL) {
		return;
	}

	elm_genlist_clear(search_list);

	name_result_list = NULL;
	code_result_list = NULL;
	i = 0;
	if (ucol_is_jamo(entry_text)) {
		EINA_LIST_FOREACH(ad->country_names_list, l, name) {
			result = ucol_compare_first_letters(name, entry_text);
			if (result == 0) {
				name_result_list = eina_list_append(name_result_list, name);
				code_result_list = eina_list_append(code_result_list, (void *)i);
			}

			i++;
		}
	} else {
		EINA_LIST_FOREACH(ad->country_names_list, l, name) {
			result = ucol_search(name, entry_text);
			if (result != -ENOENT) {
				name_result_list = eina_list_append(name_result_list, name);
				code_result_list = eina_list_append(code_result_list, (void *)i);
			}

			i++;
		}
	}

	if (name_result_list && code_result_list) {
		append_country_item(search_list, ad, name_result_list, code_result_list);
	} else {
		// TODO: Handles me
	}

	free(entry_text);
}


static Evas_Object *create_country_search_bar(Evas_Object* parent, void* data)
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


	evas_object_smart_callback_add(searchbar_entry, "changed", on_country_search_entry_changed, data);
	evas_object_smart_callback_add(searchbar_entry, "preedit,changed", on_country_search_entry_changed, data);
	evas_object_smart_callback_add(searchbar_entry, "focused", on_country_search_entry_focused, searchbar_layout);

	elm_object_part_content_set(searchbar_layout, "elm.swallow.content", searchbar_entry);
	return searchbar_layout;
}


char* on_country_name_requested(void *data, Evas_Object *obj, const char *part)
{
	if (!strcmp(part, "elm.text") && data) {
		static double total_time;
		static int count;
		double stime;
		double etime;
		char *str;

		stime = ecore_time_get();

		str = strdup(data);

		etime = ecore_time_get();
		total_time += etime - stime;
		count++;

		int x, y, w, h;
		evas_object_geometry_get(obj, &x, &y, &w, &h);

		dlog_print(DLOG_DEBUG, LOG_TAG, "Did I call even though I'm not in the screen? %s (%lf) (%dx%d)", data, total_time / count, w, h);
		return str;
	}

	return NULL;
}

static void on_country_item_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Eina_List *country_name_list;
	Eina_List *country_code_list;
	Evas_Object *popup;
	Evas_Object *btn;
	appdata_s* ad;

	elm_genlist_item_selected_set(event_info, EINA_FALSE);

	ad = evas_object_data_get(obj, "app_data");
	country_name_list = evas_object_data_del(obj, "country_name_list");
	country_code_list = evas_object_data_del(obj, "country_code_list");

	elm_naviframe_item_pop(ad->nf);

	ad->current_app_state = TG_REGISTRATION_STATE;
	ad->selected_country_id = (int)data;

	country_name_selected_cb(ad, country_name_list, country_code_list);


	if (country_name_list != ad->country_names_list) {
		eina_list_free(country_name_list);
	}

	if (country_code_list != ad->country_codes_list) {
		eina_list_free(country_code_list);
	}
}

void append_country_item(Evas_Object *genlist, appdata_s *ad, Eina_List* country_name_list, Eina_List* country_code_list)
{

	if (!genlist || !ad || !country_name_list || !country_code_list) {
		return;
	}

	int i;
	Eina_List *l;
	const char *country_name;
	static Elm_Genlist_Item_Class itc;
	Elm_Object_Item* item = NULL;

	itc.item_style = "default_style";
	itc.func.text_get = on_country_name_requested;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	l = evas_object_data_del(genlist, "country_name_list");
	if (l != ad->country_names_list) {
		eina_list_free(l);
	}

	l = evas_object_data_del(genlist, "country_code_list");
	if (l != ad->country_codes_list) {
		eina_list_free(l);
	}

	evas_object_data_set(genlist, "country_name_list", country_name_list);
	evas_object_data_set(genlist, "country_code_list", country_code_list);

	i = 0;

	EINA_LIST_FOREACH(country_name_list, l, country_name) {
		item = elm_genlist_item_append(genlist, &itc, country_name, NULL, ELM_GENLIST_ITEM_NONE, on_country_item_clicked, (void *)i);
		i++;
	}
}

static Evas_Object* create_country_genlist(appdata_s *ad, Evas_Object *layout)
{
	Evas_Object *list = elm_genlist_add(ad->nf);
	elm_genlist_homogeneous_set(list, EINA_TRUE);
	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(list);
	elm_object_focus_set(list, EINA_TRUE);
	return list;
}


void launch_country_selection_view(appdata_s *ad)
{
	if (!ad) {
		return;
	}

	ad->current_app_state = TG_COUNTRY_SELECTION_VIEW;

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_theme_set(layout, "layout", "application", "searchbar_base");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);

	Evas_Object* searchbar_layout = create_country_search_bar(layout, ad);
	elm_object_part_content_set(layout, "searchbar", searchbar_layout);

	Evas_Object* fs_layout = elm_layout_add(layout);
	elm_layout_theme_set(fs_layout, "layout", "application", "default");
	elm_object_part_content_set(layout, "elm.swallow.content", fs_layout);

	Evas_Object* peer_list = create_country_genlist(ad, fs_layout);
	evas_object_data_set(peer_list, "app_data", ad);
	elm_object_part_content_set(fs_layout, "elm.swallow.content", peer_list);
	evas_object_data_set(ad->nf, "search_list", peer_list);

	append_country_item(peer_list, ad, ad->country_names_list, ad->country_codes_list);


	elm_naviframe_item_push(ad->nf, "Countires", NULL, NULL, layout, NULL);
}




