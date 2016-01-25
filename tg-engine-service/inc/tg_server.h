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

#ifndef TG_SERVER_H_
#define TG_SERVER_H_

#include <bundle.h>

typedef struct _tg_server tg_server;

/**
 * @brief Proxy client related message receive callback definition
 */
typedef int (*tg_server_callback_func)(void *data, bundle *const msg);

/**
 * @brief Create proxy client instance
 * @return Proxy client instance on success, otherwise NULL
 */
tg_server *tg_server_create();

/**
 * @brief Destroy proxy client instance
 * @param[in]   proxy_cl    Proxy client instance
 */
void tg_server_destroy(tg_server *proxy_cl);

/**
 * @brief Register port for proxy client to receive/send messages
 * @param[in]   proxy_cl    Proxy client instance
 * @param[in]   port_name   Port name to set
 * @return Error code.  SVC_RES_OK if success.
 *                      SVC_RES_FAIL if fails
 */
int tg_server_register_port(tg_server *proxy_cl, const char *port_name);

/**
 * @brief Register callback function on proxy client message receive
 * @param[in]   proxy_cl        Proxy client instance
 * @param[in]   callback_func   Callback function
 * @param[in]   data            Data set to callback function
 * @return Error code.  SVC_RES_OK if success.
 *                      SVC_RES_FAIL if fails
 */
int tg_server_register_msg_receive_callback (tg_server *proxy_cl,
        tg_server_callback_func callback_func,
        void *data);

/**
 * @brief Send message by registered port
 * @param[in]   proxy_cl    Proxy client instance
 * @param[in]   msg         Message to send
 * @return Error code.  SVC_RES_OK if success.
 *                      SVC_RES_FAIL if fails
 */
int tg_server_send_message(tg_server *proxy_cl, bundle *const msg);

int _tg_server_set_remote_data(tg_server *proxy_cl, const char *rem_app_name, const char *rem_port_name);


struct _tg_server
{
    int local_port_id;
    char *remote_port_name;
    char *remote_app_name;
    tg_server_callback_func cb_func;
    void *cb_data;
};

typedef enum
{
    SVC_RES_OK = 0,
    SVC_RES_FAIL = -1,
} svc_result;

typedef enum
{
    REQ_OPER_NONE = 0,
    REQ_OPER_START_TIMER,
    REQ_OPER_STOP_TIMER,
    REQ_OPER_SEND_TIMER_EXP_MSG,
    REQ_OPER_EXIT_APP
} req_operation;


#endif /* TG_SERVER_H_ */
