/**
 * @file group_chat_entry_view.c
 * @date Jul 11, 2015
 * @author sandeep
 */

#include "group_chat_entry_view.h"
#include "server_requests.h"

static Evas_Object *create_image_object_from_file(const char *icon_name, Evas_Object *parent)
{
	Evas_Object *icon = elm_image_add(parent);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_image_file_set(icon, icon_name, NULL);
	evas_object_show(icon);
	return icon;
}

char* on_image_load_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	if (id == 0) {
		return strdup(_("IDS_TGRAM_OPT_FROM_GALLERY_ABB2"));
	} else {
		return strdup(_("IDS_TGRAM_OPT_TAKE_PICTURE_ABB"));
	}
}

void on_camera_result_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);

		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);
			evas_object_data_set(user_data, "image_path", (void*)file_path);
			elm_image_file_set(user_data, file_path, NULL);
			evas_object_color_set(user_data, 255, 255, 255, 255);
			break;
		}
	}
}

void on_image_load_option_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;
	int id = 0;
	Elm_Object_Item *item = event_info;

	id = (int)elm_object_item_data_get(item);
	app_control_h app_control;
	int ret = app_control_create(&app_control);

	Evas_Object* cam_icon = evas_object_data_get(popup, "cam_icon");

	appdata_s* ad = evas_object_data_get(cam_icon, "app_data");

	if(ret != APP_CONTROL_ERROR_NONE) {
		show_toast(ad, "Error: Can not load image picker");
		return;
	}

	if (id  == 1) {
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);
		app_control_set_mime(app_control, "image/jpg");
		app_control_send_launch_request(app_control, &on_camera_result_cb, cam_icon);
	} else {
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);
		app_control_set_mime(app_control,"image/*");
		app_control_send_launch_request(app_control, &on_camera_result_cb, cam_icon);
	}

	app_control_destroy(app_control);
	evas_object_del(popup);
}

void on_image_load_options_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* cam_icon =  data;
	appdata_s* ad = evas_object_data_get(data, "app_data");
	static Elm_Genlist_Item_Class itc;
	Evas_Object *popup;
	Evas_Object *box;
	Evas_Object *genlist;
	int i;
	Evas_Object *win = ad->win;

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	elm_object_part_text_set(popup, "title,text", i18n_get_text("IDS_TGRAM_HEADER_SELECT_IMAGE_ABB2"));
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_data_set(popup, "cam_icon", cam_icon);

	/* box */
	box = elm_box_add(popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* genlist */
	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	itc.item_style = "default";
	itc.func.text_get = on_image_load_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < 2; i++) {
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_image_load_option_selected_cb, popup);
	}
	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);
	elm_object_content_set(popup, box);

	evas_object_show(popup);
}

void on_group_buddy_selected(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
}

char* on_group_buddy_name_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int)data;
	Eina_List* selected_buddies = evas_object_data_get(obj, "selected_buddies");


	int size = eina_list_count(selected_buddies);
	if (size <= 0) {
		if (!strcmp(part,"elm.text")){
			char buf[512] = {'\0'};
			snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", "No Items");
			return strdup(buf);

		} else if (!strcmp(part, "elm.text.sub")) {
			return NULL;
		}
	}

	user_data_with_pic_s* item = eina_list_nth(selected_buddies, id);
	user_data_s* user = item->use_data;

	if (!strcmp(part,"elm.text")){
		char* user_name = replace(user->print_name, '_', " ");
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=35><color=#000000>%s</color></font_size></align>", user_name);
		free(user_name);
		return strdup(buf);

	}

	return NULL;
}

Evas_Object* on_group_buddy_selection_part_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.swallow.icon")) {

		int id = (int) data;
		Eina_List* selected_buddies = evas_object_data_get(obj, "selected_buddies");
		int size = eina_list_count(selected_buddies);
		if (size <= 0) {
			return eo;
		}
		user_data_with_pic_s* item = eina_list_nth(selected_buddies, id);
		user_data_s* user = item->use_data;
		Evas_Object *profile_pic = NULL;
		if (user->photo_path && strcmp(user->photo_path, "") != 0) {
			profile_pic = create_image_object_from_file(user->photo_path, obj);
		} else {
			profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_PROFILE_PIC), obj);
		}

		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		Evas_Object* user_pic_layout = elm_layout_add(obj);
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

