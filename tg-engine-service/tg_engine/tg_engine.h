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

extern char *tgl_engine_get_auth_key_filename(void);
extern char *tgl_engine_get_state_filename(void);
extern char *tgl_engine_get_secret_chat_filename(void);
extern char *tgl_engine_get_downloads_directory (void);
extern struct tgl_state *tgl_engine_get_TLS(void);
extern void tgl_engine_destroy_TLS(void);

extern void on_user_info_loaded(struct tgl_state *TLSR, void *extra, int success, struct tgl_user *U);

typedef enum TG_ENGINE_STATE {
	TG_ENGINE_STATE_INITIALIZING,
	TG_ENGINE_STATE_REGISTRATION,
	TG_ENGINE_STATE_PROFILE_REGISTRATION,
	TG_ENGINE_STATE_PROFILE_FIRST_NAME_REGISTRATION,
	TG_ENGINE_STATE_PROFILE_LAST_NAME_REGISTRATION,
	TG_ENGINE_STATE_CODE_REQUEST
} tg_engine_state;

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

extern void media_download_request(tg_engine_data_s *tg_data, int buddy_id, long long media_id);
extern void add_contacts_to_user(tg_engine_data_s *tg_data, int size, Eina_List* contact_list);
extern void create_new_group(tg_engine_data_s *tg_data, Eina_List* buddy_ids, const char* group_name, const char* group_icon);

#endif /* TG_ENGINE_H_ */
