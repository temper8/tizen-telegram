/*
    This file is part of tgl-library

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or(at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    Copyright Vitaly Valtman 2013-2015
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <openssl/rand.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include "tgl-net-inner.h"
#include "tgl-net.h"
#include "tgl.h"
#include "tgl-inner.h"
#include "tree.h"
#include "tools.h"

#ifndef POLLRDHUP
#define POLLRDHUP 0
#endif

int errno;

static void fail_connection(struct connection *c);
static void conn_try_write(void *arg);

#define PING_TIMEOUT 10

#if 0
//static Eina_Bool th_do(void *data)
static void th_do(void *data, Ecore_Thread *th)
{
	struct connection *c = data;
	fd_set writeset;
	FD_ZERO(&writeset);

	FD_SET(c->fd, &writeset);
	select(c->fd + 1, NULL, &writeset, NULL, NULL);

	ecore_thread_feedback(c->thrd, c);

	//return ECORE_CALLBACK_CANCEL;
}

static void th_feedback(void *data, Ecore_Thread *th, void *msg)
{
	struct connection *c = msg;
	conn_try_write(c);
}

// BONUS (optional): called after th_do returns and has NOT been cancelled
static void th_end(void *data, Ecore_Thread *th) {  }
// BONUS (optional): called in mainloop AFTER thread has finished cancelling
static void th_cancel(void *data, Ecore_Thread *th) { }
#else

static Eina_Bool write_call(void* data)
{
	struct connection *c = data;

	if (c->TLS == NULL || c->fd <= 0) {
		return ECORE_CALLBACK_CANCEL;
	}

	fd_set writeset;
	FD_ZERO(&writeset);

	FD_SET(c->fd, &writeset);
	select(c->fd + 1, NULL, &writeset, NULL, NULL);
	conn_try_write(c);
	return ECORE_CALLBACK_CANCEL;
}


#endif


static void start_ping_timer(struct connection *c);

Eina_Bool ping_alarm(void *arg)
{
	struct connection *c = arg;
	struct tgl_state *TLS = c->TLS;
	vlogprintf(E_DEBUG + 2,"ping alarm\n");
	//assert(c->state == conn_ready || c->state == conn_connecting);
	if(c->state != conn_ready || c->state != conn_connecting) {
		return ECORE_CALLBACK_CANCEL;
	}

	if (tglt_get_double_time() - c->last_receive_time > 6 * PING_TIMEOUT) {
		vlogprintf(E_WARNING, "fail connection: reason: ping timeout\n");
		c->state = conn_failed;
		fail_connection(c);
	} else if (tglt_get_double_time() - c->last_receive_time > 3 * PING_TIMEOUT && c->state == conn_ready) {
		tgl_do_send_ping(c->TLS, c);
		start_ping_timer(c);
	} else {
		start_ping_timer(c);
	}
	return ECORE_CALLBACK_CANCEL;
}

static void stop_ping_timer(struct connection *c)
{
	if(c->ping_ev) {
		ecore_timer_del(c->ping_ev);
		c->ping_ev = NULL;
	}
}

static void start_ping_timer(struct connection *c)
{
	c->ping_ev = ecore_timer_add(PING_TIMEOUT, ping_alarm, c);
}

static void restart_connection(struct connection *c);

Eina_Bool fail_alarm(void *arg)
{
	struct connection *c = arg;
	c->in_fail_timer = 0;
	restart_connection(c);
	return ECORE_CALLBACK_CANCEL;
}

static void start_fail_timer(struct connection *c)
{
	if (c->in_fail_timer) {
		return;
	}
	c->in_fail_timer = 1;
	c->fail_ev = ecore_timer_add(10, fail_alarm, c);
}

static struct connection_buffer *new_connection_buffer(int size)
{
	struct connection_buffer *b = talloc0(sizeof(*b));
	b->start = talloc(size);
	b->end = b->start + size;
	b->rptr = b->wptr = b->start;
	return b;
}

static void delete_connection_buffer(struct connection_buffer *b)
{
	tfree(b->start, b->end - b->start);
	tfree(b, sizeof(*b));
}

int tgln_write_out(struct connection *c, const void *_data, int len)
{
	struct tgl_state *TLS = c->TLS;
	vlogprintf(E_DEBUG, "write_out: %d bytes\n", len);
	const unsigned char *data = _data;
	if (!len) { return 0; }
	assert(len > 0);
	int x = 0;
	if (!c->out_bytes) {
		/*		Ecore_Idler *idler_for_event;
				idler_for_event = ecore_idler_add(th_do, c);*/
