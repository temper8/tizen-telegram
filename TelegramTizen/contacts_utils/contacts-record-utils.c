/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "contacts-record-utils.h"
#include "contacts-db-utils.h"
#include "logger.h"

contacts_record_h sc_record_utils_get_child_record(contacts_record_h parent_record, unsigned property_id, const char *child_table_uri)
{
	RETVM_IF(!sc_db_utils_is_connected(), NULL, "not connected to DB");
	RETVM_IF(NULL == parent_record, NULL, "contact_record is null");
	RETVM_IF(NULL == child_table_uri, NULL, "child_table_uri is null");
	int count = 0;
	contacts_record_h child_record = NULL;
	if(sc_db_utils_is_success(contacts_record_get_child_record_count(parent_record, property_id, &count)))
	{
		if(count)
		{
			sc_db_utils_is_success(contacts_record_get_child_record_at_p(parent_record, property_id, 0, &child_record));
		}
		else
		{
			if(sc_db_utils_is_success(contacts_record_create(child_table_uri, &child_record)))
			{
				if(!sc_db_utils_is_success(contacts_record_add_child_record(parent_record, property_id, child_record)))
				{
					contacts_record_destroy(child_record, true);
					child_record = NULL;
				}
			}
		}
	}
	return child_record;
}

bool sc_record_utils_get_child_str_p(contacts_record_h parent_record, unsigned parent_property_id, unsigned child_property_id, char **value)
{
	RETVM_IF(NULL == parent_record, false, "parent record is null");
	RETVM_IF(NULL == value, false, "pointer to value is null");
	contacts_record_h child_record = NULL;
	char *temp_value = NULL;
	bool result = sc_db_utils_is_success(contacts_record_get_child_record_at_p(parent_record, parent_property_id, 0, &child_record))
		&& sc_db_utils_is_success(contacts_record_get_str_p(child_record, child_property_id, &temp_value));
	if(result)
	{
		*value = temp_value;
	}
	return result;
}

bool sc_record_utils_get_child_int(contacts_record_h parent_record, unsigned parent_property_id, unsigned child_property_id, int *value)
{
	RETVM_IF(NULL == parent_record, false, "parent record is null");
	RETVM_IF(NULL == value, false, "pointer to value is null");
	contacts_record_h child_record = NULL;
	int temp_value = 0;
	bool result = sc_db_utils_is_success(contacts_record_get_child_record_at_p(parent_record, parent_property_id, 0, &child_record))
		&& sc_db_utils_is_success(contacts_record_get_int(child_record, child_property_id, &temp_value));
	if(result)
	{
		*value = temp_value;
	}
	return result;
}

bool sc_record_utils_set_child_str(contacts_record_h contact_record, unsigned parent_property, const char* child_uri, unsigned child_property, const char *str_val)
{
	RETVM_IF(!sc_db_utils_is_connected(), false, "not connected to DB");
	RETVM_IF(NULL == str_val, false, "name is null");
	RETVM_IF(NULL == contact_record, false, "contact_record is null");
	bool result = false;
	contacts_record_h child_record = sc_record_utils_get_child_record(contact_record, parent_property, child_uri);
	if(child_record)
	{
		result = sc_db_utils_is_success(contacts_record_set_str(child_record, child_property, str_val));
	}
	return result;
}

bool sc_record_utils_set_child_int(contacts_record_h contact_record, unsigned parent_property, const char *child_uri, unsigned child_property, int int_val)
{
	RETVM_IF(!sc_db_utils_is_connected(), false, "not connected to DB");
	RETVM_IF(NULL == contact_record, false, "contact_record is null");
	bool result = false;
	contacts_record_h child_record = sc_record_utils_get_child_record(contact_record, parent_property, child_uri);
	if(child_record)
	{
		result = sc_db_utils_is_success(contacts_record_set_int(child_record, child_property, int_val));
	}
	return result;
}
