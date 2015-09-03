#include "telegramtizen.h"
#include "tg_splash_screen.h"
#include "tg_registration.h"
#include "tg_db_wrapper.h"
#include "tg_login.h"
#include "tg_buddy_list.h"
#include "tg_first_registration.h"
#include "tg_chat_conv_view.h"
#include "device_contacts_manager.h"
#include "contacts-db-utils.h"
#include "server_requests.h"
#include "tg_buddy_chat_view.h"
#include "tg_init_screen.h"
#include "tg_user_main_view.h"
#include "tg_messaging_view.h"

static void
popup_block_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(obj);
}

static void
popup_timeout_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(obj);
}

void show_toast(appdata_s *ad, char* value)
{
	Evas_Object *popup;
	Evas_Object *win = ad->win;
	popup = elm_popup_add(win);
	elm_object_style_set(popup, "toast");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);

	char buf[512] = {'\0'};
	snprintf(buf, sizeof(buf), "<font_size=30><color=#000000>%s</color></font_size>", value);

	//elm_object_part_text_set(popup,"elm.text", buf);
	elm_object_text_set(popup, buf);
	evas_object_smart_callback_add(popup, "block,clicked", popup_block_clicked_cb, win);
	elm_popup_timeout_set(popup, 2.0);
	evas_object_smart_callback_add(popup, "timeout", popup_timeout_cb, NULL);
	evas_object_show(popup);
}

static int _app_send_response(appdata_s *app, bundle *const msg)
{
	int res = SVC_RES_FAIL;
	res = service_client_send_message(app->service_client, msg);
	return res;
}

static void load_registered_user_data(appdata_s *ad, Eina_List* user_info)
{
	//Eina_List* user_info = get_registered_user_info();

	if(!user_info) {
		//error
		show_toast(ad, "User info not loaded");
	}

	int row_count = eina_list_count(user_info);

	for (int i = 0 ; i < row_count ; i++) {
		Eina_List* row_vals = eina_list_nth(user_info, i);

		int *temp_user_id = (int*)eina_list_nth(row_vals, 0);
		if(temp_user_id) {
			int user_id = *temp_user_id;
			free(temp_user_id);

			ad->user_id.id = user_id;
			ad->user_id.type = TGL_PEER_USER;

			ad->current_user_data.user_id.id = user_id;
			ad->current_user_data.user_id.type = TGL_PEER_USER;

		}

		char *print_name = (char*)eina_list_nth(row_vals, 1);
		if(print_name) {
			ad->current_user_data.print_name = strdup(print_name);
			free(print_name);
		}

		int *temp_struct_ver = (int*)eina_list_nth(row_vals, 2);
		if(temp_struct_ver) {
			ad->current_user_data.structure_version = *temp_struct_ver;
			free(temp_struct_ver);
		}

		char *photo_path = (char*)eina_list_nth(row_vals, 3);
		if(photo_path) {
			ad->current_user_data.photo_path = strdup(photo_path);
			free(photo_path);
		}

		int *temp_photo_id = (int*)eina_list_nth(row_vals, 4);
		if(temp_photo_id) {
			ad->current_user_data.photo_id = *temp_photo_id;
			free(temp_photo_id);
		}

		char *first_name = (char*)eina_list_nth(row_vals, 5);
		if(first_name) {
			ad->current_user_data.first_name = strdup(first_name);
			free(first_name);
		}

		char *last_name = (char*)eina_list_nth(row_vals, 6);
		if(last_name) {
			ad->current_user_data.last_name = strdup(last_name);
			free(last_name);
		}

		char *phone_no = (char*)eina_list_nth(row_vals, 7);
		if(phone_no) {
			ad->current_user_data.phone = strdup(phone_no);
			free(phone_no);
		}

		int *temp_access_hash = (int*)eina_list_nth(row_vals, 8);
		if(temp_access_hash) {
			ad->current_user_data.access_hash = *temp_access_hash;
			free(temp_access_hash);
		}

		char *real_first_name = (char*)eina_list_nth(row_vals, 9);
		if(real_first_name) {
			ad->current_user_data.real_first_name = strdup(real_first_name);
			free(real_first_name);
		}

		char *real_last_name = (char*)eina_list_nth(row_vals, 10);
		if(real_last_name) {
			ad->current_user_data.real_last_name = strdup(real_last_name);
			free(real_last_name);
		}

		char *user_name = (char*)eina_list_nth(row_vals, 11);
		if(user_name) {
			ad->current_user_data.username = strdup(user_name);
			free(user_name);
		}

		int *temp_online_status = (int*)eina_list_nth(row_vals, 12);
		if(temp_online_status) {
			ad->current_user_data.online = *temp_online_status;
			free(temp_online_status);
		}

		int *temp_last_seen = (int*)eina_list_nth(row_vals, 13);
		if(temp_last_seen) {
			ad->current_user_data.last_seen = *temp_last_seen;
			free(temp_last_seen);
		}

		eina_list_free(row_vals);

		break;
	}
	eina_list_free(user_info);
}

