/* 
    This file is part of tgl-library

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    Copyright Vitaly Valtman 2014-2015
 */
#ifndef __TGL_LAYOUT_H__
#define __TGL_LAYOUT_H__

#define FLAG_MESSAGE_EMPTY 1
#define FLAG_DELETED 2
#define FLAG_FORBIDDEN 4
#define FLAG_HAS_PHOTO 8
#define FLAG_CREATED 16
#define FLAG_SESSION_OUTBOUND 32
#define FLAG_USER_SELF 128
#define FLAG_USER_FOREIGN 256
#define FLAG_USER_CONTACT 512
#define FLAG_USER_IN_CONTACT 1024
#define FLAG_USER_OUT_CONTACT 2048
#define FLAG_CHAT_IN_CHAT 128
#define FLAG_ENCRYPTED 4096
#define FLAG_PENDING 8192
#define FLAG_DOCUMENT_IMAGE 1
#define FLAG_DOCUMENT_STICKER 2
#define FLAG_DOCUMENT_ANIMATED 4
#define FLAG_DOCUMENT_AUDIO 8
#define FLAG_DOCUMENT_VIDEO 16

#pragma pack(push,4)

typedef struct {
	int type;
	int id;
} tgl_peer_id_t;

enum tgl_dc_state {
	st_init,
	st_reqpq_sent,
	st_reqdh_sent,
	st_client_dh_sent,
	st_init_temp,
	st_reqpq_sent_temp,
	st_reqdh_sent_temp,
	st_client_dh_sent_temp,
	st_authorized,
	st_error
};

#define MAX_DC_SESSIONS 3

struct tgl_session {
	struct tgl_dc *dc;
	long long session_id;
	long long last_msg_id;
	int seq_no;
	int received_messages;
	struct connection *c;
	struct tree_long *ack_tree;
	struct tgl_timer *ev;
};

struct tgl_dc {
	int id;
	int port;
	int flags;
	int rsa_key_idx;
	enum tgl_dc_state state;
	char *ip;
	//char *user;
	struct tgl_session *sessions[MAX_DC_SESSIONS];
	char auth_key[256];
	char temp_auth_key[256];
	char nonce[256];
	char new_nonce[256];
	char server_nonce[256];
	long long auth_key_id;
	long long temp_auth_key_id;
	long long temp_auth_key_bind_query_id;
	long long server_salt;
	struct tgl_timer *ev;
	int server_time_delta;
	double server_time_udelta;
	int has_auth;
};

enum tgl_message_media_type {
	tgl_message_media_none = 1001,
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

enum tgl_message_action_type {
	tgl_message_action_none,
	tgl_message_action_geo_chat_create,
	tgl_message_action_geo_chat_checkin,
	tgl_message_action_chat_create,
	tgl_message_action_chat_edit_title,
	tgl_message_action_chat_edit_photo,
	tgl_message_action_chat_delete_photo,
	tgl_message_action_chat_add_user,
	tgl_message_action_chat_delete_user,
	tgl_message_action_set_message_ttl,
	tgl_message_action_read_messages,
	tgl_message_action_delete_messages,
	tgl_message_action_screenshot_messages,
	tgl_message_action_flush_history,
	tgl_message_action_resend,
	tgl_message_action_notify_layer,
	tgl_message_action_typing,
	tgl_message_action_noop,
	tgl_message_action_commit_key,
	tgl_message_action_abort_key,
	tgl_message_action_request_key,
	tgl_message_action_accept_key
};

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

struct tgl_file_location {
	int dc;
	long long volume;
	int local_id;
	long long secret;
};

struct tgl_photo_size {
	char *type;
	struct tgl_file_location loc;
	int w;
	int h;
	int size;
	char *data;
};

struct tgl_geo {
	double longitude;
	double latitude;
};

struct tgl_media {
	long long media_id;
	int media_type;
	long long access_hash;
	int user_id;
	int date;
	char *caption;
	char *longitude;
	char *latitude;
	int sizes;
	char *phone_no;
	char *first_name;
	char *last_name;
	char *file_path;

