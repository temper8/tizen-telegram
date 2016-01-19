/*
 * tg_search_peer_view.c
 *
 *  Created on: Sep 18, 2015
 *      Author: sandeep
 */

#include "tg_search_peer_view.h"
#include "tg_db_wrapper.h"
#include "tg_messaging_view.h"
#include "contact_selection_view.h"
#include "ucol.h"
#include "device_contacts_manager.h"
#include "tg_search_peer_view.h"
#include "server_requests.h"
#include <contacts.h>

#define COMMAND_MENU_ITEM_COUNT 2
#define MOBILE_BUTTON_SIZE (98*1.4f)

typedef struct {
	char* string;
	char* image_path;
	void (*func) (void *data, Evas_Object * obj, void *event_info);
	Elm_Object_Item *item;
} _command_item_info;

static void _append_command_item(Evas_Object *genlist, appdata_s *ad);
static void _append_peer_item(Evas_Object *genlist, appdata_s *ad, Eina_List* item_list);
static void _append_contact_item(Evas_Object *genlist, appdata_s *ad, Eina_List* item_list);
static void on_invite_friends_clicked(void *data, Evas_Object *obj, void *event_info);
static void on_group_chat_clicked(void *data, Evas_Object *obj, void *event_info);
static void on_secret_chat_clicked(void *data, Evas_Object *obj, void *event_info);
extern void _append_group_index(Evas_Object *genlist, char *string);

static _command_item_info contact_screen_command_item_list[COMMAND_MENU_ITEM_COUNT] = {
	{"IDS_TGRAM_MBODY_INVITE_FRIENDS",	TELEGRAM_CONTACT_ADD_ICON, on_invite_friends_clicked, NULL},
	{"IDS_TGRAM_MBODY_GROUP_CHAT",		DEFAULT_LIST_THUMB_MULTI_PIC, on_group_chat_clicked, NULL},
	/*{"secret chat",		"telegram_list_thumb_image_secrete.png", on_secret_chat_clicked, NULL},*/
};


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
	Eina_List *list = evas_object_data_get(obj, "result_list");

	if (!list) {
		list = ad->search_peer_list;
	}

	user_data_with_pic_s *item = eina_list_nth(list, id);
	if (!item) {
		return NULL;
	}

	user_data_s* user = item->use_data;
	if (!user) {
		return NULL;
	}

	if (!strcmp(part,"elm.text.main.left.top") || !strcmp(part,"elm.text")){
		char *full_name = replace(user->print_name, '_', " ");
		return full_name;
	} else if (!strcmp(part, "elm.text.sub.left.bottom") || !strcmp(part,"elm.text.sub")) {
		char* last_seen = get_budy_state(ad, user->user_id.id);
		if (last_seen) {
			return last_seen;
		}
	}
	return NULL;
}

char* _on_command_name_requested(void *data, Evas_Object *obj, const char *part)
{
	int row = (int)data;

	if (!strcmp(part,"elm.text.main.left.top") || !strcmp(part,"elm.text")){
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=45><color=#1776D2>%s</color></font_size></align>", _(contact_screen_command_item_list[row].string));
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

		Evas_Object *profile_pic = NULL;
		profile_pic = create_image_object_from_file(ui_utils_get_resource(contact_screen_command_item_list[row].image_path), obj);
		evas_object_color_set(profile_pic, 45, 165, 224, 255);

		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		Evas_Object *user_pic_layout = elm_layout_add(obj);
		elm_layout_file_set(user_pic_layout, edj_path, "menu_circle_layout");
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
	user_data_with_pic_s *item  = data;
	item->contact_icon = NULL;
}

Evas_Object* on_peer_list_image_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.icon.left") || !strcmp(part, "elm.icon.1") || !strcmp(part, "elm.swallow.icon")  ) {
		int id = (int) data;
		appdata_s* ad = evas_object_data_get(obj, "app_data");
		Eina_List *list = evas_object_data_get(obj, "result_list");
		if (!list) {
			list = ad->search_peer_list;
		}
		int size = eina_list_count(list);
		if (size <= 0) {
			return eo;
		}

		user_data_with_pic_s *item = eina_list_nth(list, id);
		user_data_s *user = item->use_data;
		Evas_Object *profile_pic = NULL;

		if (user->photo_path && strcmp(user->photo_path, "") != 0) {
			profile_pic = create_image_object_from_file(user->photo_path, obj);
		} else {

			profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC), obj);
			evas_object_color_set(profile_pic, 45, 165, 224, 255);
		}

		item->contact_icon = profile_pic;
		evas_object_event_callback_add(item->contact_icon, EVAS_CALLBACK_DEL, on_peer_icon_deleted, item);
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
	return eo;
}

static void clear_search_list(appdata_s *ad)
{
	if (!ad) {
		return;
	}
	for (int i = 0; i < eina_list_count(ad->search_peer_list) ; i++) {
		user_data_with_pic_s *item = eina_list_nth(ad->search_peer_list, i);
		user_data_s* user_data = item->use_data;

		if (user_data->print_name) {
			free(user_data->print_name);
			user_data->print_name = NULL;
		}

		if (user_data->photo_path) {
			free(user_data->photo_path);
			user_data->photo_path = NULL;
		}

		if (user_data->first_name) {
			free(user_data->first_name);
			user_data->first_name = NULL;
		}

		if (user_data->last_name) {
			free(user_data->last_name);
			user_data->last_name = NULL;
		}

		if (user_data->phone) {
			free(user_data->phone);
			user_data->phone = NULL;
		}
		if (user_data->real_first_name) {
			free(user_data->real_first_name);
			user_data->real_first_name = NULL;
		}

		if (user_data->real_last_name) {
			free(user_data->real_last_name);
			user_data->real_last_name = NULL;
		}

		if (user_data->username) {
			free(user_data->username);
			user_data->username = NULL;
		}
		free(user_data);
		free(item);
	}

	eina_list_free(ad->search_peer_list);
	ad->search_peer_list = NULL;

}



