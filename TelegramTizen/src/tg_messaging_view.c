/*
 * tg_messaging_view.c
 *
 *  Created on: Aug 22, 2015
 *      Author: sandeep
 */

#include "tg_messaging_view.h"
#include "tg_db_wrapper.h"
#include "server_requests.h"
#include <attach_panel.h>
#include <mime_type.h>
#include <Elementary.h>
#include "tg_user_info_view.h"
#include "tg_chat_info_view.h"
#include "tg_audio_player.h"
#include <metadata_extractor.h>
#include "tg_search_peer_view.h"

static int scroller_show_bottom_edge(Evas_Object *scroller)
{
	if (!scroller) {
		LOGE("Cannot get the scroller");
		return 0;
	}
	Evas_Object *box_layout = NULL;
	Evas_Object *box = NULL;
	Eina_List *list = NULL;

	box_layout = elm_object_content_get(scroller);
	if (!box_layout) {
		LOGE("Fail to get the box into scroller");
		return 0;
	}
	list = elm_box_children_get(box_layout);
	if (!list) {
		LOGE("Fail to get the list into box");
		return 0;
	}

	box = eina_list_nth(list, 0);
	if (!box) {
		LOGE("Fail to get the box into box layout");
		return 0;
	}

	int h;
	evas_object_geometry_get(box, NULL, NULL, NULL, &h);
	elm_scroller_region_show(scroller, 0, h, 720, 1280);

	eina_list_free(list);

	return 1;
}

static void scroller_push_item(Evas_Object *scroller, Evas_Object *item)
{
	Evas_Object *box_layout = NULL;
	Evas_Object *box = NULL;
	Eina_List *list = NULL;

	box_layout = elm_object_content_get(scroller);
	if (!box_layout) {
		LOGE("Fail to get the box into scroller");
		return;
	}

	list = elm_box_children_get(box_layout);
	if (!list) {
		LOGE("Fail to get the list into box");
		return;
	}

	box = eina_list_nth(list, 0);
	if (!box) {
		LOGE("Fail to get the box into box layout");
		return;
	}

	eina_list_free(list);

	elm_box_pack_end(box, item);
	//elm_box_recalculate(box);

	return;
}

/************************ Menu Handler ********************/

void on_messaging_menu_option_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	int id = (int)elm_object_item_data_get(it);


	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	tg_peer_info_s *user_data = sel_item->use_data;

	if (!sel_item || !user_data) {
		show_toast(ad, "There are no messages to delete.");
		if (ad->msg_popup) {
			evas_object_del(ad->msg_popup);
			ad->msg_popup = NULL;
		}
		return;
	}


	if (get_buddy_unknown_status(user_data->peer_id) && user_data->peer_type == TGL_PEER_USER) {

		if (id == 0) {
			ad->is_loading_from_msg_view = EINA_TRUE;
			on_create_new_contact(ad);
		} else if (id == 1) {
#if 0
			char* tablename = get_table_name_from_number(user_data->peer_id);
			delete_all_records(tablename);
			free(tablename);

			// clear all messages
			Evas_Object *genlist = evas_object_data_get(ad->nf, "chat_list");
			elm_genlist_clear(genlist);

			// remove main item from main list
			if (ad->main_item_in_cahtting_data) {
				tg_main_list_item_s* old_item = ad->main_item_in_cahtting_data;
				if (old_item->peer_print_name) {
					free(old_item->peer_print_name);
					old_item->peer_print_name = NULL;
				}
				if (old_item->last_message) {
					free(old_item->last_message);
					old_item->last_message = NULL;
				}
				if (old_item->profile_pic_path) {
					free(old_item->profile_pic_path);
					old_item->profile_pic_path = NULL;
				}
				old_item->date_lbl = NULL;
				old_item->msg_status_lbl = NULL;
				old_item->main_item_layout = NULL;
				old_item->profile_pic = NULL;
				old_item->profile_pic_path = NULL;
				old_item->status_lbl = NULL;
				old_item->user_name_lbl = NULL;
				ad->main_list = eina_list_remove(ad->main_list,  ad->main_item_in_cahtting_data);

				ad->main_item_in_cahtting_data = NULL;
			}
			ad->is_last_msg_changed = EINA_FALSE;
#else
			// mark all the massages for deletion.
			char* tablename = get_table_name_from_number(user_data->peer_id);
			mark_all_records_for_deletion(tablename);
			// delete date messages
			delete_date_messages_from_table(tablename);
			free(tablename);
			// clear screen
			// clear all messages
			Evas_Object *scroller = evas_object_data_get(ad->nf, "chat_list");


			Evas_Object *box_layout = NULL;
			Evas_Object *box = NULL;
			Eina_List *list = NULL;

			box_layout = elm_object_content_get(scroller);
			if (!box_layout) {
				LOGE("Fail to get the box into scroller");
				return;
			}

			list = elm_box_children_get(box_layout);
			if (!list) {
				LOGE("Fail to get the list into box");
				return;
			}

			box = eina_list_nth(list, 0);
			if (!box) {
				LOGE("Fail to get the box into box layout");
				return;
			}

			eina_list_free(list);
			elm_box_clear(box);
			elm_box_recalculate(box);


			// send request to server
			send_delete_group_chat_request(ad, ad->service_client, user_data->peer_id);

			if (ad->main_item_in_cahtting_data) {
				tg_main_list_item_s* old_item = ad->main_item_in_cahtting_data;
				if (old_item->last_message) {
					free(old_item->last_message);
					old_item->last_message = NULL;
				}
				old_item->last_message = strdup("");
			}

			Evas_Object *nomsg_layout = evas_object_data_del(ad->nf, "chat_list_no_msg_text");
			if (nomsg_layout) {
				elm_object_signal_emit(nomsg_layout, "show", "message");
			}
#endif
		} else {
			char* tablename = get_table_name_from_number(user_data->peer_id);
			delete_all_records(tablename);
			free(tablename);

			// clear all messages
			Evas_Object *genlist = evas_object_data_get(ad->nf, "chat_list");
			elm_genlist_clear(genlist);

			// remove main item from main list
			if (ad->main_item_in_cahtting_data) {
				tg_main_list_item_s* old_item = ad->main_item_in_cahtting_data;
				if (old_item->peer_print_name) {
					free(old_item->peer_print_name);
					old_item->peer_print_name = NULL;
				}
				if (old_item->last_message) {
					free(old_item->last_message);
					old_item->last_message = NULL;
				}
				if (old_item->profile_pic_path) {
					free(old_item->profile_pic_path);
					old_item->profile_pic_path = NULL;
				}
				old_item->date_lbl = NULL;
				old_item->msg_status_lbl = NULL;
				old_item->main_item_layout = NULL;
				old_item->profile_pic = NULL;
				old_item->profile_pic_path = NULL;
				old_item->status_lbl = NULL;
				old_item->user_name_lbl = NULL;
				ad->main_list = eina_list_remove(ad->main_list,  ad->main_item_in_cahtting_data);

				ad->main_item_in_cahtting_data = NULL;
			}

			ad->is_last_msg_changed = EINA_FALSE;


			app_nf_back_cb(ad, NULL, NULL);
		}
		if (ad->msg_popup) {
			evas_object_del(ad->msg_popup);
			ad->msg_popup = NULL;
		}
		return;
	}


	if (id == 1) { // Clear history
		if (user_data->peer_type == TGL_PEER_USER || user_data->peer_type == TGL_PEER_CHAT) {

#if 0
			char* tablename = get_table_name_from_number(user_data->peer_id);
			delete_all_records(tablename);
			free(tablename);

			// clear all messages
			Evas_Object *genlist = evas_object_data_get(ad->nf, "chat_list");
			elm_genlist_clear(genlist);

			// remove main item from main list
			if (ad->main_item_in_cahtting_data) {
				tg_main_list_item_s* old_item = ad->main_item_in_cahtting_data;
				if (old_item->peer_print_name) {
					free(old_item->peer_print_name);
					old_item->peer_print_name = NULL;
				}
				if (old_item->last_message) {
					free(old_item->last_message);
					old_item->last_message = NULL;
				}
				if (old_item->profile_pic_path) {
					free(old_item->profile_pic_path);
					old_item->profile_pic_path = NULL;
				}
				old_item->date_lbl = NULL;
				old_item->msg_status_lbl = NULL;
				old_item->main_item_layout = NULL;
				old_item->profile_pic = NULL;
				old_item->profile_pic_path = NULL;
				old_item->status_lbl = NULL;
				old_item->user_name_lbl = NULL;
				ad->main_list = eina_list_remove(ad->main_list,  ad->main_item_in_cahtting_data);

				ad->main_item_in_cahtting_data = NULL;
			}

			ad->is_last_msg_changed = EINA_FALSE;
#else
			// mark all the massages for deletion.
			char* tablename = get_table_name_from_number(user_data->peer_id);
			mark_all_records_for_deletion(tablename);
			// delete date messages
			delete_date_messages_from_table(tablename);
			free(tablename);
			// clear screen
			// clear all messages
			Evas_Object *scroller = evas_object_data_get(ad->nf, "chat_list");


			Evas_Object *box_layout = NULL;
			Evas_Object *box = NULL;
			Eina_List *list = NULL;

			box_layout = elm_object_content_get(scroller);
			if (!box_layout) {
				LOGE("Fail to get the box into scroller");
				return;
			}

			list = elm_box_children_get(box_layout);
			if (!list) {
				LOGE("Fail to get the list into box");
				return;
			}

			box = eina_list_nth(list, 0);
			if (!box) {
				LOGE("Fail to get the box into box layout");
				return;
			}

			eina_list_free(list);
			elm_box_clear(box);
			elm_box_recalculate(box);


			// send request to server
			send_delete_group_chat_request(ad, ad->service_client, user_data->peer_id);

			if (ad->main_item_in_cahtting_data) {
				tg_main_list_item_s* old_item = ad->main_item_in_cahtting_data;
				if (old_item->last_message) {
					free(old_item->last_message);
					old_item->last_message = NULL;
				}
				old_item->last_message = strdup("");
			}

			Evas_Object *nomsg_layout = evas_object_data_del(ad->nf, "chat_list_no_msg_text");
			if (nomsg_layout) {
				elm_object_signal_emit(nomsg_layout, "show", "message");
			}
#endif

		} else {

		}

	} else if (id == 2) { //Delete
		if (user_data->peer_type == TGL_PEER_USER) {
			show_loading_popup(ad);
			char* tablename = get_table_name_from_number(user_data->peer_id);
			delete_all_records(tablename);
			free(tablename);

#if 0
			// clear all messages
			Evas_Object *genlist = evas_object_data_get(ad->nf, "chat_list");
			elm_genlist_clear(genlist);

			// remove main item from main list
			if (ad->main_item_in_cahtting_data) {
				tg_main_list_item_s* old_item = ad->main_item_in_cahtting_data;
				if (old_item->peer_print_name) {
					free(old_item->peer_print_name);
					old_item->peer_print_name = NULL;
				}
				if (old_item->last_message) {
					free(old_item->last_message);
					old_item->last_message = NULL;
				}
				if (old_item->profile_pic_path) {
					free(old_item->profile_pic_path);
					old_item->profile_pic_path = NULL;
				}
				old_item->date_lbl = NULL;
				old_item->msg_status_lbl = NULL;
				old_item->main_item_layout = NULL;
				old_item->profile_pic = NULL;
				old_item->profile_pic_path = NULL;
				old_item->status_lbl = NULL;
				old_item->user_name_lbl = NULL;
				ad->main_list = eina_list_remove(ad->main_list,  ad->main_item_in_cahtting_data);

				ad->main_item_in_cahtting_data = NULL;
			}

			ad->is_last_msg_changed = EINA_FALSE;


			app_nf_back_cb(ad, NULL, NULL);
#else
			elm_naviframe_item_pop(ad->nf);
			load_registered_user_data(ad);
			load_buddy_list_data(ad);
			load_unknown_buddy_list_data(ad);
			load_peer_data(ad);
			load_main_list_data(ad);
			ecore_timer_add(1, on_load_main_view_requested, ad);
#endif

		} else if (user_data->peer_type == TGL_PEER_CHAT) {

			//send group chat delete request
			show_loading_popup(ad);
			send_delete_group_chat_request(ad, ad->service_client, user_data->peer_id);

		} else {

		}
	} else if (id == 0) { // View profile
		launch_user_info_screen(ad, user_data->peer_id);
	} else {
	}
	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
}


char* on_messaging_menu_group_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	if (id == 0) {
		return strdup(i18n_get_text("IDS_TGRAM_OPT_CLEAR_HISTORY_ABB3"));
	} else {
		return strdup(i18n_get_text("IDS_TGRAM_OPT_DELETE"));
	}
}

char* on_messaging_menu_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	appdata_s *ad = evas_object_data_get(obj, "app_data");
	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	tg_peer_info_s *user_data = sel_item->use_data;
	if ((user_data->peer_type == TGL_PEER_USER) && get_buddy_unknown_status(user_data->peer_id)) {
	    if (id == 0) {
	    	return strdup(i18n_get_text("IDS_TGRAM_OPT_ADD_TO_CONTACTS_ABB2"));
	    } else if (id == 1) {
	    	return strdup(i18n_get_text("IDS_TGRAM_OPT_CLEAR_HISTORY_ABB3"));
		} else {
			return strdup(i18n_get_text("IDS_TGRAM_OPT_DELETE"));
		}
	} else {
		if (id == 0) {
			return strdup(i18n_get_text("IDS_TGRAM_OPT_VIEW_PROFILE_ABB"));
		}
		else if (id == 1) {
			return strdup(i18n_get_text("IDS_TGRAM_OPT_CLEAR_HISTORY_ABB3"));
		} else {
			return strdup(i18n_get_text("IDS_TGRAM_OPT_DELETE"));
		}
	}
}

void on_msg_popup_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}
}

void on_messaging_menu_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (ad->msg_popup || ad->current_app_state != TG_CHAT_MESSAGING_VIEW_STATE) {
		return;
	}

	static Elm_Genlist_Item_Class itc;
	//Evas_Object *popup;
	Evas_Object *genlist;
	int i;
	Evas_Object *win = ad->win;

	ad->msg_popup = elm_popup_add(win);
	elm_popup_align_set(ad->msg_popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(ad->msg_popup, EEXT_CALLBACK_BACK, on_msg_popup_back_cb, ad);
	evas_object_size_hint_weight_set(ad->msg_popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_data_set(ad->msg_popup, "app_data", ad);

	genlist = elm_genlist_add(ad->msg_popup);
	evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

	evas_object_data_set(genlist, "app_data", ad);

	itc.item_style = "default";
	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	if (sel_item->use_data->peer_type == TGL_PEER_USER) {
		itc.func.text_get = on_messaging_menu_text_get_cb;
	} else if (sel_item->use_data->peer_type == TGL_PEER_CHAT) {
		itc.func.text_get = on_messaging_menu_group_text_get_cb;
	} else {

	}

	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	if (sel_item->use_data->peer_type == TGL_PEER_CHAT) {
		for (i = 0; i < 2; i++) {
			elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_messaging_menu_option_selected_cb, ad);
		}
	} else {
		for (i = 0; i < 3; i++) {
			elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_messaging_menu_option_selected_cb, ad);
		}
	}
	evas_object_show(genlist);

	elm_object_content_set(ad->msg_popup, genlist);
	evas_object_show(ad->msg_popup);
}


