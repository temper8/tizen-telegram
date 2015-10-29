/**
 * @file tg_engine.c
 * @author sandeep
 * @date Jun 24, 2015
 */

#include "tg_engine.h"
#include "server_response.h"
#include <pthread.h>
#include <Ecore.h>
#include "tg_db_wrapper.h"
#include "tgl-fetch.h"
#include <mime_type.h>
#include "device_contacts_manager.h"
#include "tg-engine-service.h"

#define DC_SERIALIZED_MAGIC 0x868aa81d
#define STATE_FILE_MAGIC 0x28949a93
#define SECRET_CHAT_FILE_MAGIC 0x37a1988a

static struct _tg_engine {
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
	int log_level;
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
} s_info;

static void on_chat_info_received(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_chat *chat_info);
static void on_buddy_info_loaded(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_user *U);
static void on_chat_pic_loaded(struct tgl_state *TLS, void *callback_extra, int success, char *filename);
static void on_document_download_completed(struct tgl_state *TLS, void *callback_extra, int success, char *filename);
static void on_buddy_pic_loaded(struct tgl_state *TLS, void *callback_extra, int success, char *filename);
static void on_new_buddy_info_loaded(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_user *U);
void tgl_engine_var_init(void)
{
	s_info.default_username = NULL;
	s_info.config_filename = NULL;
	s_info.auth_file_name = NULL;
	s_info.state_file_name = NULL;
	s_info.secret_chat_file_name = NULL;
	s_info.downloads_directory = NULL;
	s_info.config_directory = NULL;
	s_info.binlog_file_name = NULL;
	s_info.lua_file = NULL;
}

void tgl_engine_var_free(void)
{
	if (s_info.default_username) {
		free(s_info.default_username);
		s_info.default_username = NULL;
	}
	if (s_info.config_filename) {
		free(s_info.config_filename);
		s_info.config_filename = NULL;
	}
	if (s_info.auth_file_name) {
		free(s_info.auth_file_name);
		s_info.auth_file_name = NULL;
	}
	if (s_info.state_file_name) {
		free(s_info.state_file_name);
		s_info.state_file_name = NULL;
	}
	if (s_info.secret_chat_file_name) {
		free(s_info.secret_chat_file_name);
		s_info.secret_chat_file_name = NULL;
	}
	if (s_info.downloads_directory) {
		free(s_info.downloads_directory);
		s_info.downloads_directory = NULL;
	}
	if (s_info.config_directory) {
		free(s_info.config_directory);
		s_info.config_directory = NULL;
	}
	if (s_info.binlog_file_name) {
		free(s_info.binlog_file_name);
		s_info.binlog_file_name = NULL;
	}
	if (s_info.lua_file) {
		free(s_info.lua_file);
		s_info.lua_file = NULL;
	}
	if (s_info.TLS) {
		tgl_state_free(s_info.TLS);
		tgl_free_all(s_info.TLS);
		s_info.TLS = NULL;
	}
}

char *tgl_engine_get_auth_key_filename(void)
{
  return s_info.auth_file_name;
}

char *tgl_engine_get_state_filename(void)
{
  return s_info.state_file_name;
}

char *tgl_engine_get_secret_chat_filename (void)
{
  return s_info.secret_chat_file_name;
}

char *tgl_engine_get_downloads_directory (void)
{
  return s_info.downloads_directory;
}

void write_dc(struct tgl_dc *DC, void *extra)
{
	int auth_file_fd = *(int *)extra;
	int x;

	x = !!DC;

	if (!x) {
		assert(write(auth_file_fd, &x, 4) == 4);
		return;
	}

	assert(write(auth_file_fd, &x, 4) == 4);
	assert(DC->has_auth);
	assert(write(auth_file_fd, &DC->port, 4) == 4);
	int l = strlen(DC->ip);
	assert(write(auth_file_fd, &l, 4) == 4);
	assert(write(auth_file_fd, DC->ip, l) == l);
	assert(write(auth_file_fd, &DC->auth_key_id, 8) == 8);
	assert(write(auth_file_fd, DC->auth_key, 256) == 256);
}

void write_secret_chat(tgl_peer_t *_P, void *extra)
{
	struct tgl_secret_chat *P = (void *)_P;

	if (tgl_get_peer_type (P->id) != TGL_PEER_ENCR_CHAT) {
		return;
	}

	if (P->state != sc_ok) {
		return;
	}

	int *a = extra;
	int fd = a[0];
	a[1] ++;

	int id = tgl_get_peer_id (P->id);
	assert (write (fd, &id, 4) == 4);
	//assert (write (fd, &P->flags, 4) == 4);
	int l = strlen(P->print_name);
	assert(write (fd, &l, 4) == 4);
	assert(write (fd, P->print_name, l) == l);
	assert(write (fd, &P->user_id, 4) == 4);
	assert(write (fd, &P->admin_id, 4) == 4);
	assert(write (fd, &P->date, 4) == 4);
	assert(write (fd, &P->ttl, 4) == 4);
	assert(write (fd, &P->layer, 4) == 4);
	assert(write (fd, &P->access_hash, 8) == 8);
	assert(write (fd, &P->state, 4) == 4);
	assert(write (fd, &P->key_fingerprint, 8) == 8);
	assert(write (fd, &P->key, 256) == 256);
	assert(write (fd, &P->first_key_sha, 20) == 20);
	assert(write (fd, &P->in_seq_no, 4) == 4);
	assert(write (fd, &P->last_in_seq_no, 4) == 4);
	assert(write (fd, &P->out_seq_no, 4) == 4);
}

void write_secret_chat_file(void)
{
	if (s_info.binlog_enabled) {
		return;
	}
	int secret_chat_fd = open (tgl_engine_get_secret_chat_filename(), O_CREAT | O_RDWR, 0600);
	assert (secret_chat_fd >= 0);
	int x = SECRET_CHAT_FILE_MAGIC;
	assert (write (secret_chat_fd, &x, 4) == 4);
	x = 2;
	assert (write (secret_chat_fd, &x, 4) == 4); // version
	assert (write (secret_chat_fd, &x, 4) == 4); // num

	int y[2];
	y[0] = secret_chat_fd;
	y[1] = 0;

	tgl_peer_iterator_ex(s_info.TLS, write_secret_chat, y);

	lseek(secret_chat_fd, 8, SEEK_SET);
	assert(write (secret_chat_fd, &y[1], 4) == 4);
	close(secret_chat_fd);
}

void write_auth_file(void)
{
	if (s_info.binlog_enabled) {
		return;
	}

	int auth_file_fd = open(tgl_engine_get_auth_key_filename(), O_CREAT | O_RDWR, 0600);

	assert(auth_file_fd >= 0);
	int x = DC_SERIALIZED_MAGIC;
	assert(write(auth_file_fd, &x, 4) == 4);
	assert(write(auth_file_fd, &s_info.TLS->max_dc_num, 4) == 4);
	assert(write(auth_file_fd, &s_info.TLS->dc_working_num, 4) == 4);
	tgl_dc_iterator_ex(s_info.TLS, write_dc, &auth_file_fd);
	assert(write(auth_file_fd, &s_info.TLS->our_id, 4) == 4);
	close(auth_file_fd);
}

void read_dc(int auth_file_fd, int id, unsigned ver)
{
	int port = 0;
	assert(read(auth_file_fd, &port, 4) == 4);
	int l = 0;
	assert(read(auth_file_fd, &l, 4) == 4);
	assert(l >= 0 && l < 100);
	char ip[100];
	assert(read(auth_file_fd, ip, l) == l);
	ip[l] = 0;

	long long auth_key_id;
	static unsigned char auth_key[256];
	assert(read(auth_file_fd, &auth_key_id, 8) == 8);
	assert(read(auth_file_fd, auth_key, 256) == 256);

	//bl_do_add_dc(id, ip, l, port, auth_key_id, auth_key);
	bl_do_dc_option(s_info.TLS, id, 2, "DC", l, ip, port);
	bl_do_set_auth_key_id(s_info.TLS, id, auth_key);
	bl_do_dc_signed(s_info.TLS, id);
}

void empty_auth_file(void)
{
	if (s_info.TLS->test_mode) {
		bl_do_dc_option(s_info.TLS, 1, 0, "", strlen(TG_SERVER_TEST_1), TG_SERVER_TEST_1, 443);
		bl_do_dc_option(s_info.TLS, 2, 0, "", strlen(TG_SERVER_TEST_2), TG_SERVER_TEST_2, 443);
		bl_do_dc_option(s_info.TLS, 3, 0, "", strlen(TG_SERVER_TEST_3), TG_SERVER_TEST_3, 443);
		bl_do_set_working_dc(s_info.TLS, 2);
	} else {
		bl_do_dc_option(s_info.TLS, 1, 0, "", strlen(TG_SERVER_1), TG_SERVER_1, 443);
		bl_do_dc_option(s_info.TLS, 2, 0, "", strlen(TG_SERVER_2), TG_SERVER_2, 443);
		bl_do_dc_option(s_info.TLS, 3, 0, "", strlen(TG_SERVER_3), TG_SERVER_3, 443);
		bl_do_dc_option(s_info.TLS, 4, 0, "", strlen(TG_SERVER_4), TG_SERVER_4, 443);
		bl_do_dc_option(s_info.TLS, 5, 0, "", strlen(TG_SERVER_5), TG_SERVER_5, 443);
		bl_do_set_working_dc(s_info.TLS, 4);
	}
}

void read_secret_chat(int fd, int v)
{
	int id, l, user_id, admin_id, date, ttl, layer, state;
	long long access_hash, key_fingerprint;
	static char s[1000];
	static unsigned char key[256];
	static unsigned char sha[20];
	assert(read(fd, &id, 4) == 4);
	//assert(read(fd, &flags, 4) == 4);
	assert(read(fd, &l, 4) == 4);
	assert(l > 0 && l < 1000);
	assert(read(fd, s, l) == l);
	assert(read(fd, &user_id, 4) == 4);
	assert(read(fd, &admin_id, 4) == 4);
	assert(read(fd, &date, 4) == 4);
	assert(read(fd, &ttl, 4) == 4);
	assert(read(fd, &layer, 4) == 4);
	assert(read(fd, &access_hash, 8) == 8);
	assert(read(fd, &state, 4) == 4);
	assert(read(fd, &key_fingerprint, 8) == 8);
	assert(read(fd, &key, 256) == 256);
	if (v >= 2) {
		assert(read(fd, sha, 20) == 20);
	}
	int in_seq_no = 0, out_seq_no = 0, last_in_seq_no = 0;
	if (v >= 1) {
		assert(read(fd, &in_seq_no, 4) == 4);
		assert(read(fd, &last_in_seq_no, 4) == 4);
		assert(read(fd, &out_seq_no, 4) == 4);
	}

	bl_do_encr_chat_create(s_info.TLS, id, user_id, admin_id, s, l);
	struct tgl_secret_chat  *P =(void *)tgl_peer_get(s_info.TLS, TGL_MK_ENCR_CHAT(id));
	assert(P &&(P->flags & FLAG_CREATED));
	bl_do_encr_chat_set_date(s_info.TLS, P, date);
	bl_do_encr_chat_set_ttl(s_info.TLS, P, ttl);
	bl_do_encr_chat_set_layer(s_info.TLS ,P, layer);
	bl_do_encr_chat_set_access_hash(s_info.TLS, P, access_hash);
	bl_do_encr_chat_set_state(s_info.TLS, P, state);
	bl_do_encr_chat_set_key(s_info.TLS, P, key, key_fingerprint);
	if (v >= 2) {
		bl_do_encr_chat_set_sha(s_info.TLS, P, sha);
	} else {
		SHA1((void *)key, 256, sha);
		bl_do_encr_chat_set_sha(s_info.TLS, P, sha);
	}
	if (v >= 1) {
		bl_do_encr_chat_set_seq(s_info.TLS, P, in_seq_no, last_in_seq_no, out_seq_no);
	}
}

void read_secret_chat_file(void)
{
	if (s_info.binlog_enabled) {
		return;
	}

	int secret_chat_fd = open(tgl_engine_get_secret_chat_filename(), O_RDWR, 0600);

	if (secret_chat_fd < 0) {
		return;
	}
	//assert(secret_chat_fd >= 0);
	int x;
	if (read(secret_chat_fd, &x, 4) < 4) { close(secret_chat_fd); return; }
	if (x != SECRET_CHAT_FILE_MAGIC) { close(secret_chat_fd); return; }
	int v = 0;
	assert(read(secret_chat_fd, &v, 4) == 4);
	assert(v == 0 || v == 1 || v == 2); // version
	assert(read(secret_chat_fd, &x, 4) == 4);
	assert(x >= 0);
	while(x --> 0) {
		read_secret_chat(secret_chat_fd, v);
	}
	close(secret_chat_fd);
}

void read_state_file(void)
{
	if (s_info.binlog_enabled) {
		return;
	}
	int state_file_fd = open(tgl_engine_get_state_filename(), O_CREAT | O_RDWR, 0600);
	if (state_file_fd < 0)
		return;

	int version, magic;

	if (read(state_file_fd, &magic, 4) < 4) {
		close(state_file_fd);
		return;
	}

	if (magic !=(int)STATE_FILE_MAGIC) {
		close(state_file_fd);
		return;
	}

	if (read(state_file_fd, &version, 4) < 4) {
		close(state_file_fd);
		return;
	}

	assert(version >= 0);
	int x[4];

	if (read(state_file_fd, x, 16) < 16) {
		close(state_file_fd);
		return;
	}

	int pts = x[0];
	int qts = x[1];
	int seq = x[2];
	int date = x[3];
	close(state_file_fd);
	bl_do_set_seq(s_info.TLS, seq);
	bl_do_set_pts(s_info.TLS, pts);
	bl_do_set_qts(s_info.TLS, qts);
	bl_do_set_date(s_info.TLS, date);
}

void read_auth_file(void)
{
	if (s_info.binlog_enabled) {
		return;
	}
	int auth_file_fd;

	auth_file_fd = open(tgl_engine_get_auth_key_filename(), O_CREAT | O_RDWR, 0600);
	if (auth_file_fd < 0) {
		/**
		 * Logging this for handling exceptional cases.
		 */
		empty_auth_file();
		return;
	}

	assert(auth_file_fd >= 0);
	unsigned x;
	unsigned m;

	if (read(auth_file_fd, &m, 4) < 4 ||(m != DC_SERIALIZED_MAGIC)) {
		close(auth_file_fd);
		empty_auth_file();
		return;
	}

	assert(read(auth_file_fd, &x, 4) == 4);
	assert(x > 0);
	int dc_working_num;
	assert(read(auth_file_fd, &dc_working_num, 4) == 4);

	int i;
	for(i = 0; i <=(int)x; i++) {
		int y;
		assert(read(auth_file_fd, &y, 4) == 4);
		if (y) {
			read_dc(auth_file_fd, i, m);
		}
	}

	bl_do_set_working_dc(s_info.TLS, dc_working_num);
	int our_id;
	int l = read(auth_file_fd, &our_id, 4);

	if (l < 4) {
		assert(!l);
	}
	if (our_id) {
		bl_do_set_our_id(s_info.TLS, our_id);
	}
	close(auth_file_fd);
}

