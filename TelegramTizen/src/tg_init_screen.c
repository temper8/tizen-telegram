/*
 * tg_init_screen.c
 *
 *  Created on: Aug 18, 2015
 *      Author: sandeep
 */

#include "tg_init_screen.h"
#include "tg_registration.h"
#include "index.h"

#define MAX_INDEX 7
#define RIGHT_BUTTON_WIDTH (320*1.4)
#define RIGHT_BUTTON_HEIGHT (104*1.4)

#define LEFT_BUTTON_WIDTH (320*1.4)
#define LEFT_BUTTON_HEIGHT (104*1.4)

#define CENTER_BUTTON_WIDTH (496*1.4)
#define CENTER_BUTTON_HEIGHT (104*1.4)

static void _set_init_screen(Evas_Object *layout);

static void on_start_btn_clicked(void *data, Evas_Object *obj, const char *emission, const char *source)
{
	appdata_s* ad = data;
	elm_naviframe_item_pop(ad->nf);
	launch_registration_cb(ad);
}

static void _set_init_screen(Evas_Object *layout)
{
	Evas_Object *bg = NULL;
	Evas_Object *content_layout = NULL;
	Evas_Object *button = NULL;
	Evas_Object *index = NULL;
	Evas_Object *center_btn = NULL;
	char value[256] = {0, };
	int page_idx = 0;

	bg = elm_object_part_content_get(layout, "bg_color");
	content_layout = elm_object_part_content_get(layout, "setup,main");
	button = elm_object_part_content_get(layout, "button");
	index = elm_object_part_content_get(layout, "index");
	center_btn = elm_object_part_content_get(button, "center,button");

	page_idx = (int)evas_object_data_get(layout, "page_idx");

	switch(page_idx) {
	case 1:
		evas_object_color_set(bg, 214, 82, 64, 255);
		elm_object_signal_emit(content_layout, "fast", "icon");
		elm_object_signal_emit(button, "2,button", "button");
		elm_object_translatable_part_text_set(content_layout, "title", i18n_get_text("IDS_TGRAM_HEADER_FAST"));
		snprintf(value, sizeof(value), elm_entry_utf8_to_markup(i18n_get_text("IDS_TGRAM_SBODY_P1SSTELEGRAMP2SS_DELIVERS_MESSAGES_NFASTER_THAN_ANY_OTHER_APP")), "<b>", "</b>");
		elm_object_translatable_part_text_set(content_layout, "comment", value);
		break;
	case 2:
		evas_object_color_set(bg, 242, 184, 24, 255);
		elm_object_signal_emit(content_layout, "free", "icon");
		elm_object_translatable_part_text_set(content_layout, "title", i18n_get_text("IDS_TGRAM_HEADER_FREE"));
		snprintf(value, sizeof(value), elm_entry_utf8_to_markup(i18n_get_text("IDS_TGRAM_SBODY_P1SSTELEGRAMP2SS_IS_FREE_FOREVER_N_NNO_ADS_NO_SUBSCRIPTION_FEES")), "<b>", "</b>");
		elm_object_translatable_part_text_set(content_layout, "comment", value);
		break;
	case 3:
		evas_object_color_set(bg, 118, 196, 69, 255);
		elm_object_signal_emit(content_layout, "secure", "icon");
		elm_object_translatable_part_text_set(content_layout, "title", i18n_get_text("IDS_TGRAM_HEADER_SECURE"));
		snprintf(value, sizeof(value), elm_entry_utf8_to_markup(i18n_get_text("IDS_TGRAM_SBODY_P1SSTELEGRAMP2SS_KEEPS_YOUR_MESSAGES_NSAFE_FROM_HACKERS")), "<b>", "</b>");
		elm_object_translatable_part_text_set(content_layout, "comment", value);
		break;
	case 4:
		evas_object_color_set(bg, 129, 97, 194, 255);
		elm_object_signal_emit(content_layout, "powerful", "icon");
		elm_object_translatable_part_text_set(content_layout, "title", i18n_get_text("IDS_TGRAM_HEADER_POWERFUL"));
		snprintf(value, sizeof(value), elm_entry_utf8_to_markup(i18n_get_text("IDS_TGRAM_SBODY_P1SSTELEGRAMP2SS_HAS_NO_LIMITS_ON_THE_SIZE_OF_NCHATS_AND_MEDIA_YOU_CAN_SHARE")), "<b>", "</b>");
		elm_object_translatable_part_text_set(content_layout, "comment", value);
		break;
	case 5:
		evas_object_color_set(bg, 63, 184, 212, 255);
		elm_object_signal_emit(content_layout, "cloud", "icon");
		elm_object_signal_emit(button, "2,button", "button");
		elm_object_translatable_part_text_set(content_layout, "title", i18n_get_text("IDS_TGRAM_HEADER_CLOUD_BASED_ABB"));
		snprintf(value, sizeof(value), elm_entry_utf8_to_markup(i18n_get_text("IDS_TGRAM_SBODY_P1SSTELEGRAMP2SS_ALLOWS_YOU_TO_ACCESS_NYOUR_MESSAGES_FROM_MULTIPLE_DEVICES")), "<b>", "</b>");
		elm_object_translatable_part_text_set(content_layout, "comment", value);
		break;
	case 6:
		evas_object_color_set(bg, 237, 116, 36, 255);
		elm_object_signal_emit(content_layout, "private", "icon");
		elm_object_signal_emit(button, "1,button", "button");
		elm_object_part_text_set(center_btn, "text", i18n_get_text("IDS_TGRAM_BUTTON_PREVIOUS"));
		elm_object_translatable_part_text_set(content_layout, "title", i18n_get_text("IDS_TGRAM_HEADER_PRIVATE"));
		snprintf(value, sizeof(value), elm_entry_utf8_to_markup(i18n_get_text("IDS_TGRAM_SBODY_P1SSTELEGRAMP2SS_MESSAGES_ARE_STRONGLY_ENCRYPTED_NAND_CAN_BE_DELETED_AUTOMATICALLY")), "<b>", "</b>");
		elm_object_translatable_part_text_set(content_layout, "comment", value);
		break;
	default:
		evas_object_color_set(bg, 45, 165, 224, 255);
		elm_object_signal_emit(content_layout, "telegram", "icon");
		elm_object_signal_emit(button, "1,button", "button");
		elm_object_part_text_set(center_btn,"text", i18n_get_text("IDS_TGRAM_BUTTON_NEXT_ABB5"));
		elm_object_translatable_part_text_set(content_layout, "title", i18n_get_text("IDS_TGRAM_HEADER_TELEGRAM"));
		snprintf(value, sizeof(value), elm_entry_utf8_to_markup(i18n_get_text("IDS_TGRAM_SBODY_THE_WORLDS_P1SSFASTESTP2SS_MESSAGING_APP_NIT_IS_P3SSFREEP4SS_AND_P5SSSECUREP6SS")), "<b>", "</b>", "<b>", "</b>", "<b>", "</b>");
		elm_object_translatable_part_text_set(content_layout, "comment", value);
		break;
	}
	index_bring_in(index, page_idx);
}