void load_peer_data(appdata_s *ad)
{
	if (!ad) {
		return;
	}

	if (ad->peer_list) {
		for (int i = 0; i < eina_list_count(ad->peer_list) ; i++) {
			peer_with_pic_s* pic_item = eina_list_nth(ad->peer_list, i);
			tg_peer_info_s* item = pic_item->use_data;
			if (item) {
				if (item->print_name) {
					free(item->print_name);
					item->print_name = NULL;
				}
				if (item->photo_path) {
					free(item->photo_path);
					item->photo_path = NULL;
				}
				free(item);
			}
			free(pic_item);
		}
		eina_list_free(ad->peer_list);
	}
	ad->peer_list = NULL;


	Eina_List* peer_details = get_all_peer_details();

	for (int i = 0; i < eina_list_count(peer_details) ; i++) {
		Eina_List* ts_msg = eina_list_nth(peer_details, i);
		tg_peer_info_s* peer_info = (tg_peer_info_s*)malloc(sizeof(tg_peer_info_s));

		int *temp_peer_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_peer_id) {
			peer_info->peer_id  = *temp_peer_id;
			free(temp_peer_id);
		}

		int *temp_peer_type = (int*)eina_list_nth(ts_msg, 1);
		if (temp_peer_type) {
			peer_info->peer_type  = *temp_peer_type;
			free(temp_peer_type);
		}

		int *temp_flags = (int*)eina_list_nth(ts_msg, 2);
		if (temp_flags) {
			peer_info->flags = *temp_flags;
			free(temp_flags);
		}

		char *temp_msg_id = (char*)eina_list_nth(ts_msg, 3);
		if (temp_msg_id) {
			peer_info->last_msg_id  = atoll(temp_msg_id);
			free(temp_msg_id);
		}

		int *temp_last_msg_date = (int*)eina_list_nth(ts_msg, 4);
		if (temp_last_msg_date) {
			peer_info->last_msg_date = *temp_last_msg_date;
			free(temp_last_msg_date);
		}

		char *temp_print_name = (char*)eina_list_nth(ts_msg, 5);
		if (temp_print_name) {
			peer_info->print_name  = strdup(temp_print_name);
			free(temp_print_name);
		}

		int *temp_struct_ver = (int*)eina_list_nth(ts_msg, 6);
		if (temp_struct_ver) {
			peer_info->struct_version = *temp_struct_ver;
			free(temp_struct_ver);
		}

		int *temp_no_unread = (int*)eina_list_nth(ts_msg, 7);
		if (temp_no_unread) {
			peer_info->no_of_unread_msgs = *temp_no_unread;
			free(temp_no_unread);
		}

		int *temp_last_seen = (int*)eina_list_nth(ts_msg, 8);
		if (temp_last_seen) {
			peer_info->last_seen_time = *temp_last_seen;
			free(temp_last_seen);
		}

		char *temp_pic_path = (char*)eina_list_nth(ts_msg, 9);
		if (temp_pic_path) {
			peer_info->photo_path = strdup(temp_pic_path);
			free(temp_pic_path);
		}

		int *temp_pic_id = (int*)eina_list_nth(ts_msg, 10);
		if (temp_pic_id) {
			peer_info->photo_id = *temp_pic_id;
			free(temp_pic_id);
		}


		eina_list_free(ts_msg);

		peer_with_pic_s *item = (peer_with_pic_s*) malloc(sizeof (peer_with_pic_s));
		item->use_data = peer_info;
		item->contact_icon = NULL;

		if (peer_info->last_msg_id > 0) {
			// get message from message table.

			char* tablename = get_table_name_from_number(peer_info->peer_id);
			tg_message_s* msg = get_message_from_message_table(peer_info->last_msg_id, tablename);

			if (msg) {
				int media_type = msg->media_type;
				if(media_type == tgl_message_media_none) {
					if (msg->message && strlen(msg->message) > 0) {
						item->last_message = strdup(msg->message);
					} else {
						item->last_message = strdup(" ");
					}
				} else if(media_type == tgl_message_media_photo) {
					item->last_message = strdup("Image");
				} else if(media_type == tgl_message_media_document) {
					item->last_message = strdup("Document");
				} else if(media_type == tgl_message_media_geo) {
					item->last_message = strdup("Geo location");
				} else if(media_type == tgl_message_media_contact) {
					item->last_message = strdup("Contact");
				} else if(media_type == tgl_message_media_unsupported) {
					item->last_message = strdup(" ");
				} else if(media_type == tgl_message_media_photo_encr) {
					item->last_message = strdup("Image encrypted");
				} else if(media_type == tgl_message_media_document_encr) {
					item->last_message = strdup("Document encrypted");
				} else  {
					item->last_message = strdup(" ");
				}

				// delete message object

				if(msg->message) {
					free(msg->message);
					msg->message = NULL;
				}

				if(msg->media_id) {
					free(msg->media_id);
					msg->media_id = NULL;
				}

				free(msg);
				msg = NULL;

			} else {
				item->last_message = strdup(" ");
			}

			if (tablename) {
				free(tablename);
				tablename = NULL;
			}

		}

		ad->peer_list = eina_list_append(ad->peer_list, item);
	}
	eina_list_free(peer_details);
}

