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

#define TELEGRAM_CUSTOM_WINSET_EDJ	"edje/telegram_theme.edj"
#define TELEGRAM_CHAT_VIEW_EDJ	"edje/telegram_chat_view.edj"
#define TELEGRAM_INIT_VIEW_EDJ	"edje/telegram_init_screen.edj"
#define TELEGRAM_GENLIST_THEME_EDJ	"edje/telegram_genlist_theme.edj"


#define GRP_MAIN "main"
#define DEFAULT_TELEGRAM_PATH "/opt/usr/media/telegram/"
#define DEFAULT_TG_DATABASE_PATH "/opt/usr/media/telegram/tg_data_base.db"

#define FM_ICON_PATH "images/"
#define DEFAULT_PROFILE_PIC       FM_ICON_PATH"default_profile_pic.png"
#define FM_ICON_ROBO_BUDDY       FM_ICON_PATH"robo_buddy.png"
#define SEARCH_ICON FM_ICON_PATH"/search_icon.png"
#define ATTACH_ICON FM_ICON_PATH"/ic_ab_attach.png"
#define SMILEY_ICON_UNPRESSED FM_ICON_PATH"/ic_msg_panel_smiles_pressed.png"
#define SMILEY_ICON_PRESSED FM_ICON_PATH"/ic_msg_panel_smiles_unpressed.png"
#define SEND_UNPRESSED_ICON FM_ICON_PATH"/ic_send_pressed.png"
#define SEND_PRESSED_ICON FM_ICON_PATH"/ic_send_unpressed.png"
#define CHAT_BG FM_ICON_PATH"/chat_bg.jpg"
#define BLUR_BG FM_ICON_PATH"/blur_img.jpg"
#define CAMERA_ICON FM_ICON_PATH"/camera-icon.png"
#define MESSAGE_READ_ICON FM_ICON_PATH"/ic_message_read.png"
#define MESSAGE_SENDING_ICON FM_ICON_PATH"/ic_message_sending.png"
#define MESSAGE_SENT_ICON FM_ICON_PATH"/ic_message_sent.png"
#define MESSAGE_FAILED_ICON FM_ICON_PATH"/ic_message_failed.png"
#define MESSAGE_DELIVERED_ICON FM_ICON_PATH"/ic_message_delivered.png"

#define MEDIA_DOWNLOAD_ICON FM_ICON_PATH"/ic_attach_download.png"
#define MEDIA_MANUAL_DOWNLOAD_ICON FM_ICON_PATH"/ic_attach_manual_download.png"


#define FM_ICON_CAMERA       FM_ICON_PATH"floating_camera.png"
#define FM_ICON_GALLERY       FM_ICON_PATH"ic_attach_gallery.png"
#define FM_ICON_VIDEO       FM_ICON_PATH"ic_attach_video.png"
#define FM_ICON_FILE       FM_ICON_PATH"ic_attach_doc.png"
#define FM_ICON_LOCATION       FM_ICON_PATH"ic_attach_location.png"


#define TG_ICON_FLOATING_PENCIL       FM_ICON_PATH"floating_pencil.png"
#define TG_ICON_FLOATING_BG       FM_ICON_PATH"floating_pressed.png"
#define TG_SEARCH_ICON       FM_ICON_PATH"ic_ab_search.png"

#define TG_MENU_GROUP       FM_ICON_PATH"menu_newgroup.png"
#define TG_MENU_INVITE       FM_ICON_PATH"menu_invite.png"
#define TG_MENU_CONTACTS       FM_ICON_PATH"menu_contacts.png"
#define TG_MENU_SECRET       FM_ICON_PATH"menu_secret.png"
#define TG_MENU_SETTINGS       FM_ICON_PATH"menu_settings.png"

#define TG_CHAT_DEFAULT_BG       FM_ICON_PATH"background_hd.jpg"


#define INIT_SCREEN_1       FM_ICON_PATH"screenshot_1.png"
#define INIT_SCREEN_2       FM_ICON_PATH"screenshot_2.png"
#define INIT_SCREEN_3       FM_ICON_PATH"screenshot_3.png"
#define INIT_SCREEN_4       FM_ICON_PATH"screenshot_4.png"
#define INIT_SCREEN_5       FM_ICON_PATH"screenshot_5.png"
#define INIT_SCREEN_6       FM_ICON_PATH"screenshot_6.png"
#define INIT_SCREEN_7       FM_ICON_PATH"screenshot_7.png"
#define TG_NO_CHAT_LIST       FM_ICON_PATH"no_chat.png"

