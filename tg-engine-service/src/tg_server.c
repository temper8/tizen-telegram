/*
 * tg_server.c
 *
 *  Created on: Jun 25, 2015
 *      Author: sandeep
 */

#include "tg_server.h"
#include "logger.h"
#include <stdlib.h>
#include <stdbool.h>
#include <message_port.h>

static int _tg_server_convert_msg_port_result(const int err);
static void _on_message_received_cb(int port_id, const char *rem_app_name, const char *rem_port_name, bool trusted_message, bundle *rec_msg, void *user_data);

tg_server *tg_server_create()
{
    tg_server *const proxy = calloc(1 , sizeof(tg_server));
    return proxy;
}

void tg_server_destroy(tg_server *proxy_cl)
{
    if (proxy_cl)
    {
        message_port_unregister_local_port(proxy_cl->local_port_id);
        free(proxy_cl->remote_port_name);
        free(proxy_cl->remote_app_name);
        free(proxy_cl);
        proxy_cl = NULL;
    }
}

int tg_server_register_port(tg_server *proxy_cl, const char *const port_name)
{
    int result = SVC_RES_FAIL;

    RETVM_IF(!proxy_cl, result, "Proxy client is NULL");
    RETVM_IF(!port_name, result, "Message port name is NULL");

    int temp_id = message_port_register_local_port(port_name, _on_message_received_cb, proxy_cl);
    if (temp_id < 0)
    {
        _tg_server_convert_msg_port_result(temp_id);
        ERR("Failed to register local message port");
        proxy_cl->local_port_id = 0;
        return result;
    }

    DBG("Message port %s registered with id: %d", port_name, temp_id);
    proxy_cl->local_port_id = temp_id;

    return SVC_RES_OK;
}

int tg_server_send_message(tg_server *proxy_cl, bundle *const msg)
{
    int result = SVC_RES_FAIL;

    RETVM_IF(!proxy_cl, result , "Proxy client is NULL");
    RETVM_IF(!(proxy_cl->local_port_id), result, "Message port is not registered");
    RETVM_IF(!(proxy_cl->remote_app_name), result, "Remote application name is not registered");
    RETVM_IF(!(proxy_cl->remote_port_name), result, "Remote message port is not registered");

    result = _tg_server_convert_msg_port_result(message_port_send_message_with_local_port(
            proxy_cl->remote_app_name,
            proxy_cl->remote_port_name,
            msg,
            proxy_cl->local_port_id));

    RETVM_IF(result != SVC_RES_OK, result, "Failed to send bidirectional message to: %s:%s",
            proxy_cl->remote_app_name,
            proxy_cl->remote_port_name);

    DBG("Message successfully send to: %s:%s", proxy_cl->remote_app_name, proxy_cl->remote_port_name);
    return result;
}

int tg_server_register_msg_receive_callback(tg_server *proxy_cl, tg_server_callback_func callback_func, void *data)
{
    RETVM_IF(!proxy_cl, SVC_RES_FAIL, "Proxy client is NULL");

    proxy_cl->cb_func = callback_func;
    proxy_cl->cb_data = data;

    return SVC_RES_OK;
}

int _tg_server_set_remote_data(tg_server *proxy_cl, const char *rem_app_name, const char *rem_port_name)
{
    RETVM_IF(!proxy_cl, SVC_RES_FAIL, "Proxy pointer is NULL");

    char *temp_rem_app_name = NULL;
    char *temp_rem_port_name = NULL;

    if (!proxy_cl->remote_app_name && rem_app_name)
    {
        temp_rem_app_name = strdup(rem_app_name);
        RETVM_IF(!temp_rem_app_name, SVC_RES_FAIL,
                "Failed to set remote application name. Strdup failed");
    }

    if (!proxy_cl->remote_port_name && rem_port_name)
    {
        temp_rem_port_name = strdup(rem_port_name);
        if (!temp_rem_port_name)
        {
            ERR("Failed to set remote port name. Strdup failed");
            free(temp_rem_app_name);
            return SVC_RES_FAIL;
        }
    }

    if (temp_rem_app_name)
    {
        proxy_cl->remote_app_name = temp_rem_app_name;
    }
    if (temp_rem_port_name)
    {
        proxy_cl->remote_port_name = temp_rem_port_name;
    }

    return SVC_RES_OK;
}

static int _tg_server_convert_msg_port_result(const int err)
{
    int result = SVC_RES_FAIL;

    switch (err)
    {
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

static void _on_message_received_cb(int port_id, const char *rem_app_name, const char *rem_port_name, bool trusted_message, bundle *rec_msg, void *user_data)
{
    DBG("Received message from port %d", port_id);

    RETM_IF(!user_data, "user_data is NULL");

    tg_server *proxy_cl = user_data;

    int res = _tg_server_set_remote_data(proxy_cl, rem_app_name, rem_port_name);
    RETM_IF(res != SVC_RES_OK ,"Failed to set remote data to message port");

    if (proxy_cl->cb_func)
    {
        res = proxy_cl->cb_func(proxy_cl->cb_data, rec_msg);
        RETM_IF(res != SVC_RES_OK ,"Message port callback function failed");
    }
    else
    {
        DBG("Message port callback function not set");
    }
}