void load_group_chat_data(appdata_s *ad)
{
	if (!ad) {
		return;
	}
	if (ad->group_chat_list) {
		for (int i = 0; i < eina_list_count(ad->group_chat_list) ; i++) {
			group_chat_with_pic_s* pic_item = eina_list_nth(ad->group_chat_list, i);
			tg_chat_info_s* item = pic_item->use_data;
			if (item) {
				if (item->photo_path) {
					free(item->photo_path);
					item->photo_path = NULL;
				}
				if (item->print_title) {
					free(item->print_title);
					item->print_title = NULL;
				}
				if (item->title) {
					free(item->title);
					item->title = NULL;
				}
				free(item);
			}
			free(pic_item);
		}
		eina_list_free(ad->group_chat_list);
	}
	ad->group_chat_list = NULL;
	Eina_List* chat_details = get_group_chat_details();

	for (int i = 0; i < eina_list_count(chat_details) ; i++) {
		Eina_List* ts_msg = eina_list_nth(chat_details, i);

		tg_chat_info_s* chat_info = (tg_chat_info_s*)malloc(sizeof(tg_chat_info_s));


		int *temp_chat_id = (int*)eina_list_nth(ts_msg, 0);
		if (temp_chat_id) {
			chat_info->chat_id  = *temp_chat_id;
			free(temp_chat_id);
		}

		int *temp_flags = (int*)eina_list_nth(ts_msg, 1);
		if (temp_flags) {
			chat_info->flags  = *temp_flags;
			free(temp_flags);
		}

		char *temp_print_title = (char*)eina_list_nth(ts_msg, 2);
		if (temp_print_title) {
			chat_info->print_title  = strdup(temp_print_title);
			free(temp_print_title);
		}

		int *temp_struct_ver = (int*)eina_list_nth(ts_msg, 3);
		if (temp_struct_ver) {
			chat_info->struct_version  = *temp_struct_ver;
			free(temp_struct_ver);
		}

		char *temp_photo_id = (char*)eina_list_nth(ts_msg, 4);
		if (temp_photo_id) {
			chat_info->photo_id  = atoll(temp_photo_id);
			free(temp_photo_id);
		}

		char *temp_photo_path = (char*)eina_list_nth(ts_msg, 5);
		if (temp_photo_path) {
			chat_info->photo_path  = strdup(temp_photo_path);
			free(temp_photo_path);
		}

		char *temp_title = (char*)eina_list_nth(ts_msg, 6);
		if (temp_title) {
			chat_info->title  = strdup(temp_title);
			free(temp_title);
		}

		int *temp_users_num = (int*)eina_list_nth(ts_msg, 7);
		if (temp_users_num) {
			chat_info->users_num  = *temp_users_num;
			free(temp_users_num);
		}

		int *temp_user_list_size = (int*)eina_list_nth(ts_msg, 8);
		if (temp_user_list_size) {
			chat_info->user_list_size  = *temp_user_list_size;
			free(temp_user_list_size);
		}

		int *temp_user_list_version = (int*)eina_list_nth(ts_msg, 9);
		if (temp_user_list_version) {
			chat_info->user_list_version  = *temp_user_list_version;
			free(temp_user_list_version);
		}

		int *temp_inviter_id = (int*)eina_list_nth(ts_msg, 10);
		if (temp_inviter_id) {
			chat_info->inviter_id  = *temp_inviter_id;
			free(temp_inviter_id);
		}

		char *temp_full_ids = (char*)eina_list_nth(ts_msg, 11);
		if (temp_full_ids) {
			char* item = strtok(temp_full_ids, ",");
			int count = 0;
			chat_info->chat_users[count] = atoi(item);

			while (item != NULL) {
				count++;
				item = strtok(NULL, ",");
				if (item != NULL) {
					chat_info->chat_users[count] = atoi(item);
				}
			}
			free(temp_full_ids);
		}

		int *temp_date = (int*)eina_list_nth(ts_msg, 12);
		if (temp_date) {
			chat_info->date  = *temp_date;
			free(temp_date);
		}

		int *temp_version = (int*)eina_list_nth(ts_msg, 13);
		if (temp_version) {
			chat_info->version  = *temp_version;
			free(temp_version);
		}

		int *temp_admin_id = (int*)eina_list_nth(ts_msg, 14);
		if (temp_admin_id) {
			chat_info->admin_id  = *temp_admin_id;
			free(temp_admin_id);
		}
		eina_list_free(ts_msg);

		group_chat_with_pic_s *item = (group_chat_with_pic_s*) malloc(sizeof (group_chat_with_pic_s));
		item->use_data = chat_info;
		item->contact_icon = NULL;
		ad->group_chat_list = eina_list_append(ad->group_chat_list, item);
	}

	eina_list_free(chat_details);
}

