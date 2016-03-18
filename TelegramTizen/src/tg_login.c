/*
    This file is part of Telegram application for tizen

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "tg_login.h"
#include "server_requests.h"
#include "tg_first_registration.h"
#include "tg_registration.h"

static void on_code_change_enable_ok_button(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object* done_btn = evas_object_data_get(ad->nf, "code_done_btn");
	char buf[256];
	snprintf(buf, sizeof(buf), "%s", elm_object_text_get(obj));

	if (strlen(buf) == MAX_CODE_LENGTH)
		elm_object_disabled_set(done_btn, EINA_FALSE);
	else
		elm_object_disabled_set(done_btn, EINA_TRUE);
}

static void on_naviframe_cancel_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	if (!ad)
		return;

	send_request_for_restart_server(ad, ad->service_client);

	Ecore_Timer* timer = evas_object_data_get(ad->nf, "code_timer");
	if (timer)
		ecore_timer_del(timer);

	elm_naviframe_item_pop(ad->nf);
	ad->current_app_state = TG_REGISTRATION_STATE;
	launch_registration_cb(ad);
}

static void on_code_entry_done_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
#if 1
	Evas_Object* entry = evas_object_data_get(ad->nf, "code_number_entry");

	if (entry) {
		char *tval = strdup(elm_object_text_get(entry));
		char *val = trim(tval);
		free(tval);
		if (!val || strlen(val) <= 0 || numbers_only(val) == 0) {
			show_toast(ad, "Enter a valid code");
			free(val);
			return;
		}
		Ecore_Timer *timer = evas_object_data_get(ad->nf, "code_timer");
		if (timer)
			ecore_timer_del(timer);

		send_request_for_validation(ad, ad->service_client, val);
		show_loading_popup(ad);
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
/*
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
*/
static Eina_Bool on_code_timer_cb(void* data)
{
	appdata_s* ad = data;
	(ad->timer_value)--;

	int cur_time_in_secs = ad->timer_value;
	if (cur_time_in_secs <= 0) {
		Ecore_Timer* timer = evas_object_data_get(ad->nf, "code_timer");
		ecore_timer_del(timer);

		char temp_txt[512];
		snprintf(temp_txt, sizeof(temp_txt), i18n_get_text("IDS_TGRAM_BODY_TELEGRAM_WILL_CALL_IN_P1SD_CP2SD"), 0, 0);
		Evas_Object *layout = evas_object_data_get(ad->nf, "layout");
		elm_object_part_text_set(layout, "timer_text", temp_txt);
		send_request_for_registration(ad, ad->service_client, ad->phone_number, EINA_FALSE);
		return ECORE_CALLBACK_CANCEL;
	}

	int seconds = cur_time_in_secs % 60;
	int minutes = (cur_time_in_secs / 60) % 60;

	char temp_txt[512];
	snprintf(temp_txt, sizeof(temp_txt), i18n_get_text("IDS_TGRAM_BODY_TELEGRAM_WILL_CALL_IN_P1SD_CP2SD"), minutes, seconds);

	Evas_Object *layout = evas_object_data_get(ad->nf, "layout");
	elm_object_part_text_set(layout, "timer_text", temp_txt);

	if (ad->timer_value == 0 || (seconds == 0 && minutes == 0)) {

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
	if (!ad)
		return;

	ad->current_app_state = TG_LOGIN_STATE;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "code_check_screen");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);

	char* info_txt = NULL;

	if (ad->phone_number) {
		info_txt = (char *)malloc(strlen(ad->phone_number) + 1);
		strcat(info_txt, ad->phone_number);
	}

	elm_object_part_text_set(layout, "phone_status", info_txt);
	elm_object_part_text_set(layout, "inform", i18n_get_text("IDS_TGRAM_BODY_A_VERIFICATION_CODE_HAS_BEEN_SENT_MSG"));

	Evas_Object* code_number_entry = elm_entry_add(layout);
	elm_object_part_text_set(code_number_entry, "elm.guide", i18n_get_text("IDS_TGRAM_BODY_CODE"));
	elm_entry_cursor_end_set(code_number_entry);
	evas_object_size_hint_weight_set(code_number_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(code_number_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(code_number_entry,  EINA_TRUE);
	elm_entry_scrollable_set(code_number_entry, EINA_FALSE);
	elm_entry_cnp_mode_set(code_number_entry, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(code_number_entry, EINA_TRUE);
	elm_entry_text_style_user_push(code_number_entry, "DEFAULT='color=#000000'");
	evas_object_show(code_number_entry);
	elm_object_part_content_set(layout, "code_entry", code_number_entry);

	evas_object_data_set(ad->nf, "code_number_entry", (void*)code_number_entry);

	limit_filter_data.max_char_count = MAX_CODE_LENGTH;

	elm_entry_markup_filter_append(code_number_entry, elm_entry_filter_limit_size, &limit_filter_data);
	elm_entry_markup_filter_append(code_number_entry, elm_entry_filter_accept_set, &accept_set);

	Ecore_IMF_Context *imf_context;
	imf_context = elm_entry_imf_context_get(code_number_entry);
	ecore_imf_context_input_panel_layout_set(imf_context, ECORE_IMF_INPUT_PANEL_LAYOUT_PHONENUMBER);
	evas_object_smart_callback_add(code_number_entry, "changed", on_code_change_enable_ok_button, ad);

	char temp_timer_txt[512];
	snprintf(temp_timer_txt, sizeof(temp_timer_txt), i18n_get_text("IDS_TGRAM_BODY_TELEGRAM_WILL_CALL_IN_P1SD_CP2SD"), 2, 00);
	elm_object_part_text_set(layout, "timer_text", temp_timer_txt);

	evas_object_data_set(ad->nf, "layout", layout);

	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, i18n_get_text("IDS_TGRAM_HEADER_ENTER_CODE_ABB"), NULL, NULL, scroller, NULL);

	Evas_Object *done_btn = elm_button_add(ad->nf);
	elm_object_style_set(done_btn, "naviframe/title_right");
	elm_object_text_set(done_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_DONE_ABB"));
	evas_object_smart_callback_add(done_btn, "clicked", on_code_entry_done_clicked, ad);

	Evas_Object *cancel_btn = elm_button_add(ad->nf);
	elm_object_style_set(cancel_btn, "naviframe/title_left");
	elm_object_text_set(cancel_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_CANCEL_ABB"));
	evas_object_smart_callback_add(cancel_btn, "clicked", on_naviframe_cancel_clicked, ad);

	elm_object_item_part_content_set(navi_item, "title_right_btn", done_btn);
	elm_object_item_part_content_set(navi_item, "title_left_btn", cancel_btn);

	evas_object_data_set(ad->nf, "code_done_btn", (void*)done_btn);
	elm_object_disabled_set(done_btn, EINA_TRUE);

	elm_object_focus_set(code_number_entry, EINA_TRUE);

	start_timer(ad);

}
