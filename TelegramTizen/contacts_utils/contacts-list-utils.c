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

#include "contacts-list-utils.h"

#include "contacts-db-utils.h"
#include "logger.h"

static contacts_filter_h _get_filter_with_str_field(const char *table_uri, unsigned int filter_field, const char *str_val);
static contacts_filter_h _get_filter_with_int_field(const char *table_uri, unsigned int filter_field, int int_val);
static contacts_filter_h _get_filter_with_bool_field(const char *table_uri, unsigned int filter_field, bool bool_val);

static contacts_filter_h _get_filter_with_str_field(const char *table_uri, unsigned int filter_field, const char *str_val)
{
    RETVM_IF(NULL == table_uri, NULL, "table_uri is null");
    RETVM_IF(NULL == str_val, NULL, "value is null");
    contacts_filter_h filter = NULL;

    if( !(sc_db_utils_is_success(contacts_filter_create(table_uri, &filter))
     && sc_db_utils_is_success(contacts_filter_add_str(filter, filter_field, CONTACTS_MATCH_FULLSTRING, str_val))))
    {
        contacts_filter_destroy(filter);
        filter = NULL;
    }
    return filter;
}

static contacts_filter_h _get_filter_with_int_field(const char *table_uri, unsigned int filter_field, int int_val)
{
    RETVM_IF(NULL == table_uri, NULL, "table_uri is null");
    contacts_filter_h filter = NULL;

    if( !(sc_db_utils_is_success(contacts_filter_create(table_uri, &filter))
     && sc_db_utils_is_success(contacts_filter_add_int(filter, filter_field, CONTACTS_MATCH_EQUAL, int_val))))
    {
        contacts_filter_destroy(filter);
        filter = NULL;
    }
    return filter;
}

static contacts_filter_h _get_filter_with_bool_field(const char *table_uri, unsigned int filter_field, bool bool_val)
{
    RETVM_IF(NULL == table_uri, NULL, "table_uri is null");
    contacts_filter_h filter = NULL;

    if( !(sc_db_utils_is_success(contacts_filter_create(table_uri, &filter))
     && sc_db_utils_is_success(contacts_filter_add_bool(filter, filter_field, bool_val))))
    {
        contacts_filter_destroy(filter);
        filter = NULL;
    }
    return filter;
}

contacts_list_h sc_list_utils_run_query(const char *table_uri, contacts_filter_h filter)
{
    RETVM_IF(!sc_db_utils_is_connected(), NULL, "not connected to DB");
    RETVM_IF(NULL == table_uri, NULL, "table_uri is null");
    RETVM_IF(NULL == filter, NULL, "filter is null");
    contacts_list_h  list  = NULL;
    contacts_query_h query       = NULL;
    if( sc_db_utils_is_success(contacts_query_create(table_uri, &query))
     && sc_db_utils_is_success(contacts_query_set_filter(query, filter)))
    {
        if(!sc_db_utils_is_success(contacts_db_get_records_with_query(query, 0, 0, &list)))
        {
            ERR("Error getting records list");
            contacts_list_destroy(list, true);
            list = NULL;
        }
        contacts_query_destroy(query);
    }
    return list;
}

contacts_list_h sc_list_utils_get_records_list_str_filter(const char *table_uri,
        unsigned filter_field, const char *filter_val)
{
    RETVM_IF(NULL == table_uri, NULL, "table_uri is null");
    RETVM_IF(NULL == filter_val, NULL, "filter_val is null");

    RETVM_IF(!sc_db_utils_is_connected(), NULL, "Not connected to DB");
    contacts_list_h     list   = NULL;
    contacts_filter_h   filter = _get_filter_with_str_field(table_uri, filter_field, filter_val);

    if(filter)
    {
        list = sc_list_utils_run_query(table_uri, filter);

        contacts_filter_destroy(filter);
    }
    return list;
}

contacts_list_h sc_list_utils_get_records_list_int_filter(const char *table_uri,
        unsigned filter_field, int filter_val)
{
    RETVM_IF(NULL == table_uri, NULL, "table_uri is null");

    RETVM_IF(!sc_db_utils_is_connected(), NULL, "Not connected to DB");
    contacts_list_h     list   = NULL;
    contacts_filter_h   filter = _get_filter_with_int_field(table_uri, filter_field, filter_val);

    if(filter)
    {
        list = sc_list_utils_run_query(table_uri, filter);

        contacts_filter_destroy(filter);
    }
    return list;
}

contacts_list_h sc_list_utils_get_records_list_bool_filter(const char *table_uri,
        unsigned filter_field, bool filter_val)
{
    RETVM_IF(NULL == table_uri, NULL, "table_uri is null");

    RETVM_IF(!sc_db_utils_is_connected(), NULL, "Not connected to DB");
    contacts_list_h     list   = NULL;
    contacts_filter_h   filter = _get_filter_with_bool_field(table_uri, filter_field, filter_val);

    if(filter)
    {
        list = sc_list_utils_run_query(table_uri, filter);

        contacts_filter_destroy(filter);
    }
    return list;
}