void load_buddy_list_data(appdata_s *ad)
{
	if (!ad) {
		return;
	}

	if (ad->buddy_list) {

		for (int i = 0; i < eina_list_count(ad->buddy_list) ; i++) {
			user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
			user_data_s* user_data = item->use_data;

			if (user_data->print_name) {
				free(user_data->print_name);
				user_data->print_name = NULL;
			}

			if (user_data->photo_path) {
				free(user_data->photo_path);
				user_data->photo_path = NULL;
			}

			if (user_data->first_name) {
				free(user_data->first_name);
				user_data->first_name = NULL;
			}

			if (user_data->last_name) {
				free(user_data->last_name);
				user_data->last_name = NULL;
			}

			if (user_data->phone) {
				free(user_data->phone);
				user_data->phone = NULL;
			}
			if (user_data->real_first_name) {
				free(user_data->real_first_name);
				user_data->real_first_name = NULL;
			}

			if (user_data->real_last_name) {
				free(user_data->real_last_name);
				user_data->real_last_name = NULL;
			}

			if (user_data->username) {
				free(user_data->username);
				user_data->username = NULL;
			}
			free(user_data);
			free(item);
		}

		eina_list_free(ad->buddy_list);
		ad->buddy_list = NULL;
	}

	Eina_List* user_info = get_buddy_list_info();

	if(!user_info) {
		//error
		show_toast(ad, "User info not loaded");
		return;
	}

	int row_count = eina_list_count(user_info);

	for (int i = 0 ; i < row_count ; i++) {
		Eina_List* row_vals = eina_list_nth(user_info, i);

		user_data_s* user_data = (user_data_s*)malloc(sizeof(user_data_s));
		user_data->is_selected = EINA_FALSE;

		int *temp_user_id = (int*)eina_list_nth(row_vals, 0);
		if (temp_user_id) {
			user_data->user_id.id = *temp_user_id;
			user_data->user_id.type = TGL_PEER_USER;
			free(temp_user_id);
		}

		char *print_name = (char*)eina_list_nth(row_vals, 1);
		if(print_name) {
			user_data->print_name = strdup(print_name);
			free(print_name);
		} else {
			user_data->print_name = NULL;
		}

		int *temp_struct_ver = (int*)eina_list_nth(row_vals, 2);
		if(temp_struct_ver) {
			user_data->structure_version = *temp_struct_ver;
			free(temp_struct_ver);
		}

		char *photo_path = (char*)eina_list_nth(row_vals, 3);
		if(photo_path) {
			user_data->photo_path = strdup(photo_path);
			free(photo_path);
		} else {
			user_data->photo_path = NULL;
		}


		int *temp_photo_id = (int*)eina_list_nth(row_vals, 4);
		if(temp_photo_id) {
			user_data->photo_id = *temp_photo_id;
			free(temp_photo_id);
		}

		char *first_name = (char*)eina_list_nth(row_vals, 5);
		if(first_name) {
			user_data->first_name = strdup(first_name);
			free(first_name);
		} else {
			user_data->first_name = NULL;
		}

		char *last_name = (char*)eina_list_nth(row_vals, 6);
		if(last_name) {
			user_data->last_name = strdup(last_name);
			free(last_name);
		} else {
			user_data->last_name = NULL;
		}

		char *phone_no = (char*)eina_list_nth(row_vals, 7);
		if(phone_no) {
			user_data->phone = strdup(phone_no);
			free(phone_no);
		} else {
			user_data->phone = NULL;
		}

		int *temp_access_hash = (int*)eina_list_nth(row_vals, 8);
		if(temp_access_hash) {
			user_data->access_hash = *temp_access_hash;
			free(temp_access_hash);
		}

		char *real_first_name = (char*)eina_list_nth(row_vals, 9);
		if(real_first_name) {
			user_data->real_first_name = strdup(real_first_name);
			free(real_first_name);
		} else {
			user_data->real_first_name = NULL;
		}

		char *real_last_name = (char*)eina_list_nth(row_vals, 10);
		if(real_last_name) {
			user_data->real_last_name = strdup(real_last_name);
			free(real_last_name);
		} else {
			user_data->real_last_name = NULL;
		}

		char *user_name = (char*)eina_list_nth(row_vals, 11);
		if(user_name) {
			user_data->username = strdup(user_name);
			free(user_name);
		} else {
			user_data->username = NULL;
		}

		int *temp_online_status = (int*)eina_list_nth(row_vals, 12);
		if(temp_online_status) {
			user_data->online = *temp_online_status;
			free(temp_online_status);
		}

		int *temp_last_seen = (int*)eina_list_nth(row_vals, 13);
		if(temp_last_seen) {
			user_data->last_seen = *temp_last_seen;
			free(temp_last_seen);
		}

		user_data_with_pic_s *item = (user_data_with_pic_s*) malloc(sizeof (user_data_with_pic_s));
		item->use_data = user_data;
		//item->pic_file_location = NULL;
		item->contact_icon = NULL;
		ad->buddy_list = eina_list_append(ad->buddy_list, item);

		eina_list_free(row_vals);

	}
	eina_list_free(user_info);
}

