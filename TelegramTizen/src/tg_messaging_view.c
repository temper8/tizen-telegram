/*
 * tg_messaging_view.c
 *
 *  Created on: Aug 22, 2015
 *      Author: sandeep
 */

#include "tg_messaging_view.h"
#include "tg_db_wrapper.h"
#include "server_requests.h"

static Evas_Object *create_image_object_from_file(const char *icon_name, Evas_Object *parent)
{
	Evas_Object *icon = elm_image_add(parent);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_image_file_set(icon, icon_name, NULL);
	evas_object_show(icon);
	return icon;
}

static inline Evas_Object * image_item_provider(void *data, Evas_Object *entry, const char *item)
{
	Evas_Object* layout = NULL;
    if (!strcmp(item, "itemprovider"))
    {
    	Evas_Object* chat_list = data;
    	int message_id = (int)evas_object_data_get(entry, "message_id");
		appdata_s* ad = evas_object_data_get(chat_list, "app_data");
		int user_id = (int)evas_object_data_get(chat_list, "user_id");
		//Evas_Object* text_entry = evas_object_data_set(chat_list, "text_entry");

		user_data_with_pic_s *sel_item =  eina_list_nth(ad->buddy_list, user_id);
		int buddy_id = sel_item->use_data->user_id.id;
		char* tablename = get_table_name_from_number(buddy_id);
		tg_message_s* msg = get_message_from_message_table(message_id, tablename);

		// get media details.

		char *img_path = get_image_path_from_db(atoll(msg->media_id));

		if (img_path == NULL || strlen(img_path) == 0) {

			int img_size = (int)evas_object_data_get(entry, "media_size");
			char img_size_str[10];
			const char *tmp;

			sprintf(img_size_str, "%dkbs", img_size);
			tmp = ui_utils_get_resource(BLUR_BG);
			img_path = strdup(tmp);
			char edj_path[PATH_MAX] = {0, };
			app_get_resource(EDJ_CHAT_CONV_FILE, edj_path, (int)PATH_MAX);

			layout = elm_layout_add(entry);
			elm_layout_file_set(layout, edj_path, "chat_image_item");

			Evas_Object* temp_icon = elm_image_add(entry);
			elm_image_resizable_set(temp_icon, EINA_TRUE, EINA_TRUE);
			elm_image_fill_outside_set(temp_icon, EINA_TRUE);
			elm_image_aspect_fixed_set(temp_icon, EINA_TRUE);
			elm_image_file_set(temp_icon, img_path, NULL);
			evas_object_show(temp_icon);

			Evas_Object* download_icon = elm_image_add(entry);
			elm_image_file_set(download_icon, ui_utils_get_resource(MEDIA_DOWNLOAD_ICON), NULL);
			evas_object_show(download_icon);

#if 0
			Evas_Object* img_btn = elm_button_add(entry);
			elm_object_style_set(img_btn, "transparent");
			evas_object_size_hint_weight_set(img_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(img_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
			elm_object_content_set(img_btn, temp_icon);
			evas_object_show(img_btn);
#endif

			Evas_Object* img_size_lbl = elm_label_add(entry);
			elm_object_style_set(img_size_lbl, "transparent");

			char temp_size[256] = {0,};
			snprintf(temp_size, sizeof(temp_size), "<font=Tizen:style=Regular color=#f16745 align=left><font_size=36>%s</br></font_size></font>", img_size_str);
			Eina_Strbuf *buf = eina_strbuf_new();
			eina_strbuf_append(buf, temp_size);

			elm_object_text_set(img_size_lbl, eina_strbuf_string_get(buf));
			eina_strbuf_free(buf);
			evas_object_show(img_size_lbl);

#if 0
			Evas_Object* progressbar = elm_progressbar_add(entry);
			elm_object_style_set(progressbar, "process_large");
			evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			elm_progressbar_pulse(progressbar, EINA_TRUE);
#else
			Evas_Object* pg_box = elm_box_add(entry);
			evas_object_size_hint_weight_set(pg_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(pg_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(pg_box);
#endif


			elm_object_part_content_set(layout, "swallow.chat_image_progress", pg_box);
			elm_object_part_content_set(layout, "swallow.chat_item_bg_image", temp_icon);
			elm_object_part_content_set(layout, "swallow.chat_image_item", download_icon);
			elm_object_part_content_set(layout, "swallow.chat_image_size", img_size_lbl);

			evas_object_data_set(entry, "chat_image_progress", pg_box);
			evas_object_data_set(entry, "image_obj", temp_icon);
			evas_object_data_set(entry, "download_icon", download_icon);
			evas_object_data_set(entry, "img_size_lbl", img_size_lbl);
			evas_object_show(layout);

		} else {
			// image exist

			char edj_path[PATH_MAX] = {0, };
			app_get_resource(EDJ_CHAT_CONV_FILE, edj_path, (int)PATH_MAX);

			layout = elm_layout_add(entry);
			elm_layout_file_set(layout, edj_path, "chat_image_item");

			Evas_Object* temp_icon = elm_image_add(entry);
			elm_image_file_set(temp_icon, img_path, NULL);
			evas_object_show(temp_icon);

			Evas_Object* img_btn = elm_button_add(entry);
			elm_object_style_set(img_btn, "transparent");
			evas_object_size_hint_weight_set(img_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(img_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
			elm_object_content_set(img_btn, temp_icon);
			evas_object_show(img_btn);

			elm_object_part_content_set(layout, "swallow.chat_item_bg_image", img_btn);
			evas_object_show(layout);
			if (img_path) {
				free(img_path);
			}
		}
		evas_object_data_set(entry, "media_layout", layout);
		free(tablename);
		if(msg->message) {
			free(msg->message);
			msg->message = NULL;
		}

		if(msg->media_id) {
			free(msg->media_id);
			msg->media_id = NULL;
		}

		free(msg);

    	return layout;
    }
    return NULL;
}

void on_chat_media_item_clicked(void* data, Evas_Object* layout, void* event_info)
{
/*	evas_object_data_set(comp_img_layout, "chat_list", (void*)chat_list);
	evas_object_data_set(comp_img_layout, "message_id", (void*)message_id);
	evas_object_data_set(comp_img_layout, "item_media", (void*)image);*/

	appdata_s* ad = evas_object_data_get(layout, "app_data");
	char* temp_media_id = evas_object_data_get(layout, "media_id");
	//char* img_path = evas_object_data_get(comp_img_layout, "image_path");

	long long media_id = atoll(temp_media_id);
	char* file_path = get_image_path_from_db(media_id);

	if( access (file_path, F_OK) != -1 ) {

	} else {
		file_path = NULL;
	}

	if (!file_path || strlen(file_path) <= 0) {

		// show progress bar
		Evas_Object* img_info_layout = evas_object_data_get(layout, "image_info_layout");
		Evas_Object* img_size_lbl = elm_object_part_content_get(img_info_layout, "swallow.chat_recv_image,size");
		Evas_Object* download_img = elm_object_part_content_get(img_info_layout, "swallow.chat_recv_image,download");
		//Evas_Object* progressbar = elm_object_part_content_get(img_info_layout, "swallow.chat_recv_image,progress");


		evas_object_del(img_size_lbl);
		evas_object_del(download_img);


		Evas_Object* progressbar = elm_progressbar_add(img_info_layout);
		elm_object_style_set(progressbar, "process_small");
		evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_progressbar_pulse(progressbar, EINA_TRUE);
		elm_object_part_content_set(img_info_layout, "swallow.chat_recv_image,progress", progressbar);
		evas_object_show(progressbar);

		send_request_for_image_downloading(ad->service_client, ad->buddy_in_cahtting_data->use_data->user_id.id, media_id);
	}

}


Evas_Object* on_message_item_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *layout;
	layout = elm_layout_add(obj);
	if (!strcmp(part, "elm.icon.entry")) {
		int message_id = (int)data;
		Evas_Object* chat_list = obj;
		appdata_s* ad = evas_object_data_get(chat_list, "app_data");
		int user_id = (int)evas_object_data_get(chat_list, "user_id");
		//Evas_Object* text_entry = evas_object_data_set(chat_list, "text_entry");

		user_data_with_pic_s *sel_item =  eina_list_nth(ad->buddy_list, user_id);
		int buddy_id = sel_item->use_data->user_id.id;

		char* tablename = get_table_name_from_number(buddy_id);
		tg_message_s* msg = get_message_from_message_table(message_id, tablename);
		Eina_Bool is_blur_image = EINA_FALSE;

		if (msg) {


			if (msg->media_type == tgl_message_media_photo) {

				char edj_path[PATH_MAX] = {0, };
				app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

				char* img_path = get_image_path_from_db(atoll(msg->media_id));

				if( access(img_path, F_OK) != -1 ) {

				} else {
					img_path = NULL;
				}


				if (img_path == NULL || strlen(img_path) == 0) {
					const char *tmp;
					tmp = ui_utils_get_resource(BLUR_BG);
					img_path = strdup(tmp);
					is_blur_image = EINA_TRUE;
				}


				layout = elm_layout_add(obj);
				if(msg->out) {
					elm_layout_file_set(layout, edj_path, "list_image_send_item");
				} else {
					elm_layout_file_set(layout, edj_path, "list_image_recv_item");
				}
				evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_show(layout);


				if (img_path) {

					Evas_Object* img_layout = elm_layout_add(obj);
					if(msg->out) {
						elm_layout_file_set(img_layout, edj_path, "chat_media_send_box");
					} else {
						elm_layout_file_set(img_layout, edj_path, "chat_media_recv_box");
					}
					evas_object_size_hint_weight_set(img_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
					evas_object_size_hint_align_set(img_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
					evas_object_show(img_layout);

					Evas_Object* image = create_image_object_from_file(img_path, obj);
					//elm_image_no_scale_set(image, EINA_TRUE);
					elm_image_resizable_set(image, EINA_TRUE, EINA_TRUE);
					elm_image_smooth_set(image, EINA_FALSE);
					elm_image_aspect_fixed_set(image, EINA_TRUE);
					elm_image_fill_outside_set(image, EINA_FALSE);
					elm_image_editable_set(image, EINA_TRUE);
					int pre_scale = elm_image_prescale_get(image);
					elm_image_prescale_set(image, pre_scale/2);

					if(msg->out) {
						Evas_Object* comp_img_layout = elm_layout_add(obj);

						elm_layout_file_set(comp_img_layout, edj_path, "chat_send_image_box");

						evas_object_size_hint_weight_set(comp_img_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
						evas_object_size_hint_align_set(comp_img_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
						evas_object_show(comp_img_layout);

						elm_object_part_content_set(comp_img_layout, "swallow.chat_send_image", image);
						//@TODO: need to add code here
						//elm_object_signal_emit(item_top, "set,disabled", "bg");

						elm_object_part_content_set(layout, "swallow.img_bg", img_layout);

						time_t t = msg->date;
						const char *format = "%I:%M %P";
						struct tm lt;
						char res[32];
						(void) localtime_r(&t, &lt);

						if (strftime(res, sizeof(res), format, &lt) == 0) {
							(void) fprintf(stderr,  "strftime(3): cannot format supplied "
									"date/time into buffer of size %u "
									"using: '%s'\n",
									sizeof(res), format);
						}

						char time_str[20] = {0,};
						snprintf(time_str, sizeof(time_str) - 1, "%s", res);

						char temp_time[256] = {0,};
						snprintf(temp_time, sizeof(temp_time), "<font=Tizen:style=Regular color=#000000 align=left><font_size=30>%s</font_size></font>", time_str);

						Evas_Object* send_time = elm_label_add(obj);
						elm_object_text_set(send_time,temp_time);
						evas_object_size_hint_align_set(send_time, EVAS_HINT_FILL, EVAS_HINT_FILL);
						evas_object_size_hint_weight_set(send_time, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
						elm_object_style_set(send_time, "transparent");
						evas_object_show(send_time);
						elm_object_part_content_set(comp_img_layout, "swallow.chat_send_time", send_time);
						//elm_object_part_content_set(comp_img_layout, "swallow.chat_recv_time", send_time);


						Evas_Object *status_obj = elm_icon_add(obj);
						evas_object_size_hint_weight_set(status_obj, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
						evas_object_size_hint_align_set(status_obj, EVAS_HINT_FILL, EVAS_HINT_FILL);

						if(msg->msg_state == TG_MESSAGE_STATE_SENDING) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENDING_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_SENT) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENT_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_DELIVERED) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_DELIVERED_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_RECEIVED) {

						} else if(msg->msg_state == TG_MESSAGE_STATE_FAILED) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_FAILED_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_READ) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_READ_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_UNKNOWN) {

						}
						evas_object_show(status_obj);
						elm_object_part_content_set(comp_img_layout, "status_icon", status_obj);


						evas_object_data_set(comp_img_layout, "chat_list", (void*)chat_list);
						evas_object_data_set(comp_img_layout, "message_id", (void*)message_id);
						evas_object_data_set(comp_img_layout, "item_media", (void*)image);


						ad->loaded_msg_list = eina_list_append(ad->loaded_msg_list, comp_img_layout);

						char *sender_name = NULL;
						if(msg->out) {
							sender_name = replace(ad->current_user_data.print_name, '_', " ");
						} else {
							sender_name = replace(sel_item->use_data->print_name, '_', " ");
						}

						char temp_name[256] = {0,};
						snprintf(temp_name, sizeof(temp_name), "<font=Tizen:style=Regular color=#f16745 align=left><font_size=30>%s</font_size></font>", sender_name);

						if (sender_name) {
							free(sender_name);
							sender_name = NULL;
						}
						Evas_Object* sender_name_lbl = elm_label_add(obj);
						elm_object_text_set(sender_name_lbl,temp_name);
						evas_object_size_hint_align_set(sender_name_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
						evas_object_size_hint_weight_set(sender_name_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
						elm_object_style_set(sender_name_lbl, "transparent");
						evas_object_show(sender_name_lbl);
						elm_object_part_content_set(comp_img_layout, "swallow.chat_sender_name", sender_name_lbl);

						elm_object_part_content_set(img_layout, "swallow.chat_send_image", comp_img_layout);
					} else {

						Evas_Object* comp_img_layout = elm_layout_add(obj);
						elm_layout_file_set(comp_img_layout, edj_path, "chat_recv_image_box");
						evas_object_size_hint_weight_set(comp_img_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
						evas_object_size_hint_align_set(comp_img_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
						evas_object_show(comp_img_layout);

						if (is_blur_image) {
							Eina_List* img_sizes = get_image_sizes_from_db(atoll(msg->media_id));
							int row_count = eina_list_count(img_sizes);
							int size1 = 0;
							int size2 = 0;
							int size3 = 0;
							int size4 = 0;

							int width1 = 0;
							int height1 = 0;

							int width2 = 0;
							int height2 = 0;

							int width3 = 0;
							int height3 = 0;

							int width4 = 0;
							int height4 = 0;


							int img_size = 0;
							int img_width = 0;
							int img_height = 0;

							for (int i = 0 ; i < row_count ; i++) {
								Eina_List* row_vals = eina_list_nth(img_sizes, i);
								int* temp_size1 = (int*)eina_list_nth(row_vals, 0);
								if(temp_size1) {
									size1 = *temp_size1;
									free(temp_size1);
								}

								int* temp_width1 = (int*)eina_list_nth(row_vals, 1);
								if(temp_width1) {
									width1 = *temp_width1;
									free(temp_width1);
								}

								int* temp_height1 = (int*)eina_list_nth(row_vals, 2);
								if(temp_height1) {
									height1 = *temp_height1;
									free(temp_height1);
								}

								int* temp_size2 = (int*)eina_list_nth(row_vals, 3);
								if(temp_size2) {
									size2 = *temp_size2;
									free(temp_size2);
								}

								int* temp_width2 = (int*)eina_list_nth(row_vals, 4);
								if(temp_width2) {
									width2 = *temp_width2;
									free(temp_width2);
								}

								int* temp_height2 = (int*)eina_list_nth(row_vals, 5);
								if(temp_height2) {
									height2 = *temp_height2;
									free(temp_height2);
								}

								int* temp_size3 = (int*)eina_list_nth(row_vals, 6);
								if(temp_size3) {
									size3 = *temp_size3;
									free(temp_size3);
								}

								int* temp_width3 = (int*)eina_list_nth(row_vals, 7);
								if(temp_width3) {
									width3 = *temp_width3;
									free(temp_width3);
								}

								int* temp_height3 = (int*)eina_list_nth(row_vals, 8);
								if(temp_height3) {
									height3 = *temp_height3;
									free(temp_height3);
								}

								int* temp_size4 = (int*)eina_list_nth(row_vals, 9);
								if(temp_size4) {
									size4 = *temp_size4;
									free(temp_size4);
								}

								int* temp_width4 = (int*)eina_list_nth(row_vals, 10);
								if(temp_width4) {
									width4 = *temp_width4;
									free(temp_width4);
								}

								int* temp_height4 = (int*)eina_list_nth(row_vals, 11);
								if(temp_height4) {
									height4 = *temp_height4;
									free(temp_height4);
								}

								eina_list_free(row_vals);
								break;
							}
							eina_list_free(img_sizes);

							if (size1 > 0) {
								img_size = size1;
								img_width = width1;
								img_height = height1;
							} else if (size2 > 0) {
								img_size = size2;
								img_width = width2;
								img_height = height2;
							} else if (size3 > 0) {
								img_size = size3;
								img_width = width3;
								img_height = height3;
							} else if (size4 > 0) {
								img_size = size4;
								img_width = width4;
								img_height = height4;
							} else {

							}

							img_size = img_size >> 10; //convert to kbs

							int max_width = 240;
							int max_height = 400;

							while (img_width > max_width) {
								img_width = img_width / 2;
							}

							while (img_height > max_height) {
								img_height = img_height / 2;
							}

							//evas_object_resize(image, img_width, img_height);

							char img_size_str[10];
							sprintf(img_size_str, "%dkbs", img_size);


							Evas_Object* img_info_layout = elm_layout_add(obj);
							elm_layout_file_set(img_info_layout, edj_path, "chat_recv_image_info_box");
							evas_object_size_hint_weight_set(img_info_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
							evas_object_size_hint_align_set(img_info_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
							evas_object_show(img_info_layout);



							Evas_Object* img_size_lbl = elm_label_add(obj);
							elm_object_style_set(img_size_lbl, "transparent");

							char temp_size[256] = {0,};
							snprintf(temp_size, sizeof(temp_size), "<font=Tizen:style=Regular color=#ffffff align=left><font_size=30>%s</br></font_size></font>", img_size_str);
							Eina_Strbuf *buf = eina_strbuf_new();
							eina_strbuf_append(buf, temp_size);

							elm_object_text_set(img_size_lbl, eina_strbuf_string_get(buf));
							eina_strbuf_free(buf);
							evas_object_show(img_size_lbl);

							Evas_Object* download_img = create_image_object_from_file(ui_utils_get_resource(MEDIA_DOWNLOAD_ICON), obj);
							elm_image_resizable_set(download_img, EINA_TRUE, EINA_TRUE);
							elm_image_smooth_set(download_img, EINA_FALSE);
							elm_image_aspect_fixed_set(download_img, EINA_TRUE);
							elm_image_fill_outside_set(download_img, EINA_TRUE);
							elm_image_editable_set(download_img, EINA_TRUE);


							elm_object_part_content_set(img_info_layout, "swallow.chat_recv_image,size", img_size_lbl);
							elm_object_part_content_set(img_info_layout, "swallow.chat_recv_image,download", download_img);

							evas_object_data_set(image, "image_info_layout", (void*)(img_info_layout));


							elm_object_part_content_set(layout, "swallow.image_info", img_info_layout);
						}

						elm_object_part_content_set(comp_img_layout, "swallow.chat_recv_image", image);

						elm_object_part_content_set(layout, "swallow.img_bg", img_layout);


						time_t t = msg->date;
						const char *format = "%I:%M %P";
						struct tm lt;
						char res[32];
						(void) localtime_r(&t, &lt);

						if (strftime(res, sizeof(res), format, &lt) == 0) {
							(void) fprintf(stderr,  "strftime(3): cannot format supplied "
									"date/time into buffer of size %u "
									"using: '%s'\n",
									sizeof(res), format);
						}

						char time_str[20]={0,};
						snprintf(time_str, sizeof(time_str) - 1, "%s", res);

						char temp_time[256] = {0,};
						snprintf(temp_time, sizeof(temp_time), "<font=Tizen:style=Regular color=#000000 align=left><font_size=30>%s</font_size></font>", time_str);

						Evas_Object* send_time = elm_label_add(obj);
						elm_object_text_set(send_time,temp_time);
						evas_object_size_hint_align_set(send_time, EVAS_HINT_FILL, EVAS_HINT_FILL);
						evas_object_size_hint_weight_set(send_time, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
						elm_object_style_set(send_time, "transparent");
						evas_object_show(send_time);
						elm_object_part_content_set(comp_img_layout, "swallow.chat_recv_time", send_time);

						evas_object_data_set(image, "chat_list", (void*)chat_list);
						evas_object_data_set(image, "message_id", (void*)message_id);
						evas_object_data_set(image, "item_media", (void*)image);
						evas_object_data_set(image, "app_data", (void*)ad);
						evas_object_data_set(image, "media_id", (void*)strdup(msg->media_id));
						evas_object_data_set(image, "image_path", (void*)(img_path));




						ad->loaded_msg_list = eina_list_append(ad->loaded_msg_list, image);

						evas_object_smart_callback_add(image, "clicked", on_chat_media_item_clicked, (void*)(msg->media_id));


						char *sender_name = NULL;
						if(msg->out) {
							sender_name = replace(ad->current_user_data.print_name, '_', " ");
						} else {
							sender_name = replace(sel_item->use_data->print_name, '_', " ");
						}

						char temp_name[256] = {0,};
						snprintf(temp_name, sizeof(temp_name), "<font=Tizen:style=Regular color=#f16745 align=left><font_size=30>%s</font_size></font>", sender_name);

						if (sender_name) {
							free(sender_name);
							sender_name = NULL;
						}
						Evas_Object* sender_name_lbl = elm_label_add(obj);
						elm_object_text_set(sender_name_lbl,temp_name);
						evas_object_size_hint_align_set(sender_name_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
						evas_object_size_hint_weight_set(sender_name_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
						elm_object_style_set(sender_name_lbl, "transparent");
						evas_object_show(sender_name_lbl);
						elm_object_part_content_set(comp_img_layout, "swallow.chat_sender_name", sender_name_lbl);

						elm_object_part_content_set(img_layout, "swallow.chat_send_image", comp_img_layout);

					}
				}


				if(msg->message) {
					free(msg->message);
					msg->message = NULL;
				}

				if(msg->media_id) {
					free(msg->media_id);
					msg->media_id = NULL;
				}

				free(msg);

				return layout;

			}

			Evas_Object* entry = elm_entry_add(obj);
			evas_object_data_set(entry, "chat_list", (void*)chat_list);
			evas_object_data_set(entry, "message_id", (void*)message_id);

			elm_entry_editable_set(entry, EINA_FALSE);
			elm_entry_context_menu_disabled_set(entry, EINA_TRUE);

			//elm_entry_magnifier_disabled_set(entry, EINA_TRUE);

			char *sender_name = NULL;
			if(msg->out) {
				elm_layout_theme_set(layout, "layout", "bubble", "sentmessage1/default");
				elm_object_style_set(entry, "sentmessage1");
				sender_name = replace(ad->current_user_data.print_name, '_', " ");
			} else {
				elm_layout_theme_set(layout, "layout", "bubble", "readmessage1/default");
				elm_object_style_set(entry, "readmessage1");
				sender_name = replace(sel_item->use_data->print_name, '_', " ");
			}

			elm_entry_input_panel_enabled_set(entry, EINA_FALSE);
			evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(layout);
			char temp_name[256] = {0,};

			snprintf(temp_name, sizeof(temp_name), "<font=Tizen:style=Regular color=#f16745 align=left><font_size=12>%s</br></font_size></font>", sender_name);
			Eina_Strbuf *buf = eina_strbuf_new();
			eina_strbuf_append(buf, temp_name);

			if (sender_name) {
				free(sender_name);
				sender_name = NULL;
			}

			if (msg->media_type == tgl_message_media_none) {
				char temp_msg[4*256] = {0,};
				snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Regular color=#000000 align=left><font_size=12>%s</font_size></font>", msg->message);
				eina_strbuf_append(buf, temp_msg);
				elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
				eina_strbuf_free(buf);
			} else if(msg->media_type == tgl_message_media_photo) {


			} else if(msg->media_type == tgl_message_media_document) {

			} else if(msg->media_type == tgl_message_media_geo) {

			} else if(msg->media_type == tgl_message_media_contact) {

			} else if(msg->media_type == tgl_message_media_unsupported) {

			} else if(msg->media_type == tgl_message_media_photo_encr) {

			} else if(msg->media_type == tgl_message_media_document_encr) {

			} else  {

			}

			elm_object_part_content_set(layout, "elm.icon", entry );
			ad->loaded_msg_list = eina_list_append(ad->loaded_msg_list, entry);

			//set time
			time_t t = msg->date;
			const char *format = "%I:%M %P";
			struct tm lt;
			char res[32];
			(void) localtime_r(&t, &lt);

			if (strftime(res, sizeof(res), format, &lt) == 0) {
				(void) fprintf(stderr,  "strftime(3): cannot format supplied "
						"date/time into buffer of size %u "
						"using: '%s'\n",
						sizeof(res), format);
			}

			char time_str[20]={0,};
			snprintf(time_str, sizeof(time_str) - 1, "%s", res);
			elm_object_part_text_set(entry, "time", time_str);

			Evas_Object *status_obj;
			status_obj = elm_icon_add(entry);
			evas_object_size_hint_weight_set(status_obj, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(status_obj, EVAS_HINT_FILL, EVAS_HINT_FILL);

			if(msg->msg_state == TG_MESSAGE_STATE_SENDING) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENDING_ICON), NULL);
			} else if(msg->msg_state == TG_MESSAGE_STATE_SENT) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENT_ICON), NULL);
			} else if(msg->msg_state == TG_MESSAGE_STATE_DELIVERED) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_DELIVERED_ICON), NULL);
			} else if(msg->msg_state == TG_MESSAGE_STATE_RECEIVED) {

			} else if(msg->msg_state == TG_MESSAGE_STATE_FAILED) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_FAILED_ICON), NULL);
			} else if(msg->msg_state == TG_MESSAGE_STATE_READ) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_READ_ICON), NULL);
			} else if(msg->msg_state == TG_MESSAGE_STATE_UNKNOWN) {

			}

			elm_object_part_content_set(entry, "status_icon", status_obj);
			evas_object_show(status_obj);

			free(tablename);
			if(msg->message) {
				free(msg->message);
				msg->message = NULL;
			}

			if(msg->media_id) {
				free(msg->media_id);
				msg->media_id = NULL;
			}

			free(msg);
		}
	}

	return layout;
}

void on_text_message_clicked(void *data, Evas_Object *obj, void *event_info)
{

}

void on_text_message_received_from_buddy(appdata_s* ad, long long message_id, int type_of_chat)
{
	if (!ad) {
		return;
	}

	Evas_Object* chat_list = evas_object_data_get(ad->nf, "chat_list");
	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void *)message_id, NULL, ELM_GENLIST_ITEM_NONE, on_text_message_clicked, (void*)message_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);

	int user_id = (int)evas_object_data_get(chat_list, "user_id");
	user_data_with_pic_s *sel_item =  eina_list_nth(ad->buddy_list, user_id);

	send_request_for_marked_as_read(ad->service_client, sel_item->use_data->user_id.id, sel_item->use_data->user_id.type);
}