void tg_new_msg(struct tgl_state *TLS, struct tgl_message *M)
{
	struct tgl_message *temp_msg = tgl_message_get(TLS, M->id);
	if (temp_msg) {

	}
}

void tg_marked_read(struct tgl_state *TLS, int num, struct tgl_message *list[])
{
	for (int i = 0; i < num; i++) {
		//struct tgl_message
		struct tgl_message* message = list[i];
		int identifier = -1;
		tgl_peer_t* UC;
		UC = tgl_peer_get(TLS, message->to_id);
		struct tgl_user* buddy;
		buddy = &(UC->user);
		char *phone = NULL;
		if (buddy && buddy->phone && strlen(buddy->phone) > 0) {
			phone = buddy->phone;
		}

		message->msg_state = TG_MESSAGE_STATE_READ;

		char *tb_name = get_table_name_from_number(message->to_id.id);
		update_msg_into_db(message, tb_name, identifier);
		if (message->media.type == tgl_message_media_photo) {
			update_sent_media_info_in_db(message, (long long)message->media.photo.id);
		}
		send_message_read_by_buddy_response(TLS->callback_data, message->to_id.id, message->id, tb_name, phone, tgl_get_peer_type(message->to_id));
		free(tb_name);
	}

}

void tg_logprintf(const char *format, ...)
{

}

void on_code_via_phone_result(struct tgl_state *TLS, void *callback_extra, int success)
{
	if (success) {
		printf("success");
	}
}

void request_for_code_via_call(struct tgl_state *TLS, char* phone_no, Eina_Bool trough_sms)
{
	tg_engine_data_s *tg_data;
	tg_data = TLS->callback_data;
	tgl_do_phone_call(TLS, tg_data->phone_number, tg_data->mhash, on_code_via_phone_result, TLS);
}

void tg_get_string(struct tgl_state *TLS, const char *prompt, int flags, void(*callback)(struct tgl_state *TLS, char *string, void *arg), void *arg)
{
	tg_engine_data_s *tg_data;

	tg_data = TLS->callback_data;

	tg_data->get_string = callback;
	tg_data->callback_arg = arg;
	if (strcmp (prompt, "phone number:") == 0) {

		if (tg_data->tg_state == TG_ENGINE_STATE_REGISTRATION) {
			send_request_phone_num_again(tg_data);
		} else {
			tg_data->is_first_time_registration = EINA_TRUE;
			tg_data->tg_state = TG_ENGINE_STATE_REGISTRATION;
			if (tg_data && tg_data->phone_number) {
				tg_data->get_string(TLS, tg_data->phone_number, tg_data->callback_arg);
				tg_data->code_response_timer = ecore_timer_add(60, on_code_request_timer_expired, tg_data);
			}
		}
	} else if (strcmp (prompt, "code('call' for phone call):") == 0) {

		if (tg_data->code_response_timer) {
			ecore_timer_del(tg_data->code_response_timer);
			tg_data->code_response_timer = NULL;
		}

		void **T = arg;
		tg_data->mhash = T[1];

		if (tg_data->tg_state == TG_ENGINE_STATE_CODE_REQUEST) {
			send_request_code_again(tg_data);
		} else {
			tg_data->tg_state = TG_ENGINE_STATE_CODE_REQUEST;
			send_registration_response(tg_data, EINA_TRUE);
		}

	} else if (strcmp (prompt, "register [Y/n]:") == 0) {

		tg_data->tg_state = TG_ENGINE_STATE_PROFILE_REGISTRATION;
		tg_data->get_string(TLS, "Y", tg_data->callback_arg);

	} else if (strcmp (prompt, "First name:") == 0) {
		// request for first name

		tg_data->tg_state = TG_ENGINE_STATE_PROFILE_FIRST_NAME_REGISTRATION;
		tg_data->is_first_time_registration = EINA_TRUE;

		if (tg_data->first_name) {
			tg_data->get_string(TLS, tg_data->first_name, tg_data->callback_arg);
		} else {
			send_name_registration_response(tg_data);
		}

	} else if (strcmp (prompt, "Last name:") == 0) {
		// request for last name
		tg_data->tg_state = TG_ENGINE_STATE_PROFILE_LAST_NAME_REGISTRATION;

		if (tg_data->last_name) {
			tg_data->get_string(TLS, tg_data->last_name, tg_data->callback_arg);
		}

	} else {

		// to be checked

	}
}

void tg_logged_in(struct tgl_state *TLS)
{
	tg_engine_data_s *tg_data;
	tg_data = TLS->callback_data;
	write_auth_file();
	int offline_mode = 0;
	tgl_peer_id_t t_id;
	t_id.id = TLS->our_id;
	t_id.type = TGL_PEER_USER;
	tg_data->is_first_time_registration = EINA_TRUE;
	create_data_base_tables();
	tgl_do_get_user_info(TLS, t_id, offline_mode, &on_user_info_loaded, NULL);
}

static Eina_Bool on_send_media_message_requested(void *data)
{
	sent_media_data_s *media_info = (sent_media_data_s*)data;
	if (media_info) {
		int buddy_id = atoi(media_info->buddy_id);
		int message_id = atoi(media_info->message_id);
		int media_id = atoi(media_info->media_id);
		int msg_type = atoi(media_info->message_type);
		int type_of_chat = atoi(media_info->type_of_chat);

		process_send_media_command(buddy_id, message_id, media_id, msg_type, media_info->file_path, type_of_chat);

		if (media_info->app_name) {
			free(media_info->app_name);
			media_info->app_name = NULL;
		}
		if (media_info->command) {
			free(media_info->command);
			media_info->command = NULL;
		}
		if (media_info->buddy_id) {
			free(media_info->buddy_id);
			media_info->buddy_id = NULL;
		}
		if (media_info->message_id) {
			free(media_info->message_id);
			media_info->message_id = NULL;
		}
		if (media_info->media_id) {
			free(media_info->media_id);
			media_info->media_id = NULL;
		}

		if (media_info->message_type) {
			free(media_info->message_type);
			media_info->message_type = NULL;
		}
		if (media_info->file_path) {
			free(media_info->file_path);
			media_info->file_path = NULL;
		}
		if (media_info->type_of_chat) {
			free(media_info->type_of_chat);
			media_info->type_of_chat = NULL;
		}
		free(media_info);
	}
	return ECORE_CALLBACK_CANCEL;
}

static Eina_Bool on_send_unsent_messages_requested(void *data)
{
	struct tgl_state *TLS = data;
	if (TLS) {
		//tg_engine_data_s *tg_data = TLS->callback_data;

		Eina_List *unset_text_msgs = get_all_unsent_text_messages();
		if (unset_text_msgs && eina_list_count(unset_text_msgs) > 0 ) {
			for (int i = 0 ; i < eina_list_count(unset_text_msgs) ; i++) {
				sent_message_data_s* msg_info = eina_list_nth(unset_text_msgs, i);
				if (msg_info) {
					int buddy_id = atoi(msg_info->buddy_id);
					int message_id = atoi(msg_info->message_id);
					int msg_type = atoi(msg_info->message_type);
					int type_of_chat = atoi(msg_info->type_of_chat);
					process_send_message_command(buddy_id, message_id, msg_type, msg_info->message_data, type_of_chat);

					if (msg_info->app_name) {
						free(msg_info->app_name);
						msg_info->app_name = NULL;
					}
					if (msg_info->command) {
						free(msg_info->command);
						msg_info->command = NULL;
					}
					if (msg_info->buddy_id) {
						free(msg_info->buddy_id);
						msg_info->buddy_id = NULL;
					}
					if (msg_info->message_id) {
						free(msg_info->message_id);
						msg_info->message_id = NULL;
					}

					if (msg_info->message_type) {
						free(msg_info->message_type);
						msg_info->message_type = NULL;
					}
					if (msg_info->message_data) {
						free(msg_info->message_data);
						msg_info->message_data = NULL;
					}
					if (msg_info->type_of_chat) {
						free(msg_info->type_of_chat);
						msg_info->type_of_chat = NULL;
					}
					free(msg_info);
				}

			}
			eina_list_free(unset_text_msgs);
		}

		Eina_List *unset_media_msgs = get_all_unsent_media_messages();
		int init_time = 10;
		if (unset_media_msgs && eina_list_count(unset_media_msgs) > 0 ) {
			for (int i = 0 ; i < eina_list_count(unset_media_msgs) ; i++) {
				sent_media_data_s* media_info = eina_list_nth(unset_media_msgs, i);
				if (media_info) {
/*					int buddy_id = atoi(media_info->buddy_id);
					int message_id = atoi(media_info->message_id);
					int media_id = atoi(media_info->media_id);
					int msg_type = atoi(media_info->message_type);
					int type_of_chat = atoi(media_info->type_of_chat);*/

					sent_media_data_s* new_media_info = (sent_media_data_s*)malloc(sizeof(sent_media_data_s));
					new_media_info->app_name = strdup(media_info->app_name);
					new_media_info->command = strdup(media_info->command);
					new_media_info->buddy_id = strdup(media_info->buddy_id);
					new_media_info->message_id = strdup(media_info->message_id);
					new_media_info->media_id = strdup(media_info->media_id);
					new_media_info->message_type = strdup(media_info->message_type);
					new_media_info->file_path = strdup(media_info->file_path);
					new_media_info->type_of_chat = strdup(media_info->type_of_chat);

					ecore_timer_add(init_time, on_send_media_message_requested, new_media_info);

					//process_send_media_command(buddy_id, message_id, media_id, msg_type, media_info->file_path, type_of_chat);

					if (media_info->app_name) {
						free(media_info->app_name);
						media_info->app_name = NULL;
					}
					if (media_info->command) {
						free(media_info->command);
						media_info->command = NULL;
					}
					if (media_info->buddy_id) {
						free(media_info->buddy_id);
						media_info->buddy_id = NULL;
					}
					if (media_info->message_id) {
						free(media_info->message_id);
						media_info->message_id = NULL;
					}
					if (media_info->media_id) {
						free(media_info->media_id);
						media_info->media_id = NULL;
					}

					if (media_info->message_type) {
						free(media_info->message_type);
						media_info->message_type = NULL;
					}
					if (media_info->file_path) {
						free(media_info->file_path);
						media_info->file_path = NULL;
					}
					if (media_info->type_of_chat) {
						free(media_info->type_of_chat);
						media_info->type_of_chat = NULL;
					}
					free(media_info);
				}

			}
			eina_list_free(unset_media_msgs);
		}

	}
    return ECORE_CALLBACK_CANCEL;
}

void tg_started(struct tgl_state *TLS)
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	tg_data->is_login_activated = EINA_TRUE;
}

void tg_type_notification(struct tgl_state *TLS, struct tgl_user* buddy, enum tgl_typing_status status)
{
	char *name_of_buddy = NULL;

	if (buddy->first_name && buddy->last_name) {
		name_of_buddy = (char *)malloc(strlen(buddy->first_name) + strlen(buddy->last_name) + 1);
		strcpy(name_of_buddy, buddy->first_name);
		strcat(name_of_buddy, buddy->last_name);
	} else if(buddy->first_name) {
		name_of_buddy = (char *)malloc(strlen(buddy->first_name) + 1);
		strcpy(name_of_buddy, buddy->first_name);
	} else {
		name_of_buddy = (char *)malloc(strlen(" ") + 1);
		strcpy(name_of_buddy, " ");
	}

	send_buddy_type_notification_response(TLS->callback_data, buddy->id.id, name_of_buddy, status);

	if (name_of_buddy) {
		free(name_of_buddy);
		name_of_buddy = NULL;
	}
}

void tg_type_in_chat_notification(struct tgl_state *TLS, struct tgl_user *U, struct tgl_chat *C, enum tgl_typing_status status)
{

}

void tg_type_in_secret_chat_notification(struct tgl_state *TLS, struct tgl_secret_chat *E)
{

}

void tg_status_notification(struct tgl_state *TLS, struct tgl_user *buddy)
{
	if (buddy) {
		update_buddy_into_db(BUDDY_INFO_TABLE_NAME, buddy);

		char *name_of_buddy = NULL;

		if (buddy->first_name && buddy->last_name) {
			name_of_buddy = (char *)malloc(strlen(buddy->first_name) + strlen(buddy->last_name) + 1);
			strcpy(name_of_buddy, buddy->first_name);
			strcat(name_of_buddy, buddy->last_name);
		} else if(buddy->first_name) {
			name_of_buddy = (char *)malloc(strlen(buddy->first_name) + 1);
			strcpy(name_of_buddy, buddy->first_name);
		} else {
			name_of_buddy = (char *)malloc(strlen(" ") + 1);
			strcpy(name_of_buddy, " ");
		}

		send_buddy_status_notification_response(TLS->callback_data, buddy->id.id, name_of_buddy, buddy->status.online);

		if (name_of_buddy) {
			free(name_of_buddy);
			name_of_buddy = NULL;
		}

	}
}

void tg_user_registered(struct tgl_state *TLS, struct tgl_user *U)
{

}

void tg_user_activated(struct tgl_state *TLS, struct tgl_user *U)
{

}

void tg_new_authorization(struct tgl_state *TLS, const char *device, const char *location)
{

}

void tg_chat_update(struct tgl_state *TLS, struct tgl_chat* chat_info, unsigned flags)
{
	tg_engine_data_s *tg_data;
	tg_data = TLS->callback_data;

	if (chat_info && chat_info->flags == 144) {
		return;
	}

	if (flags == TGL_GROUP_CHAT_CREATED) {
#if 0
		insert_chat_info_to_db(chat_info, NULL);
		tgl_peer_t* UC = tgl_peer_get(TLS, chat_info->id);
		insert_peer_into_database(UC, 0, 0);
#endif
		//if (tg_data->is_loading_completed) {
			tgl_do_get_chat_info(TLS, chat_info->id, 0, &on_chat_info_received, NULL);
		//}
	}

	if (!(flags & TGL_UPDATE_CREATED)) {

		if (!(flags & TGL_UPDATE_DELETED)) {
			//printf("updated");
		} else {
			//printf("deleted");
		}
	}

}

