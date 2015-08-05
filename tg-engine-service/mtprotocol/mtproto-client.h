/* 
    This file is part of tgl-library

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

    Copyright Nikolay Durov, Andrey Lopatin 2012-2013
              Vitaly Valtman 2013-2015
*/
#ifndef __MTPROTO_CLIENT_H__
#define __MTPROTO_CLIENT_H__

#include <openssl/bn.h>
#include "tgl.h"

struct connection;
struct tgl_dc;

#define TG_APP_HASH "8b5082937b2eb8814559291b93caa8a5"
#define TG_APP_ID 26793

#define ACK_TIMEOUT 1
#define MAX_DC_ID 10

struct connection;

long long tglmp_encrypt_send_message (struct tgl_state *TLS, struct connection *c, int *msg, int msg_ints, int flags);
void tglmp_dc_create_session (struct tgl_state *TLS, struct tgl_dc *DC);
struct tgl_dc *tglmp_alloc_dc (struct tgl_state *TLS, int id, char *ip, int port);
void tglmp_regenerate_temp_auth_key (struct tgl_state *TLS, struct tgl_dc *D);
void tgln_insert_msg_id (struct tgl_state *TLS, struct tgl_session *S, long long id);
void tglmp_on_start (struct tgl_state *TLS);
void tgl_dc_authorize (struct tgl_state *TLS, struct tgl_dc *DC);
void tgls_free_dc (struct tgl_state *TLS, struct tgl_dc *DC);
void tgls_free_pubkey (struct tgl_state *TLS);

#endif
