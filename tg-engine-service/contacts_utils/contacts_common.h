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

#ifndef __COMMON_H__
#define __COMMON_H__

#include <time.h>

typedef enum
{
    CF_ADDRESSBOOK = 0,
    CF_FIRST_NAME,
    CF_LAST_NAME,
    CF_PHONE_NUMBER,
    CF_EMAIL,
    CF_URL,
    CF_COMPANY,
    CF_BIRTHDAY,
    CF_NOTE,
    CF_MAX
} sc_common_contact_fields;

/**
 * @brief Retrieves properties for contact table
 * @param[in]    field_type          Type of field: number, email
 * @param[out]   parent_property_id  Contact's property as key to child table
 * @param[out]   child_uri           URI of child table
 * @param[out]   child_property_id   ID of desired field of child table
 */
void sc_common_get_contact_properties(sc_common_contact_fields field_type, unsigned *parent_property_id, const char **child_uri, unsigned *child_property_id);

/**
 * @brief Convert date to contacts database format
 * @param[in]   date    date tm structure or NULL for current date
 * @return number representation of date or current date
 */
int sc_common_date_to_int(const struct tm *date);

/**
 * @brief Convert number representation of date to tm structure
 * @param[in]   date_value    date in contacts database format
 * @return date tm structure
 */
struct tm sc_common_int_to_date(int date_value);

/**
 * @brief Convert date to string
 * @remark Return value MUST be destroyed with free() by you
 * @param[in]   date        date tm structure or NULL for current date
 * @return date in string representation
 */
char *sc_common_date_to_str(struct tm *date);

/**
 * @brief Gets contact field name by contact type
 * @remark Return value MUST NOT be destroyed by you
 * @param[in]   field_type  Field type
 * @return contact name
 */
const char *sc_common_get_contact_field_name(sc_common_contact_fields field_type);

/**
 * @brief Trims spaces in @a str
 * @remark Return value MUST be destroyed with free() by you
 * @param[in]   str     String to trim
 * @return Trimmed string on success, otherwise NULL
 */
char *sc_common_trim_spaces_in_string(const char *str);

#endif //__COMMON_H__
