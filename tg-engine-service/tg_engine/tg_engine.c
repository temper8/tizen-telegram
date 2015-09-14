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
		if (buddy) {
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

void tg_get_string(struct tgl_state *TLS, const char *prompt, int flags, void(*callback)(struct tgl_state *TLS, char *string, void *arg), void *arg)
{
	tg_engine_data_s *tg_data;

	tg_data = TLS->callback_data;

	tg_data->get_string = callback;
	tg_data->callback_arg = arg;
	if (strcmp (prompt, "phone number:") == 0) {
		tg_data->is_first_time_registration = EINA_FALSE;
		tg_data->tg_state = TG_ENGINE_STATE_REGISTRATION;
		if (tg_data && tg_data->phone_number) {
			tg_data->get_string(TLS, tg_data->phone_number, tg_data->callback_arg);
		}
	} else if (strcmp (prompt, "code('call' for phone call):") == 0) {

		tg_data->tg_state = TG_ENGINE_STATE_CODE_REQUEST;
		send_registration_response(tg_data, EINA_TRUE);

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
			send_name_registration_response();
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
	write_auth_file();
	int offline_mode = 0;
	tgl_peer_id_t t_id;
	t_id.id = TLS->our_id;
	t_id.type = TGL_PEER_USER;
	tgl_do_get_user_info(TLS, t_id, offline_mode, &on_user_info_loaded, NULL);
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
		insert_buddy_into_db(BUDDY_INFO_TABLE_NAME, buddy);

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

	if (flags == TGL_GROUP_CHAT_CREATED) {
		insert_chat_info_to_db(chat_info, NULL);
		tgl_peer_t* UC = tgl_peer_get(TLS, chat_info->id);
		insert_peer_into_database(UC, 0, 0);
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
		insert_buddy_into_db(BUDDY_INFO_TABLE_NAME, buddy);

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
				if (M->action.type == tgl_message_action_chat_create) {

					char* msg_table = get_table_name_from_number(M->to_id.id);
					create_buddy_msg_table(msg_table);
					free(msg_table);

					tgl_peer_t* UC = tgl_peer_get(TLS, M->from_id);

					int msg_len = strlen(UC->user.first_name) + strlen(" created the group") + 1;
					char* creator_name = (char*)malloc(msg_len);
					strcpy(creator_name, UC->user.first_name);
					strcat(creator_name, " created the group");
					M->message = creator_name;
					M->message_len = msg_len;
					M->unread = 1;
					M->date = time(NULL);
					insert_buddy_msg_to_db(M);
					free(creator_name);

					tgl_peer_t* chat_UC = tgl_peer_get(TLS, M->to_id);
					chat_UC->chat.date = M->date;
					insert_chat_info_to_db(&(chat_UC->chat), NULL);
					chat_UC->last = M;
					insert_peer_into_database(chat_UC, 0, 0);



					//send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
					tg_engine_data_s *tg_data = TLS->callback_data;
					send_new_group_added_response(tg_data, M->to_id.id);

				} else if (M->action.type == tgl_message_action_chat_edit_title) {

				} else if (M->action.type == tgl_message_action_chat_edit_photo) {

					char* msg_table = get_table_name_from_number(M->to_id.id);
					create_buddy_msg_table(msg_table);
					free(msg_table);

					tgl_peer_t* UC = tgl_peer_get(TLS, M->from_id);
					int msg_len = strlen(UC->user.first_name) + strlen(" changed profile photo") + 1;
					char* creator_name = (char*)malloc(msg_len);
					strcpy(creator_name, UC->user.first_name);
					strcat(creator_name, " changed profile photo");
					M->message = creator_name;
					M->message_len = msg_len;
					M->unread = 1;
					insert_buddy_msg_to_db(M);
					free(creator_name);
					send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
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

				insert_buddy_msg_to_db(M);
				if(M->media.type != tgl_message_media_none) {
					insert_media_info_to_db(M, "");
				}
				// inform to application
				send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
			}

		} else if (tgl_get_peer_type(M->to_id) == TGL_PEER_ENCR_CHAT) {

		} else {

			if ((tgl_get_peer_type (M->from_id) == TGL_PEER_USER) && (tgl_get_peer_id (M->from_id) == TLS->our_id)) {

			} else {
				if (M->media.type != tgl_message_media_none) {
					M->message = NULL;
					M->message_len = 0;
				}

				insert_buddy_msg_to_db(M);
				if(M->media.type != tgl_message_media_none) {
					insert_media_info_to_db(M, "");
				}
				// inform to application
				send_message_received_response(TLS->callback_data, M->from_id.id, M->to_id.id, M->id, tgl_get_peer_type(M->to_id));
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
			insert_buddy_into_db(USER_INFO_TABLE_NAME, U);
		} else if (U->flags & FLAG_USER_CONTACT) {
			insert_buddy_into_db(BUDDY_INFO_TABLE_NAME, U);
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

	tg_data = TLS->callback_data;

	msg_table = get_table_name_from_number(chat_info->id.id);

	create_buddy_msg_table(msg_table);

	insert_chat_info_to_db(chat_info, NULL);
	struct tgl_photo *pic = &(chat_info->photo);
	if(pic) {
		tgl_do_load_photo(TLS, pic ,&on_chat_pic_loaded,chat_info);
	}
	free(msg_table);
#if 0
	if (tg_data->is_group_creation_requested) {
		tgl_peer_t* UC;
		UC = tgl_peer_get(TLS, chat_info->id);
		// insert into peer table
		insert_peer_into_database(UC, 0, 0);
		tg_data->is_group_creation_requested = EINA_FALSE;

		/*************** insert service message ********************/

		char* msg_data = "new group created.";
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

		/***********************************************************/
		send_new_group_added_response(tg_data, chat_info->id.id);

		if (tg_data->new_group_icon) {
			tgl_do_set_chat_photo(TLS, chat_info->id, tg_data->new_group_icon, on_new_group_icon_loaded, chat_info);
		}
	}
#endif
}

void on_buddy_info_loaded(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_user *U)
{
	if(!U) {
		return;
	}
	//insert_buddy_into_db(BUDDY_INFO_TABLE_NAME, U);
	struct tgl_photo* pic = &(U->photo);
	if(pic) {
		tgl_do_load_photo(TLS, pic ,&on_buddy_pic_loaded,U);
	}
}

void on_contacts_received(struct tgl_state *TLS, void *callback_extra, int success, int size, struct tgl_user *contacts[])
{
	for (int i = size - 1; i >= 0; i--) {
		struct tgl_user *buddy = contacts[i];
		char* msg_table = get_table_name_from_number(buddy->id.id);
		create_buddy_msg_table(msg_table);
		free(msg_table);

		tgl_do_get_user_info(TLS, buddy->id, 0, &on_buddy_info_loaded, NULL);
		insert_buddy_into_db(BUDDY_INFO_TABLE_NAME, buddy);
	}

	// inform client that contact loading is done.
	//send_contacts_load_done_response(EINA_TRUE);
}

void on_contacts_and_chats_loaded(struct tgl_state *TLS, void *callback_extra, int success, int size, tgl_peer_id_t peers[], int last_msg_id[], int unread_count[])
{
	for (int i = size - 1; i >= 0; i--) {
		tgl_peer_t* UC;
		UC = tgl_peer_get(TLS, peers[i]);
		// insert into peer table
		insert_peer_into_database(UC, last_msg_id[i], unread_count[i]);
		//struct tgl_user* buddy;
		struct tgl_chat* chat_info;
		switch (tgl_get_peer_type(peers[i])) {
			case TGL_PEER_USER:
#if 0
				buddy = &(UC->user);
				if (buddy) {
					char* msg_table = get_table_name_from_number(buddy->id.id);
					create_buddy_msg_table(msg_table);
					free(msg_table);
					insert_buddy_into_db(BUDDY_INFO_TABLE_NAME, buddy);
					tgl_do_get_user_info(TLS, buddy->id, 0, &on_buddy_info_loaded, NULL);
				}
#endif
				break;
			case TGL_PEER_CHAT:
				chat_info = &(UC->chat);
				tgl_do_get_chat_info(TLS, chat_info->id, 0, &on_chat_info_received, NULL);
				break;
			case TGL_PEER_ENCR_CHAT:
				break;
		}
	}
	send_contacts_and_chats_load_done_response(TLS->callback_data, EINA_TRUE);
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

	insert_buddy_into_db(USER_INFO_TABLE_NAME, buddy);

	if (tg_data->is_first_time_registration) {
		// send contact list to add friends.
		send_add_contacts_request();
	} else {
		tgl_do_update_contact_list(TLS, on_contacts_received, NULL);
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
			if (message->media.type == tgl_message_media_photo) {
				update_sent_media_info_in_db(message, (long long)org_msg->id);
			}
			send_message_sent_to_buddy_response(tg_data, message->to_id.id, message->id, tb_name, EINA_TRUE, tgl_get_peer_type(message->to_id));
			free(tb_name);
		}
	} else {
		if (org_msg) {
			org_msg->msg_state = TG_MESSAGE_STATE_FAILED;
			char* tb_name = get_table_name_from_number(org_msg->to_id.id);
			update_msg_into_db(org_msg, tb_name, org_msg->id);
			if (org_msg->media.type == tgl_message_media_photo) {
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
			tgl_do_add_contact(TLS, phone_number, first_name, last_name, 0, on_contact_added, data);
		}

	} else {
		tgl_do_get_dialog_list(TLS, on_contacts_and_chats_loaded, NULL);
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
				free(msg_table);

				tgl_peer_t* UC = tgl_peer_get(TLS, M->from_id);
				int msg_len = strlen(UC->user.first_name) + strlen(" changed profile photo") + 1;
				char* creator_name = (char*)malloc(msg_len);
				strcpy(creator_name, UC->user.first_name);
				strcat(creator_name, " changed profile photo");
				M->message = creator_name;
				M->message_len = msg_len;
				M->unread = 1;
				insert_buddy_msg_to_db(M);
				free(creator_name);

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
				free(msg_table);

				tgl_peer_t* UC = tgl_peer_get(TLS, M->from_id);
				int msg_len = strlen(UC->user.first_name) + strlen(" created the group") + 1;
				char* creator_name = (char*)malloc(msg_len);
				strcpy(creator_name, UC->user.first_name);
				strcat(creator_name, " created the group");
				M->message = creator_name;
				M->message_len = msg_len;
				M->unread = 1;
				M->date = time(NULL);
				insert_buddy_msg_to_db(M);
				free(creator_name);

				tgl_peer_t* chat_UC = tgl_peer_get(TLS, M->to_id);
				chat_UC->chat.date = M->date;
				insert_chat_info_to_db(&(chat_UC->chat), NULL);
				chat_UC->last = M;
				insert_peer_into_database(chat_UC, 0, 0);


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
		tgl_do_add_contact(tgl_engine_get_TLS(), phone_number, first_name, last_name, 0, on_contact_added, tg_data);
	}
}

void media_download_request(tg_engine_data_s *tg_data, int buddy_id, long long media_id)
{
#if 1
	// get media details by mediaid
	Eina_List* img_details = get_image_details_from_db(media_id);

	if(!img_details) {
		send_media_download_completed_response(tg_data, -1, buddy_id, media_id, NULL);
		return;
	} else {

		char *media_id_str = 0;
		int media_type = 0;
		char *access_hash_str = 0;
		int user_id = 0;
		int date = 0;
		char *caption = 0;
		char *longitude = 0;
		char *latitude = 0;
		int sizes = 0;
		char *phone_no = 0;
		char *first_name = 0;
		char *last_name = 0;
		char *file_path = 0;

		char *photo_type1 = 0;
		int photo_loc_dc1 = 0;
		char *photo_loc_vol_str1 = 0;
		int photo_loc_id1 = 0;
		char *photo_loc_sec_str1 = 0;
		int photo_width1 = 0;
		int photo_height1 = 0;
		int photo_size1 = 0;
		char *photo_data1 = 0;

		char *photo_type2 = 0;
		int photo_loc_dc2 = 0;
		char *photo_loc_vol_str2 = 0;
		int photo_loc_id2 = 0;
		char *photo_loc_sec_str2 = 0;
		int photo_width2 = 0;
		int photo_height2 = 0;
		int photo_size2 = 0;
		char *photo_data2 = 0;

		char *photo_type3 = 0;
		int photo_loc_dc3 = 0;
		char *photo_loc_vol_str3 = 0;
		int photo_loc_id3 = 0;
		char *photo_loc_sec_str3 = 0;
		int photo_width3 = 0;
		int photo_height3 = 0;
		int photo_size3 = 0;
		char *photo_data3 = 0;

		char *photo_type4 = 0;
		int photo_loc_dc4 = 0;
		char *photo_loc_vol_str4 = 0;
		int photo_loc_id4 = 0;
		char *photo_loc_sec_str4 = 0;
		int photo_width4 = 0;
		int photo_height4 = 0;
		int photo_size4 = 0;
		char *photo_data4 = 0;


		int row_count = eina_list_count(img_details);

		for (int i = 0 ; i < row_count ; i++) {
			Eina_List* row_vals = eina_list_nth(img_details, i);

			char *temp_media_id = (char *)eina_list_nth(row_vals, 0);

			if(temp_media_id) {
				media_id_str = strdup(temp_media_id);
				free(temp_media_id);
			}

			int* temp_media_type = (int*)eina_list_nth(row_vals, 1);

			if(temp_media_type) {
				media_type = *temp_media_type;
				free(temp_media_type);
			}

			char *temp_access_hash = (char *)eina_list_nth(row_vals, 2);

			if(temp_access_hash) {
				access_hash_str = strdup(temp_access_hash);
				free(temp_access_hash);
			}

			int* temp_user_id = (int*)eina_list_nth(row_vals, 3);

			if(temp_user_id) {
				user_id = *temp_user_id;
				free(temp_user_id);
			}

			int* temp_date = (int*)eina_list_nth(row_vals, 4);

			if(temp_date) {
				date = *temp_date;
				free(temp_date);
			}

			char *temp_caption = (char *)eina_list_nth(row_vals, 5);

			if(temp_caption) {
				caption = strdup(temp_caption);
				free(temp_caption);
			}

			char *temp_longitude = (char *)eina_list_nth(row_vals, 6);

			if(temp_longitude) {
				longitude = strdup(temp_longitude);
				free(temp_longitude);
			}

			char *temp_latitude = (char *)eina_list_nth(row_vals, 7);

			if(temp_latitude) {
				latitude = strdup(temp_latitude);
				free(temp_latitude);
			}

			int* temp_sizes = (int*)eina_list_nth(row_vals, 8);

			if(temp_sizes) {
				sizes = *temp_sizes;
				free(temp_sizes);
			}

			/***************************************************************/

			char *temp_photo_type1 = (char *)eina_list_nth(row_vals, 9);
			if (temp_photo_type1 && strlen(temp_photo_type1) > 0) {
				photo_type1 =strdup(temp_photo_type1);
				free(temp_photo_type1);
			}


			int* temp_photo_loc_dc1 = (int*)eina_list_nth(row_vals, 10);
			if (temp_photo_loc_dc1) {
				photo_loc_dc1 = *temp_photo_loc_dc1;
				free(temp_photo_loc_dc1);
			}


			char *temp_photo_loc_vol1 = (char *)eina_list_nth(row_vals, 11);
			if(temp_photo_loc_vol1 && strlen(temp_photo_loc_vol1) > 0) {
				photo_loc_vol_str1 = strdup(temp_photo_loc_vol1);
				free(temp_photo_loc_vol1);
			}


			int* temp_photo_loc_id1 = (int*)eina_list_nth(row_vals, 12);
			if (temp_photo_loc_id1) {
				photo_loc_id1 = *temp_photo_loc_id1;
				free(temp_photo_loc_id1);
			}

			char *temp_photo_loc_sec1 = (char *)eina_list_nth(row_vals, 13);
			if(temp_photo_loc_sec1 && strlen(temp_photo_loc_sec1) > 0) {
				photo_loc_sec_str1 = strdup(temp_photo_loc_sec1);
				free(temp_photo_loc_sec1);
			}


			int* temp_photo_width1 = (int*)eina_list_nth(row_vals, 14);
			if(temp_photo_width1) {
				photo_width1 = *temp_photo_width1;
				free(temp_photo_width1);
			}


			int* temp_photo_height1 = (int*)eina_list_nth(row_vals, 15);
			if(temp_photo_height1) {
				photo_height1 = *temp_photo_height1;
				free(temp_photo_height1);
			}

			int* temp_photo_size1 = (int*)eina_list_nth(row_vals, 16);
			if(temp_photo_size1) {
				photo_size1 = *temp_photo_size1;
				free(temp_photo_size1);
			}


			char *temp_photo_data1 = (char *)eina_list_nth(row_vals, 17);
			if(temp_photo_data1 && strlen(temp_photo_data1) > 0) {
				photo_data1 = strdup(temp_photo_data1);
				free(temp_photo_data1);
			}


			char *temp_photo_type2 = (char *)eina_list_nth(row_vals, 18);
			if (temp_photo_type2 && strlen(temp_photo_type2) > 0) {
				photo_type2 =strdup(temp_photo_type2);
				free(temp_photo_type2);
			}


			int* temp_photo_loc_dc2 = (int*)eina_list_nth(row_vals, 19);
			if (temp_photo_loc_dc2) {
				photo_loc_dc2 = *temp_photo_loc_dc2;
				free(temp_photo_loc_dc2);
			}


			char *temp_photo_loc_vol2 = (char *)eina_list_nth(row_vals, 20);
			if(temp_photo_loc_vol2 && strlen(temp_photo_loc_vol2) > 0) {
				photo_loc_vol_str2 = strdup(temp_photo_loc_vol2);
				free(temp_photo_loc_vol2);
			}


			int* temp_photo_loc_id2 = (int*)eina_list_nth(row_vals, 21);
			if (temp_photo_loc_id2) {
				photo_loc_id2 = *temp_photo_loc_id2;
				free(temp_photo_loc_id2);
			}

			char *temp_photo_loc_sec2 = (char *)eina_list_nth(row_vals, 22);
			if(temp_photo_loc_sec2 && strlen(temp_photo_loc_sec2) > 0) {
				photo_loc_sec_str2 = strdup(temp_photo_loc_sec2);
				free(temp_photo_loc_sec2);
			}


			int* temp_photo_width2 = (int*)eina_list_nth(row_vals, 23);
			if(temp_photo_width2) {
				photo_width2 = *temp_photo_width2;
				free(temp_photo_width2);
			}


			int* temp_photo_height2 = (int*)eina_list_nth(row_vals, 24);
			if(temp_photo_height2) {
				photo_height2 = *temp_photo_height2;
				free(temp_photo_height2);
			}

			int* temp_photo_size2 = (int*)eina_list_nth(row_vals, 25);
			if(temp_photo_size2) {
				photo_size2 = *temp_photo_size2;
				free(temp_photo_size2);
			}


			char *temp_photo_data2 = (char *)eina_list_nth(row_vals, 26);
			if(temp_photo_data2 && strlen(temp_photo_data2) > 0) {
				photo_data2 = strdup(temp_photo_data2);
				free(temp_photo_data2);
			}

			char *temp_photo_type3 = (char *)eina_list_nth(row_vals, 27);
			if (temp_photo_type3 && strlen(temp_photo_type3) > 0) {
				photo_type3 =strdup(temp_photo_type3);
				free(temp_photo_type3);
			}


			int* temp_photo_loc_dc3 = (int*)eina_list_nth(row_vals, 28);
			if (temp_photo_loc_dc3) {
				photo_loc_dc3 = *temp_photo_loc_dc3;
				free(temp_photo_loc_dc3);
			}


			char *temp_photo_loc_vol3 = (char *)eina_list_nth(row_vals, 29);
			if(temp_photo_loc_vol3 && strlen(temp_photo_loc_vol3) > 0) {
				photo_loc_vol_str3 = strdup(temp_photo_loc_vol3);
				free(temp_photo_loc_vol3);
			}


			int* temp_photo_loc_id3 = (int*)eina_list_nth(row_vals, 30);
			if (temp_photo_loc_id3) {
				photo_loc_id3 = *temp_photo_loc_id3;
				free(temp_photo_loc_id3);
			}

			char *temp_photo_loc_sec3 = (char *)eina_list_nth(row_vals, 31);
			if(temp_photo_loc_sec3 && strlen(temp_photo_loc_sec3) > 0) {
				photo_loc_sec_str3 = strdup(temp_photo_loc_sec3);
				free(temp_photo_loc_sec3);
			}


			int* temp_photo_width3 = (int*)eina_list_nth(row_vals, 32);
			if(temp_photo_width3) {
				photo_width3 = *temp_photo_width3;
				free(temp_photo_width3);
			}


			int* temp_photo_height3 = (int*)eina_list_nth(row_vals, 33);
			if(temp_photo_height3) {
				photo_height3 = *temp_photo_height3;
				free(temp_photo_height3);
			}

			int* temp_photo_size3 = (int*)eina_list_nth(row_vals, 34);
			if(temp_photo_size3) {
				photo_size3 = *temp_photo_size3;
				free(temp_photo_size3);
			}


			char *temp_photo_data3 = (char *)eina_list_nth(row_vals, 35);
			if(temp_photo_data3 && strlen(temp_photo_data3) > 0) {
				photo_data3 = strdup(temp_photo_data3);
				free(temp_photo_data3);
			}

			char *temp_photo_type4 = (char *)eina_list_nth(row_vals, 36);
			if (temp_photo_type4 && strlen(temp_photo_type4) > 0) {
				photo_type4 =strdup(temp_photo_type4);
				free(temp_photo_type4);
			}


			int* temp_photo_loc_dc4 = (int*)eina_list_nth(row_vals, 37);
			if (temp_photo_loc_dc4) {
				photo_loc_dc4 = *temp_photo_loc_dc4;
				free(temp_photo_loc_dc4);
			}


			char *temp_photo_loc_vol4 = (char *)eina_list_nth(row_vals, 38);
			if(temp_photo_loc_vol4 && strlen(temp_photo_loc_vol4) > 0) {
				photo_loc_vol_str4 = strdup(temp_photo_loc_vol4);
				free(temp_photo_loc_vol4);
			}


			int* temp_photo_loc_id4 = (int*)eina_list_nth(row_vals, 39);
			if (temp_photo_loc_id4) {
				photo_loc_id4 = *temp_photo_loc_id4;
				free(temp_photo_loc_id4);
			}

			char *temp_photo_loc_sec4 = (char *)eina_list_nth(row_vals, 40);
			if(temp_photo_loc_sec4 && strlen(temp_photo_loc_sec4) > 0) {
				photo_loc_sec_str4 = strdup(temp_photo_loc_sec4);
				free(temp_photo_loc_sec4);
			}


			int* temp_photo_width4 = (int*)eina_list_nth(row_vals, 41);
			if(temp_photo_width4) {
				photo_width4 = *temp_photo_width4;
				free(temp_photo_width4);
			}


			int* temp_photo_height4 = (int*)eina_list_nth(row_vals, 42);
			if(temp_photo_height4) {
				photo_height4 = *temp_photo_height4;
				free(temp_photo_height4);
			}

			int* temp_photo_size4 = (int*)eina_list_nth(row_vals, 43);
			if(temp_photo_size4) {
				photo_size4 = *temp_photo_size4;
				free(temp_photo_size4);
			}


			char *temp_photo_data4 = (char *)eina_list_nth(row_vals, 44);
			if(temp_photo_data4 && strlen(temp_photo_data4) > 0) {
				photo_data4 = strdup(temp_photo_data4);
				free(temp_photo_data4);
			}


			/**************************************************************/

			char *temp_phone_no = (char *)eina_list_nth(row_vals, 45);

			if(temp_phone_no && strlen(temp_phone_no) > 0) {
				phone_no = strdup(temp_phone_no);
				free(temp_phone_no);
			}

			char *temp_first_name = (char *)eina_list_nth(row_vals, 46);

			if(temp_first_name && strlen(temp_first_name) > 0) {
				first_name = strdup(temp_first_name);
				free(temp_first_name);
			}

			char *temp_last_name = (char *)eina_list_nth(row_vals, 47);

			if(temp_last_name && strlen(temp_last_name) > 0) {
				last_name = strdup(temp_last_name);
				free(temp_last_name);
			}

			char *temp_file_path = (char *)eina_list_nth(row_vals, 48);

			if(temp_file_path && strlen(temp_file_path) > 0) {
				file_path = strdup(temp_file_path);
				free(temp_file_path);
			}
			break;
			eina_list_free(row_vals);
		}

		if (media_type == tgl_message_media_none) {

		} else if (media_type == tgl_message_media_photo) {

			long long media_id = atoll(media_id_str);
			long long access_hash = atoll(access_hash_str);

			struct tgl_photo* photo_prop = (struct tgl_photo*)malloc(sizeof(struct tgl_photo));
			photo_prop->id = media_id;
			photo_prop->access_hash = access_hash;
			photo_prop->user_id = user_id;
			photo_prop->date = date;
			photo_prop->caption = caption;
			photo_prop->geo.latitude = atof(latitude);
			photo_prop->geo.longitude = atof(longitude);
			photo_prop->sizes_num = sizes;

			photo_prop->sizes = talloc(sizeof(struct tgl_photo_size) * photo_prop->sizes_num);
			int i;
			for (i = 0; i < photo_prop->sizes_num; i++) {

				if (i == 0) {
					photo_prop->sizes[i].w = photo_width1;
					photo_prop->sizes[i].h = photo_height1;
					photo_prop->sizes[i].size = photo_size1;
					if(photo_data1) {
						photo_prop->sizes[i].data = strdup(photo_data1);
					}
					if(photo_type1) {
						photo_prop->sizes[i].type = strdup(photo_type1);
					}
					photo_prop->sizes[i].loc.dc = photo_loc_dc1;
					photo_prop->sizes[i].loc.local_id = photo_loc_id1;
					photo_prop->sizes[i].loc.secret = atoll(photo_loc_sec_str1);
					photo_prop->sizes[i].loc.volume = atoll(photo_loc_vol_str1);
				} else if (i == 1) {

					photo_prop->sizes[i].w = photo_width2;
					photo_prop->sizes[i].h = photo_height2;
					photo_prop->sizes[i].size = photo_size2;
					if(photo_data2) {
						photo_prop->sizes[i].data = strdup(photo_data2);
					}
					if(photo_type2) {
						photo_prop->sizes[i].type = strdup(photo_type2);
					}
					photo_prop->sizes[i].loc.dc = photo_loc_dc2;
					photo_prop->sizes[i].loc.local_id = photo_loc_id2;
					photo_prop->sizes[i].loc.secret = atoll(photo_loc_sec_str2);
					photo_prop->sizes[i].loc.volume = atoll(photo_loc_vol_str2);

				} else if (i == 2) {

					photo_prop->sizes[i].w = photo_width3;
					photo_prop->sizes[i].h = photo_height3;
					photo_prop->sizes[i].size = photo_size3;
					if(photo_data3) {
						photo_prop->sizes[i].data = strdup(photo_data3);
					}
					if(photo_type3) {
						photo_prop->sizes[i].type = strdup(photo_type3);
					}
					photo_prop->sizes[i].loc.dc = photo_loc_dc3;
					photo_prop->sizes[i].loc.local_id = photo_loc_id3;
					photo_prop->sizes[i].loc.secret = atoll(photo_loc_sec_str3);
					photo_prop->sizes[i].loc.volume = atoll(photo_loc_vol_str3);

				} else if (i == 3) {

					photo_prop->sizes[i].w = photo_width4;
					photo_prop->sizes[i].h = photo_height4;
					photo_prop->sizes[i].size = photo_size4;
					if(photo_data4) {
						photo_prop->sizes[i].data = strdup(photo_data4);
					}
					if(photo_type4) {
						photo_prop->sizes[i].type = strdup(photo_type4);
					}
					photo_prop->sizes[i].loc.dc = photo_loc_dc4;
					photo_prop->sizes[i].loc.local_id = photo_loc_id4;
					photo_prop->sizes[i].loc.secret = atoll(photo_loc_sec_str4);
					photo_prop->sizes[i].loc.volume = atoll(photo_loc_vol_str4);


				} else {

				}

			}
			photo_prop->to_peer_id = buddy_id;
			tgl_do_load_photo(s_info.TLS, photo_prop ,&on_image_download_completed, photo_prop);

		} else {

		}
	}
#endif
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
			//tgl_do_send_message(s_info.TLS, msg->to_id, msg_data, strlen(msg_data), &on_message_sent_to_buddy, (void*)(msg));
			tgl_do_send_message(s_info.TLS, msg->to_id, msg->message, strlen(msg->message), &on_message_sent_to_buddy, (void*)(msg));
		} else if (type_of_chat == TGL_PEER_ENCR_CHAT) {

		} else {

		}
	}
	free(msg_table);
}

void send_media_to_buddy(int buddy_id, int message_id, int media_id, int msg_type, char *file_path, int type_of_chat)
{
#if 0
	int t = time(NULL);
	struct tgl_message msg;
	msg.from_id.id = s_info.tg_data->id.id;
	msg.from_id.type = s_info.tg_data->id.type;
	msg.date = 0;
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id.id = 0;
	msg.fwd_from_id.type = 0;
	msg.id = 0;
	msg.message = "";
	msg.message_len = 0;
	msg.out = 0;
	msg.service = 0;
	msg.to_id.id = buddy_id;
	msg.to_id.type = s_info.tg_data->id.type;
	msg.unread = 0;
	msg.media.type = msg_type;
	msg.media.photo.id = (long long)t;

	char *msg_table = get_table_name_from_number(buddy_id);
	insert_msg_into_db(&msg, msg_table, t);
	insert_media_info_to_db(&msg, file_path);
	tgl_do_send_document(TLS, -1, msg.to_id, file_path, &on_message_sent_to_buddy, (void*) (t));
	free(msg_table);
#else

	char *msg_table = get_table_name_from_number(buddy_id);
	struct tgl_message* msg = get_message_from_message_table(message_id, msg_table);

	if (msg) {
		if (type_of_chat == TGL_PEER_USER) {

			msg->from_id.type = TGL_PEER_USER;
			msg->to_id.type = TGL_PEER_USER;


			if (msg->media.type == tgl_message_media_photo) {
				tgl_do_send_document(s_info.TLS, -1, msg->to_id, file_path, &on_message_sent_to_buddy, (void*) (msg));
			}


		} else if (type_of_chat == TGL_PEER_CHAT) {
			msg->from_id.type = TGL_PEER_CHAT;
			msg->to_id.type = TGL_PEER_CHAT;

			if (msg->media.type == tgl_message_media_photo) {
				tgl_do_send_document(s_info.TLS, -1, msg->to_id, file_path, &on_message_sent_to_buddy, (void*) (msg));
			}


		} else if (type_of_chat == TGL_PEER_ENCR_CHAT) {

		} else {

		}

	}
	free(msg_table);

#endif
}

static char *ui_utils_get_resource(const char *res_name)
{
	static char res_path[PATH_MAX] = {'\0'};
	char *path;

	path = app_get_resource_path();
	if (!path) {
		return NULL;
	}

	snprintf(res_path, PATH_MAX, "%s%s", path, res_name);
	free(path);

	return res_path;
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
		s_info.config_directory = DEFAULT_TELEGRAM_PATH; // specific path for tizen application.
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
