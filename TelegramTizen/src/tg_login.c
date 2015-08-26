/*
 * tg_login.c
 *
 *  Created on: May 20, 2015
 *      Author: sandeep
 */

#include "tg_login.h"
#include "server_requests.h"
#include "tg_first_registration.h"

#define TIMER_TEXT "We will call in "

#define CODE_INFO_TEXT "We've sent an SMS with an activation code to your phone "


static void on_code_change_enable_ok_button(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object* done_btn = evas_object_data_get(ad->nf, "code_done_btn");
	char buf[256] = {'\0',};
	snprintf(buf, sizeof(buf), "%s", elm_object_text_get(obj));

	if (strlen(buf) == MAX_CODE_LENGTH) {
		elm_object_disabled_set(done_btn, EINA_FALSE);
	} else {
		elm_object_disabled_set(done_btn, EINA_TRUE);
	}

}

static void on_code_entry_done_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
#if 1
	Evas_Object* entry = evas_object_data_get(ad->nf, "code_number_entry");

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
#else
	if (ad->timer_value > 0) {
		Ecore_Timer* timer = evas_object_data_get(ad->nf, "code_timer");
		if (timer)
			ecore_timer_del(timer);
	}
	elm_naviframe_item_pop(ad->nf);
	launch_first_registration_cb(ad);
#endif
}

static void on_wrong_num_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	if (ad->timer_value > 0) {
		Ecore_Timer* timer = evas_object_data_get(ad->nf, "code_timer");
		ecore_timer_del(timer);
	}
	elm_naviframe_item_pop(ad->nf);
	ad->current_app_state = TG_REGISTRATION_STATE;
}

static Eina_Bool on_code_timer_cb(void* data)
{
	appdata_s* ad = data;
	(ad->timer_value)--;

	int cur_time_in_secs = ad->timer_value;

	Evas_Object* info_timer = evas_object_data_get(ad->nf, "info_timer");

	int seconds = cur_time_in_secs % 60;
	int minutes = (cur_time_in_secs / 60) % 60;

	char sec_str[10];
	char min_str[10];

	sprintf(min_str, "%d", minutes);
	sprintf(sec_str, "%d", seconds);

	char* timer_text = (char*)malloc(strlen(TIMER_TEXT) + strlen(min_str) + strlen(":") + strlen(sec_str) + 1);
	strcpy(timer_text, TIMER_TEXT);
	strcat(timer_text, min_str);
	strcat(timer_text, ":");
	strcat(timer_text, sec_str);

	char temp_txt[512] = {0,};
	snprintf(temp_txt, sizeof(temp_txt), "<font=Tizen:style=Regular color=#666362 align=left><font_size=32>%s</font_size></font>", timer_text);

	elm_object_text_set(info_timer, temp_txt);

	free(timer_text);

	if (ad->timer_value == 0 || (seconds == 0 && minutes == 0) ) {

		Ecore_Timer* timer = evas_object_data_get(ad->nf, "code_timer");
		ecore_timer_del(timer);

		return ECORE_CALLBACK_CANCEL;
	}
	return ECORE_CALLBACK_RENEW;
}

void start_timer(appdata_s* ad)
{
	ad->timer_value = 120;
	Ecore_Timer* timer = ecore_timer_add(1.0f, on_code_timer_cb, ad);
	evas_object_data_set(ad->nf, "code_timer", (void*)timer);
}