static void _bottom_btn_clicked(void *data, Evas_Object *obj, const char *emission, const char *source)
{
	Evas_Object *layout = data;
	int kind = 3;
	int page_idx = 0;

	kind = (int)evas_object_data_get(obj, "kind");
	page_idx = (int)evas_object_data_get(layout, "page_idx");

	switch(kind) {
	case 1:
		page_idx ++;
		break;
	case 2:
		page_idx --;
		break;
	case 3:
	default:
		if (page_idx == 0) page_idx ++;
		else page_idx --;
		break;
	}

	if (page_idx < 0) page_idx = 0;
	else if (page_idx > 6) page_idx = 6;

	evas_object_data_set(layout, "page_idx", (void *) page_idx);

	_set_init_screen(layout);
}

static void _destroy_bottom_button(Evas_Object *layout)
{
	Evas_Object *bottom_layout = NULL;
	Evas_Object *right_btn = NULL;
	Evas_Object *left_btn = NULL;
	Evas_Object *center_btn = NULL;

	bottom_layout = elm_object_part_content_unset(layout, "button");

	right_btn = elm_object_part_content_unset(bottom_layout, "right,button");
	if (right_btn) evas_object_del(right_btn);

	left_btn = elm_object_part_content_unset(bottom_layout, "left,button");
	if (left_btn) evas_object_del(left_btn);

	center_btn = elm_object_part_content_unset(bottom_layout, "center,button");
	if (center_btn) evas_object_del(center_btn);

	evas_object_del(bottom_layout);

}

