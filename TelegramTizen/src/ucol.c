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

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include <ctype.h>

#include <Eina.h>
#include <dlog.h>
#include <Evas.h>

#include <utils_i18n.h>

#include "ucol.h"

static struct info {
	i18n_ucollator_h coll;
	enum LANGUAGE lang;
	char *env_lang;
} s_info = {
	.coll = NULL,
	.lang = LANG_ENGLISH,
	.env_lang = NULL,
};

 int ucol_init(void)
{
	const char *env;
	int status = I18N_ERROR_NONE;

	env = getenv("LANG");
	if (env) {
		if (!strcasecmp(env, "en_US.utf-8")) {
			s_info.lang = LANG_ENGLISH;
			s_info.env_lang = "en_US.utf-8";
		} else if (!strcasecmp(env, "ja_JP.utf-8")) {
			s_info.lang = LANG_JAPANESS;
			s_info.env_lang = "ja_JP.utf-8";
		} else if (!strcasecmp(env, "ko_KR.utf-8")) {
			s_info.lang = LANG_KOREAN;
			s_info.env_lang = "ko_KR.utf-8";
		}
	}

	status = i18n_ucollator_create(NULL, &s_info.coll);
	if (I18N_ERROR_NONE != status) {
		LOGE("Failed to open ucol (%d)\n", status);
		i18n_ucollator_destroy(s_info.coll);
		s_info.coll = NULL;
	}

	status = I18N_ERROR_NONE;
	status = i18n_ucollator_set_attribute(s_info.coll, I18N_UCOLLATOR_NORMALIZATION_MODE, I18N_UCOLLATOR_ON);
	if (I18N_ERROR_NONE != status) {
		LOGE("Failed to open ucol (%d)\n", status);
		i18n_ucollator_destroy(s_info.coll);
		s_info.coll = NULL;
	}

	i18n_ucollator_set_strength(s_info.coll, I18N_UCOLLATOR_PRIMARY);
	return 0;
}

static inline i18n_uchar *to_UTF16(const char *src, int *out_len)
{
	i18n_uchar *res;
	int status = I18N_ERROR_NONE;
	int len;

	i18n_ustring_from_UTF8(NULL, 0, &len, src, -1, &status);

	res = malloc((len + 1) * sizeof(*res));
	if (!res) {
		LOGE("malloc: %d\n", errno);
		return NULL;
	}

	status = I18N_ERROR_NONE;
	i18n_ustring_from_UTF8(res, len + 1, &len, src, -1, &status);
	if (I18N_ERROR_NONE != status) {
		LOGE("Unable to convert(%s) to UTF16(%d)\n", src, status);
		free(res);
		return NULL;
	}
	res[len] = (i18n_uchar)0;

	if (out_len) {
		*out_len = len;
	}
	return res;
}

static inline char *to_UTF8(i18n_uchar *src, int *out_len)
{
	char *res;
	int status = I18N_ERROR_NONE;
	int len;

	i18n_ustring_to_UTF8(NULL, 0, &len, src, -1, &status);

	res = malloc((len + 1) * sizeof(*res));
	if (!res) {
		LOGE("malloc: %d\n", errno);
		return NULL;
	}

	status = I18N_ERROR_NONE;
	i18n_ustring_to_UTF8(res, len + 1, &len, src, -1, &status);
	if (I18N_ERROR_NONE != status) {
		LOGE("Unable to convert to UTF8(%d)\n", status);
		free(res);
		return NULL;
	}
	res[len] = '\0';

	if (out_len) {
		*out_len = len;
	}

	return res;
}

