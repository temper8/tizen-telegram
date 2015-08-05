/*
 * tg_registration.c
 *
 *  Created on: May 19, 2015
 *      Author: sandeep
 */

#include "tg_registration.h"
#include "tg_db_manager.h"
#include "server_requests.h"

#include "device_contacts_manager.h"
#include "contacts-db-utils.h"

void _send_code_sms_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	Evas_Object* entry = evas_object_data_get(obj, "entry_obj");
	if(entry) {
		char* tval = strdup(elm_object_text_get(entry));

		char* val = trim(tval);
		free(tval);
		if(!val || strlen(val) <= 0 || numbers_only(val) == 0) {
			show_toast(ad, "Enter a valid phone number");
			free(val);
			return;
		}
		ad->phone_number = strdup(val);
		// request service for login
		send_request_for_registration(ad->service_client, ad->phone_number, EINA_TRUE);
	}
}

static void _send_code_call_cb(void *data, Evas_Object *obj, void *event)
{
	//appdata_reg_s* ad_reg = data;
}

void launch_registration_cb(void *data)
{

	appdata_s* ad = data;
	char edj_path[PATH_MAX] = {0, };

	ad->current_app_state = TG_REGISTRATION_STATE;

	Evas_Coord w, h;
	elm_win_screen_size_get(ad->win, NULL, NULL, &w, &h);
	Evas_Object* layout = elm_layout_add(ad->win);
	app_get_resource(EDJ_REG_FILE, edj_path, (int)PATH_MAX);
	elm_layout_file_set(layout, edj_path, "login");

	Evas_Object* box = elm_box_add(layout);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_min_set(box, w, h - 200);
	elm_object_part_content_set(layout, "bg", box);
	elm_object_part_text_set(layout, "label", "Enter Phone Number");

	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, 0.0);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);

	Evas_Object* entry = elm_entry_add(layout);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, 0);
	elm_entry_input_panel_layout_set(entry,ELM_INPUT_PANEL_LAYOUT_NUMBERONLY);
	elm_object_part_content_set(layout, "entry", entry);

	Evas_Object* sms_btn = elm_button_add(layout);
	elm_object_text_set(sms_btn, "Request code via SMS");
	evas_object_size_hint_weight_set(sms_btn, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(sms_btn, EVAS_HINT_FILL, 0);
	elm_object_part_content_set(layout, "sms_btn", sms_btn);
	evas_object_data_set(sms_btn, "app_data", ad);
	evas_object_data_set(sms_btn, "entry_obj", entry);
	evas_object_smart_callback_add(sms_btn, "clicked", _send_code_sms_cb, ad);

	Evas_Object* call_btn = elm_button_add(layout);
	elm_object_text_set(call_btn, "Request code via CALL");
	evas_object_size_hint_weight_set(call_btn, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(call_btn, EVAS_HINT_FILL, 0);
	elm_object_part_content_set(layout, "call_btn", call_btn);
	evas_object_data_set(call_btn, "app_data", ad);
	evas_object_data_set(call_btn, "entry_obj", entry);
	evas_object_smart_callback_add(call_btn, "clicked", _send_code_call_cb, ad);
	elm_naviframe_item_push(ad->nf, "Telegram", NULL, NULL, layout, NULL);
}
