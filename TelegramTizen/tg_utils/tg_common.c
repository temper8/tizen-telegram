#include <stdio.h>
#include <unistd.h>
#include <app.h>
#include "tg_common.h"
#include "tg_db_wrapper.h"
#include <media_content.h>
#include "tg_start_messaging_view.h"

void app_get_resource(const char *edj_file_in, char *edj_path_out, int edj_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(edj_path_out, edj_path_max, "%s%s", res_path, edj_file_in);
		free(res_path);
	}
}

Eina_Bool compare_date_with_current_date(int rtime)
{

	const char *format = " %d/%b/%Y";
	time_t local_t = time(NULL);
	struct tm lt;
	char local_res[256];
	(void) localtime_r(&local_t, &lt);
	if (strftime(local_res, sizeof(local_res), format, &lt) == 0) {
		return EINA_FALSE;
	}


	time_t remote_t = rtime;
	struct tm rt;
	char remote_res[32];
	(void) localtime_r(&remote_t, &rt);

	if (strftime(remote_res, sizeof(remote_res), format, &rt) == 0) {
		return EINA_FALSE;
	}
	if (strcasecmp (local_res, remote_res) == 0) {
		return EINA_TRUE;
	}
	return EINA_FALSE;
}

Evas_Object* create_button(Evas_Object *parent, char *style, char *text)
{
	Evas_Object *button;

	button = elm_button_add(parent);
	if (style)
		elm_object_style_set(button, style);
	if (text)
		elm_object_text_set(button, text);
	evas_object_show(button);

	return button;
}

Evas_Object* create_circle_button(Evas_Object *parent, char* text, char* filepath)
{
	Evas_Object *button, *image;
	button= elm_button_add(parent);
	elm_object_style_set(button, "circle");
	if (text)
		elm_object_text_set(button, text);
	image = elm_image_add(button);
	elm_image_file_set(image, filepath, NULL);
	elm_image_resizable_set(image, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(button, "icon", image);
	evas_object_smart_callback_add(button, "clicked", NULL, NULL);
	evas_object_show(button);
	return button;
}

char* get_table_name_from_number(const int id)
{
	char id_str[50];
	sprintf(id_str, "%d", id);
	char* msg_table = (char*)malloc(strlen("tg_") + strlen(id_str) + strlen("_msg") + 1);
	strcpy(msg_table, "tg_");
	strcat(msg_table, id_str);
	strcat(msg_table, "_msg");
	return msg_table;
}

char* get_budy_state(appdata_s* ad, int buddy_id)
{
	if (!ad)
		return NULL;
	char time_str[256]={0,};
	Eina_List* buddy_details_array = get_buddy_info(buddy_id);
	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {
			int* temp_online = (int*)eina_list_nth(buddy_details, 12);
			int is_online = *temp_online;
			int* temp_last_seen = (int*)eina_list_nth(buddy_details, 13);
			int last_seen = *temp_last_seen;

			char *format = NULL;
			Eina_Bool is_today = compare_date_with_current_date(last_seen);

			if (is_online > 0) {
				strcpy(time_str,"online");
			} else {
				time_t t = last_seen;

				if (is_today) {
					format = "last seen Today at %I:%M %P";
				} else {
					format = "last seen %d/%b/%Y at %I:%M %P";
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
				snprintf(time_str, sizeof(time_str), "<align=left><font_size=30><color=#808080>%s</color></font_size></align>", res);
			}

			for (int i = 0 ; i < eina_list_count(buddy_details_array); i++) {
				void* val = eina_list_nth(buddy_details, i);
				free(val);
			}
			eina_list_free(buddy_details);
		}
		eina_list_free(buddy_details_array);
	}
	return strdup(time_str);
}

int numbers_only(const char *s)
{
	return 1;
}

static bool mp_util_svc_iterate_for_get_video_item_cb(media_info_h item, void *user_data)
{
	return TRUE;
}



static bool __thumbnail_cb(media_info_h item, void *user_data)
{
	char **thumbnail_path = (char **) user_data;

	if(thumbnail_path == NULL)
		return FALSE;

	if (media_info_get_thumbnail_path(item, thumbnail_path) != MEDIA_CONTENT_ERROR_NONE) {
		return FALSE;
	}
	if (*thumbnail_path) {
	}
	return TRUE;
}

Eina_Bool get_thumbnail_from_video_url(const char *file_path, char **thumbnail_path)
{
	if (thumbnail_path == NULL) {
		return FALSE;
	}
	char condition[512 + 1] = { '\0', };
	int ret=-1;
	//snprintf(condition, 512, "%s ", file_path);
	snprintf(condition, 512, "%s = \'%s\'", MEDIA_PATH, (char *)file_path);
	ret = media_content_connect();

	filter_h filter = NULL;
	ret = media_filter_create(&filter);
	if(ret != MEDIA_CONTENT_ERROR_NONE)  {
		goto ERROR_THROW;
	}

	ret = media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		goto ERROR_THROW;
	}

	char *temp_thumbnail_path = NULL;
	ret = media_info_foreach_media_from_db(filter, __thumbnail_cb, &temp_thumbnail_path);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		goto ERROR_THROW;
	}
	*thumbnail_path = temp_thumbnail_path;
	if (filter) {
		media_filter_destroy(filter);
	}
	filter = NULL;
	ret = media_content_disconnect();
	return TRUE;

