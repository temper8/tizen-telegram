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
#include <badge.h>
#include "logger.h"

static int g_last_unread_msg_cnt;

uint64_t get_time_stamp_in_macro()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}

void tg_notification_create(tg_engine_data_s* tg_data, char * icon_path, const char *title, char *content, char *sound_path, char *app_id)
{
	if (tg_data && tg_data->s_notififcation)
		notification_delete_all(NOTIFICATION_TYPE_NOTI);
	tg_data->s_notififcation = NULL;

	tg_data->s_notififcation = notification_create(NOTIFICATION_TYPE_NOTI);
	notification_set_property(tg_data->s_notififcation, NOTIFICATION_PROP_DISABLE_TICKERNOTI);
	notification_set_layout(tg_data->s_notififcation, NOTIFICATION_LY_NOTI_EVENT_SINGLE);
	if (icon_path)
		notification_set_image(tg_data->s_notififcation, NOTIFICATION_IMAGE_TYPE_ICON, icon_path);
	if (title)
		notification_set_text(tg_data->s_notififcation, NOTIFICATION_TEXT_TYPE_TITLE, title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	if (content)
		notification_set_text(tg_data->s_notififcation, NOTIFICATION_TEXT_TYPE_CONTENT, content, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	if (sound_path)
		notification_set_sound(tg_data->s_notififcation, NOTIFICATION_SOUND_TYPE_USER_DATA, sound_path);
	else
		notification_set_sound(tg_data->s_notififcation, NOTIFICATION_SOUND_TYPE_DEFAULT, NULL);
	notification_set_vibration(tg_data->s_notififcation, NOTIFICATION_VIBRATION_TYPE_DEFAULT, NULL);

	app_control_h service = NULL;
	app_control_create(&service);
	app_control_set_app_id(service, app_id);
	app_control_set_operation(service, APP_CONTROL_OPERATION_DEFAULT);

	notification_set_launch_option(tg_data->s_notififcation, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, service);
	notification_post(tg_data->s_notififcation);
	app_control_destroy(service);

	notification_free(tg_data->s_notififcation);
	return;
}


void display_badge_with_notification(int unread_msg_cnt, tg_engine_data_s* tg_data)
{
	if (unread_msg_cnt <= 0)
		unread_msg_cnt = 0;

	badge_set_count(TELEGRAM_APP_ID, unread_msg_cnt);
	if (unread_msg_cnt != g_last_unread_msg_cnt) {
		char content[512];
		snprintf(content, sizeof(content), "%d new messages received.", unread_msg_cnt);
		tg_notification_create(tg_data,ui_utils_get_resource(DEFAULT_TELEGRAM_ICON), "Telegram", content, NULL, TELEGRAM_APP_ID);
		g_last_unread_msg_cnt = unread_msg_cnt;
	}
}


char *replace(const char *s, char ch, const char *repl)
{
	int count = 0;
	const char *t;

	for (t = s; *t; t++)
		count += (*t == ch);

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
	if (!msg_table)
		return NULL;

	snprintf(msg_table, 32, "tg_%d_msg", id);

	return msg_table;
}

char *ui_utils_get_resource(const char *res_name)
{
	static char res_path[PATH_MAX] = {'\0'};
	char *path;

	path = app_get_resource_path();
	if (!path)
		return NULL;

	snprintf(res_path, PATH_MAX, "%s%s", path, res_name);
	free(path);

	return res_path;
}

int recursive_dir_delete(const char *dir)
{
	int ret = 0;
	FTS *ftsp = NULL;
	FTSENT *curr;

	/* Cast needed (in C) because fts_open() takes a "char * const *", instead
		of a "const char * const *", which is only allowed in C++. fts_open()
		does not modify the argument. */
	char *files[] = { (char *) dir, NULL };

	/* FTS_NOCHDIR  - Avoid changing cwd, which could cause unexpected behavior
						in multithreaded programs
		FTS_PHYSICAL - Don't follow symlinks. Prevents deletion of files outside
						of the specified directory
		FTS_XDEV     - Don't cross filesystem boundaries */
	ftsp = fts_open(files, FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, NULL);
	if (!ftsp) {
		ret = -1;
		goto finish;
	}

	while ((curr = fts_read(ftsp))) {
		switch (curr->fts_info) {
		case FTS_NS:
		case FTS_DNR:
		case FTS_ERR:
			/*fprintf(stderr, "%s: fts_read error: %s\n", curr->fts_accpath, strerror(curr->fts_errno)); */
			break;

		case FTS_DC:
		case FTS_DOT:
		case FTS_NSOK:
			/* Not reached unless FTS_LOGICAL, FTS_SEEDOT, or FTS_NOSTAT were passed to fts_open() */
			break;

		case FTS_D:
			/* Do nothing. Need depth-first search, so directories are deleted in FTS_DP */
			break;

		case FTS_DP:
		case FTS_F:
		case FTS_SL:
		case FTS_SLNONE:
		case FTS_DEFAULT:
			if (remove(curr->fts_accpath) < 0)
				ret = -1;
			break;
		}
	}

finish:
	if (ftsp)
		fts_close(ftsp);
	return ret;
}
