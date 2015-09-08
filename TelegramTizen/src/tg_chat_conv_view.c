#include "tg_chat_conv_view.h"
#include "tg_db_wrapper.h"
#include "tg_common.h"
#include "server_requests.h"

typedef struct appdata_chat_conv_view{
	peer_with_pic_s *sel_item;
	const char *name;
	Evas_Object *nf;
	int num_of_bubbles;
	int total_messages;
	Evas_Object *chat_bg_box_layout;
	Evas_Object *chat_bg_box;
	Evas_Object *scroll_view;
	Evas_Object *main_box;
	Evas_Object *chat_box;
	Evas_Object *entry_box;
	Evas_Object *entry_box_layout;
	Evas_Object *chat_box_layout;
	Evas_Object *main_layout;
	Evas_Object *attach_icon;
	Evas_Object *text_entry;
	Evas_Object *smiley_icon;
	Evas_Object *send_icon;
	Eina_List *sent_pics;
	Eina_List *receive_pics;
	appdata_s* ad;
} appdata_chat_conv_view_s;

static appdata_chat_conv_view_s chat_conv_view_data = {0,};

#define CHAT_BUBBLE_TEXT_WIDTH 200
#define CHAT_BUBBLE_MAIN_TEXT_STYLE "<font_size=30>%s</font_size>"

static Evas_Object *create_bubble_table(Evas_Object *parent, Chat_message_Bubble_Style style, const char *main_text, const char *sub_text);
static Evas_Object *create_image_bubble_table(Evas_Object *parent, Chat_message_Bubble_Style style, const char *file_path, const char *sub_text, char* media_id);
static void bubble_msg_resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info);
void send_image_to_buddy(appdata_chat_conv_view_s *ad, const char* file_path);

//static void on_msg_sent_to_buddy(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *M);

static void on_chat_item_clicked(void *data, Evas_Object *obj, void *event_info)
{
	char* media_id_str = (char*)data;
	long long media_id = atoll(media_id_str);
	char* file_path = get_image_path_from_db(media_id);
	if (!file_path || strlen(file_path) <= 0) {
		// request service to download the image.
		send_request_for_image_downloading(chat_conv_view_data.ad->service_client, chat_conv_view_data.sel_item->use_data->peer_id, media_id);
	} else {

	}
}

void on_message_sent_to_buddy_successfully(appdata_s* ad, tg_message_s *M, int type_of_chat)
{
	// update UI
}

void on_message_read_by_buddy_successfully(appdata_s* ad, tg_message_s *M, int type_of_chat)
{
	// update UI
}

void on_received_image_loaded(int buddy_id, long long media_id, const char* file_path)
{
	// evas_object_data_set(main_image, "media_id", (void*)media_id);
	if(chat_conv_view_data.receive_pics) {
		int size = eina_list_count(chat_conv_view_data.receive_pics);

		for(int i = 0 ; i < size ; i++) {
			Evas_Object* img = eina_list_nth(chat_conv_view_data.receive_pics, i);
			char* temp_media_id = (char*)evas_object_data_get(img, "media_id");
			long long lmedia_id = atoll(temp_media_id);
			if(lmedia_id == media_id) {
				if (elm_image_file_set(img, file_path, NULL) == EINA_FALSE) {
					// TODO: error
				}
				chat_conv_view_data.receive_pics = eina_list_remove(chat_conv_view_data.receive_pics, img);
				break;
			}
		}
	}
}

void on_img_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		appdata_chat_conv_view_s *ad = user_data;
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);

		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);
			send_image_to_buddy(ad, file_path);
			free(file_path);
			break;
		}
	}
}

static void on_attach_clicked(void *data, Evas_Object *obj, void *event_info)
{
	app_control_h app_control;
	int ret = app_control_create(&app_control);
	if(ret != APP_CONTROL_ERROR_NONE) {
		show_toast(chat_conv_view_data.ad, "Error: Can not load image picker");
		return;
	}
	app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);
	app_control_set_mime(app_control,"image/*");
	app_control_send_launch_request(app_control, &on_img_app_control_reply_cb, &chat_conv_view_data);
	app_control_destroy(app_control);
}

static void on_text_entry_clicked(void *data, Evas_Object *obj, void *event_info)
{
	elm_entry_input_panel_hide(chat_conv_view_data.text_entry);
	elm_entry_input_panel_layout_set(chat_conv_view_data.text_entry,ELM_INPUT_PANEL_LAYOUT_NORMAL);
	elm_entry_input_panel_show(chat_conv_view_data.text_entry);
}