/************************ Menu Handler ********************/




static Evas_Object *create_image_object_from_file(const char *icon_name, Evas_Object *parent)
{
	Evas_Object *icon = elm_image_add(parent);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_image_file_set(icon, icon_name, NULL);
	evas_object_show(icon);
	return icon;
}

void on_chat_profile_pic_changed(appdata_s *ad, char *file_path)
{
	if (!ad || !file_path) {
		return;
	}

	Evas_Object *profile_image = evas_object_data_get(ad->nf, "profile_picture");
	if (profile_image) {
		elm_image_file_set(profile_image, file_path, NULL);
	}

}

void on_group_chat_info_changed(appdata_s *ad, char *type_of_change)
{
	if (!ad || !type_of_change) {
		return;
	}
	if (strstr(type_of_change, "edit_title") != NULL) {
		peer_with_pic_s *sel_item = ad->peer_in_cahtting_data;
		if (sel_item) {
			tg_peer_info_s* user = sel_item->use_data;
			char* user_name = replace(sel_item->use_data->print_name, '_', " ");
			char temp_name[512] = {'\0'};
			snprintf(temp_name, 512, "%s", user_name);
			free(user_name);
			Elm_Object_Item *nf_it = evas_object_data_get(ad->nf, "navi_item");
			elm_object_item_part_text_set(nf_it, "title", temp_name);
		}
	} else if (strstr(type_of_change, "delete_photo") != NULL) {

	} else if (strstr(type_of_change, "add_user") != NULL) {
		peer_with_pic_s *sel_item = ad->peer_in_cahtting_data;
		if (sel_item) {
			on_user_presence_state_changed(ad, sel_item->use_data->peer_id);
		}
	} else if (strstr(type_of_change, "delete_user") != NULL) {
		peer_with_pic_s *sel_item = ad->peer_in_cahtting_data;
		if (sel_item) {
			on_user_presence_state_changed(ad, sel_item->use_data->peer_id);
		}
	} else {

	}
}

void on_sent_media_item_clicked(void* data, Evas_Object* layout, void* event_info)
{
	appdata_s* ad = evas_object_data_get(layout, "app_data");
	char* media_type_str = evas_object_data_get(layout, "media_type");
	char* media_file = evas_object_data_get(layout, "media_file");

	if( access (media_file, F_OK) != -1 ) {

	} else {
		media_file = NULL;
	}

	if (media_file && strlen(media_file) > 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image");
			return;
		}
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_VIEW);
		if (strstr(media_type_str, "video") != NULL) {
			app_control_set_mime(app_control,"video/*");
		} else if (strstr(media_type_str, "audio") != NULL) {
			app_control_set_mime(app_control,"audio/*");
		} else {
			app_control_set_mime(app_control,"image/*");
		}
		app_control_set_uri(app_control, media_file);

		app_control_send_launch_request(app_control, NULL, NULL);
		app_control_destroy(app_control);
	}
}

