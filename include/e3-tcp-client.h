/*
 * Copyright (c) 2014 - Christopher M. Baker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#ifndef E3_TCP_CLIENT_H_
#define E3_TCP_CLIENT_H_

#include <e3-timer.h>
#include <e3-event.h>
#include <e3-socket.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct e3_tcp_client {
    e3_socket_t *socket;
    e3_timer_ticks_t poll_interval;
    e3_event_t connected;
    e3_event_t timeout;
    e3_event_t disconnected;
    e3_timer_t poll_timer;
    e3_timer_t timeout_timer;
} e3_tcp_client_t;

extern void
e3_tcp_client_create(e3_tcp_client_t *client, e3_socket_t *socket,
    e3_timer_ticks_t poll_interval);

extern void
e3_tcp_client_connect(e3_tcp_client_t *client, const char *host, int port,
    e3_timer_ticks_t timeout);

extern void
e3_tcp_client_delete(e3_tcp_client_t *client);

#ifdef __cplusplus
}
#endif

#endif /* E3_TCP_CLIENT_H_ */

