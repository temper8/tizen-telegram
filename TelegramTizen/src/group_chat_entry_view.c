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
		return strdup("Camera");
	} else {
		return strdup("Gallery");
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

	if (id  == 0) {
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
	elm_object_part_text_set(popup, "title,text", "Load image from");
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
	evas_object_size_hint_min_set(box, -1, 230);
	elm_object_content_set(popup, box);

	evas_object_show(popup);
}

void on_group_buddy_selected(void *data, Evas_Object *obj, void *event_info)
{
	// nothing to do
}

char* on_group_buddy_name_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int)data;
	Eina_List* selected_buddies = evas_object_data_get(obj, "selected_buddies");

	user_data_with_pic_s *item = eina_list_nth(selected_buddies, id);
	user_data_s* user = item->use_data;
	if (!strcmp(part,"elm.text")){

		char* full_name = NULL;
		if (user->first_name && user->last_name) {
			full_name = (char*)malloc(strlen(user->first_name) + strlen(user->last_name) + 1);
			strcpy(full_name, user->first_name);
			strcat(full_name, user->last_name);
		} else if (user->first_name && !user->last_name) {
			full_name = (char*)malloc(strlen(user->first_name) + 1);
			strcpy(full_name, user->first_name);
		} else if (!user->first_name && user->last_name) {
			full_name = (char*)malloc(strlen(user->last_name) + 1);
			strcpy(full_name, user->last_name);
		} else {
			full_name = (char*)malloc(strlen(user->print_name) + 1);
			strcpy(full_name, user->print_name);
		}

		char buf[512] = {'\0'};
		snprintf(buf, 512, "<align=left><font_size=30><color=#000000>%s</color></font_size></align>", full_name);
		free(full_name);
		return strdup(buf);
	}
	return NULL;
}

Evas_Object* on_group_buddy_selection_part_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;

	if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *image = NULL;
		int id = (int) data;
		Eina_List* selected_buddies = evas_object_data_get(obj, "selected_buddies");

		user_data_with_pic_s *item = eina_list_nth(selected_buddies, id);
		user_data_s* user = item->use_data;

		if (user->photo_path && strcmp(user->photo_path, "") != 0) {
			image = create_image_object_from_file(user->photo_path, obj);
		} else {
			image = create_image_object_from_file(ui_utils_get_resource(FM_ICON_ROBO_BUDDY), obj);
		}

		item->contact_icon = image;
		evas_object_event_callback_add(item->contact_icon, EVAS_CALLBACK_DEL, buddy_icon_del_cb, item);

		if(image) {
			eo = elm_layout_add(obj);
			elm_layout_theme_set(eo, "layout", "list/C/type.3", "default");
			elm_layout_content_set(eo, "elm.swallow.content", image);
		}
	}
	return eo;
}

