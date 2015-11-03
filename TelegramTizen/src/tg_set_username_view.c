/*
 * tg_set_username_view.c
 *
 *  Created on: Sep 30, 2015
 *      Author: sandeep
 */

#include "tg_set_username_view.h"
#include "server_requests.h"

static void on_username_text_change_enable_ok_button(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object *done_btn = evas_object_data_get(ad->nf, "username_done_btn");
	Evas_Object *username_entry = evas_object_data_get(ad->nf, "username_entry");
	char *temp_user_name = elm_entry_markup_to_utf8(elm_object_text_get(username_entry));

	char *user_name = trim(temp_user_name);

	if (strlen(user_name) >= MIN_USERNAME_LENGTH) {
		elm_object_disabled_set(done_btn, EINA_FALSE);
	} else {
		elm_object_disabled_set(done_btn, EINA_TRUE);
	}
	free(user_name);
}

static void on_naviframe_username_cancel_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	elm_naviframe_item_pop(ad->nf);
}

static void on_naviframe_username_done_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	Evas_Object *username_entry = evas_object_data_get(ad->nf, "username_entry");
	char *temp_user_name = elm_entry_markup_to_utf8(elm_object_text_get(username_entry));

	char *user_name = trim(temp_user_name);
	if (strlen(user_name) < MIN_USERNAME_LENGTH) {
		show_toast(ad, "Username should not be less than 5 characters");
	} else {
		send_set_username_request(ad, ad->service_client, ad->current_user_data->user_id.id, user_name);
		show_loading_popup(ad);
	}
	free(user_name);
}

void launch_set_username_cb(appdata_s *ad)
{
	if (!ad) {
		return;
	}

	ad->current_app_state = TG_SET_USERNAME_STATE;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "set_user_name_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);



	Evas_Object* username_entry = elm_entry_add(layout);
	elm_object_part_text_set(username_entry, "elm.guide", "Enter phone number");
	elm_entry_cursor_end_set(username_entry);
	evas_object_size_hint_weight_set(username_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(username_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(username_entry,  EINA_TRUE);
	elm_entry_scrollable_set (username_entry, EINA_FALSE);
	elm_entry_cnp_mode_set(username_entry, ELM_CNP_MODE_NO_IMAGE);
	elm_entry_context_menu_disabled_set(username_entry, EINA_TRUE);
	elm_entry_text_style_user_push(username_entry, "DEFAULT='color=#000000'");
	evas_object_show(username_entry);
	elm_object_part_content_set(layout, "swallow.entry_box", username_entry);

	evas_object_data_set(ad->nf, "username_entry", (void*)username_entry);

	limit_filter_data.max_char_count = MAX_USERNAME_LENGTH;
	elm_entry_markup_filter_append(username_entry, elm_entry_filter_limit_size, &limit_filter_data);
	Ecore_IMF_Context *imf_context;
	imf_context = elm_entry_imf_context_get(username_entry);
	ecore_imf_context_input_panel_layout_set(imf_context, ECORE_IMF_INPUT_PANEL_LAYOUT_NORMAL_VARIATION_PERSON_NAME);

	//evas_object_smart_callback_add(username_entry, "changed", on_username_text_change_enable_ok_button, ad);

	char* temp_help_text_one = "You can choose a username on Telegram, If you do, other people will be able to find you by this username and contact you without knowing your phone number.";
	char* temp_help_text_two = "You can use a-z, 0-9 and underscores. Minimum length is 5 characters.";

	char help_text_one[256*4] = {'\0'};
	sprintf(help_text_one, "<font=Tizen:style=Italic color=#000000 align=left><font_size=30>%s</font_size></font>", temp_help_text_one);


	char help_text_two[256*4] = {'\0'};
	sprintf(help_text_two, "<font=Tizen:style=Italic color=#000000 align=left><font_size=30>%s</font_size></font>", temp_help_text_two);

	Evas_Object* help_text1 = elm_entry_add(layout);
	elm_object_text_set(help_text1, help_text_one);
	evas_object_size_hint_weight_set(help_text1, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(help_text1, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(help_text1,  EINA_FALSE);
	elm_entry_editable_set(help_text1, EINA_FALSE);
	elm_entry_line_wrap_set(help_text1, EINA_TRUE);
	evas_object_show(help_text1);
	elm_object_part_content_set(layout, "swallow.help_text_one", help_text1);

	Evas_Object* help_text2 = elm_entry_add(layout);
	elm_object_text_set(help_text2, help_text_two);
	evas_object_size_hint_weight_set(help_text2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(help_text2, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_entry_single_line_set(help_text2,  EINA_FALSE);
	elm_entry_editable_set(help_text2, EINA_FALSE);
	elm_entry_line_wrap_set(help_text2, EINA_TRUE);
	evas_object_show(help_text2);
	elm_object_part_content_set(layout, "swallow.help_text_two", help_text2);


	elm_object_content_set(scroller, layout);
	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "Username", NULL, NULL, scroller, NULL);

	Evas_Object *cancel_btn = elm_button_add(ad->nf);
	elm_object_style_set(cancel_btn, "naviframe/title_icon");
	elm_object_text_set(cancel_btn, "Cancel");
	evas_object_smart_callback_add(cancel_btn, "clicked", on_naviframe_username_cancel_clicked, ad);

	Evas_Object *done_btn = elm_button_add(ad->nf);
	elm_object_style_set(done_btn, "naviframe/title_icon");
	elm_object_text_set(done_btn, "Done");
	evas_object_smart_callback_add(done_btn, "clicked", on_naviframe_username_done_clicked, ad);


	elm_object_item_part_content_set(navi_item, "title_left_btn", cancel_btn);
	elm_object_item_part_content_set(navi_item, "title_right_btn", done_btn);

	evas_object_data_set(ad->nf, "username_done_btn", (void*)done_btn);
	evas_object_data_set(ad->nf, "username_cancel_btn", (void*)cancel_btn);
	//elm_object_disabled_set(done_btn, EINA_TRUE);

}