void on_media_download_completed(appdata_s* ad, int buddy_id, long long media_id, const char* file_path)
{
	if (!ad)
		return;

	if (ad->loaded_msg_list && eina_list_count(ad->loaded_msg_list) > 0) {
		for (int i = eina_list_count(ad->loaded_msg_list) - 1 ; i >= 0; i--) {
			Evas_Object* layout = eina_list_nth(ad->loaded_msg_list, i);
			if (layout) {
				char* media_id_str = evas_object_data_get(layout, "media_id");

				if (media_id_str) {
					long long lmedia_id = atoll(media_id_str);
					if (media_id == lmedia_id) {
						Evas_Object* img_obj = evas_object_data_get(layout, "item_media");
						if (img_obj) {

#if 0
							Eina_List* img_sizes = get_image_sizes_from_db(media_id);
							int row_count = eina_list_count(img_sizes);
							int size1 = 0;
							int size2 = 0;
							int size3 = 0;
							int size4 = 0;

							int width1 = 0;
							int height1 = 0;

							int width2 = 0;
							int height2 = 0;

							int width3 = 0;
							int height3 = 0;

							int width4 = 0;
							int height4 = 0;


							int img_size = 0;
							int img_width = 0;
							int img_height = 0;

							for (int i = 0 ; i < row_count ; i++) {
								Eina_List* row_vals = eina_list_nth(img_sizes, i);
								int* temp_size1 = (int*)eina_list_nth(row_vals, 0);
								if(temp_size1) {
									size1 = *temp_size1;
									free(temp_size1);
								}

								int* temp_width1 = (int*)eina_list_nth(row_vals, 1);
								if(temp_width1) {
									width1 = *temp_width1;
									free(temp_width1);
								}

								int* temp_height1 = (int*)eina_list_nth(row_vals, 2);
								if(temp_height1) {
									height1 = *temp_height1;
									free(temp_height1);
								}

								int* temp_size2 = (int*)eina_list_nth(row_vals, 3);
								if(temp_size2) {
									size2 = *temp_size2;
									free(temp_size2);
								}

								int* temp_width2 = (int*)eina_list_nth(row_vals, 4);
								if(temp_width2) {
									width2 = *temp_width2;
									free(temp_width2);
								}

								int* temp_height2 = (int*)eina_list_nth(row_vals, 5);
								if(temp_height2) {
									height2 = *temp_height2;
									free(temp_height2);
								}

								int* temp_size3 = (int*)eina_list_nth(row_vals, 6);
								if(temp_size3) {
									size3 = *temp_size3;
									free(temp_size3);
								}

								int* temp_width3 = (int*)eina_list_nth(row_vals, 7);
								if(temp_width3) {
									width3 = *temp_width3;
									free(temp_width3);
								}

								int* temp_height3 = (int*)eina_list_nth(row_vals, 8);
								if(temp_height3) {
									height3 = *temp_height3;
									free(temp_height3);
								}

								int* temp_size4 = (int*)eina_list_nth(row_vals, 9);
								if(temp_size4) {
									size4 = *temp_size4;
									free(temp_size4);
								}

								int* temp_width4 = (int*)eina_list_nth(row_vals, 10);
								if(temp_width4) {
									width4 = *temp_width4;
									free(temp_width4);
								}

								int* temp_height4 = (int*)eina_list_nth(row_vals, 11);
								if(temp_height4) {
									height4 = *temp_height4;
									free(temp_height4);
								}

								eina_list_free(row_vals);
								break;
							}
							eina_list_free(img_sizes);

							if (size1 > 0) {
								img_size = size1;
								img_width = width1;
								img_height = height1;
							} else if (size2 > 0) {
								img_size = size2;
								img_width = width2;
								img_height = height2;
							} else if (size3 > 0) {
								img_size = size3;
								img_width = width3;
								img_height = height3;
							} else if (size4 > 0) {
								img_size = size4;
								img_width = width4;
								img_height = height4;
							} else {

							}

							img_size = img_size >> 10; //convert to kbs

							int max_width = 240;
							int max_height = 100;

							while (img_width > max_width) {
								img_width = img_width / 2;
							}

							while (img_height > max_height) {
								img_height = img_height / 2;
							}
							evas_object_resize(img_obj, img_width, img_height);
#endif

							Evas_Object* img_info_layout = evas_object_data_get(img_obj, "image_info_layout");
							Evas_Object* progressbar = elm_object_part_content_get(img_info_layout, "swallow.chat_recv_image,progress");
							evas_object_del(progressbar);
							elm_image_file_set(img_obj, file_path, NULL);
						}
					}
				}
			}
		}
	}
}


