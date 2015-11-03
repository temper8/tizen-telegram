/*
 * tg_select_buddy_from_list.c
 *
 *  Created on: Oct 3, 2015
 *      Author: sandeep
 */

#include "tg_select_buddy_from_list.h"
#include "tg_db_wrapper.h"
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

char* on_buddy_select_list_name_requested(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;

	appdata_s* ad = evas_object_data_get(obj, "app_data");

	int size = eina_list_count(ad->buddy_list);

	if (size <= 0) {
		if (!strcmp(part,"elm.text")){
			char buf[512] = {'\0'};
			snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", "No Items");
			return strdup(buf);

		} else if (!strcmp(part, "elm.text.sub")) {
			return NULL;
		}
	}

	user_data_with_pic_s* item = eina_list_nth(ad->buddy_list, id);
	user_data_s* user = item->use_data;

	if (!strcmp(part,"elm.text")){
		char* user_name = replace(user->print_name, '_', " ");
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", user_name);
		free(user_name);
		return strdup(buf);

	} else if (!strcmp(part, "elm.text.sub")) {
		char* last_seen = get_budy_state(ad, user->user_id.id);
		if (last_seen) {
			return last_seen;
		}
	}

	return NULL;
}

void on_buddy_selected_icon_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	user_data_with_pic_s *item  = data;
	item->contact_icon = NULL;
}

Evas_Object* on_buddy_select_list_image_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.swallow.icon")) {

		int id = (int) data;
		appdata_s* ad = evas_object_data_get(obj, "app_data");
		int size = eina_list_count(ad->buddy_list);
		if (size <= 0) {
			return eo;
		}
		user_data_with_pic_s* item = eina_list_nth(ad->buddy_list, id);
		user_data_s* user = item->use_data;
		Evas_Object *profile_pic = NULL;
		if (user->photo_path && strcmp(user->photo_path, "") != 0) {
			profile_pic = create_image_object_from_file(user->photo_path, obj);
		} else {
			profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_PROFILE_PIC), obj);
		}

		item->contact_icon = profile_pic;
		evas_object_event_callback_add(item->contact_icon, EVAS_CALLBACK_DEL, on_buddy_selected_icon_deleted, item);

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


static void on_buddy_sel_menu_canceled(void *data, Evas_Object *obj, void *event_info)
{
	//appdata_s *ad = evas_object_data_get(obj, "app_data");
	Evas_Object *popup = evas_object_data_get(obj, "popup");
	evas_object_del(popup);
}

static void on_buddy_add_to_chat_ok_selected(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = evas_object_data_get(obj, "app_data");
	Evas_Object *popup = evas_object_data_get(obj, "popup");

	if (ad->peer_in_cahtting_data && ad->peer_in_cahtting_data->use_data) {
		show_loading_popup(ad);
		send_add_buddy_to_group_chat_request(ad, ad->service_client, ad->selected_buddy_item->user_id.id, ad->peer_in_cahtting_data->use_data->peer_id);
		elm_naviframe_item_pop(ad->nf);
		ad->current_app_state = TG_SET_CHAT_INFO_STATE;
	}

	evas_object_del(popup);
}

static void on_new_buddy_to_chat_selected_cb(appdata_s *ad)
{

	if (!ad->selected_buddy_item) {
		return;
	}

	Evas_Object *popup, *btn;

	/* popup */
	popup = elm_popup_add(ad->nf);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	char* user_name = replace(ad->selected_buddy_item->print_name, '_', " ");
	char *msg_data = (char*)malloc(strlen("Add ") + strlen(user_name) + strlen(" to the group?") + 1);
	strcpy(msg_data, "Add ");
	strcat(msg_data, user_name);
	strcat(msg_data, " to the group?");
	elm_object_text_set(popup, msg_data);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "OK");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", on_buddy_add_to_chat_ok_selected, ad);
	evas_object_data_set(btn, "app_data", ad);
	evas_object_data_set(btn, "popup", popup);

	/* cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", on_buddy_sel_menu_canceled, ad);
	evas_object_data_set(btn, "app_data", ad);
	evas_object_data_set(btn, "popup", popup);

	evas_object_show(popup);

	free(user_name);
	free(msg_data);
}

static void on_buddy_item_selected(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	int item_id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");

	user_data_with_pic_s* sel_item = eina_list_nth(ad->buddy_list, item_id);
	if (!sel_item) {
		show_toast(ad, "Failed to add user to chat");
		elm_naviframe_item_pop(ad->nf);
		ad->current_app_state = TG_SET_CHAT_INFO_STATE;
		return;
	}

	int chat_id = ad->peer_in_cahtting_data->use_data->peer_id;

	tg_chat_info_s* chat_info = get_chat_info(chat_id);

	if (!chat_info) {
		show_toast(ad, "Failed to add user to chat");
		elm_naviframe_item_pop(ad->nf);
		ad->current_app_state = TG_SET_CHAT_INFO_STATE;
		return;
	}


	int user_list_size = chat_info->user_list_size;
	int online_members = 0;

	Eina_Bool is_already_present = EINA_FALSE;
	for (int i = 0; i < user_list_size; i++) {
		int chat_buddy_id = chat_info->chat_users[i];
		if (sel_item->use_data->user_id.id == chat_buddy_id) {
			is_already_present = EINA_TRUE;
		}
	}

	if(chat_info->print_title) {
		free(chat_info->print_title);
		chat_info->print_title = NULL;
	}
	if(chat_info->photo_path) {
		free(chat_info->photo_path);
		chat_info->photo_path = NULL;
	}
	if(chat_info->title) {
		free(chat_info->title);
		chat_info->title = NULL;
	}

	if (is_already_present) {
		show_toast(ad, "User already present in the chat.");
	} else {
		ad->selected_buddy_item = sel_item->use_data;
		on_new_buddy_to_chat_selected_cb(ad);
		/*elm_naviframe_item_pop(ad->nf);
		ad->current_app_state = TG_SET_CHAT_INFO_STATE;*/
		return;
	}

}



void launch_select_buddy_view(appdata_s* ad)
{
	if (!ad)
		return;

	ad->current_app_state = TG_SELECT_BUDDY_VIEW;


	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);


	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	int i;
	static Elm_Genlist_Item_Class itc1;
	Evas_Object *buddy_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(buddy_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(buddy_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(buddy_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(buddy_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_data_set(buddy_list, "app_data", ad);

	itc1.item_style = "double_label";
	itc1.func.text_get = on_buddy_select_list_name_requested;
	itc1.func.content_get = on_buddy_select_list_image_requested;
	itc1.func.state_get = NULL;
	itc1.func.del = NULL;

	int size = 0;
	if (ad->buddy_list) {
		size = eina_list_count(ad->buddy_list);
	}

	if(size > 0) {
		for (i = 0; i < size; i++) {
			elm_genlist_item_append(buddy_list, &itc1, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_buddy_item_selected, (void*) i);
		}
	} else {
		i = 1;
		elm_genlist_item_append(buddy_list, &itc1, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
	}
	evas_object_show(buddy_list);
	elm_object_content_set(scroller, buddy_list);

	/***************** contacts list *************************/

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "<font=Tizen:style=Regular color=#ffffff align=left><font_size=40>Select Buddy</font_size></font>", NULL, NULL, scroller, NULL);

}


