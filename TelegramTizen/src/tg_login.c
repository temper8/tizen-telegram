/*
 * tg_login.c
 *
 *  Created on: May 20, 2015
 *      Author: sandeep
 */

#include "tg_login.h"
#include "server_requests.h"

static void _send_code_ok_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	Evas_Object* entry = evas_object_data_get(obj, "entry_obj");
	if(entry) {
		char* tval = strdup(elm_object_text_get(entry));
		char* val = trim(tval);
		free(tval);
		if (!val || strlen(val) <= 0 || numbers_only(val) == 0) {
			show_toast(ad, "Enter a valid code");
			free(val);
			return;
		}
		send_request_for_validation(ad->service_client, val);
	}
}

static void _send_code_sms_login_cb(void *data, Evas_Object *obj, void *event_info)
{
	// to do
}

static void _send_code_call_login_cb(void *data, Evas_Object *obj, void *event)
{
	// to do
}


void launch_login_cb(void *data)
{
	appdata_s* ad = data;

	char edj_path[PATH_MAX] = {0, };

	Evas_Coord w, h;
	ad->current_app_state = TG_LOGIN_STATE;


	elm_win_screen_size_get(ad->win, NULL, NULL, &w, &h);

	Evas_Object* layout = elm_layout_add(ad->win);
	app_get_resource(EDJ_LOGIN_FILE, edj_path, (int)PATH_MAX);

	elm_layout_file_set(layout, edj_path, "login");

	Evas_Object* box = elm_box_add(layout);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_min_set(box, w, h - 200);

	elm_object_part_content_set(layout, "bg", box); /* To expands layout */

	elm_object_part_text_set(layout, "label", "Enter Telegram Code");

	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);

	Evas_Object* entry = elm_entry_add(layout);
	elm_entry_input_panel_layout_set(entry,ELM_INPUT_PANEL_LAYOUT_NUMBERONLY);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, 0);
	elm_object_part_content_set(layout, "entry", entry);


	Evas_Object* ok_btn = elm_button_add(layout);
	elm_object_text_set(ok_btn, "OK");
	evas_object_size_hint_weight_set(ok_btn, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(ok_btn, EVAS_HINT_FILL, 0);
	elm_object_part_content_set(layout, "ok_btn", ok_btn);
	evas_object_data_set(ok_btn, "app_data", ad);
	evas_object_data_set(ok_btn, "entry_obj", entry);
	evas_object_smart_callback_add(ok_btn, "clicked", _send_code_ok_cb, ad);

	Evas_Object* sms_btn = elm_button_add(layout);
	elm_object_text_set(sms_btn, "Request new code via SMS");
	evas_object_size_hint_weight_set(sms_btn, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(sms_btn, EVAS_HINT_FILL, 0);
	elm_object_part_content_set(layout, "sms_btn", sms_btn);
	evas_object_data_set(sms_btn, "app_data", ad);
	evas_object_data_set(sms_btn, "entry_obj", entry);
	evas_object_smart_callback_add(sms_btn, "clicked", _send_code_sms_login_cb, ad);

	Evas_Object* call_btn = elm_button_add(layout);
	elm_object_text_set(call_btn, "Request new code via CALL");
	evas_object_size_hint_weight_set(call_btn, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(call_btn, EVAS_HINT_FILL, 0);
	elm_object_part_content_set(layout, "call_btn", call_btn);
	evas_object_data_set(call_btn, "app_data", ad);
	evas_object_data_set(call_btn, "entry_obj", entry);
	evas_object_smart_callback_add(call_btn, "clicked", _send_code_call_login_cb, ad);

	elm_naviframe_item_push(ad->nf, "Telegram", NULL, NULL, layout, NULL);
}