static inline void send_message(tg_engine_data_s *tg_data, struct tgl_user *buddy, const char *str, const char *name_of_buddy, int name_of_buddy_len)
{
	char *update_msg;
	int len;

	/**
	 * "%s phone number updated" will be changed to IDS_STRING for i18n.
	 */
	len = name_of_buddy_len + strlen(str);
	update_msg = (char *)malloc(len + 1);
	if (!update_msg) {
		return;
	}

	snprintf(update_msg, len, str, name_of_buddy);
	send_contact_updated_response(tg_data, buddy->id.id, update_msg);
	free(update_msg);
}

void tg_user_update(struct tgl_state *TLS, struct tgl_user *buddy, unsigned flags)
{
	char *name_of_buddy;
	int name_of_buddy_len;
	static const char *NO_NAME = " ";

	if (flags & TGL_UPDATE_CREATED) {
		return;
	}

	if (buddy->first_name && buddy->last_name) {
		int first_len = strlen(buddy->first_name);
		int last_len = strlen(buddy->last_name);

		name_of_buddy_len = first_len + last_len;

		name_of_buddy = (char *)malloc(name_of_buddy_len + 1);

		strcpy(name_of_buddy, buddy->first_name);
		strcpy(name_of_buddy + first_len, buddy->last_name);
	} else if(buddy->first_name) {
		name_of_buddy = strdup(buddy->first_name);
		name_of_buddy_len = strlen(name_of_buddy);
	} else {
		name_of_buddy = (char *)NO_NAME;
		name_of_buddy_len = strlen(NO_NAME);
	}

	if (!name_of_buddy) {
		/**
		 * @note
		 * Unable to allocate heap for buddy name
		 */
		name_of_buddy = (char *)NO_NAME;
		name_of_buddy_len = strlen(NO_NAME);
	}

	if (!(flags & TGL_UPDATE_DELETED)) {
		update_buddy_into_db(BUDDY_INFO_TABLE_NAME, buddy);

		if (flags & TGL_UPDATE_PHONE) {
			send_message(TLS->callback_data, buddy, "%s phone number updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_CONTACT) {
			send_message(TLS->callback_data, buddy, "%s contact updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_PHOTO) {
			send_message(TLS->callback_data, buddy, "%s photo updated.", name_of_buddy, name_of_buddy_len);
			//tgl_do_get_user_info(TLS, buddy->id, 0, &on_buddy_info_loaded, NULL);
		}
		if (flags & TGL_UPDATE_BLOCKED) {
			send_message(TLS->callback_data, buddy, "%s contact blocked.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_REAL_NAME) {
			send_message(TLS->callback_data, buddy, "%s name updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_NAME) {
			send_message(TLS->callback_data, buddy, "%s contact name updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_REQUESTED) {
			send_message(TLS->callback_data, buddy, "%s status updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_WORKING) {
			send_message(TLS->callback_data, buddy, "%s status updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_FLAGS) {
			send_message(TLS->callback_data, buddy, "%s flags updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_TITLE) {
			send_message(TLS->callback_data, buddy, "%s title updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_ADMIN) {
			send_message(TLS->callback_data, buddy, "%s admin updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_MEMBERS) {
			send_message(TLS->callback_data, buddy, "%s memgers updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_ACCESS_HASH) {
			send_message(TLS->callback_data, buddy, "%s access hash updated.", name_of_buddy, name_of_buddy_len);
		}
		if (flags & TGL_UPDATE_USERNAME) {
			send_message(TLS->callback_data, buddy, "%s username updated.", name_of_buddy, name_of_buddy_len);
		}
	} else {
		send_message(TLS->callback_data, buddy, "%s contact deleted.", name_of_buddy, name_of_buddy_len);
	}

	if (name_of_buddy != NO_NAME) {
		free(name_of_buddy);
		name_of_buddy = NULL;
	}
}

void tg_secret_chat_update(struct tgl_state *TLS, struct tgl_secret_chat *C, unsigned flags)
{

}

void on_new_chat_info_received(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_chat *chat_info)
{
	tg_engine_data_s *tg_data;

	struct tgl_message *M = callback_extra;

	if (!chat_info) {
		return;
	}

	if (chat_info->user_list) {
		for (int i = 0; i < chat_info->user_list_size; i++) {
			int user_id = chat_info->user_list[i].user_id;
			Eina_Bool is_present_in_db = is_user_present_peer_table(user_id);
			char* tb_name = get_table_name_from_number(user_id);
			create_buddy_msg_table(tb_name);
			if (!is_present_in_db) {
				// add to buddy table
				tgl_peer_id_t from_id;
				from_id.id = user_id;
				from_id.type = TGL_PEER_USER;
				tgl_do_get_user_info(TLS, from_id, 0, on_new_buddy_info_loaded, NULL);
			}
			free(tb_name);
		}
	}

	tg_data = TLS->callback_data;

	tgl_peer_t* UC = tgl_peer_get(TLS, M->from_id);
	int msg_len = strlen(UC->user.first_name) + strlen(" created the group") + 1;
	char* creator_name = (char*)malloc(msg_len);
	strcpy(creator_name, UC->user.first_name);
	strcat(creator_name, " created the group");

	int cur_time = time(NULL);
	M->id = cur_time;
	M->message = creator_name;
	M->message_len = msg_len;
	M->unread = 1;
	M->date = cur_time;
	insert_buddy_msg_to_db(M);
	free(creator_name);

	tgl_peer_t* chat_UC = tgl_peer_get(TLS, chat_info->id);
	insert_chat_info_to_db(chat_info, NULL);
	chat_UC->last = M;
	insert_peer_into_database(chat_UC, 0, 0, 0);

	send_new_group_added_response(tg_data, chat_info->id.id);

}

void on_group_chat_info_updated(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_chat *chat_info)
{
	tg_engine_data_s *tg_data;


	if (!chat_info) {
		return;
	}

	tg_data = TLS->callback_data;
	char *type_of_change = callback_extra;

	if (!type_of_change) {
		type_of_change = strdup("");
	}

	tgl_peer_t* chat_UC = tgl_peer_get(TLS, chat_info->id);
	insert_chat_info_to_db(chat_info, NULL);
	insert_peer_into_database(chat_UC, 0, 0, 0);
	send_group_chat_updated_response(tg_data, chat_info->id.id, type_of_change);
	free(type_of_change);
}

void on_new_chat_pic_loaded(struct tgl_state *TLS, void *callback_extra, int success, char *filename)
{
	struct tgl_message *M = callback_extra;


	if (filename) {

		tgl_peer_t* peer = tgl_peer_get(TLS, M->from_id);
		int msg_len = strlen(peer->user.first_name) + strlen(" changed group icon") + 1;
		char* creator_name = (char*)malloc(msg_len);
		strcpy(creator_name, peer->user.first_name);
		strcat(creator_name, " changed group icon");

		int cur_time = time(NULL);
		M->id = cur_time;
		M->message = creator_name;
		M->message_len = msg_len;
		M->date = cur_time;
		M->unread = 1;
		insert_buddy_msg_to_db(M);
		free(creator_name);
		send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));


		tgl_peer_t* UC = tgl_peer_get(TLS, M->to_id);
		struct tgl_chat *chat_info = &(UC->chat);
		update_chat_info_to_db(chat_info, filename);
		update_peer_info_database(UC, 0);
		update_buddy_pic_db(filename, PEER_INFO_TABLE_NAME, chat_info->id.id);
		send_buddy_profile_pic_updated_response(TLS->callback_data, chat_info->id.id, filename);
	}
}

void on_video_thumb_loaded(struct tgl_state *TLS, void *callback_extra, int success, char *filename)
{
	struct tgl_message *M = (struct tgl_message*)callback_extra;
	if (success && filename) {
		// update in db and send info to app...
		long long media_id = M->media.document.id;
		update_video_thumb_in_db(media_id, filename);
		tg_engine_data_s *tg_data = TLS->callback_data;
		if (M->from_id.id == tg_data->id.id) {
			send_video_thumb_download_completed_response(tg_data, M->from_id.id, M->to_id.id, media_id, filename);
		} else {
			send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
		}
	}
}

struct tg_temp_msg_data {
	Ecore_Timer* send_timer;
	struct tgl_state *TLS;
	struct tgl_message *M;
};

static Eina_Bool on_msg_received_cb(void *data)
{
	struct tg_temp_msg_data *msg_data = data;
	insert_buddy_msg_to_db(msg_data->M);
	if(msg_data->M->media.type != tgl_message_media_none) {
		insert_media_info_to_db(msg_data->M, "");
		if (msg_data->M->media.type != tgl_message_media_none && (msg_data->M->media.document.flags & FLAG_DOCUMENT_VIDEO)) {
			tgl_do_load_document_thumb(msg_data->TLS, &(msg_data->M->media.document), on_video_thumb_loaded, msg_data->M);
			if (msg_data->send_timer) {
				ecore_timer_del(msg_data->send_timer);
			}
			free(msg_data);
			return ECORE_CALLBACK_CANCEL;
		}
	}
	// inform to application
	send_message_received_response(msg_data->TLS->callback_data, msg_data->M->from_id.id, msg_data->M->to_id.id, msg_data->M->id, tgl_get_peer_type(msg_data->M->to_id));
	if (msg_data->send_timer) {
		ecore_timer_del(msg_data->send_timer);
	}
	free(msg_data);
	return ECORE_CALLBACK_CANCEL;
}

void on_requested_chat_info_received(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_chat *chat_info)
{
	tg_engine_data_s *tg_data;

	struct tgl_message *M = callback_extra;

	char *msg_table;


	if (!chat_info) {
		return;
	}
	if (!chat_info->user_list) {
		tgl_do_get_chat_info(TLS, chat_info->id, 0, &on_requested_chat_info_received, callback_extra);
		return;
	}

	tg_data = TLS->callback_data;

	msg_table = get_table_name_from_number(chat_info->id.id);

	create_buddy_msg_table(msg_table);

	insert_chat_info_to_db(chat_info, NULL);
	struct tgl_photo *pic = &(chat_info->photo);
	if(pic) {
		tgl_do_load_photo(TLS, pic ,&on_chat_pic_loaded,chat_info);
	}

	// send message
	int msg_id = insert_current_date_to_table(msg_table);
	if (msg_id > 0) {
		send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, msg_id, tgl_get_peer_type(M->to_id));
		struct tg_temp_msg_data *msg_data = (struct tg_temp_msg_data*)malloc(sizeof(struct tg_temp_msg_data));
		msg_data->M = M;
		msg_data->TLS = TLS;
		msg_data->send_timer = ecore_timer_add(3, on_msg_received_cb, msg_data);
	} else {
		if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_AUDIO)) {
			M->message = strdup("Audio");
			M->message_len = strlen("Audio");
		} else if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_VIDEO)) {
			M->message = strdup("Video");
			M->message_len = strlen("Video");
		}
		insert_buddy_msg_to_db(M);
		if(M->media.type != tgl_message_media_none) {
			insert_media_info_to_db(M, "");
			if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_VIDEO)) {
				tgl_do_load_document_thumb(TLS, &(M->media.document), on_video_thumb_loaded, M);
				return;
			}
		}
		// inform to application
		send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
	}

	free(msg_table);
}


void on_requested_update_chat_received(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_chat *chat_info)
{
	tg_engine_data_s *tg_data;
	char *msg_table;
	msg_table = get_table_name_from_number(chat_info->id.id);
	create_buddy_msg_table(msg_table);
	free(msg_table);
	if (!chat_info) {
		return;
	}
	if (!chat_info->user_list) {
		tgl_do_get_chat_info(TLS, chat_info->id, 0, &on_chat_info_received, NULL);
		return;
	}

	tg_data = TLS->callback_data;

	insert_chat_info_to_db(chat_info, NULL);
	struct tgl_photo *pic = &(chat_info->photo);
	if(pic) {
		tgl_do_load_photo(TLS, pic ,&on_chat_pic_loaded,chat_info);
	}
	//char *type_of_change = strdup("add_user");
	tgl_peer_t* chat_UC = tgl_peer_get(TLS, chat_info->id);
	insert_chat_info_to_db(chat_info, NULL);
	insert_peer_into_database(chat_UC, 0, 0, 0);
	send_response_to_group_chat_updated_response(tg_data, chat_info->id.id);
	//free(type_of_change);
}

void do_update_chat_info(int chat_id)
{
	tgl_peer_id_t to_id;
	to_id.id = chat_id;
	to_id.type = TGL_PEER_CHAT;
	tgl_do_get_chat_info(s_info.TLS, to_id, 0, &on_requested_update_chat_received, NULL);
}

void on_new_buddy_info_loaded(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_user *U)
{
	if(!U) {
		return;
	}
	tg_engine_data_s *tg_data = TLS->callback_data;
	struct tgl_message *M = callback_extra;
	if (U->id.id == tg_data->id.id) {
		return;
	}
	tgl_peer_t* UC = tgl_peer_get(TLS, U->id);
	insert_peer_into_database(UC, 0, 0, 1);
	U->is_unknown = 1;
	init_insert_buddy_into_db(BUDDY_INFO_TABLE_NAME, U);
	struct tgl_photo* pic = &(U->photo);
	if(pic) {
		tgl_do_load_photo(TLS, pic ,&on_buddy_pic_loaded,U);
	}

	send_new_buddy_added_response(tg_data, U->id.id);

	if (M) {
		char* tb_name = get_table_name_from_number(U->id.id);
		int msg_id = insert_current_date_to_table(tb_name);
		free(tb_name);
		if (msg_id > 0) {
			send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, msg_id, tgl_get_peer_type(M->to_id));

			struct tg_temp_msg_data *msg_data = (struct tg_temp_msg_data*)malloc(sizeof(struct tg_temp_msg_data));
			msg_data->M = M;
			msg_data->TLS = TLS;
			msg_data->send_timer = ecore_timer_add(3, on_msg_received_cb, msg_data);
		} else {
			if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_AUDIO)) {
				M->message = strdup("Audio");
				M->message_len = strlen("Audio");
			} else if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_VIDEO)) {
				M->message = strdup("Video");
				M->message_len = strlen("Video");
			}
			insert_buddy_msg_to_db(M);
			if(M->media.type != tgl_message_media_none) {
				insert_media_info_to_db(M, "");
				if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_VIDEO)) {
					tgl_do_load_document_thumb(TLS, &(M->media.document), on_video_thumb_loaded, M);
					return;
				} else if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_AUDIO)) {

				}
			}
			// inform to application
			send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
		}
	}
}