static inline int hangul_to_jamo(const char *index)
{
	Eina_Unicode *ret;
	Eina_Unicode tmp = 0;
	int base = 0xAC00;
	int last = 0xD79F;
	int a;
	static int table[] = {
		0x00003131, 0x00003131,
		0x00003134,
		0x00003137, 0x00003137,
		0x00003139,
		0x00003141,
		0x00003142, 0x00003142,
		0x00003145, 0x00003145,
		0x00003147,
		0x00003148, 0x00003148,
		0x0000314a,
		0x0000314b,
		0x0000314c,
		0x0000314d,
		0x0000314e,
		/*
		   0xb184e3, 0xb284e3, 0xb484e3, 0xb784e3, 0xb884e3, 0xb984e3,
		   0x8185e3, 0x8285e3, 0x8385e3, 0x8585e3, 0x8685e3, 0x8785e3,
		   0x8885e3, 0x8985e3, 0x8a85e3, 0x8b85e3, 0x8c85e3, 0x8d85e3,
		   0x8e85e3,
		 */
	};

	ret = eina_unicode_utf8_to_unicode(index, &a);
	if (ret) {
		tmp = *ret;
		free(ret);
	}

	if (tmp < base || tmp > last) {
		return tmp;
	}

	tmp = tmp - base;
	a = tmp / (21 * 28);
	return table[a];
}

#define __isalpha(a)	(((a) >= 'a' && (a) <= 'z') || ((a) >= 'A' && (a) <= 'Z'))
#define __tolower(a)	(((a) >= 'A' && (a) <= 'Z') ? (a) + 32 : (a))

 int ucol_compare_first_letters(const char *name, const char *letters)
{
	if (ucol_is_hangul(letters)) {
		int jamo_name;
		int jamo_letters = 0;
		Eina_Unicode *ucs;

		jamo_name = hangul_to_jamo(name);

		ucs = eina_unicode_utf8_to_unicode(letters, &jamo_letters);
		if (ucs) {
			jamo_letters = (int)*ucs;
			free(ucs);
		}

		if (__isalpha(jamo_letters)) {
			if (!__isalpha(jamo_name)) {
				//LOGD("%d - %d (%s, %s)\n", jamo_name, jamo_letters, name, letters);
				return -1;
			}

			return __tolower(jamo_name) - __tolower(jamo_letters);
		}

		return jamo_name - jamo_letters;
	}

	return ucol_ncompare(name, letters, strlen(letters));
}

 int ucol_is_jamo(const char *name)
{
	i18n_uchar *uni;
	int name_len = 0;
	int lang = 0;

	uni = to_UTF16(name, &name_len);
	if (!uni) {
		LOGE("DEST: Failed to convert to UTF16\n");
		return 0;
	}

	i18n_uchar_get_ublock_code(*uni, &lang);
	free(uni);
	switch (lang) {
	case I18N_UCHAR_UBLOCK_HANGUL_JAMO:
	case I18N_UCHAR_UBLOCK_HANGUL_COMPATIBILITY_JAMO:
	case I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_A:
	case I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_B:
		return 1;
	case I18N_UCHAR_UBLOCK_HANGUL_SYLLABLES:
	default:
		break;
	}

	return 0;
}

