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
#define LOG_TAG "telegram_tizen"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.telegram_tizen"
#endif

#define EDJ_FILE "edje/telegramtizen.edj"
#define GRP_MAIN "main"



static const char *TELEGRAM_CLIENT_PORT_NAME = "TIZEN_CLIENT_PORT";
static const char *TELEGRAM_SERVER_PORT_NAME = "TIZEN_SERVER_PORT";
static const char *TELEGRAM_SERVER_APP_NAME = "org.tizen.tg-engine-service";

#endif /* __telegramtizen_H__ */