void tg_msg_receive(struct tgl_state *TLS, struct tgl_message *M)
{
	if (M && TLS->started) {

		if (M->flags & (FLAG_MESSAGE_EMPTY | FLAG_DELETED)) {
			return;
		}
		if (!(M->flags & FLAG_CREATED)) {
			return;
		}
		if (M->service) {
			// this is service message. to be handled in telegram.
			if (tgl_get_peer_id (M->from_id) != TLS->our_id) {
				char *type_of_change = NULL;
				if (M->action.type == tgl_message_action_chat_create) {

					char* msg_table = get_table_name_from_number(M->to_id.id);
					create_buddy_msg_table(msg_table);
					int msg_id = insert_current_date_to_table(msg_table);
					free(msg_table);

					tgl_do_get_chat_info(TLS, M->to_id, 0, &on_new_chat_info_received, M);

				} else if (M->action.type == tgl_message_action_chat_edit_title) {
					type_of_change = strdup("edit_title");
					tgl_peer_t* UC = tgl_peer_get(TLS, M->from_id);
					int msg_len = strlen(UC->user.first_name) + strlen(" changed the chat title") + 1;
					char* creator_name = (char*)malloc(msg_len);
					strcpy(creator_name, UC->user.first_name);
					strcat(creator_name, " changed the chat title");

					int cur_time = time(NULL);
					M->id = cur_time;
					M->message = creator_name;
					M->message_len = msg_len;
					M->unread = 1;
					M->date = cur_time;
					insert_buddy_msg_to_db(M);
					free(creator_name);
					send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
					tgl_do_get_chat_info(TLS, M->to_id, 0, &on_group_chat_info_updated, type_of_change);
				} else if (M->action.type == tgl_message_action_chat_edit_photo) {

					char* msg_table = get_table_name_from_number(M->to_id.id);
					create_buddy_msg_table(msg_table);
					int msg_id = insert_current_date_to_table(msg_table);
					free(msg_table);
					struct tgl_photo *pic = &(M->action.photo);
					if(pic) {
						tgl_do_load_photo(TLS, pic ,&on_new_chat_pic_loaded, M);
					}

				} else if (M->action.type == tgl_message_action_chat_delete_photo) {
					type_of_change = strdup("delete_photo");
					tgl_peer_t* UC = tgl_peer_get(TLS,  M->from_id);
					int msg_len = strlen(UC->user.first_name) + strlen(" deleted the profile photo") + 1;
					char* creator_name = (char*)malloc(msg_len);
					strcpy(creator_name, UC->user.first_name);
					strcat(creator_name, " deleted the profile photo");

					int cur_time = time(NULL);
					M->id = cur_time;
					M->message = creator_name;
					M->message_len = msg_len;
					M->unread = 1;
					M->date = cur_time;
					insert_buddy_msg_to_db(M);
					free(creator_name);
					send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));


					char *filename = "";
					tgl_peer_t* lUC = tgl_peer_get(TLS, M->to_id);
					struct tgl_chat *chat_info = &(lUC->chat);
					update_chat_info_to_db(chat_info, filename);
					update_peer_info_database(lUC, 0);
					update_buddy_pic_db(filename, PEER_INFO_TABLE_NAME, chat_info->id.id);
					send_buddy_profile_pic_updated_response(TLS->callback_data, chat_info->id.id, filename);


				} else if (M->action.type == tgl_message_action_chat_add_user) {
					type_of_change = strdup("add_user");
					tgl_peer_t* UC = tgl_peer_get(TLS,  M->from_id);
					int msg_len = strlen(UC->user.first_name) + strlen(" added to the group") + 1;
					char* creator_name = (char*)malloc(msg_len);
					strcpy(creator_name, UC->user.first_name);
					strcat(creator_name, " added to the group");

					int cur_time = time(NULL);
					M->id = cur_time;
					M->message = creator_name;
					M->message_len = msg_len;
					M->unread = 1;
					M->date = cur_time;
					insert_buddy_msg_to_db(M);
					free(creator_name);
					send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
					tgl_do_get_chat_info(TLS, M->to_id, 0, &on_group_chat_info_updated, type_of_change);
				} else if (M->action.type == tgl_message_action_chat_delete_user) {
					type_of_change = strdup("delete_user");
					tgl_peer_t* UC = tgl_peer_get(TLS,  M->from_id);
					int msg_len = strlen(UC->user.first_name) + strlen(" left the group") + 1;
					char* creator_name = (char*)malloc(msg_len);
					strcpy(creator_name, UC->user.first_name);
					strcat(creator_name, " left the group");

					int cur_time = time(NULL);
					M->id = cur_time;
					M->message = creator_name;
					M->message_len = msg_len;
					M->unread = 1;
					M->date = cur_time;
					insert_buddy_msg_to_db(M);
					free(creator_name);
					send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
					tgl_do_get_chat_info(TLS, M->to_id, 0, &on_group_chat_info_updated, type_of_change);
				}
			}
			return;
		}

		if (!tgl_get_peer_type(M->to_id)) {
			// bad message
			return;
		}

		if (tgl_get_peer_type(M->to_id) == TGL_PEER_USER) {
			if (M->out) {
				if (M->unread) {

				} else {

				}
			} else {
				if (M->media.type != tgl_message_media_none) {
					M->message = NULL;
					M->message_len = 0;
				}

				int user_id = M->from_id.id;
#if 0
				Eina_Bool is_present_in_db = is_user_present_peer_table(user_id);
				char* tb_name = get_table_name_from_number(user_id);
				create_buddy_msg_table(tb_name);
				if (!is_present_in_db) {
					// add to buddy table
					tgl_do_get_user_info(TLS, M->from_id, 0, on_new_buddy_info_loaded, NULL);
				}
#else
				char* tb_name = get_table_name_from_number(user_id);
				Eina_Bool is_present_in_db = is_user_present_peer_table(user_id);
				create_buddy_msg_table(tb_name);
				if (!is_present_in_db) {
					tgl_do_get_user_info(TLS, M->from_id, 0, on_new_buddy_info_loaded, M);
					free(tb_name);
					return;
				}
#endif
				int msg_id = update_current_date_to_table(tb_name, M->date);
				free(tb_name);
				if (msg_id > 0) {
					send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, msg_id, tgl_get_peer_type(M->to_id));

					struct tg_temp_msg_data *msg_data = (struct tg_temp_msg_data*)malloc(sizeof(struct tg_temp_msg_data));
					msg_data->M = M;
					msg_data->TLS = TLS;
					msg_data->send_timer = ecore_timer_add(6, on_msg_received_cb, msg_data);
				} else {
					if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_AUDIO)) {
						M->message = strdup("Audio");
						M->message_len = strlen("Audio");
					} else if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_VIDEO)) {
						M->message = strdup("Video");
						M->message_len = strlen("Video");
					}
					insert_buddy_msg_to_db(M);
					if(M->media.type != tgl_message_media_none) {
						insert_media_info_to_db(M, "");
						if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_VIDEO)) {
							tgl_do_load_document_thumb(TLS, &(M->media.document), on_video_thumb_loaded, M);
							return;
						} else if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_AUDIO)) {

						}
					}
					// inform to application
					send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
				}

			}

		} else if (tgl_get_peer_type(M->to_id) == TGL_PEER_ENCR_CHAT) {

		} else {

			if ((tgl_get_peer_type (M->from_id) == TGL_PEER_USER) && (tgl_get_peer_id (M->from_id) == TLS->our_id)) {

			} else {
				if (M->media.type != tgl_message_media_none) {
					M->message = NULL;
					M->message_len = 0;
				}
				int user_id = 0;
				if (tgl_get_peer_type(M->to_id) == TGL_PEER_USER) {
					user_id = M->from_id.id;
				} else if (tgl_get_peer_type(M->to_id) == TGL_PEER_CHAT) {
					user_id = M->to_id.id;
				}

				// check whether user is present or not

				Eina_Bool is_present_in_peer_db = is_user_present_peer_table(user_id);

				if (!is_present_in_peer_db) {
					tgl_do_get_chat_info(TLS, M->to_id, 0, &on_requested_chat_info_received, M);
					return;
				}

				Eina_Bool is_present_in_chat_db = is_user_present_chat_table(user_id);
				if (!is_present_in_chat_db) {
					//sandeep
					tgl_do_get_chat_info(TLS, M->to_id, 0, &on_requested_chat_info_received, M);
					return;
				}

				char* tb_name = get_table_name_from_number(user_id);
				int msg_id = update_current_date_to_table(tb_name, M->date);
				free(tb_name);
				if (msg_id > 0) {
					send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, msg_id, tgl_get_peer_type(M->to_id));
					struct tg_temp_msg_data *msg_data = (struct tg_temp_msg_data*)malloc(sizeof(struct tg_temp_msg_data));
					msg_data->M = M;
					msg_data->TLS = TLS;
					msg_data->send_timer = ecore_timer_add(6, on_msg_received_cb, msg_data);
				} else {
					if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_AUDIO)) {
						M->message = strdup("Audio");
						M->message_len = strlen("Audio");
					} else if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_VIDEO)) {
						M->message = strdup("Video");
						M->message_len = strlen("Video");
					}
					insert_buddy_msg_to_db(M);
					if(M->media.type != tgl_message_media_none) {
						insert_media_info_to_db(M, "");
						if (M->media.type != tgl_message_media_none && (M->media.document.flags & FLAG_DOCUMENT_VIDEO)) {
							tgl_do_load_document_thumb(TLS, &(M->media.document), on_video_thumb_loaded, M);
							return;
						}
					}
					// inform to application
					send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
				}
			}
		}
	}
}

void tg_our_id(struct tgl_state *TLS, int id)
{

}

void tg_notification(struct tgl_state *TLS, char *type, char *message)
{

}

void tg_user_status_update(struct tgl_state *TLS, struct tgl_user *U)
{

	if (tgl_get_peer_type (U->id) != TGL_PEER_USER) {
		return;
	}

	if (!U) {
		// unknown user
	} else {
		if ((U->flags & FLAG_DELETED)) {
			// deleted user
		} else if (!(U->flags & FLAG_CREATED)) {
			// newly created user
		} else {
			// existing user

		}

		if (U->flags & FLAG_USER_SELF) {
			update_buddy_into_db(USER_INFO_TABLE_NAME, U);
		} else if (U->flags & FLAG_USER_CONTACT) {
			update_buddy_into_db(BUDDY_INFO_TABLE_NAME, U);
#if 0
			struct tgl_user_status *S = &(U->status);

			if (S->online > 0) {
				//online;
			} else {
				if (S->online == 0) {
					//"offline
				} else if (S->online == -1) {
					//offline was online ");
				} else if (S->online == -2) {
					// offline (was online recently)
				} else if (S->online == -3) {
					//offline (was online last week)
				} else if (S->online == -4) {
					//offline (was online last month)
				}
			}
#endif
			// update status to application.
			send_buddy_status_updated_response(TLS->callback_data, U->id.id);

		} else {

		}
	}

}

char *tg_create_print_name(struct tgl_state *TLS, tgl_peer_id_t id, const char *a1, const char *a2, const char *a3, const char *a4)
{
	return NULL;
}

struct tgl_update_callback upd_cb = {
	.new_msg = tg_new_msg,
	.marked_read = tg_marked_read,
	.logprintf = tg_logprintf,
	.get_string = tg_get_string,
	.logged_in = tg_logged_in,
	.started = tg_started,
	.type_notification = tg_type_notification,
	.type_in_chat_notification = tg_type_in_chat_notification,
	.type_in_secret_chat_notification = tg_type_in_secret_chat_notification,
	.status_notification = tg_status_notification,
	.user_registered = tg_user_registered,
	.user_activated = tg_user_activated,
	.new_authorization = tg_new_authorization,
	.user_update = tg_user_update,
	.chat_update = tg_chat_update,
	.secret_chat_update = tg_secret_chat_update,
	.msg_receive = tg_msg_receive,
	.our_id = tg_our_id,
	.user_status_update = tg_user_status_update
};

void on_chat_pic_loaded(struct tgl_state *TLS, void *callback_extra, int success, char *filename)
{
	struct tgl_chat *chat_info = callback_extra;

	if (filename) {
		update_chat_info_to_db(chat_info, filename);
		tgl_peer_t* UC = tgl_peer_get(TLS, chat_info->id);
		update_peer_info_database(UC, 0);
		update_buddy_pic_db(filename, PEER_INFO_TABLE_NAME, chat_info->id.id);
		send_buddy_profile_pic_updated_response(TLS->callback_data, chat_info->id.id, filename);
	}
}

void on_buddy_pic_loaded(struct tgl_state *TLS, void *callback_extra, int success, char *filename)
{
	struct tgl_user *buddy = callback_extra;
	tg_engine_data_s *tg_data = TLS->callback_data;

	if (buddy && buddy->id.id == tg_data->id.id) {
		if(filename) {
			update_buddy_pic_db(filename, USER_INFO_TABLE_NAME, buddy->id.id);
			update_buddy_pic_db(filename, BUDDY_INFO_TABLE_NAME, buddy->id.id);
			send_buddy_profile_pic_updated_response(TLS->callback_data, buddy->id.id, filename);
		}
		return;
	}

	if (filename) {
		update_buddy_pic_db(filename, BUDDY_INFO_TABLE_NAME, buddy->id.id);
		update_buddy_pic_db(filename, PEER_INFO_TABLE_NAME, buddy->id.id);
		send_buddy_profile_pic_updated_response(TLS->callback_data, buddy->id.id, filename);
	}
}

#if 0
void on_new_group_icon_loaded(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *M)
{
	struct tgl_chat *chat_info = callback_extra;
	tg_engine_data_s *tg_data;

	tg_data = TLS->callback_data;

	if(tg_data->new_group_icon) {

		char *msg_table = get_table_name_from_number(chat_info->id.id);
		create_buddy_msg_table(msg_table);

		char *msg_data = "group icon changed.";
		struct tgl_message msg;
		msg.from_id.id = 0;
		msg.from_id.type = 0;
		msg.date = 0;
		msg.flags = 0;
		msg.fwd_date = 0;
		msg.fwd_from_id.id = 0;
		msg.fwd_from_id.type = 0;
		msg.id = 0;
		msg.message = msg_data;
		msg.message_len = strlen (msg_data);
		msg.out = 0;
		msg.service = 0;
		msg.to_id.id = 0;
		msg.to_id.type = tg_data->id.type;
		msg.unread = 0;
		msg.media.type = -1;
		int t = time(NULL);
		insert_msg_into_db(&msg, msg_table, t);
		free(msg_table);

		update_chat_info_to_db(chat_info, tg_data->new_group_icon);
		update_buddy_pic_db(tg_data->new_group_icon, PEER_INFO_TABLE_NAME, chat_info->id.id);
		send_buddy_profile_pic_updated_response(TLS->callback_data, chat_info->id.id, tg_data->new_group_icon);

		free(tg_data->new_group_icon);
		tg_data->new_group_icon = NULL;
	}
}
#endif