void on_group_chat_done_buton_clicked(void *data, Evas_Object *object, void *event_info)
{
	Evas_Object* name_entry = data;
	appdata_s* ad = evas_object_data_get(name_entry, "app_data");

	// Load chat name entry view
	char* temp_group_name = elm_object_text_get(name_entry);
	if (!temp_group_name) {
		elm_object_text_set(name_entry, "");
		show_toast(ad, "Enter a valid name to group");
		return;
	}

	char* group_name = trim(temp_group_name);

	if (!group_name || strlen(group_name) <= 0) {
		elm_object_text_set(name_entry, "");
		show_toast(ad, "Enter a valid name to group");
		return;
	}

	Eina_List* selected_buddies = evas_object_data_get(name_entry, "selected_buddies");
	Evas_Object* cam_icon = evas_object_data_get(name_entry, "cam_icon");
	char* img_file_path = evas_object_data_get(cam_icon, "image_path");

	send_group_creation_request_to_server(ad->service_client, selected_buddies, group_name, img_file_path);
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

void launch_group_chat_name_entry_view(void *data)
{
	appdata_s* ad = data;
	ad->current_app_state = TG_GROUP_CHAT_NAME_ENTRY_STATE;

	int w, h;
	elm_win_screen_size_get(ad->win, NULL, NULL, &w, &h);
	h -= 130;

	char edj_path[PATH_MAX] = {0, };

	Evas_Object* main_layout = elm_layout_add(ad->win);
	app_get_resource(EDJ_CHAT_CONV_FILE, edj_path, (int)PATH_MAX);
	elm_layout_file_set(main_layout, edj_path, "group_chat_entry");
	evas_object_size_hint_min_set(main_layout, w, h);
	evas_object_show(main_layout);

	Evas_Object* entry_layout = elm_layout_add(ad->win);
	app_get_resource(EDJ_CHAT_CONV_FILE, edj_path, (int)PATH_MAX);
	elm_layout_file_set(entry_layout, edj_path, "group_chat_photo_name_entry");
	evas_object_show(entry_layout);
	elm_object_part_content_set(main_layout, "swallow.group_chat_entry_box", entry_layout);

	Evas_Object* cam_icon = elm_image_add(main_layout);
	elm_image_file_set(cam_icon, ui_utils_get_resource(CAMERA_ICON), NULL);
	evas_object_show(cam_icon);

	evas_object_smart_callback_add(cam_icon, "clicked", on_image_load_options_cb, (void*)cam_icon);
	elm_object_part_content_set(entry_layout, "swallow.cam_box", cam_icon);

	Evas_Object* name_entry = elm_entry_add(main_layout);
	elm_entry_single_line_set(name_entry, EINA_TRUE);
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

	static Elm_Genlist_Item_Class itc;

	Evas_Object* buddy_gen_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(buddy_gen_list, ELM_LIST_COMPRESS);
	elm_genlist_decorate_mode_set(buddy_gen_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(buddy_gen_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(buddy_gen_list, EVAS_HINT_FILL, EVAS_HINT_FILL);

	evas_object_data_set(buddy_gen_list, "app_data", ad);
	evas_object_data_set(buddy_gen_list, "selected_buddies", (void*)selected_buddies);

	evas_object_data_set(cam_icon, "app_data", ad);
	evas_object_data_set(cam_icon, "selected_buddies", (void*)selected_buddies);

	evas_object_data_set(name_entry, "app_data", ad);
	evas_object_data_set(name_entry, "selected_buddies", (void*)selected_buddies);
	evas_object_data_set(name_entry, "cam_icon", cam_icon);

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

	Elm_Object_Item* chat_nav_item = elm_naviframe_item_push(ad->nf, "New chat group", NULL, NULL, main_layout, NULL);

	Evas_Object* done_btn = elm_button_add(ad->layout);
	elm_object_style_set(done_btn, "naviframe/title_icon");
	Evas_Object* done_icon = elm_image_add(ad->layout);
	elm_image_file_set(done_icon, ui_utils_get_resource(FM_OK_BUTTON), NULL);
	evas_object_smart_callback_add(done_btn, "clicked", on_group_chat_done_buton_clicked, name_entry);
	elm_object_content_set(done_btn, done_icon);
	evas_object_show(done_btn);

	Evas_Object* cancel_btn = elm_button_add(ad->layout);
	elm_object_style_set(cancel_btn, "naviframe/title_icon");
	Evas_Object* cancel_icon = elm_image_add(ad->layout);
	elm_image_file_set(cancel_icon, ui_utils_get_resource(FM_CANCEL_BUTTON), NULL);
	evas_object_smart_callback_add(cancel_btn, "clicked", on_group_chat_cancel_buton_clicked, ad);
	elm_object_content_set(cancel_btn, cancel_icon);
	evas_object_show(cancel_btn);

	elm_object_item_part_content_set(chat_nav_item, "title_right_btn", done_btn);
	elm_object_item_part_content_set(chat_nav_item, "title_left_btn", cancel_btn);

}
