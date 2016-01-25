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
