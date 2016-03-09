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

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <dlog.h>
#include <tg-engine-service.h>

#define MODULE_INFO (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define _IS_USE_LOGGING
#ifdef _IS_USE_LOGGING
#define INF(fmt, arg...) dlog_print(DLOG_INFO, \
        LOG_TAG, "%s: %s(%d) > " fmt, MODULE_INFO, \
        __func__, __LINE__, ##arg)

#define LOGI(fmt, arg...) dlog_print(DLOG_INFO, \
        LOG_TAG, "%s: %s(%d) > " fmt, MODULE_INFO, \
        __func__, __LINE__, ##arg)

#define DBG(fmt, arg...) dlog_print(DLOG_DEBUG, \
        LOG_TAG, "%s: %s(%d) > " fmt, MODULE_INFO, \
        __func__, __LINE__, ##arg)

#define LOGD(fmt, arg...) dlog_print(DLOG_DEBUG, \
        LOG_TAG, "%s: %s(%d) > " fmt, MODULE_INFO, \
        __func__, __LINE__, ##arg)

#define WARN(fmt, arg...) dlog_print(DLOG_WARN, \
        LOG_TAG, "%s: %s(%d) > " fmt, MODULE_INFO, \
        __func__, __LINE__, ##arg)

#define ERR(fmt, arg...) dlog_print(DLOG_ERROR, \
        LOG_TAG, "%s: %s(%d) > " fmt, MODULE_INFO, \
        __func__, __LINE__, ##arg)

#define LOGE(fmt, arg...) dlog_print(DLOG_ERROR, \
        LOG_TAG, "%s: %s(%d) > " fmt, MODULE_INFO, \
        __func__, __LINE__, ##arg)

#else

#define INF(fmt, arg...)
#define LOGI(fmt, arg...)
#define DBG(fmt, arg...)
#define LOGD(fmt, arg...)
#define WARN(fmt, arg...)
#define ERR(fmt, arg...)
#define LOGE(fmt, arg...)
#endif


#define RETM_IF(expr, fmt, arg...) \
{ \
    if (expr) { \
        ERR(fmt, ##arg); \
        return; \
    } \
}

#define RETVM_IF(expr, val, fmt, arg...) \
{ \
    if (expr) { \
        ERR(fmt, ##arg); \
        return (val); \
    } \
}

#define retv_if(expr, val) do { \
	if (expr) { \
		ERR("(%s) -> %s() return", #expr, __FUNCTION__); \
		return (val); \
	} \
} while (0)

#define ret_if(expr) do { \
	if (expr) { \
		ERR("(%s) -> %s() return", #expr, __FUNCTION__); \
		return; \
	} \
} while (0)

#define goto_if(expr, val) do { \
	if (expr) { \
		ERR("(%s) -> goto", #expr); \
		goto val; \
	} \
} while (0)

#define break_if(expr) { \
	if (expr) { \
		ERR("(%s) -> break", #expr); \
		break; \
	} \
}

#define continue_if(expr) { \
	if (expr) { \
		ERR("(%s) -> continue", #expr); \
		continue; \
	} \
}



#endif /* __LOGGER_H__ */