#if 0
		if(c->thrd) {
			ecore_thread_cancel(c->thrd);
			c->thrd = NULL;
		}

		c->thrd = ecore_thread_feedback_run(th_do, th_feedback, th_end, th_cancel, c, EINA_FALSE);
#else
		if(c->write_ev) {
			ecore_timer_del(c->write_ev);
			c->write_ev = NULL;
		}
		c->write_ev = ecore_timer_add(0.000001, write_call, c);
#endif
	}

	if (!c->out_head) {
		struct connection_buffer *b = new_connection_buffer(1 << 20);
		c->out_head = c->out_tail = b;
	}
	while(len) {
		if (c->out_tail->end - c->out_tail->wptr >= len) {
			memcpy(c->out_tail->wptr, data, len);
			c->out_tail->wptr += len;
			c->out_bytes += len;
			return x + len;
		} else {
			int y = c->out_tail->end - c->out_tail->wptr;
			assert(y < len);
			memcpy(c->out_tail->wptr, data, y);
			x += y;
			len -= y;
			data += y;
			struct connection_buffer *b = new_connection_buffer(1 << 20);
			c->out_tail->next = b;
			b->next = 0;
			c->out_tail = b;
			c->out_bytes += y;
		}
	}
	return x;
}

int tgln_read_in(struct connection *c, void *_data, int len)
{
	unsigned char *data = _data;
	if (!len) { return 0; }
	assert(len > 0);
	if (len > c->in_bytes) {
		len = c->in_bytes;
	}
	int x = 0;
	while(len) {
		int y = c->in_head->wptr - c->in_head->rptr;
		if (y > len) {
			memcpy(data, c->in_head->rptr, len);
			c->in_head->rptr += len;
			c->in_bytes -= len;
			return x + len;
		} else {
			memcpy(data, c->in_head->rptr, y);
			c->in_bytes -= y;
			x += y;
			data += y;
			len -= y;
			void *old = c->in_head;
			c->in_head = c->in_head->next;
			if (!c->in_head) {
				c->in_tail = 0;
			}
			delete_connection_buffer(old);
		}
	}
	return x;
}

int tgln_read_in_lookup(struct connection *c, void *_data, int len)
{
	unsigned char *data = _data;
	if (!len || !c->in_bytes) {
		return 0;
	}
	assert(len > 0);

	if (len > c->in_bytes) {
		len = c->in_bytes;
	}

	int x = 0;
	struct connection_buffer *b = c->in_head;

	while(len) {
		int y = b->wptr - b->rptr;
		if (y >= len) {
			memcpy(data, b->rptr, len);
			return x + len;
		} else {
			memcpy(data, b->rptr, y);
			x += y;
			data += y;
			len -= y;
			b = b->next;
		}
	}
	return x;
}

void tgln_flush_out(struct connection *c)
{
	// not used.
}

#define MAX_CONNECTIONS 100
static struct connection *Connections[MAX_CONNECTIONS];
static int max_connection_fd;

static void rotate_port(struct connection *c)
{
	switch(c->port) {
	case 443:
		c->port = 80;
		break;
	case 80:
		c->port = 25;
		break;
	case 25:
		c->port = 443;
		break;
	}
}

static void try_read(struct connection *c);
static void try_write(struct connection *c);

static Eina_Bool conn_try_read(void *arg, Ecore_Fd_Handler *handler)
{
	struct connection *c = arg;
	struct tgl_state *TLS = c->TLS;
	vlogprintf(E_DEBUG + 1, "Try read. Fd = %d\n", c->fd);
	try_read(c);
	return ECORE_CALLBACK_RENEW;
}