#define POPUP_TEXT_TAKE_PHOTO "Take photo"
#define POPUP_TEXT_TAKE_GALLERY "Gallery"
#define POPUP_TEXT_TAKE_VIDEO "Video"
#define POPUP_TEXT_TAKE_FILE "File"
#define POPUP_TEXT_TAKE_LOCATION "Location"


#define LIST_CONTACT_ROUND_MASK_ICON FM_ICON_PATH"/info_page_pic_mask.png"


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

#define SIZE_CODE 10
static char *phone_codes[SIZE_CODE][2] = { {"Argentina (+54)", "+54"},
										{"Brazil (+55)", "+55"},
										{"China (+86)", "+86"},
										{"France (+33)", "+33"},
										{"India (+91)", "+91"},
										{"Malaysia (+60)", "+60"},
										{"Russia (+7)", "+7"},
										{"Singapore (+65)", "+65"},
										{"South Korea (+82)", "+82"},
										{"United States (+1)" , "+1"}
									     };



#define NUMBER_OF_MENU_ITEMS 5

#define MENU_NEW_GROUP "New Group"
#define MENU_SECRET_CHAT "New secret Chat"
#define MENU_CONTACTS "Contacts"
#define MENU_INVITE_FRIENDS "Invite Friends"
#define MENU_SETTINGS "settings"

static char* main_view_menu_items[NUMBER_OF_MENU_ITEMS][2] = { {MENU_NEW_GROUP, TG_MENU_GROUP},
										{MENU_SECRET_CHAT, TG_MENU_SECRET},
										{MENU_CONTACTS, TG_MENU_CONTACTS},
										{MENU_INVITE_FRIENDS, TG_MENU_INVITE},
										{MENU_SETTINGS, TG_MENU_SETTINGS}
									     };


typedef enum {
	CHAT_MESSAGE_BUBBLE_NONE = 0,
	CHAT_MESSAGE_BUBBLE_SENT,
	CHAT_MESSAGE_BUBBLE_RECEIVE,
	CHAT_MESSAGE_BUBBLE_LAST
} Chat_message_Bubble_Style;

#define CHAT_BUBBLE_SUB_TEXT_STYLE "<font_size=20 font_weight=Bold color=#000000>%s</font_size>"



static Elm_Entry_Filter_Limit_Size limit_filter_data;
static Elm_Entry_Filter_Accept_Set accept_set = {
       .accepted = "0123456789",
       .rejected = NULL
 };

#define MAX_NUM_LENGTH 10
#define MAX_CODE_LENGTH 5

typedef struct {
	int type;
	int id;
} tgl_peer_id_t;