void on_text_message_state_changed(appdata_s* ad, tg_message_s *msg, int type_of_chat)
{
	if (!ad)
		return;

	if (ad->loaded_msg_list && eina_list_count(ad->loaded_msg_list) > 0) {
		for (int i = eina_list_count(ad->loaded_msg_list) - 1 ; i >= 0; i--) {
			Evas_Object* entry = eina_list_nth(ad->loaded_msg_list, i);

			if (entry) {
				int message_id = (int)evas_object_data_get(entry, "message_id");
				if (message_id == msg->msg_id || message_id == msg->unique_id) {

					Evas_Object* status_obj = elm_object_part_content_get(entry, "status_icon");
					if (status_obj) {
						if(msg->msg_state == TG_MESSAGE_STATE_SENDING) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENDING_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_SENT) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENT_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_DELIVERED) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_DELIVERED_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_RECEIVED) {

						} else if(msg->msg_state == TG_MESSAGE_STATE_FAILED) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_FAILED_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_READ) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_READ_ICON), NULL);
						} else if(msg->msg_state == TG_MESSAGE_STATE_UNKNOWN) {

						}
					}
					return;
				}
			}
		}
	}
}

static void on_text_message_send_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");
	Evas_Object* text_entry = evas_object_data_get(chat_list, "text_entry");

	user_data_with_pic_s *sel_item =  eina_list_nth(ad->buddy_list, user_id);

	const char* text_to_send = elm_entry_entry_get(text_entry);
	if (!text_to_send || (strlen(text_to_send) == 0))
		return;

	int unique_id = time(NULL);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data.user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = 0;
	msg.message = (char*)text_to_send;
	msg.message_len = strlen(text_to_send);
	msg.media_type = tgl_message_media_none;
	msg.media_id = "";
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->user_id.id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;

	char* msg_table = get_table_name_from_number(msg.to_id);

	insert_msg_into_db(&msg, msg_table, unique_id);
	free(msg_table);

	// send request to service
	send_request_for_message_transport(ad->service_client, sel_item->use_data->user_id.id, msg.msg_id, tgl_message_media_none, text_to_send, sel_item->use_data->user_id.type);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void *)unique_id, NULL, ELM_GENLIST_ITEM_NONE, on_text_message_clicked, (void*)unique_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	elm_entry_entry_set(text_entry, "");
}


