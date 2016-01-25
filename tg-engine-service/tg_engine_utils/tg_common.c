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

#include "tg_common.h"
#include <fts.h>

void tg_notification_create(tg_engine_data_s* tg_data, char * icon_path, const char *title, char *content, char *sound_path, char *app_id)
{
	int err = NOTIFICATION_ERROR_NONE;
	if (tg_data && tg_data->s_notififcation) {
		//err = notification_delete(tg_data->s_notififcation);
		err = notification_delete_all(NOTIFICATION_TYPE_NOTI);
		tg_data->s_notififcation = NULL;
	}

	bundle *b = NULL;
	notification_error_e ret = NOTIFICATION_ERROR_NONE;
	tg_data->s_notififcation = notification_create(NOTIFICATION_TYPE_NOTI);
	ret = notification_set_property(tg_data->s_notififcation, NOTIFICATION_PROP_DISABLE_TICKERNOTI);
	ret = notification_set_layout(tg_data->s_notififcation, NOTIFICATION_LY_NOTI_EVENT_SINGLE);

	if (icon_path) {
		ret = notification_set_image(tg_data->s_notififcation, NOTIFICATION_IMAGE_TYPE_ICON, icon_path);
	}
	if (title) {
		ret = notification_set_text(tg_data->s_notififcation, NOTIFICATION_TEXT_TYPE_TITLE, title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	}
	if (content) {
		ret = notification_set_text(tg_data->s_notififcation, NOTIFICATION_TEXT_TYPE_CONTENT, content, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	}

	if (sound_path) {
		ret = notification_set_sound(tg_data->s_notififcation, NOTIFICATION_SOUND_TYPE_USER_DATA, sound_path);
	} else {
		ret = notification_set_sound(tg_data->s_notififcation, NOTIFICATION_SOUND_TYPE_DEFAULT, NULL);
	}
	ret = notification_set_vibration(tg_data->s_notififcation, NOTIFICATION_VIBRATION_TYPE_DEFAULT, NULL);
	if (ret != NOTIFICATION_ERROR_NONE) {
		//failed
	}
	app_control_h service = NULL;
	app_control_create(&service);
	app_control_set_app_id(service, app_id);
	app_control_set_operation(service, APP_CONTROL_OPERATION_DEFAULT);

	ret  = notification_set_launch_option(tg_data->s_notififcation, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, service);
	if (ret != NOTIFICATION_ERROR_NONE) {
		//failed
	}
	notification_post(tg_data->s_notififcation);
	app_control_destroy(service);
	bundle_free(b);
	ret = notification_free(tg_data->s_notififcation);
	if (ret != NOTIFICATION_ERROR_NONE) {
	}
	return;
}

char *replace(const char *s, char ch, const char *repl)
{
	int count = 0;
	const char *t;

	for (t = s; *t; t++) {
		count += (*t == ch);
	}

	size_t rlen = strlen(repl);
	char *res = malloc(strlen(s) + (rlen - 1) * count + 1);
	char *ptr = res;

	for (t = s; *t; t++) {
		if (*t == ch) {
			memcpy(ptr, repl, rlen);
			ptr += rlen;
		} else {
			*ptr++ = *t;
		}
	}

	*ptr = 0;
	return res;
}

char *get_table_name_from_number(const int id)
{
	char *msg_table;

	msg_table = (char *)malloc(32);
	if (!msg_table) {
		return NULL;
	}

	snprintf(msg_table, 32, "tg_%d_msg", id);

	return msg_table;
}

char *ui_utils_get_resource(const char *res_name)
{
	static char res_path[PATH_MAX] = {'\0'};
	char *path;

	path = app_get_resource_path();
	if (!path) {
		return NULL;
	}

	snprintf(res_path, PATH_MAX, "%s%s", path, res_name);
	free(path);

	return res_path;
}

int recursive_dir_delete(const char *dir)
{
    int ret = 0;
    FTS *ftsp = NULL;
    FTSENT *curr;

    // Cast needed (in C) because fts_open() takes a "char * const *", instead
    // of a "const char * const *", which is only allowed in C++. fts_open()
    // does not modify the argument.
    char *files[] = { (char *) dir, NULL };

    // FTS_NOCHDIR  - Avoid changing cwd, which could cause unexpected behavior
    //                in multithreaded programs
    // FTS_PHYSICAL - Don't follow symlinks. Prevents deletion of files outside
    //                of the specified directory
    // FTS_XDEV     - Don't cross filesystem boundaries
    ftsp = fts_open(files, FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, NULL);
    if (!ftsp) {
        fprintf(stderr, "%s: fts_open failed: %s\n", dir, strerror(errno));
        ret = -1;
        goto finish;
    }

    while ((curr = fts_read(ftsp))) {
        switch (curr->fts_info) {
        case FTS_NS:
        case FTS_DNR:
        case FTS_ERR:
            fprintf(stderr, "%s: fts_read error: %s\n",
                    curr->fts_accpath, strerror(curr->fts_errno));
            break;

        case FTS_DC:
        case FTS_DOT:
        case FTS_NSOK:
            // Not reached unless FTS_LOGICAL, FTS_SEEDOT, or FTS_NOSTAT were
            // passed to fts_open()
            break;

        case FTS_D:
            // Do nothing. Need depth-first search, so directories are deleted
            // in FTS_DP
            break;

        case FTS_DP:
        case FTS_F:
        case FTS_SL:
        case FTS_SLNONE:
        case FTS_DEFAULT:
            if (remove(curr->fts_accpath) < 0) {
                fprintf(stderr, "%s: Failed to remove: %s\n",
                        curr->fts_path, strerror(errno));
                ret = -1;
            }
            break;
        }
    }

finish:
    if (ftsp) {
        fts_close(ftsp);
    }

    return ret;
}
