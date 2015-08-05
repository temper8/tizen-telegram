/*
 * tg_common.h
 *
 *  Created on: May 19, 2015
 *      Author: sandeep
 */

#ifndef TG_COMMON_H_
#define TG_COMMON_H_

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include "service_client.h"

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "telegram_tizen"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.telegram_tizen"
#endif

#define EDJ_REG_FILE "edje/telegram_tizen_reg.edj"
#define EDJ_LOGIN_FILE "edje/telegram_tizen_login.edj"
#define EDJ_CHAT_LIST_FILE "edje/telegram_chat_list.edj"
#define EDJ_CHAT_CONV_FILE "edje/telegram_chat_conv.edj"

#define GRP_MAIN "main"
#define DEFAULT_TELEGRAM_PATH "/opt/usr/media/telegram/"
#define DEFAULT_TG_DATABASE_PATH "/opt/usr/media/telegram/tg_data_base.db"

#define FM_ICON_PATH "images/"
#define FM_ICON_ROBO_BUDDY       FM_ICON_PATH"robo_buddy.png"
#define SEARCH_ICON FM_ICON_PATH"/search_icon.png"
#define ATTACH_ICON FM_ICON_PATH"/attach_icon.png"
#define SMILEY_ICON FM_ICON_PATH"/smiley_icon.png"
#define SEND_ICON FM_ICON_PATH"/send_icon.png"
#define CHAT_BG FM_ICON_PATH"/chat_bg.jpg"
#define BLUR_BG FM_ICON_PATH"/blur_img.jpg"
#define CAMERA_ICON FM_ICON_PATH"/camera-icon.png"

#define FM_ICON_MSG_SENT       FM_ICON_PATH"bubble_sent_bg.#.png"
#define FM_ICON_MSG_RECEIVE       FM_ICON_PATH"bubble_rec_bg.#.png"

#define FM_OK_BUTTON       FM_ICON_PATH"ok_bn_press.png"
#define FM_CANCEL_BUTTON       FM_ICON_PATH"cancel_bn_press.png"

#define TELEGRAM_DEBUG_LOG(fmt, args...) LOGD(" +++ LOG : "fmt, ##args)

#define retv_if (expr, val) do { \
		if (expr) { \
			TELEGRAM_DEBUG_LOG("(%s) -> %s() return", #expr, __func__); \
			return (val); \
		} \
} while (0)

#define SAFE_STRCMP(str1, str2)   ((str1 && str2) ? strcmp(str1, str2) : -1)
#define SAFE_STRDUP(text)		(text == NULL ? NULL : strdup(text))	//what to use for strcpy?
#define SAFE_STRLEN(src)	\
		((src != NULL)? strlen(src): 0)
#define ELM_OBJ_PART_TEXT_SET(obj, part, text) 		elm_object_domain_translatable_part_text_set(obj, part, "telegram", text)


#define TGL_PEER_USER 1
#define TGL_PEER_CHAT 2
#define TGL_PEER_GEO_CHAT 3
#define TGL_PEER_ENCR_CHAT 4
#define TGL_PEER_UNKNOWN 0


typedef struct {
	int type;
	int id;
} tgl_peer_id_t;

typedef enum state_of_app {
	TG_SPLASH_SCREEN_STATE,
	TG_REGISTRATION_STATE,
	TG_PROFILE_REGISTRATION_STATE,
	TG_LOGIN_STATE,
	TG_BUDDY_LIST_STATE,
	TG_BUDDY_LIST_SELECTION_STATE,
	TG_GROUP_CHAT_NAME_ENTRY_STATE,
	TG_BUDDY_CHAT_STATE,
	TG_BUDDY_CHAT_CONV_STATE
} state_of_app_s;

enum tgl_typing_status {
	tgl_typing_none = 1,
	tgl_typing_typing,
	tgl_typing_cancel,
	tgl_typing_record_video,
	tgl_typing_upload_video,
	tgl_typing_record_audio,
	tgl_typing_upload_audio,
	tgl_typing_upload_photo,
	tgl_typing_upload_document,
	tgl_typing_geo,
	tgl_typing_choose_contact
};



typedef struct user_data {
	tgl_peer_id_t user_id;
	char* print_name;
	int structure_version;
	char* photo_path;
	int photo_id;
	char* first_name;
	char* last_name;
	char* phone;
	int access_hash;
	char* real_first_name;
	char* real_last_name;
	char* username;
	int online;
	int last_seen;
	Eina_Bool is_selected;
} user_data_s;