static Evas_Object *get_gif_image_from_path(const char* path, Evas_Object* parent, char *key)
{
	if (!path || !parent || !key) {
			return NULL;
		}
	LOGD(">>>>>>>>>> key : %s", key);
		Evas_Object *media_image = elm_image_add(parent);
		elm_image_aspect_fixed_set(media_image, EINA_FALSE);
		elm_image_file_set(media_image, path, key);
		evas_object_size_hint_weight_set(media_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(media_image, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(media_image);
		return media_image;
}

static Evas_Object *get_image_from_path(const char* path, Evas_Object* parent)
{
	if (!path || !parent) {
		return NULL;
	}
	Evas_Object *media_image = elm_image_add(parent);
	elm_image_aspect_fixed_set(media_image, EINA_FALSE);
	elm_image_file_set(media_image, path, NULL);
	evas_object_size_hint_weight_set(media_image, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(media_image, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(media_image);
	return media_image;
}

int get_image_size(long long media_id)
{
	Eina_List* media_sizes = get_image_sizes_from_db(media_id);
	int row_count = eina_list_count(media_sizes);
	int size1 = 0;
	int size2 = 0;
	int size3 = 0;
	int size4 = 0;
	int media_size = 0;
	for (int i = 0 ; i < row_count ; i++) {
		Eina_List* row_vals = eina_list_nth(media_sizes, i);
		int* temp_size1 = (int*)eina_list_nth(row_vals, 0);
		if(temp_size1) {
			size1 = *temp_size1;
			free(temp_size1);
		}
		int* temp_size2 = (int*)eina_list_nth(row_vals, 3);
		if(temp_size2) {
			size2 = *temp_size2;
			free(temp_size2);
		}
		int* temp_size3 = (int*)eina_list_nth(row_vals, 6);
		if(temp_size3) {
			size3 = *temp_size3;
			free(temp_size3);
		}
		int* temp_size4 = (int*)eina_list_nth(row_vals, 9);
		if(temp_size4) {
			size4 = *temp_size4;
			free(temp_size4);
		}
		eina_list_free(row_vals);
		break;
	}
	eina_list_free(media_sizes);

	if (size1 > 0) {
		media_size = size1;
	} else if (size2 > 0) {
		media_size = size2;
	} else if (size3 > 0) {
		media_size = size3;
	} else if (size4 > 0) {
		media_size = size4;
	} else {

	}
	return media_size;
}

void on_media_chat_item_clicked(void* data, Evas_Object *entry, void* event_info)
{
	Evas_Object *button = evas_object_data_get(entry, "button_object");
	if (button) {
		char* img_state = evas_object_data_get(button, "image_state");
		if (img_state && strstr(img_state, "download_in_progress") != NULL) {
			return;
		}
	}

	appdata_s* ad = evas_object_data_get(entry, "app_data");
	char *temp_media_id = evas_object_data_get(entry, "media_id");
	char *media_type_str = evas_object_data_get(entry, "media_type");

	if (media_type_str && strstr(media_type_str, "location") != NULL) {
		char *url = evas_object_data_get(entry, "location_url");
		launch_app_control(ad, media_type_str, url);
		return;
	}

	long long media_id = atoll(temp_media_id);

	char *media_file = get_media_path_from_db(media_id);

	if( access (media_file, F_OK) != -1 ) {

	} else {
		media_file = NULL;
	}

	if (!media_file || strlen(media_file) <= 0) {
		Eina_Bool ret = send_request_for_media_downloading(ad, ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id, media_id);
		if (!ret) {
			show_toast(ad, "Please check your network connection.");
			return;
		}
		// show progress bar
		char temp_msg[256] = {0,};
	    snprintf(temp_msg, sizeof(temp_msg), "%s", "Downloading...");
		elm_object_part_text_set(button, "size", temp_msg);

		Evas_Object* progressbar = elm_progressbar_add(button);
		elm_object_style_set(progressbar, "process_small");
		evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_progressbar_pulse(progressbar, EINA_TRUE);
		evas_object_show(progressbar);

		Evas_Object* old_content = elm_object_part_content_unset(button, "download_image");
		if (old_content) {
			evas_object_del(old_content);
		}

		elm_object_part_content_set(button, "download_image", progressbar);
		evas_object_data_set(button, "image_state", "download_in_progress");

	} else {
		launch_app_control(ad, media_type_str, media_file);
	}
}

static void on_video_play_pressed(void *data, Evas_Object *obj, void *event_info)
{
	if (!data)
		return;
	elm_image_file_set(data, ui_utils_get_resource(TG_PLAY_PRESS_ICON), NULL);
}

static void on_video_play_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	if (!data)
		return;
	elm_image_file_set(data, ui_utils_get_resource(TG_PLAY_NORMAL_ICON), NULL);
}

static Evas_Object* get_video_paly_icon(Evas_Object *parent)
{
	Evas_Object* play_pause_btn = elm_button_add(parent);
	elm_object_style_set(play_pause_btn, "transparent");
	evas_object_size_hint_align_set(play_pause_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(play_pause_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	Evas_Object* play_pause_icon = elm_image_add(parent);
	evas_object_size_hint_align_set(play_pause_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(play_pause_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	elm_image_file_set(play_pause_icon, ui_utils_get_resource(TG_PLAY_NORMAL_ICON), NULL);

	elm_image_resizable_set(play_pause_icon, EINA_TRUE, EINA_TRUE);
	evas_object_show(play_pause_icon);

	elm_object_content_set(play_pause_btn, play_pause_icon);

	evas_object_smart_callback_add(play_pause_btn, "pressed", on_video_play_pressed, play_pause_icon);
	evas_object_smart_callback_add(play_pause_btn, "unpressed", on_video_play_unpressed, play_pause_icon);
	return play_pause_btn;
}

static Evas_Object *get_media_layout_with_play(char *img_path, Evas_Object *parent, Eina_Bool show_play_icon)
{
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
	Evas_Object *rec_video_layout = elm_layout_add(parent);
	elm_layout_file_set(rec_video_layout, edj_path, "bubble_video_item_layout");
	evas_object_size_hint_weight_set(rec_video_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(rec_video_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(rec_video_layout);

	Evas_Object *vid_thumb_icon = get_image_from_path(img_path, parent);
	elm_object_part_content_set(rec_video_layout, "swallow.video_thumb_item", vid_thumb_icon);

	if (show_play_icon) {
/*		Evas_Object* play_img = get_image_from_path(ui_utils_get_resource(MEDIA_PLAY_ICON), parent);
		elm_object_part_content_set(rec_video_layout, "swallow.play_btn", play_img);*/

		Evas_Object* play_pause_btn = get_video_paly_icon(parent);
		elm_object_part_content_set(rec_video_layout, "swallow.play_btn", play_pause_btn);
	}

	return rec_video_layout;
}

void audio_player_progress_updated(void* handler, int current, int total, void *user_data)
{
	Evas_Object *parent = user_data;
	Evas_Object *progressbar = evas_object_data_get(parent, "progress_control");


	int seconds = (int) (current / 1000) % 60 ;
	int minutes = (int) ((current / (1000*60)) % 60);

	char tot_dur[256] = {0,};
	char *format = NULL;
	if (seconds < 10 && minutes < 10) {
		format = "0%d:0%d";
	} else if (seconds > 10 && minutes < 10) {
		format = "%d:0%d";
	} else if (seconds < 10 && minutes > 10) {
		format = "0%d:%d";
	} else {
		format = "0%d:0%d";
	}

	sprintf(tot_dur, format, minutes, seconds);
	elm_object_part_text_set(progressbar, "elm.text.bottom.right", tot_dur);

	double current_status = (double)((double)current/(double)total);

	elm_progressbar_value_set(progressbar, current_status);

}

void audio_player_state_changed(void* handler, TG_AUDIO_PLAYER_STATE state, void *user_data)
{
	tg_player_handler *audio_payer = handler;
	Evas_Object *parent = user_data;

	if (!audio_payer || !parent) {
		return;
	}

	Eina_Bool is_play_mode = (Eina_Bool)evas_object_data_get(parent, "is_play_mode");
	switch(audio_payer->state) {
	case TG_AUDIO_PLAYER_STATE_NONE:
		break;
	case TG_AUDIO_PLAYER_STATE_INITIALIZED:
		evas_object_data_set(parent, "tg_audio_player", audio_payer);
		play_audio_player(audio_payer);
		break;
	case TG_AUDIO_PLAYER_STATE_PLAYING:
		elm_image_file_set(parent, ui_utils_get_resource(TG_PAUSE_NORMAL_ICON), NULL);
		is_play_mode = !is_play_mode;
		evas_object_data_set(parent, "is_play_mode", is_play_mode);
		break;
	case TG_AUDIO_PLAYER_STATE_INTERRUPTED:
		elm_image_file_set(parent, ui_utils_get_resource(TG_PLAY_NORMAL_ICON), NULL);
		is_play_mode = !is_play_mode;
		evas_object_data_set(parent, "is_play_mode", is_play_mode);
		break;
	case TG_AUDIO_PLAYER_STATE_PAUSE:
		elm_image_file_set(parent, ui_utils_get_resource(TG_PLAY_NORMAL_ICON), NULL);
		is_play_mode = !is_play_mode;
		evas_object_data_set(parent, "is_play_mode", is_play_mode);
		break;
	case TG_AUDIO_PLAYER_STATE_ERROR:
		break;
	case TG_AUDIO_PLAYER_STATE_END:
		destroy_audio_player(audio_payer);
		free(audio_payer);

		is_play_mode = EINA_FALSE;
		evas_object_data_set(parent, "is_play_mode", is_play_mode);
		evas_object_data_set(parent, "tg_audio_player", NULL);
		elm_image_file_set(parent, ui_utils_get_resource(TG_PLAY_NORMAL_ICON), NULL);
		audio_player_progress_updated(NULL, 0, 1, parent);
		break;
	default:
		break;
	}

}

static void on_message_play_pause_clicked(void *data, Evas_Object *obj, void *event_info)
{
	if (!data)
		return;

	appdata_s * ad = evas_object_data_get(data, "app_data");
	char *audio_file = evas_object_data_get(data, "audio_file_path");
	char *media_id = evas_object_data_get(data, "media_id");
	if (!audio_file  || strlen(audio_file) <= 0 || strstr(audio_file, "_null_") != NULL) {
		//there is no file. download it.
		Evas_Object *progressbar = evas_object_data_get(data, "progress_control");
		Eina_Bool is_download_in_progress = (Eina_Bool)evas_object_data_get(progressbar, "is_download_in_progress");

		if (is_download_in_progress) {

		} else {
			elm_object_style_set(progressbar, "pending");
			Eina_Bool ret = send_request_for_media_downloading(ad, ad->service_client, ad->peer_in_cahtting_data->use_data->peer_id, atoll(media_id));
			if (!ret) {
				show_toast(ad, "Please check your network connection.");
				return;
			}
		}
		return;
	}

	tg_player_handler *audio_payer = evas_object_data_get(data, "tg_audio_player");

	if (!audio_payer) {
		audio_payer = init_audio_player(audio_file, &audio_player_state_changed, &audio_player_progress_updated, data);

		if (!audio_payer) {
			show_toast(ad, "Unsupported file.");
		}
		return;
	}

	if (audio_payer->state == TG_AUDIO_PLAYER_STATE_PAUSE || audio_payer->state == TG_AUDIO_PLAYER_STATE_INTERRUPTED) {

		play_audio_player(audio_payer);

	} else if (audio_payer->state == TG_AUDIO_PLAYER_STATE_PLAYING) {

		pause_audio_player(audio_payer);

	}
}

static void on_message_play_pause_pressed(void *data, Evas_Object *obj, void *event_info)
{
	if (!data)
		return;

	Eina_Bool is_play_mode = (Eina_Bool)evas_object_data_get(data, "is_play_mode");
	if (is_play_mode) {
		elm_image_file_set(data, ui_utils_get_resource(TG_PAUSE_PRESS_ICON), NULL);
	} else {
		elm_image_file_set(data, ui_utils_get_resource(TG_PLAY_PRESS_ICON), NULL);
	}
}

static void on_message_play_pause_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	if (!data)
		return;

	Eina_Bool is_play_mode = (Eina_Bool)evas_object_data_get(data, "is_play_mode");
	if (is_play_mode) {

		elm_image_file_set(data, ui_utils_get_resource(TG_PAUSE_NORMAL_ICON), NULL);
	} else {
		elm_image_file_set(data, ui_utils_get_resource(TG_PLAY_NORMAL_ICON), NULL);
	}
}

static void progressbar_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{


}

static Evas_Object *create_audio_progressbar(Evas_Object *parent, int duration)
{
	Evas_Object *progressbar;

	progressbar = elm_progressbar_add(parent);
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_value_set(progressbar, 0.0);
	evas_object_event_callback_add(progressbar, EVAS_CALLBACK_DEL, progressbar_del_cb, NULL);
	evas_object_show(progressbar);

	elm_object_part_text_set(progressbar, "elm.text.top.left", "");
	elm_object_part_text_set(progressbar, "elm.text.top.right", "");

	elm_object_part_text_set(progressbar, "elm.text.bottom.right", "00:00");

	return progressbar;
}


static Evas_Object *get_audio_layout_with_play(Evas_Object *parent)
{
	Evas_Object* chat_scroller = parent;
	Evas_Object *rec_video_layout = NULL;
	tgl_media_s *media_msg = NULL;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");
	int message_id = (int)evas_object_data_get(chat_scroller, "message_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
	int buddy_id = sel_item->use_data->peer_id;
	char* tablename = get_table_name_from_number(buddy_id);

	tg_message_s* msg = get_message_from_message_table(message_id, tablename);

	free(tablename);

	if (!msg) {
		return NULL;
	}

	Evas_Object *parent_obj = evas_object_data_get(chat_scroller, "parent_obj"); //entry

	//if (msg->out) {

		media_msg = get_media_details_from_db(atoll(msg->media_id));

		char *audio_file = media_msg->file_path;

		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		rec_video_layout = elm_layout_add(parent);
		elm_layout_file_set(rec_video_layout, edj_path, "bubble_audio_item_layout");
		evas_object_size_hint_weight_set(rec_video_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(rec_video_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(rec_video_layout);

		/**************** play icon **********************/
		Evas_Object* play_pause_btn = elm_button_add(parent);
		elm_object_style_set(play_pause_btn, "transparent");
		evas_object_size_hint_align_set(play_pause_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(play_pause_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

		Evas_Object* play_pause_icon = elm_image_add(parent);
		evas_object_size_hint_align_set(play_pause_icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(play_pause_icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		elm_image_file_set(play_pause_icon, ui_utils_get_resource(TG_PLAY_NORMAL_ICON), NULL);

		elm_image_resizable_set(play_pause_icon, EINA_TRUE, EINA_TRUE);
		evas_object_show(play_pause_icon);
		elm_object_content_set(play_pause_btn, play_pause_icon);

		Eina_Bool is_play_mode = EINA_TRUE;
		evas_object_data_set(play_pause_icon, "is_play_mode", is_play_mode);

		if (audio_file) {
			evas_object_data_set(play_pause_icon, "audio_file_path", strdup(audio_file));
		}
		evas_object_data_set(play_pause_icon, "app_data", ad);
		evas_object_data_set(play_pause_icon, "user_id", (void*)user_id);
		evas_object_data_set(play_pause_icon, "message_id", (void*)message_id);
		evas_object_data_set(play_pause_icon, "media_id", strdup(msg->media_id));

		evas_object_smart_callback_add(parent_obj, "clicked", on_message_play_pause_clicked, play_pause_icon);
		evas_object_smart_callback_add(parent_obj, "pressed", on_message_play_pause_pressed, play_pause_icon);
		evas_object_smart_callback_add(parent_obj, "unpressed", on_message_play_pause_unpressed, play_pause_icon);

		evas_object_smart_callback_add(play_pause_btn, "clicked", on_message_play_pause_clicked, play_pause_icon);
		evas_object_smart_callback_add(play_pause_btn, "pressed", on_message_play_pause_pressed, play_pause_icon);
		evas_object_smart_callback_add(play_pause_btn, "unpressed", on_message_play_pause_unpressed, play_pause_icon);
		elm_object_part_content_set(rec_video_layout, "swallow.play_icon", play_pause_btn);
		/**************** play icon **********************/

		/*************** progress bar ********************/

		int total_duration = 0;
		if (audio_file) {
			metadata_extractor_h metadata;
			metadata_extractor_create(&metadata);
			int ret = metadata_extractor_set_path(metadata, audio_file);
			char *value = NULL;
			ret = metadata_extractor_get_metadata(metadata, METADATA_DURATION, &value);
			metadata_extractor_destroy(metadata);

			if (value) {
				total_duration = atoi(value);
				free(value);
			}
		} else {
			total_duration = media_msg->doc_duration;
			//convert into milli secs
			total_duration = 1000 * total_duration;
		}

		Evas_Object *progress = create_audio_progressbar(parent, total_duration);

		evas_object_data_set(parent_obj, "play_pause_icon", play_pause_icon);
		evas_object_data_set(parent_obj, "progress_bar", progress);

		elm_object_part_content_set(rec_video_layout, "swallow.progress_icon", progress);

		evas_object_data_set(play_pause_icon, "progress_control", (void*)progress);
		Eina_Bool is_download_in_progress = EINA_FALSE;
		evas_object_data_set(progress, "is_download_in_progress", (void*)is_download_in_progress);

		/*************** progress bar ********************/

	//}

	if(msg->message) {
		free(msg->message);
		msg->message = NULL;
	}
	if(msg->media_id) {
		free(msg->media_id);
		msg->media_id = NULL;
	}
	free(msg);
	free_media_details(media_msg);

	return rec_video_layout;
}


static Evas_Object * item_provider(void *data, Evas_Object *entry, const char *item)
{
	Evas_Object *layout = NULL;
	if (!strcmp(item, "itemprovider")) {
		Evas_Object* chat_scroller = data;
		appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
		int user_id = (int)evas_object_data_get(chat_scroller, "user_id");
		int message_id = (int)evas_object_data_get(chat_scroller, "message_id");

		peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
		int buddy_id = sel_item->use_data->peer_id;

		char* tablename = get_table_name_from_number(buddy_id);
		tg_message_s* msg = get_message_from_message_table(message_id, tablename);
		free(tablename);
		if (!msg) {
			return NULL;
		}

		Evas_Object *item_to_display = NULL;
		tgl_media_s *media_msg = NULL;
		if (msg->media_type == tgl_message_media_photo || msg->media_type == tgl_message_media_document) {

			Eina_Bool is_blur_image = EINA_FALSE;
			char* img_path = NULL;
			Evas_Object *temp = NULL;
			temp = evas_object_data_get(entry, "img_object");
			if (temp == NULL) {
				const char *tmp;
				tmp = ui_utils_get_resource(BLUR_BG);
				img_path = strdup(tmp);
				is_blur_image = EINA_TRUE;
			} else {
				item_to_display = temp;
			}

			if (msg->media_type == tgl_message_media_document) {
				media_msg = get_media_details_from_db(atoll(msg->media_id));

				if (media_msg && strstr(media_msg->doc_type, "video") != NULL) {
					if (img_path == NULL || strlen(img_path) == 0) {
						img_path = strdup(ui_utils_get_resource(TG_VIDEO_ICON));
					}
				}
				if (media_msg && strstr(media_msg->doc_type, "audio") != NULL) {
					if (img_path) {
						free(img_path);
						img_path = NULL;
					}
					img_path = strdup(ui_utils_get_resource(TG_AUDIO_ICON));
				}
				char* media_file = get_media_path_from_db(atoll(msg->media_id));
				if (!media_file || !strcmp(media_file, "_null_") || strlen(media_file) <= 0 ||  access(media_file, F_OK) == -1) {
					is_blur_image = EINA_TRUE;
				}

				if (media_file && strstr(media_file, ".webp") != NULL) {
					is_blur_image = EINA_FALSE;
				}
				free(media_file);

			}

			if (media_msg && strstr(media_msg->doc_type, "audio") != NULL) {

				evas_object_data_set(chat_scroller, "parent_obj", (void*)entry);
				item_to_display = get_audio_layout_with_play(chat_scroller);

			} else if (msg->out) {

				if (msg->media_type == tgl_message_media_photo) {

					//item_to_display = get_image_from_path(img_path, entry);

				} else {
					if (media_msg && strstr(media_msg->doc_type, "video") != NULL) {

						item_to_display = get_media_layout_with_play(img_path, entry, EINA_TRUE);

					} else {
						//item_to_display = get_image_from_path(img_path, entry);
						elm_image_animated_set(item_to_display, EINA_TRUE);
						elm_image_animated_play_set(item_to_display, EINA_TRUE);
					}
				}

			} else {
				if (!is_blur_image) {

					if (msg->media_type == tgl_message_media_photo) {

						evas_object_data_set(entry, "image_object", (void*)item_to_display);

					} else {
						if (media_msg && strstr(media_msg->doc_type, "video") != NULL) {

							item_to_display = get_media_layout_with_play(img_path, entry, EINA_TRUE);

						} else {
							if (strstr(media_msg->mime_type, "webp") != NULL) {
								evas_object_data_set(entry, "image_object", (void*)item_to_display);
							} else {
								evas_object_data_set(entry, "image_object", (void*)item_to_display);
								elm_image_animated_set(item_to_display, EINA_TRUE);
								elm_image_animated_play_set(item_to_display, EINA_TRUE);
							}
						}
					}

				} else {
					char edj_path[PATH_MAX] = {0, };
					app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
					Evas_Object *rec_img_layout = elm_layout_add(entry);
					elm_layout_file_set(rec_img_layout, edj_path, "bubble_received_media_layout");
					evas_object_size_hint_weight_set(rec_img_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
					evas_object_size_hint_align_set(rec_img_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
					evas_object_show(rec_img_layout);
					Evas_Object *img_item = NULL;


					if (msg->media_type == tgl_message_media_photo) {
						img_item = get_image_from_path(img_path, entry);
					} else {
						if ((media_msg && strstr(media_msg->doc_type, "video") != NULL )|| (media_msg && strstr(media_msg->doc_type, "audio") != NULL)) {
							img_item = get_media_layout_with_play(img_path, entry, EINA_FALSE);
						} else {
							img_item = get_image_from_path(img_path, entry);
						}
					}
					elm_object_part_content_set(rec_img_layout, "swallow.image_item", img_item);

					int media_size = 0;
					if (msg->media_type == tgl_message_media_photo) {
						media_size = get_image_size(atoll(msg->media_id));
					} else {
						if (media_msg && strstr(media_msg->doc_type, "video") != NULL) {
							media_size = get_media_size_from_db(atoll(msg->media_id));
						} else if (media_msg && strstr(media_msg->doc_type, "audio") != NULL) {
							media_size = get_media_size_from_db(atoll(msg->media_id));
						} else {
							media_size = get_media_size_from_db(atoll(msg->media_id));
						}
					}

					int media_size_kbs = (media_size < (1 << 20)); //convert to kbs
					char media_size_str[10] = { 0, };
					if (media_size_kbs > 0) {
						sprintf(media_size_str, "%dKB", media_size_kbs);
					} else {
						sprintf(media_size_str, "%dB", media_size);
					}


					Evas_Object *size_btn = elm_layout_add(entry);
					elm_layout_file_set(size_btn, edj_path, "download_btn");
					elm_object_part_text_set(size_btn, "size", media_size_str);
					evas_object_size_hint_weight_set(size_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
					evas_object_size_hint_align_set(size_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
					evas_object_show(size_btn);

					evas_object_data_set(size_btn, "image_state", "ready_to_download");

					Evas_Object* download_img = get_image_from_path(ui_utils_get_resource(MEDIA_DOWNLOAD_ICON), entry);
					elm_object_part_content_set(size_btn, "download_image", download_img);

					elm_object_part_content_set(rec_img_layout, "swallow.download_btn", size_btn);

					evas_object_data_set(entry, "image_object", (void*)img_item);
					evas_object_data_set(entry, "button_object", (void*)size_btn);
					evas_object_data_set(entry, "image_size", (void*)strdup(media_size_str));

					ad->loaded_msg_list = eina_list_append(ad->loaded_msg_list, entry);

					item_to_display = rec_img_layout;
				}
			}

			if (img_path) {
				free(img_path);
				img_path = NULL;
			}
			// delete media details

		}

		evas_object_data_set(entry, "chat_list", (void*)chat_scroller);
		evas_object_data_set(entry, "message_id", (void*)message_id);
		evas_object_data_set(entry, "app_data", (void*)ad);


		if (msg->media_type == tgl_message_media_photo) {
			evas_object_data_set(entry, "media_type", (void*)strdup("image"));
		} else if (msg->media_type == tgl_message_media_geo) {
			evas_object_data_set(entry, "media_type", (void*)strdup("location"));
		} else {
			if (media_msg && strstr(media_msg->doc_type, "video") != NULL) {
				evas_object_data_set(entry, "media_type", (void*)strdup("video"));
			} else if (media_msg && strstr(media_msg->doc_type, "audio") != NULL) {
				evas_object_data_set(entry, "media_type", (void*)strdup("audio"));
			} else {
				evas_object_data_set(entry, "media_type", (void*)strdup("animated_image"));
			}
		}

		evas_object_data_set(entry, "media_id", (void*)strdup(msg->media_id));
		if (item_to_display) {
			if (media_msg && strstr(media_msg->doc_type, "audio") != NULL) {
				layout = item_to_display;
			} else {
				char edj_path[PATH_MAX] = {0, };
				app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
				layout = elm_layout_add(entry);
				elm_layout_file_set(layout, edj_path, "chat_image_layout");
				evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_show(layout);

				Evas_Object *rounded_layout = elm_layout_add(entry);
				elm_layout_file_set(rounded_layout, edj_path, "rounded_corner_layout");
				evas_object_size_hint_weight_set(rounded_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(rounded_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_show(rounded_layout);
				elm_object_part_content_set(rounded_layout, "content", item_to_display);

				elm_object_part_content_set(layout, "swallow.chat_image", rounded_layout);
				evas_object_smart_callback_add(entry, "clicked", on_media_chat_item_clicked, NULL);
			}
		}

		if(msg->message) {
			free(msg->message);
			msg->message = NULL;
		}

		if(msg->media_id) {
			free(msg->media_id);
			msg->media_id = NULL;
		}

		free(msg);
		free_media_details(media_msg);
	}

	return layout;
}

static void __resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Evas_Object *layout = NULL;
	Evas_Object *chat_scroller = NULL;

	layout = evas_object_data_get(ad->nf, "main_layout");
	chat_scroller = evas_object_data_get(ad->nf, "chat_list");

	int is_end_edge = 0;
	is_end_edge = (int)evas_object_data_get(layout, "is_end_edge");

	if (is_end_edge) {
		int ret = 1;
		ret = scroller_show_bottom_edge(chat_scroller);
		if (!ret) {
			LOGE("Fail to show the bottom of scroller");
		}
	}
}

static void _create_image_item(tg_message_s *msg, Evas_Object *entry, char *image, int size)
{
	char* img_path = NULL;
	img_path = get_video_thumb_path_from_db(atoll(msg->media_id));
	if (img_path == NULL || strlen(img_path) == 0 || strstr(img_path, "_null_") != NULL) {
		img_path = get_media_path_from_db(atoll(msg->media_id));
		if( access (img_path, F_OK) == -1 ) {
			img_path = NULL;
		}
	}

	int w, h, entry_h;
	Evas_Object *img_item = NULL;
	char key[256] = {0, };
	snprintf(key, sizeof(key), "%d", msg->msg_id);

	if (img_path && strstr(img_path, ".webp") != NULL) {
		img_item = get_image_from_path(img_path, entry);
	} else {
		if (msg->media_type == tgl_message_media_document) {
			img_item = get_gif_image_from_path(img_path, entry, key);
		} else {
			img_item = get_image_from_path(img_path, entry);
		}
	}

	w = 0;
	h = 0;
	if (img_item) {
		evas_object_data_set(entry, "img_object", img_item);
		elm_image_object_size_get(img_item, &w, &h);
	}

	if (img_path && strstr(img_path, ".webp") != NULL) {
		entry_h = 200;
	} else {
		if (w && h) {
			entry_h = (318 * h) / w;
		} else {
			entry_h = 200;
			evas_object_data_set(entry, "img_object", NULL);
		}
	}
	snprintf(image, size - 1, "<item size=318x%d vsize=full href=itemprovider></item>", entry_h);
}

Evas_Object *on_message_item_content_get_cb(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *entry = elm_entry_add(obj);
	Evas_Object *layout = NULL;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	if (!strcmp(part, "elm.icon.entry")) {

		int message_id = (int)data;
		Evas_Object *chat_scroller = obj;
		appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");

		Evas_Object *nomsg_layout = evas_object_data_del(ad->nf, "chat_list_no_msg_text");
		if (nomsg_layout) {
			elm_object_signal_emit(nomsg_layout, "hide", "message");
		}

		int user_id = (int)evas_object_data_get(chat_scroller, "user_id");
		evas_object_data_set(chat_scroller, "message_id", data);


		peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
		int buddy_id = sel_item->use_data->peer_id;

		char* tablename = get_table_name_from_number(buddy_id);
		tg_message_s* msg = get_message_from_message_table(message_id, tablename);
		//Eina_Bool is_blur_image = EINA_FALSE;

		if (msg) {
#if 0
			if (msg->unread) {
				msg->unread = 0;
				update_msg_into_db(msg, tablename);
				ad->is_last_msg_changed = EINA_TRUE;
			}
#endif
			if (msg->out) {

			} else {
				// update un read

			}

			if (msg->service == 2) {
				layout = elm_layout_add(obj);
				elm_layout_file_set(layout, edj_path, "chat_date_item");
				evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_show(layout);

				// convert date from string to int
				char *date_str = msg->message;
				int date_num = atoi(date_str);

				// convert date format
				time_t t = date_num;
				char *format = NULL;
				format = "%a, %e %b %Y";
				struct tm lt;
				char res[256];
				(void) localtime_r(&t, &lt);

				if (strftime(res, sizeof(res), format, &lt) == 0) {
					(void) fprintf(stderr,  "strftime(3): cannot format supplied "
							"date/time into buffer of size %u "
							"using: '%s'\n",
							sizeof(res), format);
				}

				elm_object_part_text_set(layout, "elm.text", res);
				return layout;
			} else if (msg->service == 1) {
				layout = elm_layout_add(obj);
				elm_layout_file_set(layout, edj_path, "chat_service_item_box");
				evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_show(layout);

				elm_object_part_text_set(layout, "elm.text", msg->message);

				return layout;
			}

			evas_object_data_set(entry, "chat_list", (void*)chat_scroller);
			evas_object_data_set(entry, "message_id", (void*)message_id);

			elm_entry_editable_set(entry, EINA_FALSE);
			elm_entry_context_menu_disabled_set(entry, EINA_TRUE);
			elm_entry_single_line_set(entry, EINA_TRUE);

			layout = elm_layout_add(obj);

			if(msg->out) {
				elm_layout_file_set(layout, edj_path, "entry,send,layout");
				elm_object_style_set(entry, "sentmessage1");
				//sender_name = replace(ad->current_user_data->print_name, '_', " ");
			} else {
				elm_layout_file_set(layout, edj_path, "entry,receive,layout");
				elm_object_style_set(entry, "readmessage1");

				/* If you need to get the name, you need this code */
				/*
				char *sender_name = NULL;
				if (sel_item->use_data->peer_type == TGL_PEER_USER) {
					sender_name = replace(sel_item->use_data->print_name, '_', " ");
				} else if (sel_item->use_data->peer_type == TGL_PEER_CHAT) {
					int from_id = msg->from_id;
					// get name of buddy
					char* buddy_name = get_buddy_name_from_id(from_id);
					if (buddy_name) {
						sender_name = replace(buddy_name, '_', " ");
						free(buddy_name);
					}
				} else {
					sender_name = replace(sel_item->use_data->print_name, '_', " ");
				}
				*/
			}

			evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
			elm_object_part_content_set(layout,"elm.swallow.content", entry);
			evas_object_show(layout);

			elm_entry_input_panel_enabled_set(entry, EINA_FALSE);
			evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(entry);

			// To be handled for group chat

			Eina_Strbuf *buf = eina_strbuf_new();
			char *caption = NULL;

			LOGD("entry media type is %d", msg->media_type);

			if (msg->media_type == tgl_message_media_none) {
				char *temp_msg = replace(msg->message, '\n', "<br>");
				eina_strbuf_append(buf, temp_msg);
				elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
				eina_strbuf_free(buf);

			} else if(msg->media_type == tgl_message_media_photo || msg->media_type == tgl_message_media_document) {
				elm_entry_item_provider_append(entry, item_provider, chat_scroller);

				tgl_media_s *media_msg = get_media_details_from_db(atoll(msg->media_id));
				if (media_msg && media_msg->caption && strlen(media_msg->caption) > 0) {
					caption = strdup(media_msg->caption);
				}
				if (msg->out) {
					if (media_msg) {
						if (strstr(media_msg->doc_type, "audio") != NULL) {
							if (ad->target_direction == TELEGRAM_TARGET_DIRECTION_PORTRAIT || ad->target_direction == TELEGRAM_TARGET_DIRECTION_PORTRAIT_INVERSE) {
								eina_strbuf_append(buf, "<item size=318x100 vsize=full hsize=full href=itemprovider></item>");
							} else {
								eina_strbuf_append(buf, "<item size=318x100 vsize=full hsize=full href=itemprovider></item>");
							}

						} else if (strstr(media_msg->doc_type, "video") != NULL) {
							eina_strbuf_append(buf, "<item size=318x200 vsize=full hsize=full href=itemprovider></item>");
						} else {
							char image[256]={0,};
							_create_image_item(msg, entry, image, sizeof(image));
							eina_strbuf_append(buf, image);
						}
					}
				} else {
					if (media_msg) {
						if (strstr(media_msg->doc_type, "audio") != NULL) {
							eina_strbuf_append(buf, "<item size=318x100 vsize=full hsize=full href=itemprovider></item>");
						} else if (strstr(media_msg->doc_type, "video") != NULL) {
							eina_strbuf_append(buf, "<item size=318x200 vsize=full hsize=full href=itemprovider></item>");
						} else {
							char image[256]={0,};
							_create_image_item(msg, entry, image, sizeof(image));
							eina_strbuf_append(buf, image);
						}
					}
				}
				free_media_details(media_msg);
				elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
				eina_strbuf_free(buf);
			} else if(msg->media_type == tgl_message_media_geo) {

				tgl_media_s *media_msg = get_media_details_from_db(atoll(msg->media_id));

				char loc_url[4*256] = {0,};
				if (media_msg) {
					if (media_msg->caption && strlen(media_msg->caption) > 0) {
						caption = strdup(media_msg->caption);
					}
					snprintf(loc_url, sizeof(loc_url), "https://maps.google.com/?q=%s,%s", media_msg->latitude, media_msg->longitude);
					char temp_msg[4*256] = {0,};
					snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Normal|underline color=#0000FF align=left><font_size=15>%s</font_size></font>", loc_url);
					eina_strbuf_append(buf, temp_msg);
					elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
					eina_strbuf_free(buf);
				}

				free_media_details(media_msg);
				evas_object_data_set(entry, "media_type", (void*)strdup("location"));
				evas_object_data_set(entry, "location_url", (void*)strdup(loc_url));
				evas_object_smart_callback_add(entry, "clicked", on_media_chat_item_clicked, NULL);

			} else if(msg->media_type == tgl_message_media_contact) {

				tgl_media_s *media_msg = get_media_details_from_db(atoll(msg->media_id));

				if (media_msg) {
					if (media_msg->caption && strlen(media_msg->caption) > 0) {
						caption = strdup(media_msg->caption);
					}
					char temp_msg[4*256] = {0,};
					snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Normal|underline color=#000000 align=left><font_size=15>%s %s, %s</font_size></font>", media_msg->first_name, media_msg->last_name, media_msg->phone_no);
					eina_strbuf_append(buf, temp_msg);
					elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
					eina_strbuf_free(buf);
					free_media_details(media_msg);
				}

			} else if(msg->media_type == tgl_message_media_unsupported) {

			} else if(msg->media_type == tgl_message_media_photo_encr) {

			} else if(msg->media_type == tgl_message_media_document_encr) {

			} else  {

			}
			ad->loaded_msg_list = eina_list_append(ad->loaded_msg_list, entry);
			if (caption) {
				// implement UI.
				LOGD("caption is (%s)", caption);
				free(caption);
			}

			//set time
			time_t t = msg->date;
			const char *format = "%I:%M %p";
			struct tm lt;
			char res[32];
			(void) localtime_r(&t, &lt);

			if (strftime(res, sizeof(res), format, &lt) == 0) {
				(void) fprintf(stderr,  "strftime(3): cannot format supplied "
						"date/time into buffer of size %u "
						"using: '%s'\n",
						sizeof(res), format);
			}

			char time_str[20]={0,};
			snprintf(time_str, sizeof(time_str) - 1, "%s", res);
			elm_object_part_text_set(entry, "time", time_str);

			Evas_Object *status_obj;
			status_obj = elm_icon_add(entry);
			evas_object_size_hint_weight_set(status_obj, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(status_obj, EVAS_HINT_FILL, EVAS_HINT_FILL);

			if(msg->msg_state == TG_MESSAGE_STATE_SENDING) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENDING_ICON), NULL);
				elm_object_signal_emit(entry, "status_on", "status");
			} else if(msg->msg_state == TG_MESSAGE_STATE_SENT) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENT_ICON), NULL);
				elm_object_signal_emit(entry, "status_on", "status");
			} else if(msg->msg_state == TG_MESSAGE_STATE_DELIVERED) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_DELIVERED_ICON), NULL);
				elm_object_signal_emit(entry, "status_on", "status");
			} else if(msg->msg_state == TG_MESSAGE_STATE_RECEIVED) {
				elm_object_signal_emit(entry, "status_off", "status");
			} else if(msg->msg_state == TG_MESSAGE_STATE_FAILED) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_FAILED_ICON), NULL);
				elm_object_signal_emit(entry, "status_on", "status");
			} else if(msg->msg_state == TG_MESSAGE_STATE_READ) {
				elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_READ_ICON), NULL);
				elm_object_signal_emit(entry, "status_on", "status");
			} else if(msg->msg_state == TG_MESSAGE_STATE_UNKNOWN) {
				elm_object_signal_emit(entry, "status_off", "status");
			}

			elm_object_part_content_set(entry, "status_icon", status_obj);
			evas_object_show(status_obj);

			free(tablename);
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
#if 0
		if (chat_scroller) {
			int size = elm_genlist_items_count(chat_scroller);
			if (size > 0) {
				Elm_Object_Item *litem = elm_genlist_nth_item_get(chat_scroller, size -1);
				elm_genlist_item_show(litem, ELM_GENLIST_ITEM_SCROLLTO_TOP);
			}
		}
#endif
	}
	return layout;
}

void on_text_message_clicked(void *data, Evas_Object *obj, const char *emission, const char *source)
{

}

void on_text_message_received_from_buddy(appdata_s* ad, long long message_id, int type_of_chat)
{
	if (!ad) {
		return;
	}
	peer_with_pic_s* pic_peer_item = ad->peer_in_cahtting_data;
	tg_peer_info_s* peer_item = pic_peer_item->use_data;
	char* tablename = get_table_name_from_number(peer_item->peer_id);
	tg_message_s* msg = get_message_from_message_table(message_id, tablename);

	Evas_Object* chat_scroller = evas_object_data_get(ad->nf, "chat_list");
	Evas_Object *message = NULL;

	if (msg) {
			// update peer table
			if (peer_item) {
				peer_item->last_msg_id = msg->msg_id;
				peer_item->last_msg_date =  msg->date;
				insert_or_update_peer_into_database(peer_item);
			}

			Evas_Object *layout = evas_object_data_get(ad->nf, "main_layout");
			if (layout) {
				int is_end_edge = (int) evas_object_data_get(layout, "is_end_edge");
				if (!is_end_edge) {
					Evas_Object *bubble_layout = NULL;
					bubble_layout = elm_object_part_content_get(layout, "swallow.messagebubble");

					int user_id = (int) evas_object_data_get(chat_scroller, "user_id");
					peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
					char *sender_name = NULL;
					if (sel_item->use_data->peer_type == TGL_PEER_USER) {
						sender_name = replace(sel_item->use_data->print_name, '_', " ");
					} else if (sel_item->use_data->peer_type == TGL_PEER_CHAT) {
						int from_id = msg->from_id;
						// get name of buddy
						char* buddy_name = get_buddy_name_from_id(from_id);
						if (buddy_name) {
							sender_name = replace(buddy_name, '_', " ");
							free(buddy_name);
						}
					} else {
						sender_name = replace(sel_item->use_data->print_name, '_', " ");
					}

					elm_object_part_text_set(bubble_layout, "text_name", sender_name);
					elm_object_part_text_set(bubble_layout, "text_message", msg->message);
					elm_object_signal_emit(layout, "show", "bubblemessage");
				}
			}

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
	free(tablename);

	message = on_message_item_content_get_cb((void *)message_id, chat_scroller, "elm.icon.entry");
	elm_object_signal_callback_add(message, "clicked", "item", on_text_message_clicked, (void*)message_id);
	scroller_push_item(chat_scroller, message);

	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");
	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	send_request_for_marked_as_read(ad, ad->service_client, sel_item->use_data->peer_id, sel_item->use_data->peer_type);
	ad->is_last_msg_changed = EINA_TRUE;
	on_user_presence_state_changed(ad, sel_item->use_data->peer_id);
}


void on_media_download_completed(appdata_s* ad, int buddy_id, long long media_id, const char *file_path, const char *caption)
{
	if (!ad)
		return;

	if (ad->loaded_msg_list && eina_list_count(ad->loaded_msg_list) > 0) {
		for (int i = eina_list_count(ad->loaded_msg_list) - 1 ; i >= 0; i--) {
			Evas_Object* entry = eina_list_nth(ad->loaded_msg_list, i);
			if (entry) {

				char* media_type_str = evas_object_data_get(entry, "media_type");
				char* media_id_str = evas_object_data_get(entry, "media_id");
				char* media_size_str = evas_object_data_get(entry, "image_size");
				Evas_Object *img_item = evas_object_data_get(entry, "image_object");
				Evas_Object *size_btn = evas_object_data_get(entry, "button_object");

				if (media_id_str) {

					long long lmedia_id = atoll(media_id_str);

					if (media_id == lmedia_id) {
						if (img_item || (strstr(media_type_str, "audio") != NULL)) {


							if (strstr(file_path, "failed_to_load") != NULL) {

								if ((strstr(media_type_str, "audio") != NULL)) {
									Evas_Object *play_pause_icon = evas_object_data_get(entry, "play_pause_icon");
									Evas_Object *progressbar = evas_object_data_get(entry, "progress_bar");
									evas_object_data_set(progressbar, "is_download_in_progress", EINA_FALSE);
									evas_object_data_set(play_pause_icon, "audio_file_path", NULL);
									//sandeep
									elm_object_style_set(progressbar, "default");
									return;
								}

								// download failed.
								if (size_btn) {
									Evas_Object* progress = elm_object_part_content_get(size_btn, "download_image");
									if (progress) {
										evas_object_del(progress);
									}
									Evas_Object* download_img = get_image_from_path(ui_utils_get_resource(MEDIA_DOWNLOAD_ICON), size_btn);
									elm_object_part_content_set(size_btn, "download_image", download_img);
									evas_object_data_set(size_btn, "image_state", "ready_to_download");
									char temp_msg[256] = {0,};
									snprintf(temp_msg, sizeof(temp_msg), "<font=Tizen:style=Bold color=#008000 align=center><font_size=30>%s</font_size></font>", media_size_str);
									elm_object_text_set(size_btn, temp_msg);
								}


							} else {

								if ((strstr(media_type_str, "audio") != NULL)) {
									Evas_Object *play_pause_icon = evas_object_data_get(entry, "play_pause_icon");
									Evas_Object *progressbar = evas_object_data_get(entry, "progress_bar");
									evas_object_data_set(progressbar, "is_download_in_progress", EINA_FALSE);
									elm_object_style_set(progressbar, "default");
									evas_object_data_set(play_pause_icon, "audio_file_path", file_path);
									//sandeep
									metadata_extractor_h metadata;
									metadata_extractor_create(&metadata);
									int ret = metadata_extractor_set_path(metadata, file_path);
									char *value = NULL;
									ret = metadata_extractor_get_metadata(metadata, METADATA_DURATION, &value);
									metadata_extractor_destroy(metadata);

									int duration = 0;
									if (value) {
										duration = atoi(value);
										free(value);
									}

									elm_object_part_text_set(progressbar, "elm.text.top.left", "");
									elm_object_part_text_set(progressbar, "elm.text.top.right", "");

									return;
								}

								if (size_btn) {
									evas_object_del(size_btn);
								}

								if ((strstr(media_type_str, "video") != NULL)) {
									Evas_Object* play_img = get_video_paly_icon(img_item);
									//Evas_Object* play_img = get_image_from_path(ui_utils_get_resource(MEDIA_PLAY_ICON), img_item);
									elm_object_part_content_set(img_item, "swallow.play_btn", play_img);
								} else if (strstr(media_type_str, "image") != NULL) {

									img_item = get_image_from_path(file_path, entry);
									int w, h, entry_h;
									elm_image_object_size_get(img_item, &w, &h);
									entry_h = (318 * h) / w;
									Eina_Strbuf *buf = eina_strbuf_new();
									char image[256]={0,};
									evas_object_data_set(entry, "img_object", img_item);
									snprintf(image, sizeof(image) - 1, "<item size=318x%d vsize=full href=itemprovider></item>", entry_h);
									eina_strbuf_append(buf, image);
									elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
									eina_strbuf_free(buf);

								} else if (strstr(media_type_str, "animated_image") != NULL) {

									int msg_id = (int) evas_object_data_get(entry, "message_id");
									char key[256] = {0, };
									snprintf(key, sizeof(key), "%d", msg_id);

									img_item = get_gif_image_from_path(file_path, entry, key);
									elm_image_animated_set(img_item, EINA_TRUE);
									elm_image_animated_play_set(img_item, EINA_TRUE);
									int w, h, entry_h;
									elm_image_object_size_get(img_item, &w, &h);
									entry_h = (318 * h) / w;
									evas_object_data_set(entry, "img_object", img_item);
									Eina_Strbuf *buf = eina_strbuf_new();
									char image[256]={0,};
									snprintf(image, sizeof(image) - 1, "<item size=318x%d vsize=full href=itemprovider></item>", entry_h);
									eina_strbuf_append(buf, image);
									elm_entry_entry_set(entry, eina_strbuf_string_get(buf));
									eina_strbuf_free(buf);
								}
							}
						}
					}

				}
			}
		}
	}
}

//elm_object_part_content_set(comp_img_layout, "swallow.chat_send_image", image);

void on_video_thumb_download_completed(appdata_s* ad, int buddy_id, long long media_id, const char* file_path, const char *caption)
{
	on_media_download_completed(ad, buddy_id, media_id, file_path, caption);
}

void on_text_message_state_changed(appdata_s* ad, tg_message_s *msg, int type_of_chat)
{
	if (!ad)
		return;

#if 0
	peer_with_pic_s* pic_peer_item = ad->peer_in_cahtting_data;
	if (pic_peer_item) {
		tg_peer_info_s* peer_item = pic_peer_item->use_data;
		// update peer table
		if (peer_item) {
			peer_item->last_msg_id = msg->msg_id;
			peer_item->last_msg_date =  msg->date;
			insert_or_update_peer_into_database(peer_item);
		}
	}
#endif
	if (ad->loaded_msg_list && eina_list_count(ad->loaded_msg_list) > 0) {
		for (int i = eina_list_count(ad->loaded_msg_list) - 1 ; i >= 0; i--) {
			Evas_Object* entry = eina_list_nth(ad->loaded_msg_list, i);

			if (entry) {
				int message_id = (int)evas_object_data_get(entry, "message_id");
				if (message_id == msg->msg_id || message_id == msg->unique_id) {

					evas_object_data_set(entry, "media_id", (void*)strdup(msg->media_id));
					evas_object_data_set(entry, "message_id", (void*)message_id);

					Evas_Object* status_obj = elm_object_part_content_get(entry, "status_icon");
					if (status_obj) {
						if(msg->msg_state == TG_MESSAGE_STATE_SENDING) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENDING_ICON), NULL);
							elm_object_signal_emit(entry, "status_on", "status");
						} else if(msg->msg_state == TG_MESSAGE_STATE_SENT) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENT_ICON), NULL);
							elm_object_signal_emit(entry, "status_on", "status");
						} else if(msg->msg_state == TG_MESSAGE_STATE_DELIVERED) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_DELIVERED_ICON), NULL);
							elm_object_signal_emit(entry, "status_on", "status");
						} else if(msg->msg_state == TG_MESSAGE_STATE_RECEIVED) {
							elm_object_signal_emit(entry, "status_off", "status");
						} else if(msg->msg_state == TG_MESSAGE_STATE_FAILED) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_FAILED_ICON), NULL);
							elm_object_signal_emit(entry, "status_on", "status");
						} else if(msg->msg_state == TG_MESSAGE_STATE_READ) {
							elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_READ_ICON), NULL);
							elm_object_signal_emit(entry, "status_on", "status");
						} else if(msg->msg_state == TG_MESSAGE_STATE_UNKNOWN) {
							elm_object_signal_emit(entry, "status_off", "status");
						}
					}
					return;
				}
			}
		}
	}
}