static void on_smiley_clicked(void *data, Evas_Object *obj, void *event_info)
{
	elm_entry_input_panel_hide(chat_conv_view_data.text_entry);
	elm_entry_input_panel_layout_set(chat_conv_view_data.text_entry,ELM_INPUT_PANEL_LAYOUT_EMOTICON);
	elm_entry_input_panel_show(chat_conv_view_data.text_entry);
}

#if 0
void on_chat_buddy_msg_marked_read(struct tgl_state *TLS, int num, struct tgl_message *list[])
{

}


void on_buddy_pic_msg_loaded(struct tgl_state *TLS, void *callback_extra, int success, char *filename)
{
	if(filename && success && callback_extra) {
		struct tgl_message* M = (char*)callback_extra;
		Evas_Object *bubble_table = NULL;

		time_t t = M->date;
		const char *format = "%H:%M";
		struct tm lt;
		char res[32];
		(void) localtime_r(&t, &lt);

		if (strftime(res, sizeof(res), format, &lt) == 0) {
			(void) fprintf(stderr,  "strftime(3): cannot format supplied "
					"date/time into buffer of size %u "
					"using: '%s'\n",
					sizeof(res), format);
			//exit(0);
		}

		update_photo_info_in_db(M, filename, 0);

		bubble_table = create_image_bubble_table(chat_conv_view_data.ad->win, CHAT_MESSAGE_BUBBLE_RECEIVE,
				filename,
				res);
		//evas_object_smart_callback_add(bubble_table, "clicked", on_chat_item_clicked, filename);
		evas_object_show(bubble_table);
		elm_box_pack_end(chat_conv_view_data.main_box, bubble_table);
		evas_object_event_callback_add(chat_conv_view_data.main_box, EVAS_CALLBACK_RESIZE, bubble_msg_resize_cb, &chat_conv_view_data);
	}
}
#endif

void on_chat_buddy_msg_receive(tg_message_s *M, int type_of_chat)
{
	int peer_id = 0;
	if(type_of_chat == TGL_PEER_USER) {
		peer_id = M->from_id;
	} else if(type_of_chat == TGL_PEER_CHAT) {
		peer_id = M->to_id;
	}

	if(M) {
		if(peer_id == chat_conv_view_data.sel_item->use_data->peer_id) {
			//M->message
			Evas_Object *bubble_table = NULL;
			time_t t = M->date;
			const char *format = "%H:%M";
			struct tm lt;
			char res[32];
			(void) localtime_r(&t, &lt);

			if (strftime(res, sizeof(res), format, &lt) == 0) {
				(void) fprintf(stderr,  "strftime(3): cannot format supplied "
						"date/time into buffer of size %u "
						"using: '%s'\n",
						sizeof(res), format);
				//exit(0);
			}

			if(M->media_type == tgl_message_media_none) {

				bubble_table = create_bubble_table(chat_conv_view_data.ad->win, CHAT_MESSAGE_BUBBLE_RECEIVE,
						M->message,
						res);
				evas_object_show(bubble_table);
				elm_box_pack_end(chat_conv_view_data.main_box, bubble_table);
				evas_object_event_callback_add(chat_conv_view_data.main_box, EVAS_CALLBACK_RESIZE, bubble_msg_resize_cb, &chat_conv_view_data);
			} else if(M->media_type == tgl_message_media_photo) {
				// load photo
#if 0
				struct tgl_photo* pic = &(M->media.photo);
				if(pic) {
					tgl_do_load_photo(TLS, pic ,&on_buddy_pic_msg_loaded,M);
				}
#endif
				char* path = ui_utils_get_resource(BLUR_BG);
				bubble_table = create_image_bubble_table(chat_conv_view_data.ad->win, CHAT_MESSAGE_BUBBLE_RECEIVE,
						path,
						res, M->media_id);
				evas_object_show(bubble_table);
				elm_box_pack_end(chat_conv_view_data.main_box, bubble_table);
				evas_object_event_callback_add(chat_conv_view_data.main_box, EVAS_CALLBACK_RESIZE, bubble_msg_resize_cb, &chat_conv_view_data);
			}
		}
	}
}

