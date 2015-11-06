/*
 * tg_user_main_view.c
 *
 *  Created on: Aug 20, 2015
 *      Author: sandeep
 */

#include "tg_user_main_view.h"
#include "tg_start_messaging_view.h"
#include "tg_messaging_view.h"
#include "contact_selection_view.h"
#include "tg_search_peer_view.h"
#include "tg_settings_view.h"
#include "tg_db_manager.h"
#include "server_requests.h"
#include "tg_db_wrapper.h"
#include "tg_main_item_deletion_view.h"
#include "tg_search_message_view.h"


static Evas_Object *create_image_object_from_file(const char *icon_name, Evas_Object *parent)
{
	Evas_Object *icon = elm_image_add(parent);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(icon, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_image_file_set(icon, icon_name, NULL);
	evas_object_show(icon);
	return icon;
}

static char* on_menu_item_name_get_cb(void *data, Evas_Object *obj, const char *part)
{
		if (!strcmp(part,"elm.text"))
		{
			int id = (int) data;

			char temp_text[256];
			sprintf(temp_text, "<font=Tizen:style=Normal color=#000000 align=left><font_size=30>%s</font_size></font>", main_view_menu_items[id][0]);

			return strdup(temp_text);
		}
		else return NULL;
}

static Evas_Object* on_menu_item_image_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int)data;
	if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *img = elm_image_add(obj);
		elm_image_file_set(img, ui_utils_get_resource(main_view_menu_items[id][1]), NULL);
		evas_object_size_hint_min_set(img, ELM_SCALE_SIZE(36), ELM_SCALE_SIZE(36));
		return img;
	}
	return NULL;
}

static void launch_contact_picker(appdata_s* ad)
{
	app_control_h app_control;
	int ret = app_control_create(&app_control);

	app_control_set_operation(app_control, APP_CONTROL_OPERATION_COMPOSE);
	//app_control_set_app_id(app_control, "tizen.messages");
	//app_control_add_extra_data(app_control, APP_CONTROL_DATA_TO, recipient);
	app_control_set_mime(app_control,"text/html");
	char *text = "Invite you to telegram! https://telegram.org/dl";
	app_control_add_extra_data(app_control, APP_CONTROL_DATA_TEXT, text);
	if (app_control_send_launch_request(app_control, NULL, NULL) == APP_CONTROL_ERROR_NONE) {
		// sms view launched
	}
	app_control_destroy(app_control);
}

static void on_menu_item_selected(void *data, Evas_Object *obj, void *event_info)
{
	//int index __attribute__((unused)) = (int)data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	int id = (int) data;
	if (id == 0) { // new group
		launch_contact_selction_view(ad);
	} else if (id == 1) { // new sec chat

	} else if (id == 2) { // contacts
		launch_start_messaging_view(ad);
	} else if (id == 3) { // invite friends
		launch_contact_picker(ad);
	} else if (id == 4) { // settings
		launch_settings_screen(ad);
	} else {

	}
	elm_panel_hidden_set(ad->panel, EINA_TRUE);
}

static void on_menu_list_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
}

Evas_Object* create_side_panel_list(appdata_s* ad, Evas_Object *parent)
{

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "user_main_screen_side_panel");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);


	Evas_Object* user_info_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(user_info_layout, edj_path, "menu_user_layout");
	evas_object_size_hint_weight_set(user_info_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(user_info_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(user_info_layout);
	elm_object_part_content_set(layout, "main_box", user_info_layout);

	Evas_Object *profile_pic = NULL;
	/*********** user info ********************/
	if (ad->current_user_data->photo_path && strlen(ad->current_user_data->photo_path) > 0 && strstr(ad->current_user_data->photo_path, "_null_") == NULL) {
		profile_pic = create_image_object_from_file(ad->current_user_data->photo_path, ad->nf);
	} else  {
		profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC), ad->nf);
	}

	Evas_Object *user_pic_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(user_pic_layout, edj_path, "main_circle_layout");
	evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(user_pic_layout);
	elm_object_part_content_set(user_pic_layout, "content", profile_pic);

	elm_object_part_content_set(user_info_layout, "user_photo_box", user_pic_layout);

	evas_object_data_set(ad->nf, "main_user_profile_pic", profile_pic);


	char* full_name = NULL;
	/*
	if (ad->current_user_data.first_name && ad->current_user_data.last_name) {
		full_name =(char*)malloc(strlen(ad->current_user_data.first_name) + strlen("") + strlen(ad->current_user_data.last_name) + 1);
		strcpy(full_name, ad->current_user_data.first_name);
		strcat(full_name, "");
		strcat(full_name, ad->current_user_data.last_name);
	} else if (ad->current_user_data.first_name) {
		full_name =(char*)malloc(strlen(ad->current_user_data.first_name) + strlen("") + strlen(ad->current_user_data.last_name) + 1);
		strcpy(full_name, ad->current_user_data.first_name);
		strcat(full_name, "");
		strcat(full_name, ad->current_user_data.last_name);
	}*/

	if (ad->current_user_data->print_name) {
		full_name = replace(ad->current_user_data->print_name, '_', " ");
	} else {
		full_name = strdup("");
	}


	char* phone_no = NULL;
	if (ad->current_user_data->phone) {
		phone_no = (char*)malloc(strlen(ad->current_user_data->phone) + strlen("+") + 1);
		strcpy(phone_no, "+");
		strcat(phone_no, ad->current_user_data->phone);
	} else {
		phone_no = strdup("");
	}

	char temp_full_name[256];
	sprintf(temp_full_name, "<font=Tizen:style=Bold color=#000000 align=center><font_size=30>%s</font_size></font>", full_name);


	char temp_phone_no[256];
	sprintf(temp_phone_no, "<font=Tizen:style=Bold color=#000000 align=center><font_size=30>%s</font_size></font>", phone_no);


	Evas_Object* user_name = elm_label_add(ad->nf);
	elm_object_text_set(user_name, temp_full_name);
	elm_label_ellipsis_set(user_name, EINA_TRUE);
	evas_object_show(user_name);
	elm_object_part_content_set(user_info_layout, "user_name_box", user_name);

	Evas_Object* phone_no_lbl = elm_label_add(ad->nf);
	elm_object_text_set(phone_no_lbl, temp_phone_no);
	elm_label_ellipsis_set(phone_no_lbl, EINA_TRUE);
	evas_object_show(phone_no_lbl);
	elm_object_part_content_set(user_info_layout, "phone_number_box", phone_no_lbl);


	free(full_name);
	free(phone_no);


	/*********** user info ********************/


	Evas_Object* menu_gen_list = elm_genlist_add(parent);
	elm_list_mode_set(menu_gen_list, ELM_LIST_COMPRESS);
	elm_genlist_mode_set(menu_gen_list, ELM_LIST_COMPRESS);
	evas_object_size_hint_weight_set(menu_gen_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(menu_gen_list, EVAS_HINT_FILL, EVAS_HINT_FILL);

	evas_object_data_set(menu_gen_list, "app_data", ad);

	static Elm_Genlist_Item_Class itc;
	itc.item_style = "type1";
	itc.func.text_get = on_menu_item_name_get_cb;
	itc.func.content_get = on_menu_item_image_get_cb;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	for (int i = 0; i < NUMBER_OF_MENU_ITEMS; i++) {
		elm_genlist_item_append(menu_gen_list, &itc, (void *)i, NULL, ELM_GENLIST_ITEM_NONE, on_menu_item_selected, (void*)i);
	}
	evas_object_show(menu_gen_list);
	elm_object_part_content_set(layout, "options_box", menu_gen_list);
	evas_object_smart_callback_add(menu_gen_list, "selected", on_menu_list_clicked_cb, ad);
	return scroller;

}


