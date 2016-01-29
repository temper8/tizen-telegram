#include <dlog.h>
#include <stdarg.h>

#if defined(assert)
#undef assert
#endif
#define assert(a) do { \
	int ret; \
	ret = (a); \
	if (!ret) { \
		dlog_print(DLOG_DEBUG, "tg-engine-service", "[%s:%d] assert(%s)", __FILE__, __LINE__, #a); \
	} \
} while (0)