void on_user_presence_state_changed(appdata_s* ad, int buddy_id)
{
	if (!ad)
		return;

	Eina_List* buddy_details_array = get_buddy_info(buddy_id);
	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {
			int* temp_online = (int*)eina_list_nth(buddy_details, 12);
			int is_online = *temp_online;
			int* temp_last_seen = (int*)eina_list_nth(buddy_details, 13);
			int last_seen = *temp_last_seen;

			Evas_Object* profile_time = evas_object_data_get(ad->nf, "profile_time");

			char *format = NULL;
			Eina_Bool is_today = compare_date_with_current_date(last_seen);

			if (is_online > 0) {
				elm_object_text_set(profile_time,"online");
			} else {
				time_t t = last_seen;

				if (is_today) {
					format = "Last seen at Today, %I:%M %P";
				} else {
					format = "Last seen at %d/%b/%Y, %I:%M %P";
				}

				struct tm lt;
				char res[256];
				(void) localtime_r(&t, &lt);

				if (strftime(res, sizeof(res), format, &lt) == 0) {
					(void) fprintf(stderr,  "strftime(3): cannot format supplied "
							"date/time into buffer of size %u "
							"using: '%s'\n",
							sizeof(res), format);
				}

				char time_str[256]={0,};
				snprintf(time_str, sizeof(time_str) - 1, "<font=Tizen:style=Italic color=#000000 align=left><font_size=30>%s</font_size></font>", res);

				elm_object_text_set(profile_time,time_str);
			}

			for (int i = 0 ; i < eina_list_count(buddy_details_array); i++) {
				void* val = eina_list_nth(buddy_details, i);
				free(val);
			}
			eina_list_free(buddy_details);
		}
		eina_list_free(buddy_details_array);
	}
}