void on_group_chat_done_buton_clicked(void *data, Evas_Object *object, void *event_info)
{
	Evas_Object* name_entry = data;
	appdata_s* ad = evas_object_data_get(name_entry, "app_data");

	// Load chat name entry view
	const char *temp_group_name = elm_object_text_get(name_entry);
	if (!temp_group_name) {
		elm_object_text_set(name_entry, "");
		show_toast(ad, "Enter a valid name to group");
		return;
	}

	char *group_name = trim(temp_group_name);

	if (!group_name || strlen(group_name) <= 0) {
		elm_object_text_set(name_entry, "");
		show_toast(ad, "Enter a valid name to group");
		return;
	}

	Eina_List* selected_buddies = evas_object_data_get(name_entry, "selected_buddies");
	//Evas_Object* cam_icon = evas_object_data_get(name_entry, "cam_icon");
	Evas_Object* cam_icon = evas_object_data_get(ad->nf, "group_chat_profile_pic");
	char* img_file_path = evas_object_data_get(cam_icon, "image_path");

	show_loading_popup(ad);

	send_group_creation_request_to_server(ad, ad->service_client, selected_buddies, group_name, img_file_path);
	eina_list_free(selected_buddies);
}

void on_group_chat_cancel_buton_clicked(void *data, Evas_Object *object, void *event_info)
{
	appdata_s* ad = data;
	if (ad->buddy_list) {
		for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
			user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
			user_data_s* user = item->use_data;
			user->is_selected = EINA_FALSE;
		}
	}
	elm_naviframe_item_pop(ad->nf);
	ad->current_app_state = TG_BUDDY_LIST_STATE;
	evas_object_show(ad->panel);
	elm_panel_hidden_set(ad->panel, EINA_FALSE);
}

char* group_chat_entry_requested_cb(void *data, Evas_Object *obj, const char *part)
{
	//int id = (int) data;
	return NULL;
}

Evas_Object* group_chat_pic_requested_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.icon.left") || !strcmp(part, "elm.icon.1") || !strcmp(part, "elm.swallow.icon")  ) {
		appdata_s* ad = evas_object_data_get(obj, "app_data");
		int id = (int) data;
		if (id == 0) {
			Evas_Object *profile_pic = NULL;
			profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_MULTI_PIC), ad->nf);
			evas_object_color_set(profile_pic, 45, 165, 224, 255);
			evas_object_data_set(profile_pic, "app_data", ad);
			evas_object_smart_callback_add(profile_pic, "clicked", on_image_load_options_cb, (void*)profile_pic);
			char edj_path[PATH_MAX] = {0, };
			app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
			Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
			elm_layout_file_set(user_pic_layout, edj_path, "group_circle_layout");
			evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(user_pic_layout);
			elm_object_part_content_set(user_pic_layout, "content", profile_pic);
			evas_object_data_set(ad->nf, "group_chat_profile_pic", profile_pic);

			eo = elm_layout_add(obj);
			elm_layout_theme_set(eo, "layout", "list/B/type.1", "default");
			elm_layout_content_set(eo, "elm.swallow.content", user_pic_layout);
		}
	}
	return eo;
}

