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

#include "tg_registration.h"
#include "tg_db_manager.h"
#include "server_requests.h"
#include "tg_login.h"
#include "tg_country_selection_view.h"

static void on_text_change_enable_ok_button(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object* country_name_btn = evas_object_data_get(ad->nf, "country_name_btn");
	Evas_Object* done_btn = evas_object_data_get(ad->nf, "reg_done_btn");
	Evas_Object *layout = NULL;
	char buf[256] = {'\0',};
	char code_buf[256] = {'\0',};

	snprintf(buf, sizeof(buf), "%s", elm_object_text_get(obj));
	snprintf(code_buf, sizeof(code_buf), "%s", elm_object_text_get(country_name_btn));

	layout = evas_object_data_get(ad->nf, "regi,layout");
	if (strcasecmp(buf, "") != 0) {
		elm_object_signal_emit(layout, "show", "delete");
	} else {
		elm_object_signal_emit(layout, "hide", "delete");
	}

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
	char country_code[256] = {'\0',};

	snprintf(code_buf, sizeof(code_buf), "%s", elm_object_text_get(country_name_btn));
	snprintf(country_code, sizeof(country_code), "%s", elm_object_text_get(country_code_btn));

	if (strlen(phone_num) == MAX_NUM_LENGTH && strcasecmp(code_buf, "Select your country") != 0 && ad->is_server_ready) {
		char phone_number[256];
		snprintf(phone_number, sizeof(phone_number), "%s%s", cunt_code, phone_num);
		ad->phone_number = strdup(phone_number);
		show_loading_popup(ad);
		send_request_for_registration(ad, ad->service_client, ad->phone_number, EINA_TRUE);
	} else {
		if (strlen(phone_num) == MAX_NUM_LENGTH)
		   show_toast(ad, i18n_get_text("IDS_NFC_POP_INITIALISING_PLEASE_WAIT_ING"));
	}

	free(phone_num);
	free(cunt_code);
}

static void on_naviframe_cancel_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	elm_win_lower(ad->win);
	elm_exit();
}

void country_name_selected_cb(appdata_s *ad, Eina_List *count_name_list, Eina_List *country_code_list)
{
	int country_code_idx;
	Evas_Object* country_name_btn;
	Evas_Object* country_code_btn;
	Evas_Object* pn_number_entry;
	Evas_Object* done_btn;
	char *country_name;
	char *country_code;
	char temp_str[32];
	const char *number_text;

	if (!count_name_list || !country_code_list)
		return;

	country_name_btn = evas_object_data_get(ad->nf, "country_name_btn");
	country_code_btn = evas_object_data_get(ad->nf, "country_code_btn");
	pn_number_entry = evas_object_data_get(ad->nf, "pn_number_entry");
	country_name = eina_list_nth(count_name_list, ad->selected_country_id);

	if (ad->country_codes_list != country_code_list) {
		country_code_idx = (int)eina_list_nth(country_code_list, ad->selected_country_id);
		country_code = eina_list_nth(ad->country_codes_list, country_code_idx);
	} else {
		country_code = eina_list_nth(country_code_list, ad->selected_country_id);
	}

	elm_object_text_set(country_name_btn, country_name);

	snprintf(temp_str, sizeof(temp_str), "<align=center>%s<align>", country_code);
	elm_object_text_set(country_code_btn, temp_str);

	done_btn = evas_object_data_get(ad->nf, "reg_done_btn");
	number_text = elm_object_text_get(pn_number_entry);

	if (number_text && strlen(number_text) == MAX_NUM_LENGTH) {
		elm_object_disabled_set(done_btn, EINA_FALSE);
	} else {
		elm_object_disabled_set(done_btn, EINA_TRUE);
	}
}

static void delete_btn_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *pn_number_entry = data;
	elm_object_text_set(pn_number_entry, "");
}

static void on_country_name_list_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	launch_country_selection_view(ad);
}

void launch_registration_cb(appdata_s *ad)
{
	if (!ad)
		return;

	ad->current_app_state = TG_REGISTRATION_STATE;
	eina_list_free(ad->country_codes_list);
	eina_list_free(ad->country_names_list);
	free(ad->country_code_buffer);

	load_list_of_countries(ad);

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "registration_screen");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);
	evas_object_data_set(ad->nf, "regi,layout", layout);

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
	elm_object_part_text_set(pn_number_entry, "elm.guide", i18n_get_text("IDS_TGRAM_BODY_PHONE_NUMBER_ABB"));
	elm_entry_cursor_end_set(pn_number_entry);
	evas_object_size_hint_weight_set(pn_number_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(pn_number_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(pn_number_entry,  EINA_TRUE);
	elm_entry_scrollable_set(pn_number_entry, EINA_FALSE);
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

	Evas_Object* delete_btn = elm_button_add(layout);
	elm_object_style_set(delete_btn, "icon_expand_delete");
	evas_object_size_hint_weight_set(delete_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(delete_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_max_set(delete_btn, 80, 80);
	evas_object_smart_callback_add(delete_btn, "clicked", delete_btn_clicked, pn_number_entry);
	elm_object_part_content_set(layout, "phone_number_delete", delete_btn);
	evas_object_show(delete_btn);

	//confirm text
	elm_object_part_text_set(layout, "text_display", i18n_get_text("IDS_TGRAM_BODY_CONFIRM_YOUR_COUNTRY_CODE_MSG"));

	//naviframe GUI
	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, i18n_get_text("IDS_TGRAM_HEADER_ENTER_NUMBER_ABB"), NULL, NULL, scroller, NULL);

	Evas_Object *cancel_btn = elm_button_add(ad->nf);
	elm_object_style_set(cancel_btn, "naviframe/title_left");
	elm_object_text_set(cancel_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_CANCEL_ABB"));
	evas_object_smart_callback_add(cancel_btn, "clicked", on_naviframe_cancel_clicked, ad);

	Evas_Object *done_btn = elm_button_add(ad->nf);
	elm_object_style_set(done_btn, "naviframe/title_right");
	elm_object_text_set(done_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_DONE_ABB"));
	evas_object_smart_callback_add(done_btn, "clicked", on_naviframe_done_clicked, ad);


	elm_object_item_part_content_set(navi_item, "title_left_btn", cancel_btn);
	elm_object_item_part_content_set(navi_item, "title_right_btn", done_btn);

	evas_object_data_set(ad->nf, "reg_done_btn", (void*)done_btn);
	evas_object_data_set(ad->nf, "reg_cancel_btn", (void*)cancel_btn);
	elm_object_disabled_set(done_btn, EINA_TRUE);
}
