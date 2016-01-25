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

#include "tg_first_registration.h"
#include "server_requests.h"
#include "tg_user_main_view.h"

static void on_first_name_change_enable_ok_button(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object* done_btn = evas_object_data_get(ad->nf, "name_done_btn");
	char buf[256] = {'\0',};
	snprintf(buf, sizeof(buf), "%s", elm_object_text_get(obj));
	char* org_buf = trim(buf);

	if (strlen(org_buf) > 0) {
		elm_object_disabled_set(done_btn, EINA_FALSE);
	} else {
		elm_object_disabled_set(done_btn, EINA_TRUE);
	}
	free(org_buf);
}

static void on_naviframe_cancel_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	elm_win_lower(ad->win);
	elm_exit();
}

static void on_name_entry_done_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
#if 1
	Evas_Object* first_name_entry = evas_object_data_get(ad->nf, "first_name_entry");
	Evas_Object* last_name_entry = evas_object_data_get(ad->nf, "second_name_entry");
	const char* tfirst_name = elm_object_text_get(first_name_entry);
	if (!tfirst_name) {
		show_toast(ad, "Enter first name");
		return;
	}
	const char* tlast_name = elm_object_text_get(last_name_entry);
	if (!tlast_name) {
		tlast_name = "";
	}
	char* first_name = trim((char*)tfirst_name);
	char* last_name = trim((char*)tlast_name);
	send_request_for_profile_registration(ad, ad->service_client, first_name, last_name);
	show_loading_popup(ad);
	free(first_name);
	free(last_name);
#else
	elm_naviframe_item_pop(ad->nf);
	launch_user_main_view_cb(ad);
#endif
}

void launch_first_registration_cb(appdata_s *ad)
{

	if (!ad)
		return;
	ad->current_app_state = TG_PROFILE_REGISTRATION_STATE;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	elm_win_resize_object_add(ad->win, scroller);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "name_reg_screen");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);


	elm_object_part_text_set(layout, "inform", i18n_get_text("IDS_TGRAM_BODY_ENTER_YOUR_FIRST_AND_LAST_NAME_ABB"));

	Evas_Object* first_name_entry = elm_entry_add(layout);
	evas_object_size_hint_weight_set(first_name_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(first_name_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);

	elm_object_part_text_set(first_name_entry, "elm.guide", i18n_get_text("IDS_TGRAM_BODY_FIRST_NAME_HREQUIRED_ABB"));

	elm_entry_single_line_set(first_name_entry, EINA_TRUE);
	elm_entry_scrollable_set(first_name_entry, EINA_FALSE);
	elm_entry_cnp_mode_set(first_name_entry, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(first_name_entry, EINA_TRUE);
	elm_entry_text_style_user_push(first_name_entry, "DEFAULT='color=#000000'");
	evas_object_show(first_name_entry);
	elm_object_part_content_set(layout, "first_name_entry", first_name_entry);

	evas_object_data_set(ad->nf, "first_name_entry", (void*)first_name_entry);

	evas_object_smart_callback_add(first_name_entry, "changed", on_first_name_change_enable_ok_button, ad);

	Evas_Object* second_name_entry = elm_entry_add(layout);
	evas_object_size_hint_weight_set(second_name_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(second_name_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);

	elm_object_part_text_set(second_name_entry, "elm.guide", i18n_get_text("IDS_TGRAM_BODY_LAST_NAME_HREQUIRED_ABB"));

	elm_entry_single_line_set(second_name_entry, EINA_TRUE);
	elm_entry_scrollable_set(second_name_entry, EINA_FALSE);
	elm_entry_cnp_mode_set(second_name_entry, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(second_name_entry, EINA_TRUE);
	elm_entry_text_style_user_push(second_name_entry, "DEFAULT='color=#000000'");
	evas_object_show(second_name_entry);
	elm_object_part_content_set(layout, "second_name_entry", second_name_entry);

	evas_object_data_set(ad->nf, "second_name_entry", (void*)second_name_entry);


	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, i18n_get_text("IDS_TGRAM_HEADER_ENTER_NAME_ABB2"), NULL, NULL, scroller, NULL);

	Evas_Object *done_btn = elm_button_add(ad->nf);
	elm_object_style_set(done_btn, "naviframe/title_right");
	elm_object_text_set(done_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_DONE_ABB"));
	evas_object_smart_callback_add(done_btn, "clicked", on_name_entry_done_clicked, ad);

	Evas_Object *cancel_btn = elm_button_add(ad->nf);
	elm_object_style_set(cancel_btn, "naviframe/title_left");
	elm_object_text_set(cancel_btn, i18n_get_text("IDS_TGRAM_ACBUTTON_CANCEL_ABB"));
	evas_object_smart_callback_add(cancel_btn, "clicked", on_naviframe_cancel_clicked, ad)
	;
	elm_object_item_part_content_set(navi_item, "title_right_btn", done_btn);
	elm_object_item_part_content_set(navi_item, "title_left_btn", cancel_btn);

	evas_object_data_set(ad->nf, "name_done_btn", (void*)done_btn);
	elm_object_disabled_set(done_btn, EINA_TRUE);

}