	char *photo_type1;
	int photo_loc_dc1;
	long long photo_loc_vol1;
	int photo_loc_id1;
	long long photo_loc_sec1;
	int photo_width1;
	int photo_height1;
	int photo_size1;
	char *photo_data1;

	char *photo_type2;
	int photo_loc_dc2;
	long long photo_loc_vol2;
	int photo_loc_id2;
	long long photo_loc_sec2;
	int photo_width2;
	int photo_height2;
	int photo_size2;
	char *photo_data2;

	char *photo_type3;
	int photo_loc_dc3;
	long long photo_loc_vol3;
	int photo_loc_id3;
	long long photo_loc_sec3;
	int photo_width3;
	int photo_height3;
	int photo_size3;
	char *photo_data3;

	char *photo_type4;
	int photo_loc_dc4;
	long long photo_loc_vol4;
	int photo_loc_id4 ;
	long long photo_loc_sec4;
	int photo_width4;
	int photo_height4;
	int photo_size4;
	char *photo_data4;


	char* mime_type;
	char* doc_type;
	int doc_width;
	int doc_height;
	int doc_duration;
	int doc_size;
	int doc_dc;
	char* doc_thumb_path;

};

struct tgl_photo {
	long long id;
	long long access_hash;
	int user_id;
	int date;
	char *caption;
	struct tgl_geo geo;
	int sizes_num;
	struct tgl_photo_size *sizes;
	int to_peer_id;
};

struct tgl_encr_photo {
	long long id;
	long long access_hash;
	int dc_id;
	int size;
	int key_fingerprint;
	int flags;

	unsigned char *key;
	unsigned char *iv;
	int w;
	int h;
};

/*struct tgl_encr_video {
  long long id;
  long long access_hash;
  int dc_id;
  int size;
  int key_fingerprint;

  unsigned char *key;
  unsigned char *iv;
  int w;
  int h;
  int duration;
  char *mime_type;
};

struct tgl_encr_audio {
  long long id;
  long long access_hash;
  int dc_id;
  int size;
  int key_fingerprint;

  unsigned char *key;
  unsigned char *iv;
  int duration;
  char *mime_type;
};*/

struct tgl_encr_document {
	long long id;
	long long access_hash;
	int dc_id;
	int size;
	int key_fingerprint;
	int flags;

	unsigned char *key;
	unsigned char *iv;
	int w;
	int h;
	char *caption;
	char *mime_type;
	int duration;
};

//struct tgl_encr_file {
//  char *filename;
//  unsigned char *key;
//  unsigned char *iv;
//};


struct tgl_user_status {
	int online;
	int when;
	struct tgl_timer *ev;
};

struct tgl_user {
	tgl_peer_id_t id;
	int flags;
	struct tgl_message *last;
	char *print_name;
	int structure_version;
	struct tgl_file_location photo_big;
	struct tgl_file_location photo_small;
	long long photo_id;
	struct tgl_photo photo;
	char *first_name;
	char *last_name;
	char *phone;
	long long access_hash;
	struct tgl_user_status status;
	int blocked;
	char *real_first_name;
	char *real_last_name;
	char *username;
	int is_unknown;
};

struct tgl_chat_user {
	int user_id;
	int inviter_id;
	int date;
};

struct tgl_chat {
	tgl_peer_id_t id;
	int flags;
	struct tgl_message *last;
	char *print_title;
	int structure_version;
	struct tgl_file_location photo_big;
	struct tgl_file_location photo_small;
	struct tgl_photo photo;
	char *title;
	int users_num;
	int user_list_size;
	int user_list_version;
	struct tgl_chat_user *user_list;
	int date;
	int version;
	int admin_id;
};

enum tgl_secret_chat_state {
	sc_none,
	sc_waiting,
	sc_request,
	sc_ok,
	sc_deleted
};

enum tgl_secret_chat_exchange_state {
	tgl_sce_none,
	tgl_sce_requested,
	tgl_sce_accepted,
	tgl_sce_committed
};

struct tgl_secret_chat {
	tgl_peer_id_t id;
	int flags;
	struct tgl_message *last;
	char *print_name;
	int structure_version;
	struct tgl_file_location photo_big;
	struct tgl_file_location photo_small;
	struct tgl_photo photo;
	int user_id;
	int admin_id;
	int date;
	int ttl;
	int layer;
	int in_seq_no;
	int out_seq_no;
	int last_in_seq_no;
	long long access_hash;
	unsigned char *g_key;
	unsigned char *nonce;

