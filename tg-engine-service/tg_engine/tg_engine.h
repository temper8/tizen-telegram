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
#include "server_response.h"
#include <net_connection.h>

#define PROGNAME "telegram-tizen"
#define VERSION "0.01"
#define CONFIG_DIRECTORY ".telegram-tizen"
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

int verbosity;
int msg_num_mode;
char *default_username;
char *config_filename;
char *prefix;
char *auth_file_name;
char *state_file_name;
char *secret_chat_file_name;
char *downloads_directory;
char *config_directory;
char *binlog_file_name;
char *lua_file;
int binlog_enabled;
extern int log_level;
int sync_from_start;
int allow_weak_random;
int disable_colors;
int readline_disabled;
int disable_output;
int reset_authorization;
int port;
int use_ids;
int ipv6_enabled;
char *start_command;
char *rsa_file_name;
char *config_full_path;
int need_dc_list_update;
struct tgl_state *TLS;

extern void logprintf (const char *format, ...) __attribute__ ((format (printf, 1, 2)));
extern void check_type_sizes(void);
extern int str_empty(char *str);
extern void parse_config(void);
extern void running_for_first_time(void);
extern void init_tl_engine();
extern void write_auth_file(void);

static char* get_config_filename(void)
{
  return config_filename;
}

static char* get_auth_key_filename(void)
{
  return auth_file_name;
}

static char* get_state_filename(void)
{
  return state_file_name;
}

static char* get_secret_chat_filename (void) {
  return secret_chat_file_name;
}

static char* get_downloads_directory (void) {
  return downloads_directory;
}

static char* get_binlog_file_name(void)
{
  return binlog_file_name;
}

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
	char* phone_number;
	char* sms_code;
	char* first_name;
	char* last_name;
	tg_server* tg_server;
	tg_engine_state tg_state;
	void(*get_string)(struct tgl_state *TLS, char *string, void *arg);
	void* callback_arg;
	Eina_Bool is_first_time_registration;
	Eina_List* contact_list_to_add;
	int current_index;
	Eina_Bool is_network_connected;
	Eina_Bool is_login_activated;
	connection_h connection;
	Eina_Bool is_group_creation_requested;
	char* new_group_icon;
} tg_engine_data_s;

tg_engine_data_s* tg_data;


typedef struct contact_data {
	int contact_id;
	char* display_name;
	char* first_name;
	char* last_name;
	char* phone_number;
} contact_data_s;


void send_message_to_buddy(int buddy_id, int msg_type, char* msg_data, int type_of_chat);
void send_media_to_buddy(int buddy_id, int msg_type, char* file_path);

void media_download_request(int buddy_id, long long media_id);
void add_contacts_to_user(int size, Eina_List* contact_list);
void create_new_group(Eina_List* buddy_ids, const char* group_name, const char* group_icon);

#endif /* TG_ENGINE_H_ */