static int chat_history_db_callback(void *data, int argc, char **argv, char **azColName) {

	int temp_from_id = chat_conv_view_data.sel_item->use_data->peer_id;
	char from_id[50];
	sprintf(from_id, "%d", temp_from_id);

	int temp_own_id = chat_conv_view_data.ad->user_id.id;
	char own_id[50];
	sprintf(own_id, "%d", temp_own_id);

	Eina_Bool is_sent_msg = EINA_FALSE;
	char* message = NULL;
	char* msg_time = NULL;
	char* media_type_str = NULL;
	char* media_id_str = NULL;

	for (int i=0; i < argc; i++) {
		if (strcmp(azColName[i], "from_id") == 0) {
			char* tmp_val = argv[i];
			if(strcmp(tmp_val, from_id) == 0 ) {
				is_sent_msg = EINA_FALSE;
			} else {
				is_sent_msg = EINA_TRUE;
			}
		} else if (strcmp(azColName[i], "message") == 0) {
			message = strdup(argv[i]);
		} else if (strcmp(azColName[i], "date") == 0) {
			msg_time = strdup(argv[i]);
		} else if (strcmp(azColName[i], "media_type") == 0) {
			media_type_str = strdup(argv[i]);
		} else if (strcmp(azColName[i], "media_id") == 0) {
			media_id_str = strdup(argv[i]);
		}
	}

	int media_type = atoi(media_type_str);
	if(media_type == tgl_message_media_none) {
		Evas_Object *bubble_table;
		int time_val = strtol(msg_time, (char**)NULL, 10);
		time_t t = time_val;
		const char *format = "%H:%M";
		struct tm lt;
		char res[32];
		(void) localtime_r(&t, &lt);

		if (strftime(res, sizeof(res), format, &lt) == 0) {
			(void) fprintf(stderr,  "strftime(3): cannot format supplied "
					"date/time into buffer of size %u "
					"using: '%s'\n",
					sizeof(res), format);
		}
		if(is_sent_msg) {
			bubble_table = create_bubble_table(chat_conv_view_data.ad->win, CHAT_MESSAGE_BUBBLE_SENT,
					message,
					res);
		} else {
			bubble_table = create_bubble_table(chat_conv_view_data.ad->win, CHAT_MESSAGE_BUBBLE_RECEIVE,
					message,
					res);
		}
		elm_box_pack_end(chat_conv_view_data.main_box, bubble_table);

	} else if(media_type == tgl_message_media_photo) {

		long long media_id = atoll(media_id_str);

		char* img_path = get_image_path_from_db(media_id);

		if (img_path == NULL || strlen(img_path) == 0) {
			img_path = ui_utils_get_resource(BLUR_BG);
		}

		Evas_Object *bubble_table = NULL;
		int time_val = strtol(msg_time, (char**)NULL, 10);
		time_t t = time_val;
		const char *format = "%H:%M";
		struct tm lt;
		char res[32];
		(void) localtime_r(&t, &lt);

		if (strftime(res, sizeof(res), format, &lt) == 0) {
			(void) fprintf(stderr,  "strftime(3): cannot format supplied "
					"date/time into buffer of size %u "
					"using: '%s'\n",
					sizeof(res), format);
			//exit(0);
		}
		if(is_sent_msg) {
			bubble_table = create_image_bubble_table(chat_conv_view_data.ad->win, CHAT_MESSAGE_BUBBLE_SENT,
					img_path,
					res, (void*)media_id_str);
		} else {
			bubble_table = create_image_bubble_table(chat_conv_view_data.ad->win, CHAT_MESSAGE_BUBBLE_RECEIVE,
					img_path,
					res, (void*)media_id_str);
		}
		evas_object_show(bubble_table);
		elm_box_pack_end(chat_conv_view_data.main_box, bubble_table);

	} else if(media_type == tgl_message_media_document) {

	} else if(media_type == tgl_message_media_geo) {

	} else if(media_type == tgl_message_media_contact) {

	} else if(media_type == tgl_message_media_unsupported) {

	} else if(media_type == tgl_message_media_photo_encr) {

	} else if(media_type == tgl_message_media_document_encr) {

	} else  {

	}

	evas_object_event_callback_add(chat_conv_view_data.main_box, EVAS_CALLBACK_RESIZE, bubble_msg_resize_cb, &chat_conv_view_data);
	return 0;
}

#if 0
void on_msg_sent_to_buddy(struct tgl_state *TLS, void *callback_extra, int success, struct tgl_message *M)
{
	int t = callback_extra;
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	if(db) {
		char* table_name = "buddy_info_table";
		int user_id = M->to_id.id;
		char usr_str[50];
		sprintf(usr_str,"%d",user_id);

		char* where_clause = (char*)malloc(strlen("user_id = ") + strlen(usr_str) + 1);
		strcpy(where_clause, "user_id = ");
		strcat(where_clause, usr_str);

		Eina_List* col_types = NULL;
		col_types = eina_list_append(col_types, "TEXT");

		Eina_List* col_names = NULL;
		col_names = eina_list_append(col_names, "phone");

		Eina_List* vals = get_values_from_table_sync(db, table_name, col_names, col_types, where_clause);
		close_database(db);

		char* phone_no = NULL;

		if(!vals) {
			show_toast("DB error");
			return;
		} else {
			int row_count = eina_list_count(vals);

			for (int i = 0 ; i < row_count ; i++) {
				Eina_List* row_vals = eina_list_nth(vals, i);
				phone_no = (char*)eina_list_nth(row_vals, 0);
				if(!phone_no) {
					show_toast("DB Error");
					return;
				} else {
					break;
				}
				eina_list_free(row_vals);
			}
			eina_list_free(vals);
		}

		if(phone_no) {
			char* tb_name = get_table_name_from_number(phone_no);

			update_msg_into_db(M,tb_name, t);

			if (M->media.type == tgl_message_media_photo) {
				update_photo_info_in_db(M, NULL, t);
			}

			free(tb_name);
			free(phone_no);
		}
	}
	close_database(db);
}
#endif