static int _on_service_client_msg_received_cb(void *data, bundle *const rec_msg)
{
	int result = SVC_RES_FAIL;
	RETVM_IF(!data, result, "Data is NULL");
	appdata_s *app = data;
	char *rec_key_val = NULL;

	result = bundle_get_str(rec_msg, "command", &rec_key_val);

	if (strcmp(rec_key_val, "registration_done") == 0) {
		char* is_success_val = NULL;
		result = bundle_get_str(rec_msg, "is_success", &is_success_val);

		if (strncmp("true", is_success_val, strlen("true")) == 0) {
			show_toast(app, is_success_val);
			// Launch login view
			elm_naviframe_item_pop(app->nf);
			launch_login_cb(data);
		} else {
			// error handling
			show_toast(app, "Error: registration");
		}

	} else if (strcmp(rec_key_val, "contacts_load_done") == 0) {
		char* is_success_val = NULL;
		result = bundle_get_str(rec_msg, "is_success", &is_success_val);
		if (strncmp("true", is_success_val, strlen("true")) == 0) {

			// Load user data
			Eina_List* user_info = get_registered_user_info();
			load_registered_user_data(app, user_info);

			if (app->current_app_state == TG_LOGIN_STATE || app->current_app_state == TG_REGISTRATION_STATE || app->current_app_state == TG_PROFILE_REGISTRATION_STATE) {
				// Launch buddy list view
				load_buddy_list_data(app);
				load_group_chat_data(app);
				load_peer_data(app);
				elm_naviframe_item_pop(app->nf);

				//launch_buddy_list_cb(app);

				launch_user_main_view_cb(app);



			} else if (app->current_app_state == TG_BUDDY_LIST_STATE) {
				////refresh_buddy_list(app);
			} else {

			}

		} else {
			// error handling
			show_toast(app, "Error: loading contacts");
		}
	} else if (strcmp(rec_key_val, "contacts_and_chats_load_done") == 0) {
		char* is_success_val = NULL;
		result = bundle_get_str(rec_msg, "is_success", &is_success_val);
		if (strncmp("true", is_success_val, strlen("true")) == 0) {

			// Load user data
			Eina_List* user_info = get_registered_user_info();
			load_registered_user_data(app, user_info);

			if (app->current_app_state == TG_LOGIN_STATE || app->current_app_state == TG_REGISTRATION_STATE || app->current_app_state == TG_PROFILE_REGISTRATION_STATE) {
				// Launch buddy list view
				load_buddy_list_data(app);
				load_group_chat_data(app);
				load_peer_data(app);
				elm_naviframe_item_pop(app->nf);
				//launch_buddy_list_cb(app);
				launch_user_main_view_cb(app);
			} else if (app->current_app_state == TG_BUDDY_LIST_STATE) {
				app->current_app_state = TG_BUDDY_LIST_STATE;
				evas_object_show(app->panel);
				elm_panel_hidden_set(app->panel, EINA_FALSE);
				////refresh_buddy_list(app);
			} else {

			}

		} else {
			// error handling
			show_toast(app, "Error: loading contacts");
		}
	} else if (strcmp(rec_key_val, "buddy_profile_pic_updated") == 0) {
		char* user_id_str = NULL;
		result = bundle_get_str(rec_msg, "user_id", &user_id_str);
		int user_id = atoi(user_id_str);

		char* pic_file_path = NULL;
		result = bundle_get_str(rec_msg, "file_path", &pic_file_path);

		// update profile pic if buddy list view is present.
		if(user_id == app->user_id.id) {
			// registerd user.
			// to be handled
		} else {
#if 0
			// update buddy list in appdata.
			if(app->buddy_list) {
				int size = eina_list_count(app->buddy_list);
				for (int i = 0 ; i < size ; i++) {
					user_data_with_pic_s *item = eina_list_nth(app->buddy_list, i);
					if (item->use_data->user_id.id == user_id) {
						item->use_data->photo_path = strdup(pic_file_path);
						if (item->contact_icon) {
							elm_image_file_set(item->contact_icon, pic_file_path, NULL);
						}
						break;
					}
				}
			}
#else
			if(app->peer_list) {
				int size = eina_list_count(app->peer_list);
				for (int i = 0 ; i < size ; i++) {
					peer_with_pic_s *item = eina_list_nth(app->peer_list, i);
					if (item->use_data->peer_id == user_id) {
						item->use_data->photo_path = strdup(pic_file_path);
						if (item->contact_icon) {
							elm_image_file_set(item->contact_icon, pic_file_path, NULL);
						}
						break;
					}
				}
			}

#endif
		}
	} else if (strcmp(rec_key_val, "message_received") == 0) {

		char* from_id_str = NULL;
		result = bundle_get_str(rec_msg, "from_id", &from_id_str);
		int from_id = atoi(from_id_str);

		char* to_id_str = NULL;
		result = bundle_get_str(rec_msg, "to_id", &to_id_str);
		int to_id = atoi(to_id_str);

		char* msg_id_str = NULL;
		result = bundle_get_str(rec_msg, "message_id", &msg_id_str);
		long long message_id = atoll(msg_id_str);

		char* type_of_chat_str = NULL;
		result = bundle_get_str(rec_msg, "type_of_chat", &type_of_chat_str);
		int type_of_chat = atoi(type_of_chat_str);




		if (from_id == app->user_id.id) {
			// sent by the user. May be from another device.
		}

		//load message from the received info.
		// get phone number using buddy id.

		if (type_of_chat == TGL_PEER_USER) {
			if (app->current_app_state ==  TG_CHAT_MESSAGING_VIEW_STATE && app->buddy_in_cahtting_data
					&& app->buddy_in_cahtting_data->use_data->user_id.id == from_id) {
				on_text_message_received_from_buddy(app, message_id, type_of_chat);
			}
		} else if (type_of_chat == TGL_PEER_CHAT) {
			if (app->current_app_state ==  TG_CHAT_MESSAGING_VIEW_STATE && app->buddy_in_cahtting_data
					&& app->buddy_in_cahtting_data->use_data->user_id.id == to_id) {
				char* tablename = get_table_name_from_number(to_id);
				tg_message_s* msg = get_message_from_message_table(message_id, tablename);
				if (msg) {
					on_chat_buddy_msg_receive(msg, type_of_chat);
				}
				if(msg->message) {
					free(msg->message);
					msg->message = NULL;
				}

				if(msg->media_id) {
					free(msg->media_id);
					msg->media_id = NULL;
				}
				free(tablename);
				free(msg);
			}

		}

	} else if (strcmp(rec_key_val, "message_sent_to_buddy") == 0) {
		char* buddy_id_str = NULL;
		result = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
		int buddy_id = atoi(buddy_id_str);

		char* msg_id_str = NULL;
		result = bundle_get_str(rec_msg, "message_id", &msg_id_str);
		int message_id = atoi(msg_id_str);

		char* table_name = NULL;
		result = bundle_get_str(rec_msg, "table_name", &table_name);

		char* phone_number = NULL;
		result = bundle_get_str(rec_msg, "phone_number", &phone_number);

		char* type_of_chat_str = NULL;
		result = bundle_get_str(rec_msg, "type_of_chat", &type_of_chat_str);
		int type_of_chat = atoi(type_of_chat_str);

		tg_message_s* msg = get_message_from_message_table(message_id, table_name);

		if (msg && app->current_app_state ==  TG_CHAT_MESSAGING_VIEW_STATE && app->buddy_in_cahtting_data
				&& app->buddy_in_cahtting_data->use_data->user_id.id == buddy_id) {
			// update message to sent state
			on_text_message_state_changed(app, msg, type_of_chat);
		}
		if (msg) {
			if(msg->message) {
				free(msg->message);
				msg->message = NULL;
			}

			if(msg->media_id) {
				free(msg->media_id);
				msg->media_id = NULL;
			}
			free(msg);
		}
	} else if (strcmp(rec_key_val, "message_read_by_buddy") == 0) {
		char* buddy_id_str = NULL;
		result = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
		int buddy_id = atoi(buddy_id_str);

		char* msg_id_str = NULL;
		result = bundle_get_str(rec_msg, "message_id", &msg_id_str);
		int message_id = atoi(msg_id_str);

		char* table_name = NULL;
		result = bundle_get_str(rec_msg, "table_name", &table_name);

		char* phone_number = NULL;
		result = bundle_get_str(rec_msg, "phone_number", &phone_number);

		char* type_of_chat_str = NULL;
		result = bundle_get_str(rec_msg, "type_of_chat", &type_of_chat_str);
		int type_of_chat = atoi(type_of_chat_str);

		tg_message_s* msg = get_message_from_message_table(message_id, table_name);

		if (msg && app->current_app_state ==  TG_CHAT_MESSAGING_VIEW_STATE && app->buddy_in_cahtting_data
				&& app->buddy_in_cahtting_data->use_data->user_id.id == buddy_id) {

			// update message to sent state
			on_text_message_state_changed(app, msg, type_of_chat);
		}
		if (msg) {
			if(msg->message) {
				free(msg->message);
				msg->message = NULL;
			}

			if(msg->media_id) {
				free(msg->media_id);
				msg->media_id = NULL;
			}
			free(msg);
		}
	} else if (strcmp(rec_key_val, "media_download_completed") == 0) {

		char* buddy_id_str = NULL;
		result = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
		int buddy_id = atoi(buddy_id_str);

		char* media_id_str = NULL;
		result = bundle_get_str(rec_msg, "media_id", &media_id_str);
		long long media_id = atoll(media_id_str);

		char* file_name = NULL;
		result = bundle_get_str(rec_msg, "file_name", &file_name);

		if (file_name && app->current_app_state ==  TG_CHAT_MESSAGING_VIEW_STATE && app->buddy_in_cahtting_data
				&& app->buddy_in_cahtting_data->use_data->user_id.id == buddy_id) {
			// update media to sent state
			on_media_download_completed(app, buddy_id, media_id, file_name);
		}
	} else if (strcmp(rec_key_val, "name_registration_request") == 0) {

		launch_first_registration_cb(app);

	} else if (strcmp(rec_key_val, "add_contacts_request") == 0) {

		// load contacts

		if(sc_db_utils_connect())
		{
			Eina_List* contacts_list = get_contact_list_from_device_db();
			sc_db_utils_disconnect();

			if (!contacts_list || eina_list_count(contacts_list) <= 0) {
				// no contacts avilable. empty contact list.
				return result;
			}
			send_contacts_list_to_server(app->service_client, contacts_list);

			for (int i = 0; i < eina_list_count(contacts_list) ; i++) {
				contact_data_s* contact_data = eina_list_nth(contacts_list, i);
				if (contact_data->display_name) {
					free(contact_data->display_name);
					contact_data->display_name = NULL;
				}

				if (contact_data->first_name) {
					free(contact_data->first_name);
					contact_data->first_name = NULL;
				}

				if (contact_data->last_name) {
					free(contact_data->last_name);
					contact_data->last_name = NULL;
				}

				if (contact_data->phone_number) {
					free(contact_data->phone_number);
					contact_data->phone_number = NULL;
				}
				free(contact_data);
			}
			eina_list_free(contacts_list);
		}
	} else if (strcmp(rec_key_val, "new_group_added") == 0) {

		char* chat_id_str = NULL;
		result = bundle_get_str(rec_msg, "chat_id", &chat_id_str);
		int chat_id = atoi(chat_id_str);

#if 0
		// get group chat details from database.(chat info)
		// tg_chat_info_s* chat_info = get_chat_info(chat_id);

		load_buddy_list_data(app);
		load_group_chat_data(app);
		load_peer_data(app);

		if (app->current_app_state == TG_BUDDY_LIST_STATE) {
			//refresh_buddy_list(app);
			show_toast(app, "new group created");
		} else {
			elm_naviframe_item_pop(app->nf);
			//refresh_buddy_list(app);
		}
#else
		if (app->buddy_list) {
			for (int i = 0 ; i < eina_list_count(app->buddy_list) ; i++) {
				user_data_with_pic_s *item = eina_list_nth(app->buddy_list, i);
				user_data_s* user = item->use_data;
				user->is_selected = EINA_FALSE;
			}
		}
		elm_naviframe_item_pop(app->nf);
		app->current_app_state = TG_BUDDY_LIST_STATE;
		evas_object_show(app->panel);
		elm_panel_hidden_set(app->panel, EINA_FALSE);
		//refresh_buddy_list(app);
		show_toast(app, "new group created");
#endif
	} else if (strcmp(rec_key_val, "contact_updated") == 0) {


		char* buddy_id_str = NULL;
		result = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
		int buddy_id = atoi(buddy_id_str);

		char* update_msg = NULL;
		result = bundle_get_str(rec_msg, "update_message", &update_msg);
		show_toast(app, update_msg);
	} else if (strcmp(rec_key_val, "buddy_status_updated") == 0) {
		char* buddy_id_str = NULL;
		result = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
		int buddy_id = atoi(buddy_id_str);
		// update to online or last seen, if current view is conversation.

		// sandeep
		if (app->current_app_state ==  TG_CHAT_MESSAGING_VIEW_STATE && app->buddy_in_cahtting_data && app->buddy_in_cahtting_data->use_data->user_id.id == buddy_id) {
			on_user_presence_state_changed(app, buddy_id);
		}

	} else if (strcmp(rec_key_val, "type_status_updated") == 0) {

		char* buddy_id_str = NULL;
		result = bundle_get_str(rec_msg, "buddy_id", &buddy_id_str);
		int buddy_id = atoi(buddy_id_str);

		char* buddy_name = NULL;
		result = bundle_get_str(rec_msg, "buddy_name", &buddy_name);

		char* type_status_str = NULL;
		result = bundle_get_str(rec_msg, "type_status", &type_status_str);
		enum tgl_typing_status type_status = atoi(type_status_str);

		// update UI
		char* type_status_message = NULL;

		switch (type_status) {
			case tgl_typing_none:
				type_status_message = (char*)malloc(strlen("doing nothing") + 1);
				strcpy(type_status_message, "doing nothing");
				break;
			case tgl_typing_typing:
				type_status_message = (char*)malloc(strlen("typing") + 1);
				strcpy(type_status_message, "typing");
				break;
			case tgl_typing_cancel:
				type_status_message = (char*)malloc(strlen("deleting typed message") + 1);
				strcpy(type_status_message, "deleting typed message");
				break;
			case tgl_typing_record_video:
				type_status_message = (char*)malloc(strlen("recording video") + 1);
				strcpy(type_status_message, "recording video");
				break;
			case tgl_typing_upload_video:
				type_status_message = (char*)malloc(strlen("uploading video") + 1);
				strcpy(type_status_message, "uploading video");
				break;
			case tgl_typing_record_audio:
				type_status_message = (char*)malloc(strlen("recording audio") + 1);
				strcpy(type_status_message, "recording audio");
				break;
			case tgl_typing_upload_audio:
				type_status_message = (char*)malloc(strlen("uploading audio") + 1);
				strcpy(type_status_message, "uploading audio");
				break;
			case tgl_typing_upload_photo:
				type_status_message = (char*)malloc(strlen("uploading photo") + 1);
				strcpy(type_status_message, "uploading photo");
				break;
			case tgl_typing_upload_document:
				type_status_message = (char*)malloc(strlen("uploading document") + 1);
				strcpy(type_status_message, "uploading document");
				break;
			case tgl_typing_geo:
				type_status_message = (char*)malloc(strlen("choosing location") + 1);
				strcpy(type_status_message, "choosing location");
				break;
			case tgl_typing_choose_contact:
				type_status_message = (char*)malloc(strlen("choosing contact") + 1);
				strcpy(type_status_message, "choosing contact");
				break;
		}

		// update UI. may be contacts view or conversation view.


		if (type_status_message) {
			free(type_status_message);
			type_status_message = NULL;
		}

	} else {

	}
	return result;
}