static void on_message_smiley_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* text_entry = data;
	//elm_entry_input_panel_hide(text_entry);
	elm_entry_input_panel_layout_set(text_entry,ELM_INPUT_PANEL_LAYOUT_EMOTICON);
	elm_object_focus_set(text_entry, EINA_TRUE);
	//elm_entry_input_panel_show(text_entry);
}

static void on_message_text_entry_clicked(void *data, Evas_Object *obj, void *event_info)
{
	//elm_entry_input_panel_hide(obj);
	elm_entry_input_panel_layout_set(obj,ELM_INPUT_PANEL_LAYOUT_NORMAL);
	//elm_entry_input_panel_show(obj);
}


Evas_Object* create_chat_genlist(Evas_Object *win)
{
    Evas_Object *genlist;
    Elm_Theme *theme = elm_theme_new();
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_GENLIST_THEME_EDJ, edj_path, (int)PATH_MAX);
	elm_theme_extension_add(theme, edj_path);
    genlist = elm_genlist_add(win);
    elm_object_theme_set(genlist, theme);
    elm_object_style_set(genlist, "telegram/default");
    evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);
    return genlist;
}

void on_list_media_item_clicked(void *data, Evas_Object *obj, void *event_info)
{

}


void send_image_message_to_buddy(void *data, const char* file_path)
{
	Evas_Object* chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");

	user_data_with_pic_s *sel_item =  eina_list_nth(ad->buddy_list, user_id);

	int unique_id = time(NULL);

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data.user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = tgl_message_media_photo;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->user_id.id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;

	char* msg_table = get_table_name_from_number(msg.to_id);

	insert_msg_into_db(&msg, msg_table, unique_id);

	Evas_Object* img = create_image_object_from_file(file_path, chat_list);

	int img_width = 0;
	int img_height = 0;
	elm_image_object_size_get(img, &img_width, &img_height);
	struct stat st;
	stat(file_path, &st);
	int img_size = st.st_size;
	evas_object_del(img);

	insert_media_info_to_db(&msg, (char*)file_path, img_width, img_height, img_size);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad->service_client, sel_item->use_data->user_id.id, msg.msg_id, unique_id, tgl_message_media_photo, file_path, TGL_PEER_USER);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "entry";
	itc.func.text_get = NULL;
	itc.func.content_get = on_message_item_content_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;
	Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void*)unique_id, NULL, ELM_GENLIST_ITEM_NONE, on_list_media_item_clicked, (void*)unique_id);
	elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
	free(msg.media_id);
}



