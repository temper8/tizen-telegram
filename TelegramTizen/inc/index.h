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

#ifndef INDEX_H_
#define INDEX_H_

#include "tg_common.h"

extern void index_destroy(Evas_Object *index);
extern Evas_Object *index_create(Evas_Object *ui_manager, unsigned int count);
extern void index_update(Evas_Object *index, unsigned int count);
extern void index_bring_in(Evas_Object *index, int idx);

#endif /* INDEX_H_ */
