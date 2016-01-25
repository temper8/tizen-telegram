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

#include "tg_splash_screen.h"

void
launch_splash_screen_cb(void *data)
{
	appdata_s* ad = data;

	char edj_path[PATH_MAX] = {0, };

	ad->current_app_state = TG_REGISTRATION_STATE;
	Evas_Object* layout = elm_layout_add(ad->win);
	app_get_resource(TELEGRAM_INIT_VIEW_EDJ, edj_path, (int)PATH_MAX);
	elm_layout_file_set(layout, edj_path, "splash_screen");
	Evas_Object* progressbar = elm_progressbar_add(layout);
	elm_object_style_set(progressbar, "process_small");
	evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_progressbar_pulse(progressbar, EINA_TRUE);
	elm_object_part_content_set(layout, "swallow.splash_screen", progressbar);
	Elm_Object_Item *item =  elm_naviframe_item_push(ad->nf, NULL, NULL, NULL, layout, NULL);
	elm_naviframe_item_title_enabled_set(item, EINA_FALSE, EINA_TRUE);

}