void launch_group_chat_name_entry_view(void *data)
{
	appdata_s* ad = data;
	ad->current_app_state = TG_GROUP_CHAT_NAME_ENTRY_STATE;

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	char edj_path[PATH_MAX] = {0, };

	Evas_Object* main_layout = elm_layout_add(ad->win);
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
	elm_layout_file_set(main_layout, edj_path, "group_chat_entry");
	evas_object_size_hint_weight_set(main_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(main_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(main_layout);

	elm_object_content_set(scroller, main_layout);

	Evas_Object* entry_layout = elm_layout_add(ad->win);
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
	elm_layout_file_set(entry_layout, edj_path, "group_chat_photo_name_entry");
	evas_object_show(entry_layout);
	elm_object_part_content_set(main_layout, "swallow.group_chat_entry_box", entry_layout);

#if 0
	Evas_Object* cam_icon = elm_image_add(main_layout);
	elm_image_file_set(cam_icon, ui_utils_get_resource(CAMERA_ICON), NULL);
	evas_object_show(cam_icon);
#endif
#if 0

	Evas_Object *cam_icon = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_MULTI_PIC), main_layout);
	evas_object_color_set(cam_icon, 45, 165, 224, 255);


	Evas_Object *user_pic_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(user_pic_layout, edj_path, "search_circle_layout");
	evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(user_pic_layout);
	elm_object_part_content_set(user_pic_layout, "content", cam_icon);


	Evas_Object* eo = elm_layout_add(main_layout);
	elm_layout_theme_set(eo, "layout", "list/B/type.1", "default");
	elm_layout_content_set(eo, "elm.swallow.content", user_pic_layout);

	evas_object_smart_callback_add(cam_icon, "clicked", on_image_load_options_cb, (void*)cam_icon);
	elm_object_part_content_set(entry_layout, "swallow.cam_box", eo);
#endif

	/********************* list *************************/


	Evas_Object *list = elm_genlist_add(ad->nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(list);

	elm_object_part_content_set(entry_layout, "swallow.cam_box", list);

	evas_object_data_set(ad->nf, "group_chat_entry_list", list);
	evas_object_data_set(list, "app_data", ad);
	static Elm_Genlist_Item_Class itc1;
	itc1.item_style = "type1";
	itc1.func.text_get = group_chat_entry_requested_cb;
	itc1.func.content_get = group_chat_pic_requested_cb;
	itc1.func.state_get = NULL;
	itc1.func.del = NULL;

	elm_genlist_item_append(list, &itc1, (void*) 0, NULL, ELM_GENLIST_ITEM_NONE, on_group_buddy_selected, (void*)ad);


	/******************** list *************************/


	Evas_Object* name_entry = elm_entry_add(main_layout);
	elm_entry_single_line_set(name_entry, EINA_TRUE);
	limit_filter_data.max_char_count = 20;
	elm_entry_markup_filter_append(name_entry, elm_entry_filter_limit_size, &limit_filter_data);
	evas_object_show(name_entry);
	elm_object_part_content_set(entry_layout, "swallow.entry_box", name_entry);

	Eina_List* selected_buddies = NULL;

	for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
		user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
		user_data_s* user = item->use_data;
		if (user->is_selected) {
			selected_buddies = eina_list_append(selected_buddies, item);
		}
	}

	/***************** contacts header *************************/
	Evas_Object* contact_lbl = elm_label_add(ad->nf);
	evas_object_show(contact_lbl);
	evas_object_size_hint_weight_set(contact_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(contact_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);

	char res_str[256] = {'\0'};
	sprintf(res_str, i18n_get_text("IDS_TGRAM_BODY_PD_PARTICIPANTS"), eina_list_count(selected_buddies));

	char count_str[256] = {'\0'};
	sprintf(count_str, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=45>&nbsp;&nbsp;%s</font_size></font>", res_str);

	elm_object_text_set(contact_lbl, count_str);
	elm_object_part_content_set(main_layout, "swallow.contacts_header", contact_lbl);
	/***************** contacts header *************************/


	static Elm_Genlist_Item_Class itc;

	Evas_Object* buddy_gen_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(buddy_gen_list, ELM_LIST_COMPRESS);
	// FIXME: Deprecated API
	//elm_genlist_decorate_mode_set(buddy_gen_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(buddy_gen_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(buddy_gen_list, EVAS_HINT_FILL, EVAS_HINT_FILL);

	evas_object_data_set(buddy_gen_list, "app_data", ad);
	evas_object_data_set(buddy_gen_list, "selected_buddies", (void*)selected_buddies);

	//evas_object_data_set(cam_icon, "app_data", ad);
	//evas_object_data_set(cam_icon, "selected_buddies", (void*)selected_buddies);

	evas_object_data_set(name_entry, "app_data", ad);
	evas_object_data_set(name_entry, "selected_buddies", (void*)selected_buddies);
	//evas_object_data_set(name_entry, "cam_icon", cam_icon);

	itc.item_style = "default_style";
	itc.func.text_get = on_group_buddy_name_get_cb;
	itc.func.content_get = on_group_buddy_selection_part_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	int size = 0;
	if (selected_buddies) {
		size = eina_list_count(selected_buddies);
	} else {
		size = 1; // no items
	}

	for (int i = 0; i < size; i++) {
		elm_genlist_item_append(buddy_gen_list, &itc, (void*)i, NULL, ELM_GENLIST_ITEM_NONE, on_group_buddy_selected, (void*)i);
	}

	evas_object_show(buddy_gen_list);

	elm_object_part_content_set(main_layout, "swallow.group_chat_buddy_list_box", buddy_gen_list);

	Elm_Object_Item* chat_nav_item = elm_naviframe_item_push(ad->nf, "New Group", NULL, NULL, scroller, NULL);

	Evas_Object *done_btn = elm_button_add(ad->nf);
	elm_object_style_set(done_btn, "naviframe/title_right");
	elm_object_text_set(done_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_DONE_ABB"));
	evas_object_smart_callback_add(done_btn, "clicked", on_group_chat_done_buton_clicked, name_entry);
	evas_object_show(done_btn);

	Evas_Object *cancel_btn = elm_button_add(ad->nf);
	elm_object_style_set(cancel_btn, "naviframe/title_left");
	elm_object_text_set(cancel_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_CANCEL_ABB"));
	evas_object_smart_callback_add(cancel_btn, "clicked", on_group_chat_cancel_buton_clicked, ad);
	evas_object_show(cancel_btn);

	elm_object_item_part_content_set(chat_nav_item, "title_right_btn", done_btn);
	elm_object_item_part_content_set(chat_nav_item, "title_left_btn", cancel_btn);

}