void launch_login_cb(appdata_s* ad)
{

	if (!ad) {
		return;
	}

	ad->current_app_state = TG_LOGIN_STATE;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "code_check_screen");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);

	char* info_txt = NULL;

	if (ad->phone_number) {
		info_txt = (char*)malloc(strlen(CODE_INFO_TEXT) + strlen(ad->phone_number) + 1);
		strcpy(info_txt, CODE_INFO_TEXT);
		strcat(info_txt, ad->phone_number);
	} else {
		info_txt = (char*)malloc(strlen(CODE_INFO_TEXT) + 1);
		strcpy(info_txt, CODE_INFO_TEXT);
	}

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
	elm_object_part_content_set(layout, "phone_status", info_btn);


	Evas_Object* code_number_entry = elm_entry_add(layout);
	elm_object_part_text_set(code_number_entry, "elm.guide", "<font=Tizen:style=Regular color=#666362 align=left><font_size=36>Code</font_size></font>");
	elm_entry_cursor_end_set(code_number_entry);
	evas_object_size_hint_weight_set(code_number_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(code_number_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(code_number_entry,  EINA_TRUE);
	elm_entry_scrollable_set (code_number_entry, EINA_FALSE);
	elm_entry_cnp_mode_set(code_number_entry, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(code_number_entry, EINA_TRUE);
	elm_entry_text_style_user_push(code_number_entry, "DEFAULT='color=#000000'");
	evas_object_show(code_number_entry);
	elm_object_part_content_set(layout, "code_entry", code_number_entry);

	evas_object_data_set(ad->nf, "code_number_entry", (void*)code_number_entry);


	limit_filter_data.max_char_count = MAX_CODE_LENGTH;

	elm_entry_markup_filter_append(code_number_entry, elm_entry_filter_limit_size, &limit_filter_data);
	//Set the entry field to accept only numbers
	elm_entry_markup_filter_append(code_number_entry, elm_entry_filter_accept_set, &accept_set);

	Ecore_IMF_Context *imf_context;
	imf_context = elm_entry_imf_context_get(code_number_entry);
	ecore_imf_context_input_panel_layout_set(imf_context, ECORE_IMF_INPUT_PANEL_LAYOUT_PHONENUMBER);
	//Enable OK button if no of chars has reached to 10 then
	evas_object_smart_callback_add(code_number_entry, "changed", on_code_change_enable_ok_button, ad);


	char temp_timer_txt[512] = {0,};
	snprintf(temp_timer_txt, sizeof(temp_timer_txt), "<font=Tizen:style=Regular color=#666362 align=left><font_size=32>%s2::00</font_size></font>", TIMER_TEXT);


	Evas_Object* info_timer = elm_entry_add(layout);
	elm_object_text_set(info_timer, temp_timer_txt);
	evas_object_size_hint_weight_set(info_timer, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(info_timer, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(info_timer,  EINA_FALSE);
	elm_entry_editable_set(info_timer, EINA_FALSE);
	elm_entry_line_wrap_set(info_timer, EINA_TRUE);
	evas_object_show(info_timer);
	elm_object_part_content_set(layout, "timer_text", info_timer);

	evas_object_data_set(ad->nf, "info_timer", (void*)info_timer);


	Evas_Object* wrong_num_btn = elm_entry_add(layout);
	elm_entry_editable_set(wrong_num_btn, EINA_FALSE);
	elm_object_text_set(wrong_num_btn, "<font=Tizen:style=Regular color=#0000ff align=left><font_size=32>Wrong number?</font_size></font>");
	evas_object_size_hint_weight_set(wrong_num_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(wrong_num_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(wrong_num_btn, "clicked", on_wrong_num_clicked, ad);
	elm_object_part_content_set(layout, "wrong_num_btn", wrong_num_btn);


	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "Your code", NULL, NULL, scroller, NULL);

    Evas_Object *done_btn = elm_button_add(ad->nf);
    elm_object_style_set(done_btn, "naviframe/title_icon");
    elm_object_text_set(done_btn, "Done");
    evas_object_smart_callback_add(done_btn, "clicked", on_code_entry_done_clicked, ad);


    Evas_Object *cancel_btn = elm_label_add(ad->nf);
    elm_object_style_set(cancel_btn, "naviframe/title_icon");



    elm_object_item_part_content_set(navi_item, "title_right_btn", done_btn);
    elm_object_item_part_content_set(navi_item, "title_left_btn", cancel_btn);

    evas_object_data_set(ad->nf, "code_done_btn", (void*)done_btn);
    elm_object_disabled_set(done_btn, EINA_TRUE);

    start_timer(ad);

}
