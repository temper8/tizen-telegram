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