void load_chat_history(Evas_Object* chat_list)
{
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	int user_id = (int)evas_object_data_get(chat_list, "user_id");

	user_data_with_pic_s *sel_item =  eina_list_nth(ad->buddy_list, user_id);
	int buddy_id = sel_item->use_data->user_id.id;

	char* tablename = get_table_name_from_number(buddy_id);

	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ID);

	Eina_List* vals = get_values_from_table_sync(db, tablename, col_names, col_types, NULL);
	close_database(db);

	if(!vals) {

	} else {
		int row_count = eina_list_count(vals);
		for (int i = 0 ; i < row_count ; i++) {
			Eina_List* row_vals = eina_list_nth(vals, i);
			int* temp_message_id = (int*)eina_list_nth(row_vals, 0);
			int message_id = *temp_message_id;
			static Elm_Genlist_Item_Class itc;
			itc.item_style = "entry";
			itc.func.text_get = NULL;
			itc.func.content_get = on_message_item_content_get_cb;
			itc.func.state_get = NULL;
			itc.func.del = NULL;
			Elm_Object_Item* item = elm_genlist_item_append(chat_list, &itc, (void *)message_id, NULL, ELM_GENLIST_ITEM_NONE, on_list_media_item_clicked, (void*)message_id);
			elm_genlist_item_show(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
			eina_list_free(row_vals);
		}
		eina_list_free(vals);
	}

	free(tablename);
}



