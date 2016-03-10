#include <dlog.h>
#include <stdarg.h>
#include <tg-engine-service.h>

#if defined(assert)
#undef assert
#endif
#define assert(a) do { \
	if (!(a)) { \
		dlog_print(DLOG_VERBOSE, LOG_TAG, "[%s:%d] assert(%s)", __FILE__, __LINE__, #a); \
	} \
} while (0)


