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

#ifndef TG_USER_INFO_VIEW_H_
#define TG_USER_INFO_VIEW_H_


#include "tg_common.h"

extern void launch_user_info_screen(appdata_s* ad, int peer_id);
extern void on_user_block_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success);
extern void on_user_unblock_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success);
extern void on_user_deleted_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success);
extern void on_user_added_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success);

#endif /* TG_USER_INFO_VIEW_H_ */