void conn_try_write(void *arg)
{
	struct connection *c = arg;
	struct tgl_state *TLS = c->TLS;

	if (c->state == conn_connecting) {
		c->state = conn_ready;
		c->methods->ready(TLS, c);
	}

	try_write(c);
	if (c->out_bytes) {
		/*		Ecore_Idler *idler_for_event;
				idler_for_event = ecore_idler_add(th_do, c);*/
#if 0
		if(c->thrd) {
			ecore_thread_cancel(c->thrd);
			c->thrd = NULL;
		}

		c->thrd = ecore_thread_feedback_run(th_do, th_feedback, th_end, th_cancel, c, EINA_FALSE);
#else
		if(c->write_ev) {
			ecore_timer_del(c->write_ev);
			c->write_ev = NULL;
		}
		c->write_ev = ecore_timer_add(0.000001, write_call, c);
#endif
	}
}

static int my_connect(struct connection *c, const char *host)
{
	struct tgl_state *TLS = c->TLS;
	int v6 = TLS->ipv6_enabled;

	int fd = socket(v6 ? AF_INET6 : AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		vlogprintf(E_ERROR, "Can not create socket: %m\n");
		start_fail_timer(c);
		return -1;
	}
	assert(fd >= 0 && fd < MAX_CONNECTIONS);

	if (fd > max_connection_fd) {
		max_connection_fd = fd;
	}

	int flags = -1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags));
	setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &flags, sizeof(flags));
	setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof(flags));

	struct sockaddr_in addr;
	struct sockaddr_in6 addr6;
	memset(&addr, 0, sizeof(addr));
	memset(&addr6, 0, sizeof(addr6));

	if (v6) {
		addr6.sin6_family = AF_INET6;
		addr6.sin6_port = htons(c->port);
		if (inet_pton(AF_INET6, host, &addr6.sin6_addr.s6_addr) != 1) {
			vlogprintf(E_ERROR, "Bad ipv6 %s\n", host);
			close(fd);
			return -1;
		}
	} else {
		addr.sin_family = AF_INET;
		addr.sin_port = htons(c->port);
		if (inet_pton(AF_INET, host, &addr.sin_addr.s_addr) != 1) {
			vlogprintf(E_ERROR, "Bad ipv4 %s\n", host);
			close(fd);
			return -1;
		}
	}

	fcntl(fd, F_SETFL, O_NONBLOCK);

	if (connect(fd,(struct sockaddr *)(v6 ?(void *)&addr6 :(void *)&addr), v6 ? sizeof(addr6) : sizeof(addr)) == -1) {
		if (errno != EINPROGRESS) {
			close(fd);
			return -1;
		}
	}

	return fd;
}

static Eina_Bool read_timer_alarm(void* arg)
{
	struct connection *c = arg;
	if(c->read_ev) {
		ecore_main_fd_handler_del(c->read_ev);
		c->read_ev = NULL;
	}
	c->read_ev = ecore_main_fd_handler_add(c->fd, ECORE_FD_READ, conn_try_read, c, NULL,NULL);
	return ECORE_CALLBACK_CANCEL;
}

struct connection *tgln_create_connection(struct tgl_state *TLS, const char *host, int port, struct tgl_session *session, struct tgl_dc *dc, struct mtproto_methods *methods)
{
	struct connection *c = talloc0(sizeof(*c));
	c->TLS = TLS;
	c->ip = tstrdup(host);
	c->port = port;

	int fd = my_connect(c, c->ip);
	if (fd < 0) {
		vlogprintf(E_ERROR, "Can not connect to %s:%d %m\n", host, port);
		tfree(c, sizeof(*c));
		return 0;
	}

	c->fd = fd;
	c->state = conn_connecting;
	c->last_receive_time = tglt_get_double_time();
	c->flags = 0;
	//c->thrd = 0;
	c->write_ev = 0;
	assert(!Connections[fd]);
	Connections[fd] = c;

	Ecore_Timer* timer = ecore_timer_add(2, read_timer_alarm, c);
	if(!timer) {
		//handle error
	}

	start_ping_timer(c);