void on_gallery_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {

		Evas_Object* chat_list = user_data;
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);

		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);
			send_image_message_to_buddy(chat_list, file_path);
			free(file_path);
			break;
		}
	}
}


void on_media_type_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* chat_list = data;
	appdata_s* ad = evas_object_data_get(chat_list, "app_data");
	const char *label = elm_object_item_text_get((Elm_Object_Item *) event_info);
	if (strcasecmp(label, POPUP_TEXT_TAKE_GALLERY) == 0 || strcasecmp(label, POPUP_TEXT_TAKE_PHOTO) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}

		if (strcasecmp(label, POPUP_TEXT_TAKE_PHOTO) == 0) {
			app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);
		} else {
			app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);
		}


		app_control_set_mime(app_control,"image/*");
		app_control_send_launch_request(app_control, &on_gallery_app_control_reply_cb, data);
		app_control_destroy(app_control);
	}
	evas_object_del(obj);
}


void popup_move_dropdown(Evas_Object *ctxpopup, Evas_Object *btn)
{
	Evas_Coord x, y, w , h;
	evas_object_geometry_get(btn, &x, &y, &w, &h);
	evas_object_move(ctxpopup, x + (w / 2), y + h);
}

void on_media_attach_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(obj);
}

static void on_media_attach_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* chat_list = data;

	Evas_Object *ctxpopup = elm_ctxpopup_add(chat_list);
	elm_object_style_set(ctxpopup, "dropdown/label");
	eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_BACK, eext_ctxpopup_back_cb, chat_list);
	evas_object_smart_callback_add(ctxpopup,"dismissed", on_media_attach_dismissed_cb, chat_list);

	elm_ctxpopup_item_append(ctxpopup, POPUP_TEXT_TAKE_PHOTO, create_image_object_from_file(ui_utils_get_resource(FM_ICON_CAMERA), chat_list), on_media_type_selected_cb, chat_list);
	elm_ctxpopup_item_append(ctxpopup, POPUP_TEXT_TAKE_GALLERY, create_image_object_from_file(ui_utils_get_resource(FM_ICON_GALLERY), chat_list), on_media_type_selected_cb, chat_list);
	elm_ctxpopup_item_append(ctxpopup, POPUP_TEXT_TAKE_VIDEO, create_image_object_from_file(ui_utils_get_resource(FM_ICON_VIDEO), chat_list), on_media_type_selected_cb, chat_list);
	elm_ctxpopup_item_append(ctxpopup, POPUP_TEXT_TAKE_FILE, create_image_object_from_file(ui_utils_get_resource(FM_ICON_FILE), chat_list), on_media_type_selected_cb, chat_list);
	elm_ctxpopup_item_append(ctxpopup, POPUP_TEXT_TAKE_LOCATION, create_image_object_from_file(ui_utils_get_resource(FM_ICON_LOCATION), chat_list), on_media_type_selected_cb, chat_list);

	elm_ctxpopup_direction_priority_set(ctxpopup, ELM_CTXPOPUP_DIRECTION_DOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN);

	popup_move_dropdown(ctxpopup, obj);
	evas_object_show(ctxpopup);
}

static void on_text_message_send_pressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(SEND_UNPRESSED_ICON), NULL);
}

static void on_text_message_send_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(SEND_PRESSED_ICON), NULL);
}

static void on_message_smiley_pressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(SMILEY_ICON_PRESSED), NULL);
}

static void on_message_smiley_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(SMILEY_ICON_UNPRESSED), NULL);
}