Eina_Bool add_date_item_to_chat(void *data)
{
	Evas_Object *chat_scroller = data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	char* msg_table = get_table_name_from_number(sel_item->use_data->peer_id);
	create_buddy_msg_table(msg_table);
	int msg_id = insert_current_date_to_table(msg_table);
	free(msg_table);

	if (msg_id > 0) {
		// send request to service
		Evas_Object *message = NULL;

		message = on_message_item_content_get_cb((void *)msg_id, chat_scroller, "elm.icon.entry");
		elm_object_signal_callback_add(message, "clicked", "item", on_text_message_clicked, (void*)msg_id);
		scroller_push_item(chat_scroller, message);

		ad->is_last_msg_changed = EINA_TRUE;
		return EINA_TRUE;
	}
	return EINA_FALSE;
}



static Eina_Bool on_new_text_message_send_cb(void *data)
{
	Evas_Object *chat_scroller = data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");
	Evas_Object *text_entry = evas_object_data_get(chat_scroller, "text_entry");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	const char* text_to_send = elm_entry_entry_get(text_entry);
	if (!text_to_send || (strlen(text_to_send) == 0))
		return ECORE_CALLBACK_CANCEL;

	int unique_id = get_time_stamp_in_macro();
	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = 0;
	msg.message = (char*)text_to_send;
	msg.message_len = strlen(text_to_send);
	msg.media_type = tgl_message_media_none;
	msg.media_id = "";
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;
	msg.is_marked_for_delete = 0;
	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	free(msg_table);

	peer_with_pic_s* pic_peer_item = ad->peer_in_cahtting_data;
	if (pic_peer_item) {
		tg_peer_info_s* peer_item = pic_peer_item->use_data;
		// update peer table
		if (peer_item) {
			peer_item->last_msg_id = msg.msg_id;
			peer_item->last_msg_date =  msg.date;
			insert_or_update_peer_into_database(peer_item);
		}
	}

	// send request to service
	send_request_for_message_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, tgl_message_media_none, text_to_send, sel_item->use_data->peer_type);

	Evas_Object *message = NULL;

	message = on_message_item_content_get_cb((void *)unique_id, chat_scroller, "elm.icon.entry");
	elm_object_signal_callback_add(message, "clicked", "item", on_text_message_clicked, (void*)unique_id);
	scroller_push_item(chat_scroller, message);

	elm_entry_entry_set(text_entry, "");
	ad->is_last_msg_changed = EINA_TRUE;
	return ECORE_CALLBACK_CANCEL;
}