typedef enum {
	TELEGRAM_APP_FILE_TYPE_NONE = 0,
	TELEGRAM_APP_FILE_TYPE_IMAGE,	   /**< Image category */
	TELEGRAM_APP_FILE_TYPE_VIDEO,	   /**< Video category */
	TELEGRAM_APP_FILE_TYPE_MUSIC,	   /**< Music category */
	TELEGRAM_APP_FILE_TYPE_STICKER,	/** Sticker / Anicon category */
	TELEGRAM_APP_FILE_TYPE_PDF,		   /**< Pdf category */
	TELEGRAM_APP_FILE_TYPE_DOC,		   /**< Word category */
	TELEGRAM_APP_FILE_TYPE_PPT,		   /**< Powerpoint category */
	TELEGRAM_APP_FILE_TYPE_EXCEL,	   /**< Excel category */
	TELEGRAM_APP_FILE_TYPE_VOICE,	   /**< Voice category */
	TELEGRAM_APP_FILE_TYPE_HTML,		   /**< Html category */
	TELEGRAM_APP_FILE_TYPE_FLASH,	   /**< Flash category */
	TELEGRAM_APP_FILE_TYPE_TXT,		   /**< Txt category */
	TELEGRAM_APP_FILE_TYPE_VCONTACT,	   /**< Vcontact category */
	TELEGRAM_APP_FILE_TYPE_VCALENDAR,	   /**< Vcalendar category */
	TELEGRAM_APP_FILE_TYPE_VNOTE,	   /**< Vnote category */
	TELEGRAM_APP_FILE_TYPE_VBOOKMARK,	   /**< Vbookmark category */
	TELEGRAM_APP_FILE_TYPE_SNB,		   /**< Snotes category */
	TELEGRAM_APP_FILE_TYPE_SVG,		   /**< Svg category */
	TELEGRAM_APP_FILE_TYPE_RSS,		   /**< Rss reader file, *.opml */
	TELEGRAM_APP_FILE_TYPE_JAVA,		   /**< java file, *.jad, *.jar */
	TELEGRAM_APP_FILE_TYPE_WGT,		   /**< wrt , *.wgt, *.wgt */
	TELEGRAM_APP_FILE_TYPE_TPK,			/**< *.tpk */
	TELEGRAM_APP_FILE_TYPE_HWP,			/**< *.hwp */
	TELEGRAM_APP_FILE_TYPE_EMAIL,		/**< *.eml */
	TELEGRAM_APP_FILE_TYPE_DRM,			/**< drm file , *.dcf */
	TELEGRAM_APP_FILE_TYPE_ZIP,			/**< zip compressed file , *.zip */
	TELEGRAM_APP_FILE_TYPE_ETC,		   /**< Other files category */
	TELEGRAM_APP_FILE_TYPE_MAX
} TELEGRAM_APP_FILE_TYPE_E;


typedef enum state_of_app {
	TG_SPLASH_SCREEN_STATE,
	TG_INIT_SCREEN_STATE,
	TG_REGISTRATION_STATE,
	TG_PROFILE_REGISTRATION_STATE,
	TG_LOGIN_STATE,
	TG_BUDDY_LIST_STATE,
	TG_BUDDY_LIST_SELECTION_STATE,
	TG_GROUP_CHAT_NAME_ENTRY_STATE,
	TG_BUDDY_CHAT_STATE,
	TG_BUDDY_CHAT_CONV_STATE,
	TG_USER_MAIN_VIEW_STATE,
	TG_START_MESSAGING_VIEW_STATE,
	TG_CHAT_MESSAGING_VIEW_STATE
} state_of_app_s;

enum tgl_typing_status {
	tgl_typing_none = 10001,
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

typedef enum MESSAGE_STATE {
	TG_MESSAGE_STATE_SENDING = 1,
	TG_MESSAGE_STATE_SENT,
	TG_MESSAGE_STATE_DELIVERED,
	TG_MESSAGE_STATE_FAILED,
	TG_MESSAGE_STATE_RECEIVED,
	TG_MESSAGE_STATE_READ,
	TG_MESSAGE_STATE_UNKNOWN
} TG_MESSAGE_STATE;


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
	Evas_Object *name_object;
	Evas_Object *msg_object;
	char *last_message;
	Eina_Bool is_out_message;
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
	int msg_state;
	int message_len;
	int media_type;
	char* media_id;
	int unique_id;
} tg_message_s;

typedef struct tg_main_list_item {
	char* peer_print_name;
	int peer_id;
	int peer_type;
	char* last_message;
	int last_msg_id;
	int last_msg_status;
	int last_msg_type;
	int last_msg_service;
	int number_of_unread_msgs;
	int last_seen_time;
	Eina_Bool is_out_msg;
	char* profile_pic_path;
	Evas_Object* profile_pic;
	Evas_Object* user_name_lbl;
	Evas_Object* status_lbl;
	Evas_Object* date_lbl;
	Evas_Object* msg_status_lbl;
} tg_main_list_item_s;

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

	Eina_List* main_list;


	int curtimezoneoffset;
	int curtimeformat;
	tgl_peer_id_t user_id;
	state_of_app_s current_app_state;
	user_data_s current_user_data;
	peer_with_pic_s* peer_in_cahtting_data;
	user_data_with_pic_s* buddy_in_cahtting_data;
	Eina_Bool is_network_connected;
	service_client* service_client;
	Eina_Bool is_first_time_registration;
	Eina_List* loaded_msg_list;
	int timer_value;
	Eina_Bool is_last_msg_changed;
} appdata_s;