void on_chat_info_received(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_chat *chat_info)
{
	tg_engine_data_s *tg_data;
	char *msg_table;

	if (!chat_info) {
		return;
	}
	if (chat_info->flags == 144) {
		return;
	}
	msg_table = get_table_name_from_number(chat_info->id.id);
	create_buddy_msg_table(msg_table);

	int msg_count = get_number_of_messages(msg_table);
	if (msg_count <= 0) {
		if (chat_info->admin_id > 0) {
			set_date_item_to_table(msg_table, chat_info->date);
			tgl_peer_id_t admin_id;
			admin_id.id = chat_info->admin_id;
			admin_id.type = TGL_PEER_USER;

			tgl_peer_t* UC = tgl_peer_get(TLS, admin_id);
			int msg_len = strlen(UC->user.first_name) + strlen(" created the group") + 1;
			char* creator_name = (char*)malloc(msg_len);
			strcpy(creator_name, UC->user.first_name);
			strcat(creator_name, " created the group");
			struct tgl_message msg;
			int cur_time = chat_info->date;
			msg.to_id = chat_info->id;
			msg.from_id = admin_id;
			msg.id = cur_time;
			msg.message = creator_name;
			msg.message_len = msg_len;
			msg.unread = 0;
			msg.date = cur_time;
			msg.media.type = tgl_message_media_none;
			msg.service = 1;
			msg.out = 0;

			insert_buddy_msg_to_db(&msg);
			free(creator_name);
			send_message_received_response(TLS->callback_data, msg.from_id.id, msg.to_id.id, msg.id, tgl_get_peer_type(msg.to_id));
		}

	}

	free(msg_table);
	if (!chat_info->user_list) {
		tgl_do_get_chat_info(TLS, chat_info->id, 0, &on_chat_info_received, NULL);
		return;
	}

	tg_data = TLS->callback_data;

	insert_chat_info_to_db(chat_info, NULL);
	struct tgl_photo *pic = &(chat_info->photo);
	if(pic) {
		tgl_do_load_photo(TLS, pic ,&on_chat_pic_loaded,chat_info);
	}
}

void on_buddy_info_loaded(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_user *U)
{
	if(!U) {
		return;
	}
	tg_engine_data_s *tg_data = TLS->callback_data;
	if (U->id.id == tg_data->id.id) {
		return;
	}

	//update_buddy_into_db(BUDDY_INFO_TABLE_NAME, U);
	struct tgl_photo* pic = &(U->photo);
	if(pic) {
		tgl_do_load_photo(TLS, pic ,&on_buddy_pic_loaded,U);
	}
}

void on_chat_history_received(struct tgl_state *TLS, void *callback_extra, int success, int size, struct tgl_message *list[])
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	for (int i = 0; i < size; i++) {
		struct tgl_message* message = list[i];
		if (message->service || message->from_id.id == tg_data->id.id) {
			continue;
		}
		Eina_Bool ret = insert_buddy_msg_to_db(message);
		if (ret) {
			tg_msg_receive(s_info.TLS, message);
		}
	}
	tg_data->current_chat_index = tg_data->current_chat_index + 1;
	if (tg_data->current_chat_index < eina_list_count(tg_data->chat_list)) {
		tgl_peer_t* UC = eina_list_nth(tg_data->chat_list, tg_data->current_chat_index);
		tgl_do_get_history(s_info.TLS, UC->id, 20, 0, on_chat_history_received, UC);
	} else {
		tg_data->current_chat_index = 0;
	}
}

static Eina_Bool on_load_chat_history_requested(void *data)
{
	struct tgl_state *TLS = data;
	if (TLS) {
		tg_engine_data_s *tg_data = TLS->callback_data;
		tg_data->current_chat_index = 0;
		tgl_peer_t* UC = eina_list_nth(tg_data->chat_list, tg_data->current_chat_index);
		tgl_do_get_history(s_info.TLS, UC->id, 20, 0, on_chat_history_received, UC);
	}
	return ECORE_CALLBACK_CANCEL;
}

void on_buddy_history_received(struct tgl_state *TLS, void *callback_extra, int success, int size, struct tgl_message *list[])
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	for (int i = 0; i < size; i++) {
		struct tgl_message* message = list[i];
		if (message->service || message->from_id.id == tg_data->id.id) {
			continue;
		}
		Eina_Bool ret = insert_buddy_msg_to_db(message);
		if (ret) {
			tg_msg_receive(s_info.TLS, message);
		}
	}
	tg_data->current_buddy_index = tg_data->current_buddy_index + 1;
	if (tg_data->current_buddy_index < eina_list_count(tg_data->buddy_list)) {
		tgl_peer_t* UC = eina_list_nth(tg_data->buddy_list, tg_data->current_buddy_index);
		tgl_do_get_history(s_info.TLS, UC->id, 20, 0, on_buddy_history_received, UC);
	} else {
		tg_data->current_buddy_index = 0;
		ecore_timer_add(5, on_load_chat_history_requested, TLS);
	}
}

static Eina_Bool on_load_buddy_history_requested(void *data)
{
	struct tgl_state *TLS = data;
	if (TLS) {
		tg_engine_data_s *tg_data = TLS->callback_data;
		tg_data->current_buddy_index = 0;
		tgl_peer_t* UC = eina_list_nth(tg_data->buddy_list, tg_data->current_buddy_index);
		tgl_do_get_history(s_info.TLS, UC->id, 20, 0, on_buddy_history_received, UC);
	}
	return ECORE_CALLBACK_CANCEL;
}

void on_contacts_received(struct tgl_state *TLS, void *callback_extra, int success, int size, struct tgl_user *contacts[])
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	for (int i = size - 1; i >= 0; i--) {
		struct tgl_user *buddy = contacts[i];
		char* msg_table = get_table_name_from_number(buddy->id.id);
		create_buddy_msg_table(msg_table);
		free(msg_table);

		if (buddy->id.id == 333000 || buddy->id.id == 777000) {
			buddy->is_unknown = 1;
		} else {
			buddy->is_unknown = 0;
		}
		init_insert_buddy_into_db(BUDDY_INFO_TABLE_NAME, buddy);
		tgl_peer_t* UC = tgl_peer_get(TLS, buddy->id);
		if (UC) {
			init_insert_peer_into_database(UC, 0, 0, 0);
		}
	}

	// inform client that contact loading is done.
	//send_contacts_load_done_response(EINA_TRUE);
	send_contacts_and_chats_load_done_response(TLS->callback_data, EINA_TRUE);

	for (int i = size - 1; i >= 0; i--) {
		struct tgl_user *buddy = contacts[i];
		tgl_do_get_user_info(TLS, buddy->id, 0, on_buddy_info_loaded, NULL);
	}
	send_response_for_server_connection_status(tg_data, tg_data->is_login_activated);
	ecore_timer_add(3, on_send_unsent_messages_requested, TLS);
	ecore_timer_add(6, on_load_buddy_history_requested, TLS);
}


void on_contacts_and_chats_loaded(struct tgl_state *TLS, void *callback_extra, int success, int size, tgl_peer_id_t peers[], int last_msg_id[], int unread_count[])
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	if (tg_data->chat_list) {
		eina_list_free(tg_data->chat_list);
		tg_data->chat_list = NULL;
	}
	if (tg_data->buddy_list) {
		eina_list_free(tg_data->buddy_list);
		tg_data->buddy_list = NULL;
	}
	for (int i = size - 1; i >= 0; i--) {
		tgl_peer_t* UC = tgl_peer_get(TLS, peers[i]);
        // user exited from chat
		if(UC->flags == 144) {
			continue;
		}

		// insert into peer table
		insert_peer_into_database(UC, last_msg_id[i], unread_count[i], 0);
		switch (tgl_get_peer_type(peers[i])) {
			case TGL_PEER_USER:
				tg_data->buddy_list = eina_list_append(tg_data->buddy_list, UC);
				break;
			case TGL_PEER_CHAT:
				tg_data->chat_list = eina_list_append(tg_data->chat_list, UC);
				break;
			case TGL_PEER_ENCR_CHAT:
				// To-Do
				break;
			default:
				break;
		}
	}
	tgl_do_update_contact_list(TLS, on_contacts_received, NULL);
}

void add_contacts_to_account(struct tgl_state *TLS)
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	if(sc_db_utils_connect())
	{
		Eina_List* contact_list = get_contact_list_from_device_db();
		sc_db_utils_disconnect();

		if (!contact_list || eina_list_count(contact_list) <= 0) {
			// no contacts avilable. empty contact list.
			tgl_do_get_dialog_list(TLS, on_contacts_and_chats_loaded, NULL);
			if (contact_list) {
				eina_list_free(contact_list);
			}
			return;
		}
		int size = eina_list_count(contact_list);
		if (size > 0) {
			add_contacts_to_user(tg_data, size, contact_list);
		} else {
			eina_list_free(contact_list);
			tgl_do_get_dialog_list(TLS, on_contacts_and_chats_loaded, NULL);
		}
	}
}

void on_user_info_loaded(struct tgl_state *TLS, void *extra, int success, struct tgl_user *buddy)
{
	tg_engine_data_s *tg_data = TLS->callback_data;

	tg_data->id.id = buddy->id.id;
	tg_data->id.type = buddy->id.type;

	struct tgl_photo* pic = &(buddy->photo);
	if(pic) {
		tgl_do_load_photo(TLS, pic ,&on_buddy_pic_loaded, buddy);
	}
	buddy->is_unknown = 0;
	init_insert_buddy_into_db(USER_INFO_TABLE_NAME, buddy);

	if (tg_data->is_first_time_registration) {
		// send contact list to add friends.
		//send_add_contacts_request(tg_data);
		add_contacts_to_account(TLS);
	} else {
		tgl_do_get_dialog_list(TLS, on_contacts_and_chats_loaded, NULL);
	}
}

void on_message_sent_to_buddy(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *message)
{
	tg_engine_data_s *tg_data;
	struct tgl_message* org_msg = (struct tgl_message*)callback_extra;
	tg_data = TLS->callback_data;

	if (success && message) {
		tgl_peer_t* UC = tgl_peer_get(TLS, message->to_id);
		if (UC) {
			message->msg_state = TG_MESSAGE_STATE_SENT;
			char* tb_name = get_table_name_from_number(message->to_id.id);
			update_msg_into_db(message, tb_name, org_msg->id);

			// delete message from unsent db
			delete_message_from_unsent_db(org_msg->id);
			delete_media_from_unsent_db(org_msg->id);

			if (message->media.type == tgl_message_media_photo || message->media.type == tgl_message_media_document || message->media.type == tgl_message_media_geo) {
				update_sent_media_info_in_db(message, (long long)org_msg->id);
			}
			send_message_sent_to_buddy_response(tg_data, message->to_id.id, message->id, tb_name, EINA_TRUE, tgl_get_peer_type(message->to_id));
			free(tb_name);

			if (message->media.type != tgl_message_media_none && (message->media.document.flags & FLAG_DOCUMENT_VIDEO)) {
				//tgl_do_load_document_thumb(TLS, &(message->media.document), on_video_thumb_loaded, message);
			}

		}
	} else {
		if (org_msg) {
			org_msg->msg_state = TG_MESSAGE_STATE_FAILED;
			char* tb_name = get_table_name_from_number(org_msg->to_id.id);
			update_msg_into_db(org_msg, tb_name, org_msg->id);
			if (org_msg->media.type == tgl_message_media_photo || org_msg->media.type == tgl_message_media_document || message->media.type == tgl_message_media_geo) {
				update_sent_media_info_in_db(org_msg, (long long)org_msg->id);
			}
			send_message_sent_to_buddy_response(tg_data, org_msg->to_id.id, org_msg->id, tb_name, EINA_FALSE, tgl_get_peer_type(org_msg->to_id));
			free(tb_name);
		}
	}
	if (org_msg) {
		if (org_msg->message) {
			free(org_msg->message);
		}
		free(org_msg);
	}
}

void on_image_download_completed(struct tgl_state *TLS, void *callback_extra, int success, char *filename)
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	struct tgl_photo* photo_prop = (struct tgl_photo*)callback_extra;
	long long media_id = photo_prop->id;
	int buddy_id = photo_prop->user_id;
	int to_id = photo_prop->to_peer_id;
	if (success) {
		if(photo_prop && filename) {
			update_receive_media_info_in_db(media_id, filename);
			//send response to application
			send_media_download_completed_response(tg_data, buddy_id, to_id, media_id, filename);
			free(photo_prop);
		}
	} else {
		send_media_download_completed_response(tg_data, buddy_id, to_id, media_id, NULL);
	}
}

void on_document_download_completed(struct tgl_state *TLS, void *callback_extra, int success, char *filename)
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	struct tgl_document* doc_prop = (struct tgl_document*)callback_extra;
	long long media_id = doc_prop->id;
	int buddy_id = doc_prop->user_id;
	int to_id = doc_prop->to_peer_id;
	if (success) {
		if(doc_prop && filename) {
			update_receive_media_info_in_db(media_id, filename);
			//send response to application
			send_media_download_completed_response(tg_data, buddy_id, to_id, media_id, filename);
		}
	} else {
		send_media_download_completed_response(tg_data, buddy_id, to_id, media_id, NULL);
	}

	if (doc_prop) {
		if (doc_prop->caption) {
			free(doc_prop->caption);
		}
		free(doc_prop);
	}

}

void free_contact_data(Eina_List *contact_data)
{
	if (contact_data) {
		for (int i = 0; i < eina_list_count(contact_data); i++) {
			contact_data_s* contact = eina_list_nth(contact_data, i);
			if (contact) {
				if (contact->display_name) {
					free(contact->display_name);
					contact->display_name = NULL;
				}
				if (contact->first_name) {
					free(contact->first_name);
					contact->first_name = NULL;
				}
				if (contact->last_name) {
					free(contact->last_name);
					contact->last_name = NULL;
				}
				if (contact->phone_number) {
					free(contact->phone_number);
					contact->phone_number = NULL;
				}
			}
			free(contact);
		}
		eina_list_free(contact_data);
	}
}