void on_side_panel_scroll_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Panel_Scroll_Info *ev = event_info;
	Evas_Object *bg = data;
	int col = 127 * ev->rel_x;
	evas_object_color_set(bg, 0, 0, 0, col);
}

void on_side_list_back_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *panel = data;
	elm_panel_hidden_set(panel, EINA_TRUE);
}

Evas_Object* create_side_panel(Evas_Object *parent)
{
	Evas_Object *panel, *bg;

	panel = elm_panel_add(parent);
	elm_panel_scrollable_set(panel, EINA_TRUE);
	elm_panel_hidden_set(panel, EINA_TRUE);
	elm_panel_orient_set(panel, ELM_PANEL_ORIENT_LEFT);

	bg = evas_object_rectangle_add(evas_object_evas_get(parent));
	evas_object_color_set(bg, 0, 0, 0, 0);
	elm_object_part_content_set(parent, "elm.swallow.bg", bg);
	evas_object_show(bg);

	evas_object_smart_callback_add(panel, "scroll", on_side_panel_scroll_clicked, bg);
	evas_object_show(panel);

	return panel;
}

void on_side_panel_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Elm_Object_Item *it = (Elm_Object_Item *) elm_list_selected_item_get(obj);
	if(it == NULL) return;
	elm_object_item_part_text_set(elm_naviframe_top_item_get(ad->nf), NULL, elm_object_item_part_text_get(it, "default"));
	elm_list_item_selected_set(it, EINA_FALSE);
}


