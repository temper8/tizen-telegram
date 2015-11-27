/*
 * tg_engine.h
 *
 *  Created on: Jun 24, 2015
 *      Author: sandeep
 */

#ifndef TG_ENGINE_H_
#define TG_ENGINE_H_
#include <app.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <fcntl.h>
#include <grp.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <tools.h>
#ifdef USE_LUA
#include "lua-tg.h"
#endif
#include "tgl.h"
#include "tgl-net.h"
#include "tgl-timers.h"
#include "tgl-binlog.h"
#include <openssl/sha.h>
#include "tg_server.h"

#include <Elementary.h>
#include <efl_extension.h>
#include <net_connection.h>
#include <notification.h>

#define PROGNAME "telegram-tizen"
#define VERSION "0.01"
//#define CONFIG_DIRECTORY ".telegram-tizen"
#define CONFIG_DIRECTORY "telegram_tizen"
#define CONFIG_FILE "config"
#define AUTH_KEY_FILE "auth"
#define STATE_FILE "state"
#define SECRET_CHAT_FILE "secret"
#define DOWNLOADS_DIRECTORY "downloads"
#define BINLOG_FILE "binlog"
#define RSA_KEY_FILE "tg-server.pub"
#define DEFAULT_TELEGRAM_PATH "/opt/usr/media/telegram/"
//#define DEFAULT_TELEGRAM_PATH "/opt/usr/apps/"PACKAGE"/"          /*app_get_data_path()*/
//#define DEFAULT_TELEGRAM_PATH app_get_external_data_path()
//#define DEFAULT_TG_DATABASE_PATH DEFAULT_TELEGRAM_PATH"tg_data_base.db"
#define DEFAULT_TG_DATABASE_PATH "/opt/usr/media/telegram/tg_data_base.db"
#define TELEGRAM_CLI_VERSION "1.0.0"
#define CONFIG_DIRECTORY_MODE 0700
#define DEFAULT_RSA_FILE_NAME "server.pub"
#define DEFAULT_TELEGRAM_ICON "tg_icon.png"
#define TELEGRAM_CLI_APP_HASH "8b5082937b2eb8814559291b93caa8a5"
#define TELEGRAM_CLI_APP_ID 26793

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define DEFAULT_CONFIG_CONTENTS     \
  "# This is an empty config file\n" \
  "# Feel free to put something here\n"

extern void logprintf (const char *format, ...) __attribute__ ((format (printf, 1, 2)));
extern void check_type_sizes(void);
extern int str_empty(char *str);
extern void parse_config(void);
extern void running_for_first_time(void);
extern void init_tl_engine();
extern void write_auth_file(void);

extern void tgl_engine_var_init(void);
extern void tgl_engine_var_free(void);
extern char *tgl_engine_get_auth_key_filename(void);
extern char *tgl_engine_get_state_filename(void);
extern char *tgl_engine_get_secret_chat_filename(void);
extern char *tgl_engine_get_downloads_directory (void);
extern struct tgl_state *tgl_engine_get_TLS(void);
extern void tgl_engine_destroy_TLS(void);

extern void on_user_info_loaded(struct tgl_state *TLSR, void *extra, int success, struct tgl_user *U);

typedef enum TG_ENGINE_STATE {
	TG_ENGINE_STATE_NONE,
	TG_ENGINE_STATE_INITIALIZING,
	TG_ENGINE_STATE_REGISTRATION,
	TG_ENGINE_STATE_PROFILE_REGISTRATION,
	TG_ENGINE_STATE_PROFILE_FIRST_NAME_REGISTRATION,
	TG_ENGINE_STATE_PROFILE_LAST_NAME_REGISTRATION,
	TG_ENGINE_STATE_CODE_REQUEST
} tg_engine_state;

typedef struct sent_message_data {
	char *app_name;
	char *command;
	char *buddy_id;
	char *message_id;
	char *message_type;
	char *message_data;
	char *type_of_chat;
} sent_message_data_s;

typedef struct sent_media_data {
	char *app_name;
	char *command;
	char *buddy_id;
	char *message_id;
	char *media_id;
	char *message_type;
	char *file_path;
	char *type_of_chat;
} sent_media_data_s;

typedef struct tg_engine_data {
	tgl_peer_id_t id;
	char *phone_number;
	char *sms_code;
	char *first_name;
	char *last_name;
	tg_server *tg_server;
	tg_engine_state tg_state;
	void (*get_string)(struct tgl_state *TLS, char *string, void *arg);
	void *callback_arg;
	Eina_Bool is_first_time_registration;
	Eina_List *contact_list_to_add;
	int current_index;
	Eina_Bool is_network_connected;
	Eina_Bool is_login_activated;
	connection_h connection;
	Eina_Bool is_group_creation_requested;
	char *new_group_icon;
	Ecore_Idler *lazy_init_idler;
	char* mhash;
	//Eina_Bool is_loading_completed;
	notification_h s_notififcation;
	Eina_List *chat_list;
	int current_chat_index;

	Eina_List *buddy_list;
	int current_buddy_index;
	int current_group_chat_index;
	Ecore_Timer *code_response_timer;
} tg_engine_data_s;

typedef struct contact_data {
	int contact_id;
	char *display_name;
	char *first_name;
	char *last_name;
	char *phone_number;
} contact_data_s;


extern void send_do_mark_read_messages(int buddy_id, int type_of_chat);
extern void send_message_to_buddy(int buddy_id, int message_id, int msg_type, char* msg_data, int type_of_chat);
extern void send_media_to_buddy(int buddy_id, int message_id, int media_id, int msg_type, char* file_path, int type_of_chat);
extern void logout_telegram(tg_engine_data_s *tg_data);
extern void media_download_request(tg_engine_data_s *tg_data, int buddy_id, long long media_id);
extern void add_contacts_to_user(tg_engine_data_s *tg_data, int size, Eina_List* contact_list);
extern void create_new_group(tg_engine_data_s *tg_data, Eina_List* buddy_ids, const char* group_name, const char* group_icon);
extern void set_profile_picture(tg_engine_data_s *tg_data, int buddy_id, const char *file_path);
extern void set_user_name(tg_engine_data_s *tg_data, int buddy_id, const char *username);
extern void update_user_display_name(tg_engine_data_s *tg_data, int buddy_id, const char *first_name, const char *last_name);
extern void request_for_code_via_call(struct tgl_state *TLS, char* phone_no, Eina_Bool trough_sms);
extern void free_contact_data(Eina_List *contact_data);
extern void leave_group_chat(tg_engine_data_s *tg_data, int group_chat_id);
extern void delete_selected_group_chat(tg_engine_data_s *tg_data, Eina_List *sel_grp_chats);
extern void do_delete_buddy(int buddy_id);
extern void do_delete_message(int buddy_id, int message_id);
extern void request_for_secret_chat(int buddy_id);
extern void do_add_buddy(int buddy_id, char *first_name, char *last_name, char *phone_num);
extern void do_update_chat_info(int chat_id);
extern void do_unblock_buddy(int buddy_id);
extern void do_block_buddy(int buddy_id);
extern void set_group_chat_profile_picture(tg_engine_data_s *tg_data, int buddy_id, const char *file_path);
extern void set_group_chat_new_title(tg_engine_data_s *tg_data, int buddy_id, const char *new_title);
extern void set_group_chat_add_new_buddy(tg_engine_data_s *tg_data, int s_buddy_id, int s_chat_id);
extern void set_group_chat_remove_buddy(tg_engine_data_s *tg_data, int s_buddy_id, int s_chat_id);

#endif /* TG_ENGINE_H_ */