void on_contact_added(struct tgl_state *TLS,void *callback_extra, int success, int size, struct tgl_user *users[])
{
	tg_engine_data_s* data = callback_extra;

	data->current_index++;

	if (data->current_index < eina_list_count(data->contact_list_to_add)) {
		contact_data_s* contact = eina_list_nth(data->contact_list_to_add, data->current_index);

		if (contact) {
			char *first_name = contact->first_name;
			char *last_name = contact->last_name;
			char *phone_number = contact->phone_number;

			if (!first_name) {
				first_name = contact->display_name;
				if (!first_name) {
					first_name = "";
				}
			}

			if (!last_name) {
				last_name = "";
			}

			if (first_name && last_name && phone_number) {
				tgl_do_add_contact(tgl_engine_get_TLS(), phone_number, first_name, last_name, 0, on_contact_added, data);
			} else {
				on_contact_added(tgl_engine_get_TLS(), data, 0, 0, NULL);
			}
		}

	} else {
		tgl_do_get_dialog_list(TLS, on_contacts_and_chats_loaded, NULL);
		free_contact_data(data->contact_list_to_add);
		data->contact_list_to_add = NULL;
	}
}

void on_new_group_icon_loaded(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *M)
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	if (!success) {
		// send fail notification
	} else {
		// send success notofication
		if (M) {
			if (M->action.type == tgl_message_action_chat_create) {

			} else if (M->action.type == tgl_message_action_chat_edit_title) {

			} else if (M->action.type == tgl_message_action_chat_edit_photo) {

				char* msg_table = get_table_name_from_number(M->to_id.id);
				create_buddy_msg_table(msg_table);
				int msg_id = insert_current_date_to_table(msg_table);

				tgl_peer_t* UC = tgl_peer_get(TLS, M->from_id);
				int msg_len = strlen(UC->user.first_name) + strlen(" changed profile photo") + 1;
				char* creator_name = (char*)malloc(msg_len);
				strcpy(creator_name, UC->user.first_name);
				strcat(creator_name, " changed profile photo");


				//send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id,msg_id, tgl_get_peer_type(M->to_id));
				int cur_time = time(NULL);
				M->id = cur_time;
				M->message = creator_name;
				M->message_len = msg_len;
				M->unread = 1;
				M->date = cur_time;
				insert_buddy_msg_to_db(M);
				free(creator_name);
				free(msg_table);
				struct tgl_photo *pic = &(M->action.photo);
				if(pic) {
					tgl_peer_t* UC = tgl_peer_get(TLS, M->to_id);
					struct tgl_chat *chat_info = &(UC->chat);
					tgl_do_load_photo(TLS, pic ,&on_chat_pic_loaded, chat_info);
				}


			} else if (M->action.type == tgl_message_action_chat_delete_photo) {

			} else if (M->action.type == tgl_message_action_chat_add_user) {

			} else if (M->action.type == tgl_message_action_chat_delete_user) {

			}
			send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));


		}
	}

}

void on_new_group_created(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *M)
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	if (!success) {
		// send fail notification
	} else {
		// send success notofication
		if (M) {
			if (M->action.type == tgl_message_action_chat_create) {
				char* msg_table = get_table_name_from_number(M->to_id.id);
				create_buddy_msg_table(msg_table);


				int msg_id = insert_current_date_to_table(msg_table);
				//send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id,msg_id, tgl_get_peer_type(M->to_id));


				tgl_peer_t* UC = tgl_peer_get(TLS, M->from_id);
				int msg_len = strlen(UC->user.first_name) + strlen(" created the group") + 1;
				char* creator_name = (char*)malloc(msg_len);
				strcpy(creator_name, UC->user.first_name);
				strcat(creator_name, " created the group");



				int cur_time = time(NULL);
				M->id = cur_time;
				M->message = creator_name;
				M->message_len = msg_len;
				M->unread = 1;
				M->date = cur_time;

				insert_buddy_msg_to_db(M);
				free(creator_name);
				free(msg_table);
				tgl_peer_t* chat_UC = tgl_peer_get(TLS, M->to_id);
				chat_UC->chat.date = M->date;
				insert_chat_info_to_db(&(chat_UC->chat), NULL);
				chat_UC->last = M;
				insert_peer_into_database(chat_UC, 0, 0, 0);

				if (tg_data->new_group_icon) {
					tgl_peer_t* UC = tgl_peer_get(TLS, M->to_id);
					struct tgl_chat *chat_info = &(UC->chat);
					tgl_do_set_chat_photo(TLS, chat_info->id, tg_data->new_group_icon, on_new_group_icon_loaded, chat_info);
				}


			} else if (M->action.type == tgl_message_action_chat_edit_title) {

			} else if (M->action.type == tgl_message_action_chat_edit_photo) {

			} else if (M->action.type == tgl_message_action_chat_delete_photo) {

			} else if (M->action.type == tgl_message_action_chat_add_user) {

			} else if (M->action.type == tgl_message_action_chat_delete_user) {

			}
			send_new_group_added_response(tg_data, M->to_id.id);
		}
	}
}

void on_set_profile_picture_response_received(struct tgl_state *TLS, void *callback_extra, int success)
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	char *file_path = callback_extra;
	if (success) {
		// update db
		update_buddy_pic_db(file_path, USER_INFO_TABLE_NAME, tg_data->id.id);
		update_buddy_pic_db(file_path, BUDDY_INFO_TABLE_NAME, tg_data->id.id);
		send_self_profile_picture_updated_response(tg_data, file_path, EINA_TRUE);
	} else {
		send_self_profile_picture_updated_response(tg_data, file_path, EINA_FALSE);
	}
	if (file_path) {
		free(file_path);
	}
}
void set_profile_picture(tg_engine_data_s *tg_data, int buddy_id, const char *file_path)
{
	if (file_path) {
		char *org_path = strdup(file_path);
		tgl_do_set_profile_photo(tgl_engine_get_TLS(), (char*)file_path, on_set_profile_picture_response_received, org_path);
	}
}

void on_set_new_chat_title_response_received(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *M)
{
	if (success) {
		char *type_of_change = NULL;
		if (M && M->action.type == tgl_message_action_chat_edit_title) {
			type_of_change = strdup("edit_title");
			tgl_peer_t* UC = tgl_peer_get(TLS, M->from_id);
			int msg_len = strlen(UC->user.first_name) + strlen(" changed the chat title") + 1;
			char* creator_name = (char*)malloc(msg_len);
			strcpy(creator_name, UC->user.first_name);
			strcat(creator_name, " changed the chat title");

			int cur_time = time(NULL);
			M->id = cur_time;
			M->message = creator_name;
			M->message_len = msg_len;
			M->unread = 1;
			M->date = cur_time;
			insert_buddy_msg_to_db(M);
			free(creator_name);
			send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
			tgl_do_get_chat_info(TLS, M->to_id, 0, &on_group_chat_info_updated, type_of_change);
		}
	} else {
		tg_engine_data_s *tg_data = TLS->callback_data;
		struct tgl_chat *chat_info = (struct tgl_chat*)callback_extra;
		send_group_chat_rename_response(tg_data, chat_info->id.id, EINA_FALSE);
	}
}

void set_group_chat_new_title(tg_engine_data_s *tg_data, int buddy_id, const char *new_title)
{
	if (new_title) {
		tgl_peer_id_t peer_id;
		peer_id.id = buddy_id;
		peer_id.type = TGL_PEER_CHAT;

		tgl_peer_t* UC = tgl_peer_get(tgl_engine_get_TLS(), peer_id);
		struct tgl_chat *chat_info = &(UC->chat);
		tgl_do_rename_chat(tgl_engine_get_TLS(), chat_info->id, (char*)new_title, on_set_new_chat_title_response_received, chat_info);
	}
}

void on_new_buddy_added_to_chat_response_received(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *M)
{
	if (success) {
		char *type_of_change = NULL;
		if (M && M->action.type == tgl_message_action_chat_add_user) {
			type_of_change = strdup("add_user");
			tgl_peer_t* UC = tgl_peer_get(TLS,  M->from_id);

			tgl_peer_id_t added_id;
			added_id.id = M->action.user;
			added_id.type = TGL_PEER_USER;

			tgl_peer_t* added_UC = tgl_peer_get(TLS, added_id);
			char* new_user_name = replace(added_UC->print_name, '_', " ");
			int msg_len = strlen(UC->user.first_name) + strlen(" added ") + strlen(new_user_name) + 1;
			char* creator_name = (char*)malloc(msg_len);
			strcpy(creator_name, UC->user.first_name);
			strcat(creator_name, " added ");
			strcat(creator_name, new_user_name);
			free(new_user_name);

			int cur_time = time(NULL);
			M->id = cur_time;
			M->message = creator_name;
			M->message_len = msg_len;
			M->unread = 1;
			M->date = cur_time;
			insert_buddy_msg_to_db(M);
			free(creator_name);
			send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
			tgl_do_get_chat_info(TLS, M->to_id, 0, &on_group_chat_info_updated, type_of_change);
		}
	} else {
		tg_engine_data_s *tg_data = TLS->callback_data;
		struct tgl_chat *chat_info = (struct tgl_chat*)callback_extra;
		send_group_chat_new_buddy_response(tg_data, chat_info->id.id, EINA_FALSE);
	}
}

void set_group_chat_add_new_buddy(tg_engine_data_s *tg_data, int s_buddy_id, int s_chat_id)
{
	tgl_peer_id_t chat_id;
	chat_id.id = s_chat_id;
	chat_id.type = TGL_PEER_CHAT;

	tgl_peer_id_t buddy_id;
	buddy_id.id = s_buddy_id;
	buddy_id.type = TGL_PEER_USER;

	tgl_peer_t* UC = tgl_peer_get(tgl_engine_get_TLS(), chat_id);
	struct tgl_chat *chat_info = &(UC->chat);
	tgl_do_add_user_to_chat(tgl_engine_get_TLS(), chat_id, buddy_id, 100, on_new_buddy_added_to_chat_response_received, chat_info);
}


void on_buddy_removed_from_chat_response_received(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *M)
{
	if (success) {
		char *type_of_change = NULL;
		if (M && M->action.type == tgl_message_action_chat_delete_user) {
			type_of_change = strdup("delete_user");
			tgl_peer_t* UC = tgl_peer_get(TLS,  M->from_id);
			tgl_peer_id_t added_id;
			added_id.id = M->action.user;
			added_id.type = TGL_PEER_USER;

			tgl_peer_t* added_UC = tgl_peer_get(TLS, added_id);
			char* new_user_name = replace(added_UC->print_name, '_', " ");
			int msg_len = strlen(UC->user.first_name) + strlen(" removed ") + strlen(new_user_name) + 1;
			char* creator_name = (char*)malloc(msg_len);
			strcpy(creator_name, UC->user.first_name);
			strcat(creator_name, " removed ");
			strcat(creator_name, new_user_name);
			free(new_user_name);
			int cur_time = time(NULL);
			M->id = cur_time;
			M->message = creator_name;
			M->message_len = msg_len;
			M->unread = 1;
			M->date = cur_time;
			insert_buddy_msg_to_db(M);
			free(creator_name);
			send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
			tgl_do_get_chat_info(TLS, M->to_id, 0, &on_group_chat_info_updated, type_of_change);
		}
	} else {
		tg_engine_data_s *tg_data = TLS->callback_data;
		struct tgl_chat *chat_info = (struct tgl_chat*)callback_extra;
		send_group_chat_delete_buddy_response(tg_data, chat_info->id.id, EINA_FALSE);
	}
}

void set_group_chat_remove_buddy(tg_engine_data_s *tg_data, int s_buddy_id, int s_chat_id)
{
	tgl_peer_id_t chat_id;
	chat_id.id = s_chat_id;
	chat_id.type = TGL_PEER_CHAT;

	tgl_peer_id_t buddy_id;
	buddy_id.id = s_buddy_id;
	buddy_id.type = TGL_PEER_USER;

	tgl_peer_t* UC = tgl_peer_get(tgl_engine_get_TLS(), chat_id);
	struct tgl_chat *chat_info = &(UC->chat);
	tgl_do_del_user_from_chat(tgl_engine_get_TLS(), chat_id, buddy_id, on_buddy_removed_from_chat_response_received, chat_info);
}

void set_group_chat_profile_picture(tg_engine_data_s *tg_data, int buddy_id, const char *file_path)
{
	if (file_path) {
		tgl_peer_id_t peer_id;
		peer_id.id = buddy_id;
		peer_id.type = TGL_PEER_CHAT;

		tgl_peer_t* UC = tgl_peer_get(tgl_engine_get_TLS(), peer_id);
		struct tgl_chat *chat_info = &(UC->chat);
		tgl_do_set_chat_photo(tgl_engine_get_TLS(), chat_info->id, (char*)file_path, on_new_group_icon_loaded, chat_info);
	}
}

void on_set_username_response_received(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_user *buddy)
{
	tg_engine_data_s *tg_data = TLS->callback_data;
	char *org_username = callback_extra;
	if (success) {
		// update db
		update_buddy_into_db(USER_INFO_TABLE_NAME, buddy);
		update_buddy_into_db(BUDDY_INFO_TABLE_NAME, buddy);
		send_self_user_name_updated_response(tg_data, org_username, EINA_TRUE);
	} else {
		send_self_user_name_updated_response(tg_data, org_username, EINA_FALSE);
	}
	if (org_username) {
		free(org_username);
	}
}

void set_user_name(tg_engine_data_s *tg_data, int buddy_id, const char *username)
{
	if (username) {
		char *org_username = strdup(username);
		tgl_do_set_username(tgl_engine_get_TLS(), username, on_set_username_response_received, org_username);
	}
}

void on_profile_name_changed(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_user *buddy)
{
	tg_engine_data_s *tg_data = callback_extra;
	if (success) {
		// update db
		update_buddy_into_db(USER_INFO_TABLE_NAME, buddy);
		update_buddy_into_db(BUDDY_INFO_TABLE_NAME, buddy);
		send_self_profile_name_updated_response(tg_data, buddy->first_name, buddy->last_name, EINA_TRUE);
	} else {
		send_self_profile_name_updated_response(tg_data, "", "", EINA_FALSE);
	}
}

void update_user_display_name(tg_engine_data_s *tg_data, int buddy_id, const char *first_name, const char *last_name)
{
	if (first_name && last_name) {
		tgl_do_set_profile_name(tgl_engine_get_TLS(), first_name, last_name, on_profile_name_changed, tg_data);
	}
}