	c->dc = dc;
	c->session = session;
	c->methods = methods;

	char byte = 0xef;
	int ret;
	ret = tgln_write_out(c, &byte, 1);
	assert(ret == 1);
	tgln_flush_out(c);

	return c;
}

static void restart_connection(struct connection *c)
{
	struct tgl_state *TLS = c->TLS;

	if (c->last_connect_time == time(0)) {
		start_fail_timer(c);
		return;
	}

	if (strcmp(c->ip, c->dc->ip)) {
		tfree_str(c->ip);
		c->ip = tstrdup(c->dc->ip);
	}

	c->last_connect_time = time(0);
	int fd = my_connect(c, c->ip);
	if (fd < 0) {
		vlogprintf(E_WARNING, "Can not connect to %s:%d %m\n", c->ip, c->port);
		start_fail_timer(c);
		return;
	}

	c->fd = fd;
	c->state = conn_connecting;
	//c->thrd = 0;
	c->write_ev = 0;
	c->last_receive_time = tglt_get_double_time();
	start_ping_timer(c);
	Connections[fd] = c;
	Ecore_Timer* timer = ecore_timer_add(2, read_timer_alarm, c);
	if(!timer) {

	}

	char byte = 0xef;
	assert(tgln_write_out(c, &byte, 1) == 1);
	tgln_flush_out(c);
}

static void fail_connection(struct connection *c)
{
	struct tgl_state *TLS = c->TLS;
	if (c->state == conn_ready || c->state == conn_connecting) {
		stop_ping_timer(c);
	}

	if(c->read_ev) {
		ecore_main_fd_handler_del(c->read_ev);
		c->read_ev = NULL;
	}
#if 0
	if(c->thrd) {
		ecore_thread_cancel(c->thrd);
		c->thrd = NULL;
	}
#else
	if(c->write_ev) {
		ecore_timer_del(c->write_ev);
		c->write_ev = NULL;
	}
#endif
	rotate_port(c);
	struct connection_buffer *b = c->out_head;
	while(b) {
		struct connection_buffer *d = b;
		b = b->next;
		delete_connection_buffer(d);
	}
	b = c->in_head;
	while(b) {
		struct connection_buffer *d = b;
		b = b->next;
		delete_connection_buffer(d);
	}
	c->out_head = c->out_tail = c->in_head = c->in_tail = 0;
	c->state = conn_failed;
	c->out_bytes = c->in_bytes = 0;
	close(c->fd);
	Connections[c->fd] = 0;
	vlogprintf(E_NOTICE, "Lost connection to server... %s:%d\n", c->ip, c->port);
	restart_connection(c);
}

static void try_write(struct connection *c)
{
	struct tgl_state *TLS = c->TLS;
	vlogprintf(E_DEBUG, "try write: fd = %d\n", c->fd);
	int x = 0;

	while(c->out_head) {
		int r = write(c->fd, c->out_head->rptr, c->out_head->wptr - c->out_head->rptr);
		if (r >= 0) {
			x += r;
			c->out_head->rptr += r;
			if (c->out_head->rptr != c->out_head->wptr) {
				break;
			}
			struct connection_buffer *b = c->out_head;
			c->out_head = b->next;
			if (!c->out_head) {
				c->out_tail = 0;
			}
			delete_connection_buffer(b);
		} else {
			if (errno != EAGAIN && errno != EWOULDBLOCK) {
				vlogprintf(E_NOTICE, "fail_connection: write_error %m\n");
				fail_connection(c);
				return;
			} else {
				break;
			}
		}
	}

	vlogprintf(E_DEBUG, "Sent %d bytes to %d\n", x, c->fd);
	c->out_bytes -= x;
}