void create_side_main_view(appdata_s *ad)
{
	ad->panel = create_side_panel(ad->layout);
	elm_object_part_content_set(ad->layout, "elm.swallow.left", ad->panel);
	Evas_Object *panel_list = create_side_panel_list(ad, ad->panel);
	evas_object_size_hint_weight_set(panel_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(panel_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(panel_list, "selected", on_side_panel_clicked, ad);
	eext_object_event_callback_add(panel_list, EEXT_CALLBACK_BACK, on_side_list_back_clicked, ad->panel);
	elm_object_content_set(ad->panel, panel_list);
	evas_object_data_set(ad->panel, "panel_list", panel_list);
	return;
}

void on_side_panel_requested(void *data, Evas_Object * obj, void *event_info)
{
	appdata_s *ad = data;

	if (!ad)
		return;

	if (ad->current_app_state == TG_USER_MAIN_VIEW_STATE) {

		if (ad->panel == NULL) {
			create_side_main_view(ad);
		}
		if (!elm_object_disabled_get(ad->panel))
			elm_panel_toggle(ad->panel);
	}

	return;
}

/******************** long press menu *******************************************/


char* on_longpress_group_menu_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	if (id == 0) {
		return strdup(i18n_get_text("IDS_TGRAM_OPT_CLEAR_HISTORY_ABB3"));
	} else {
		return strdup(i18n_get_text("IDS_TGRAM_OPT_LEAVE_CHAT"));
	}
}

char* on_longpress_single_menu_text_get_cb(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	if (id == 0) {
		return strdup(i18n_get_text("IDS_TGRAM_OPT_CLEAR_HISTORY_ABB3"));
	} else {
		return strdup(i18n_get_text("IDS_TGRAM_OPT_DELETE"));
	}
}

/******************** long press menu *******************************************/
void on_chat_long_press_option_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *popup = data;
	appdata_s *ad = (appdata_s*)evas_object_data_get(popup, "app_data");
	tg_main_list_item_s  *sel_item = (tg_main_list_item_s*)evas_object_data_get(popup, "selected_chat_item");
	int item_id = (int)evas_object_data_get(popup, "selected_chat_item_index");

	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);
	int id = (int)elm_object_item_data_get(it);

	if (id == 0) {
		if (sel_item->peer_type == TGL_PEER_USER || sel_item->peer_type == TGL_PEER_CHAT) {
			char* tablename = get_table_name_from_number(sel_item->peer_id);
			delete_all_records(tablename);
			free(tablename);

			//change item in list
			sel_item->last_message = strdup("");
			sel_item->last_msg_id = -1;
			sel_item->last_msg_type = -1;
			sel_item->is_out_msg = -1;
			sel_item->last_msg_status = -1;
			sel_item->number_of_unread_msgs = 0;

			if (sel_item->status_lbl) {
				char *org_msg = "";
				elm_object_text_set(sel_item->status_lbl, org_msg);
			}
			if (sel_item->date_lbl) {
				Eina_Bool is_today = compare_date_with_current_date(sel_item->last_seen_time);

				if (is_today) {
					elm_object_text_set(sel_item->date_lbl, "<font=Tizen:style=Normal color=#000000 align=center><font_size=25>Today</font_size></font>");
				} else {
					char *format = NULL;
					time_t t = sel_item->last_seen_time;
					format = "%d/%b/%Y";
					struct tm lt;
					char res[256];
					(void) localtime_r(&t, &lt);

					if (strftime(res, sizeof(res), format, &lt) == 0) {
						(void) fprintf(stderr,  "strftime(3): cannot format supplied "
								"date/time into buffer of size %u "
								"using: '%s'\n",
								sizeof(res), format);
					}

					char time_str[256]={0,};
					snprintf(time_str, sizeof(time_str), "<font=Tizen:style=Normal color=#000000 align=center><font_size=25>%s</font_size></font>", res);

					elm_object_text_set(sel_item->date_lbl,time_str);
				}
			}
#if 0
			if (sel_item->msg_status_lbl) {
				Evas_Object* temp_lbl = elm_object_part_content_get(sel_item->msg_status_lbl, "swallow.status");
				if (temp_lbl) {
					evas_object_del(temp_lbl);
				}
				Evas_Object* num_lbl = elm_label_add(ad->nf);
				elm_object_style_set(num_lbl, "transparent");
				elm_object_text_set(num_lbl, "");
				evas_object_size_hint_weight_set(num_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(num_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_show(num_lbl);
				elm_object_part_content_set(sel_item->msg_status_lbl, "swallow.status", num_lbl);
			}
#endif
			Evas_Object *buddy_list = evas_object_data_get(ad->nf, "buddy_list");
			if (buddy_list) {
				elm_genlist_realized_items_update(buddy_list);
			}

		} else {

		}

	} else if (id == 1) {
		if (sel_item->peer_type == TGL_PEER_USER) {
			char* tablename = get_table_name_from_number(sel_item->peer_id);
			delete_all_records(tablename);
			free(tablename);

			// delete from main list

			if (sel_item->peer_print_name) {
				free(sel_item->peer_print_name);
				sel_item->peer_print_name = NULL;
			}
			if (sel_item->last_message) {
				free(sel_item->last_message);
				sel_item->last_message = NULL;
			}
			if (sel_item->profile_pic_path) {
				free(sel_item->profile_pic_path);
				sel_item->profile_pic_path = NULL;
			}
			sel_item->date_lbl = NULL;
			sel_item->msg_status_lbl = NULL;
			sel_item->main_item_layout = NULL;
			sel_item->profile_pic = NULL;
			sel_item->profile_pic_path = NULL;
			sel_item->status_lbl = NULL;
			sel_item->user_name_lbl = NULL;

			//ad->main_list
			ad->main_list = eina_list_remove(ad->main_list, sel_item);
			refresh_main_list_view(ad, EINA_FALSE);

		} else if (sel_item->peer_type == TGL_PEER_CHAT) {

			//send group chat delete request
			show_loading_popup(ad);
			send_delete_group_chat_request(ad, ad->service_client, sel_item->peer_id);

		} else {

		}
	} else {

	}
	evas_object_del(popup);
}


static void on_buddy_list_longpress(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	int item_id = (int)elm_object_item_data_get(it);
	tg_main_list_item_s  *sel_item = eina_list_nth(ad->main_list, item_id);

	if (sel_item) {
		static Elm_Genlist_Item_Class itc;
		Evas_Object *popup;
		Evas_Object *box;
		Evas_Object *genlist;
		int i;
		Evas_Object *win = ad->win;

		popup = elm_popup_add(win);
		elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
		eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
		evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

		evas_object_data_set(popup, "app_data", ad);
		evas_object_data_set(popup, "selected_chat_item", (void*)sel_item);
		evas_object_data_set(popup, "selected_chat_item_index", (void*)item_id);
		/* box */
		box = elm_box_add(popup);
		evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

		/* genlist */
		genlist = elm_genlist_add(box);
		evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);

		itc.item_style = "default";


		if (sel_item->peer_type == TGL_PEER_USER) {
			itc.func.text_get = on_longpress_single_menu_text_get_cb;
		} else if (sel_item->peer_type == TGL_PEER_CHAT) {
			itc.func.text_get = on_longpress_group_menu_text_get_cb;
		} else {

		}

		itc.func.content_get = NULL;
		itc.func.state_get = NULL;
		itc.func.del = NULL;

		for (i = 0; i < 2; i++) {
			elm_genlist_item_append(genlist, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, on_chat_long_press_option_selected_cb, popup);
		}
		evas_object_show(genlist);
		elm_box_pack_end(box, genlist);
		evas_object_size_hint_min_set(box, -1, 230);
		elm_object_content_set(popup, box);
		evas_object_show(popup);
	}
}

