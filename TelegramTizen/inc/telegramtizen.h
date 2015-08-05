#ifndef __telegramtizen_H__
#define __telegramtizen_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "telegramtizen"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.telegramtizen"
#endif

#define EDJ_FILE "edje/telegramtizen.edj"
#define GRP_MAIN "main"



static const char *TELEGRAM_CLIENT_PORT_NAME = "TIZEN_CLIENT_PORT";
static const char *TELEGRAM_SERVER_PORT_NAME = "TIZEN_SERVER_PORT";
static const char *TELEGRAM_SERVER_APP_NAME = "org.tizen.tg-engine-service";

#endif /* __telegramtizen_H__ */