extern void show_toast(appdata_s* ad, char* value);
extern void layout_back_cb(void *data, Evas_Object *obj, void *event_info);
extern void tg_login_nf_back_cb(void *data, Evas_Object *obj, void *event_info);
extern void detail_list_nf_back_cb(void *data, Evas_Object *obj, void *event_info);
extern void create_buddy_msg_table(const char* table_name);
extern void load_buddy_list_data(appdata_s *ad);
extern void load_group_chat_data(appdata_s *ad);
extern void load_peer_data(appdata_s *ad);
extern void load_main_list_data(appdata_s *ad);

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

static inline char* trim(const char * s)
{
	if (!s) {
		return NULL;
	}

	int l = strlen(s);

	while (isspace(s[l - 1])) {
		--l;
	}

	while (*s && isspace(*s)) {
		++s, --l;
	}

	return strndup(s, l);
}

extern Evas_Object* create_circle_button(Evas_Object *parent, char* text, char* filepath);
extern Evas_Object* create_button(Evas_Object *parent, char *style, char *text);
extern int numbers_only(const char *s);

static inline void telegram_image_mask_delete_cb(Evas_Object *obj)
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
extern char* get_table_name_from_number(const int id);
extern Eina_Bool compare_date_with_current_date(int rtime);

static inline void buddy_icon_del_cb(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	user_data_with_pic_s *item  = data;
	item->contact_icon = NULL;
}

static inline  const char *ui_utils_get_resource(const char *res_name)
{
	static char res_path[PATH_MAX] = {'\0'};

	char *res_path_buff = app_get_resource_path();
	if (!res_path_buff) {
		return NULL;
	}
	snprintf(res_path, sizeof(res_path) - 1, "%s%s", res_path_buff, res_name);
	free(res_path_buff);

	return res_path;
}

static inline char *get_current_time()
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

static inline char *replace(const char *s, char ch, const char *repl)
{
	int count = 0;
	const char *t;

	for(t = s; *t; t++) {
		count += (*t == ch);
	}

	size_t rlen = strlen(repl);
	char *res = malloc(strlen(s) + (rlen - 1) * count + 1);
	char *ptr = res;

	for(t = s; *t; t++) {
		if(*t == ch) {
			memcpy(ptr, repl, rlen);
			ptr += rlen;
		} else {
			*ptr++ = *t;
		}
	}

	*ptr = 0;
	return res;
}

static inline Evas_Object * create_scroller(Evas_Object *parent)
{
	Evas_Object *scroller = elm_scroller_add(parent);
	if (!scroller) {
		/**
		 * @todo
		 * Handling this exceptional cases.
		 */
		return NULL;
	}
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_FALSE);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
	evas_object_show(scroller);
	return scroller;
}

static inline int telegram_is_drm_file(const char *file_path)
{
	return 0;
}

