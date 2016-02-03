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

#include "service_client.h"
#include <stdlib.h>
#include <stdbool.h>
#include <message_port.h>

struct _service_client {
	int local_port_id;
	char *remote_port_name;
	char *remote_app_name;
	service_client_callback_func cb_func;
	void *cb_data;
};

static int _service_client_convert_msg_port_result(const int err);
static void _on_message_received_cb(int port_id,
		const char *rem_app_name,
		const char *rem_port_name,
		bool trusted_message,
		bundle *rec_msg,
		void *user_data);

service_client *service_client_create()
{
	service_client *const service = calloc(1 , sizeof(service_client));
	return service;
}

void service_client_destroy(service_client *service_cl)
{
	if (service_cl) {
		message_port_unregister_local_port(service_cl->local_port_id);
		free(service_cl->remote_port_name);
		free(service_cl->remote_app_name);
		free(service_cl);
		service_cl = NULL;
	}
}

int service_client_register_port(service_client *service_cl, const char *const port_name)
{
	int result = SVC_RES_FAIL;

	RETVM_IF(!service_cl, result, "service client is NULL");
	RETVM_IF(!port_name, result, "Message port name is NULL");

	int temp_id = message_port_register_local_port(port_name, _on_message_received_cb, service_cl);
	if (temp_id < 0) {
		_service_client_convert_msg_port_result(temp_id);
		ERR("Failed to register local message port");
		service_cl->local_port_id = 0;
		return result;
	}

	DBG("Message port %s registered with id: %d", port_name, temp_id);
	service_cl->local_port_id = temp_id;

	return SVC_RES_OK;
}

int service_client_send_message(service_client *service_cl, bundle *const msg)
{
	int result = SVC_RES_FAIL;

	RETVM_IF(!service_cl, result , "service client is NULL");
	RETVM_IF(!(service_cl->local_port_id), result, "Message port is not registered");
	RETVM_IF(!(service_cl->remote_app_name), result, "Remote application name is not registered");
	RETVM_IF(!(service_cl->remote_port_name), result, "Remote message port is not registered");

	result = _service_client_convert_msg_port_result(message_port_send_message_with_local_port(
				service_cl->remote_app_name,
				service_cl->remote_port_name,
				msg,
				service_cl->local_port_id));

	RETVM_IF(result != SVC_RES_OK, result, "Failed to send bidirectional message to: %s:%s",
			service_cl->remote_app_name,
			service_cl->remote_port_name);

	DBG("Message successfully send to: %s:%s", service_cl->remote_app_name, service_cl->remote_port_name);
	return result;
}

int service_client_register_msg_receive_callback(service_client *service_cl,
		service_client_callback_func callback_func,
		void *data)
{
	RETVM_IF(!service_cl, SVC_RES_FAIL, "service client is NULL");

	service_cl->cb_func = callback_func;
	service_cl->cb_data = data;

	return SVC_RES_OK;
}

int _service_client_set_remote_data(service_client *service_cl,
		const char *rem_app_name,
		const char *rem_port_name)
{
	RETVM_IF(!service_cl, SVC_RES_FAIL, "service pointer is NULL");

	char *temp_rem_app_name = NULL;
	char *temp_rem_port_name = NULL;

	if (!service_cl->remote_app_name && rem_app_name) {
		temp_rem_app_name = strdup(rem_app_name);
		RETVM_IF(!temp_rem_app_name, SVC_RES_FAIL,
				"Failed to set remote application name. Strdup failed");
	}

	if (!service_cl->remote_port_name && rem_port_name) {
		temp_rem_port_name = strdup(rem_port_name);
		if (!temp_rem_port_name) {
			ERR("Failed to set remote port name. Strdup failed");
			free(temp_rem_app_name);
			return SVC_RES_FAIL;
		}
	}

	if (temp_rem_app_name) {
		service_cl->remote_app_name = temp_rem_app_name;
	}

	if (temp_rem_port_name) {
		service_cl->remote_port_name = temp_rem_port_name;
	}

	return SVC_RES_OK;
}

static int _service_client_convert_msg_port_result(const int err)
{
	int result = SVC_RES_FAIL;

	switch (err) {
	case MESSAGE_PORT_ERROR_NONE:
		result = SVC_RES_OK;
		break;
	case MESSAGE_PORT_ERROR_IO_ERROR:
		ERR("MessagePort error: i/o error");
		break;
	case MESSAGE_PORT_ERROR_OUT_OF_MEMORY:
		ERR("MessagePort error: out of memory");
		break;
	case MESSAGE_PORT_ERROR_INVALID_PARAMETER:
		ERR("MessagePort error: invalid parameter");
		break;
	case MESSAGE_PORT_ERROR_PORT_NOT_FOUND:
		ERR("MessagePort error: message port not found");
		break;
	case MESSAGE_PORT_ERROR_CERTIFICATE_NOT_MATCH:
		ERR("MessagePort error: certificate not match");
		break;
	case MESSAGE_PORT_ERROR_MAX_EXCEEDED:
		ERR("MessagePort error: max exceeded");
		break;
	default:
		ERR("MessagePort error: unknown error");
		break;
	}
	return result;
}

static void _on_message_received_cb(int port_id,
		const char *rem_app_name,
		const char *rem_port_name,
		bool trusted_message,
		bundle *rec_msg,
		void *user_data)
{
	DBG("Received message from port %d", port_id);
	//RETM_IF(!user_data, "user_data is NULL");
	service_client *service_cl = user_data;
	int res = _service_client_set_remote_data(service_cl, rem_app_name, rem_port_name);
	//RETM_IF(res != SVC_RES_OK, "Failed to set remote data to message port");

	if (service_cl->cb_func) {
		res = service_cl->cb_func(service_cl->cb_data, rec_msg);
		//RETM_IF(res != SVC_RES_OK, "Message port callback function failed");
	} else {
		//DBG("Message port callback function not set");
	}
}