void create_new_group(tg_engine_data_s *tg_data, Eina_List* buddy_ids, const char *group_name, const char *group_icon)
{
	if (!buddy_ids || ! group_name) {
		return;
	}
	int users_num = eina_list_count(buddy_ids);
	static tgl_peer_id_t ids[1024];
	static char _group_icon[1024];
	int i;
	for (i = 0; i < users_num; i++) {
		char *buddy_id_str = (char *)eina_list_nth(buddy_ids, i);
		int buddy_id = atoi(buddy_id_str);
		ids[i].id = buddy_id;
		ids[i].type = TGL_PEER_USER;
	}

	strncpy(_group_icon, group_icon, sizeof(_group_icon));

	tgl_do_create_group_chat_ex(tgl_engine_get_TLS(), users_num, ids, group_name, on_new_group_created, (void *)_group_icon);
	tg_data->is_group_creation_requested = EINA_TRUE;

	if (tg_data->new_group_icon) {
		free(tg_data->new_group_icon);
	}

	if (group_icon && strlen(group_icon) > 0) {
		tg_data->new_group_icon = strdup(group_icon);
	} else {
		tg_data->new_group_icon = NULL;
	}

}

void add_contacts_to_user(tg_engine_data_s *tg_data, int size, Eina_List* contact_list)
{
	tg_data->contact_list_to_add = contact_list;
	contact_data_s* contact = eina_list_nth(contact_list, 0);
	if (contact) {
		char *first_name = contact->first_name;
		char *last_name = contact->last_name;
		char *phone_number = contact->phone_number;

		tg_data->current_index = 0;

		if (!first_name) {
			first_name = contact->display_name;
			if (!first_name) {
				first_name = "";
			}
		}

		if (!last_name) {
			last_name = "";
		}

		if (first_name && last_name && phone_number) {
			tgl_do_add_contact(tgl_engine_get_TLS(), phone_number, first_name, last_name, 0, on_contact_added, tg_data);
		} else {
			on_contact_added(tgl_engine_get_TLS(), tg_data, 0, 0, NULL);
		}
	}
}

void media_download_request(tg_engine_data_s *tg_data, int buddy_id, long long media_id)
{
	// get media details by mediaid
	struct tgl_media* img_details = get_media_details_from_db(media_id);

	if(!img_details) {
		send_media_download_completed_response(tg_data, -1, buddy_id, media_id, NULL);
		return;
	} else {

		if (img_details->media_type == tgl_message_media_none) {

		} else if (img_details->media_type == tgl_message_media_photo) {

			struct tgl_photo* photo_prop = (struct tgl_photo*)malloc(sizeof(struct tgl_photo));
			photo_prop->id = img_details->media_id;
			photo_prop->access_hash = img_details->access_hash;
			photo_prop->user_id = img_details->user_id;
			photo_prop->date = img_details->date;
			photo_prop->caption = img_details->caption;
			photo_prop->geo.latitude = atof(img_details->latitude);
			photo_prop->geo.longitude = atof(img_details->longitude);
			photo_prop->sizes_num = img_details->sizes;

			photo_prop->sizes = talloc(sizeof(struct tgl_photo_size) * photo_prop->sizes_num);
			int i;
			for (i = 0; i < photo_prop->sizes_num; i++) {

				if (i == 0) {
					photo_prop->sizes[i].w = img_details->photo_width1;
					photo_prop->sizes[i].h = img_details->photo_height1;
					photo_prop->sizes[i].size = img_details->photo_size1;
					if(img_details->photo_data1) {
						photo_prop->sizes[i].data = strdup(img_details->photo_data1);
					}
					if(img_details->photo_type1) {
						photo_prop->sizes[i].type = strdup(img_details->photo_type1);
					}
					photo_prop->sizes[i].loc.dc = img_details->photo_loc_dc1;
					photo_prop->sizes[i].loc.local_id = img_details->photo_loc_id1;
					photo_prop->sizes[i].loc.secret = img_details->photo_loc_sec1;
					photo_prop->sizes[i].loc.volume = img_details->photo_loc_vol1;
				} else if (i == 1) {

					photo_prop->sizes[i].w = img_details->photo_width2;
					photo_prop->sizes[i].h = img_details->photo_height2;
					photo_prop->sizes[i].size = img_details->photo_size2;
					if(img_details->photo_data2) {
						photo_prop->sizes[i].data = strdup(img_details->photo_data2);
					}
					if(img_details->photo_type2) {
						photo_prop->sizes[i].type = strdup(img_details->photo_type2);
					}
					photo_prop->sizes[i].loc.dc = img_details->photo_loc_dc2;
					photo_prop->sizes[i].loc.local_id = img_details->photo_loc_id2;
					photo_prop->sizes[i].loc.secret = img_details->photo_loc_sec2;
					photo_prop->sizes[i].loc.volume = img_details->photo_loc_vol2;

				} else if (i == 2) {

					photo_prop->sizes[i].w = img_details->photo_width3;
					photo_prop->sizes[i].h = img_details->photo_height3;
					photo_prop->sizes[i].size = img_details->photo_size3;
					if(img_details->photo_data3) {
						photo_prop->sizes[i].data = strdup(img_details->photo_data3);
					}
					if(img_details->photo_type3) {
						photo_prop->sizes[i].type = strdup(img_details->photo_type3);
					}
					photo_prop->sizes[i].loc.dc = img_details->photo_loc_dc3;
					photo_prop->sizes[i].loc.local_id = img_details->photo_loc_id3;
					photo_prop->sizes[i].loc.secret = img_details->photo_loc_sec3;
					photo_prop->sizes[i].loc.volume = img_details->photo_loc_vol3;

				} else if (i == 3) {

					photo_prop->sizes[i].w = img_details->photo_width4;
					photo_prop->sizes[i].h = img_details->photo_height4;
					photo_prop->sizes[i].size = img_details->photo_size4;
					if(img_details->photo_data4) {
						photo_prop->sizes[i].data = strdup(img_details->photo_data4);
					}
					if(img_details->photo_type4) {
						photo_prop->sizes[i].type = strdup(img_details->photo_type4);
					}
					photo_prop->sizes[i].loc.dc = img_details->photo_loc_dc4;
					photo_prop->sizes[i].loc.local_id = img_details->photo_loc_id4;
					photo_prop->sizes[i].loc.secret = img_details->photo_loc_sec4;
					photo_prop->sizes[i].loc.volume = img_details->photo_loc_vol4;

				} else {

				}
			}
			photo_prop->to_peer_id = buddy_id;
			tgl_do_load_photo(s_info.TLS, photo_prop ,&on_image_download_completed, photo_prop);

		} else if (img_details->media_type == tgl_message_media_document) {
			struct tgl_document* doc_prop = (struct tgl_document*)malloc(sizeof(struct tgl_document));
			doc_prop->id = img_details->media_id;;
			doc_prop->access_hash = img_details->access_hash;
			doc_prop->user_id = img_details->user_id;
			doc_prop->date = img_details->date;
			doc_prop->size = img_details->sizes;
			doc_prop->mime_type = NULL;
			doc_prop->dc_id = img_details->doc_dc;
			doc_prop->to_peer_id = buddy_id;

			if (img_details->caption) {
				doc_prop->caption = strdup(img_details->caption);
			} else {
				doc_prop->caption = NULL;
			}


			if (!(img_details->mime_type) || strlen(img_details->mime_type) <= 0) {

				if (img_details->doc_type && strlen(img_details->doc_type) > 0) {
					if (strstr(img_details->doc_type, "video") != NULL) {
						doc_prop->mime_type = strdup("video/mp4");
					} else if (strstr(img_details->doc_type, "audio") != NULL) {
						doc_prop->mime_type = strdup("audio/wav");
					}
				}
			} else {
				doc_prop->mime_type = img_details->mime_type;
			}

			if (strstr(img_details->doc_type, "video") != NULL) {
				doc_prop->flags =  FLAG_DOCUMENT_VIDEO;
			} else if (strstr(img_details->doc_type, "audio") != NULL) {
				doc_prop->flags =  FLAG_DOCUMENT_AUDIO;
			}

			tgl_do_load_document(s_info.TLS, doc_prop ,on_document_download_completed, doc_prop);


		} else {

		}

		// delete image details

		if (img_details->caption) {
			free(img_details->caption);
		}
		if (img_details->longitude) {
			free(img_details->longitude);
		}
		if (img_details->latitude) {
			free(img_details->latitude);
		}
		if (img_details->phone_no) {
			free(img_details->phone_no);
		}
		if (img_details->first_name) {
			free(img_details->first_name);
		}
		if (img_details->last_name) {
			free(img_details->last_name);
		}
		if (img_details->file_path) {
			free(img_details->file_path);
		}
		if (img_details->photo_type1) {
			free(img_details->photo_type1);
		}
		if (img_details->photo_data1) {
			free(img_details->photo_data1);
		}
		if (img_details->photo_type2) {
			free(img_details->photo_type2);
		}
		if (img_details->photo_data2) {
			free(img_details->photo_data2);
		}
		if (img_details->photo_type3) {
			free(img_details->photo_type3);
		}
		if (img_details->photo_data3) {
			free(img_details->photo_data3);
		}
		if (img_details->photo_type4) {
			free(img_details->photo_type4);
		}
		if (img_details->photo_data4) {
			free(img_details->photo_data4);
		}
		if (img_details->mime_type) {
			free(img_details->mime_type);
		}
		if (img_details->doc_type) {
			free(img_details->doc_type);
		}
		if (img_details->doc_thumb_path) {
			free(img_details->doc_thumb_path);
		}

	}
}

void on_mark_read_callback(struct tgl_state *TLS, void *callback_extra, int success)
{
	// message read sent successfully. update to UI if needed.
}

void send_do_mark_read_messages(int buddy_id, int type_of_chat)
{
	tgl_peer_id_t chat_id;
	chat_id.id = buddy_id;
	chat_id.type = type_of_chat;

	tgl_do_mark_read(s_info.TLS, chat_id, &on_mark_read_callback , (void*)(&chat_id));
}


void on_user_block_response(struct tgl_state *TLS, void *callback_extra, int success)
{
	int buddy_id = (int)callback_extra;
	tg_engine_data_s *tg_data = TLS->callback_data;
	if (success) {
		// update database
		int blocked = 1;
		update_buddy_block_db(BUDDY_INFO_TABLE_NAME, buddy_id, blocked);
		send_buddy_blocked_response(tg_data, buddy_id, EINA_TRUE);
	} else {
		send_buddy_blocked_response(tg_data, buddy_id, EINA_FALSE);
	}
}

void on_user_unblock_response(struct tgl_state *TLS, void *callback_extra, int success)
{
	int buddy_id = (int)callback_extra;
	tg_engine_data_s *tg_data = TLS->callback_data;
	if (success) {
		int blocked = 0;
		update_buddy_block_db(BUDDY_INFO_TABLE_NAME, buddy_id, blocked);
		send_buddy_unblocked_response(tg_data, buddy_id, EINA_TRUE);
	} else {
		send_buddy_unblocked_response(tg_data, buddy_id, EINA_FALSE);
	}
}

void on_user_delete_response(struct tgl_state *TLS, void *callback_extra, int success)
{
	int buddy_id = (int)callback_extra;
	tg_engine_data_s *tg_data = TLS->callback_data;
	if (success) {
		// update database
		// delete from peer table
		// delete from buddy table
		// delete chat items
#if 0
		//delete_chat_from_db(buddy_id);
		//delete_buddy_from_db(buddy_id);
		//char* msg_table = get_table_name_from_number(buddy_id);
		//drop_table(msg_table);
		//free(msg_table);
#endif
		int deleted = 1;
		update_buddy_delete_db(BUDDY_INFO_TABLE_NAME, buddy_id, deleted);
		send_buddy_deleted_response(tg_data, buddy_id, EINA_TRUE);
	} else {
		send_buddy_deleted_response(tg_data, buddy_id, EINA_FALSE);
	}
}


void on_buddy_readded(struct tgl_state *TLS,void *callback_extra, int success, int size, struct tgl_user *users[])
{
	int buddy_id = (int)callback_extra;
	tg_engine_data_s *tg_data = TLS->callback_data;
	if (success) {
		int deleted = 0;
		update_buddy_delete_db(BUDDY_INFO_TABLE_NAME, buddy_id, deleted);
		send_buddy_readded_response(tg_data, buddy_id, EINA_TRUE);
	} else {
		send_buddy_readded_response(tg_data, buddy_id, EINA_FALSE);
	}
}

void do_add_buddy(int buddy_id, char *first_name, char *last_name, char *phone_num)
{
	if (!first_name) {
		first_name = "";
	}
	if (!last_name) {
		last_name = "";
	}
	if (!phone_num) {
		phone_num = "";
	}

	if (first_name && last_name && phone_num) {
		tgl_do_add_contact(s_info.TLS, phone_num, first_name, last_name, 0, on_buddy_readded, (void*)(buddy_id));
	}
}


void do_delete_buddy(int buddy_id)
{
	tgl_peer_id_t peer_id;
	peer_id.id = buddy_id;
	peer_id.type = TGL_PEER_USER;
	tgl_do_del_contact(s_info.TLS, peer_id, &on_user_delete_response , (void*)(buddy_id));
}

void do_block_buddy(int buddy_id)
{
	tgl_peer_id_t peer_id;
	peer_id.id = buddy_id;
	peer_id.type = TGL_PEER_USER;
	tgl_do_block_user(s_info.TLS, peer_id, &on_user_block_response , (void*)(buddy_id));
}

void do_unblock_buddy(int buddy_id)
{
	tgl_peer_id_t peer_id;
	peer_id.id = buddy_id;
	peer_id.type = TGL_PEER_USER;
	tgl_do_unblock_user(s_info.TLS, peer_id, &on_user_unblock_response , (void*)(buddy_id));
}

void on_selected_group_chats_delete_reponse(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *M)
{
	Eina_List *sel_grp_chats = callback_extra;
	tg_engine_data_s *tg_data = TLS->callback_data;
	int chat_id = eina_list_nth(sel_grp_chats, tg_data->current_group_chat_index);

	if (success) {
		// update database
		// delete from peer table
		delete_chat_from_db(chat_id);
		char* msg_table = get_table_name_from_number(chat_id);
		drop_table(msg_table);
		free(msg_table);
	} else {

	}

	tg_data->current_group_chat_index = tg_data->current_group_chat_index + 1;

	if (tg_data->current_group_chat_index < eina_list_count(sel_grp_chats)) {
		int group_chat_id = (int)eina_list_nth(sel_grp_chats, tg_data->current_group_chat_index);

		tgl_peer_id_t chat_id;
		chat_id.id = group_chat_id;
		chat_id.type = TGL_PEER_CHAT;

		tgl_peer_id_t self_id = tg_data->id;

		tgl_do_del_user_from_chat(s_info.TLS, chat_id, self_id, on_selected_group_chats_delete_reponse, (void*)(sel_grp_chats));
	} else {
		send_selected_group_chats_deleted_response(tg_data);
	}
}