void on_main_chat_item_selected(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it = event_info;
	elm_genlist_item_selected_set(it, EINA_FALSE);

	//int item_id = (int) data;
	int item_id = (int)elm_object_item_data_get(it);

	appdata_s* ad = evas_object_data_get(obj, "app_data");

	tg_main_list_item_s* sel_item = eina_list_nth(ad->main_list, item_id);

	ad->buddy_in_cahtting_data = NULL;
	ad->peer_in_cahtting_data = NULL;
	int buddy_id = -1;
	if (sel_item) {

		if (sel_item->peer_type == TGL_PEER_CHAT) {

			tg_chat_info_s* chat_info = get_chat_info(sel_item->peer_id);
			if (!chat_info) {
				// request chat info
				//show_toast(ad, "Loading chat info. Please wait.");
				show_loading_popup(ad);
				send_update_chat_request(ad, ad->service_client, sel_item->peer_id);
				return;
			}
		}

		if (sel_item->peer_type == TGL_PEER_USER) {
			for (int i = 0; i < eina_list_count(ad->buddy_list); i++) {
				user_data_with_pic_s *item = eina_list_nth(ad->buddy_list, i);
				user_data_s* user_data = item->use_data;

				if (user_data->user_id.id == sel_item->peer_id) {
					ad->buddy_in_cahtting_data = item;
					break;
				}
			}

			if (ad->buddy_in_cahtting_data == NULL) {
				for (int i = 0; i < eina_list_count(ad->unknown_buddy_list); i++) {
					user_data_with_pic_s *item = eina_list_nth(ad->unknown_buddy_list, i);
					user_data_s* user_data = item->use_data;

					if (user_data->user_id.id == sel_item->peer_id) {
						ad->buddy_in_cahtting_data = item;
						break;
					}
				}
			}
		}

		for (int i = 0; i < eina_list_count(ad->peer_list); i++) {
			peer_with_pic_s* pic_item = eina_list_nth(ad->peer_list, i);
			tg_peer_info_s* item = pic_item->use_data;

			if (item->peer_id == sel_item->peer_id) {
				ad->peer_in_cahtting_data = pic_item;
				buddy_id = i;
				break;
			}
		}
		ad->main_item_in_cahtting_data = sel_item;
#if 0
		if (ad->panel) {
			Evas_Object *panel_list = evas_object_data_get(ad->panel, "panel_list");
			if (panel_list) {
				evas_object_del(panel_list);
			}
			evas_object_del(ad->panel);
			ad->panel = NULL;
		}
#endif
		delete_floating_button(ad);
		launch_messaging_view_cb(ad, buddy_id);
	}
}

void on_buddy_icon_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	tg_main_list_item_s *item  = data;
	item->profile_pic = NULL;
}

void on_buddy_date_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	tg_main_list_item_s *item  = data;
	item->date_lbl = NULL;
}

void on_buddy_main_item_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	tg_main_list_item_s *item  = data;
	item->main_item_layout = NULL;
}
#if 0
void on_buddy_msg_status_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	tg_main_list_item_s *item  = data;
	item->msg_status_lbl = NULL;
}
#endif
void on_buddy_user_name_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	tg_main_list_item_s *item  = data;
	item->user_name_lbl = NULL;
}

void on_buddy_user_status_deleted(void *data, Evas *e, Evas_Object *icon, void *event_info)
{
	tg_main_list_item_s *item  = data;
	item->status_lbl = NULL;
}