typedef struct user_data_with_pic {
	user_data_s *use_data;
	//char* pic_file_location;
	Evas_Object *contact_icon;
} user_data_with_pic_s;

enum tgl_message_media_type {
	tgl_message_media_none,
	tgl_message_media_photo,
	//tgl_message_media_video,
	//tgl_message_media_audio,
	tgl_message_media_document,
	tgl_message_media_geo,
	tgl_message_media_contact,
	tgl_message_media_unsupported,
	tgl_message_media_photo_encr,
	//tgl_message_media_video_encr,
	//tgl_message_media_audio_encr,
	tgl_message_media_document_encr,
};

typedef struct tg_chat_info {
	int chat_id;
	int flags;
	char* print_title;
	int struct_version;
	long long photo_id;
	char* photo_path;
	char* title;
	int users_num;
	int user_list_size;
	int user_list_version;
	int inviter_id;
	int chat_users[100];
	int date;
	int version;
	int admin_id;
} tg_chat_info_s;

typedef struct tg_peer_info {
	int peer_id;
	int peer_type;
	int flags;
	long long last_msg_id;
	int last_msg_date;
	char* print_name;
	int struct_version;
	int no_of_unread_msgs;
	int last_seen_time;
	char* photo_path;
	long long photo_id;
} tg_peer_info_s;

typedef struct peer_with_pic {
	tg_peer_info_s *use_data;
	Evas_Object *contact_icon;
} peer_with_pic_s;

typedef struct group_chat_with_pic {
	tg_chat_info_s *use_data;
	Evas_Object *contact_icon;
} group_chat_with_pic_s;

typedef struct tg_message {
	int msg_id;
	int flags;
	int fwd_from_id;
	int fwd_date;
	int from_id;
	int to_id;
	int out;
	int unread;
	int date;
	int service;
	char* message;
	int message_len;
	int media_type;
	char* media_id;
	int unique_id;
} tg_message_s;

typedef struct appdata {
	Evas_Object* win;
	Evas_Object* layout;
	Evas_Object* conform;
	Evas_Object* nf;
	Evas_Object* panel;
	struct event_base *basic_event;
	char* phone_number;
	char* sms_code;
	Eina_List* buddy_list;
	Eina_List* group_chat_list;
	Eina_List* peer_list;
	int curtimezoneoffset;
	int curtimeformat;
	tgl_peer_id_t user_id;
	state_of_app_s current_app_state;
	user_data_s current_user_data;
	tg_peer_info_s* buddy_in_cahtting_data;
	Eina_Bool is_network_connected;
	service_client* service_client;
	Eina_Bool is_first_time_registration;
} appdata_s;

extern void show_toast(appdata_s* ad, char* value);
extern void layout_back_cb(void *data, Evas_Object *obj, void *event_info);
extern void tg_login_nf_back_cb(void *data, Evas_Object *obj, void *event_info);
extern void detail_list_nf_back_cb(void *data, Evas_Object *obj, void *event_info);
extern void load_rec_msg_to_db(struct tgl_state *TLS, struct tgl_message *M);
extern void create_buddy_msg_table(const char* table_name);
extern void insert_msg_into_db(struct tgl_message *M, char* table_name, int unique_id);
extern void update_msg_into_db(struct tgl_message *M, char* table_name, int unique_id);
extern void insert_photo_info_to_db(struct tgl_message *M, char* file_path);
extern void update_photo_info_in_db(struct tgl_message *M, char* file_path, int unique_val);
extern void load_buddy_list_data(appdata_s *ad);
extern void load_group_chat_data(appdata_s *ad);
extern void load_peer_data(appdata_s *ad);

#if 0
static char *trim(char *s) {
    char *ptr;
    if (!s)
        return NULL;   // handle NULL string
    if (!*s)
        return s;      // handle empty string
    for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr);
    ptr[1] = '\0';
    return s;
}
#endif

static char*  trim(char * s)
{
	if (!s)
		return NULL;

	int l = strlen(s);

	while (isspace(s[l - 1]))
		--l;
	while (* s && isspace(* s))
		++s, --l;

	return strndup(s, l);
}

static int numbers_only(const char *s)
{
	return 1;
}

static void app_get_resource(const char *edj_file_in, char *edj_path_out, int edj_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(edj_path_out, edj_path_max, "%s%s", res_path, edj_file_in);
		free(res_path);
	}
}