void delete_selected_group_chat(tg_engine_data_s *tg_data, Eina_List *sel_grp_chats)
{
	if (sel_grp_chats && eina_list_count(sel_grp_chats) > 0) {

		tg_data->current_group_chat_index = 0;
		int group_chat_id = (int)eina_list_nth(sel_grp_chats, tg_data->current_group_chat_index);

		tgl_peer_id_t chat_id;
		chat_id.id = group_chat_id;
		chat_id.type = TGL_PEER_CHAT;

		tgl_peer_id_t self_id = tg_data->id;

		tgl_do_del_user_from_chat(s_info.TLS, chat_id, self_id, on_selected_group_chats_delete_reponse, (void*)(sel_grp_chats));
	}
}

void on_group_chat_delete_reponse(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *M)
{
	int chat_id = (int)callback_extra;
	tg_engine_data_s *tg_data = TLS->callback_data;
	if (success) {
		// update database
		// delete from peer table
		delete_chat_from_db(chat_id);
		char* msg_table = get_table_name_from_number(chat_id);
		drop_table(msg_table);
		free(msg_table);
		send_group_chat_deleted_response(tg_data, chat_id, EINA_TRUE);
	} else {
		send_group_chat_deleted_response(tg_data, chat_id, EINA_FALSE);
	}
}

void leave_group_chat(tg_engine_data_s *tg_data, int group_chat_id)
{
	tgl_peer_id_t chat_id;
	chat_id.id = group_chat_id;
	chat_id.type = TGL_PEER_CHAT;

	tgl_peer_id_t self_id = tg_data->id;

	tgl_do_del_user_from_chat(s_info.TLS, chat_id, self_id, on_group_chat_delete_reponse, (void*)(group_chat_id));
}

#if 0
void on_new_msg_requested_chat_info_received(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_chat *chat_info)
{
	tg_engine_data_s *tg_data;

	struct tgl_message *msg = callback_extra;

	char *msg_table;

	if (!chat_info) {
		return;
	}
	if (!chat_info->user_list) {
		tgl_do_get_chat_info(TLS, chat_info->id, 0, &on_requested_chat_info_received, callback_extra);
		return;
	}

	tg_data = TLS->callback_data;

	msg_table = get_table_name_from_number(chat_info->id.id);

	create_buddy_msg_table(msg_table);

	insert_chat_info_to_db(chat_info, NULL);
	struct tgl_photo *pic = &(chat_info->photo);
	if(pic) {
		tgl_do_load_photo(TLS, pic ,&on_chat_pic_loaded,chat_info);
	}

	tgl_do_send_message(s_info.TLS, msg->to_id, msg->message, strlen(msg->message), &on_message_sent_to_buddy, (void*)(msg));

	char *type_of_change = strdup("add_user");
	tgl_do_get_chat_info(s_info.TLS, msg->to_id, 0, &on_group_chat_info_updated, type_of_change);

	free(msg_table);
}
#endif
void send_message_to_buddy(int buddy_id, int message_id, int msg_type, char *msg_data, int type_of_chat)
{
	// get type of chat from buddy_id.
	char *msg_table = get_table_name_from_number(buddy_id);
	struct tgl_message* msg = get_message_from_message_table(message_id, msg_table);

	if (msg) {
		if (type_of_chat == TGL_PEER_USER) {
			msg->from_id.type = TGL_PEER_USER;
			msg->to_id.type = TGL_PEER_USER;
			tgl_do_send_message(s_info.TLS, msg->to_id, msg->message, strlen(msg->message), &on_message_sent_to_buddy, (void*)(msg));
		} else if (type_of_chat == TGL_PEER_CHAT) {
			msg->from_id.type = TGL_PEER_CHAT;
			msg->to_id.type = TGL_PEER_CHAT;
#if 0
			Eina_Bool is_present_in_chat_db = is_user_present_chat_table(msg->to_id.id);
			if (!is_present_in_chat_db) {
				//sandeep
				tgl_do_get_chat_info(s_info.TLS, msg->to_id, 0, &on_new_msg_requested_chat_info_received, msg);
				return;
			}
#endif
			tgl_do_send_message(s_info.TLS, msg->to_id, msg->message, strlen(msg->message), &on_message_sent_to_buddy, (void*)(msg));
		} else if (type_of_chat == TGL_PEER_ENCR_CHAT) {

		} else {

		}
	}
	free(msg_table);
}

void send_media_to_buddy(int buddy_id, int message_id, int media_id, int msg_type, char *file_path, int type_of_chat)
{
	char *msg_table = get_table_name_from_number(buddy_id);
	struct tgl_message* msg = get_message_from_message_table(message_id, msg_table);

	if (msg) {
		if (type_of_chat == TGL_PEER_USER) {

			msg->from_id.type = TGL_PEER_USER;
			msg->to_id.type = TGL_PEER_USER;

			if (msg->media.type == tgl_message_media_photo) {
				tgl_do_send_document(s_info.TLS, -1, msg->to_id, file_path, &on_message_sent_to_buddy, (void*) (msg));
			} else if (msg->media.type == tgl_message_media_document) {
				char *extn = strrchr(file_path, '.');
				if (extn) {
					extn = replace(extn, '.', "");
				}
				char *mime_type = NULL;;
				if (extn) {
					mime_type_get_mime_type(extn, &mime_type);
				}

				if (strstr(mime_type, "video") != NULL) {

					char* thumb_path = get_video_thumb_path_from_db(media_id);
					tgl_do_send_video(s_info.TLS, -2, msg->to_id, file_path, thumb_path, &on_message_sent_to_buddy, (void*) (msg));
					if (thumb_path) {
						free(thumb_path);
						thumb_path = NULL;
					}
				} else if (strstr(mime_type, "audio") != NULL) {
					tgl_do_send_audio(s_info.TLS, msg->to_id, file_path, &on_message_sent_to_buddy, (void*) (msg));
				} else {

				}
			} else if (msg->media.type == tgl_message_media_geo) {
				char *latitude = NULL;
				char *longitude = NULL;
				get_geo_location_from_db(media_id, &latitude, &longitude);
				if (latitude && longitude) {
					tgl_do_send_location(s_info.TLS, msg->to_id, strtod(latitude, NULL), strtod(longitude, NULL), &on_message_sent_to_buddy, (void*) (msg));
				}
			} else if (msg->media.type == tgl_message_media_contact) {
				char *first_name = NULL;
				char *last_name = NULL;
				char *phone_num = NULL;
				get_contact_details_from_db(media_id, &first_name, &last_name, &phone_num);
				if (first_name && last_name && phone_num) {
					tgl_do_send_contact(s_info.TLS, msg->to_id, first_name, strlen(first_name), last_name, strlen(last_name), phone_num, strlen(phone_num), &on_message_sent_to_buddy, (void*) (msg));
				}
			}

		} else if (type_of_chat == TGL_PEER_CHAT) {
			msg->from_id.type = TGL_PEER_CHAT;
			msg->to_id.type = TGL_PEER_CHAT;

			if (msg->media.type == tgl_message_media_photo) {
				tgl_do_send_document(s_info.TLS, -1, msg->to_id, file_path, &on_message_sent_to_buddy, (void*) (msg));
			} else if (msg->media.type == tgl_message_media_document) {


				char *extn = strrchr(file_path, '.');
				if (extn) {
					extn = replace(extn, '.', "");
				}
				char *mime_type = NULL;;
				if (extn) {
					mime_type_get_mime_type(extn, &mime_type);
				}

				if (strstr(mime_type, "video") != NULL) {

					char* thumb_path = get_video_thumb_path_from_db(media_id);
					tgl_do_send_video(s_info.TLS, -2, msg->to_id, file_path, thumb_path, &on_message_sent_to_buddy, (void*) (msg));
					if (thumb_path) {
						free(thumb_path);
						thumb_path = NULL;
					}
				} else if (strstr(mime_type, "audio") != NULL) {
					tgl_do_send_audio(s_info.TLS, msg->to_id, file_path, &on_message_sent_to_buddy, (void*) (msg));
				} else {

				}
			} else if (msg->media.type == tgl_message_media_geo) {
				char *latitude = NULL;
				char *longitude = NULL;
				get_geo_location_from_db(media_id, &latitude, &longitude);
				if (latitude && longitude) {
					tgl_do_send_location(s_info.TLS, msg->to_id, strtod(latitude, NULL), strtod(longitude, NULL), &on_message_sent_to_buddy, (void*) (msg));
				}
			}


		} else if (type_of_chat == TGL_PEER_ENCR_CHAT) {

		} else {

		}

	}
	free(msg_table);

}

void check_type_sizes(void)
{
	if (sizeof(int) != 4u) {
		logprintf("sizeof(int) isn't equal 4.\n");
		exit(1);
	}
	if (sizeof(char) != 1u) {
		logprintf("sizeof(char) isn't equal 1.\n");
		exit(1);
	}
}

int str_empty(char *str)
{
	return((str == NULL) ||(strlen(str) < 1));
}

void parse_config(void)
{
	if (!s_info.disable_output) {
		//printf("libconfig not enabled\n");
	}

	char *rsa_path = ui_utils_get_resource(DEFAULT_RSA_FILE_NAME);
	tasprintf(&s_info.rsa_file_name, "%s", rsa_path);
	tasprintf(&s_info.config_full_path, "%s%s", DEFAULT_TELEGRAM_PATH, CONFIG_DIRECTORY);
	struct stat st = { 0 };
	if (stat(s_info.config_full_path, &st) == -1) {
		mkdir(s_info.config_full_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	if (remove(s_info.rsa_file_name) == 0) {
		//printf("File successfully deleted\n");
	}

	tasprintf(&s_info.downloads_directory, "%s%s/%s", DEFAULT_TELEGRAM_PATH, CONFIG_DIRECTORY, DOWNLOADS_DIRECTORY);

	if (s_info.binlog_enabled) {
		tasprintf(&s_info.binlog_file_name, "%s%s/%s", DEFAULT_TELEGRAM_PATH, CONFIG_DIRECTORY, BINLOG_FILE);
		tgl_set_binlog_mode(s_info.TLS, 1);
		tgl_set_binlog_path(s_info.TLS, s_info.binlog_file_name);
	} else {
		tgl_set_binlog_mode(s_info.TLS, 0);
		//tgl_set_auth_file_path(auth_file_name;
		tasprintf(&s_info.auth_file_name, "%s%s/%s", DEFAULT_TELEGRAM_PATH, CONFIG_DIRECTORY, AUTH_KEY_FILE);
		tasprintf(&s_info.state_file_name, "%s%s/%s", DEFAULT_TELEGRAM_PATH, CONFIG_DIRECTORY, STATE_FILE);
		tasprintf(&s_info.secret_chat_file_name, "%s%s/%s", DEFAULT_TELEGRAM_PATH, CONFIG_DIRECTORY, SECRET_CHAT_FILE);
	}
	tgl_set_download_directory(s_info.TLS, s_info.downloads_directory);
	if (!mkdir(s_info.downloads_directory, CONFIG_DIRECTORY_MODE)) {
		if (!s_info.disable_output) {
			//printf("[%s] created\n", downloads_directory);
		}
	}
}

void running_for_first_time(void)
{
	check_type_sizes();
	if (!str_empty(s_info.config_filename)) {
		return; // Do not create custom config file
	}

	if (str_empty(s_info.config_directory)) {
		s_info.config_directory = strdup(DEFAULT_TELEGRAM_PATH); // specific path for tizen application.
	}

	struct stat st = {0};
	if (stat(s_info.config_directory, &st) == -1) {
		mkdir(s_info.config_directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	tasprintf(&s_info.config_filename, "%s%s", s_info.config_directory, CONFIG_FILE);

	int config_file_fd;
	// see if config file is there
	if (access(s_info.config_filename, R_OK) != 0) {
		// config file missing, so touch it
		config_file_fd = open(s_info.config_filename, O_CREAT | O_RDWR, 0600);
		if (config_file_fd == -1)  {
			perror("open[config_file]");
			//printf("I: config_file=[%s]\n", config_filename);
			exit(EXIT_FAILURE);
		}
		if (write(config_file_fd, DEFAULT_CONFIG_CONTENTS, strlen(DEFAULT_CONFIG_CONTENTS)) <= 0) {
			perror("write[config_file]");
			exit(EXIT_FAILURE);
		}
		close(config_file_fd);
	}
}

void init_tl_engine(void *cbdata)
{
	s_info.TLS = tgl_state_alloc();
	if (!s_info.TLS) {
		/**
		 * @todo
		 * Unable to allocate the TGL State info.
		 */
		return;
	}

	running_for_first_time();

	parse_config();

	tgl_set_rsa_key(s_info.TLS, s_info.rsa_file_name);
	tgl_set_callback(s_info.TLS, &upd_cb, cbdata);
	tgl_set_net_methods(s_info.TLS, &tgl_conn_methods);
	tgl_set_timer_methods(s_info.TLS, &tgl_libevent_timers);
	assert(s_info.TLS->timer_methods);
	tgl_set_download_directory(s_info.TLS, tgl_engine_get_downloads_directory());
	tgl_register_app_id(s_info.TLS, TELEGRAM_CLI_APP_ID, TELEGRAM_CLI_APP_HASH);
	tgl_set_app_version(s_info.TLS, "Telegram-cli " TELEGRAM_CLI_VERSION);
	if (s_info.ipv6_enabled) {
		tgl_enable_ipv6(s_info.TLS);
	}
	tgl_init(s_info.TLS);

	if (s_info.binlog_enabled) {
		double t = tglt_get_double_time();
		if (s_info.verbosity >= E_DEBUG) {
			logprintf("replay log start\n");
		}
		tgl_replay_log(s_info.TLS);
		if (s_info.verbosity >= E_DEBUG) {
			logprintf("replay log end in %lf seconds\n", tglt_get_double_time() - t);
		}
		tgl_reopen_binlog_for_writing(s_info.TLS);
	} else {
		read_auth_file();
		read_state_file();
		read_secret_chat_file();
	}
}

void tgl_engine_destroy_TLS(void)
{
	if (!s_info.TLS) {
		return;
	}

	tgl_state_free(tgl_engine_get_TLS());
	s_info.TLS = NULL;
}

struct tgl_state *tgl_engine_get_TLS(void)
{
	return s_info.TLS;
}
