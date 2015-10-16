/*
 * tg_search_peer_view.c
 *
 *  Created on: Sep 18, 2015
 *      Author: sandeep
 */

#include "tg_search_peer_view.h"
#include "tg_db_wrapper.h"
#include "tg_messaging_view.h"

#define COMMAND_MENU_ITEM_COUNT 2

typedef struct {
	char* string;
	char* image_path;
	void (*func) (void *data, Evas_Object * obj, void *event_info);
	Elm_Object_Item *item;
} _command_item_info;


static void on_invite_friends_clicked(void *data, Evas_Object *obj, void *event_info);
static void on_group_chat_clicked(void *data, Evas_Object *obj, void *event_info);
static void on_secret_chat_clicked(void *data, Evas_Object *obj, void *event_info);

static _command_item_info contact_screen_command_item_list[COMMAND_MENU_ITEM_COUNT] = {
	{"invites friends",	"telegram_list_thumb_image_add.png",  	on_invite_friends_clicked, NULL},
	{"group chat",		"telegram_list_thumb_image_multi.png", on_group_chat_clicked, NULL},
	/*{"secret chat",		"telegram_list_thumb_image_secrete.png", on_secret_chat_clicked, NULL},*/
};


char* _util_get_first_char(char *input_text)


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

	peer_with_pic_s* item = eina_list_nth(ad->search_peer_list, id);
	if(!item) {
		return NULL;
	}
	tg_peer_info_s* user = item->use_data;

	if (!strcmp(part,"elm.text.main.left.top") || !strcmp(part,"elm.text")){
		return strdup(user->print_name);
	} else if (!strcmp(part, "elm.text.sub.left.bottom") || !strcmp(part,"elm.text.sub")) {
		if (user->peer_type == TGL_PEER_USER) {
			char* last_seen = get_budy_state(ad, user->peer_id);
			if (last_seen) {
				return last_seen;
			}
		}
	}

	return NULL;
}

char* _on_command_name_requested(void *data, Evas_Object *obj, const char *part)
{
	int row = (int)data;

	if (!strcmp(part,"elm.text.main.left.top") || !strcmp(part,"elm.text")){
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=45><color=#1776D2>%s</color></font_size></align>", contact_screen_command_item_list[row].string);
		return strdup(buf);
	}

	return NULL;
}

Evas_Object* _on_command_name_image_requested(void *data, Evas_Object *obj, const char *part)
{
	int row = (int)data;

	Evas_Object *eo = NULL;
	char path[256] = {0,};

	if (!strcmp(part, "elm.icon.left") || !strcmp(part, "elm.icon.1") || !strcmp(part, "elm.swallow.icon")  ) {

		sprintf(path, "%s%s", FM_ICON_PATH, contact_screen_command_item_list[row].image_path);

		Evas_Object *profile_pic = create_image_object_from_file(ui_utils_get_resource(path), obj);
		evas_object_color_set(profile_pic, 155, 216, 226, 255);

		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

		Evas_Object* user_pic_layout = elm_layout_add(obj);
		elm_layout_file_set(user_pic_layout, edj_path, "circle_layout");
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


void on_peer_icon_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	peer_with_pic_s *item  = data;
	item->contact_icon = NULL;
}

Evas_Object* on_peer_list_image_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.icon.left") || !strcmp(part, "elm.icon.1") || !strcmp(part, "elm.swallow.icon")  ) {

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
		elm_layout_theme_set(eo, "layout", "list/B/type.2", "default");
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

static void on_invite_friends_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	show_toast(data, "on_invite_friends_clicked");
}

static void on_group_chat_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	show_toast(data, "on_group_chat_clicked");
}

static void on_secret_chat_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	show_toast(data, "on_secret_chat_clicked");
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

static void _update_index_item(void *data, void *item_data, int id)
{
	appdata_s* ad = data;
	peer_with_pic_s* item = eina_list_nth(ad->search_peer_list, id);
	tg_peer_info_s* user = item->use_data;

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

static void _append_peer_item(Evas_Object *genlist, appdata_s *ad, Eina_List* item_list)
{
	int i;
	static Elm_Genlist_Item_Class itc;
	Elm_Object_Item* item = NULL;

	//itc.item_style = "2line.top";
	itc.item_style = "type1";
	itc.func.text_get = on_peer_list_name_requested;
	itc.func.content_get = on_peer_list_image_requested;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	int count = eina_list_count(item_list);

	if(count > 0) {
		for (i = 0; i < count; i++) {
			item = elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_peer_item_clicked, (void*) i);
			_update_index_item(ad, item, i);
		}
	} else {
		i = 1;
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
	}
}

static void _append_command_item(Evas_Object *genlist, appdata_s *ad)
{
	int i;
	static Elm_Genlist_Item_Class itc;
	Elm_Object_Item* item = NULL;

	//itc.item_style = "2line.top";
	itc.item_style = "type1";
	itc.func.text_get = _on_command_name_requested;
	itc.func.content_get = _on_command_name_image_requested;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < COMMAND_MENU_ITEM_COUNT; i++) {
		elm_genlist_item_append(genlist, &itc, i, NULL, ELM_GENLIST_ITEM_NONE, contact_screen_command_item_list[i].func, ad);
	}


}