	enum tgl_secret_chat_state state;
	int key[64];
	long long key_fingerprint;
	unsigned char first_key_sha[20];

	long long exchange_id;
	enum tgl_secret_chat_exchange_state exchange_state;
	int exchange_key[64];
	long long exchange_key_fingerprint;
};

typedef union tgl_peer {
	struct {
		tgl_peer_id_t id;
		int flags;
		struct tgl_message *last;
		char *print_name;
		int structure_version;
		struct tgl_file_location photo_big;
		struct tgl_file_location photo_small;
		struct tgl_photo photo;
	};
	struct tgl_user user;
	struct tgl_chat chat;
	struct tgl_secret_chat encr_chat;
} tgl_peer_t;
/*
struct tgl_video {
  long long id;
  long long access_hash;
  int user_id;
  int date;
  int size;
  int dc_id;
  struct tgl_photo_size thumb;
  char *caption;
  int duration;
  int w;
  int h;
  char *mime_type;
};

struct tgl_audio {
  long long id;
  long long access_hash;
  int user_id;
  int date;
  int size;
  int dc_id;
  int duration;
  char *mime_type;
};*/

struct tgl_document {
	long long id;
	long long access_hash;
	int user_id;
	int date;
	int size;
	int dc_id;
	struct tgl_photo_size thumb;
	char *caption;
	char *mime_type;

	int w;
	int h;
	int flags;
	int duration;

	int to_peer_id;
};

struct tgl_message_action {
	enum tgl_message_action_type type;
	union {
		struct {
			char *title;
			int user_num;
			int *users;
		};
		char *new_title;
		struct tgl_photo photo;
		int user;
		int ttl;
		int layer;
		int read_cnt;
		int delete_cnt;
		int screenshot_cnt;
		enum tgl_typing_status typing;
		struct {
			int start_seq_no;
			int end_seq_no;
		};
		struct {
			unsigned char *g_a;
			long long exchange_id;
			long long key_fingerprint;
		};
	};
};

struct tgl_message_media {
	enum tgl_message_media_type type;
	union {
		struct tgl_photo photo;
		//struct tgl_video video;
		//struct tgl_audio audio;
		struct tgl_document document;
		struct tgl_encr_document encr_document;

		struct tgl_geo geo;
		struct {
			char *phone;
			char *first_name;
			char *last_name;
			int user_id;
		};
		struct tgl_encr_photo encr_photo;
		//struct tgl_encr_video encr_video;
		//struct tgl_encr_audio encr_audio;
		//struct tgl_encr_document encr_document;
		//struct tgl_encr_file encr_file;
		struct {
			void *data;
			int data_size;
		};
	};
};

struct tgl_message {
	struct tgl_message *next_use, *prev_use;
	struct tgl_message *next, *prev;
	long long id;
	int flags;
	tgl_peer_id_t fwd_from_id;
	int fwd_date;
	tgl_peer_id_t from_id;
	tgl_peer_id_t to_id;
	int out;
	int unread;
	int date;
	int service;
	int msg_state;
	union {
		struct tgl_message_action action;
		struct {
			char *message;
			int message_len;
			struct tgl_message_media media;
		};
	};
};
#pragma pack(pop)
#endif