static void on_text_message_send_clicked(void *data, Evas_Object *obj, const char *emission, const char *source)
{
	Evas_Object* chat_scroller = data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");
	Evas_Object* text_entry = evas_object_data_get(chat_scroller, "text_entry");
	int ret = 1;

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
	const char* text_to_send = elm_entry_markup_to_utf8(elm_object_text_get(text_entry));
	if (!text_to_send || (strlen(text_to_send) == 0))
		return;

	if (add_date_item_to_chat(data)) {
		//ecore_timer_add(2, on_new_text_message_send_cb, chat_scroller);
		//return;
		wait_for(1);
	}

	int unique_id = get_time_stamp_in_macro();
	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = 0;
	msg.message = (char*)text_to_send;
	msg.message_len = strlen(text_to_send);
	msg.media_type = tgl_message_media_none;
	msg.media_id = "";
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;
	msg.is_marked_for_delete = 0;
	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	free(msg_table);

	peer_with_pic_s* pic_peer_item = ad->peer_in_cahtting_data;
	if (pic_peer_item) {
		tg_peer_info_s* peer_item = pic_peer_item->use_data;
		// update peer table
		if (peer_item) {
			peer_item->last_msg_id = msg.msg_id;
			peer_item->last_msg_date =  msg.date;
			insert_or_update_peer_into_database(peer_item);
		}
	}

	// send request to service
	send_request_for_message_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, tgl_message_media_none, text_to_send, sel_item->use_data->peer_type);

	Evas_Object *message = NULL;

	Evas_Object *layout = evas_object_data_get(ad->nf, "main_layout");
	evas_object_data_set(layout, "is_end_edge", (void *) 1);

	message = on_message_item_content_get_cb((void *)unique_id, chat_scroller, "elm.icon.entry");
	elm_object_signal_callback_add(message, "clicked", "item", on_text_message_clicked, (void*)unique_id);
	scroller_push_item(chat_scroller, message);

	elm_entry_entry_set(text_entry, "");
	ad->is_last_msg_changed = EINA_TRUE;
}

void on_user_status_changed(appdata_s* ad, char* status)
{
	if (!ad || !status)
		return;

	Elm_Object_Item *nf_it = evas_object_data_get(ad->nf, "navi_item");
	char status_str[256]={0,};
	snprintf(status_str, sizeof(status_str) - 1, "%s", status);
	elm_object_item_part_text_set(nf_it, "subtitle", status_str);
}