Evas_Object* on_chat_item_load_requested(void *data, Evas_Object *obj, const char *part)
{
	int id = (int) data;
	appdata_s* ad = evas_object_data_get(obj, "app_data");
	if (ad->main_list == NULL || eina_list_count(ad->main_list) <= 0) {
		return NULL;
	}
	tg_main_list_item_s* item = eina_list_nth(ad->main_list, id);
	if (!item) {
		return NULL;
	}

	Eina_Bool is_empty_msg = EINA_FALSE;

	if (!strcmp(part, "elm.swallow.content")) {

		if (item->main_item_layout) {
			return item->main_item_layout;
		}

		char edj_path[PATH_MAX] = {0, };
		app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
		Evas_Object* layout = elm_layout_add(ad->nf);
		elm_layout_file_set(layout, edj_path, "main_list_custom_item");
		evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(layout);
		Evas_Object* item_layout = elm_layout_add(ad->nf);
		if (ad->target_direction == TELEGRAM_TARGET_DIRECTION_LANDSCAPE_INVERSE || ad->target_direction == TELEGRAM_TARGET_DIRECTION_LANDSCAPE) {
			if ((item->last_message == NULL) || (strlen(item->last_message) <= 0) || (strcmp(item->last_message, " ") == 0)) {
				elm_layout_file_set(item_layout, edj_path, "main_list_custom_no_msg_item_land");
				is_empty_msg = EINA_TRUE;
			} else {
				if (item->is_out_msg && !(item->last_msg_service)) {
					elm_layout_file_set(item_layout, edj_path, "main_list_custom_sent_item_land");
				} else {
					elm_layout_file_set(item_layout, edj_path, "main_list_custom_received_item_land");
				}
			}
		} else {
			if ((item->last_message == NULL) || (strlen(item->last_message) <= 0) || (strcmp(item->last_message, " ") == 0)) {
				elm_layout_file_set(item_layout, edj_path, "main_list_custom_no_msg_item");
				is_empty_msg = EINA_TRUE;
			} else {
				if (item->is_out_msg && !(item->last_msg_service)) {
					elm_layout_file_set(item_layout, edj_path, "main_list_custom_sent_item");
				} else {
					elm_layout_file_set(item_layout, edj_path, "main_list_custom_received_item");
				}
			}
		}
		evas_object_size_hint_weight_set(item_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(item_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(item_layout);
		elm_object_part_content_set(layout, "swallow.item", item_layout);

		/*************************** profile pic ***************************************/
		if (item->profile_pic == NULL) {
			Evas_Object *profile_pic = NULL;
			if (item->profile_pic_path && strcmp(item->profile_pic_path, "") != 0) {
				profile_pic = elm_image_add(obj);
				evas_object_size_hint_weight_set(profile_pic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(profile_pic, EVAS_HINT_FILL, EVAS_HINT_FILL);
				elm_object_focus_set(profile_pic, EINA_FALSE);

				Eina_Bool is_success = elm_image_file_set(profile_pic, item->profile_pic_path, NULL);

				if (!is_success) {
					if (item->peer_type == TGL_PEER_USER) {
						profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC), obj);
						// send download request again To-Do
					} else if (item->peer_type == TGL_PEER_CHAT) {
						profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_MULTI_PIC), obj);
						// send download request again To-Do
					} else {

					}
					evas_object_color_set(profile_pic, 45, 165, 224, 255);
				}
				evas_object_show(profile_pic);
			} else {

				if (item->peer_type == TGL_PEER_USER) {
					profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC), obj);
				} else if (item->peer_type == TGL_PEER_CHAT) {
					profile_pic = create_image_object_from_file(ui_utils_get_resource(DEFAULT_LIST_THUMB_MULTI_PIC), obj);
				} else {

				}
				evas_object_color_set(profile_pic, 45, 165, 224, 255);
			}

			item->profile_pic = profile_pic;
			evas_object_event_callback_add(item->profile_pic, EVAS_CALLBACK_DEL, on_buddy_icon_deleted, item);
		}

		Evas_Object* user_pic_layout = elm_layout_add(ad->nf);
		elm_layout_file_set(user_pic_layout, edj_path, "circle_layout");
		evas_object_size_hint_weight_set(user_pic_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(user_pic_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(user_pic_layout);
		elm_object_part_content_set(user_pic_layout, "content", item->profile_pic);

		elm_object_part_content_set(item_layout, "swallow.icon", user_pic_layout);

		/*************************** profile pic ***************************************/

		/*************************** user name ***************************************/

#if 0
		char* user_name = replace(item->peer_print_name, '_', " ");
#endif
		char* user_name = str_replace(item->buddy_display_name, "_null_", "");
		char buf[512] = {'\0'};
		snprintf(buf, 512, "<font=Tizen:style=Bold color=#000000 align=left><font_size=35>%s</font_size></font>", user_name);
		free(user_name);

		Evas_Object*  name_lbl = elm_label_add(ad->nf);
		elm_object_text_set(name_lbl, buf);
		evas_object_size_hint_weight_set(name_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(name_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(name_lbl);

		elm_object_part_content_set(item_layout, "swallow.title", name_lbl);

		item->user_name_lbl = name_lbl;
		evas_object_event_callback_add(item->user_name_lbl, EVAS_CALLBACK_DEL, on_buddy_user_name_deleted, item);

		/*************************** user name ***************************************/

		/*************************** last message ***************************************/

		char* org_msg = NULL;
		if (item->last_message) {
			org_msg = str_replace(item->last_message, "<br/>", " ");
		} else {
			org_msg = strdup("");
		}

		int len_org_str = strlen(org_msg);

		char res[30] = {'\0'};
		char status_buf[126] = {'\0'};
		if(len_org_str > 30) {
			strncpy(res, org_msg, 29);
			if(item->last_msg_service) {
				sprintf(status_buf,"<font=Tizen:style=Bold color=#158CB0 align=left><font_size=28>%s</font_size></font>", res);
			} else {
				sprintf(status_buf,"<font=Tizen:style=Bold color=#A4A4A4 align=left><font_size=28>%s</font_size></font>", res);
			}
		} else {
			if(item->last_msg_service) {
				sprintf(status_buf, "<font=Tizen:style=Bold color=#158CB0 align=left><font_size=28>%s</font_size></font>", org_msg);
			} else {
				sprintf(status_buf, "<font=Tizen:style=Bold color=#A4A4A4 align=left><font_size=28>%s</font_size></font>", org_msg);
			}
		}
		free(org_msg);

		Evas_Object*  status_lbl = elm_label_add(ad->nf);
		elm_object_text_set(status_lbl, status_buf);
		evas_object_size_hint_weight_set(status_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(status_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(status_lbl);

		item->status_lbl = status_lbl;
		evas_object_event_callback_add(item->status_lbl, EVAS_CALLBACK_DEL, on_buddy_user_status_deleted, item);

		elm_object_part_content_set(item_layout, "swallow.last_message", item->status_lbl);

		/*************************** last message ***************************************/

		/*************************** date ***************************************/
		Eina_Bool is_today = compare_date_with_current_date(item->last_seen_time);
		Evas_Object* time_lbl = elm_label_add(ad->nf);
		if (is_today) {
			//elm_object_text_set(time_lbl, "<font=Tizen:style=Normal color=#000000 align=left><font_size=27>Today</font_size></font>");
			// get time to display

			char *format = NULL;
			time_t t = item->last_seen_time;
			format = "%I:%M %p";
			struct tm lt;
			char res[28] = {'\0'};
			(void) localtime_r(&t, &lt);

			if (strftime(res, sizeof(res), format, &lt) == 0) {
				(void) fprintf(stderr,  "strftime(3): cannot format supplied "
						"date/time into buffer of size %u "
						"using: '%s'\n",
						sizeof(res), format);
			}

			char time_str[128]={0,};
			sprintf(time_str, "<font=Tizen:style=Normal color=#000000 align=right><font_size=27>%s</font_size></font>", res);

			elm_object_text_set(time_lbl,time_str);


		} else {
			char *format = NULL;
			time_t t = item->last_seen_time;
			format = "%b %d";
			struct tm lt;
			char res[28] = {'\0'};
			(void) localtime_r(&t, &lt);

			if (strftime(res, sizeof(res), format, &lt) == 0) {
				(void) fprintf(stderr,  "strftime(3): cannot format supplied "
						"date/time into buffer of size %u "
						"using: '%s'\n",
						sizeof(res), format);
			}

			char time_str[128]={0,};
			sprintf(time_str, "<font=Tizen:style=Normal color=#000000 align=right><font_size=27>%s</font_size></font>", res);

			elm_object_text_set(time_lbl,time_str);
		}

		evas_object_size_hint_weight_set(time_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(time_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_show(time_lbl);

		item->date_lbl = time_lbl;
		evas_object_event_callback_add(item->date_lbl, EVAS_CALLBACK_DEL, on_buddy_date_deleted, item);

		elm_object_part_content_set(item_layout, "swallow.date", time_lbl);

		/*************************** date ***************************************/

		/*************************** sent message status ***************************************/
		if (!is_empty_msg) {
			if (item->is_out_msg && !(item->last_msg_service)) {

				Evas_Object *status_obj;
				status_obj = elm_icon_add(obj);
				evas_object_size_hint_weight_set(status_obj, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(status_obj, EVAS_HINT_FILL, EVAS_HINT_FILL);

				if(item->last_msg_status == TG_MESSAGE_STATE_SENDING) {
					elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENDING_ICON), NULL);
				} else if(item->last_msg_status == TG_MESSAGE_STATE_SENT) {
					elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_SENT_ICON), NULL);
				} else if(item->last_msg_status == TG_MESSAGE_STATE_DELIVERED) {
					elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_DELIVERED_ICON), NULL);
				} else if(item->last_msg_status == TG_MESSAGE_STATE_RECEIVED) {

				} else if(item->last_msg_status == TG_MESSAGE_STATE_FAILED) {
					elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_FAILED_ICON), NULL);
				} else if(item->last_msg_status == TG_MESSAGE_STATE_READ) {
					elm_image_file_set(status_obj, ui_utils_get_resource(MESSAGE_READ_ICON), NULL);
				} else if(item->last_msg_status == TG_MESSAGE_STATE_UNKNOWN) {

				}
#if 0
				Evas_Object *msg_status = elm_layout_add(ad->nf);
				elm_layout_file_set(msg_status, edj_path, "status_bg_layout");
				evas_object_size_hint_weight_set(msg_status, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(msg_status, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_show(msg_status);
				elm_object_part_content_set(msg_status, "content", status_obj);
#endif
				evas_object_color_set(status_obj, 75, 96,178, 255);
				elm_object_part_content_set(item_layout, "swallow.read_unread_status", status_obj);

			} else {
				if (item->number_of_unread_msgs > 0) {
					Evas_Object* num_lbl = elm_label_add(ad->nf);
					elm_object_style_set(num_lbl, "transparent");
					char unread_msgs[256];
					sprintf(unread_msgs, "<font=Tizen:style=Bold color=#ffffff align=center><font_size=25>%d</font_size></font>", item->number_of_unread_msgs);
					elm_object_text_set(num_lbl, unread_msgs);
					evas_object_size_hint_weight_set(num_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
					evas_object_size_hint_align_set(num_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
					evas_object_show(num_lbl);

					Evas_Object* msg_status = elm_layout_add(ad->nf);
					elm_layout_file_set(msg_status, edj_path, "count_bg_layout");
					evas_object_size_hint_weight_set(msg_status, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
					evas_object_size_hint_align_set(msg_status, EVAS_HINT_FILL, EVAS_HINT_FILL);
					evas_object_show(msg_status);
					elm_object_part_content_set(msg_status, "content", num_lbl);
					//evas_object_color_set(num_lbl, 37, 137, 186, 255 * 0.8);
					elm_object_part_content_set(item_layout, "swallow.unread_count", msg_status);
				}
			}
		}
		/*************************** sent message status ***************************************/
		item->main_item_layout = layout;
		evas_object_event_callback_add(item->main_item_layout, EVAS_CALLBACK_DEL, on_buddy_main_item_deleted, item);
		return layout;
	}
	return NULL;
}

void reload_main_list_view(appdata_s* ad)
{
	Evas_Object *buddy_list = evas_object_data_get(ad->nf, "buddy_list");
	if (buddy_list) {
		elm_genlist_clear(buddy_list);

		int i = 0;
		static Elm_Genlist_Item_Class itc;
		itc.item_style = "full";
		itc.func.text_get = NULL;
		itc.func.content_get = on_chat_item_load_requested;
		itc.func.state_get = NULL;
		itc.func.del = NULL;

		int size = eina_list_count(ad->main_list);
		if(size > 0) {
			for (i = 0; i < size; i++) {
				elm_genlist_item_append(buddy_list, &itc, (void*) i, NULL, ELM_GENLIST_ITEM_NONE, on_main_chat_item_selected, (void*) i);
			}
		} else {
			i = 1;
			elm_genlist_item_append(buddy_list, &itc, (void*) i, NULL, ELM_GENLIST_ITEM_NONE, on_main_chat_item_selected, (void*) i);
		}
		evas_object_show(buddy_list);
	}
}


void refresh_main_list_view(appdata_s* ad, Eina_Bool is_new_item)
{
	Evas_Object *buddy_list = evas_object_data_get(ad->nf, "buddy_list");
	if (buddy_list) {
		if (is_new_item) {
			static Elm_Genlist_Item_Class itc;
			itc.item_style = "full";
			itc.func.text_get = NULL;
			itc.func.content_get = on_chat_item_load_requested;
			itc.func.state_get = NULL;
			itc.func.del = NULL;

			int size = eina_list_count(ad->main_list);
			int i = size - 1;
			elm_genlist_item_append(buddy_list, &itc, (void*) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
		} else {
			elm_genlist_clear(buddy_list);

			static Elm_Genlist_Item_Class itc;
			itc.item_style = "full";
			itc.func.text_get = NULL;
			itc.func.content_get = on_chat_item_load_requested;
			itc.func.state_get = NULL;
			itc.func.del = NULL;

			int i = 0;
			if (ad->main_list) {
				int size = eina_list_count(ad->main_list);
				if(size > 0) {
					for (i = 0; i < size; i++) {
						elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
					}
				} else {
					i = 1;
					elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
				}
			}
		}
		elm_genlist_realized_items_update(buddy_list);
	} else {

		int size = eina_list_count(ad->main_list);
		if (size > 0) {

			Evas_Object* no_chat_img = evas_object_data_get(ad->nf, "no_chat_image");
			if(no_chat_img) {
				evas_object_del(no_chat_img);
			}

			Evas_Object* bg_box = evas_object_data_get(ad->nf, "main_list_box");
			if (bg_box) {
				int i;
				static Elm_Genlist_Item_Class itc;
				Evas_Object *buddy_list = elm_genlist_add(ad->nf);
				elm_list_mode_set(buddy_list, ELM_LIST_COMPRESS);
				elm_genlist_mode_set(buddy_list, ELM_LIST_COMPRESS);
				evas_object_size_hint_weight_set(buddy_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				evas_object_size_hint_align_set(buddy_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
				evas_object_data_set(buddy_list, "app_data", ad);

				itc.item_style = "full";
				itc.func.text_get = NULL;
				itc.func.content_get = on_chat_item_load_requested;
				itc.func.state_get = NULL;
				itc.func.del = NULL;

				int size = eina_list_count(ad->main_list);
				if(size > 0) {
					for (i = 0; i < size; i++) {
						elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
					}
				} else {
					i = 1;
					elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
				}
				evas_object_show(buddy_list);
				elm_box_pack_end(bg_box, buddy_list);
				evas_object_data_set(ad->nf, "buddy_list", buddy_list);
			}
		}
	}
}

static void on_user_list_search_clicked(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
#if 0
	if (ad->panel) {
		Evas_Object *panel_list = evas_object_data_get(ad->panel, "panel_list");
		if (panel_list) {
			evas_object_del(panel_list);
		}
		evas_object_del(ad->panel);
		ad->panel = NULL;
	}
#endif
	delete_floating_button(ad);
	launch_start_peer_search_view(ad);
}

static void on_search_icon_pressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(TG_SEARCH_PRESSED_ICON), NULL);
}

static void on_search_icon_unpressed(void *data, Evas_Object *obj, void *event_info)
{
	elm_image_file_set(data, ui_utils_get_resource(TG_SEARCH_ICON), NULL);
}

static void _more_popup_rotate(void *data, Evas_Object *obj, void *event_info)
{
	int pos;
	Evas_Coord w, h;
	appdata_s *ad = data;

	elm_win_screen_size_get(ad->win, NULL, NULL, &w, &h);
	pos = elm_win_rotation_get(ad->win);

	switch (pos) {
	case 90:
	case 270:
		evas_object_move(ad->menu_popup, 0, w);
		break;
	case 180:
	default:
		evas_object_move(ad->menu_popup, 0, h);
		break;
    }
}

static void _ctxpopup_dismiss_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	evas_object_del(ad->menu_popup);
	ad->menu_popup = NULL;
}

static void _ctxpopup_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;

	if (!ad) {
			LOGE("ad is NULL");
			return;
	}

	if (!ad->win) {
		LOGE("window is NULL");
		return;
	}
	evas_object_smart_callback_del(ad->win, "rotation,changed", _more_popup_rotate);
	if (ad->menu_popup) {
		evas_object_smart_callback_del(ad->menu_popup, "dismissed", _ctxpopup_dismiss_cb);
		evas_object_del(ad->menu_popup);
		ad->menu_popup = NULL;
	}
}

static void ctxpopup_delete_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad) {
		LOGE("ad is NULL");
		return;
	}

	_ctxpopup_dismiss_cb(ad, NULL, NULL);

	launch_main_item_deletion_view_cb(ad);
}

static void ctxpopup_search_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad) {
		LOGE("ad is NULL");
		return;
	}
	delete_floating_button(ad);
	_ctxpopup_dismiss_cb(ad, NULL, NULL);

	/* please input here when search menu is clicked */
	launch_search_message_view(ad);
}

