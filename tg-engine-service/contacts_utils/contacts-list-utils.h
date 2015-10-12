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