static void compare_with_current_date(int rtime, Elm_Object_Item *nf_it)
{
	char time_str[256]={0,};
	time_t local_t = time(NULL);
	int diff_sec = 0;
	int diff_min = 0;
	int diff_hour = 0;
	int diff_day = 0;

	diff_sec = local_t - rtime;
	diff_min = diff_sec / 60;
	diff_hour = diff_min / 60;
	diff_day = diff_hour / 24;
	LOGD("different : day : %d, hour = %d, min = %d, sec = %d", diff_day, diff_hour, diff_min, diff_sec);


	if (diff_day > 30) {
		snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_LONG_TIME_AGO_ABB"));
		goto OUT;
	}

	if (diff_day > 7) {
		snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_WITHIN_A_MONTH_ABB"));
		goto OUT;
	}
	if (diff_day > 1) {
		snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_WITHIN_A_WEEK_ABB"));
		goto OUT;
	}

	if (diff_hour > 1) {
		snprintf(time_str, sizeof(time_str) - 1, i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_PD_HOURS_AGO_ABB"), diff_hour);
		goto OUT;
	}

	if (diff_hour == 1) {
		snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_1_HOUR_AGO_ABB"));
		goto OUT;
	}
	if (diff_min > 1) {
		snprintf(time_str, sizeof(time_str) - 1, i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_PD_MINUTES_AGO_ABB"), diff_min);
		goto OUT;
	}
	if (diff_min == 1) {
		snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_1_MINUTE_AGO_ABB"));
		goto OUT;
	}
	snprintf(time_str, sizeof(time_str) - 1, "%s", i18n_get_text("IDS_TGRAM_HEADER_LAST_SEEN_RECENTLY_ABB"));

OUT:
	elm_object_item_part_text_set(nf_it, "subtitle", time_str);
}

void on_user_presence_state_changed(appdata_s* ad, int buddy_id)
{
	if (!ad)
		return;
	int type_of_chat = ad->peer_in_cahtting_data->use_data->peer_type;
	Elm_Object_Item *nf_it = evas_object_data_get(ad->nf, "navi_item");

	if (type_of_chat == TGL_PEER_USER) {

		Eina_List* buddy_details_array = get_buddy_info(buddy_id);
		if (buddy_details_array && eina_list_count(buddy_details_array) > 0) {
			Eina_List* buddy_details = eina_list_nth(buddy_details_array, 0);
			if (buddy_details && eina_list_count(buddy_details) > 0) {
				int* temp_online = (int*)eina_list_nth(buddy_details, 12);
				int is_online = *temp_online;
				int* temp_last_seen = (int*)eina_list_nth(buddy_details, 13);
				int last_seen = *temp_last_seen;

				if (is_online > 0) {
					char status_str[256]={0,};
					snprintf(status_str, sizeof(status_str) - 1, "%s", i18n_get_text("IDS_TGRAM_SBODY_ONLINE"));
					elm_object_item_part_text_set(nf_it, "subtitle", status_str);
				} else {
					compare_with_current_date(last_seen, nf_it);
				}

				for (int i = 0 ; i < eina_list_count(buddy_details_array); i++) {
					void* val = eina_list_nth(buddy_details, i);
					free(val);
				}
				eina_list_free(buddy_details);
			}
			eina_list_free(buddy_details_array);
		}

	} else if (type_of_chat == TGL_PEER_CHAT) {

		tg_chat_info_s* chat_info = get_chat_info(buddy_id);
		if (!chat_info) {
			char status_str[256]={0,};
			snprintf(status_str, sizeof(status_str) - 1, "Unidentified.");
			elm_object_item_part_text_set(nf_it, "subtitle", status_str);
			return;
		}

		int user_list_size = chat_info->user_list_size;
		int online_members = 0;

		char *names_of_buddies = NULL;


		for (int i = 0; i < user_list_size; i++) {

			int is_online = get_buddy_online_status(chat_info->chat_users[i]);
			if (is_online > 0) {
				online_members++;
			}

			char *buddy_full_name = get_buddy_name_from_id(chat_info->chat_users[i]);
			if (buddy_full_name) {
				char *buddy_name =  replace(buddy_full_name, '_', " ");
				if (buddy_name) {
					if (!names_of_buddies) {
						names_of_buddies = (char*)malloc(strlen(buddy_name) + 1);
						strcpy(names_of_buddies, buddy_name);
					} else {
						names_of_buddies = (char*)realloc(names_of_buddies, strlen(names_of_buddies) + strlen(" / ") + strlen(buddy_name) + 1);
						strcat(names_of_buddies, " / ");
						strcat(names_of_buddies, buddy_name);
					}
				}
			}
		}

		evas_object_data_set(ad->nf, "names_of_buddies", (void*)names_of_buddies);

#if 0
		if (online_members == 0) {
			char status_str[256]={0,};
			snprintf(status_str, sizeof(status_str) - 1, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=30>%d %s</font_size></font>", user_list_size, i18n_get_text("IDS_TGRAM_BODY_PD_PARTICIPANTS"));
			elm_object_item_part_text_set(nf_it, "subtitle", status_str);
		} else {
			char status_str[256]={0,};
			snprintf(status_str, sizeof(status_str) - 1, "<font=Tizen:style=Bold color=#ffffff align=left><font_size=30>%d %s, %d %s</font_size></font>", user_list_size, , online_members, i18n_get_text("IDS_TGRAM_SBODY_ONLINE"));
			elm_object_item_part_text_set(nf_it, "subtitle", status_str);
		}
#else
		char status_str[256]={0,};
		snprintf(status_str, sizeof(status_str) - 1, i18n_get_text("IDS_TGRAM_BODY_PD_PARTICIPANTS"), user_list_size);

		char temp_status_str[512]={0,};
		snprintf(temp_status_str, sizeof(temp_status_str) - 1, "%s", status_str);

		elm_object_item_part_text_set(nf_it, "subtitle", temp_status_str);
#endif

		if (chat_info) {
			if(chat_info->print_title) {
				free(chat_info->print_title);
				chat_info->print_title = NULL;
			}
			if(chat_info->photo_path) {
				free(chat_info->photo_path);
				chat_info->photo_path = NULL;
			}
			if(chat_info->title) {
				free(chat_info->title);
				chat_info->title = NULL;
			}

		}
	}
}

static Eina_Bool on_change_input_type_requested(void *data)
{
	Evas_Object* text_entry = data;
	if (!text_entry) {
		LOGE("Fail to get the text_entry");
		return ECORE_CALLBACK_CANCEL;
	}
	elm_object_focus_set(text_entry, EINA_TRUE);
	elm_entry_input_panel_layout_set(text_entry, ELM_INPUT_PANEL_LAYOUT_EMOTICON);
	elm_entry_input_panel_show(text_entry);

	return ECORE_CALLBACK_CANCEL;
}

static void on_message_cancel_clicked(void *data, Evas_Object *obj, const char *emission, const char *source)
{
	Evas_Object *layout = data;
	if (!layout) {
		LOGE("Fail to get the layout");
		return;
	}
	elm_object_signal_emit(layout, "hide", "bubblemessage");
}

static void on_message_smiley_clicked(void *data, Evas_Object *obj, const char *emission, const char *source)
{
	Evas_Object* text_entry = data;
	if (!text_entry) {
		LOGE("Fail to get the text_entry");
		return;
	}
	ecore_timer_add(0.3, on_change_input_type_requested, text_entry);
}

static void on_message_text_entry_clicked(void *data, Evas_Object *obj, void *event_info)
{
	if (!obj) {
		LOGE("Fail to get the entry");
		return;
	}
	/* This Api is needed for type of keyboard: emoticon or caractor */
	elm_entry_input_panel_layout_set(obj, ELM_INPUT_PANEL_LAYOUT_NORMAL);
}

static void on_message_text_entry_changed(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *layout = data;

	if (!layout) {
		LOGE("Fail to get the entry layout");
		return;
	}
	int attach_show = (int) evas_object_data_get(layout, "is_attach_show");

	if (elm_entry_is_empty(obj)) {
		if (!attach_show) {
			elm_object_signal_emit(layout, "show", "attach_btn");
			evas_object_data_set(layout, "is_attach_show", (void *) 1);
		}
	} else {
		if (attach_show) {
			elm_object_signal_emit(layout, "hide", "attach_btn");
			evas_object_data_set(layout, "is_attach_show", (void *) 0);
		}
	}
}

Evas_Object* create_chat_genlist(Evas_Object *win)
{
    Evas_Object *genlist;
    Elm_Theme *theme = elm_theme_new();
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_GENLIST_THEME_EDJ, edj_path, (int)PATH_MAX);
	elm_theme_extension_add(theme, edj_path);
    genlist = elm_genlist_add(win);
    elm_object_theme_set(genlist, theme);
    elm_object_style_set(genlist, "telegram/default");
    evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);
    return genlist;
}

void on_list_media_item_clicked(void *data, Evas_Object *obj, const char *emission, const char *source)
{

}

static Eina_Bool on_new_contact_message_send_cb(void *data)
{
	Evas_Object *chat_scroller = data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	int unique_id = time(NULL);

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = tgl_message_media_contact;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;
	msg.is_marked_for_delete = 0;

	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;

	char *first_name = evas_object_data_get(chat_scroller, "contact_first_name");
	char *last_name = evas_object_data_get(chat_scroller, "contact_last_name");
	char *phone_number = evas_object_data_get(chat_scroller, "contact_phone_number");

	insert_media_info_to_db(&msg, NULL, img_width, img_height, media_size, NULL, NULL, first_name, last_name, phone_number);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, tgl_message_media_contact, NULL, sel_item->use_data->peer_type);

	Evas_Object *message = NULL;

	message = on_message_item_content_get_cb((void *)unique_id, chat_scroller, "elm.icon.entry");
	elm_object_signal_callback_add(message, "clicked", "item", on_list_media_item_clicked, (void*)unique_id);
	scroller_push_item(chat_scroller, message);

	free(msg.media_id);

	return ECORE_CALLBACK_CANCEL;

}

void send_contact_message_to_buddy(void *data, char *first_name, char *last_name, char *phone_number)
{
	Evas_Object *chat_scroller = data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");

	if (add_date_item_to_chat(data)) {
/*		evas_object_data_set(chat_scroller, "contact_first_name", strdup(first_name));
		evas_object_data_set(chat_scroller, "contact_last_name", strdup(last_name));
		evas_object_data_set(chat_scroller, "contact_phone_number", strdup(phone_number));

		ecore_timer_add(2, on_new_contact_message_send_cb, chat_scroller);
		return;*/
		wait_for(1);
	}

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	int unique_id = get_time_stamp_in_macro();

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = tgl_message_media_contact;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;
	msg.is_marked_for_delete = 0;

	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;
	insert_media_info_to_db(&msg, NULL, img_width, img_height, media_size, NULL, NULL, first_name, last_name, phone_number);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, tgl_message_media_contact, NULL, sel_item->use_data->peer_type);

	Evas_Object *message = NULL;

	message = on_message_item_content_get_cb((void *)unique_id, chat_scroller, "elm.icon.entry");
	elm_object_signal_callback_add(message, "clicked", "item", on_list_media_item_clicked, (void*)unique_id);
	scroller_push_item(chat_scroller, message);
	free(msg.media_id);
}

static Eina_Bool on_new_location_message_send_cb(void *data)
{
	Evas_Object *chat_scroller = data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	int unique_id = time(NULL);

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = tgl_message_media_geo;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;
	msg.is_marked_for_delete = 0;

	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;

	char *latitude = evas_object_data_get(chat_scroller, "contact_latitude");
	char *longitude = evas_object_data_get(chat_scroller, "contact_longitude");

	insert_media_info_to_db(&msg, NULL, img_width, img_height, media_size, latitude, longitude, NULL, NULL, NULL);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, tgl_message_media_geo, NULL, sel_item->use_data->peer_type);

	Evas_Object *message = NULL;

	message = on_message_item_content_get_cb((void *)unique_id, chat_scroller, "elm.icon.entry");
	elm_object_signal_callback_add(message, "clicked", "item", on_list_media_item_clicked, (void*)unique_id);
	scroller_push_item(chat_scroller, message);

	free(msg.media_id);
	return ECORE_CALLBACK_CANCEL;
}

void send_location_message_to_buddy(void *data, char *latitude, char *longitude)
{
	Evas_Object *chat_scroller = data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");

	if (add_date_item_to_chat(data)) {
/*		evas_object_data_set(chat_scroller, "contact_latitude", strdup(latitude));
		evas_object_data_set(chat_scroller, "contact_longitude", strdup(longitude));
		ecore_timer_add(2, on_new_location_message_send_cb, chat_scroller);
		return;*/
		wait_for(1);
	}

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	int unique_id = get_time_stamp_in_macro();

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = tgl_message_media_geo;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;
	msg.is_marked_for_delete = 0;

	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;
	insert_media_info_to_db(&msg, NULL, img_width, img_height, media_size, latitude, longitude, NULL, NULL, NULL);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, tgl_message_media_geo, NULL, sel_item->use_data->peer_type);

	Evas_Object *message = NULL;

	message = on_message_item_content_get_cb((void *)unique_id, chat_scroller, "elm.icon.entry");
	elm_object_signal_callback_add(message, "clicked", "item", on_list_media_item_clicked, (void*)unique_id);
	scroller_push_item(chat_scroller, message);

	free(msg.media_id);
}

static Eina_Bool on_new_media_message_send_cb(void *data)
{
	Evas_Object *chat_scroller = data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	int unique_id = time(NULL);

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	char *file_type_char = evas_object_data_get(chat_scroller, "file_type");
	int file_type = atoi(file_type_char);
	char *file_path = evas_object_data_get(chat_scroller, "file_path");

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = file_type;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;
	msg.is_marked_for_delete = 0;

	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;
	if (file_type == tgl_message_media_photo) {
		Evas_Object *img = create_image_object_from_file(file_path, chat_scroller);
		elm_image_object_size_get(img, &img_width, &img_height);
		struct stat st;
		stat(file_path, &st);
		media_size = st.st_size;
		evas_object_del(img);
	}

	insert_media_info_to_db(&msg, (char*)file_path, img_width, img_height, media_size, NULL, NULL , NULL, NULL, NULL);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, file_type, file_path, sel_item->use_data->peer_type);

	Evas_Object *message = NULL;

	message = on_message_item_content_get_cb((void *)unique_id, chat_scroller, "elm.icon.entry");
	elm_object_signal_callback_add(message, "clicked", "item", on_list_media_item_clicked, (void*)unique_id);
	scroller_push_item(chat_scroller, message);

	free(msg.media_id);
	ad->is_last_msg_changed = EINA_TRUE;
	return ECORE_CALLBACK_CANCEL;
}

void send_media_message_to_buddy(void *data, const char* file_path, enum tgl_message_media_type file_type)
{
	Evas_Object *chat_scroller = data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");
	if (add_date_item_to_chat(data)) {
/*		int temp_file_type = file_type;
		char file_type_char[10]= {0, };
		sprintf(file_type_char, "%d", temp_file_type);
		evas_object_data_set(chat_scroller, "file_type", strdup(file_type_char));
		evas_object_data_set(chat_scroller, "file_path", strdup(file_path));

		ecore_timer_add(2, on_new_media_message_send_cb, chat_scroller);
		return;*/
		wait_for(1);
	}
	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);

	int unique_id = get_time_stamp_in_macro();

	char unique_id_str[50];
	sprintf(unique_id_str, "%d", unique_id);

	tg_message_s msg;
	msg.msg_id = unique_id;
	msg.from_id = ad->current_user_data->user_id.id;
	msg.date = time(NULL);
	msg.flags = 0;
	msg.fwd_date = 0;
	msg.fwd_from_id= 0;
	msg.fwd_from_id = 0;
	msg.unique_id = unique_id;
	msg.message = "";
	msg.message_len = 0;
	msg.media_type = file_type;
	msg.media_id = strdup(unique_id_str);
	msg.out = 1;
	msg.service = 0;
	msg.to_id = sel_item->use_data->peer_id;
	msg.unread = 0;
	msg.msg_state = TG_MESSAGE_STATE_SENDING;
	msg.is_marked_for_delete = 0;

	char* msg_table = get_table_name_from_number(msg.to_id);
	create_buddy_msg_table(msg_table);
	insert_msg_into_db(&msg, msg_table, unique_id);
	int img_width = 0;
	int img_height = 0;
	int media_size = 0;
	if (file_type == tgl_message_media_photo) {
		Evas_Object* img = create_image_object_from_file(file_path, chat_scroller);
		elm_image_object_size_get(img, &img_width, &img_height);
		struct stat st;
		stat(file_path, &st);
		media_size = st.st_size;
		evas_object_del(img);
	}

	insert_media_info_to_db(&msg, (char*)file_path, img_width, img_height, media_size, NULL, NULL , NULL, NULL, NULL);

	free(msg_table);

	// send request to service
	send_request_for_media_transport(ad, ad->service_client, sel_item->use_data->peer_id, msg.msg_id, unique_id, file_type, file_path, sel_item->use_data->peer_type);

	Evas_Object *message = NULL;

	message = on_message_item_content_get_cb((void *)unique_id, chat_scroller, "elm.icon.entry");
	elm_object_signal_callback_add(message, "clicked", "item", on_list_media_item_clicked, (void*)unique_id);
	scroller_push_item(chat_scroller, message);

	free(msg.media_id);
	ad->is_last_msg_changed = EINA_TRUE;
}