static void ctxpopup_contact_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad) {
		LOGE("ad is NULL");
		return;
	}

	_ctxpopup_dismiss_cb(ad, NULL, NULL);
    on_floating_icon_clicked(data, obj, event_info);
	/* please input here when contact menu is clicked */
}

static void ctxpopup_settings_select_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	if (!ad) {
		LOGE("ad is NULL");
		return;
	}

	_ctxpopup_dismiss_cb(ad, NULL, NULL);
	delete_floating_button(ad);
	launch_settings_screen(ad);
}

static void _create_more_popup(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *it;
	Evas_Object *ctxpopup;
	appdata_s *ad = data;

	if (!ad) {
			LOGE("ad is NULL");
			return;
	}

	if (ad->current_app_state != TG_USER_MAIN_VIEW_STATE) {
		return;
	}

	ctxpopup = elm_ctxpopup_add(ad->nf);
	elm_object_style_set(ctxpopup, "more/default");
	elm_ctxpopup_auto_hide_disabled_set(ctxpopup, EINA_TRUE);
	eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_BACK, eext_ctxpopup_back_cb, NULL);
	eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_MORE, eext_ctxpopup_back_cb, NULL);
	evas_object_event_callback_add(ctxpopup, EVAS_CALLBACK_DEL, _ctxpopup_del_cb, ad);

	evas_object_smart_callback_add(ctxpopup, "dismissed", _ctxpopup_dismiss_cb, ad);
	evas_object_smart_callback_add(ad->win, "rotation,changed", _more_popup_rotate, ad);

	it = elm_ctxpopup_item_append(ctxpopup, i18n_get_text("IDS_TGRAM_OPT_DELETE"), NULL, ctxpopup_delete_select_cb, ad);
	it = elm_ctxpopup_item_append(ctxpopup, i18n_get_text("IDS_TGRAM_OPT_SEARCH"), NULL, ctxpopup_search_select_cb, ad);
	it = elm_ctxpopup_item_append(ctxpopup, i18n_get_text("IDS_TGRAM_OPT_CONTACTS"), NULL, ctxpopup_contact_select_cb, ad);
	it = elm_ctxpopup_item_append(ctxpopup, i18n_get_text("IDS_TGRAM_OPT_SETTINGS"), NULL, ctxpopup_settings_select_cb, ad);
	//elm_object_item_domain_text_translatable_set(it, SETTING_PACKAGE, EINA_TRUE);
	elm_ctxpopup_direction_priority_set(ctxpopup, ELM_CTXPOPUP_DIRECTION_UP, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN, ELM_CTXPOPUP_DIRECTION_UNKNOWN);

	if (ad->menu_popup) {
		evas_object_del(ad->menu_popup);
	}

	ad->menu_popup = ctxpopup;

	_more_popup_rotate(ad, NULL, NULL);

	evas_object_show(ctxpopup);

}