static void try_rpc_read(struct connection *c)
{
	assert(c->in_head);
	struct tgl_state *TLS = c->TLS;

	while(1) {
		if (c->in_bytes < 1) { return; }
		unsigned len = 0;
		unsigned t = 0;
		assert(tgln_read_in_lookup(c, &len, 1) == 1);

		if (len >= 1 && len <= 0x7e) {
			if (c->in_bytes <(int)(1 + 4 * len)) { return; }
		} else {
			if (c->in_bytes < 4) { return; }
			assert(tgln_read_in_lookup(c, &len, 4) == 4);
			len =(len >> 8);
			if (c->in_bytes <(int)(4 + 4 * len)) { return; }
			len = 0x7f;
		}

		if (len >= 1 && len <= 0x7e) {
			assert(tgln_read_in(c, &t, 1) == 1);
			assert(t == len);
			assert(len >= 1);
		} else {
			assert(len == 0x7f);
			assert(tgln_read_in(c, &len, 4) == 4);
			len =(len >> 8);
			assert(len >= 1);
		}

		len *= 4;
		int op;
		assert(tgln_read_in_lookup(c, &op, 4) == 4);

		if (c->methods->execute(TLS, c, op, len) < 0) {
			return;
		}
	}

}

static void try_read(struct connection *c)
{
	struct tgl_state *TLS = c->TLS;
	vlogprintf(E_DEBUG, "try read: fd = %d\n", c->fd);

	if (c->TLS == NULL || c->fd <= 0) {
		return;
	}
	if (!c->in_tail) {
		c->in_head = c->in_tail = new_connection_buffer(1 << 20);
	}

	int x = 0;

	while(1) {
		int r = read(c->fd, c->in_tail->wptr, c->in_tail->end - c->in_tail->wptr);
		if (r > 0) {
			c->last_receive_time = tglt_get_double_time();
			stop_ping_timer(c);
			start_ping_timer(c);
		}
		if (r >= 0) {
			c->in_tail->wptr += r;
			x += r;
			if (c->in_tail->wptr != c->in_tail->end) {
				break;
			}
			struct connection_buffer *b = new_connection_buffer(1 << 20);
			c->in_tail->next = b;
			c->in_tail = b;
		} else {
			if (errno != EAGAIN && errno != EWOULDBLOCK) {
				vlogprintf(E_NOTICE, "fail_connection: read_error %m\n");
				fail_connection(c);
				return;
			} else {
				break;
			}
		}
	}

	vlogprintf(E_DEBUG, "Received %d bytes from %d\n", x, c->fd);

	c->in_bytes += x;

	if (x) {
		try_rpc_read(c);
	}

}

static void incr_out_packet_num(struct connection *c)
{
	c->out_packet_num++;
}

static struct tgl_dc *get_dc(struct connection *c)
{
	return c->dc;
}

static struct tgl_session *get_session(struct connection *c)
{
	return c->session;
}

static void tgln_free(struct connection *c)
{
	if (c->ip) { tfree_str(c->ip); }
	struct connection_buffer *b = c->out_head;
	while(b) {
		struct connection_buffer *d = b;
		b = b->next;
		delete_connection_buffer(d);
	}
	b = c->in_head;
	while(b) {
		struct connection_buffer *d = b;
		b = b->next;
		delete_connection_buffer(d);
	}

	if(c->ping_ev) {
		ecore_timer_del(c->ping_ev);
		c->ping_ev = NULL;
	}
	if(c->fail_ev) {
		ecore_timer_del(c->fail_ev);
		c->fail_ev = NULL;
	}

	if(c->read_ev) {
		ecore_main_fd_handler_del(c->read_ev);
		c->read_ev = NULL;
	}
#if 0
	if(c->thrd) {
		ecore_thread_cancel(c->thrd);
		c->thrd = NULL;
	}
#else
	if(c->write_ev) {
		ecore_timer_del(c->write_ev);
		c->write_ev = NULL;
	}
#endif
	if (c->fd >= 0) {
		Connections[c->fd] = 0; close(c->fd);
	}

	tfree(c, sizeof(*c));
}

struct tgl_net_methods tgl_conn_methods = {
	.write_out = tgln_write_out,
	.read_in = tgln_read_in,
	.read_in_lookup = tgln_read_in_lookup,
	.flush_out = tgln_flush_out,
	.incr_out_packet_num = incr_out_packet_num,
	.get_dc = get_dc,
	.get_session = get_session,
	.create_connection = tgln_create_connection,
	.free = tgln_free
};
