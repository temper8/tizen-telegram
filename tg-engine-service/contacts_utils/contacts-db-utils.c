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
		switch(err_code) {
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
