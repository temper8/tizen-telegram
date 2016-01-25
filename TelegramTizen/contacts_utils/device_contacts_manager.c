/*
    This file is part of Telegram application for tizen

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
*/

#include "device_contacts_manager.h"
#include "tg_common.h"
#include "tg_db_wrapper.h"
#include "logger.h"

bool sc_cdetails_get_contact_val(sc_common_contact_fields field_type, int contact_id, char **value)
{
	RETVM_IF(field_type >= CF_MAX || field_type < CF_PHONE_NUMBER, false, "incorrect field type");
	RETVM_IF(NULL == value, false, "pointer to value is null");

	bool is_success = false;
	unsigned parent_property_id = 0, child_property_id = 0;
	char *tmp_value = NULL;
	sc_common_get_contact_properties(field_type, &parent_property_id, NULL, &child_property_id);

	contacts_record_h contact_record = NULL;
	if(sc_db_utils_is_success(contacts_db_get_record(_contacts_contact._uri, contact_id, &contact_record)))
	{
		if(CF_BIRTHDAY == field_type)
		{
			int ivalue = 0;
			if( sc_record_utils_get_child_int(contact_record, parent_property_id, child_property_id, &ivalue))
			{
				struct tm date = sc_common_int_to_date(ivalue);
				*value = sc_common_date_to_str(&date);
				is_success = true;
			}
		}
		else
		{
			if( sc_record_utils_get_child_str_p(contact_record, parent_property_id, child_property_id, &tmp_value)
					&& tmp_value)
			{
				*value = strdup(tmp_value);
				is_success = true;
			}
		}
		contacts_record_destroy(contact_record, false);
	}
	return is_success;
}

Eina_List* get_contact_list_from_device_db()
{
	Eina_List* contact_list = NULL;

	contacts_record_h record = NULL;
	contacts_list_h person_list = NULL;
	if(sc_db_utils_connect())
	{


		if(sc_db_utils_is_success(contacts_db_get_all_records(_contacts_person._uri, 0, 0, &person_list)))
		{
			CONTACTS_LIST_FOREACH(person_list, record)
				{
				char *name = NULL;
				int id = 0;
				if (sc_db_utils_is_success(contacts_record_get_str_p(record, _contacts_person.display_name, &name))
						&& sc_db_utils_is_success(contacts_record_get_int(record, _contacts_person.id, &id)))
				{
					contact_data_s* contact_data = (contact_data_s*)malloc(sizeof(contact_data_s));
					contact_data->display_name = NULL;
					contact_data->first_name = NULL;
					contact_data->last_name = NULL;
					contact_data->phone_number = NULL;

					contact_data->contact_id = id;
					contact_data->display_name = strdup(elm_entry_utf8_to_markup(name));

					char *first_name = NULL;
					if(sc_cdetails_get_contact_val(CF_FIRST_NAME, contact_data->contact_id, &first_name))
					{
						if (first_name) {
							contact_data->first_name = strdup(elm_entry_utf8_to_markup(first_name));
							free(first_name);
						}
					}

					char *last_name = NULL;
					if(sc_cdetails_get_contact_val(CF_LAST_NAME, contact_data->contact_id, &last_name))
					{
						if (last_name) {
							contact_data->last_name = strdup(elm_entry_utf8_to_markup(last_name));
							free(last_name);
						}
					}

					char *pic_url = NULL;
					if(sc_cdetails_get_contact_val(CF_URL, contact_data->pic_url, &pic_url))
					{
						if (pic_url) {
							contact_data->pic_url = strdup(elm_entry_utf8_to_markup(pic_url));
							free(pic_url);
						} else {
							contact_data->pic_url = strdup(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC));
						}
					} else {
						contact_data->pic_url = strdup(ui_utils_get_resource(DEFAULT_LIST_THUMB_SINGLE_PIC));
					}


					char *phone_number = NULL;
					if(sc_cdetails_get_contact_val(CF_PHONE_NUMBER, contact_data->contact_id, &phone_number))
					{
						if (phone_number) {
							contact_data->phone_number = strdup(elm_entry_utf8_to_markup(phone_number));
							free(phone_number);
						}
					}

					// check contact exist in buddylist
					Eina_Bool is_tg_contact = EINA_FALSE;
					if (contact_data->phone_number) {
						is_tg_contact = is_phone_number_exists_in_buddy_list(contact_data->phone_number);
					}

					if (contact_data->phone_number == NULL || is_tg_contact) {

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

						if (contact_data->pic_url) {
							free(contact_data->pic_url);
							contact_data->pic_url = NULL;
						}

						if (contact_data->phone_number) {
							free(contact_data->phone_number);
							contact_data->phone_number = NULL;
						}

						free(contact_data);
						continue;
					}

					contact_list = eina_list_append(contact_list, contact_data);
				}

				}
			contacts_list_destroy(person_list, true);
		}
	}
	sc_db_utils_disconnect();

	return contact_list;
}


void free_contact_list(Eina_List *contact_data)
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

