/*
 * tg_settings_view.c
 *
 *  Created on: Sep 29, 2015
 *      Author: sandeep
 */


#include "tg_settings_view.h"
#include "server_requests.h"
#include "tg_set_username_view.h"
#include "tg_edit_name_view.h"
#include "tg_db_wrapper.h"

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

static void on_chat_bg_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (ad && ad->chat_background) {
#if 0
		if (strstr(ad->chat_background, ui_utils_get_resource(TG_CHAT_DEFAULT_BG)) != NULL) {
			show_toast(ad, "Default background");
		} else {
			launch_app_control(ad, "image", ad->chat_background);
		}
#endif
	}
}

Evas_Object* on_settings_info_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	int id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	if (!strcmp(part, "elm.swallow.icon.0")) {
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
			first_text = "Chat Background";
		} else {
			first_text = "";
		}

		snprintf(buf, 512, "<font=Tizen:style=Bold color=#000000 align=left><font_size=40>%s</font_size></font>", first_text);

		Evas_Object*  name_lbl = elm_label_add(ad->nf);
		elm_object_text_set(name_lbl, buf);
		evas_object_size_hint_weight_set(name_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(name_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(name_lbl);

		elm_object_part_content_set(user_status_layout, "swallow.name", name_lbl);
		return user_status_layout;
	} else if (!strcmp(part, "elm.swallow.end")) {
		if (ad->chat_background) {

			char *doc_thumb = NULL;
			get_thumbnail_from_video_url(ad->chat_background, &doc_thumb);
			Evas_Object *chat_bg = NULL;
			if (doc_thumb) {
				chat_bg = get_image_from_path(doc_thumb, ad->nf);
			} else {
				chat_bg = get_image_from_path(ad->chat_background, ad->nf);
			}

			evas_object_data_set(ad->nf, "settings_chat_bg", chat_bg);

			eo = elm_layout_add(obj);
			elm_layout_theme_set(eo, "layout", "list/C/type.1", "default");
			elm_layout_content_set(eo, "elm.swallow.content", chat_bg);
			evas_object_smart_callback_add(chat_bg, "clicked", on_chat_bg_clicked, ad);
		}
	}
	return eo;
}


Evas_Object* on_user_phone_info_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	int id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	if (!strcmp(part, "elm.swallow.icon.0")) {
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
			if (ad->current_user_data->phone) {
				first_text = ad->current_user_data->phone;
			} else {
				first_text = "";
			}
		} else {
			if (ad->current_user_data->username && strlen(ad->current_user_data->username) > 0 && strstr(ad->current_user_data->username, "_null_") == NULL) {
				first_text = ad->current_user_data->username;
			} else {
				first_text = "None";
			}
		}

		snprintf(buf, 512, "<font=Tizen:style=Bold color=#000000 align=left><font_size=40>%s</font_size></font>", first_text);

		Evas_Object*  name_lbl = elm_label_add(ad->nf);
		elm_object_text_set(name_lbl, buf);
		evas_object_size_hint_weight_set(name_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(name_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(name_lbl);

		if (id == 1) {
			evas_object_data_set(ad->nf, "settings_user_name_label", name_lbl);
		}

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
	return eo;
}

Evas_Object* on_user_info_requested(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *profile_pic = NULL;

		if (ad->current_user_data->photo_path && strlen(ad->current_user_data->photo_path) > 0 && strstr(ad->current_user_data->photo_path, "_null_") == NULL) {
			profile_pic = get_image_from_path(ad->current_user_data->photo_path, ad->nf);
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


		char* user_name = replace(ad->current_user_data->print_name, '_', " ");
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<font=Tizen:style=Bold color=#FFFFFF align=left><font_size=40>%s</font_size></font>", user_name);
		free(user_name);

		Evas_Object*  name_lbl = elm_label_add(ad->nf);
		elm_object_text_set(name_lbl, buf);
		evas_object_size_hint_weight_set(name_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(name_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(name_lbl);

		elm_object_part_content_set(user_status_layout, "swallow.name", name_lbl);

		char* user_status = i18n_get_text("IDS_TGRAM_SBODY_ONLINE");
		char status_buf[126] = {'\0'};
		sprintf(status_buf, "<font=Tizen:style=Normal color=#FFFFFF align=left><font_size=35>%s</font_size></font>", user_status);

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

void on_user_info_item_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
}

void on_phone_info_item_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	int id = (int)data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");

	if (id == 1) {
		launch_set_username_cb(ad);
	}
}

void on_image_select_result_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);

		for(int i = 0 ; i < array_length ; i++) {
			file_path = path_arryay[i];
			if (file_path) {
				appdata_s *ad = (appdata_s*)user_data;
				if (ad) {
					show_loading_popup(ad);
					send_set_profile_pic_request(ad, ad->service_client, ad->current_user_data->user_id.id, file_path);
				}
				break;
			}
		}
	}
}

