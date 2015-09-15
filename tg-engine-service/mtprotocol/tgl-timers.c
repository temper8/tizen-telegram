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

    Copyright Vitaly Valtman 2013-2015
 */
#include "tgl.h"
#include <stdlib.h>
#include <Ecore.h>

#define TIMER_MAX_VALUE 1000

struct timer_context {
	Ecore_Timer *handler;
	void *cbdata;
};

static Eina_Bool timer_alarm(void* arg)
{
	struct timer_context *tc = arg;
	tc->handler = NULL;
	void **p = tc->cbdata;
	((void (*)(struct tgl_state *, void *))p[1])(p[0], p[2]);
	return ECORE_CALLBACK_CANCEL;
}

struct tgl_timer *tgl_timer_alloc(struct tgl_state *TLS, void (*cb)(struct tgl_state *TLS, void *arg), void *arg)
{
	void **p = malloc (sizeof (void *) * 3);
	p[0] = TLS;
	p[1] = cb;
	p[2] = arg;

	struct timer_context *tc;
	tc = malloc(sizeof(*tc));
	if (tc) {
		tc->handler = NULL;
		tc->cbdata = (void *)p;
		return (void *)tc;
	}

	return NULL;
}

void tgl_timer_insert(struct tgl_timer *t, double p)
{
	if (p < 0) {
		p = 0.000001;
	}
	struct timer_context *tc = (struct timer_context *)t;
	tc->handler = ecore_timer_add(p, timer_alarm, tc);
	if (!tc->handler) {
		// Something goes wrong
	}
	return;
}

void tgl_timer_delete(struct tgl_timer *t)
{
	struct timer_context *tc = (struct timer_context *)t;
	if (tc->handler) {
		ecore_timer_del(tc->handler);
		tc->handler = NULL;
	}
}

void tgl_timer_free(struct tgl_timer *t)
{
	struct timer_context *tc;
	tc = (struct timer_context *)t;
	if (tc->handler) {
		// Something goes wrong, tgl_timer_delete is not called before.
		// Exceptional cases.
		ecore_timer_del(tc->handler);
		tc->handler = NULL;
	}
	free(tc->cbdata);
	free(tc);
}

struct tgl_timer_methods tgl_libevent_timers = {
	.alloc = tgl_timer_alloc,
	.insert = tgl_timer_insert,
	.remove = tgl_timer_delete,
	.free = tgl_timer_free
};