static void _append_index_item(Evas_Object *genlist, appdata_s *ad)
{
	int i;
	static Elm_Genlist_Item_Class itc;
	Elm_Object_Item* item = NULL;

	//itc.item_style = "2line.top";
	itc.item_style = "type1";
	itc.func.text_get = on_peer_list_name_requested;
	itc.func.content_get = on_peer_list_image_requested;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	int count = eina_list_count(ad->search_peer_list);

	if(count > 0) {
		for (i = 0; i < count; i++) {
			item = elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_peer_item_clicked, (void*) i);
			_update_index_item(ad, item, i);
		}
	} else {
		i = 1;
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
	}
}


void _group_index_selected_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
	Elm_Object_Item *it = (Elm_Object_Item*)event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	Evas_Object *check = elm_object_item_part_content_get(it, "elm.swallow.end");
	if (!check) {
		check = elm_object_item_part_content_get(it, "elm.icon.right");
	}

	if (check) {
		elm_check_state_set(check, !elm_check_state_get(check));
		evas_object_smart_callback_call(check, "changed", NULL);
	}
}

/*
char* _group_index_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	char *text = (char*)data;

	if (!strcmp(part, "elm.text.main")) {
		return strdup(text);
	}
}

void _append_gl_group_index(Evas_Object *genlist, char* text) {
	static Elm_Genlist_Item_Class itc;
	ret_if(!itc);

	itc.item_style = "groupindex";
	itc.func.text_get = _group_index_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.del = gl_del_cb;

	elm_genlist_item_append(genlist, &itc, strdup(text), NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);
}*/