static inline TELEGRAM_APP_FILE_TYPE_E __telegram_common_get_file_type_by_file_ext(const char *file_ext, const char *fullpath)
{
	const char *ptr;

	if (file_ext == NULL) {
		LOGI("file_ext is NULL");
		return TELEGRAM_APP_FILE_TYPE_ETC;
	}

	ptr = file_ext + 1;
	switch (*file_ext) {
	case 'a':
	case 'A':
		if (strcasecmp("SF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		if (strcasecmp("MR", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VOICE;
		}
		if (strcasecmp("WB", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VOICE;
		}
		if (strcasecmp("AC", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("VI", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		break;

	case 'b':
	case 'B':
		if (strcasecmp("MP", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_IMAGE;
		}
		break;

	case 'd':
	case 'D':
		if (strcasecmp("OC", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_DOC;
		}
		if (strcasecmp("OCX", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_DOC;
		}
		if (strcasecmp("IVX", ptr) == 0) {
			if (telegram_is_drm_file(fullpath) == 0) {
				return TELEGRAM_APP_FILE_TYPE_DRM;
			} else {
				return TELEGRAM_APP_FILE_TYPE_VIDEO;
			}
		}
		if (strcasecmp("CF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_DRM;
		}
		if (strcasecmp("M", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_DRM;
		}
		break;

	case 'g':
	case 'G':
		if (strcasecmp("IF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_IMAGE;
		}
		if (strcasecmp("72", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		break;

	case 'h':
	case 'H':
		if (strcasecmp("TML", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_HTML;
		}
		if (strcasecmp("TM", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_HTML;
		}
		break;

	case 'i':
	case 'I':
		if (strcasecmp("MY", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("CS", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VCALENDAR;
		}
		break;

	case 'j':
	case 'J':
		if (strcasecmp("PG", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_IMAGE;
		}
		if (strcasecmp("PEG", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_IMAGE;
		}
		if (strcasecmp("PE", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_IMAGE;
		}
		break;

	case 'm':
	case 'M':
		if (strcasecmp("MF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("P3", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("ID", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("IDI", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("P4", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		if (strcasecmp("PG", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		if (strcasecmp("PEG", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		if (strcasecmp("4A", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("3G", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_FLASH;
		}
		if (strcasecmp("XMF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("KV", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		break;

	case 'o':
	case 'O':
		if (strcasecmp("pml", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_RSS;
		}
		if (strcasecmp("DF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_DRM;
		}
		if (strcasecmp("RO", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_DRM;
		}
		break;

	case 'p':
	case 'P':
		if (strcasecmp("NG", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_IMAGE;
		}
		if (strcasecmp("JPEG", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_IMAGE;
		}
		if (strcasecmp("DF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_PDF;
		}
		if (strcasecmp("PT", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_PPT;
		}
		if (strcasecmp("PTX", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_PPT;
		}
		break;

	case 'r':
	case 'R':
		if (strcasecmp("O", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_DRM;
		}
		break;

	case 's':
	case 'S':
		if (strcasecmp("DP", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		if (strcasecmp("PM", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("MP", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("PF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("WF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_FLASH;
		}
		if (strcasecmp("VG", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_SVG;
		}
		if (strcasecmp("VGZ", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_SVG;
		}
		break;

	case 't':
	case 'T':
		if (strcasecmp("XT", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_TXT;
		}
		if (strcasecmp("PK", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_TPK;
		}
		break;

	case 'v':
	case 'V':
		if (strcasecmp("CF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VCONTACT;
		}
		if (strcasecmp("TS", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VCALENDAR;
		}
		if (strcasecmp("CS", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VCALENDAR;
		}
		break;

	case 'w':
	case 'W':
		if (strcasecmp("AV", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("BMP", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_IMAGE;
		}
		if (strcasecmp("GT", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_WGT;
		}
		if (strcasecmp("MA", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("MV", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		break;

	case 'x':
	case 'X':
		if (strcasecmp("LS", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_EXCEL;
		}
		if (strcasecmp("LSX", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_EXCEL;
		}
		if (strcasecmp("MF", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_MUSIC;
		}
		if (strcasecmp("HTML", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_HTML;
		}
		break;

	case '3':
		if (strcasecmp("GP", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		if (strcasecmp("GPP", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		if (strcasecmp("G2", ptr) == 0) {
			return TELEGRAM_APP_FILE_TYPE_VIDEO;
		}
		break;
	}
	return TELEGRAM_APP_FILE_TYPE_ETC;
}

static inline char* telegram_common_get_file_ext(const char *a_pszfile_name)
{
	if (a_pszfile_name != NULL) {
		int nlen = strlen(a_pszfile_name);
		char *psztemp = (char *)a_pszfile_name + nlen;

		while (nlen--) {
			psztemp--;
			if (*psztemp == '.') {
				psztemp++;
				break;
			}
		}
		return psztemp;
	}

	return NULL;
}


static inline TELEGRAM_APP_FILE_TYPE_E telegram_common_get_file_type(const char *filepath)
{
	TELEGRAM_APP_FILE_TYPE_E file_type = TELEGRAM_APP_FILE_TYPE_NONE;
	if(filepath == NULL)
	{
		return TELEGRAM_APP_FILE_TYPE_NONE;
	}
	char *file_ext = telegram_common_get_file_ext(filepath);

	if (file_ext) {
		file_type = __telegram_common_get_file_type_by_file_ext(file_ext, filepath);
	} else {
		LOGI("file_ext is NULL");
	}

	return file_type;
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

extern void app_get_resource(const char *edj_file_in, char *edj_path_out, int edj_path_max);

#endif /* TG_COMMON_H_ */