ERROR_THROW:
	if (filter) {
		media_filter_destroy(filter);
	}
	filter = NULL;
	ret = media_content_disconnect();
	return FALSE;
}

void show_loading_popup(appdata_s* ad)
{
	if (!ad)
		return;

	if (ad->loading_popup) {
		evas_object_del(ad->loading_popup);
		ad->loading_popup = NULL;
	}

	Evas_Object *layout;
	Evas_Object *progressbar;


	ad->loading_popup = elm_popup_add(ad->win);
	elm_popup_align_set(ad->loading_popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(ad->loading_popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* layout */
	layout = elm_layout_add(ad->loading_popup);
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_POPUP_VIEW_EDJ, edj_path, (int)PATH_MAX);
	elm_layout_file_set(layout, edj_path, "processing_view_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(layout, "elm.text", "<font=Tizen:style=Italic color=#666362 align=left><font_size=36>Loading...</font_size></font>");
	progressbar = elm_progressbar_add(layout);
	elm_object_style_set(progressbar, "process_medium");
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_pulse(progressbar, EINA_TRUE);
	elm_object_part_content_set(layout, "processing", progressbar);

	elm_object_content_set(ad->loading_popup, layout);

	evas_object_show(ad->loading_popup);

}

void hide_loading_popup(appdata_s* ad)
{
	if (!ad)
		return;

	if (ad->loading_popup) {
		evas_object_del(ad->loading_popup);
		ad->loading_popup = NULL;
	}
}

void launch_app_control(appdata_s *ad, char *media_type, char *url)
{
	if (!media_type || !url) {
		return;
	}
	app_control_h app_control;
	int ret = app_control_create(&app_control);
	if(ret != APP_CONTROL_ERROR_NONE) {
		show_toast(ad, "Error: Can not load image");
		return;
	}
	app_control_set_operation(app_control, APP_CONTROL_OPERATION_VIEW);
	if (strstr(media_type, "video") != NULL) {
		app_control_set_mime(app_control,"video/*");
		app_control_set_app_id(app_control, "com.samsung.video-player-lite");
	} else if (strstr(media_type, "audio") != NULL) {
		app_control_set_mime(app_control,"audio/*");
	} else if (strstr(media_type, "image") != NULL) {
		app_control_set_mime(app_control,"image/*");
	} else if (strstr(media_type, "location") != NULL) {
		app_control_set_app_id(app_control, "com.samsung.browser");
	}
	app_control_set_uri(app_control, url);


	int nRet = app_control_send_launch_request(app_control, NULL, NULL);
	if(nRet != APP_CONTROL_ERROR_NONE) {
		if(nRet == APP_CONTROL_ERROR_INVALID_PARAMETER) {
			printf("app_control_send_launch_request is fail APP_CONTROL_ERROR_INVALID_PARAMETER [0x%x]", nRet);
		}
		else if(nRet == APP_CONTROL_ERROR_OUT_OF_MEMORY ) {
			printf("app_control_send_launch_request is fail APP_CONTROL_ERROR_OUT_OF_MEMORY [0x%x]", nRet);
		}
		else if(nRet == APP_CONTROL_ERROR_APP_NOT_FOUND ) {
			printf("app_control_send_launch_request is fail APP_CONTROL_ERROR_APP_NOT_FOUND [0x%x]", nRet);
		}
		else if(nRet == APP_CONTROL_ERROR_KEY_NOT_FOUND ) {
			printf("app_control_send_launch_request is fail APP_CONTROL_ERROR_KEY_NOT_FOUND [0x%x]", nRet);
		}
		else if(nRet == APP_CONTROL_ERROR_KEY_REJECTED ) {
			printf("app_control_send_launch_request is fail APP_CONTROL_ERROR_KEY_REJECTED [0x%x]", nRet);
		}
		else if(nRet == APP_CONTROL_ERROR_INVALID_DATA_TYPE ) {
			printf("app_control_send_launch_request is fail APP_CONTROL_ERROR_INVALID_DATA_TYPE [0x%x]", nRet);
		}
		else if(nRet == APP_CONTROL_ERROR_LAUNCH_REJECTED ) {
			printf("app_control_send_launch_request is fail APP_CONTROL_ERROR_LAUNCH_REJECTED [0x%x]", nRet);
		}
	}
	app_control_destroy(app_control);

}

void free_user_data(user_data_s *user_data)
{
	if (!user_data) {
		return;
	}

	if (user_data->print_name) {
		free(user_data->print_name);
		user_data->print_name = NULL;
	}

	if (user_data->first_name) {
		free(user_data->first_name);
		user_data->first_name = NULL;
	}

	if (user_data->last_name) {
		free(user_data->last_name);
		user_data->last_name = NULL;
	}

	if (user_data->phone) {
		free(user_data->phone);
		user_data->phone = NULL;
	}

	if (user_data->real_first_name) {
		free(user_data->real_first_name);
		user_data->real_first_name = NULL;
	}
	if (user_data->real_last_name) {
		free(user_data->real_last_name);
		user_data->real_last_name = NULL;
	}
	if (user_data->username) {
		free(user_data->username);
		user_data->username = NULL;
	}

	free(user_data);
	user_data = NULL;
}


void tg_notification_create(appdata_s *app_data, char * icon_path, const char *title, char *content, char *sound_path, char *app_id)
{
	int err = NOTIFICATION_ERROR_NONE;
	if (app_data && app_data->s_notififcation) {
		//err = notification_delete(app_data->s_notififcation);
		notification_delete_all(NOTIFICATION_TYPE_NOTI);
		app_data->s_notififcation = NULL;
	}

	notification_error_e ret = NOTIFICATION_ERROR_NONE;
	app_data->s_notififcation = notification_create(NOTIFICATION_TYPE_NOTI);
	ret = notification_set_property(app_data->s_notififcation, NOTIFICATION_PROP_DISABLE_TICKERNOTI);
	ret = notification_set_layout(app_data->s_notififcation, NOTIFICATION_LY_NOTI_EVENT_SINGLE);

	if (icon_path) {
		ret = notification_set_image(app_data->s_notififcation, NOTIFICATION_IMAGE_TYPE_ICON, icon_path);
	}
	if (title) {
		ret = notification_set_text(app_data->s_notififcation, NOTIFICATION_TEXT_TYPE_TITLE, title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	}
	if (content) {
		ret = notification_set_text(app_data->s_notififcation, NOTIFICATION_TEXT_TYPE_CONTENT, content, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	}

	if (sound_path) {
		ret = notification_set_sound(app_data->s_notififcation, NOTIFICATION_SOUND_TYPE_USER_DATA, sound_path);
	} else {
		ret = notification_set_sound(app_data->s_notififcation, NOTIFICATION_SOUND_TYPE_DEFAULT, NULL);
	}
	ret = notification_set_vibration(app_data->s_notififcation, NOTIFICATION_VIBRATION_TYPE_DEFAULT, NULL);
	if (ret != NOTIFICATION_ERROR_NONE) {
		//failed
	}
	app_control_h service = NULL;
	app_control_create(&service);
	app_control_set_app_id(service, app_id);
	app_control_set_operation(service, APP_CONTROL_OPERATION_DEFAULT);

	//notification_update()

	ret  = notification_set_launch_option(app_data->s_notififcation, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, service);
	if (ret != NOTIFICATION_ERROR_NONE) {
		//failed
	}
	notification_post(app_data->s_notififcation);
	app_control_destroy(service);
	ret = notification_free(app_data->s_notififcation);
	if(ret != NOTIFICATION_ERROR_NONE) {
	}
	return;
}

void on_new_message_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;

	if (!ad->buddy_list || eina_list_count(ad->buddy_list) <= 0) {
		load_buddy_list_data(ad);
	}
	delete_floating_button(ad);
	launch_start_messaging_view(ad);
}


void create_floating_button(appdata_s* ad)
{
	if (!ad)
		return;
	if (ad->floating_btn)
		return;

    Evas_Object *pencil_icon = elm_image_add(ad->nf);
    elm_image_file_set(pencil_icon, ui_utils_get_resource(TG_ICON_FLOATING_PENCIL), NULL);
    evas_object_show(pencil_icon);
	ad->floating_btn = eext_floatingbutton_add(ad->layout);
	evas_object_color_set(ad->floating_btn, 255, 255, 255, 255);
	elm_object_part_content_set(ad->layout, "elm.swallow.floatingbutton", ad->floating_btn);
	/* Floating Button 1 */
	Evas_Object *new_msg_btn = elm_button_add(ad->floating_btn);
	evas_object_smart_callback_add(new_msg_btn, "clicked", on_new_message_clicked, ad);
	elm_object_part_content_set(ad->floating_btn, "button1", new_msg_btn);
	elm_object_part_content_set(new_msg_btn, "icon", pencil_icon);
}

void delete_floating_button(appdata_s* ad)
{
	if (!ad)
		return;

	if (ad->floating_btn){
		evas_object_del(ad->floating_btn);
		ad->floating_btn = NULL;
	}
}
