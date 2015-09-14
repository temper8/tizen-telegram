#include <stdio.h>
#include <stdarg.h>
#include "tg_common.h"

const char *tg_common_to_string(const char *fmt, ...)
{
	va_list vp;
	static char string_buffer[256];
	int ret;

	va_start(vp, fmt);
	ret = vsnprintf(string_buffer, sizeof(string_buffer) - 1, fmt, vp);
	va_end(vp);

	return ret <= 0 ? NULL : string_buffer;
}

/* End of a file */