int ucol_is_hangul(const char *name)
{
 	i18n_uchar *uni;
 	int name_len = 0;
 	int lang = 0;

 	uni = to_UTF16(name, &name_len);
 	if (!uni) {
 		LOGE("DEST: Failed to convert to UTF16\n");
 		return 0;
 	}

 	i18n_uchar_get_ublock_code(*uni, &lang);
 	free(uni);
 	switch (lang) {
 	case I18N_UCHAR_UBLOCK_HANGUL_JAMO:
 	case I18N_UCHAR_UBLOCK_HANGUL_COMPATIBILITY_JAMO:
 	case I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_A:
 	case I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_B:
 	case I18N_UCHAR_UBLOCK_HANGUL_SYLLABLES:
 		return 1;
 	default:
 		break;
 	}

 	return 0;
 }


 int ucol_is_alpha(const char *name)
{
	Eina_Unicode *ucs;
	int len;
	int letter = 0;

	ucs = eina_unicode_utf8_to_unicode(name, &len);
	if (ucs) {
		letter = (int)*ucs;
		free(ucs);
	}

	return __isalpha(letter);
}

 int ucol_detect_lang(int ch)
{
	//	int result;
	int lang;
	//	int status;
	//	int size;

	/*
	   u_strToUpper((UChar *)&ch, 1, (UChar *)&result, -1, NULL, &status);
	   if (U_FAILURE(status)) {
	   LOGE("u_strToLower: %s\n", u_errorName(status));
	   return LANG_UNKNOWN;
	   }

	   size = unorm_normalize((UChar *)&result, 1, UNORM_NFD, 0, (UChar *)&result, 1, &status);
	   if (U_FAILURE(status)) {
	   LOGE("unorm_normalize: %s\n", u_errorName(status));
	   return LANG_UNKNOWN;
	   }
	 */

	i18n_uchar_get_ublock_code(ch, &lang);
	switch (lang) {
	case I18N_UCHAR_UBLOCK_HIRAGANA:
	case I18N_UCHAR_UBLOCK_KATAKANA:
	case I18N_UCHAR_UBLOCK_KATAKANA_PHONETIC_EXTENSIONS:
	case I18N_UCHAR_UBLOCK_JAVANESE:
	case I18N_UCHAR_UBLOCK_HALFWIDTH_AND_FULLWIDTH_FORMS:
		lang = LANG_JAPANESS;
		break;
	case I18N_UCHAR_UBLOCK_HANGUL_JAMO:
	case I18N_UCHAR_UBLOCK_HANGUL_COMPATIBILITY_JAMO:
	case I18N_UCHAR_UBLOCK_HANGUL_SYLLABLES:
	case I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_A:
	case I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_B:
		lang = LANG_KOREAN;
		break;
	case I18N_UCHAR_UBLOCK_BASIC_LATIN:                                                        // = 1, /*[0000]*/
	case I18N_UCHAR_UBLOCK_LATIN_1_SUPPLEMENT:                                 // =2, /*[0080]*/
	case I18N_UCHAR_UBLOCK_LATIN_EXTENDED_A:                                           // =3, /*[0100]*/
	case I18N_UCHAR_UBLOCK_LATIN_EXTENDED_B:                                           // =4, /*[0180]*/
	case I18N_UCHAR_UBLOCK_LATIN_EXTENDED_ADDITIONAL:                  // =38, /*[1E00]*/
		lang = LANG_ENGLISH;
		break;
	case I18N_UCHAR_UBLOCK_CJK_RADICALS_SUPPLEMENT:                     //=58, /*[2E80]*/
	case I18N_UCHAR_UBLOCK_CJK_SYMBOLS_AND_PUNCTUATION:                 //=61, /*[3000]*/
	case I18N_UCHAR_UBLOCK_ENCLOSED_CJK_LETTERS_AND_MONTHS:  //=68, /*[3200]*/
	case I18N_UCHAR_UBLOCK_CJK_STROKES:                                                         // =130, /*[31C0]*/
	case I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY:                                           // =69, /*[3300]*/
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A: //=70, /*[3400]*/
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS:                              //=71, /*[4E00]*/
	case I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_IDEOGRAPHS:                //=79, /*[F900]*/
	case I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_FORMS:                             //=83, /*[FE30]*/
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B:       // =94, /*[20000]*/
	case I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT:         // =95, /*[2F800]*/
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C:         // =197, /*[2A700]*/
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D:         // =209, /*[2B740]*/
		lang = LANG_CHINESS;
		break;
	default:
		LOGD("Detected unknown: %d\n", lang);
		lang = LANG_UNKNOWN;
		break;
	}

	return lang;
}