void
bubble_msg_resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	appdata_chat_conv_view_s *ad = data;

	Evas_Coord w, h;

	//elm_scroller_child_size_get(ad->scroll_view, &w, &h);
	evas_object_size_hint_min_get(ad->main_box, &w, &h);

	elm_scroller_region_show(ad->scroll_view, 0, h, 0, 0);

	evas_object_event_callback_del(ad->main_box, EVAS_CALLBACK_RESIZE, bubble_msg_resize_cb);
}

void send_message_to_buddy(appdata_chat_conv_view_s *ad)
{
	Evas_Object *bubble_table;

	if (!ad->text_entry)
		return;
	const char* text_to_send = elm_entry_entry_get(ad->text_entry);
	if (!text_to_send || (strlen(text_to_send) == 0))
		return;

	// send request to service
	//send_request_for_message_transport(ad->ad->service_client, ad->sel_item->use_data->peer_id, tgl_message_media_none, text_to_send, chat_conv_view_data.sel_item->use_data->peer_type);

	bubble_table = create_bubble_table(ad->ad->win, CHAT_MESSAGE_BUBBLE_SENT,
			elm_entry_entry_get(ad->text_entry),
			get_current_time());

	evas_object_show(bubble_table);
	elm_box_pack_end(ad->main_box, bubble_table);
	elm_entry_entry_set(ad->text_entry, "");
	//free(text_to_send);

	evas_object_event_callback_add(ad->main_box, EVAS_CALLBACK_RESIZE, bubble_msg_resize_cb, ad);
}

void send_image_to_buddy(appdata_chat_conv_view_s *ad, const char* file_path)
{
	Evas_Object *bubble_table;
	//send_request_for_media_transport(ad->ad->service_client, ad->sel_item->use_data->peer_id, tgl_message_media_photo, file_path);
	int t = time(NULL); // to identify message after getting id.
	char unique_id[50];
	sprintf(unique_id, "%d", t);
	bubble_table = create_image_bubble_table(ad->ad->win, CHAT_MESSAGE_BUBBLE_SENT,	file_path, get_current_time(), unique_id);
	evas_object_show(bubble_table);
	elm_box_pack_end(ad->main_box, bubble_table);
	evas_object_event_callback_add(ad->main_box, EVAS_CALLBACK_RESIZE, bubble_msg_resize_cb, ad);
}

static void load_chat_history(appdata_chat_conv_view_s *ad)
{
	int buddy_id = chat_conv_view_data.sel_item->use_data->peer_id;

#if 0
	Eina_List* buddy_details_array = get_buddy_info(buddy_id);
	if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
		Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
		if (buddy_details && eina_list_count(buddy_details) > 0) {
			char* phone = eina_list_nth(buddy_details, 7);
			if (phone) {
				// get table name from phone number
				char* tablename = get_table_name_from_number(phone);
				Eina_List* col_names = NULL;
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ID);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FLAGS);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FWD_FROM_ID);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FWD_DATE);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FROM_ID);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_TO_ID);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_OUT_MSG);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNREAD);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_DATE);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_SERVICE);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_LENGTH);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_TYPE);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_ID);
				col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNIQUE_ID);
				sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
				Eina_Bool ret = get_values_from_table(db, tablename, col_names, &chat_history_db_callback, NULL, NULL);
				if(!ret) {
					//show_toast("DB Error: Failed to load chat");
				}
				eina_list_free(col_names);
				close_database(db);
			}
		}
	}
#else
	char* tablename = get_table_name_from_number(buddy_id);
	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FLAGS);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FWD_FROM_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FWD_DATE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_FROM_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_TO_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_OUT_MSG);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNREAD);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_DATE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_SERVICE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_LENGTH);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_TYPE);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MEDIA_ID);
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_UNIQUE_ID);
	sqlite3* db = create_database(DEFAULT_TG_DATABASE_PATH);
	Eina_Bool ret = get_values_from_table(db, tablename, col_names, &chat_history_db_callback, NULL, NULL);
	if(!ret) {
		//show_toast("DB Error: Failed to load chat");
	}
	eina_list_free(col_names);
	close_database(db);
	free(tablename);
