/*
 * tg_init_screen.c
 *
 *  Created on: Aug 18, 2015
 *      Author: sandeep
 */

#include "tg_init_screen.h"
#include "tg_registration.h"

static Evas_Object* get_single_box(appdata_s* ad, Eina_Bool is_next);
static Evas_Object* get_next_previous_box(appdata_s* ad);
static void on_next_btn_clicked(void* data, Evas_Object* obj, void* event)
{
	appdata_s* ad = data;

	Evas_Object* image = evas_object_data_get(ad->nf, "current_image");

	char* cur_img = evas_object_data_get(image, "current_image_index");

	if (strcasecmp(cur_img, INIT_SCREEN_1) == 0) {


		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_2), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_2);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);

		Evas_Object* btn_box = evas_object_data_get(ad->nf, "button_box");
		evas_object_del(btn_box);
		btn_box = get_next_previous_box(ad);

		elm_object_part_content_set(layout, "button_box", btn_box);

	} else if (strcasecmp(cur_img, INIT_SCREEN_2) == 0) {

		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_3), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_3);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);

	} else if (strcasecmp(cur_img, INIT_SCREEN_3) == 0) {

		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_4), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_4);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);

	} else if (strcasecmp(cur_img, INIT_SCREEN_4) == 0) {


		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_5), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_5);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);


	} else if (strcasecmp(cur_img, INIT_SCREEN_5) == 0) {


		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_6), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_6);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);


	} else if (strcasecmp(cur_img, INIT_SCREEN_6) == 0) {


		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_7), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_7);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);


		Evas_Object* btn_box = evas_object_data_get(ad->nf, "button_box");
		evas_object_del(btn_box);
		btn_box = get_single_box(ad, EINA_FALSE);
		elm_object_part_content_set(layout, "button_box", btn_box);


	} else if (strcasecmp(cur_img, INIT_SCREEN_7) == 0) {

	}


}

static void on_previous_btn_clicked(void* data, Evas_Object* obj, void* event)
{
	appdata_s* ad = data;

	Evas_Object* image = evas_object_data_get(ad->nf, "current_image");

	char* cur_img = evas_object_data_get(image, "current_image_index");

	if (strcasecmp(cur_img, INIT_SCREEN_7) == 0) {
		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_6), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_6);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);

		Evas_Object* btn_box = evas_object_data_get(ad->nf, "button_box");
		evas_object_del(btn_box);
		btn_box = get_next_previous_box(ad);
		elm_object_part_content_set(layout, "button_box", btn_box);


	} else if (strcasecmp(cur_img, INIT_SCREEN_6) == 0) {

		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_5), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_5);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);

	} else if (strcasecmp(cur_img, INIT_SCREEN_5) == 0) {


		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_4), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_4);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);


	} else if (strcasecmp(cur_img, INIT_SCREEN_4) == 0) {

		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_3), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_3);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);


	} else if (strcasecmp(cur_img, INIT_SCREEN_3) == 0) {

		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_2), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_2);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);


	} else if (strcasecmp(cur_img, INIT_SCREEN_2) == 0) {


		Evas_Object* layout = evas_object_data_get(ad->nf, "init_layout");
		evas_object_del(image);
		image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_1), layout);
		evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_1);
		evas_object_data_set(ad->nf, "current_image", (void*)image);
		elm_object_part_content_set(layout, "main_image", image);

		Evas_Object* btn_box = evas_object_data_get(ad->nf, "button_box");
		evas_object_del(btn_box);
		btn_box = get_single_box(ad, EINA_TRUE);
		elm_object_part_content_set(layout, "button_box", btn_box);


	} else if (strcasecmp(cur_img, INIT_SCREEN_1) == 0) {

	}
}

static void on_start_btn_clicked(void* data, Evas_Object* obj, void* event)
{
	appdata_s* ad = data;
	elm_naviframe_item_pop(ad->nf);
	launch_registration_cb(ad);
}

Evas_Object* get_single_box(appdata_s* ad, Eina_Bool is_next)
{
	Evas_Object* bigbox = elm_box_add(ad->win);
	evas_object_size_hint_weight_set(bigbox, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_box_horizontal_set(bigbox, EINA_TRUE);
	evas_object_show(bigbox);

	Evas_Object* bt = elm_button_add(ad->win);

	if (is_next) {
		elm_object_text_set(bt, "Next");
		evas_object_smart_callback_add(bt, "clicked", on_next_btn_clicked, ad);
	} else {
		elm_object_text_set(bt, "Previous");
		evas_object_smart_callback_add(bt, "clicked", on_previous_btn_clicked, ad);
	}

	evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(bt);
	elm_box_pack_end(bigbox, bt);

	return bigbox;
}

Evas_Object* get_next_previous_box(appdata_s* ad)
{
	Evas_Object* bigbox = elm_box_add(ad->win);
	evas_object_size_hint_weight_set(bigbox, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_box_horizontal_set(bigbox, EINA_TRUE);
	elm_box_homogeneous_set(bigbox, EINA_TRUE);
	evas_object_show(bigbox);

	Evas_Object* pbt = elm_button_add(ad->win);
	elm_object_text_set(pbt, "Previous");
	evas_object_size_hint_weight_set(pbt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(pbt, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(pbt);

	Evas_Object* nbt = elm_button_add(ad->win);
	elm_object_text_set(nbt, "Next");
	evas_object_size_hint_weight_set(nbt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(nbt, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(nbt);

	evas_object_smart_callback_add(pbt, "clicked", on_previous_btn_clicked, ad);
	evas_object_smart_callback_add(nbt, "clicked", on_next_btn_clicked, ad);

	elm_box_pack_end(bigbox, pbt);
	elm_box_pack_end(bigbox, nbt);
	return bigbox;
}


void launch_init_screen(appdata_s* ad)
{
	char edj_path[PATH_MAX] = {0, };
	Evas_Object* layout = elm_layout_add(ad->win);
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
	elm_layout_file_set(layout, edj_path, "init_screen");
	ad->current_app_state = TG_INIT_SCREEN_STATE;

	Evas_Object* image = create_image_object_from_file(ui_utils_get_resource(INIT_SCREEN_1), layout);

	evas_object_data_set(image, "current_image_index", (void*)INIT_SCREEN_1);

	evas_object_data_set(ad->nf, "current_image", (void*)image);

	Evas_Object* btn_box = get_single_box(ad, EINA_TRUE);

	evas_object_data_set(ad->nf, "button_box", (void*)btn_box);

	elm_object_part_content_set(layout, "main_image", image);
	elm_object_part_content_set(layout, "button_box", btn_box);


	Evas_Object* pbt = elm_button_add(ad->win);
	elm_object_style_set(pbt, "transparent");
	evas_object_size_hint_weight_set(pbt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(pbt, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(pbt);
	elm_object_part_content_set(layout, "start_btn", pbt);
	evas_object_smart_callback_add(pbt, "clicked", on_start_btn_clicked, ad);


	evas_object_data_set(ad->nf, "init_layout", (void*)layout);

	elm_naviframe_item_simple_push(ad->nf, layout);
}