static char *ucol_toupper(const char *haystack)
{
	i18n_uchar *_haystack;
	i18n_uchar *u_haystack;
	int haystack_len;
	int status = I18N_ERROR_NONE;
	int ret;
	char *utf8_ret;

	u_haystack = to_UTF16(haystack, &haystack_len);
	if (!u_haystack) {
		// Error will be printed by to_UTF16
		return NULL;
	}

	haystack_len = i18n_ustring_to_upper(NULL, 0, u_haystack, -1, NULL, &status);

	_haystack = malloc(sizeof(*_haystack) * (haystack_len + 1));
	if (!_haystack) {
		LOGE("malloc: %d\n", errno);
		free(u_haystack);
		return NULL;
	}

	//ret = u_strFoldCase((UChar *)_haystack, haystack_len, (UChar *)haystack, -1, U_FOLD_CASE_DEFAULT, &status);
	status = I18N_ERROR_NONE;
	ret = i18n_ustring_to_upper(_haystack, haystack_len + 1, u_haystack, -1, NULL, &status);
	free(u_haystack);
	if (I18N_ERROR_NONE != status) {
		LOGE("upper: %d\n", status);
		free(_haystack);
		return NULL;
	}

	utf8_ret = to_UTF8(_haystack, &ret);
	free(_haystack);

	return utf8_ret;
}

 int ucol_case_ncompare(const char *src, const char *dest, int len)
{
	char *_src;
	char *_dest;
	int ret;

	if (!src || !dest || len <= 0) {
		return -EINVAL;
	}

	if (!s_info.coll) {
		LOGE("Fallback to strncasecmp\n");
		return strncasecmp(src, dest, len);
	}

	_src = ucol_toupper(src);
	if (!_src) {
		return -EFAULT;
	}

	_dest = ucol_toupper(dest);
	if (!_dest) {
		free(_src);
		return -EFAULT;
	}

	ret = ucol_ncompare(_src, _dest, len);

	free(_src);
	free(_dest);
	return ret;
}

 int ucol_ncompare(const char *src, const char *dest, int len)
{
	i18n_uchar *src_uni;
	i18n_uchar *dest_uni;
	i18n_ucollator_result_e res;
	int32_t dest_len;
	int32_t src_len;
	char *tmp;

	if (!src || !dest || len <= 0) {
		return -EINVAL;
	}

	if (!s_info.coll) {
		LOGE("Fallback to strcmp\n");
		return strncmp(src, dest, len);
	}

	tmp = malloc(len + 1);
	if (!tmp) {
		LOGE("malloc: %d\n", errno);
		return strncmp(src, dest, len);
	}
	strncpy(tmp, dest, len);
	tmp[len] = '\0';

	/* To get the ucs16 len */
	src_uni = to_UTF16(tmp, &len);
	free(tmp);
	if (!src_uni) {
		LOGE("Failed get utf16\n");
		return strncmp(src, dest, len);
	}
	free(src_uni);

	src_uni = to_UTF16(src, &src_len);
	if (!src_uni) {
		LOGE("SRC: Failed to convert to UTF16\n");
		return strncmp(src, dest, len);
	}

	dest_uni = to_UTF16(dest, &dest_len);
	if (!dest_uni) {
		LOGE("DEST: Failed to convert to UTF16\n");
		free(src_uni);
		return strncmp(src, dest, len);
	}

	switch (s_info.lang) {
	case LANG_JAPANESS:
		if (__isalpha(*src_uni) && !__isalpha(*dest_uni)) {
			res = I18N_UCOLLATOR_GREATER;
		} else if (!__isalpha(*src_uni) && __isalpha(*dest_uni)) {
			res = I18N_UCOLLATOR_LESS;
		} else {
			int src_lang;
			int dest_lang;

			src_lang = ucol_detect_lang(*src_uni);
			dest_lang = ucol_detect_lang(*dest_uni);

			if (src_lang == LANG_JAPANESS && dest_lang != LANG_JAPANESS) {
				res = I18N_UCOLLATOR_LESS;
			} else if (src_lang != LANG_JAPANESS && dest_lang == LANG_JAPANESS) {
				res = I18N_UCOLLATOR_GREATER;
			} else {
				i18n_ucollator_str_collator(s_info.coll, src_uni, len, dest_uni, len, &res);
			}
		}
		break;
	case LANG_KOREAN:
		if (__isalpha(*src_uni) && !__isalpha(*dest_uni)) {
			res = I18N_UCOLLATOR_GREATER;
		} else if (!__isalpha(*src_uni) && __isalpha(*dest_uni)) {
			res = I18N_UCOLLATOR_LESS;
		} else {
			int src_lang;
			int dest_lang;

			src_lang = ucol_detect_lang(*src_uni);
			dest_lang = ucol_detect_lang(*dest_uni);

			if (src_lang == LANG_KOREAN && dest_lang != LANG_KOREAN) {
				res = I18N_UCOLLATOR_LESS;
			} else if (src_lang != LANG_KOREAN && dest_lang == LANG_KOREAN) {
				res = I18N_UCOLLATOR_GREATER;
			} else {
				i18n_ucollator_str_collator(s_info.coll, src_uni, len, dest_uni, len, &res);
			}
		}
		break;
	case LANG_ENGLISH:
	default:
		/*
		   if (__isalpha(*src_uni) && !__isalpha(*dest_uni)) {
		   res = UCOL_LESS;
		   } else if (!__isalpha(*src_uni) && __isalpha(*dest_uni)) {
		   res = UCOL_GREATER;
		   } else {
		 */
		i18n_ucollator_str_collator(s_info.coll, src_uni, len, dest_uni, len, &res);
		/*
		   }
		 */
	}

	free(src_uni);
	free(dest_uni);

	switch (res) {
	case I18N_UCOLLATOR_LESS:
		return -1;

	case I18N_UCOLLATOR_EQUAL:
		return 0;

	case I18N_UCOLLATOR_GREATER:
		return 1;

	default:
		LOGD("%s ? %s\n", src, dest);
		return 0;
	}
}

 int ucol_case_compare(const char *src, const char *dest)
{
	char *_src;
	char *_dest;
	int ret;

	if (!src || !dest) {
		return -EINVAL;
	}

	if (!s_info.coll) {
		LOGE("Fallback to strcasecmp\n");
		return strcasecmp(src, dest);
	}

	_src = ucol_toupper(src);
	if (!_src) {
		return -EFAULT;
	}

	_dest = ucol_toupper(dest);
	if (!_dest) {
		free(_src);
		return -EFAULT;
	}

	ret = ucol_compare(_src, _dest);
	free(_src);
	free(_dest);
	return ret;
}

 int ucol_compare(const char *src, const char *dest)
{
	i18n_uchar *src_uni;
	i18n_uchar *dest_uni;
	i18n_ucollator_result_e res;
	int32_t dest_len;
	int32_t src_len;
	int len;

	if (!src || !dest) {
		return -EINVAL;
	}

	if (!s_info.coll) {
		LOGE("Fallback to strcmp\n");
		return strcmp(src, dest);
	}

	src_uni = to_UTF16(src, &src_len);
	if (!src_uni) {
		LOGE("SRC: Failed to convert to UTF16\n");
		return strcmp(src, dest);
	}

	dest_uni = to_UTF16(dest, &dest_len);
	if (!dest_uni) {
		LOGE("DEST: Failed to convert to UTF16\n");
		free(src_uni);
		return strcmp(src, dest);
	}

	len = src_len > dest_len ? dest_len : src_len;

	switch (s_info.lang) {
	case LANG_JAPANESS:
		if (__isalpha(*src_uni) && !__isalpha(*dest_uni)) {
			res = I18N_UCOLLATOR_GREATER;
		} else if (!__isalpha(*src_uni) && __isalpha(*dest_uni)) {
			res = I18N_UCOLLATOR_LESS;
		} else {
			int src_lang;
			int dest_lang;

			src_lang = ucol_detect_lang(*src_uni);
			dest_lang = ucol_detect_lang(*dest_uni);

			if (src_lang == LANG_JAPANESS && dest_lang != LANG_JAPANESS) {
				res = I18N_UCOLLATOR_LESS;
			} else if (src_lang != LANG_JAPANESS && dest_lang == LANG_JAPANESS) {
				res = I18N_UCOLLATOR_GREATER;
			} else {
				i18n_ucollator_str_collator(s_info.coll, src_uni, len, dest_uni, len, &res);
			}
		}
		break;
	case LANG_KOREAN:
		if (__isalpha(*src_uni) && !__isalpha(*dest_uni)) {
			res = I18N_UCOLLATOR_GREATER;
		} else if (!__isalpha(*src_uni) && __isalpha(*dest_uni)) {
			res = I18N_UCOLLATOR_LESS;
		} else {
			int src_lang;
			int dest_lang;

			src_lang = ucol_detect_lang(*src_uni);
			dest_lang = ucol_detect_lang(*dest_uni);

			if (src_lang == LANG_KOREAN && dest_lang != LANG_KOREAN) {
				res = I18N_UCOLLATOR_LESS;
			} else if (src_lang != LANG_KOREAN && dest_lang == LANG_KOREAN) {
				res = I18N_UCOLLATOR_GREATER;
			} else {
				i18n_ucollator_str_collator(s_info.coll, src_uni, len, dest_uni, len, &res);
			}
		}
		break;
	case LANG_ENGLISH:
	default:
		if (__isalpha(*src_uni) && !__isalpha(*dest_uni)) {
			res = I18N_UCOLLATOR_LESS;
		} else if (!__isalpha(*src_uni) && __isalpha(*dest_uni)) {
			res = I18N_UCOLLATOR_GREATER;
		} else {
			i18n_ucollator_str_collator(s_info.coll, src_uni, len, dest_uni, len, &res);
		}
	}

	free(src_uni);
	free(dest_uni);

	switch (res) {
	case I18N_UCOLLATOR_LESS:
		return -1;

	case I18N_UCOLLATOR_EQUAL:
		if (src_len > dest_len) {
			return 1;
		} else if (src_len == dest_len) {
			return 0;
		}

		return -1;

	case I18N_UCOLLATOR_GREATER:
		return 1;

	default:
		LOGD("%s ? %s\n", src, dest);
		return 0;
	}
}

