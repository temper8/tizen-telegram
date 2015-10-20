#ifndef TG_UCOL_H_
#define TG_UCOL_H_

#include "tg_common.h"

enum LANGUAGE {
	LANG_ENGLISH,
	LANG_KOREAN,
	LANG_JAPANESS,
	LANG_CHINESS,
	LANG_UNKNOWN
};

extern int ucol_init(void);

extern int ucol_compare(const char *src, const char *dest);
extern int ucol_case_compare(const char *src, const char *dest);

extern int ucol_ncompare(const char *src, const char *dest, int len);
extern int ucol_case_ncompare(const char *src, const char *dest, int len);

extern int ucol_search(const char *haystack, const char *needle);
extern int ucol_case_search(const char *haystack, const char *needle);

extern int ucol_compare_first_letters(const char *src, const char *letters);
extern int ucol_detect_lang(int ch);
extern int ucol_fini(void);
extern const int ucol_current_lang(void);
extern int ucol_is_alpha(const char *name);
extern int ucol_is_jamo(const char *name);
extern int ucol_is_hangul(const char *name);
/* End of a file */


#endif
