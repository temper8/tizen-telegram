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

#include "contacts-db-utils.h"

#include "logger.h"

#include <contacts.h>

static bool is_connected = false;

bool sc_db_utils_connect()
{
    if(!is_connected)
    {
        is_connected = sc_db_utils_is_success(contacts_connect());
    }
    return is_connected;
}

bool sc_db_utils_disconnect()
{
    if(is_connected)
    {
        is_connected = !sc_db_utils_is_success(contacts_disconnect());
    }
    return !is_connected;
}

bool sc_db_utils_is_connected()
{
    return is_connected;
}

bool sc_db_utils_is_success(int err_code)
{
#ifdef _DEBUG

    if(err_code == CONTACTS_ERROR_NONE)
    {
        return true;
    }
    else
    {
        const char *error_message = NULL;
        switch(err_code)
        {
        case CONTACTS_ERROR_OUT_OF_MEMORY:
            error_message = "Out of memory";
            break;
        case CONTACTS_ERROR_INVALID_PARAMETER:
            error_message = "Invalid parameter";
            break;
        case CONTACTS_ERROR_FILE_NO_SPACE:
            error_message = "File system is full";
            break;
        case CONTACTS_ERROR_NO_DATA:
            error_message = "Requested data does not exist";
            break;
        case CONTACTS_ERROR_PERMISSION_DENIED:
            error_message = "Permission denied";
            break;
        case CONTACTS_ERROR_DB:
            error_message = "Unknown DB error, make sure that connection was established";
            break;
        case CONTACTS_ERROR_IPC_NOT_AVALIABLE:
            error_message = "IPC server is not available";
            break;
        case CONTACTS_ERROR_IPC:
            error_message = "Unknown IPC error";
            break;
        case CONTACTS_ERROR_SYSTEM:
            error_message = "System error";
            break;
        case CONTACTS_ERROR_INTERNAL:
            error_message = "Internal error";
            break;
        default:
            error_message = "Unknown error";
            break;
        }

        ERR("Contacts database error %d: %s", err_code, error_message);
        return false;
    }
#else
    return err_code == CONTACTS_ERROR_NONE;
#endif /* _DEBUG */
}