void launch_messaging_view_cb(appdata_s* ad, int user_id)
{
	if (!ad)
		return;

	ad->current_app_state = TG_CHAT_MESSAGING_VIEW_STATE;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);




	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "chat_messaging_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);



	user_data_with_pic_s *sel_item =  eina_list_nth(ad->buddy_list, user_id);
	user_data_s* user = sel_item->use_data;
	Evas_Object *profile_pic;
	if (user->photo_path && strcmp(user->photo_path, "") != 0) {
		profile_pic = create_image_object_from_file(user->photo_path, layout);
	} else {
		profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_PROFILE_PIC), layout);
	}


	/*************************** message list ************************************/

	Evas_Object* msg_box_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(msg_box_layout, edj_path, "custom_gen_list");
	evas_object_size_hint_weight_set(msg_box_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(msg_box_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(msg_box_layout);

#if 0
	Evas_Object* list_bg = elm_image_add(msg_box_layout);
	evas_object_size_hint_align_set(list_bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(list_bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_image_file_set(list_bg, ui_utils_get_resource(TG_CHAT_DEFAULT_BG), NULL);
    elm_image_resizable_set(list_bg, EINA_TRUE, EINA_TRUE);
    elm_image_fill_outside_set(list_bg, EINA_TRUE);
    evas_object_show(list_bg);

    Evas_Object* chat_conv_list = create_chat_genlist(ad->win);
#endif
#if 1
	Evas_Object* chat_conv_list = elm_genlist_add(ad->nf);
	elm_list_mode_set(chat_conv_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(chat_conv_list, ELM_LIST_COMPRESS);
	elm_object_style_set(chat_conv_list, "solid/default");
	evas_object_size_hint_weight_set(chat_conv_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(chat_conv_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_genlist_realization_mode_set(chat_conv_list, EINA_TRUE);
	//evas_object_color_set(chat_conv_list, 255 , 255, 255, 255);
#endif

	evas_object_show(chat_conv_list);

	//elm_object_part_content_set(msg_box_layout, "swallow.gen_list.bg", list_bg);
	elm_object_part_content_set(msg_box_layout, "swallow.gen_list", chat_conv_list);


	elm_object_part_content_set(layout, "swallow.chat_box", msg_box_layout);

	/*************************** message list ************************************/


	/********************** title layout ******************************/

/*
	Evas_Object* title_scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(title_scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(title_scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
*/

	Evas_Object* title_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(title_layout, edj_path, "message_title_box");
	evas_object_size_hint_weight_set(title_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(title_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(title_layout);

	Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(user_pic_layout, edj_path, "circle_layout");
	evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(user_pic_layout);
	elm_object_part_content_set(user_pic_layout, "content", profile_pic);

	Evas_Object* eo = elm_layout_add(ad->nf);
	elm_layout_theme_set(eo, "layout", "list/C/type.3", "default");
	elm_layout_content_set(eo, "elm.swallow.content", user_pic_layout);

	elm_object_part_content_set(title_layout, "swallow.profile_pic", eo);

	char* user_name = replace(sel_item->use_data->print_name, '_', " ");
	char temp_name[512] = {'\0'};
    snprintf(temp_name, 512, "<font=Tizen:style=Italic color=#000000 align=left><font_size=30>%s</font_size></font>", user_name);
    free(user_name);

	Evas_Object* profile_name = elm_label_add(title_layout);
	elm_object_text_set(profile_name,temp_name);
	evas_object_size_hint_align_set(profile_name, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(profile_name, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_style_set(profile_name, "transparent");
	evas_object_show(profile_name);
	elm_object_part_content_set(title_layout, "swallow.profile_name", profile_name);

	Evas_Object* profile_time = elm_label_add(title_layout);
	evas_object_size_hint_align_set(profile_time, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(profile_time, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(profile_time);
	elm_object_part_content_set(title_layout, "swallow.profile_time", profile_time);
	evas_object_data_set(ad->nf, "profile_time", (void*)profile_time);

	//elm_object_content_set(title_scroller, title_layout);

	on_user_presence_state_changed(ad, sel_item->use_data->user_id.id);

	elm_object_part_content_set(layout, "swallow.title_box", title_layout);


	/********************** title layout ******************************/

	/********************** entry layout*******************************/
	Evas_Object* entry_box_layout = elm_layout_add(ad->win);
	elm_layout_file_set(entry_box_layout, edj_path, "chat_entry_box");
	evas_object_size_hint_align_set(entry_box_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(entry_box_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(entry_box_layout);

	Evas_Object* attach_icon = elm_image_add(entry_box_layout);
	evas_object_size_hint_align_set(attach_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(attach_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_image_file_set(attach_icon, ui_utils_get_resource(ATTACH_ICON), NULL);
    elm_image_resizable_set(attach_icon, EINA_TRUE, EINA_TRUE);
    evas_object_show(attach_icon);
    evas_object_smart_callback_add(attach_icon, "clicked", on_media_attach_clicked, chat_conv_list);
	elm_object_part_content_set(entry_box_layout, "swallow.attach_icon", attach_icon);

	Evas_Object* text_entry = elm_entry_add(entry_box_layout);
	elm_object_part_text_set(text_entry, "elm.guide", "<font=Tizen:style=Italic color=#A8A8A8 valign=middle><font_size=35>Enter Message</font_size></font>");
	elm_entry_line_wrap_set(text_entry, EINA_TRUE);
	evas_object_size_hint_align_set(text_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(text_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(text_entry);
	elm_entry_scrollable_set(text_entry, EINA_TRUE);
	evas_object_smart_callback_add(text_entry, "clicked", on_message_text_entry_clicked, ad);
	elm_object_part_content_set(entry_box_layout, "swallow.text_entry", text_entry);

	elm_entry_text_style_user_push(text_entry, "DEFAULT='font_size=32 color=#000000 align=left font=Tizen:style=Italic'");

	//evas_object_data_set(chat_conv_list, "text_entry", (void*)text_entry);


	Evas_Object* smiley_btn = elm_button_add(entry_box_layout);
	elm_object_style_set(smiley_btn, "transparent");
	evas_object_size_hint_align_set(smiley_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(smiley_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	Evas_Object* smiley_icon = elm_image_add(entry_box_layout);
	evas_object_size_hint_align_set(smiley_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(smiley_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_image_file_set(smiley_icon, ui_utils_get_resource(SMILEY_ICON_UNPRESSED), NULL);
    elm_image_resizable_set(smiley_icon, EINA_TRUE, EINA_TRUE);
    evas_object_show(smiley_icon);
    elm_object_content_set(smiley_btn, smiley_icon);
    evas_object_smart_callback_add(smiley_btn, "clicked", on_message_smiley_clicked, text_entry);
    evas_object_smart_callback_add(smiley_btn, "pressed", on_message_smiley_pressed, smiley_icon);
    evas_object_smart_callback_add(smiley_btn, "unpressed", on_message_smiley_unpressed, smiley_icon);
	elm_object_part_content_set(entry_box_layout, "swallow.smiely_icon", smiley_btn);


	Evas_Object* send_btn = elm_button_add(entry_box_layout);
	elm_object_style_set(send_btn, "transparent");
	evas_object_size_hint_align_set(send_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(send_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	Evas_Object* send_icon = elm_image_add(entry_box_layout);
	evas_object_size_hint_align_set(send_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(send_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_image_file_set(send_icon, ui_utils_get_resource(SEND_PRESSED_ICON), NULL);
    elm_image_resizable_set(send_icon, EINA_TRUE, EINA_TRUE);
    evas_object_show(send_icon);

    elm_object_content_set(send_btn, send_icon);

    evas_object_smart_callback_add(send_btn, "clicked", on_text_message_send_clicked, chat_conv_list);
    evas_object_smart_callback_add(send_btn, "pressed", on_text_message_send_pressed, send_icon);
    evas_object_smart_callback_add(send_btn, "unpressed", on_text_message_send_unpressed, send_icon);
	elm_object_part_content_set(entry_box_layout, "swallow.send_icon", send_btn);

	elm_object_part_content_set(layout, "swallow.entry_box", entry_box_layout);
	/********************** entry layout*******************************/

	evas_object_data_set(ad->nf, "chat_list", (void*)chat_conv_list);
	evas_object_data_set(chat_conv_list, "app_data", ad);
	evas_object_data_set(chat_conv_list, "user_id", (void*)user_id);
	evas_object_data_set(chat_conv_list, "text_entry", (void*)text_entry);
	evas_object_data_set(chat_conv_list, "profile_time", (void*)profile_time);

	elm_naviframe_item_simple_push(ad->nf, scroller);
	load_chat_history(chat_conv_list);
	send_request_for_marked_as_read(ad->service_client, sel_item->use_data->user_id.id, sel_item->use_data->user_id.type);
}