void on_new_contact_creation_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		appdata_s* ad = user_data;
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		int status;
		char* mime_type = NULL;
		status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);
		if (status != APP_CONTROL_ERROR_NONE) {
			status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_PATH, &path_arryay,  &array_length);
			if (status != APP_CONTROL_ERROR_NONE) {
				if (ad) {
					show_toast(ad, "Unable to get the result from attach panel");
				}
				return;
			}
		}

		status = app_control_get_mime(reply, &mime_type);
		if (status != APP_CONTROL_ERROR_NONE) {
			if (ad) {
				show_toast(ad, "Unable to get the mime type from attach panel");
			}
			return;
		}

		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);
			free(file_path);
		}
	}
}

static void delete_btn_clicked(void *data, Evas_Object *obj, void *event_info)
{
	void **cbdata = (void **)data;
	Elm_Object_Item *item = *cbdata;
	Evas_Object *entry = NULL;
	Evas_Object *layout = NULL;

	layout = elm_object_item_part_content_get(item, "elm.icon.entry");
	entry = elm_object_part_content_get(layout, "elm.swallow.content");

	elm_object_text_set(entry, "");
}

static void list_delete_btn_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *genlist = data;
	Evas_Object *btn = NULL;
	Elm_Object_Item *item = NULL;

	int count = 0;
	int idx = 3;
	count = elm_genlist_items_count(genlist);

	while(idx <= count) {
		item = elm_genlist_nth_item_get(genlist, idx);
		btn = elm_object_item_part_content_get(item, "elm.icon.2");
		if (btn == obj) break;
		idx ++;
	}

	elm_object_item_del(item);
}

static void onFocus(void *data, Evas_Object *obj, void *event_info)
{
	elm_object_signal_emit((Evas_Object*) data, "elm,state,focused", "");
}

static void onUnfocus(void *data, Evas_Object *obj, void *event_info)
{
	elm_object_signal_emit((Evas_Object*) data, "elm,state,unfocused", "");
}