void on_image_request_option_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;
	int id = 0;
	Elm_Object_Item *item = event_info;

	id = (int)elm_object_item_data_get(item);
	app_control_h app_control;
	int ret = app_control_create(&app_control);


	appdata_s *ad = evas_object_data_get(popup, "app_data");

	if(ret != APP_CONTROL_ERROR_NONE) {
		show_toast(ad, "Error: Can not load image picker");
		return;
	}

	if (id == 1) {
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);
		app_control_set_mime(app_control, "image/jpg");
		app_control_send_launch_request(app_control, &on_image_select_result_cb, ad);
	} else {
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);
		app_control_set_mime(app_control,"image/*");
		app_control_send_launch_request(app_control, &on_image_select_result_cb, ad);
	}

	app_control_destroy(app_control);
	evas_object_del(popup);
}

char* on_camera_load_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	if (id == 0) {
		return strdup(_("IDS_TGRAM_OPT_FROM_GALLERY_ABB2"));
	} else {
		return strdup(_("IDS_TGRAM_OPT_TAKE_PICTURE_ABB"));
	}
}

void on_camera_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;

	if (!ad)
		return;

	static Elm_Genlist_Item_Class itc;
	Evas_Object *popup;
	Evas_Object *box;
	Evas_Object *genlist;
	int i;


	Evas_Object *win = ad->win;

	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	elm_object_part_text_set(popup, "title,text", i18n_get_text("IDS_TGRAM_HEADER_SELECT_IMAGE_ABB2"));
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	//evas_object_data_set(popup, "cam_icon", cam_icon);
	evas_object_data_set(popup, "app_data", ad);
	/* box */
	box = elm_box_add(popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* genlist */
	genlist = elm_genlist_add(box);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	itc.item_style = "default";
	itc.func.text_get = on_camera_load_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < 2; i++) {
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_image_request_option_selected_cb, popup);
	}
	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);
	evas_object_size_hint_min_set(box, -1, 230);
	elm_object_content_set(popup, box);

	evas_object_show(popup);
}


/**************************************************************************/




void on_chat_bg_select_result_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);

		for(int i = 0 ; i < array_length ; i++) {
			file_path = path_arryay[i];
			if (file_path) {
				appdata_s *ad = (appdata_s*)user_data;
				if (ad) {
					Evas_Object *chat_bg = evas_object_data_get(ad->nf, "settings_chat_bg");
					if (chat_bg) {
						elm_image_file_set(chat_bg, file_path, NULL);

						preference_set_string(TG_CHAT_BG_PREFERENCE, file_path);

						char *chat_bg = NULL;
						preference_get_string(TG_CHAT_BG_PREFERENCE, &chat_bg);

						if (ad->chat_background) {
							free(ad->chat_background);
							ad->chat_background = NULL;
						}

						if (chat_bg) {
							ad->chat_background = strdup(chat_bg);
						}

						if (!ad->chat_background) {
							ad->chat_background = strdup(ui_utils_get_resource(TG_CHAT_DEFAULT_BG));
							preference_set_string(TG_CHAT_BG_PREFERENCE, ad->chat_background);
						}
					}
				}
				break;
			}
		}
	}
}


