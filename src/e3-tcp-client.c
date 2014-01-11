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

#include <e3-tcp-client.h>

#define POLL_INTERVAL_IN_TICKS 10

static void
poll_connecting(e3_tcp_client_t *tcp_client) {
    e3_socket_flags_t flags = e3_socket_poll(tcp_client->socket);
    
    if (flags & E3_SOCKET_FLAGS_WRITE) {
    
    }
    else if (flags & E3_SOCKET_FLAGS_ERROR) {
    
    }
    else {
    
    }
}

void
e3_tcp_client_create(e3_tcp_client_t *tcp_client, e3_socket_t *socket) {
    tcp_client->socket = socket;
}

void
e3_tcp_client_connect(e3_tcp_client_t *tcp_client, const char *host, int port,
    e3_timer_ticks_t timeout) {
    
    (void) timeout;
    e3_socket_connect(tcp_client->socket, host, port);
    
    e3_timer_create(&tcp_client->poll_timer, POLL_INTERVAL_IN_TICKS,
        (e3_timer_function_t) poll_connecting, &tcp_client);
}

void
e3_tcp_client_delete(e3_tcp_client_t *tcp_client) {
    (void) tcp_client;
}

