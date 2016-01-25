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

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <stdbool.h>

/**
 * @brief Connect to database
 * @return true if success, otherwise false
 */
extern bool sc_db_utils_connect();

/**
 * @brief Disconnect from database
 * @return true if success, otherwise false
 */
extern bool sc_db_utils_disconnect();

/**
 * @brief Check is connected to database
 * @return true if connected, otherwise false
 */
extern bool sc_db_utils_is_connected();

/**
 * @brief Check database error code
 * @param[in]   err_code    Error code
 * @return true if @a err_code == CONTACTS_ERROR_NONE, otherwise false
 */
bool sc_db_utils_is_success(int err_code);

#endif /* __DATABASE_H__ */
