/*
 * service_client.h
 *
 *  Created on: Jun 25, 2015
 *      Author: sandeep
 */

#ifndef SERVICE_CLIENT_H_
#define SERVICE_CLIENT_H_

#include <bundle.h>
#include "logger.h"

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

typedef struct _service_client service_client;

/**
 * @brief service client related message receive callback definition
 */
typedef int (*service_client_callback_func)(void *data, bundle *const msg);

/**
 * @brief Create service client instance
 * @return service client instance on success, otherwise NULL
 */
service_client *service_client_create();

/**
 * @brief Destroy service client instance
 * @param[in]   service_cl    service client instance
 */
void service_client_destroy(service_client *service_cl);

/**
 * @brief Register port for service client to receive/send messages
 * @param[in]   service_cl    service client instance
 * @param[in]   port_name   Port name to set
 * @return Error code.  SVC_RES_OK if success.
 *                      SVC_RES_FAIL if fails
 */
int service_client_register_port(service_client *service_cl, const char *port_name);

/**
 * @brief Register callback function on service client message receive
 * @param[in]   service_cl        service client instance
 * @param[in]   callback_func   Callback function
 * @param[in]   data            Data set to callback function
 * @return Error code.  SVC_RES_OK if success.
 *                      SVC_RES_FAIL if fails
 */
int service_client_register_msg_receive_callback (service_client *service_cl,
        service_client_callback_func callback_func,
        void *data);

/**
 * @brief Send message by registered port
 * @param[in]   service_cl    service client instance
 * @param[in]   msg         Message to send
 * @return Error code.  SVC_RES_OK if success.
 *                      SVC_RES_FAIL if fails
 */
int service_client_send_message(service_client *service_cl, bundle *const msg);

int _service_client_set_remote_data(service_client *service_cl,
        const char *rem_app_name,
        const char *rem_port_name);


#endif /* SERVICE_CLIENT_H_ */
