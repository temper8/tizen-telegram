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

#ifndef TG_SEARCH_PEER_VIEW_H_
#define TG_SEARCH_PEER_VIEW_H_

#include "tg_common.h"

extern void launch_start_peer_search_view(appdata_s* ad);
extern void on_create_new_contact(appdata_s* ad);
extern void on_new_contact_added_response_received(appdata_s *ad, int buddy_id, Eina_Bool is_success);

#endif /* TG_SEARCH_PEER_VIEW_H_ */