static void telegram_image_mask_delete_cb(Evas_Object *obj)
{
	if (obj == NULL)
		return;

	void *mask = evas_object_image_data_get(obj, EINA_TRUE);
	if (mask) {
		free(mask);
		mask = NULL;
	}
}

//static char* get_table_name_from_number(const char* phone_no)
static char* get_table_name_from_number(const int id)
{
	char id_str[50];
	sprintf(id_str, "%d", id);
	char* msg_table = (char*)malloc(strlen("tg_") + strlen(id_str) + strlen("_msg") + 1);
	strcpy(msg_table, "tg_");
	strcat(msg_table, id_str);
	strcat(msg_table, "_msg");
	return msg_table;
}

static void telegram_set_mask_and_circular_pic(Evas_Object *image, char *image_path, char *mask_path, int width, int height)
{
	if (image == NULL)
		return;
	if (image_path == NULL)
		return;

	Evas_Object *img_obj = NULL;
	void *mask;
	//if (image_path != NULL)
	//mask = ea_image_effect_mask(image_path, mask_path, width, height, 0, 0);
	img_obj = elm_image_object_get(image);
	evas_object_image_colorspace_set(img_obj, EVAS_COLORSPACE_ARGB8888);
	evas_object_image_size_set(img_obj, width, height);
	evas_object_image_data_set(img_obj, mask);
	evas_object_image_alpha_set(img_obj, EINA_TRUE);
	evas_object_event_callback_add(img_obj, EVAS_CALLBACK_DEL, telegram_image_mask_delete_cb, NULL);
}

static Evas_Object* buddy_widget_main_icon_get(const char *icon_name, Evas_Object *parent)
{
    Evas_Object *icon = elm_image_add(parent);
    elm_object_focus_set(icon, EINA_FALSE);
    elm_image_file_set(icon, icon_name, NULL);
    evas_object_show(icon);
    return icon;
}

static void buddy_icon_del_cb(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	user_data_with_pic_s *item  = data;
	item->contact_icon = NULL;
}

static const char *_ui_utils_get_res_path()
{
	char res_folder_path[PATH_MAX] = {'\0'};
	if (res_folder_path[0] == '\0') {
		char *res_path_buff = app_get_resource_path();
		strncpy(res_folder_path, res_path_buff, PATH_MAX-1);
		free(res_path_buff);
	}
	return res_folder_path;
}

static char *ui_utils_get_resource(const char *res_name)
{
	static char res_path[PATH_MAX] = {'\0'};
	snprintf(res_path, PATH_MAX, "%s%s", _ui_utils_get_res_path(), res_name);
	return res_path;
}

static char* get_current_time()
{
	Eina_Strbuf *strbuf = eina_strbuf_new();
	time_t local_time = time(NULL);
	char buf[200] = {0};
	char *ret = NULL;
	struct tm *time_info = localtime(&local_time);

	strftime(buf, 200, "%l:%M", time_info);
	eina_strbuf_append_printf(strbuf, "%s %s", buf, (time_info->tm_hour >= 12) ? "PM":"AM");
	ret = eina_strbuf_string_steal(strbuf);
	eina_strbuf_free(strbuf);
	return ret;
}

typedef struct _telegram_Time
{
	int hours;
	int minutes;
	int ampm; /* 0 for AM, 1 for PM */
	int days;

} telegram_time;

typedef enum {
	telegram_TIME_FORMAT_12H = 0,
	telegram_TIME_FORMAT_24H,
	telegram_TIME_FORMAT_UNKNOWN

} telegram_time_format;

typedef struct Buddy {
	int buddyNO;
	char* buddyID;
	char* name;
	char* initialConsonant;
	char* statusMsg;
	char favoriteFlag;
	char friendStatus;
	char* profilePath;
	char* birthday;
	char* email;
	int rank;
	long updateTime;
	char* phoneNumber;
	char* orgNums;
	int grade;
	char* emailAccount;
	char relationHideFlag;
	char updateStatus;
	char knownPhoneNumberFlag;
	char phoneNumberShowFlag;
	char whoBlindMeFlag;
	char voipFlag;
	char isBlindedFlag;
	char* extraInfo ;
	int nameInfo ;
	char* msisdns;
	char* smsContacts;
} Buddy;

#endif /* TG_COMMON_H_ */