static Eina_Bool on_timer_expired(void *data)
{
	Evas_Object *scroller = data;
	int ret = 1;

	if (!scroller) {
		LOGE("Cannot get the scroller");
		return ECORE_CALLBACK_CANCEL;
	}
	ret = scroller_show_bottom_edge(scroller);
	if (!ret) {
		LOGE("Fail to show the bottom of scroller");
	}

	return ECORE_CALLBACK_CANCEL;
}

Eina_Bool load_chat_history(Evas_Object *chat_scroller)
{
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	int user_id = (int)evas_object_data_get(chat_scroller, "user_id");

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
	int buddy_id = sel_item->use_data->peer_id;

	char* tablename = get_table_name_from_number(buddy_id);

	Eina_List* col_types = NULL;
	col_types = eina_list_append(col_types, TG_DB_COLUMN_INTEGER);

	Eina_List* col_names = NULL;
	col_names = eina_list_append(col_names, MESSAGE_INFO_TABLE_MESSAGE_ID);

	char unknown_str[50];
	int unknown = 0;
	sprintf(unknown_str, "%d", unknown);

	char* where_clause = (char*)malloc(strlen(MESSAGE_INFO_TABLE_MARKED_FOR_DELETE) + strlen(" = ") + strlen(unknown_str) + 1);
	strcpy(where_clause, MESSAGE_INFO_TABLE_MARKED_FOR_DELETE);
	strcat(where_clause, " = ");
	strcat(where_clause, unknown_str);

	Eina_List* vals = get_values_from_table_sync_order_by(tablename, col_names, col_types, MESSAGE_INFO_TABLE_DATE, EINA_TRUE, where_clause);
	if(!vals) {
		// set no messages yet
		return EINA_FALSE;
	} else {
		int row_count = eina_list_count(vals);

		if (row_count <= 0) {
			// set no messages yet
			return EINA_FALSE;
		}

		for (int i = 0 ; i < row_count ; i++) {
			Eina_List* row_vals = eina_list_nth(vals, i);
			int* temp_message_id = (int*)eina_list_nth(row_vals, 0);
			int message_id = *temp_message_id;
			Evas_Object *message = NULL;

			message = on_message_item_content_get_cb((void *)message_id, chat_scroller, "elm.icon.entry");
			elm_object_signal_callback_add(message, "clicked", "item", on_list_media_item_clicked, (void*)message_id);
			scroller_push_item(chat_scroller, message);

			eina_list_free(row_vals);
		}
		eina_list_free(vals);
	}

	Ecore_Timer *timer = NULL;
	timer = ecore_timer_add(0.1, on_timer_expired, chat_scroller);

	free(tablename);
	return EINA_TRUE;
}



void on_gallery_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		Evas_Object* chat_scroller = user_data;
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		int status;
		char* mime_type = NULL;
		appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");

		status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);
		if (status != APP_CONTROL_ERROR_NONE) {
			status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_PATH, &path_arryay,  &array_length);
			if (status != APP_CONTROL_ERROR_NONE) {
				if (ad) {
					show_toast(ad, "Unable to get the result from attach panel");
				}
				return;
			}
		}

		status = app_control_get_mime(reply, &mime_type);
		if (status != APP_CONTROL_ERROR_NONE) {
			if (ad) {
				show_toast(ad, "Unable to get the mime type from attach panel");
			}
			return;
		}

		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);
			send_media_message_to_buddy(chat_scroller, file_path, tgl_message_media_photo);
			free(file_path);
			//break;
		}
	}
}

void on_location_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	Evas_Object* chat_scroller = user_data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		char *latitude = NULL;
		char *longitude = NULL;
		app_control_get_extra_data(reply, "latitude", &latitude);
		app_control_get_extra_data(reply, "longitude", &longitude);

		if (latitude && longitude) {
			send_location_message_to_buddy(chat_scroller, latitude, longitude);
		} else {
			//send_location_message_to_buddy(chat_scroller, "0.00000000000", "0.00000000000");
			show_toast(ad, "Unable to detect location values.");
		}
	} else {
		show_toast(ad, "Device does not support location feature.");
	}
}

void on_video_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {

		Evas_Object* chat_scroller = user_data;
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		int status;
		char* mime_type = NULL;
		appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");

		status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);
		if (status != APP_CONTROL_ERROR_NONE) {
			status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_PATH, &path_arryay,  &array_length);
			if (status != APP_CONTROL_ERROR_NONE) {
				if (ad) {
					show_toast(ad, "Unable to get the result from attach panel");
				}
				return;
			}
		}

		status = app_control_get_mime(reply, &mime_type);
		if (status != APP_CONTROL_ERROR_NONE) {
			if (ad) {
				show_toast(ad, "Unable to get the mime type from attach panel");
			}
			return;
		}
		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);
			send_media_message_to_buddy(chat_scroller, file_path, tgl_message_media_document);
			free(file_path);
			//break;
		}
	}
}

void on_file_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {

		Evas_Object* chat_scroller = user_data;
		appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);

		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);

			// get mime type of the file

			char *mime_type = NULL;
			if (file_path) {
				char *extn = strrchr(file_path, '.');
				if (extn) {
					extn = replace(extn, '.', "");
				}
				if (extn) {
					mime_type_get_mime_type(extn, &mime_type);
				}
			}
			if (mime_type) {
				if (strstr(mime_type, "video") != NULL) {
					send_media_message_to_buddy(chat_scroller, file_path, tgl_message_media_document);
				} else if (strstr(mime_type, "audio") != NULL) {
					send_media_message_to_buddy(chat_scroller, file_path, tgl_message_media_document);
				} else if (strstr(mime_type, "image") != NULL) {
					send_media_message_to_buddy(chat_scroller, file_path, tgl_message_media_photo);
				} else {
					show_toast(ad, "Unsupported file.");
				}
			} else {
				show_toast(ad, "Unsupported file.");
			}
			free(file_path);
			break;
		}
	}
}

static void on_voice_record_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {
		Evas_Object* chat_scroller = user_data;

		char* file_path = NULL;
		char** path_arryay = NULL;
		int array_length = 0;
		int status;
		char* mime_type = NULL;
		appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");

		status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_SELECTED, &path_arryay,  &array_length);
		if (status != APP_CONTROL_ERROR_NONE) {
			status = app_control_get_extra_data_array(reply, APP_CONTROL_DATA_PATH, &path_arryay,  &array_length);
			if (status != APP_CONTROL_ERROR_NONE) {
				if (ad) {
					show_toast(ad, "Unable to get the result from attach panel");
				}
				return;
			}
		}

		status = app_control_get_mime(reply, &mime_type);
		if (status != APP_CONTROL_ERROR_NONE) {
			if (ad) {
				show_toast(ad, "Unable to get the mime type from attach panel");
			}
			return;
		}

		for(int i = 0 ; i < array_length ; i++) {
			file_path = strdup(path_arryay[i]);
			send_media_message_to_buddy(chat_scroller, file_path, tgl_message_media_document);
			free(file_path);
			//break;
		}
	}
}

void on_contact_app_control_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED) {

		Evas_Object* chat_scroller = user_data;
		char *contact_name = NULL;
		char *phone_number = NULL;
		app_control_get_extra_data(reply, "http://tizen.org/appcontrol/data/name", &contact_name);
		app_control_get_extra_data(reply, "http://tizen.org/appcontrol/data/phone", &phone_number);

	}
}

static void _result_cb(attach_panel_h attach_panel, attach_panel_content_category_e content_category, app_control_h result, app_control_result_e result_code, void *user_data)
{
	switch(content_category) {
	case ATTACH_PANEL_CONTENT_CATEGORY_IMAGE:
	case ATTACH_PANEL_CONTENT_CATEGORY_CAMERA:
		on_gallery_app_control_reply_cb(NULL, result, result_code, user_data);
		break;
	case ATTACH_PANEL_CONTENT_CATEGORY_VIDEO:
	case ATTACH_PANEL_CONTENT_CATEGORY_VIDEO_RECORDER:
		on_video_app_control_reply_cb(NULL, result, result_code, user_data);
		break;
	case ATTACH_PANEL_CONTENT_CATEGORY_VOICE:
		on_voice_record_reply_cb(NULL, result, result_code, user_data);
		break;
	case ATTACH_PANEL_CONTENT_CATEGORY_MYFILES:
	case ATTACH_PANEL_CONTENT_CATEGORY_AUDIO:
		on_file_app_control_reply_cb(NULL, result, result_code, user_data);
		break;
	case ATTACH_PANEL_CONTENT_CATEGORY_CONTACT:
		on_contact_app_control_reply_cb(NULL, result, result_code, user_data);
		break;
	default:
		break;
	}

}

void on_media_type_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object* chat_scroller = data;
	appdata_s* ad = evas_object_data_get(chat_scroller, "app_data");
	const char *label = elm_object_item_text_get((Elm_Object_Item *) event_info);
	if (strcasecmp(label, POPUP_TEXT_TAKE_GALLERY) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}

		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);

		app_control_set_mime(app_control,"image/*");
		app_control_add_extra_data(app_control, APP_CONTROL_DATA_SELECTION_MODE, "single");
		app_control_send_launch_request(app_control, &on_gallery_app_control_reply_cb, data);
		app_control_destroy(app_control);
	} else if (strcasecmp(label, POPUP_TEXT_TAKE_PHOTO) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);
		app_control_set_mime(app_control,"image/jpg");
		//app_control_add_extra_data(app_control, "crop", "caller_id");
		app_control_send_launch_request(app_control, &on_gallery_app_control_reply_cb, data);
		app_control_destroy(app_control);
	} else if (strcasecmp(label, POPUP_TEXT_TAKE_VIDEO) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}

		app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);

		int remain_byte_size = 10485760;
		int request_KB_size = 0;

		if (remain_byte_size >= 1024) {
			request_KB_size = remain_byte_size / 1024;
		} else {
			// TODO: Need to check minimum size for recording
			request_KB_size = 1;
		}

		char recording_size[128] = {0, };
		snprintf(recording_size, sizeof(recording_size), "%d", request_KB_size);
		app_control_set_mime(app_control,"video/3gp");
		app_control_add_extra_data(app_control, "LIMIT", recording_size);
		app_control_add_extra_data(app_control, "RESOLUTION", "VGA");
		app_control_add_extra_data(app_control, "CALLER", "telegram");

		app_control_send_launch_request(app_control, &on_video_app_control_reply_cb, data);
		app_control_destroy(app_control);
	} else if (strcasecmp(label, POPUP_TEXT_TAKE_AUDIO) == 0) {

		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}

		app_control_set_operation(app_control, APP_CONTROL_OPERATION_CREATE_CONTENT);

		int size = 10485760;

        int remain_byte_size = (int)size;
        int request_KB_size = 0;

        if (remain_byte_size >= 1024) {
                request_KB_size = remain_byte_size / 1024;
        } else {
                // TODO: Need to check minimum size for recording
                request_KB_size = 1;
        }

		char recording_size[128] = {0, };
		snprintf(recording_size, sizeof(recording_size), "%d", request_KB_size);
		app_control_add_extra_data(app_control, "SIZE", recording_size);
		app_control_set_mime(app_control,"audio/*");
		app_control_send_launch_request(app_control, &on_voice_record_reply_cb, data);
		app_control_destroy(app_control);

	} else if (strcasecmp(label, POPUP_TEXT_TAKE_FILE) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load image picker");
			return;
		}

		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);

		app_control_set_mime(app_control,"*/*");
		app_control_add_extra_data(app_control, APP_CONTROL_DATA_SELECTION_MODE, "single");
		app_control_send_launch_request(app_control, &on_file_app_control_reply_cb, data);
		app_control_destroy(app_control);

	} else if (strcasecmp(label, POPUP_TEXT_TAKE_LOCATION) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load location picker");
			return;
		}
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);
		//app_control_set_app_id(app_control, "com.here.tizen.maps");
		app_control_set_uri(app_control, "geo");
		app_control_send_launch_request(app_control, &on_location_app_control_reply_cb, data);
		app_control_destroy(app_control);
	} else if (strcasecmp(label, POPUP_TEXT_TAKE_CONTACT) == 0) {
		app_control_h app_control;
		int ret = app_control_create(&app_control);
		if(ret != APP_CONTROL_ERROR_NONE) {
			show_toast(ad, "Error: Can not load location picker");
			return;
		}
		app_control_set_operation(app_control, APP_CONTROL_OPERATION_PICK);
		app_control_set_mime(app_control,"application/vnd.tizen.contact");
		app_control_add_extra_data(app_control, APP_CONTROL_DATA_SELECTION_MODE, "single");
		app_control_send_launch_request(app_control, &on_contact_app_control_reply_cb, data);
		app_control_destroy(app_control);
	}

	evas_object_del(obj);
}


void popup_move_dropdown(Evas_Object *ctxpopup, Evas_Object *btn)
{
	Evas_Coord x, y, w , h;
	evas_object_geometry_get(btn, &x, &y, &w, &h);
	evas_object_move(ctxpopup, x + (w / 2), y + h - 50);
}

void on_media_attach_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(obj);
}

static void on_media_attach_clicked(void *data, Evas_Object *obj, const char *emission, const char *source)
{
	Evas_Object* chat_scroller = data;
	appdata_s *ad = evas_object_data_get(chat_scroller, "app_data");
	attach_panel_h attach_panel = NULL;
	int ret;
	bool visible = false;

	attach_panel = evas_object_data_get(ad->conform, "attach_panel");
	if (attach_panel) {
			if (attach_panel_get_visibility(attach_panel, &visible) != ATTACH_PANEL_ERROR_NONE) {
				return;
			}
			if (!visible) {
				attach_panel_show(attach_panel);
			}
			return;
		}

	ret = attach_panel_create(ad->conform, &attach_panel);

	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_IMAGE, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_CAMERA, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_VOICE, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_VIDEO, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_AUDIO, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_CONTACT, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_VIDEO_RECORDER, NULL);
	attach_panel_set_result_cb(attach_panel, _result_cb, chat_scroller);

	attach_panel_show(attach_panel);
	evas_object_data_set(ad->conform, "attach_panel", attach_panel);

}

#if 0
static void on_text_message_send_pressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(SEND_UNPRESSED_ICON), NULL);
}

static void on_text_message_send_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(SEND_PRESSED_ICON), NULL);
}
#endif

void on_message_back_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad)
		return;

	app_nf_back_cb(data, obj, event_info);
}

void on_user_info_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;

	peer_with_pic_s  *sel_item = ad->peer_in_cahtting_data;
	tg_peer_info_s *user_data = sel_item->use_data;

	if (!sel_item || !user_data) {
		show_toast(ad, "Can not display user info");
		return;
	}

	if (user_data->peer_type == TGL_PEER_USER) {
		launch_user_info_screen(ad, user_data->peer_id);
	} else if (user_data->peer_type == TGL_PEER_CHAT) {
		launch_chat_info_screen(ad, user_data->peer_id);
	} else {

	}
}