Evas_Object *create_no_object_layout(appdata_s* ad)
{
	if (!ad)
		return NULL;

	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "no_chat_layout");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);

	Evas_Object *no_chat_lbl =  elm_label_add(ad->nf);
	evas_object_size_hint_weight_set(no_chat_lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(no_chat_lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(no_chat_lbl);
	elm_label_ellipsis_set(no_chat_lbl, EINA_TRUE);

	char temp_text[256];
	sprintf(temp_text, "<font=Tizen:style=Bold =#000000 align=center><font_size=30>%s</font_size></font>", i18n_get_text("IDS_TGRAM_NPBODY_NO_CHATS"));

	elm_object_text_set(no_chat_lbl, temp_text);
	elm_object_part_content_set(layout, "no_chats_lbl", no_chat_lbl);

	char temp_text1[256*4];
	sprintf(temp_text1, "<font=Tizen:style=Normal align=center><font_size=30>%s</font_size></font>", i18n_get_text("IDS_TGRAM_BODY_TO_START_A_NEW_CONVERSATION_TAP_THE_CREATE_NEW_GROUP_BUTTON_IN_THE_BOTTOM_RIGHT_OR_PRESS_THE_MENU_KEY_FOR_MORE_OPTIONS"));

	Evas_Object *no_chat_msg_lbl = elm_entry_add(ad->nf);
	elm_entry_editable_set(no_chat_msg_lbl, EINA_FALSE);
	elm_entry_context_menu_disabled_set(no_chat_msg_lbl, EINA_TRUE);
	//elm_entry_selection_handler_disabled_set(no_chat_msg_lbl, EINA_TRUE);
	elm_object_text_set(no_chat_msg_lbl, temp_text1);

	elm_object_part_content_set(layout, "no_chats_msg_lbl", no_chat_msg_lbl);

	return layout;
}

void launch_user_main_view_cb(appdata_s* ad)
{
	if (!ad)
		return;

#if 0
	if (ad->panel) {
		Evas_Object *panel_list = evas_object_data_get(ad->panel, "panel_list");
		if (panel_list) {
			evas_object_del(panel_list);
		}
		evas_object_del(ad->panel);
		ad->panel = NULL;
	}
#endif
	ad->current_app_state = TG_USER_MAIN_VIEW_STATE;
	ad->is_tg_initilized = EINA_TRUE;
	char edj_path[PATH_MAX] = {0, };
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
	send_request_for_server_connection_status(ad, ad->service_client);
	send_request_for_delete_notifications(ad, ad->service_client);

	Evas_Object* scroller = elm_scroller_add(ad->nf);
	elm_scroller_bounce_set(scroller, EINA_FALSE, EINA_TRUE);
	elm_scroller_policy_set(scroller,ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);

	Evas_Object* layout = elm_layout_add(ad->nf);
	elm_layout_file_set(layout, edj_path, "user_main_screen_new");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(layout);
	elm_object_content_set(scroller, layout);

	//elm_layout_theme_set(ad->layout, "layout", "drawer", "panel");
	// sandeep
	//create_side_main_view(ad);


	/************** no chat item++ *********************/
	Evas_Object *buddy_list = NULL;
	Evas_Object* bg_box = elm_box_add(layout);
	evas_object_size_hint_weight_set(bg_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(bg_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(bg_box);
	elm_object_part_content_set(layout, "main_box", bg_box);

	if (ad->main_list == NULL || eina_list_count(ad->main_list) <= 0) {
		Evas_Object* no_chat_img = create_no_object_layout(ad);

		evas_object_data_set(ad->nf, "no_chat_image", no_chat_img);

		elm_box_pack_end(bg_box, no_chat_img);
	} else {
		int i;
		static Elm_Genlist_Item_Class itc;
		buddy_list = elm_genlist_add(ad->nf);
		elm_list_mode_set(buddy_list, ELM_LIST_COMPRESS);
		elm_genlist_mode_set(buddy_list, ELM_LIST_COMPRESS);
		evas_object_size_hint_weight_set(buddy_list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(buddy_list, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_data_set(buddy_list, "app_data", ad);
		elm_genlist_homogeneous_set(buddy_list, EINA_TRUE);


		itc.item_style = "full";
		itc.func.text_get = NULL;
		itc.func.content_get = on_chat_item_load_requested;
		itc.func.state_get = NULL;
		itc.func.del = NULL;

		int size = eina_list_count(ad->main_list);
		if(size > 0) {
			for (i = 0; i < size; i++) {
				elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
			}
		} else {
			i = 1;
			elm_genlist_item_append(buddy_list, &itc, (void *) i, NULL, ELM_GENLIST_ITEM_NONE, NULL, (void*) i);
		}
		evas_object_show(buddy_list);
		elm_box_pack_end(bg_box, buddy_list);
		evas_object_data_set(ad->nf, "buddy_list", buddy_list);

		evas_object_smart_callback_add(buddy_list, "longpressed", on_buddy_list_longpress, ad);
		evas_object_smart_callback_add(buddy_list, "selected", on_main_chat_item_selected, ad);

	}
	evas_object_data_set(ad->nf, "main_list_box", bg_box);
	/************** no chat item-- *********************/



	create_floating_button(ad);
#if 0
	Evas_Object* search_layout = elm_layout_add(ad->nf);
	elm_layout_file_set(search_layout, edj_path, "title_search_layout");
	evas_object_size_hint_weight_set(search_layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(search_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(search_layout);

	Evas_Object *search_btn = elm_button_add(layout);
	elm_object_style_set(search_btn, "transparent");
	evas_object_size_hint_align_set(search_btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(search_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);


    Evas_Object *search_icon = elm_image_add(layout);
    elm_image_file_set(search_icon, ui_utils_get_resource(TG_SEARCH_ICON), NULL);
    evas_object_show(search_icon);

    elm_object_content_set(search_btn, search_icon);

    elm_object_part_content_set(search_layout, "search_box", search_btn);
    evas_object_smart_callback_add(search_btn, "clicked", on_user_list_search_clicked, ad);
    evas_object_smart_callback_add(search_btn, "pressed", on_search_icon_pressed, search_icon);
    evas_object_smart_callback_add(search_btn, "unpressed", on_search_icon_unpressed, search_icon);
#endif

    ad->main_item = elm_naviframe_item_push(ad->nf, i18n_get_text("IDS_TGRAM_HEADER_TELEGRAM"), NULL, NULL, scroller, NULL);

#if 0
    Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->nf, "<font=Tizen:style=Bold color=#ffffff align=center><font_size=48>Telegram</font_size></font>", NULL, NULL, scroller, NULL);
	elm_object_item_part_content_set(navi_item, "title_right_btn", search_layout);
	/* left panel toggle button */
	Evas_Object *panel_btn = create_button(ad->nf, "naviframe/drawers", NULL);
	evas_object_smart_callback_add(panel_btn, "clicked", on_side_panel_requested, ad);
	elm_object_item_part_content_set(navi_item, "title_left_btn", panel_btn);
#endif

//	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_MORE, on_messaging_menu_button_clicked, ad);

	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_MORE, _create_more_popup, ad);
}


