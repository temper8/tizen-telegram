/*
 * tg_first_registration.c
 *
 *  Created on: Jul 6, 2015
 *      Author: sandeep
 */

#include "tg_first_registration.h"
#include "server_requests.h"

static void on_submit_button_clicked(void *data, Evas_Object *btn, void *ev)
{
	appdata_s* ad = evas_object_data_get(btn, "app_data");
	Evas_Object* first_name_entry = evas_object_data_get(btn, "first_name_entry");
	Evas_Object* last_name_entry = evas_object_data_get(btn, "last_name_entry");

	const char* first_name = elm_object_text_get(first_name_entry);
	if (!first_name) {
		show_toast(ad, "Enter first name");
		return;
	}

	const char* last_name = elm_object_text_get(last_name_entry);
	if (!last_name) {
		last_name = "";
	}
	send_request_for_profile_registration(ad->service_client, first_name, last_name);
}


void launch_first_registration_cb(void *data)
{
	appdata_s* ad = data;

	char edj_path[PATH_MAX] = {0, };

	ad->current_app_state = TG_PROFILE_REGISTRATION_STATE;
	ad->is_first_time_registration = EINA_TRUE;

	Evas_Coord w, h;
	elm_win_screen_size_get(ad->win, NULL, NULL, &w, &h);
	h -= 130;

	// creating main layout
	Evas_Object* main_layout = elm_layout_add(ad->win);
	app_get_resource(EDJ_CHAT_CONV_FILE, edj_path, (int)PATH_MAX);
	elm_layout_file_set(main_layout, edj_path, "chat_first_registration");
	evas_object_size_hint_min_set(main_layout, w, h);

	Evas_Object* first_name_lbl = elm_label_add(main_layout);
	elm_object_text_set(first_name_lbl, "Enter first name:");
	evas_object_show(first_name_lbl);
	elm_object_part_content_set(main_layout, "swallow.first_name_label", first_name_lbl);

	Evas_Object* first_name_entry = elm_entry_add(main_layout);
	elm_entry_single_line_set(first_name_entry, EINA_TRUE);
	evas_object_show(first_name_entry);
	elm_object_part_content_set(main_layout, "swallow.first_name_entry", first_name_entry);


	Evas_Object* last_name_lbl = elm_label_add(main_layout);
	elm_object_text_set(last_name_lbl, "Enter last name:");
	evas_object_show(last_name_lbl);
	elm_object_part_content_set(main_layout, "swallow.last_name_label", last_name_lbl);

	Evas_Object* last_name_entry = elm_entry_add(main_layout);
	elm_entry_single_line_set(last_name_entry, EINA_TRUE);
	evas_object_show(last_name_entry);
	elm_object_part_content_set(main_layout, "swallow.last_name_entry", last_name_entry);

	Evas_Object* submit_btn = elm_button_add(main_layout);
	elm_object_text_set(submit_btn, "Submit");
	evas_object_show(submit_btn);

	evas_object_data_set(submit_btn, "app_data", ad);
	evas_object_data_set(submit_btn, "first_name_entry", first_name_entry);
	evas_object_data_set(submit_btn, "last_name_entry", last_name_entry);

	elm_object_part_content_set(main_layout, "swallow.submit_btn", submit_btn);

	evas_object_smart_callback_add(submit_btn, "clicked", on_submit_button_clicked, ad);

	elm_naviframe_item_push(ad->nf, "Telegram", NULL, NULL, main_layout, NULL);
}



