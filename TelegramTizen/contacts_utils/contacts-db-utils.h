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

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <stdbool.h>

/**
 * @brief Connect to database
 * @return true if success, otherwise false
 */
bool sc_db_utils_connect();

/**
 * @brief Disconnect from database
 * @return true if success, otherwise false
 */
bool sc_db_utils_disconnect();

/**
 * @brief Check is connected to database
 * @return true if connected, otherwise false
 */
bool sc_db_utils_is_connected();

/**
 * @brief Check database error code
 * @param[in]   err_code    Error code
 * @return true if @a err_code == CONTACTS_ERROR_NONE, otherwise false
 */
bool sc_db_utils_is_success(int err_code);

#endif /* __DATABASE_H__ */