int init_service(appdata_s *app)
{
	int result = SVC_RES_FAIL;
	RETVM_IF(!app, result, "Application data is NULL");

	app->service_client = service_client_create();
	RETVM_IF(!app->service_client, result, "Failed to create service client");

	result = service_client_register_port(app->service_client, TELEGRAM_CLIENT_PORT_NAME);
	if (result != SVC_RES_OK)
	{
		ERR("Failed to register service client port");
		service_client_destroy(app->service_client);
		app->service_client = NULL;
		return result;
	}

	result = _service_client_set_remote_data(app->service_client, TELEGRAM_SERVER_APP_NAME, TELEGRAM_SERVER_PORT_NAME);

	result = service_client_register_msg_receive_callback(app->service_client, _on_service_client_msg_received_cb, app);
	if (result != SVC_RES_OK)
	{
		ERR("Failed to register service client on message receive callback");
		service_client_destroy(app->service_client);
		app->service_client = NULL;
		return result;
	}
	return result;
}

void win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

void app_nf_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	switch(ad->current_app_state) {
		case TG_INIT_SCREEN_STATE:
			elm_win_lower(ad->win);
			elm_exit();
			break;
		case TG_USER_MAIN_VIEW_STATE:
			elm_win_lower(ad->win);
			elm_exit();
			break;
		case TG_CHAT_MESSAGING_VIEW_STATE:
			elm_naviframe_item_pop(ad->nf);
			ad->current_app_state = TG_START_MESSAGING_VIEW_STATE;
			break;
		case TG_START_MESSAGING_VIEW_STATE:
			elm_naviframe_item_pop(ad->nf);
			ad->current_app_state = TG_USER_MAIN_VIEW_STATE;
			break;
		case TG_REGISTRATION_STATE:
			elm_win_lower(ad->win);
			elm_exit();
			break;
		case TG_LOGIN_STATE:

			if (ad->timer_value > 0) {
				Ecore_Timer* timer = evas_object_data_get(ad->nf, "code_timer");
				if (timer)
					ecore_timer_del(timer);
			}

			elm_naviframe_item_pop(ad->nf);
			ad->current_app_state = TG_REGISTRATION_STATE;
			break;
		case TG_PROFILE_REGISTRATION_STATE:
			/*			ad->current_app_state = TG_REGISTRATION_STATE;
						elm_naviframe_item_pop(ad->nf);*/
			elm_win_lower(ad->win);
			elm_exit();
			break;
		case TG_BUDDY_LIST_STATE:
			evas_object_data_set(ad->nf, "buddy_list", NULL);
			elm_win_lower(ad->win);
			elm_exit();
			break;
		case TG_BUDDY_CHAT_CONV_STATE:
			ad->buddy_in_cahtting_data = NULL;
			if (ad->loaded_msg_list) {
				eina_list_free(ad->loaded_msg_list);
				ad->loaded_msg_list = NULL;
			}
			elm_naviframe_item_pop(ad->nf);
			ad->current_app_state = TG_BUDDY_LIST_STATE;
			//evas_object_show(ad->panel);
			//refresh_buddy_list(ad);
			break;
		case TG_BUDDY_LIST_SELECTION_STATE:
			if (ad->buddy_list) {
				for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
					user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
					user_data_s* user = item->use_data;
					user->is_selected = EINA_FALSE;
				}
			}
			elm_naviframe_item_pop(ad->nf);
			ad->current_app_state = TG_BUDDY_LIST_STATE;
			evas_object_show(ad->panel);
			elm_panel_hidden_set(ad->panel, EINA_FALSE);
			//refresh_buddy_list(ad);
			break;
		case TG_GROUP_CHAT_NAME_ENTRY_STATE:
			if (ad->buddy_list) {
				for (int i = 0 ; i < eina_list_count(ad->buddy_list) ; i++) {
					user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
					user_data_s* user = item->use_data;
					user->is_selected = EINA_FALSE;
				}
			}
			elm_naviframe_item_pop(ad->nf);
			ad->current_app_state = TG_BUDDY_LIST_STATE;
			evas_object_show(ad->panel);
			elm_panel_hidden_set(ad->panel, EINA_FALSE);
			//refresh_buddy_list(ad);
			break;
		default:
			break;
	}
}