static int util_get_utf8_len(char ch)
 {
     int idx_len;
     if ((ch & 0x80) == 0x00) {
         idx_len = 1;
     } else if ((ch & 0xE0) == 0xC0) {
         idx_len = 2;
     } else if ((ch & 0xF0) == 0xE0) {
         idx_len = 3;
     } else if ((ch & 0xFC) == 0xF8) {
         idx_len = 4;
     } else if ((ch & 0xFE) == 0xFC) {
         idx_len = 5;
     } else if ((ch & 0xFF) == 0xFE) {
         idx_len = 6;
     } else {
         idx_len = 1;
     }

     return idx_len;
 }


 int ucol_case_search(const char *haystack, const char *needle)
{
	char *_haystack;
	char *_needle;
	const char *ptr;
	int len;
	int needle_len;
	int idx;
	int ret;

	if (!haystack || !needle) {
		return -EINVAL;
	}

	if (!s_info.coll) {
		LOGE("Fallback to strcasestr\n");
		ptr = strcasestr(haystack, needle);
		if (!ptr) {
			return -ENOENT;
		}

		return (int)(ptr - haystack);
	}

	_haystack = ucol_toupper(haystack);
	if (!_haystack) {
		// Error will be printed by ucol_toupper
		return -EFAULT;
	}

	_needle = ucol_toupper(needle);
	if (!_needle) {
		// Error will be printed by ucol_toupper
		free(_haystack);
		return -EFAULT;
	}

	needle_len = strlen(_needle);
	len = strlen(_haystack) - needle_len;
	if (len == 0) {
		ret = ucol_compare(_haystack, _needle);
		free(_needle);
		free(_haystack);
		return ret == 0 ? 0 : -ENOENT;
	} else if (len < 0) {
		free(_haystack);
		free(_needle);
		return -ENOENT;
	}

	for (idx = 0; idx <= len; ) {
		ret = ucol_ncompare(_haystack + idx, _needle, needle_len);
		if (ret == 0) {
			free(_haystack);
			free(_needle);
			return idx;
		}

		idx += util_get_utf8_len(_haystack[idx]);
	}

	free(_haystack);
	free(_needle);
	return -ENOENT;
}

 int ucol_search(const char *haystack, const char *needle)
{
	int ret;
	int len;
	const char *ptr;
	int idx;
	int needle_len;

	if (!haystack || !needle) {
		return -EINVAL;
	}

	if (!s_info.coll) {
		LOGE("Fallback to strstr\n");
		ptr = strstr(haystack, needle);
		if (!ptr) {
			return -ENOENT;
		}

		return (int)(ptr - haystack);
	}

	needle_len = strlen(needle);
	len = strlen(haystack) - needle_len;
	if (len == 0) {
		return ucol_compare(haystack, needle) == 0 ? 0 : -ENOENT;
	} else if (len < 0) {
		return -ENOENT;
	}

	for (idx = 0; idx <= len;) {
		ret = ucol_ncompare(haystack + idx, needle, needle_len);
		if (ret == 0) {
			return idx;
		}

		idx += util_get_utf8_len(haystack[idx]);
	}

	return -ENOENT;
}

 int ucol_fini(void)
{
	if (s_info.coll) {
		i18n_ucollator_destroy(s_info.coll);
		s_info.coll = NULL;
	}
	return 0;
}

 const int ucol_current_lang(void)
{
	return s_info.lang;
}

/* End of a file */