static Evas_Object *_get_content_cb(void *data, Evas_Object *obj, const char *part)
{
	if (0 == strcmp(part, "elm.icon.entry")) {
		Evas_Object *layout = elm_layout_add(obj);
		elm_layout_theme_set(layout, "layout", "editfield", "singleline");

		Evas_Object* phone_entry = elm_entry_add(obj);
		evas_object_size_hint_weight_set(phone_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(phone_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
		elm_entry_input_panel_layout_set(phone_entry, ELM_INPUT_PANEL_LAYOUT_PHONENUMBER);

		elm_object_part_text_set(phone_entry, "elm.guide", i18n_get_text("IDS_TGRAM_BODY_PHONE_NUMBER_ABB"));

		elm_entry_single_line_set(phone_entry, EINA_TRUE);
		elm_entry_scrollable_set (phone_entry, EINA_TRUE);
		elm_object_part_content_set(layout, "elm.swallow.content", phone_entry);
		evas_object_smart_callback_add(phone_entry, "focused", onFocus, layout);
		evas_object_smart_callback_add(phone_entry, "unfocused", onUnfocus, layout);
		evas_object_show(phone_entry);

		appdata_s *ad = evas_object_data_get(obj, "app_data");
		if (ad) {
			if(ad->is_loading_from_msg_view) {
				char temp_name[512] = {'\0'};
				snprintf(temp_name, 512, "%s", get_buddy_phone_num_from_id(ad->peer_in_cahtting_data->use_data->peer_id));
				elm_object_text_set(phone_entry, temp_name);
			}
			evas_object_data_set(ad->nf, "add_contact_phone_number", phone_entry);
		}
		return layout;
	} else if (0 == strcmp(part, "elm.icon.2")) {

		Evas_Object* phone_delete_btn = elm_button_add(obj);
		elm_object_style_set(phone_delete_btn, "icon_expand_delete");
		evas_object_smart_callback_add(phone_delete_btn, "clicked", delete_btn_clicked, data);
		evas_object_show(phone_delete_btn);
		return phone_delete_btn;
	} else if (0 == strcmp(part, "elm.icon.1")) {
	}

	return NULL;
}

static Evas_Object *_get_first_name_content_cb(void *data, Evas_Object *obj, const char *part)
{
	if (0 == strcmp(part, "elm.icon.entry")) {
		Evas_Object *layout = elm_layout_add(obj);
		elm_layout_theme_set(layout, "layout", "editfield", "singleline");

		Evas_Object* phone_entry = elm_entry_add(obj);
		evas_object_size_hint_weight_set(phone_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(phone_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);

		elm_object_part_text_set(phone_entry, "elm.guide", i18n_get_text("IDS_TGRAM_BODY_FIRST_NAME_ABB"));

		elm_entry_single_line_set(phone_entry, EINA_TRUE);
		elm_entry_scrollable_set (phone_entry, EINA_TRUE);
		elm_object_part_content_set(layout, "elm.swallow.content", phone_entry);
		evas_object_smart_callback_add(phone_entry, "focused", onFocus, layout);
		evas_object_smart_callback_add(phone_entry, "unfocused", onUnfocus, layout);
		evas_object_show(phone_entry);

		appdata_s *ad = evas_object_data_get(obj, "app_data");
		if (ad) {
			evas_object_data_set(ad->nf, "add_contact_first_name", phone_entry);
		}

		return layout;

	} else if (0 == strcmp(part, "elm.icon.2")) {
		Evas_Object* phone_delete_btn = elm_button_add(obj);
		elm_object_style_set(phone_delete_btn, "icon_expand_delete");
		evas_object_smart_callback_add(phone_delete_btn, "clicked", delete_btn_clicked, data);
		evas_object_show(phone_delete_btn);
		return phone_delete_btn;
	}
	return NULL;
}

static Evas_Object *_get_second_name_content_cb(void *data, Evas_Object *obj, const char *part)
{
	if (0 == strcmp(part, "elm.icon.entry")) {

		Evas_Object *layout = elm_layout_add(obj);
		elm_layout_theme_set(layout, "layout", "editfield", "singleline");

		Evas_Object* phone_entry = elm_entry_add(obj);
		evas_object_size_hint_weight_set(phone_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(phone_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);

		elm_object_part_text_set(phone_entry, "elm.guide", i18n_get_text("IDS_TGRAM_BODY_LAST_NAME_ABB"));

		elm_entry_single_line_set(phone_entry, EINA_TRUE);
		elm_entry_scrollable_set (phone_entry, EINA_TRUE);
		elm_object_part_content_set(layout, "elm.swallow.content", phone_entry);
		evas_object_smart_callback_add(phone_entry, "focused", onFocus, layout);
		evas_object_smart_callback_add(phone_entry, "unfocused", onUnfocus, layout);
		evas_object_show(phone_entry);

		appdata_s *ad = evas_object_data_get(obj, "app_data");
		if (ad) {
			evas_object_data_set(ad->nf, "add_contact_last_name", phone_entry);
		}

		return layout;

	} else if (0 == strcmp(part, "elm.icon.2")) {
		Evas_Object* phone_delete_btn = elm_button_add(obj);
		elm_object_style_set(phone_delete_btn, "icon_expand_delete");
		evas_object_smart_callback_add(phone_delete_btn, "clicked", delete_btn_clicked, data);
		evas_object_show(phone_delete_btn);
		return phone_delete_btn;
	}
	return NULL;
}

static char *_get_name_text_cb(void *data, Evas_Object *obj, const char *part)
{
	char *buf = NULL;
	if (0 == strcmp(part, "elm.text")) {
		buf = elm_entry_utf8_to_markup(i18n_get_text("IDS_TGRAM_BODY_NAME_ABB"));
		return buf;
	}
	return NULL;
}

static Evas_Object* get_image_from_path(const char* path, Evas_Object* parent)
{
	if (!path || !parent) {
		return NULL;
	}
	Evas_Object *media_image = evas_object_image_filled_add(evas_object_evas_get(parent));
	evas_object_image_file_set(media_image, path, NULL);
	return media_image;
}

static Evas_Object *_get_picture_cb(void *data, Evas_Object *obj, const char *part)
{
	if (0 == strcmp(part, "contents")) {
		char edj_path[PATH_MAX] = {0, };
		Evas_Object *profile_pic = NULL;
		Evas_Object *image_layout = NULL;

		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		image_layout = elm_layout_add(obj);
		elm_layout_file_set(image_layout, edj_path, "contact_image_masking");
		evas_object_size_hint_weight_set(image_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(image_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(image_layout);

		profile_pic = get_image_from_path(ui_utils_get_resource(TG_CALLER_ID_IMAGE), obj);
		evas_object_color_set(profile_pic, 45, 165, 224, 225);

		appdata_s *ad = evas_object_data_get(obj, "app_data");
		if (ad) {
			evas_object_data_set(ad->nf, "add_contact_pic", profile_pic);
		}
		elm_object_part_content_set(image_layout, "image", profile_pic);

		return image_layout;
	}
	return NULL;
}

static void _append_picture_item(Evas_Object *genlist, appdata_s *ad)
{
	Elm_Genlist_Item_Class *itc = NULL;
	Elm_Object_Item *item = NULL;

	itc = elm_genlist_item_class_new();
	itc->item_style = "input.1image";
	itc->func.text_get = NULL;
	itc->func.content_get = _get_picture_cb;
	itc->func.state_get = NULL;
	itc->func.del = NULL;

	item = elm_genlist_item_append(genlist, itc, NULL, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);

	if(itc) elm_genlist_item_class_free(itc);
}

static void del_cb(void *data, Evas_Object *obj)
{
	free(data);
}

static void _append_name_item(Evas_Object *genlist, appdata_s *ad)
{
	Elm_Genlist_Item_Class *itc = NULL;
	Elm_Genlist_Item_Class *ttc = NULL;
	Elm_Object_Item *item = NULL;
	void **item_data;
	void **second_data;

	ttc = elm_genlist_item_class_new();
	ttc->item_style = "input.2icon";
	ttc->func.text_get = _get_name_text_cb;
	ttc->func.content_get = _get_first_name_content_cb;
	ttc->func.state_get = NULL;
	ttc->func.del = del_cb;

	item_data = malloc(sizeof(*item_data));
	second_data = malloc(sizeof(*second_data));

	item = elm_genlist_item_append(genlist, ttc, item_data, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);

	*item_data = item;

	itc = elm_genlist_item_class_new();
	itc->item_style = "input.3icon";
	itc->func.text_get = NULL;
	itc->func.content_get = _get_second_name_content_cb;
	itc->func.state_get = NULL;
	itc->func.del = NULL;

	item = elm_genlist_item_append(genlist, itc, second_data, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);
	*second_data = item;

	if(itc) elm_genlist_item_class_free(itc);
	if(ttc) elm_genlist_item_class_free(ttc);
}

static void _append_phone_item(Evas_Object *genlist, appdata_s *ad)
{
	Elm_Genlist_Item_Class *itc = NULL;
	Elm_Object_Item *item = NULL;
	void **item_data;

	itc = elm_genlist_item_class_new();
	itc->item_style = "input.3icon";
	itc->func.text_get = NULL;
	itc->func.content_get = _get_content_cb;
	itc->func.state_get = NULL;
	itc->func.del = NULL;

	item_data = malloc(sizeof(*item_data));

	item = elm_genlist_item_append(genlist, itc, item_data, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);

	*item_data = item;

	if(itc) elm_genlist_item_class_free(itc);
}

static void _insert_before_phone_item(Evas_Object *genlist, appdata_s *ad)
{
	Elm_Genlist_Item_Class *itc = NULL;
	Elm_Object_Item *item = NULL;
	Elm_Object_Item *before = NULL;

	itc = elm_genlist_item_class_new();
	itc->item_style = "input.3icon";
	itc->func.text_get = NULL;
	itc->func.content_get = _get_content_cb;
	itc->func.state_get = NULL;
	itc->func.del = NULL;

	before = elm_genlist_last_item_get(genlist);

	item = elm_genlist_item_insert_before(genlist, itc, NULL, NULL, before, ELM_GENLIST_ITEM_NONE, NULL, NULL);

	if(itc) elm_genlist_item_class_free(itc);
}

static void phone_btn_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *genlist = data;
	appdata_s *ad = evas_object_data_get(genlist, "app_data");

	_insert_before_phone_item(genlist, ad);
}

static Evas_Object *_get_icon_cb(void *data, Evas_Object *obj, const char *part)
{
	if (0 == strcmp(part, "elm.icon.1")) {
		Evas_Object* mobile_btn = elm_button_add(obj);
		elm_object_style_set(mobile_btn, "transparent");
		evas_object_size_hint_weight_set(mobile_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(mobile_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_min_set(mobile_btn, ELM_SCALE_SIZE(MOBILE_BUTTON_SIZE), ELM_SCALE_SIZE(MOBILE_BUTTON_SIZE));
		evas_object_smart_callback_add(mobile_btn, "clicked", phone_btn_clicked, obj);
		elm_object_translatable_text_set(mobile_btn, "IDS_TGRAM_OPT_MOBILE");
		evas_object_show(mobile_btn);

		return mobile_btn;
	}
	return NULL;
}

static void _append_phone_icon(Evas_Object *genlist, appdata_s *ad)
{
	Elm_Genlist_Item_Class *itc = NULL;
	Elm_Object_Item *item = NULL;

	itc = elm_genlist_item_class_new();
	itc->item_style = "input.1icon";
	itc->func.text_get = NULL;
	itc->func.content_get = _get_icon_cb;
	itc->func.state_get = NULL;
	itc->func.del = NULL;

	item = elm_genlist_item_append(genlist, itc, ad, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);

	if(itc) elm_genlist_item_class_free(itc);
}

static Evas_Object* create_genlist(appdata_s *ad, Evas_Object *layout)
{
	Evas_Object *list = elm_genlist_add(layout);
	elm_genlist_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(list);
	elm_object_focus_set(list, EINA_TRUE);
	return list;
}

Eina_Bool add_contact_to_phone_book(appdata_s *ad)
{
	if (!ad)
		return EINA_FALSE;

	char* phone_num = NULL;
	char* first_name = NULL;
	char* last_name = NULL;
	char* profile_pic_path = NULL;

	Evas_Object *phone_num_entry = evas_object_data_get(ad->nf, "add_contact_phone_number");
	if (phone_num_entry)
		phone_num = elm_entry_markup_to_utf8(elm_object_text_get(phone_num_entry));

	Evas_Object *first_name_entry = evas_object_data_get(ad->nf, "add_contact_first_name");
	if (first_name_entry)
		first_name = elm_entry_markup_to_utf8(elm_object_text_get(first_name_entry));

	Evas_Object *last_name_entry = evas_object_data_get(ad->nf, "add_contact_last_name");
	if (last_name_entry)
		last_name = elm_entry_markup_to_utf8(elm_object_text_get(last_name_entry));

	if ((phone_num && strlen(phone_num) > 0) && (first_name && strlen(first_name) > 0) && (last_name && strlen(last_name) > 0)) {
		int err_code = contacts_connect();


		/*********************************************************************/

		 contacts_query_h query = NULL;
		 contacts_query_create(_contacts_person_contact._uri, &query);

		 contacts_filter_h filter = NULL;
		 contacts_filter_create(_contacts_person_contact._uri, &filter);

		 contacts_filter_add_int(filter, _contacts_person_contact.address_book_id, CONTACTS_MATCH_EQUAL, 0);
		 contacts_query_set_filter(query, filter);

		 contacts_list_h list = NULL;
		 int ret_val = contacts_db_search_records_with_query(query, phone_num, -1, -1, &list);


		 contacts_filter_destroy(filter);
		 contacts_query_destroy(query);

		 contacts_record_h record = NULL;
		 Eina_Bool is_contact_exists = EINA_FALSE;
		 do
		 {
			 contacts_list_get_current_record_p(list, &record);
			 if (NULL == record) {
				 break;
			 }
			 is_contact_exists = EINA_TRUE;
		 } while (CONTACTS_ERROR_NONE == contacts_list_next(list));
		 contacts_list_destroy(list, true); // Destroy child records automatically

		 if (is_contact_exists) {
			 err_code = contacts_disconnect();
			 hide_loading_popup(ad);
			 show_toast(ad, i18n_get_text("IDS_CST_BODY_CONTACT_ALREADY_EXISTS"));
			 return EINA_FALSE;
		 }

		/***********************************************************************/

		contacts_record_h contact = NULL;
		contacts_record_create(_contacts_contact._uri, &contact);

		char dis_name_str[1024] = {0,};
		strcpy(dis_name_str, first_name);
		strcat(dis_name_str, " ");
		strcat(dis_name_str, last_name);

		// add name
		contacts_record_h dis_name = NULL;
		contacts_record_create(_contacts_name._uri, &dis_name);
		contacts_record_set_str(dis_name, _contacts_name.first, dis_name_str);
		contacts_record_add_child_record(contact, _contacts_contact.display_name, dis_name);

		// add name
		contacts_record_h name = NULL;
		contacts_record_create(_contacts_name._uri, &name);
		contacts_record_set_str(name, _contacts_name.first, first_name);
		contacts_record_add_child_record(contact, _contacts_contact.name, name);


		// add name
		contacts_record_h lname = NULL;
		contacts_record_create(_contacts_name._uri, &lname);
		contacts_record_set_str(lname, _contacts_name.last, last_name);
		contacts_record_add_child_record(contact, _contacts_contact.name, lname);

		// add number
		contacts_record_h number = NULL;
		contacts_record_create(_contacts_number._uri, &number);
		contacts_record_set_str(number, _contacts_number.number, phone_num);
		contacts_record_add_child_record(contact, _contacts_contact.number, number);

		// insert to database
		int contact_id = 0;
		int ret = contacts_db_insert_record(contact, &contact_id);

		if (ret == 0) {
			printf(" contact insert success\n");
		} else {
			printf(" contact insert failed\n");
		}

		// destroy record
		contacts_record_destroy(contact, true);
		err_code = contacts_disconnect();
		return EINA_TRUE;
	} else {
		// show message
	}
	return EINA_FALSE;
}
static Eina_Bool on_contacts_reloaded(void *data)
{
	appdata_s *ad = data;
	hide_loading_popup(ad);
	elm_naviframe_item_pop(ad->nf);
	ad->current_app_state = TG_PEER_SEARCH_VIEW_STATE;
	show_floating_button(ad);
	return ECORE_CALLBACK_CANCEL;
}

void on_new_contact_added_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success)
{
	if (is_success) {

		if (ad->is_loading_from_msg_view) {
			show_loading_popup(ad);
			elm_naviframe_item_pop(ad->nf);
			ad->current_app_state = TG_CHAT_MESSAGING_VIEW_STATE;
			elm_naviframe_item_pop(ad->nf);
			load_registered_user_data(ad);
			load_buddy_list_data(ad);
			load_unknown_buddy_list_data(ad);
			load_peer_data(ad);
			load_main_list_data(ad);
			ecore_timer_add(1, on_load_main_view_requested, ad);
		} else {
			// add new buddy to list
			Evas_Object *peer_list = evas_object_data_get(ad->nf, "search_list");
			if (peer_list) {
				elm_genlist_clear(peer_list);
				clear_search_list(ad);
				free_contact_list(ad->contact_list);

				ad->search_peer_list = load_buddy_data_by_name(ad->user_id.id, NULL);
				ad->contact_list = get_contact_list_from_device_db();

				_append_command_item(peer_list, ad);
				if (ad->search_peer_list && eina_list_count(ad->search_peer_list) > 0) {
					_append_group_index(peer_list, i18n_get_text("IDS_TGRAM_HEADER_TELEGRAM"));
					_append_peer_item(peer_list, ad, ad->search_peer_list);
				}
				if (ad->contact_list && eina_list_count(ad->contact_list) > 0) {
					_append_group_index(peer_list, i18n_get_text("IDS_TGRAM_MBODY_INVITE_FRIENDS"));
					_append_contact_item(peer_list, ad, ad->contact_list);
				}
			}
			show_loading_popup(ad);
			ecore_timer_add(5, on_contacts_reloaded, ad);
		}
	} else {
		// show failed message
		Evas_Object *peer_list = evas_object_data_get(ad->nf, "search_list");
		if (peer_list) {
			elm_genlist_clear(peer_list);
			clear_search_list(ad);
			free_contact_list(ad->contact_list);

			ad->search_peer_list = load_buddy_data_by_name(ad->user_id.id, NULL);
			ad->contact_list = get_contact_list_from_device_db();

			_append_command_item(peer_list, ad);
			if (ad->search_peer_list && eina_list_count(ad->search_peer_list) > 0) {
				_append_group_index(peer_list, i18n_get_text("IDS_TGRAM_HEADER_TELEGRAM"));
				_append_peer_item(peer_list, ad, ad->search_peer_list);
			}
			if (ad->contact_list && eina_list_count(ad->contact_list) > 0) {
				_append_group_index(peer_list, i18n_get_text("IDS_TGRAM_MBODY_INVITE_FRIENDS"));
				_append_contact_item(peer_list, ad, ad->contact_list);
			}
		}
		show_loading_popup(ad);
		ecore_timer_add(5, on_contacts_reloaded, ad);
	}
}

static void on_new_contact_done_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	char* phone_num = NULL;
	char* first_name = NULL;
	char* last_name = NULL;
	char* profile_pic_path = NULL;

	Evas_Object *phone_num_entry = evas_object_data_get(ad->nf, "add_contact_phone_number");
	if (phone_num_entry)
		phone_num = elm_entry_markup_to_utf8(elm_object_text_get(phone_num_entry));

	Evas_Object *first_name_entry = evas_object_data_get(ad->nf, "add_contact_first_name");
	if (first_name_entry)
		first_name = elm_entry_markup_to_utf8(elm_object_text_get(first_name_entry));

	Evas_Object *last_name_entry = evas_object_data_get(ad->nf, "add_contact_last_name");
	if (last_name_entry)
		last_name = elm_entry_markup_to_utf8(elm_object_text_get(last_name_entry));

	if ((phone_num && strlen(phone_num) > 0) && (first_name && strlen(first_name) > 0) && (last_name && strlen(last_name) > 0)) {
		if (add_contact_to_phone_book(ad)) {
			show_loading_popup(ad);
			send_add_buddy_request(ad, ad->service_client, -1, first_name, last_name, phone_num);
		}
	} else {
		// show message

		if (!first_name || strlen(first_name) <= 0) {
			show_toast(ad, i18n_get_text("IDS_TGRAM_BODY_ENTER_YOUR_FIRST_AND_LAST_NAME_ABB"));
			return;
		}
		if (!last_name || strlen(last_name) <= 0) {
			show_toast(ad, i18n_get_text("IDS_TGRAM_BODY_ENTER_YOUR_FIRST_AND_LAST_NAME_ABB"));
			return;
		}

		if (!phone_num || strlen(phone_num) <= 0) {
			show_toast(ad, i18n_get_text("IDS_TGRAM_HEADER_ENTER_NUMBER_ABB"));
			return;
		}

	}
}

static void on_new_contact_cancel_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	if (!ad)
		return;
	elm_naviframe_item_pop(ad->nf);
	if (ad->is_loading_from_msg_view) {
		ad->is_loading_from_msg_view = EINA_FALSE;
		ad->current_app_state = TG_CHAT_MESSAGING_VIEW_STATE;
	} else {
		ad->current_app_state = TG_PEER_SEARCH_VIEW_STATE;
		show_floating_button(ad);
	}
}

void on_create_new_contact(appdata_s* ad)
{
	if (!ad)
		return;

	delete_floating_button(ad);
	ad->current_app_state = TG_ADD_CONTACT_STATE;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Elm_Theme *theme = elm_theme_new();
	elm_theme_ref_set(theme, NULL);
	elm_theme_extension_add(theme, edj_path);

	Evas_Object* phone_list = create_genlist(ad, ad->nf);
	elm_genlist_select_mode_set(phone_list, ELM_OBJECT_SELECT_MODE_NONE);
	elm_object_theme_set(phone_list, theme);
	evas_object_data_set(phone_list, "app_data", ad);

	_append_picture_item(phone_list, ad);
	_append_name_item(phone_list, ad);
	_append_phone_item(phone_list, ad);
	//_append_phone_icon(phone_list, ad);

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, i18n_get_text("IDS_TGRAM_HEADER_CREATE_CONTACT_ABB"), NULL, NULL, phone_list, NULL);

	Evas_Object *done_btn = elm_button_add(ad->nf);
	elm_object_style_set(done_btn, "naviframe/title_right");
	elm_object_text_set(done_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_DONE_ABB"));
	evas_object_smart_callback_add(done_btn, "clicked", on_new_contact_done_clicked, ad);

	Evas_Object *cancel_btn = elm_button_add(ad->nf);
	elm_object_style_set(cancel_btn, "naviframe/title_left");
	elm_object_text_set(cancel_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_CANCEL_ABB"));
	evas_object_smart_callback_add(cancel_btn, "clicked", on_new_contact_cancel_clicked, ad);

	elm_object_item_part_content_set(navi_item, "title_right_btn", done_btn);
	elm_object_item_part_content_set(navi_item, "title_left_btn", cancel_btn);

	evas_object_data_set(ad->nf, "name_done_btn", (void*)done_btn);
	//elm_object_disabled_set(done_btn, EINA_TRUE);
}


static void on_invite_friends_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	app_control_h app_control;
	int ret = app_control_create(&app_control);
	if (ret != APP_CONTROL_ERROR_NONE) {
		return;
	}
	app_control_set_operation(app_control, APP_CONTROL_OPERATION_COMPOSE);
	app_control_set_uri(app_control, "sms:");
	//app_control_set_mime(app_control,"text/html");
	char *text = "Invite you to telegram! https://telegram.org/dl";
	app_control_add_extra_data(app_control, APP_CONTROL_DATA_TEXT, text);
	if (app_control_send_launch_request(app_control, NULL, NULL) == APP_CONTROL_ERROR_NONE) {
		// sms view launched
	}
	app_control_destroy(app_control);
}

static void on_group_chat_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	appdata_s* ad = evas_object_data_get(obj, "app_data");

	if (ad && ad->buddy_list && eina_list_count(ad->buddy_list) > 0) {
		delete_floating_button(ad);
		launch_contact_selction_view(ad);
	} else {
		char msg_str[512]={0,};
		int size = 0;
		snprintf(msg_str, sizeof(msg_str) - 1, i18n_get_text("IDS_TGRAM_BODY_PD_PARTICIPANTS"), size);

		char org_msg[1024] = {0,};
		strcpy(org_msg, msg_str);
		strcat(org_msg, ". ");
		strcat(org_msg, i18n_get_text("IDS_TGRAM_MBODY_INVITE_FRIENDS"));
		show_toast(ad, org_msg);
	}
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
	Eina_List *list = evas_object_data_get(obj, "result_list");

	user_data_with_pic_s* sel_item = eina_list_nth(list, item_id);
	ad->buddy_in_cahtting_data = sel_item;

	int peer_id = -1;
	for (int i = 0; i < eina_list_count(ad->peer_list); i++) {
		peer_with_pic_s* pic_item = eina_list_nth(ad->peer_list, i);
		tg_peer_info_s* item = pic_item->use_data;

		if (item->peer_id == sel_item->use_data->user_id.id) {
			ad->peer_in_cahtting_data = pic_item;
			peer_id = i;
			break;
		}
	}

	if (peer_id == -1) {
		ad->peer_in_cahtting_data = NULL;
		ad->buddy_in_cahtting_data = NULL;
		show_toast(ad, "Unable to retrieve buddy details");
		return;
	}

	ad->main_item_in_cahtting_data = NULL;
	for (int i = 0 ; i < eina_list_count(ad->main_list) ; i++) {
		tg_main_list_item_s *item = eina_list_nth(ad->main_list, i);
		if (item->peer_id == sel_item->use_data->user_id.id) {
			ad->main_item_in_cahtting_data = item;
			break;
		}
	}

	ad->buddy_in_cahtting_data = NULL;
	for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
		user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
		if (item->use_data->user_id.id == sel_item->use_data->user_id.id) {
			ad->buddy_in_cahtting_data = item;
			break;
		}
	}

	elm_naviframe_item_pop(ad->nf);
	delete_floating_button(ad);
	launch_messaging_view_cb(ad, peer_id);
}

#if 0
static void _update_index_item(void *data, void *item_data, int id, Eina_List *list)
{
	appdata_s* ad = data;
	user_data_with_pic_s* item = eina_list_nth(list, id);
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

void _append_peer_item(Evas_Object *genlist, appdata_s *ad, Eina_List* item_list)
{
	int i;
	static Elm_Genlist_Item_Class itc;
	Elm_Object_Item* item = NULL;

	itc.item_style = "type1";
	itc.func.text_get = on_peer_list_name_requested;
	itc.func.content_get = on_peer_list_image_requested;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	int count = eina_list_count(item_list);

	evas_object_data_set(genlist, "result_list", item_list);

	if(count > 0) {
		for (i = 0; i < count; i++) {
			item = elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_peer_item_clicked, (void*) i);
		}
	}
}

static char *group_index_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	char buf[1024];
	char *group_text = data;
	if (!group_text) {
		group_text = i18n_get_text("IDS_TGRAM_HEADER_TELEGRAM");
	}

	if (!strcmp("elm.text", part))
	{
		snprintf(buf, sizeof(buf), "%s", group_text);
		return strdup(buf);
	}

	return NULL;
}

void _append_group_index(Evas_Object *genlist, char *string)
{
	static Elm_Genlist_Item_Class itc;
	Elm_Object_Item* item = NULL;

	itc.item_style = "group_index";
	itc.func.text_get = group_index_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	item = elm_genlist_item_append(genlist, &itc, string, NULL, ELM_GENLIST_ITEM_TREE, NULL, NULL);
	elm_genlist_item_expanded_set(item, EINA_TRUE);
}

static void popup_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;
	evas_object_del(popup);
}