void
layout_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}

void _btn_clicked(void* data, Evas_Object* btn, void* ev)
{
	appdata_s *ad = data;
	bundle *msg = bundle_create();
	if (bundle_add_str(msg, "tizen_app", "Hello service") != 0)
	{
		ERR("Failed to add data by key to bundle");
		bundle_free(msg);
	}

	int result = _app_send_response(ad, msg);
	if(result != SVC_RES_OK)
	{
		bundle_free(msg);
	}
	bundle_free(msg);
}

static void create_base_gui(appdata_s *ad)
{

	struct stat st = {0};

	if (stat(DEFAULT_TELEGRAM_PATH, &st) == -1) {
		mkdir(DEFAULT_TELEGRAM_PATH, S_IRWXU);
	}

	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_conformant_set(ad->win, EINA_TRUE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_app_base_scale_set(1.8);

	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
	}

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_CUSTOM_WINSET_EDJ, edj_path, (int)PATH_MAX);

	elm_theme_extension_add(NULL, edj_path);
	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);

	ad->conform = elm_conformant_add(ad->win);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);

	ad->layout = elm_layout_add(ad->conform);
	evas_object_size_hint_weight_set(ad->layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	elm_layout_theme_set(ad->layout, "layout", "drawer", "panel");
	evas_object_show(ad->layout);

	elm_object_content_set(ad->conform, ad->layout);
	ad->nf = elm_naviframe_add(ad->layout);

	ad->current_app_state = TG_SPLASH_SCREEN_STATE;
	launch_splash_screen_cb(ad);
	create_data_base_tables();
	elm_object_part_content_set(ad->layout, "elm.swallow.content", ad->nf);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_BACK, app_nf_back_cb, ad);

	evas_object_show(ad->win);


	// check for user info

	Eina_List* user_info = get_registered_user_info();

	if (!user_info) {
		elm_naviframe_item_pop(ad->nf);
		ad->current_app_state = TG_REGISTRATION_STATE;
		launch_init_screen(ad);
		//launch_user_main_view_cb(ad);
	} else {
		//show_toast(ad, "user already registered");
		load_registered_user_data(ad, user_info);
		load_buddy_list_data(ad);
		load_group_chat_data(ad);
		load_peer_data(ad);
		// Launch buddy list view
		elm_naviframe_item_pop(ad->nf);
		//launch_buddy_list_cb(ad);
		launch_user_main_view_cb(ad);
	}
	//eina_list_free(user_info);
}

static bool
app_create(void *data)
{
	/*
	   Hook to take necessary actions before main event loop starts
	   Initialize UI resources and application's data
	   If this function returns true, the main loop of application starts
	   If this function returns false, the application is terminated
	 */

	appdata_s *ad = data;
	ad->phone_number = NULL;
	ad->buddy_list = NULL;
	ad->is_first_time_registration = EINA_FALSE;
	ad->panel = NULL;
	ad->loaded_msg_list = NULL;
	create_base_gui(ad);
	init_service(ad);
	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */
	appdata_s* app_data = data;
	if(app_data->service_client) {
		service_client_destroy(app_data->service_client);
		app_data->service_client = NULL;
	}
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);
	ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_main() is failed. err = %d", ret);
	}

	return ret;
}