#endif
}

Evas_Object* create_image_bubble_table(Evas_Object *parent, Chat_message_Bubble_Style style, const char *file_path, const char *sub_text, char* media_id)
{
	Evas_Object *bubble_table,*main_box, *sub_box, *main_image, *sub_label;
	Eina_Strbuf *strbuf = NULL;
	char *buf = NULL;

	bubble_table = elm_table_add(parent);
	evas_object_size_hint_weight_set(bubble_table, EVAS_HINT_EXPAND, 0.0);
	elm_table_padding_set(bubble_table, ELM_SCALE_SIZE(10), ELM_SCALE_SIZE(10));
	evas_object_show(bubble_table);

	/* Prepare string buffer for making mark up text */
	strbuf = eina_strbuf_new();

	Evas_Object* layout = elm_layout_add(bubble_table);
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(EDJ_CHAT_CONV_FILE, edj_path, (int)PATH_MAX);

	if(style == CHAT_MESSAGE_BUBBLE_SENT) {
		elm_layout_file_set(layout, edj_path, "chat_send_pic_item_box");
	} else if(style == CHAT_MESSAGE_BUBBLE_RECEIVE) {
		elm_layout_file_set(layout, edj_path, "chat_recv_pic_item_box");
	}

	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(layout);

	main_box = elm_box_add(bubble_table);
	evas_object_size_hint_align_set(main_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(main_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(main_box);


	main_image = elm_image_add(bubble_table);

	if (elm_image_file_set(main_image, file_path, NULL) == EINA_FALSE) {
		// TODO:
	}

	int win_w, win_h;
	elm_win_screen_size_get(chat_conv_view_data.ad->win, NULL, NULL, &win_w, &win_h);

	int w;
	int h;
	elm_image_object_size_get(main_image, &w, &h);
	elm_image_resizable_set(main_image, EINA_TRUE, EINA_TRUE);

	//evas_object_size_hint_min_set(main_image, w, h);
	evas_object_size_hint_min_set(main_image, 400, 400);

	evas_object_size_hint_max_set(main_image, 3*(win_w/4), (win_h/4));
	//evas_object_resize(main_image, w, h);
	elm_image_aspect_fixed_set(main_image,EINA_TRUE);

	evas_object_repeat_events_set(main_image, EINA_TRUE);

	evas_object_smart_callback_add(main_image, "clicked", on_chat_item_clicked, (void*)media_id);

	evas_object_show(main_image);

	elm_box_pack_end(main_box,layout);

	evas_object_data_set(main_image, "media_id", (void*)media_id);

	sub_box = elm_box_add(bubble_table);
	evas_object_size_hint_align_set(sub_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(sub_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(sub_box);

	/* Make a mark up text to string buffer for sub label widget */
	eina_strbuf_append_printf(strbuf, CHAT_BUBBLE_SUB_TEXT_STYLE, sub_text);
	/* Get the string from string buffer. String buffer will be empty. */
	buf = eina_strbuf_string_steal(strbuf);
	/* Free string buffer */
	eina_strbuf_free(strbuf);

	sub_label = elm_label_add(bubble_table);
	elm_object_text_set(sub_label, buf);
	evas_object_size_hint_weight_set(sub_label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_repeat_events_set(sub_label, EINA_TRUE);
	evas_object_show(sub_label);

	elm_box_pack_end(sub_box,sub_label);

	switch (style) {
	case CHAT_MESSAGE_BUBBLE_SENT:
		chat_conv_view_data.sent_pics = eina_list_append(chat_conv_view_data.sent_pics, main_image);
		elm_object_part_content_set(layout, "swallow.chat_send_pic", main_image);
		evas_object_size_hint_align_set(bubble_table, 1.0, 0.0);
		evas_object_size_hint_align_set(sub_label, 1.0, EVAS_HINT_FILL);
		elm_table_pack(bubble_table, main_box, 0, 0, 1, 1);
		elm_table_pack(bubble_table, sub_box, 0, 1, 1, 1);
		break;
	case CHAT_MESSAGE_BUBBLE_RECEIVE:
		chat_conv_view_data.receive_pics = eina_list_append(chat_conv_view_data.receive_pics, main_image);
		elm_object_part_content_set(layout, "swallow.chat_recv_pic", main_image);
		evas_object_size_hint_align_set(bubble_table, 0.0, 0.0);
		evas_object_size_hint_align_set(sub_label, 0.0, EVAS_HINT_FILL);
		elm_table_pack(bubble_table, main_box, 0, 0, 1, 1);
		elm_table_pack(bubble_table, sub_box, 0, 1, 1, 1);
		break;
	case CHAT_MESSAGE_BUBBLE_NONE:
	case CHAT_MESSAGE_BUBBLE_LAST:
	default:
		break;
	}

	return bubble_table;
}

Evas_Object *
create_bubble_table(Evas_Object *parent, Chat_message_Bubble_Style style, const char *main_text, const char *sub_text)
{
	Evas_Object *bubble_table,*main_box, *sub_box, *main_label, *sub_label;
	Eina_Strbuf *strbuf = NULL;
	char *buf = NULL;

	bubble_table = elm_table_add(parent);
	evas_object_size_hint_weight_set(bubble_table, EVAS_HINT_EXPAND, 0.0);
	elm_table_padding_set(bubble_table, ELM_SCALE_SIZE(5), ELM_SCALE_SIZE(5));
	evas_object_show(bubble_table);

	/* Prepare string buffer for making mark up text */
	strbuf = eina_strbuf_new();
	/* Make a mark up text to string buffer for main label widget */
	eina_strbuf_append_printf(strbuf, CHAT_BUBBLE_MAIN_TEXT_STYLE, main_text);
	/* Get the string from string buffer. String buffer will be empty. */
	buf = eina_strbuf_string_steal(strbuf);


	Evas_Object* layout = elm_layout_add(bubble_table);
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(EDJ_CHAT_CONV_FILE, edj_path, (int)PATH_MAX);

	if(style == CHAT_MESSAGE_BUBBLE_SENT) {
		elm_layout_file_set(layout, edj_path, "chat_send_item_box");
	} else if(style == CHAT_MESSAGE_BUBBLE_RECEIVE) {
		elm_layout_file_set(layout, edj_path, "chat_recv_item_box");
	}

	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(layout);

	main_box = elm_box_add(bubble_table);
	evas_object_size_hint_align_set(main_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(main_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(main_box);


	main_label = elm_label_add(bubble_table);
	elm_object_text_set(main_label, buf);
	elm_label_wrap_width_set(main_label, ELM_SCALE_SIZE(CHAT_BUBBLE_TEXT_WIDTH));
	elm_label_line_wrap_set(main_label, ELM_WRAP_MIXED);
	evas_object_size_hint_weight_set(main_label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(main_label, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_repeat_events_set(main_label, EINA_TRUE);
	evas_object_show(main_label);

	elm_box_pack_end(main_box,layout);

	sub_box = elm_box_add(bubble_table);
	evas_object_size_hint_align_set(sub_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(sub_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(sub_box);

	/* Make a mark up text to string buffer for sub label widget */
	eina_strbuf_append_printf(strbuf, CHAT_BUBBLE_SUB_TEXT_STYLE, sub_text);
	/* Get the string from string buffer. String buffer will be empty. */
	buf = eina_strbuf_string_steal(strbuf);
	/* Free string buffer */
	eina_strbuf_free(strbuf);

	sub_label = elm_label_add(bubble_table);
	elm_object_text_set(sub_label, buf);
	evas_object_size_hint_weight_set(sub_label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_repeat_events_set(sub_label, EINA_TRUE);
	evas_object_show(sub_label);

	elm_box_pack_end(sub_box,sub_label);

	switch (style) {
	case CHAT_MESSAGE_BUBBLE_SENT:
		elm_object_part_content_set(layout, "swallow.chat_send_text", main_label);
		evas_object_size_hint_align_set(bubble_table, 1.0, 0.0);
		evas_object_size_hint_align_set(sub_label, 1.0, EVAS_HINT_FILL);
		elm_table_pack(bubble_table, main_box, 0, 0, 1, 1);
		elm_table_pack(bubble_table, sub_box, 0, 1, 1, 1);
		break;
	case CHAT_MESSAGE_BUBBLE_RECEIVE:
		elm_object_part_content_set(layout, "swallow.chat_recv_text", main_label);
		evas_object_size_hint_align_set(bubble_table, 0.0, 0.0);
		evas_object_size_hint_align_set(sub_label, 0.0, EVAS_HINT_FILL);
		elm_table_pack(bubble_table, main_box, 0, 0, 1, 1);
		elm_table_pack(bubble_table, sub_box, 0, 1, 1, 1);
		break;
	case CHAT_MESSAGE_BUBBLE_NONE:
	case CHAT_MESSAGE_BUBBLE_LAST:
	default:
		break;
	}

	return bubble_table;
}

static void on_send_clicked(void *data, Evas_Object *obj, void *event_info)
{
	send_message_to_buddy(data);
}

void launch_chat_conv_view_cb(void *data, int user_id)
{
	appdata_s* ad = data;
	ad->current_app_state = TG_BUDDY_CHAT_CONV_STATE;
	chat_conv_view_data.ad = ad;
	chat_conv_view_data.nf = ad->nf;
	chat_conv_view_data.sent_pics = NULL;
	chat_conv_view_data.receive_pics = NULL;

	chat_conv_view_data.sel_item = eina_list_nth(ad->peer_list, user_id);
	int w, h;
	elm_win_screen_size_get(ad->win, NULL, NULL, &w, &h);
	h -= 130;

	char edj_path[PATH_MAX] = {0, };

	evas_object_hide(ad->panel);
	elm_layout_theme_set(ad->layout, "layout", "application", "default");
	chat_conv_view_data.chat_bg_box_layout = elm_layout_add(ad->win);
	app_get_resource(EDJ_CHAT_CONV_FILE, edj_path, (int)PATH_MAX);
	elm_layout_file_set(chat_conv_view_data.chat_bg_box_layout, edj_path, "chat_bg_conv");
	//evas_object_size_hint_min_set(chat_conv_view_data.chat_bg_box_layout, w, h);
	evas_object_show(chat_conv_view_data.chat_bg_box_layout);

	chat_conv_view_data.chat_bg_box = elm_box_add(chat_conv_view_data.chat_bg_box_layout);
	evas_object_size_hint_align_set(chat_conv_view_data.chat_bg_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.chat_bg_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(chat_conv_view_data.chat_bg_box_layout, "swallow.chat_bg_box", chat_conv_view_data.chat_bg_box);
	evas_object_show(chat_conv_view_data.chat_bg_box);

	chat_conv_view_data.main_layout = elm_layout_add(ad->win);
	app_get_resource(EDJ_CHAT_CONV_FILE, edj_path, (int)PATH_MAX);
	elm_layout_file_set(chat_conv_view_data.main_layout, edj_path, "chat_conv");
	evas_object_size_hint_min_set(chat_conv_view_data.main_layout, w, h);
	evas_object_show(chat_conv_view_data.main_layout);

	chat_conv_view_data.chat_box = elm_box_add(chat_conv_view_data.main_layout);
	evas_object_size_hint_align_set(chat_conv_view_data.chat_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.chat_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(chat_conv_view_data.main_layout, "swallow.chat_box", chat_conv_view_data.chat_box);
	evas_object_show(chat_conv_view_data.chat_box);

	chat_conv_view_data.entry_box = elm_box_add(chat_conv_view_data.main_layout);
	evas_object_size_hint_align_set(chat_conv_view_data.entry_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.entry_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(chat_conv_view_data.main_layout, "swallow.entry_box", chat_conv_view_data.entry_box);
	evas_object_show(chat_conv_view_data.entry_box);

	chat_conv_view_data.scroll_view = elm_scroller_add(chat_conv_view_data.chat_box);
	evas_object_size_hint_align_set(chat_conv_view_data.scroll_view, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.scroll_view, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_scroller_bounce_set(chat_conv_view_data.scroll_view, EINA_FALSE, EINA_TRUE);
	evas_object_show(chat_conv_view_data.scroll_view);


	chat_conv_view_data.chat_box_layout = elm_layout_add(ad->win);
	elm_layout_file_set(chat_conv_view_data.chat_box_layout, edj_path, "chat_display_box");
	evas_object_size_hint_align_set(chat_conv_view_data.chat_box_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.chat_box_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(chat_conv_view_data.chat_box_layout);

	chat_conv_view_data.main_box = elm_box_add(chat_conv_view_data.chat_box_layout);
	evas_object_size_hint_align_set(chat_conv_view_data.main_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.main_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(chat_conv_view_data.chat_box_layout, "swallow.chat_box", chat_conv_view_data.main_box);
	elm_box_align_set(chat_conv_view_data.main_box,0.0, 1.0);
	elm_box_padding_set(chat_conv_view_data.main_box, 25, 25);
	elm_box_homogeneous_set(chat_conv_view_data.main_box, EINA_FALSE);

	evas_object_show(chat_conv_view_data.main_box);
	elm_object_content_set(chat_conv_view_data.scroll_view, chat_conv_view_data.chat_box_layout);


	elm_box_pack_end(chat_conv_view_data.chat_box, chat_conv_view_data.scroll_view);

	/********************** entry layout*******************************/
	chat_conv_view_data.entry_box_layout = elm_layout_add(ad->win);
	elm_layout_file_set(chat_conv_view_data.entry_box_layout, edj_path, "chat_entry_box");
	evas_object_size_hint_align_set(chat_conv_view_data.entry_box_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.entry_box_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(chat_conv_view_data.entry_box_layout);

	chat_conv_view_data.attach_icon = elm_image_add(chat_conv_view_data.entry_box_layout);
	evas_object_size_hint_align_set(chat_conv_view_data.attach_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.attach_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_image_file_set(chat_conv_view_data.attach_icon, ui_utils_get_resource(ATTACH_ICON), NULL);
	elm_image_resizable_set(chat_conv_view_data.attach_icon, EINA_TRUE, EINA_TRUE);
	evas_object_show(chat_conv_view_data.attach_icon);
	evas_object_smart_callback_add(chat_conv_view_data.attach_icon, "clicked", on_attach_clicked, &chat_conv_view_data);
	elm_object_part_content_set(chat_conv_view_data.entry_box_layout, "swallow.attach_icon", chat_conv_view_data.attach_icon);

	chat_conv_view_data.text_entry = elm_entry_add(chat_conv_view_data.entry_box_layout);
	elm_object_part_text_set(chat_conv_view_data.text_entry, "elm.guide", "Enter Message");
	elm_entry_line_wrap_set(chat_conv_view_data.text_entry, EINA_TRUE);
	evas_object_size_hint_align_set(chat_conv_view_data.text_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.text_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(chat_conv_view_data.text_entry);
	elm_entry_scrollable_set(chat_conv_view_data.text_entry, EINA_TRUE);
	evas_object_smart_callback_add(chat_conv_view_data.text_entry, "clicked", on_text_entry_clicked, &chat_conv_view_data);
	elm_object_part_content_set(chat_conv_view_data.entry_box_layout, "swallow.text_entry", chat_conv_view_data.text_entry);

	chat_conv_view_data.smiley_icon = elm_image_add(chat_conv_view_data.entry_box_layout);
	evas_object_size_hint_align_set(chat_conv_view_data.smiley_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.smiley_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_image_file_set(chat_conv_view_data.smiley_icon, ui_utils_get_resource(SMILEY_ICON_UNPRESSED), NULL);
	elm_image_resizable_set(chat_conv_view_data.smiley_icon, EINA_TRUE, EINA_TRUE);
	evas_object_show(chat_conv_view_data.smiley_icon);
	evas_object_smart_callback_add(chat_conv_view_data.smiley_icon, "clicked", on_smiley_clicked, &chat_conv_view_data);
	elm_object_part_content_set(chat_conv_view_data.entry_box_layout, "swallow.smiely_icon", chat_conv_view_data.smiley_icon);

	chat_conv_view_data.send_icon = elm_image_add(chat_conv_view_data.entry_box_layout);
	evas_object_size_hint_align_set(chat_conv_view_data.send_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(chat_conv_view_data.send_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_image_file_set(chat_conv_view_data.send_icon, ui_utils_get_resource(SEND_PRESSED_ICON), NULL);
	elm_image_resizable_set(chat_conv_view_data.send_icon, EINA_TRUE, EINA_TRUE);
	evas_object_show(chat_conv_view_data.send_icon);
	evas_object_smart_callback_add(chat_conv_view_data.send_icon, "clicked", on_send_clicked, &chat_conv_view_data);
	elm_object_part_content_set(chat_conv_view_data.entry_box_layout, "swallow.send_icon", chat_conv_view_data.send_icon);

	/******************************************************************************************************/

	elm_box_pack_end(chat_conv_view_data.entry_box, chat_conv_view_data.entry_box_layout);

	//elm_box_pack_end(chat_conv_view_data.chat_bg_box, chat_conv_view_data.main_layout);

	Elm_Object_Item* chat_nav_item = elm_naviframe_item_push(ad->nf, chat_conv_view_data.sel_item->use_data->print_name, NULL, NULL, chat_conv_view_data.main_layout, NULL);
	elm_object_item_part_content_set(chat_nav_item, "title_left_btn", chat_conv_view_data.sel_item->contact_icon);

	load_chat_history(&chat_conv_view_data);

#if 0
	set_msg_mark_read_app_callback(&on_chat_buddy_msg_marked_read);
	set_msg_received_app_callback(&on_chat_buddy_msg_receive);
#endif


	evas_object_event_callback_add(chat_conv_view_data.main_box, EVAS_CALLBACK_RESIZE, bubble_msg_resize_cb, &chat_conv_view_data);

	/*	char* path = ui_utils_get_resource(SEARCH_ICON);
		Evas_Object *bubble_table = NULL;
		bubble_table = create_image_bubble_table(chat_conv_view_data.ad->win, CHAT_MESSAGE_BUBBLE_SENT,
		path,
		"10:50");
		elm_box_pack_end(chat_conv_view_data.main_box, bubble_table);*/

}
