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


#ifndef __RECORD_H__
#define __RECORD_H__

#include <contacts.h>

/**
 * @brief Gets child record
 * @remark if child record is not exist, new child record will be created
 * @remark return value MUST NOT be destroyed by you
 * @param[in]       parent_record       Handle to parent record
 * @param[in]       property_id         Id of foreign key in parent table
 * @param[in]       child_table_uri     URI of child table
 * return Handle to child record if success, otherwise NULL
 */
contacts_record_h sc_record_utils_get_child_record(contacts_record_h parent_record, unsigned property_id, const char *child_table_uri);

/**
 * @brief Gets string value from child record if it exist
 * @remark @a value MUST NOT be destroyed by you
 * @param[in]       parent_record       Parent record
 * @param[in]       parent_property_id  ID of foreign key in parent table
 * @param[in]       child_property_id   ID of field in child table, where store string value
 * @param[out]      value               The value to be returned
 * @return true if success, otherwise false
 */
bool sc_record_utils_get_child_str_p(contacts_record_h parent_record, unsigned parent_property_id, unsigned child_property_id, char **value);

/**
 * @brief Gets integer value from child record if it exist
 * @param[in]       parent_record       Parent record
 * @param[in]       parent_property_id  ID of foreign key in parent table
 * @param[in]       child_property_id   ID of field in child table, where store integer value
 * @param[out]      value               The value to be returned
 * @return true if success, otherwise false
 */
bool sc_record_utils_get_child_int(contacts_record_h parent_record, unsigned parent_property_id, unsigned child_property_id, int *value);

/**
 * @brief Sets string value to child record
 * @param[in]       parent_record       Parent record
 * @param[in]       parent_property     ID of foreign key in parent table
 * @param[in]       child_uri           URI of child table
 * @param[in]       child_property      ID of field in child table
 * @param[in]       str_val             Passed string value
 * @return true if success, otherwise false
 */
bool sc_record_utils_set_child_str(contacts_record_h parent_record,
        unsigned parent_property, const char* child_uri, unsigned child_property, const char *str_val);

/**
 * @brief Sets integer value to child record
 * @param[in]       parent_record       Parent record
 * @param[in]       parent_property     ID of foreign key in parent table
 * @param[in]       child_uri           URI of child table
 * @param[in]       child_property      ID of field in child table
 * @param[in]       int_val             Passed integer value
 * @return true if success, otherwise false
 */
bool sc_record_utils_set_child_int(contacts_record_h parent_record,
        unsigned parent_property, const char *child_uri, unsigned child_property, int int_val);

#endif /* __RECORD_H__ */