void on_chat_bg_change_option_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;
	int id = 0;
	Elm_Object_Item *item = event_info;

	id = (int)elm_object_item_data_get(item);
	app_control_h app_control;
	int ret = app_control_create(&app_control);


	appdata_s *ad = evas_object_data_get(popup, "app_data");

	if(ret != APP_CONTROL_ERROR_NONE) {
		show_toast(ad, "Error: Can not load image picker");
		return;
	}
	/*if (id == 0) {
		if (ad->chat_background) {
			free(ad->chat_background);
			ad->chat_background = NULL;
		}
		ad->chat_background = strdup(ui_utils_get_resource(TG_CHAT_DEFAULT_BG));
		preference_set_string(TG_CHAT_BG_PREFERENCE, ad->chat_background);
		Evas_Object *chat_bg = evas_object_data_get(ad->nf, "settings_chat_bg");
		if (chat_bg) {
			elm_image_file_set(chat_bg, ad->chat_background, NULL);
		}
	}else */if (id  == 1) {
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);
		app_control_set_mime(app_control, "image/jpg");
		app_control_send_launch_request(app_control, &on_chat_bg_select_result_cb, ad);
	} else {
		app_control_set_launch_mode(app_control, APP_CONTROL_LAUNCH_MODE_GROUP);
		app_control_set_app_id(app_control, "ug-gallery-efl");
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);
		app_control_set_mime(app_control,"image/*");
		app_control_send_launch_request(app_control, &on_chat_bg_select_result_cb, ad);
	}

	app_control_destroy(app_control);
	evas_object_del(popup);
}

char* on_chat_bg_load_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	if (id == 0) {
		return strdup(_("IDS_TGRAM_OPT_FROM_GALLERY_ABB2"));
	} else {
		return strdup(_("IDS_TGRAM_OPT_TAKE_PICTURE_ABB"));
	}
}

void on_settings_info_item_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	Evas_Object* cam_icon =  data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
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

	evas_object_data_set(popup, "app_data", ad);
	/* box */
	box = elm_box_add(popup);
	elm_box_horizontal_set(box, EINA_FALSE);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);

	/* genlist */
	genlist = elm_genlist_add(box);
	elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_scroller_content_min_limit(genlist, EINA_TRUE, EINA_TRUE);

	itc.item_style = "default";
	itc.func.text_get = on_chat_bg_load_text_get_cb;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (i = 0; i < 2; i++) {
		elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_chat_bg_change_option_selected_cb, popup);
	}
	evas_object_show(genlist);
	elm_box_pack_end(box, genlist);
	elm_object_content_set(popup, box);
	evas_object_show(popup);
}