static void _ok_popup_clicked(void *data, Evas_Object *obj, void *event_info)
{
	contact_data_s* contact = evas_object_data_get(obj, "contact");
	if (!contact) {
		LOGE("Fail to get the contact info");
		return;
	}

	app_control_h app_control;
	int ret = app_control_create(&app_control);
	if (ret != APP_CONTROL_ERROR_NONE) {
		return;
	}
	app_control_set_operation(app_control, APP_CONTROL_OPERATION_COMPOSE);
	app_control_set_uri(app_control, "sms:");

	char phone_num[512] = {0,};
	strcpy(phone_num, "sms:");
	strcat(phone_num, contact->phone_number);

	app_control_set_uri(app_control, phone_num);
	char *text = "Invite you to telegram! https://telegram.org/dl";
	app_control_add_extra_data(app_control, APP_CONTROL_DATA_TEXT, text);
	if (app_control_send_launch_request(app_control, NULL, NULL) == APP_CONTROL_ERROR_NONE) {
		// sms view launched
	}
	app_control_destroy(app_control);

	popup_btn_clicked_cb(data, NULL, NULL);

	return;
}

static void on_contact_item_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup;
	Evas_Object *btn;

	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	int item_id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	Eina_List *list = evas_object_data_get(obj, "contact_list");
	contact_data_s* contact = eina_list_nth(list, item_id);
	if (!contact) {
		LOGE("Fail to get the contact info");
		return;
	}

	char temp_name[512] = {'\0'};
	snprintf(temp_name, 512, i18n_get_text("IDS_PB_OPT_SEND_MESSAGE_TO_PS"), contact->display_name);

	/* popup */
	popup = elm_popup_add(ad->win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_translatable_text_set(popup, temp_name);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_translatable_text_set(btn, "IDS_TGRAM_MBODY_INVITE_FRIENDS");
	elm_object_part_content_set(popup, "button1", btn);

	evas_object_smart_callback_add(btn, "clicked", _ok_popup_clicked, popup);
	evas_object_data_set(btn, "contact", contact);

	/* cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_translatable_text_set(btn, "IDS_TGRAM_ACBUTTON_CANCEL_ABB");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", popup_btn_clicked_cb, popup);
	evas_object_show(popup);
}

char* on_contact_list_name_requested(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;

	appdata_s* ad = evas_object_data_get(obj, "app_data");
	Eina_List *list = evas_object_data_get(obj, "contact_list");

	if (!list) {
		list = ad->contact_list;
	}

	contact_data_s* contact = eina_list_nth(list, id);
	if (!contact) {
		return NULL;
	}

	if (!strcmp(part,"elm.text.main.left.top") || !strcmp(part,"elm.text")){
		return strdup(contact->display_name);
	} else if (!strcmp(part, "elm.text.sub.left.bottom") || !strcmp(part,"elm.text.sub")) {
		return NULL;
	}
	return NULL;
}


Evas_Object* on_contact_list_image_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.icon.left") || !strcmp(part, "elm.icon.1") || !strcmp(part, "elm.swallow.icon")  ) {
		int id = (int) data;
		appdata_s* ad = evas_object_data_get(obj, "app_data");
		Eina_List *list = evas_object_data_get(obj, "contact_list");
		if (!list) {
			list = ad->contact_list;
		}
		int size = eina_list_count(list);
		if (size <= 0) {
			return eo;
		}
		contact_data_s* contact = eina_list_nth(list, id);
		if (!contact || !contact->pic_url) {
			return NULL;
		}

		Evas_Object *profile_pic = NULL;
		profile_pic = create_image_object_from_file(contact->pic_url, obj);
		evas_object_color_set(profile_pic, 45, 165, 224, 255);

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


void _append_contact_item(Evas_Object *genlist, appdata_s *ad, Eina_List* item_list)
{

	if (!genlist || !ad || !item_list) {
		return;
	}

	int i;
	static Elm_Genlist_Item_Class itc;
	Elm_Object_Item* item = NULL;

	itc.item_style = "type1";
	itc.func.text_get = on_contact_list_name_requested;
	itc.func.content_get = on_contact_list_image_requested;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	int count = eina_list_count(item_list);

	evas_object_data_set(genlist, "contact_list", item_list);

	if(count > 0) {
		for (i = 0; i < count; i++) {
			item = elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_contact_item_clicked, (void*) i);
		}
	}
}

void _append_command_item(Evas_Object *genlist, appdata_s *ad)
{
	int i;
	static Elm_Genlist_Item_Class itc;

	//itc.item_style = "2line.top";
	itc.item_style = "type1";
	itc.func.text_get = _on_command_name_requested;
	itc.func.content_get = _on_command_name_image_requested;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < COMMAND_MENU_ITEM_COUNT; i++) {
		elm_genlist_item_append(genlist, &itc, (void *)i, NULL, ELM_GENLIST_ITEM_NONE, contact_screen_command_item_list[i].func, ad);
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

static void _on_search_entry_changed(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	char* entry_text = NULL;

	Evas_Object *search_list = evas_object_data_get(ad->nf, "search_list");
	Evas_Object *main_layout = evas_object_data_get(ad->nf, "main_layout");
	Evas_Object *index = evas_object_data_get(ad->nf, "fs_index");

	user_data_with_pic_s *tl_item;
	user_data_s* tl_user; // = item->use_data;

	if (!search_list) {
		DBG("search_list is null");
		return;
	}

	elm_genlist_clear(search_list);

	entry_text = trim(elm_entry_markup_to_utf8(elm_object_text_get(obj)));

	Eina_List *tl_result_list = NULL;
	Eina_List *ll = NULL;

	// telegram contacts
	if (ucol_is_jamo(entry_text)) {
		LOGD("entry_text is jamo, %s", entry_text);
		EINA_LIST_FOREACH(ad->search_peer_list, ll, tl_item) {
			int result;
			tl_user = tl_item->use_data;
			result = ucol_compare_first_letters(tl_user->print_name, entry_text);
			if (result == 0) {
				tl_result_list = eina_list_append(tl_result_list, tl_item);
			}
		}
	} else {
		LOGD("entry_text is not jamo, %s", entry_text);
		EINA_LIST_FOREACH(ad->search_peer_list, ll, tl_item) {
			tl_user = tl_item->use_data;

			if (ucol_search(tl_user->print_name, entry_text) != -ENOENT) {
				tl_result_list = eina_list_append(tl_result_list, tl_item);
			}
		}
	}
	Eina_List *contact_result_list = NULL;
	Eina_List *l = NULL;
	contact_data_s* cn_item = NULL;
	//device contacts
	if (ucol_is_jamo(entry_text)) {
		LOGD("entry_text is jamo, %s", entry_text);
		EINA_LIST_FOREACH(ad->contact_list, l, cn_item) {
			int result;
			result = ucol_compare_first_letters(cn_item->display_name, entry_text);
			if (result == 0) {
				contact_result_list = eina_list_append(contact_result_list, cn_item);
			}
		}
	} else {
		LOGD("entry_text is not jamo, %s", entry_text);
		EINA_LIST_FOREACH(ad->contact_list, l, cn_item) {
			if (ucol_search(cn_item->display_name, entry_text) != -ENOENT) {
				contact_result_list = eina_list_append(contact_result_list, cn_item);
			}
		}
	}


	if ((entry_text == NULL || strlen(entry_text) == 0) && tl_result_list == NULL && contact_result_list == NULL) {
		tl_result_list = ad->search_peer_list;
		contact_result_list = ad->contact_list;
		_append_command_item(search_list, ad);
	}

	LOGD("count of result_list is %d", eina_list_count(tl_result_list));

	if (!(entry_text == NULL || strlen(entry_text) == 0) && !tl_result_list && !contact_result_list) {
		Evas_Object *no_contents = evas_object_data_get(ad->nf, "no_contents_layout");
		elm_object_part_content_unset(main_layout, "elm.swallow.content");
		elm_object_part_content_set(main_layout, "elm.swallow.content", no_contents);
	} else {
		Evas_Object *fs_layout = evas_object_data_get(ad->nf, "fs_layout");
		if (tl_result_list && eina_list_count(tl_result_list) > 0) {
			_append_group_index(search_list, i18n_get_text("IDS_TGRAM_HEADER_TELEGRAM"));
			_append_peer_item(search_list, data, tl_result_list);
		}
		Evas_Object *content = elm_object_part_content_unset(main_layout, "elm.swallow.content");
		if (evas_object_data_get(ad->nf, "no_contents_layout") == content) {
			evas_object_hide(content);
		}
		elm_object_part_content_set(main_layout, "elm.swallow.content", fs_layout);

		if (contact_result_list && eina_list_count(contact_result_list) > 0) {
			_append_group_index(search_list, i18n_get_text("IDS_TGRAM_MBODY_INVITE_FRIENDS"));
			_append_contact_item(search_list, ad, contact_result_list);
		}
	}

	elm_index_level_go(index, 0);
	elm_genlist_realized_items_update(search_list);
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
	evas_object_smart_callback_add(searchbar_entry, "preedit,changed", _on_search_entry_changed, data);
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
	appdata_s* ad = data;
	Evas_Object *search_list = evas_object_data_get(ad->nf, "search_list");
	//Elm_Object_Item *gl_item = elm_genlist_first_item_get(search_list);

	user_data_with_pic_s* gl_item = NULL;//eina_list_nth(ad->search_peer_list, 0);

	//tg_peer_info_s* user = item->use_data;
	Eina_List* list = ad->search_peer_list;
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

	if (list == ad->search_peer_list) {
		index += 2;
	}

	Elm_Object_Item *item = elm_genlist_nth_item_get(search_list, index);
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

void launch_start_peer_search_view(appdata_s* ad)
{
	if (!ad)
		return;

	ad->current_app_state = TG_PEER_SEARCH_VIEW_STATE;

	clear_search_list(ad);

	free_contact_list(ad->contact_list);

	ad->search_peer_list = load_buddy_data_by_name(ad->user_id.id, NULL);
	ad->contact_list = get_contact_list_from_device_db();

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_theme_set(layout, "layout", "application", "searchbar_base");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);

	Evas_Object* searchbar_layout = _create_searchbar(layout, ad);
	elm_object_part_content_set(layout, "searchbar", searchbar_layout);

	Evas_Object* fs_layout = elm_layout_add(layout);
	//elm_layout_theme_set(fs_layout, "layout", "application", "fastscroll");
	elm_layout_theme_set(fs_layout, "layout", "application", "default");
	elm_object_part_content_set(layout, "elm.swallow.content", fs_layout);

#if 0
	Evas_Object* index = create_fastscroll(ad);
	elm_object_part_content_set(fs_layout, "elm.swallow.fastscroll", index);
#endif

	Evas_Object* peer_list = create_genlist(ad, fs_layout);
	evas_object_data_set(peer_list, "app_data", ad);
	elm_object_part_content_set(fs_layout, "elm.swallow.content", peer_list);

	_append_command_item(peer_list, ad);
	if (ad->search_peer_list && eina_list_count(ad->search_peer_list) > 0) {
		_append_group_index(peer_list, i18n_get_text("IDS_TGRAM_HEADER_TELEGRAM"));
		_append_peer_item(peer_list, ad, ad->search_peer_list);
	}

	if (ad->contact_list && eina_list_count(ad->contact_list) > 0) {
		_append_group_index(peer_list, i18n_get_text("IDS_TGRAM_MBODY_INVITE_FRIENDS"));
		_append_contact_item(peer_list, ad, ad->contact_list);
	}

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
	evas_object_data_set(ad->nf, "search_list", peer_list);

	elm_naviframe_item_push(ad->nf, i18n_get_text("IDS_TGRAM_HEADER_CONTACTS_ABB"), NULL, NULL, layout, NULL);

}
