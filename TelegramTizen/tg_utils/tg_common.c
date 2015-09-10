#include <stdio.h>
#include <unistd.h>
#include <app.h>
#include "tg_common.h"

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

int numbers_only(const char *s)
{
	return 1;
}