/*************************************************************************/
#if 0
void launch_settings_screen(appdata_s* ad)
{
	if (!ad) {
		return;
	}

	ad->current_app_state = TG_SETTINGS_SCREEN_STATE;

	if (!ad->current_user_data) {
		load_registered_user_data(ad);
	}

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "settings_screen");
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
	itc.func.content_get = on_user_info_requested;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	int i = 1;
	elm_genlist_item_append(pic_name_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_user_info_item_clicked, (void*) i);

	evas_object_show(pic_name_list);
	elm_object_part_content_set(layout, "pic_name_layout", pic_name_list);
	/******************* user Info **********************/


	Evas_Object* user_info_lbl = elm_label_add(ad->nf);
	evas_object_show(user_info_lbl);
	evas_object_size_hint_weight_set(user_info_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(user_info_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(user_info_lbl, "<font=Tizen:style=Bold color=#00FFFF align=left><font_size=45>&nbsp;&nbsp;Info</font_size></font>");
	elm_object_part_content_set(layout, "user_info", user_info_lbl);


	/******************** Phone num layout ********************/

	Evas_Object *phone_num_list = NULL;
	static Elm_Genlist_Item_Class sitc;
	phone_num_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(phone_num_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(phone_num_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(phone_num_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(phone_num_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_data_set(phone_num_list, "app_data", ad);

	sitc.item_style = "type1";
	sitc.func.text_get = NULL;
	sitc.func.content_get = on_user_phone_info_requested;
	sitc.func.state_get = NULL;
	sitc.func.del = NULL;
	for (int i = 0 ; i < 2; i++) {
		elm_genlist_item_append(phone_num_list, &sitc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_phone_info_item_clicked, (void*) i);
	}

	evas_object_show(phone_num_list);
	elm_object_part_content_set(layout, "phone_num_layout", phone_num_list);

	/******************* Phone Num layout ************************/

	Evas_Object* settings_info_lbl = elm_label_add(ad->nf);
	evas_object_show(settings_info_lbl);
	evas_object_size_hint_weight_set(settings_info_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(settings_info_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(settings_info_lbl, "<font=Tizen:style=Bold color=#00FFFF align=left><font_size=45>&nbsp;&nbsp;Settings</font_size></font>");
	elm_object_part_content_set(layout, "settings_info", settings_info_lbl);



	/******************** Settings layout ********************/

	Evas_Object *settings_list = NULL;
	static Elm_Genlist_Item_Class titc;
	settings_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(settings_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(settings_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(settings_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(settings_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_data_set(settings_list, "app_data", ad);

	titc.item_style = "type1";
	titc.func.text_get = NULL;
	titc.func.content_get = on_settings_info_requested;
	titc.func.state_get = NULL;
	titc.func.del = NULL;
	for (int i = 0 ; i < 1; i++) {
		elm_genlist_item_append(settings_list, &titc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_settings_info_item_clicked, (void*) i);
	}

	evas_object_show(settings_list);
	elm_object_part_content_set(layout, "setting_option_layout", settings_list);

	/******************* Settings layout ************************/



	//Evas_Object *profile_pic = NULL;
	//profile_pic = get_image_from_path(ui_utils_get_resource(CAMERA_ICON), ad->nf);
	/*Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(user_pic_layout, edj_path, "circle_layout");
	evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(user_pic_layout);
	elm_object_part_content_set(user_pic_layout, "content", profile_pic);

	Evas_Object *eo = elm_layout_add(ad->nf);
	elm_layout_theme_set(eo, "layout", "list/C/type.3", "default");
	elm_layout_content_set(eo, "elm.swallow.content", user_pic_layout);*/

	Evas_Object* cam_btn = elm_button_add(ad->layout);
	evas_object_size_hint_weight_set(cam_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(cam_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(cam_btn);


	Evas_Object *cam_image = elm_image_add(ad->layout);
	elm_image_file_set(cam_image, ui_utils_get_resource(CAMERA_ICON), NULL);
	evas_object_size_hint_weight_set(cam_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(cam_image, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(cam_image);
	elm_object_content_set(cam_btn, cam_image);

	elm_object_part_content_set(layout, "cam_layout", cam_btn);
	evas_object_smart_callback_add(cam_btn, "clicked", on_camera_button_clicked, cam_btn);
	evas_object_data_set(cam_btn, "app_data", ad);

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "Settings", NULL, NULL, scroller, NULL);
}

#endif


char* _text_requested_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;

	appdata_s* ad = evas_object_data_get(obj, "app_data");
	char *user_name = NULL;
	char *first_name = NULL;
	char *last_name = NULL;
	if (!strcmp(part,"elm.text.main.left.top") || !strcmp(part,"elm.text")){
		switch(id) {
			case 0:
				//return replace(ad->current_user_data->print_name, '_', " ");
#if 0
				user_name = (char*)malloc(strlen(ad->current_user_data->first_name) + strlen(" ") + strlen(ad->current_user_data->last_name) + 1);
				strcpy(user_name, ad->current_user_data->first_name);
				strcat(user_name, " ");
				strcat(user_name, ad->current_user_data->last_name);
				return user_name;
#else
				first_name = ad->current_user_data->first_name;
				last_name = ad->current_user_data->last_name;


				if (!first_name || strstr(first_name ,"null") != 0) {
					first_name = NULL;
				}

				if (!first_name && !last_name) {
					first_name = "";
				}

				if (!last_name || strstr(last_name ,"null") != 0) {
					last_name = "";
				}
				user_name = (char*)malloc(strlen(first_name) + strlen(" ") + strlen(last_name) + 1);
				strcpy(user_name, first_name);
				strcat(user_name, " ");
				strcat(user_name, last_name);
				return user_name;
#endif
			case 1:
				return strdup(i18n_get_text("IDS_TGRAM_OPT_SET_BACKGROUND_IMAGE_ABB"));
			default:
				break;
		}


	} else if (!strcmp(part, "elm.text.sub.left.bottom") || !strcmp(part,"elm.text.sub")) {
		switch(id) {
			case 0:
			if (ad->current_user_data->online) {
				return strdup(i18n_get_text("IDS_TGRAM_SBODY_ONLINE"));
			} else {
				return strdup("offine");
			}
			break;
		}
	}

	return NULL;
}

Evas_Object* _content_requested_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *eo = NULL;
	if (!strcmp(part, "elm.icon.left") || !strcmp(part, "elm.icon.1") || !strcmp(part, "elm.swallow.icon")  ) {
		appdata_s* ad = evas_object_data_get(obj, "app_data");

		int id = (int) data;
		if (id == 0) {

			Evas_Object *profile_pic = NULL;

			if (ad->current_user_data->photo_path && strlen(ad->current_user_data->photo_path) > 0 && strstr(ad->current_user_data->photo_path, "_null_") == NULL) {
				profile_pic = get_image_from_path(ad->current_user_data->photo_path, ad->nf);
			} else  {
				profile_pic = get_image_from_path(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC), ad->nf);
				evas_object_color_set(profile_pic, 45, 165, 224, 255);
			}

			char edj_path[PATH_MAX] = {0, };
			app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
			Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
			elm_layout_file_set(user_pic_layout, edj_path, "search_circle_layout");
			evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(user_pic_layout);
			elm_object_part_content_set(user_pic_layout, "content", profile_pic);
			evas_object_data_set(ad->nf, "settings_user_profile_pic", profile_pic);

			eo = elm_layout_add(obj);
			elm_layout_theme_set(eo, "layout", "list/B/type.1", "default");
			elm_layout_content_set(eo, "elm.swallow.content", user_pic_layout);
		}

	}
	return eo;
}

static void _cancel_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;
	evas_object_del(popup);
}

static void _logout_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Evas_Object *popup = NULL;

	popup = evas_object_data_del(obj, "popup");
	if (popup) {
		evas_object_del(popup);
	}
	send_request_for_logout(ad, ad->service_client);
	show_loading_popup(ad);
}

static void _create_logout_popup(appdata_s *ad)
{
	Evas_Object *popup;
	Evas_Object *logout_btn;
	Evas_Object *btn;

	/* popup */
	popup = elm_popup_add(ad->win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_translatable_text_set(popup,"IDS_TGRAM_POP_USE_TELEGRAM_SEAMLESSLY_ACROSS_ANY_NUMBER_OF_DEVICES_MSG");
	elm_object_part_text_set(popup, "title,text", i18n_get_text("IDS_TGRAM_OPT_LOG_OUT"));

	/* logout button */
	logout_btn = elm_button_add(popup);
	elm_object_style_set(logout_btn, "popup");
	elm_object_translatable_text_set(logout_btn, "IDS_TGRAM_BUTTON_LOG_OUT_ABB2");
	elm_object_part_content_set(popup, "button2", logout_btn);
	evas_object_smart_callback_add(logout_btn, "clicked", _logout_btn_clicked_cb, ad);
	evas_object_data_set(logout_btn, "popup", popup);

	/* cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_translatable_text_set(btn, "IDS_TGRAM_BUTTON_CANCEL_ABB5");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _cancel_btn_clicked_cb, popup);

	evas_object_show(popup);
}

static void _more_popup_rotate(void *data, Evas_Object *obj, void *event_info)
{
	int pos;
	Evas_Coord w, h;
	appdata_s *ad = data;

	elm_win_screen_size_get(ad->win, NULL, NULL, &w, &h);
	pos = elm_win_rotation_get(ad->win);

	switch (pos) {
	case 90:
	case 270:
		evas_object_move(ad->menu_popup, 0, w);
		break;
	case 180:
	default:
		evas_object_move(ad->menu_popup, 0, h);
		break;
    }
}

static void _ctxpopup_dismiss_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	evas_object_del(ad->menu_popup);
	ad->menu_popup = NULL;
}

static void _ctxpopup_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;

	if (!ad) {
			LOGE("ad is NULL");
			return;
	}

	if (!ad->win) {
		LOGE("window is NULL");
		return;
	}
	evas_object_smart_callback_del(ad->win, "rotation,changed", _more_popup_rotate);
	if (ad->menu_popup) {
		evas_object_smart_callback_del(ad->menu_popup, "dismissed", _ctxpopup_dismiss_cb);
		evas_object_del(ad->menu_popup);
		ad->menu_popup = NULL;
	}
}

static void ctxpopup_profile_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad) {
		LOGE("ad is NULL");
		return;
	}

	_ctxpopup_dismiss_cb(ad, NULL, NULL);
	on_camera_button_clicked(ad, obj, event_info);

	/* please input here when set profile picture menu is clicked */
}

static void ctxpopup_edit_name_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad) {
		LOGE("ad is NULL");
		return;
	}

	_ctxpopup_dismiss_cb(ad, NULL, NULL);
	launch_editname_screen(ad);
	/* please input here when edit name menu is clicked */
}

static void ctxpopup_logout_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad) {
		LOGE("ad is NULL");
		return;
	}

	_ctxpopup_dismiss_cb(ad, NULL, NULL);
	_create_logout_popup(ad);
}

static void _create_more_popup(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it;
	Evas_Object *ctxpopup;
	appdata_s *ad = data;

	if (!ad) {
			LOGE("ad is NULL");
			return;
	}

	if (ad->current_app_state != TG_SETTINGS_SCREEN_STATE) {
		return;
	}

	ctxpopup = elm_ctxpopup_add(ad->nf);
	elm_object_style_set(ctxpopup, "more/default");
	elm_ctxpopup_auto_hide_disabled_set(ctxpopup, EINA_TRUE);
	eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_BACK, eext_ctxpopup_back_cb, NULL);
	eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_MORE, eext_ctxpopup_back_cb, NULL);
	evas_object_event_callback_add(ctxpopup, EVAS_CALLBACK_DEL, _ctxpopup_del_cb, ad);

	evas_object_smart_callback_add(ctxpopup, "dismissed", _ctxpopup_dismiss_cb, ad);
	evas_object_smart_callback_add(ad->win, "rotation,changed", _more_popup_rotate, ad);

	it = elm_ctxpopup_item_append(ctxpopup, i18n_get_text("IDS_TGRAM_OPT_SET_PROFILE_PICTURE_ABB"), NULL, ctxpopup_profile_select_cb, ad);
	it = elm_ctxpopup_item_append(ctxpopup, i18n_get_text("IDS_TGRAM_OPT_EDIT_NAME"), NULL, ctxpopup_edit_name_select_cb, ad);
	it = elm_ctxpopup_item_append(ctxpopup, i18n_get_text("IDS_TGRAM_OPT_LOG_OUT"), NULL, ctxpopup_logout_select_cb, ad);
	//elm_object_item_domain_text_translatable_set(it, SETTING_PACKAGE, EINA_TRUE);
	elm_ctxpopup_direction_priority_set(ctxpopup, ELM_CTXPOPUP_DIRECTION_UP, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN);

	if (ad->menu_popup) {
		evas_object_del(ad->menu_popup);
	}

	ad->menu_popup = ctxpopup;

	_more_popup_rotate(ad, NULL, NULL);

	evas_object_show(ctxpopup);

}

static Eina_Bool _pop_cb(void *data, Elm_Object_Item *it)
{
	appdata_s* ad = data;

	if (!ad) {
		LOGE("ad is NULL");
		return EINA_FALSE;
	}

	eext_object_event_callback_del(ad->nf, EEXT_CALLBACK_MORE, _create_more_popup);

	return EINA_TRUE;
}

void refresh_settings_screen(appdata_s* ad)
{
	if (!ad)
		return;
	Evas_Object *list = evas_object_data_get(ad->nf, "settings_list");
	if (list) {
		elm_genlist_realized_items_update(list);
	}
}

void launch_settings_screen(appdata_s* ad)
{
	if (!ad) {
		return;
	}

	ad->current_app_state = TG_SETTINGS_SCREEN_STATE;

	if (!ad->current_user_data) {
		load_registered_user_data(ad);
	}

	static Elm_Genlist_Item_Class itc;
	Evas_Object *list = elm_genlist_add(ad->nf);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(list);

	evas_object_data_set(list, "app_data", ad);

	evas_object_data_set(ad->nf, "settings_list", list);

	itc.item_style = "type1";
	itc.func.text_get = _text_requested_cb;
	itc.func.content_get = _content_requested_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	elm_genlist_item_append(list, &itc, (void*) 0, NULL, ELM_GENLIST_ITEM_NONE, on_camera_button_clicked, (void*) ad);
	elm_genlist_item_append(list, &itc, (void*) 1, NULL, ELM_GENLIST_ITEM_NONE, on_settings_info_item_clicked, (void*)1);

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, i18n_get_text("IDS_TGRAM_OPT_SETTINGS"), NULL, NULL, list, NULL);

	elm_naviframe_item_pop_cb_set(navi_item, _pop_cb, ad);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_MORE, _create_more_popup, ad);
}

