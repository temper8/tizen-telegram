/**
 * @file tg_registration.c
 * @date May 19, 2015
 * @author sandeep
 */

#include "tg_registration.h"
#include "tg_db_manager.h"
#include "server_requests.h"
#include "tg_login.h"
#include "device_contacts_manager.h"
#include "contacts-db-utils.h"

static void on_text_change_enable_ok_button(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object* country_name_btn = evas_object_data_get(ad->nf, "country_name_btn");
	Evas_Object* done_btn = evas_object_data_get(ad->nf, "reg_done_btn");
	char buf[256] = {'\0',};
	snprintf(buf, sizeof(buf), "%s", elm_object_text_get(obj));

	char code_buf[256] = {'\0',};
	snprintf(code_buf, sizeof(code_buf), "%s", elm_object_text_get(country_name_btn));

	if (strlen(buf) == MAX_NUM_LENGTH && strcasecmp(code_buf, "Select your country") != 0) {
		elm_object_disabled_set(done_btn, EINA_FALSE);
	} else {
		elm_object_disabled_set(done_btn, EINA_TRUE);
	}

}

static void on_naviframe_done_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object* country_name_btn = evas_object_data_get(ad->nf, "country_name_btn");
	Evas_Object* country_code_btn = evas_object_data_get(ad->nf, "country_code_btn");
	Evas_Object* pn_number_entry = evas_object_data_get(ad->nf, "pn_number_entry");


	char* phone_num = elm_entry_markup_to_utf8(elm_object_text_get(pn_number_entry));
	char* cunt_code = elm_entry_markup_to_utf8(elm_object_text_get(country_code_btn));


	char code_buf[256] = {'\0',};
	snprintf(code_buf, sizeof(code_buf), "%s", elm_object_text_get(country_name_btn));

	char country_code[256] = {'\0',};
	snprintf(country_code, sizeof(country_code), "%s", elm_object_text_get(country_code_btn));

	if (strlen(phone_num) == MAX_NUM_LENGTH && strcasecmp(code_buf, "Select your country") != 0) {
		char phone_number[256];
		strcpy(phone_number, cunt_code);
		strcat(phone_number, phone_num);
		ad->phone_number = strdup(phone_number);
		send_request_for_registration(ad->service_client, ad->phone_number, EINA_TRUE);
	} else {

	}

	free(phone_num);
	free(cunt_code);

}

static void on_naviframe_cancel_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
#if 0
	elm_win_lower(ad->win);
	elm_exit();
#else
	elm_naviframe_item_pop(ad->nf);
	launch_login_cb(ad);
#endif
}

static void country_name_popup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(obj);
}

static void country_name_popup_item_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object* country_name_btn = evas_object_data_get(ad->nf, "country_name_btn");
	Evas_Object* country_code_btn = evas_object_data_get(ad->nf, "country_code_btn");
	Evas_Object* pn_number_entry = evas_object_data_get(ad->nf, "pn_number_entry");

	const char *label = elm_object_item_text_get((Elm_Object_Item *)event_info);
	if (label) {
		elm_object_text_set(country_name_btn, label);

		for (int i = 0 ; i < SIZE_CODE; i++) {
			if(strcasecmp(phone_codes[i][0], label) == 0) {
				char temp_str[50];
				sprintf(temp_str, "<align=center>%s<align>", phone_codes[i][1]);
				elm_object_text_set(country_code_btn, temp_str);

				Evas_Object* done_btn = evas_object_data_get(ad->nf, "reg_done_btn");
				char buf[256] = {'\0',};
				snprintf(buf, sizeof(buf), "%s", elm_object_text_get(pn_number_entry));

				if (strlen(buf) == MAX_NUM_LENGTH && strcasecmp(label, "Select your country") != 0) {
					elm_object_disabled_set(done_btn, EINA_FALSE);
				} else {
					elm_object_disabled_set(done_btn, EINA_TRUE);
				}

				break;
			}
		}
	}

	evas_object_del(obj);
}

static void move_dropdown(Evas_Object *ctxpopup, Evas_Object *btn)
{
	Evas_Coord x, y, w , h;
	evas_object_geometry_get(btn, &x, &y, &w, &h);
	evas_object_move(ctxpopup, x + (w / 2), y + h);
}

static void on_country_name_list_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;

	Evas_Object* country_name_popup = evas_object_data_get(ad->nf, "country_name_popup");

	if (country_name_popup) {
		evas_object_del(country_name_popup);
	}

	country_name_popup = elm_ctxpopup_add(ad->nf);
	elm_object_style_set(country_name_popup, "dropdown/list");
	eext_object_event_callback_add(country_name_popup, EEXT_CALLBACK_BACK, eext_ctxpopup_back_cb, NULL);
	evas_object_smart_callback_add(country_name_popup,"dismissed", country_name_popup_dismissed_cb, NULL);


	for (int i = 0 ; i < SIZE_CODE; i++) {
		elm_ctxpopup_item_append(country_name_popup, phone_codes[i][0], NULL, country_name_popup_item_select_cb, ad);
	}

	elm_ctxpopup_direction_priority_set(country_name_popup, ELM_CTXPOPUP_DIRECTION_DOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN);

	move_dropdown(country_name_popup, obj);
	evas_object_show(country_name_popup);

	evas_object_data_set(ad->nf, "country_name_popup", country_name_popup);
}

