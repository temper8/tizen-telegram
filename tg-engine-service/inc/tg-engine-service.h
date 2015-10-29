#ifndef __tg_engine_service_H__
#define __tg_engine_service_H__

#include <dlog.h>
#include "tg_common.h"

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "tg-engine-service"
static const char *TELEGRAM_CLIENT_PORT_NAME = "TIZEN_CLIENT_PORT";
static const char *TELEGRAM_SERVER_PORT_NAME = "TIZEN_SERVER_PORT";
static const char *TELEGRAM_CLIENT_APP_NAME = "org.tizen.telegramtizen";

extern Eina_Bool event_idler_cb(void *data);
extern Eina_Bool on_code_request_timer_expired(void *data);

#endif /* __tg-engine-service_H__ */