void refresh_messaging_view(appdata_s *ad)
{
	if (!ad)
		return;

	Evas_Object *scroller = evas_object_data_get(ad->nf, "chat_list");

		if (scroller) {
			Evas_Object *box_layout = NULL;
			Evas_Object *box = NULL;
			Eina_List *list = NULL;
			Eina_List *box_list = NULL;
			Evas_Object *last_item = NULL;

			box_layout = elm_object_content_get(scroller);
			if (!box_layout) {
				LOGE("Fail to get the box into scroller");
				return;
			}
			list = elm_box_children_get(box_layout);
			if (!list) {
				LOGE("Fail to get the list into box");
				return;
			}

			box = eina_list_nth(list, 0);
			if (!box) {
				LOGE("Fail to get the box into box layout");
				return;
			}

			box_list = elm_box_children_get(box);
			if (!box_list) {
				LOGE("Fail to get the box_list into box");
				return;
			}

			last_item = eina_list_nth(box_list, eina_list_count(box_list)-1);
			if (!last_item) {
				LOGE("Fail to get the last item into box");
				return;
			}

			int x, y;
			evas_object_geometry_get(last_item, &x, &y, NULL, NULL);

			elm_scroller_region_show(scroller, x, y, -1, -1);

			eina_list_free(box_list);
			eina_list_free(list);
		}
}

static void on_expand_button_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *expand_pic = data;
	if (!expand_pic)
		return;

	appdata_s *ad = evas_object_data_get(expand_pic, "app_data");
	Evas_Object *parent_layout = evas_object_data_get(expand_pic, "parent_layout");

	Eina_Bool is_expanded = (Eina_Bool)evas_object_data_get(expand_pic, "is_expanded");

	if (!is_expanded) {

		elm_image_file_set(expand_pic, ui_utils_get_resource(TG_EXPAND_CLOSE), NULL);

		Evas_Object *grp_names_bg = elm_bg_add(ad->nf);
		evas_object_size_hint_align_set(grp_names_bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(grp_names_bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_color_set(grp_names_bg, 45, 165, 224, 202);
	    elm_image_resizable_set(grp_names_bg, EINA_TRUE, EINA_TRUE);
	    elm_image_fill_outside_set(grp_names_bg, EINA_TRUE);
	    evas_object_show(grp_names_bg);
	    elm_object_part_content_set(parent_layout, "swallow.group_detail_box,bg", grp_names_bg);

	    Evas_Object* grp_names_lbl = elm_entry_add(ad->nf);
		elm_entry_cursor_end_set(grp_names_lbl);
		evas_object_size_hint_weight_set(grp_names_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(grp_names_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		elm_entry_single_line_set(grp_names_lbl,  EINA_FALSE);
		elm_entry_scrollable_set (grp_names_lbl, EINA_TRUE);
		elm_entry_cnp_mode_set(grp_names_lbl, ELM_CNP_MODE_NO_IMAGE);
		elm_entry_context_menu_disabled_set(grp_names_lbl, EINA_TRUE);
		elm_object_focus_set(grp_names_lbl, EINA_FALSE);
	    elm_entry_editable_set(grp_names_lbl, EINA_FALSE);

		evas_object_show(grp_names_lbl);

		char *names_of_buddies = evas_object_data_get(ad->nf, "names_of_buddies");
		if (names_of_buddies) {
			int len = strlen(names_of_buddies);
			char *names_str = (char*)malloc(len + 256);
			sprintf(names_str, "<font=Tizen:style=Bold color=#FAFAFA align=center><font_size=40>%s</font_size></font>",names_of_buddies);
			elm_object_text_set(grp_names_lbl, names_str);
			free(names_str);
		}

		elm_object_part_content_set(parent_layout, "swallow.group_detail_box", grp_names_lbl);

	} else {

		elm_image_file_set(expand_pic, ui_utils_get_resource(TG_EXPAND_OPEN), NULL);

		Evas_Object *grp_names_lbl = elm_object_part_content_get(parent_layout, "swallow.group_detail_box");
		if (grp_names_lbl) {
			evas_object_del(grp_names_lbl);
			grp_names_lbl = NULL;
		}

		Evas_Object *grp_names_bg = elm_object_part_content_get(parent_layout, "swallow.group_detail_box,bg");
		if (grp_names_bg) {
			evas_object_del(grp_names_bg);
			grp_names_bg = NULL;
		}
	}
	is_expanded = !is_expanded;
	evas_object_data_set(expand_pic, "is_expanded", (void *)is_expanded);
}

static Eina_Bool _pop_cb(void *data, Elm_Object_Item *it)
{
	appdata_s *ad = data;
	attach_panel_h attach_panel = NULL;
	if (!ad) {
		LOGE("Failed to get the ad");
		return EINA_FALSE;
	}
	attach_panel = evas_object_data_get(ad->conform, "attach_panel");
	if (attach_panel) {
		attach_panel_hide(attach_panel);
	}

	return EINA_TRUE;
}

static void _edge_cb(void *data, Evas_Object *scroller, void *event_info)
{
	Evas_Object *layout = data;
	int is_end_edge = 0;
	is_end_edge = (int)evas_object_data_get(layout, "is_end_edge");

	if (!is_end_edge) {
		elm_object_signal_emit(layout, "hide", "bubblemessage");
		evas_object_data_set(layout, "is_end_edge", (void *) 1);
	}
}

static void _scroll_cb(void *data, Evas_Object *scroller, void *event_info)
{
	Evas_Object *layout = data;
	evas_object_data_set(layout, "is_end_edge", (void *) 0);
}

void launch_messaging_view_cb(appdata_s* ad, int user_id)
{
	if (!ad)
		return;

	if (ad->msg_popup) {
		evas_object_del(ad->msg_popup);
		ad->msg_popup = NULL;
	}

	delete_floating_button(ad);

	ad->current_app_state = TG_CHAT_MESSAGING_VIEW_STATE;
	ad->is_last_msg_changed = EINA_FALSE;
	send_request_for_server_connection_status(ad, ad->service_client);
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object *layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "chat_messaging_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);

	peer_with_pic_s *sel_item =  eina_list_nth(ad->peer_list, user_id);
	tg_peer_info_s* user = sel_item->use_data;

	/*************************** START: message list ************************************/

	Evas_Object* msg_box_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(msg_box_layout, edj_path, "custom_gen_list");
	evas_object_size_hint_weight_set(msg_box_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(msg_box_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(msg_box_layout);

	Evas_Object *list_bg = elm_image_add(msg_box_layout);
	evas_object_size_hint_align_set(list_bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(list_bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	if (ad->chat_background) {
		elm_image_file_set(list_bg, ad->chat_background, NULL);
	} else {
		//elm_image_file_set(list_bg, ui_utils_get_resource(TG_CHAT_DEFAULT_BG), NULL);
	}
    elm_image_resizable_set(list_bg, EINA_TRUE, EINA_TRUE);
    elm_image_fill_outside_set(list_bg, EINA_TRUE);
    evas_object_show(list_bg);

    elm_object_part_content_set(msg_box_layout, "swallow.gen_list.bg", list_bg);

	Evas_Object *chat_scroller = elm_scroller_add(ad->nf);
	evas_object_size_hint_weight_set(chat_scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(chat_scroller, EVAS_HINT_FILL, 0.0);
	elm_scroller_policy_set(chat_scroller, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(chat_scroller);
	evas_object_smart_callback_add(chat_scroller, "scroll", _scroll_cb, layout);
	evas_object_smart_callback_add(chat_scroller, "edge,bottom", _edge_cb, layout);
	evas_object_data_set(layout, "is_end_edge", (void *) 1);

	Evas_Object *align_box = elm_box_add(chat_scroller);
	if (!align_box) {
		LOGE("fail to add the box");
		return;
	}

	elm_box_horizontal_set(align_box, EINA_FALSE);
	elm_box_align_set(align_box, 0.5, 0.0);
	evas_object_size_hint_weight_set(align_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(align_box, EVAS_HINT_FILL, 0.0);
	elm_object_content_set(chat_scroller, align_box);
	evas_object_show(align_box);

	Evas_Object *chat_box = elm_box_add(chat_scroller);
	if (!chat_box) {
		LOGE("fail to add the box");
		return;
	}
	elm_box_horizontal_set(chat_box, EINA_FALSE);
	elm_box_align_set(chat_box, 0.5, 0.0);
	evas_object_size_hint_weight_set(chat_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(chat_box, EVAS_HINT_FILL, 0.0);
	evas_object_show(chat_box);
	elm_box_pack_end(align_box, chat_box);
	evas_object_event_callback_add(chat_box, EVAS_CALLBACK_RESIZE, __resize_cb, ad);

	elm_object_part_content_set(msg_box_layout, "swallow.gen_list", chat_scroller);
	elm_object_part_content_set(layout, "swallow.chat_box", msg_box_layout);

	/********************** START: entry layout*******************************/
	Evas_Object* entry_box_layout = elm_layout_add(ad->win);
	if (!entry_box_layout) {
		LOGE("Fail to add the entry box layout");
	}

	elm_layout_file_set(entry_box_layout, edj_path, "chat_entry_box");
	evas_object_size_hint_align_set(entry_box_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(entry_box_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(entry_box_layout);

	Evas_Object *entry_layout = elm_layout_add(entry_box_layout);
	if (!entry_layout) {
		LOGE("Fail to add the entry_layout");
	}
	elm_layout_theme_set(entry_layout, "layout", "editfield", "singleline");

	Evas_Object* text_entry = elm_entry_add(entry_layout);
	if (!text_entry) {
		LOGE("Fail to add the text_entry");
	}

	elm_object_part_text_set(text_entry, "elm.guide", "Text message");
	elm_entry_line_wrap_set(text_entry, EINA_TRUE);
	elm_entry_scrollable_set(text_entry, EINA_TRUE);
	evas_object_size_hint_align_set(text_entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(text_entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(text_entry);
	evas_object_data_set(entry_box_layout, "is_attach_show", (void *) 1);

	elm_object_part_content_set(entry_layout, "elm.swallow.content", text_entry);
	evas_object_smart_callback_add(text_entry, "changed", on_message_text_entry_changed, entry_box_layout);
	evas_object_smart_callback_add(text_entry, "preedit,changed", on_message_text_entry_changed, entry_box_layout);
	evas_object_smart_callback_add(text_entry, "clicked", on_message_text_entry_clicked, NULL);
	elm_object_part_content_set(entry_box_layout, "swallow.text_entry", entry_layout);

	/* button clicked event */
	elm_object_signal_callback_add(entry_box_layout, "smile", "clicked", on_message_smiley_clicked, text_entry);
	elm_object_signal_callback_add(entry_box_layout, "attach", "clicked", on_media_attach_clicked, chat_scroller);
	elm_object_signal_callback_add(entry_box_layout, "send", "clicked", on_text_message_send_clicked, chat_scroller);
	elm_object_part_content_set(layout, "swallow.entry", entry_box_layout);

	/********************** END: entry layout*******************************/

	/************************* START: message bubble ************************/

	Evas_Object* bubble_layout = elm_layout_add(ad->win);
	if (!bubble_layout) {
		LOGE("Fail to add the bubble_layout");
	}

	elm_layout_file_set(bubble_layout, edj_path, "bubble_layout");
	evas_object_size_hint_align_set(bubble_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(bubble_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(bubble_layout);
	elm_object_signal_callback_add(bubble_layout, "cancel", "clicked", on_message_cancel_clicked, layout);
	elm_object_part_content_set(layout, "swallow.messagebubble", bubble_layout);
	evas_object_data_set(ad->nf, "main_layout", layout);

	/********************** END: entry message bubble*******************************/

	evas_object_data_set(ad->nf, "chat_list", (void*)chat_scroller);
	evas_object_data_set(chat_scroller, "app_data", ad);
	evas_object_data_set(chat_scroller, "user_id", (void*)user_id);
	evas_object_data_set(chat_scroller, "text_entry", (void*)text_entry);

	/* Set the name in title area */

	char temp_name[512] = {'\0'};

	if ((user->peer_type == TGL_PEER_USER) && get_buddy_unknown_status(user->peer_id)) {
			snprintf(temp_name, 512, "%s", get_buddy_phone_num_from_id(sel_item->use_data->peer_id));
	} else {
		char* user_name = replace(sel_item->use_data->print_name, '_', " ");
		snprintf(temp_name, 512, "%s", user_name);
		free(user_name);
	}

	Elm_Object_Item *nf_it = elm_naviframe_item_push(ad->nf, temp_name, NULL, NULL, layout, NULL);
	evas_object_data_set(ad->nf, "navi_item", nf_it);

	on_user_presence_state_changed(ad, sel_item->use_data->peer_id);

	Evas_Object *back_btn = create_button(ad->nf, "naviframe/back_btn/default", NULL);
	evas_object_smart_callback_add(back_btn, "clicked", on_message_back_button_clicked, ad);
	elm_object_item_part_content_set(nf_it, "elm.swallow.prev_btn", back_btn);
	elm_naviframe_item_pop_cb_set(nf_it, _pop_cb, ad);

	/******************** expand ************************/
	if (user->peer_type == TGL_PEER_CHAT) {
		Evas_Object *expand_pic = NULL;
		expand_pic = elm_image_add(layout);
		evas_object_size_hint_weight_set(expand_pic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(expand_pic, EVAS_HINT_FILL, EVAS_HINT_FILL);
		elm_object_focus_set(expand_pic, EINA_FALSE);
		elm_image_file_set(expand_pic, ui_utils_get_resource(TG_EXPAND_OPEN), NULL);
		evas_object_show(expand_pic);
		evas_object_data_set(expand_pic, "app_data", ad);
		evas_object_data_set(expand_pic, "parent_layout", layout);

		Eina_Bool is_expanded = EINA_FALSE;
		evas_object_data_set(expand_pic, "is_expanded", is_expanded);
		Evas_Object* expand_btn = elm_button_add(ad->layout);
		elm_object_style_set(expand_btn, "transparent");
		evas_object_smart_callback_add(expand_btn, "clicked", on_expand_button_clicked, expand_pic);
		elm_object_content_set(expand_btn, expand_pic);
		evas_object_show(expand_btn);
		elm_object_item_part_content_set(nf_it, "title_right_btn", expand_btn);

	}
	/******************** expand ************************/

	Eina_Bool ret = load_chat_history(chat_scroller);

	int buddy_id = sel_item->use_data->peer_id;
	char* tablename = get_table_name_from_number(buddy_id);

	Eina_Bool res = set_all_rows_read(tablename);
	if (!res) {
		//failed.
	}
	free(tablename);

	if (!ret) {
		LOGD("There is no message in chat room");
		// show no messages
		elm_object_part_text_set(layout, "no_msg_text", i18n_get_text("IDS_TGRAM_BODY_NO_MESSAGES_HERE_YET_ING"));
		elm_object_signal_emit(layout, "show", "message");
		evas_object_data_set(ad->nf, "chat_list_no_msg_text", layout);
	}

	send_request_for_marked_as_read(ad, ad->service_client, sel_item->use_data->peer_id, sel_item->use_data->peer_type);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_MORE, on_messaging_menu_button_clicked, ad);
}