void launch_registration_cb(appdata_s* ad)
{
	if (!ad) {
		return;
	}

	ad->current_app_state = TG_REGISTRATION_STATE;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "registration_screen");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);

	Evas_Object* country_name_btn = elm_button_add(layout);
	elm_object_text_set(country_name_btn, "Select your country");
	elm_object_style_set(country_name_btn, "dropdown");
	evas_object_size_hint_weight_set(country_name_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(country_name_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(country_name_btn, "clicked", on_country_name_list_clicked, ad);
	elm_object_part_content_set(layout, "country_name", country_name_btn);

	evas_object_data_set(ad->nf, "country_name_btn", (void*)country_name_btn);


	Evas_Object* country_code_btn = elm_entry_add(layout);
	elm_object_text_set(country_code_btn, "<align=center>--<align>");
	evas_object_size_hint_weight_set(country_code_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(country_code_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(country_code_btn,  EINA_TRUE);
	elm_entry_editable_set(country_code_btn, EINA_FALSE);
	evas_object_show(country_code_btn);
	elm_object_part_content_set(layout, "country_code", country_code_btn);

	evas_object_data_set(ad->nf, "country_code_btn", (void*)country_code_btn);


	Evas_Object* pn_number_entry = elm_entry_add(layout);
	elm_object_part_text_set(pn_number_entry, "elm.guide", "Enter phone number");
	elm_entry_cursor_end_set(pn_number_entry);
	evas_object_size_hint_weight_set(pn_number_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(pn_number_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(pn_number_entry,  EINA_TRUE);
	elm_entry_scrollable_set (pn_number_entry, EINA_FALSE);
	elm_entry_cnp_mode_set(pn_number_entry, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(pn_number_entry, EINA_TRUE);
	elm_entry_text_style_user_push(pn_number_entry, "DEFAULT='color=#000000'");
	evas_object_show(pn_number_entry);
	elm_object_part_content_set(layout, "phone_number_entry", pn_number_entry);

	evas_object_data_set(ad->nf, "pn_number_entry", (void*)pn_number_entry);


	limit_filter_data.max_char_count = MAX_NUM_LENGTH;

	elm_entry_markup_filter_append(pn_number_entry, elm_entry_filter_limit_size, &limit_filter_data);
	//Set the entry field to accept only numbers
	elm_entry_markup_filter_append(pn_number_entry, elm_entry_filter_accept_set, &accept_set);

	Ecore_IMF_Context *imf_context;
	imf_context = elm_entry_imf_context_get(pn_number_entry);
	ecore_imf_context_input_panel_layout_set(imf_context, ECORE_IMF_INPUT_PANEL_LAYOUT_PHONENUMBER);
	//Enable OK button if no of chars has reached to 10 then
	evas_object_smart_callback_add(pn_number_entry, "changed", on_text_change_enable_ok_button, ad);


	Evas_Object* note_btn = elm_entry_add(layout);
	elm_object_text_set(note_btn, "<align=left>Please confirm your country code and enter your phone number.<align>");
	evas_object_size_hint_weight_set(note_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(note_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(note_btn,  EINA_FALSE);
	elm_entry_editable_set(note_btn, EINA_FALSE);
	elm_entry_line_wrap_set(note_btn, EINA_TRUE);
	evas_object_show(note_btn);
	elm_object_part_content_set(layout, "text_display", note_btn);


	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "Your phone", NULL, NULL, scroller, NULL);

	Evas_Object *cancel_btn = elm_button_add(ad->nf);
	elm_object_style_set(cancel_btn, "naviframe/title_icon");
	elm_object_text_set(cancel_btn, "Cancel");
	evas_object_smart_callback_add(cancel_btn, "clicked", on_naviframe_cancel_clicked, ad);

	Evas_Object *done_btn = elm_button_add(ad->nf);
	elm_object_style_set(done_btn, "naviframe/title_icon");
	elm_object_text_set(done_btn, "Done");
	evas_object_smart_callback_add(done_btn, "clicked", on_naviframe_done_clicked, ad);


	elm_object_item_part_content_set(navi_item, "title_left_btn", cancel_btn);
	elm_object_item_part_content_set(navi_item, "title_right_btn", done_btn);

	evas_object_data_set(ad->nf, "reg_done_btn", (void*)done_btn);
	evas_object_data_set(ad->nf, "reg_cancel_btn", (void*)cancel_btn);
	elm_object_disabled_set(done_btn, EINA_TRUE);
}
