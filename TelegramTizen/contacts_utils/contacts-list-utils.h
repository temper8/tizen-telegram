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

#ifndef __LIST_H__
#define __LIST_H__

#include <contacts.h>

#define CONTACTS_LIST_FOREACH(list, record) \
    bool success = (contacts_list_get_current_record_p(list, &record) == CONTACTS_ERROR_NONE); \
    for( ; success; \
        success = ((contacts_list_next(list) == CONTACTS_ERROR_NONE) \
        && (contacts_list_get_current_record_p(list, &record) == CONTACTS_ERROR_NONE)) \
        )

/**
 * @brief Execute query
 * @remark return value MUST be destroyed with contacts_list_destroy by you
 * @param[in]   table_uri       URI to DB table
 * @param[in]   filter          Filter for query
 * @return list on success, otherwise NULL
 */
contacts_list_h sc_list_utils_run_query(const char *table_uri, contacts_filter_h filter);

/**
 *@brief Retrieves record list from contacts DB
 *@remark return value MUST be destroyed with contacts_list_destroy by you
 *@param[in]    table_uri       URI to table
 *@param[in]    filter_field    Filterable field of table
 *@param[in]    filter_val      Value of filterable field @a filter_field
 *@return records list on success, otherwise NULL
 */
contacts_list_h sc_list_utils_get_records_list_str_filter(const char *table_uri,
        unsigned filter_field, const char *filter_val);

/**
 *@brief Retrieves record list from contacts DB
 *@remark return value MUST be destroyed with contacts_list_destroy by you
 *@param[in]    table_uri       URI to table
 *@param[in]    filter_field    Filterable field of table
 *@param[in]    filter_val      Value of filterable field @a filter_field
 *@return records list on success, otherwise NULL
 */
contacts_list_h sc_list_utils_get_records_list_int_filter(const char *table_uri,
        unsigned filter_field, int filter_val);

/**
 *@brief Retrieves record list from contacts DB
 *@remark return value MUST be destroyed with contacts_list_destroy by you
 *@param[in]    table_uri       URI to table
 *@param[in]    filter_field    Filterable field of table
 *@param[in]    filter_val      Value of filterable field @a filter_field
 *@return records list on success, otherwise NULL
 */
contacts_list_h sc_list_utils_get_records_list_bool_filter(const char *table_uri,
        unsigned filter_field, bool filter_val);

#endif /* __LIST_H__ */