static Evas_Object *_create_bottom_button(Evas_Object *layout, char *edj_path)
{
	Evas_Object *bottom_layout = NULL;
	Evas_Object *right_btn = NULL;
	Evas_Object *left_btn = NULL;
	Evas_Object *center_btn = NULL;

	bottom_layout = elm_layout_add(layout);
	elm_layout_file_set(bottom_layout, edj_path, "button");
	evas_object_size_hint_weight_set(bottom_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(bottom_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_content_set(layout, "button", bottom_layout);
	evas_object_show(bottom_layout);

	right_btn = elm_layout_add(bottom_layout);
	elm_layout_file_set(right_btn, edj_path, "button,style");
	evas_object_size_hint_weight_set(right_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(right_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_min_set(right_btn, ELM_SCALE_SIZE(RIGHT_BUTTON_WIDTH), ELM_SCALE_SIZE(RIGHT_BUTTON_HEIGHT));
	evas_object_size_hint_max_set(right_btn, ELM_SCALE_SIZE(RIGHT_BUTTON_WIDTH), ELM_SCALE_SIZE(RIGHT_BUTTON_HEIGHT));
	evas_object_show(right_btn);
	elm_object_part_text_set(right_btn, "text", i18n_get_text("IDS_TGRAM_BUTTON_NEXT_ABB5"));
	elm_object_part_content_set(bottom_layout, "right,button", right_btn);
	elm_object_signal_callback_add(right_btn, "clicked", "button", _bottom_btn_clicked, layout);
	evas_object_data_set(right_btn, "kind", (void *) 1);

	left_btn = elm_layout_add(bottom_layout);
	elm_layout_file_set(left_btn, edj_path, "button,style");
	evas_object_size_hint_weight_set(left_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(left_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_min_set(left_btn, ELM_SCALE_SIZE(LEFT_BUTTON_WIDTH), ELM_SCALE_SIZE(LEFT_BUTTON_HEIGHT));
	evas_object_size_hint_max_set(left_btn, ELM_SCALE_SIZE(LEFT_BUTTON_WIDTH), ELM_SCALE_SIZE(LEFT_BUTTON_HEIGHT));
	evas_object_show(left_btn);
	elm_object_part_text_set(left_btn, "text", i18n_get_text("IDS_TGRAM_BUTTON_PREVIOUS"));
	elm_object_part_content_set(bottom_layout, "left,button", left_btn);
	elm_object_signal_callback_add(left_btn, "clicked", "button", _bottom_btn_clicked, layout);
	evas_object_data_set(left_btn, "kind", (void *) 2);

	center_btn = elm_layout_add(bottom_layout);
	elm_layout_file_set(center_btn, edj_path, "button,style");
	evas_object_size_hint_weight_set(center_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(center_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_min_set(center_btn, ELM_SCALE_SIZE(CENTER_BUTTON_WIDTH), ELM_SCALE_SIZE(CENTER_BUTTON_HEIGHT));
	evas_object_size_hint_max_set(center_btn, ELM_SCALE_SIZE(CENTER_BUTTON_WIDTH), ELM_SCALE_SIZE(CENTER_BUTTON_HEIGHT));
	evas_object_show(center_btn);
	elm_object_part_text_set(center_btn, "text", i18n_get_text("IDS_TGRAM_BUTTON_NEXT_ABB5"));
	elm_object_part_content_set(bottom_layout, "center,button", center_btn);
	elm_object_signal_callback_add(center_btn, "clicked", "button", _bottom_btn_clicked, layout);
	evas_object_data_set(center_btn, "kind", (void *) 3);

	return bottom_layout;
}

void launch_destroy_screen(Evas_Object *layout)
{
	Evas_Object *bg = NULL;
	Evas_Object *content_layout = NULL;
	Evas_Object *pbt = NULL;
	Evas_Object *index = NULL;

	_destroy_bottom_button(layout);

	index = elm_object_part_content_unset(layout, "index");
	index_destroy(index);

	pbt = elm_object_part_content_unset(layout, "start,button");
	if (pbt) evas_object_del(pbt);

	bg = elm_object_part_content_unset(layout, "bg_color");
	if (bg) evas_object_del(bg);

	content_layout = elm_object_part_content_unset(layout, "setup,main");
	if (content_layout) evas_object_del(content_layout);

	evas_object_del(layout);
}

void launch_init_screen(appdata_s* ad)
{
	Evas_Object *layout = NULL;
	Evas_Object *bg = NULL;
	Evas_Object *content_layout = NULL;
	Evas_Object *pbt = NULL;
	Evas_Object *index = NULL;
	Evas_Object *bottom_button = NULL;
	char edj_path[PATH_MAX] = {0, };

	layout = elm_layout_add(ad->win);
	app_get_resource(TELEGRAM_START_VIEW_EDJ, edj_path, (int)PATH_MAX);
	elm_layout_file_set(layout, edj_path, "setup,layout");
	ad->current_app_state = TG_INIT_SCREEN_STATE;
	evas_object_data_set(layout, "page_idx", (void *) 0);

	bg = evas_object_rectangle_add(evas_object_evas_get(layout));
	evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_content_set(layout, "bg_color", bg);
	evas_object_show(bg);

	content_layout = elm_layout_add(layout);
	elm_layout_file_set(content_layout, edj_path, "setup,main");
	evas_object_size_hint_weight_set(content_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(content_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_content_set(layout, "setup,main", content_layout);
	evas_object_show(content_layout);

	_set_init_screen(layout);

	pbt = elm_layout_add(layout);
	elm_layout_file_set(pbt, edj_path, "button,style");
	evas_object_size_hint_weight_set(pbt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(pbt, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(pbt);
	elm_object_part_text_set(pbt, "text", i18n_get_text("IDS_TGRAM_ACBUTTON_START_MESSAGING"));
	elm_object_part_content_set(layout, "start,button", pbt);
	elm_object_signal_callback_add(pbt, "clicked", "button", on_start_btn_clicked, ad);

	index = index_create(layout, MAX_INDEX);
	index_bring_in(index, 0);
	elm_object_part_content_set(layout, "index", index);

	bottom_button = _create_bottom_button(layout, edj_path);

	evas_object_data_set(ad->nf, "init_layout", (void*)layout);

	elm_naviframe_item_simple_push(ad->nf, layout);
}