static void _on_search_entry_changed(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	char* entry_text = NULL;

	Evas_Object *search_list = evas_object_data_get(ad->nf, "search_list");
	Evas_Object *main_layout = evas_object_data_get(ad->nf, "main_layout");
	Evas_Object *index = evas_object_data_get(ad->nf, "fs_index");

	if (!search_list) {
		DBG("search_list is null");
		return;
	}

	elm_genlist_clear(search_list);
	clear_search_list(ad);
	elm_index_item_clear(index);

	entry_text = trim(elm_object_text_get(obj));

	if (strlen(entry_text) > 0) {
		ad->search_peer_list = load_peer_data_by_name(entry_text);
	} else {
		ad->search_peer_list = load_peer_data_by_name(NULL);
	}

	if (ad->search_peer_list) {
		Evas_Object *fs_layout = evas_object_data_get(ad->nf, "fs_layout");
		_append_peer_item(search_list, data, ad->search_peer_list);
		elm_object_part_content_unset(main_layout, "elm.swallow.content");
		elm_object_part_content_set(main_layout, "elm.swallow.content", fs_layout);
	} else {
		Evas_Object *no_contents = evas_object_data_get(ad->nf, "no_contents_layout");

		elm_object_part_content_unset(main_layout, "elm.swallow.content");
		elm_object_part_content_set(main_layout, "elm.swallow.content", no_contents);
	}

	elm_index_level_go(index, 0);

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


Evas_Object *_create_searchbar(Evas_Object* parent, void* data)
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
	elm_entry_scrollable_set (searchbar_entry, EINA_FALSE);
	elm_entry_cnp_mode_set(searchbar_entry, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(searchbar_entry, EINA_TRUE);
	elm_object_part_text_set(searchbar_entry, "elm.guide", i18n_get_text("IDS_TGRAM_NPBODY_SEARCH"));
	elm_object_focus_set(searchbar_entry, EINA_FALSE);
	//elm_object_tree_focus_allow_set(searchbar_entry, EINA_FALSE);
	//evas_object_event_callback_add(searchbar_entry, EVAS_CALLBACK_DEL, _searchbar_entry_del_cb, NULL);

	limit_filter_data.max_char_count = 255;
	elm_entry_markup_filter_append(searchbar_entry, elm_entry_filter_limit_size, &limit_filter_data);


	evas_object_smart_callback_add(searchbar_entry, "changed", _on_search_entry_changed, data);
	evas_object_smart_callback_add(searchbar_entry, "focused", _on_search_entry_focused, searchbar_layout);
	/*
	evas_object_smart_callback_add(ad->searchbar_entry, "maxlength,reached", _searchbar_entry_max_length_reached_cb, data);
	evas_object_smart_callback_add(ad->searchbar_entry,	"preedit,changed", _searchbar_entry_preedit_changed_cb, data);
	evas_object_smart_callback_add(ad->searchbar_entry, "language,changed",	_searchbar_entry_lang_changed, data);
	 */

	elm_object_part_content_set(searchbar_layout, "elm.swallow.content", searchbar_entry);
	return searchbar_layout;
}

static void _index_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
#if 0
	appdata_s* ad = data;
	Evas_Object *search_list = evas_object_data_get(ad->nf, "search_list");
	//Elm_Object_Item *gl_item = elm_genlist_first_item_get(search_list);

	peer_with_pic_s* gl_item = NULL;//eina_list_nth(ad->search_peer_list, 0);

	//tg_peer_info_s* user = item->use_data;
	Eina_List* list = ad->search_peer_list;

	while (list) {
		//const char *part_text = elm_object_item_part_text_get(gl_item, "elm.text");

		//const char *part_text = elm_object_item_data_get(gl_item);
		gl_item = eina_list_data_get(list);
		char *part_text = gl_item->use_data->print_name;
		int id = gl_item->use_data->peer_id;
		const char *index_letter = elm_index_item_letter_get(event_info);

		int unicode_len = eina_unicode_utf8_get_len(part_text);
		int str_len = strlen(part_text);
		int lang_byte = str_len/unicode_len+(str_len%unicode_len > 0 ? 1: 0);
		char *compare_text = strndup(part_text, lang_byte);

		Elm_Object_Item *item = elm_genlist_nth_item_get(search_list, id);

		if (!strcmp(index_letter, compare_text)) {
			elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
			break;
		}

		//gl_item = elm_genlist_item_next_get(gl_item);
		list = eina_list_next(list);

	}

#endif
	elm_genlist_item_show(elm_object_item_data_get(event_info), ELM_GENLIST_ITEM_SCROLLTO_TOP);
	elm_index_item_selected_set(event_info, EINA_FALSE);
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

#if 1
	/* 2. Local language */
	str = dgettext("efl-extension", "IDS_EA_BODY_ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	len = strlen(str);

	while (i < len) {
		j = i;
		eina_unicode_utf8_next_get(str, &i);
		snprintf(buf, i - j + 1, "%s", str + j);
		buf[i - j + 1] = 0;

		elm_index_item_append(index, buf, NULL, NULL);
	}
#endif
	elm_index_level_go(index, 0);

	evas_object_smart_callback_add(index, "selected", _index_selected_cb, ad);
	//evas_object_smart_callback_add(index, "changed", _index_changed_cb, NULL);
	//evas_object_smart_callback_add(index, "language,changed", _index_language_changed_cb, NULL);

	return index;
}


static Evas_Object* create_genlist(appdata_s *ad, Evas_Object *layout)
{
	Evas_Object *list = elm_genlist_add(ad->nf);

	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(list, ELM_LIST_COMPRESS);

	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_data_set(list, "app_data", ad);
	elm_object_part_content_set(layout, "elm.swallow.content", list);
	evas_object_show(list);
	elm_object_focus_set(list, EINA_TRUE);

	return list;
}


void launch_start_peer_search_view(appdata_s* ad)
{
	if (!ad)
		return;

	ad->current_app_state = TG_PEER_SEARCH_VIEW_STATE;

	clear_search_list(ad);
	ad->search_peer_list = load_peer_data_by_name(NULL);

	/* main layout */
	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_theme_set(layout, "layout", "application", "searchbar_base");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	evas_object_data_set(ad->nf, "main_layout", layout);

	/* search field */
	Evas_Object* searchbar_layout = _create_searchbar(layout, ad);
	elm_object_part_content_set(layout, "searchbar", searchbar_layout);

	/* fastscroll layout */
	Evas_Object* fs_layout = elm_layout_add(layout);
	elm_layout_theme_set(fs_layout, "layout", "application", "fastscroll");
	elm_object_part_content_set(layout, "elm.swallow.content", fs_layout);
	evas_object_data_set(ad->nf, "fs_layout", fs_layout);

	/* fastscroll */
	Evas_Object* index = create_fastscroll(ad);
	elm_object_part_content_set(fs_layout, "elm.swallow.fastscroll", index);
	evas_object_data_set(ad->nf, "fs_index", index);

	/* peer list - Genlist */
	Evas_Object* peer_list = create_genlist(ad, fs_layout);

	_append_command_item(peer_list, ad);
	_append_peer_item(peer_list, ad, ad->search_peer_list);
	evas_object_data_set(ad->nf, "search_list", peer_list);

	/* no contents */
	Evas_Object *nocontents = elm_layout_add(ad->nf);
	elm_layout_theme_set(nocontents, "layout", "nocontents", "default");
	evas_object_size_hint_weight_set(nocontents, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(nocontents, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_text_set(nocontents, "elm.text", "No Items");
	evas_object_data_set(ad->nf, "no_contents_layout", nocontents);

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "Telegram", NULL, NULL, layout, NULL);
	elm_naviframe_prev_btn_auto_pushed_set(ad->nf, EINA_FALSE);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_BACK, eext_naviframe_back_cb, NULL);


	//elm_naviframe_item_simple_push(ad->nf, scroller);
	//elm_naviframe_item_simple_push(ad->nf, layout);
}
