/*
 * tg_add_contact.c
 *
 *  Created on: Oct 10, 2015
 *      Author: sandeep
 */

#include "tg_add_contact.h"
#include "tg_db_wrapper.h"
#include "server_requests.h"

#define NEW_NAME_INFO_TEXT "Set up contact's first and last name"

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


static void on_contact_name_entry_done_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object* first_name_entry = evas_object_data_get(ad->nf, "new_contact_first_name_entry");
	Evas_Object* last_name_entry = evas_object_data_get(ad->nf, "new_contact_second_name_entry");
	const char* tfirst_name = elm_object_text_get(first_name_entry);
	if (!tfirst_name) {
		show_toast(ad, "Enter first name");
		return;
	}
	const char* tlast_name = elm_object_text_get(last_name_entry);
	if (!tlast_name) {
		tlast_name = "";
	}
	char* first_name = trim((char*)tfirst_name);
	char* last_name = trim((char*)tlast_name);

	// To-Do
	if (!first_name || strlen(first_name) <= 0) {
		show_toast(ad, "Invalid first name");
	}

	if (!last_name || strlen(last_name) <= 0) {
		show_toast(ad, "Invalid last name");
	}

	char* phone_num = get_buddy_phone_num_from_id(ad->peer_in_cahtting_data->use_data->peer_id);

	send_add_buddy_request(ad, ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id, first_name, last_name, phone_num);


	free(first_name);
	free(last_name);

	elm_naviframe_item_pop(ad->nf);
	show_loading_popup(ad);
	ad->current_app_state = TG_SET_USER_INFO_STATE;
}

Evas_Object* on_new_buddy_info_requested(void *data, Evas_Object *obj, const char *part)
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
		sprintf(status_buf, "<font=Tizen:style=Normal color=#FFFFFF align=left><font_size=35>%s</font_size></font>", online_status);

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


static void on_contact_name_change_enable_ok_button(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object* done_btn = evas_object_data_get(ad->nf, "name_done_btn");
	char buf[256] = {'\0',};
	snprintf(buf, sizeof(buf), "%s", elm_object_text_get(obj));
	char* org_buf = trim(buf);

	if (strlen(org_buf) > 0) {
		elm_object_disabled_set(done_btn, EINA_FALSE);
	} else {
		elm_object_disabled_set(done_btn, EINA_TRUE);
	}
	free(org_buf);
}


void launch_add_contact_screen(appdata_s* ad)
{
	if (!ad) {
		return;
	}
	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}

	ad->current_app_state = TG_ADD_CONTACT_STATE;


	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "add_contact_screen");
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
	itc.func.content_get = on_new_buddy_info_requested;
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
	elm_object_text_set(user_info_lbl, "<font=Tizen:style=Bold color=#00FFFF align=left><font_size=45>&nbsp;&nbsp;Add contact</font_size></font>");
	elm_object_part_content_set(layout, "user_info", user_info_lbl);

	/*************** Entry screen ****************************/



	char *first_name = NULL;
	char *last_name = NULL;
	char *phone_num = NULL;
	get_buddy_contact_details_from_db(ad->peer_in_cahtting_data->use_data->peer_id, &first_name, &last_name, &phone_num);
	if (!last_name) {
		last_name = "";
	}

	char* info_txt = NULL;
	info_txt = (char*)malloc(strlen(NEW_NAME_INFO_TEXT) + 1);
	strcpy(info_txt, NEW_NAME_INFO_TEXT);

	char temp_txt[512] = {0,};
	snprintf(temp_txt, sizeof(temp_txt), "<font=Tizen:style=Regular color=#666362 align=left><font_size=32>%s</font_size></font>", info_txt);
	free(info_txt);

	Evas_Object* info_btn = elm_entry_add(layout);
	elm_object_text_set(info_btn, temp_txt);
	evas_object_size_hint_weight_set(info_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(info_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(info_btn,  EINA_FALSE);
	elm_entry_editable_set(info_btn, EINA_FALSE);
	elm_entry_line_wrap_set(info_btn, EINA_TRUE);
	evas_object_show(info_btn);
	elm_object_part_content_set(layout, "setup_guide_text", info_btn);


	Evas_Object* first_name_entry = elm_entry_add(layout);
	evas_object_size_hint_weight_set(first_name_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(first_name_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);

	elm_object_part_text_set(first_name_entry, "elm.guide", "<font=Tizen:style=Regular color=#666362 align=left><font_size=36>First name (required)</font_size></font>");
	elm_object_text_set(first_name_entry, first_name);
	elm_entry_single_line_set(first_name_entry, EINA_TRUE);
	elm_entry_scrollable_set(first_name_entry, EINA_FALSE);
	elm_entry_cnp_mode_set(first_name_entry, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(first_name_entry, EINA_TRUE);
	elm_entry_text_style_user_push(first_name_entry, "DEFAULT='color=#000000'");
	evas_object_show(first_name_entry);
	elm_object_part_content_set(layout, "first_name_entry", first_name_entry);

	evas_object_data_set(ad->nf, "new_contact_first_name_entry", (void *)first_name_entry);

	evas_object_smart_callback_add(first_name_entry, "changed", on_contact_name_change_enable_ok_button, ad);

	Evas_Object* second_name_entry = elm_entry_add(layout);
	evas_object_size_hint_weight_set(second_name_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(second_name_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(second_name_entry, last_name);
	elm_object_part_text_set(second_name_entry, "elm.guide", "<font=Tizen:style=Regular color=#666362 align=left><font_size=36>Last name (optional)</font_size></font>");

	elm_entry_single_line_set(second_name_entry, EINA_TRUE);
	elm_entry_scrollable_set(second_name_entry, EINA_FALSE);
	elm_entry_cnp_mode_set(second_name_entry, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(second_name_entry, EINA_TRUE);
	elm_entry_text_style_user_push(second_name_entry, "DEFAULT='color=#000000'");
	evas_object_show(second_name_entry);
	elm_object_part_content_set(layout, "second_name_entry", second_name_entry);

	evas_object_data_set(ad->nf, "new_contact_second_name_entry", (void *)second_name_entry);

	//elm_object_part_content_set(layout, "layout", layout);
	/*************** Entry screen ****************************/

	Elm_Object_Item *navi_item = elm_naviframe_item_push(ad->nf, "User Info", NULL, NULL, scroller, NULL);
	Evas_Object *done_btn = elm_button_add(ad->nf);
	elm_object_style_set(done_btn, "naviframe/title_icon");
	elm_object_text_set(done_btn, "Done");
	evas_object_smart_callback_add(done_btn, "clicked", on_contact_name_entry_done_clicked, ad);

	Evas_Object *cancel_btn = elm_label_add(ad->nf);
	elm_object_style_set(cancel_btn, "naviframe/title_icon");

	elm_object_item_part_content_set(navi_item, "title_right_btn", done_btn);
	elm_object_item_part_content_set(navi_item, "title_left_btn", cancel_btn);

	evas_object_data_set(ad->nf, "name_done_btn", (void*)done_btn);
	//elm_object_disabled_set(done_btn, EINA_TRUE);
}
