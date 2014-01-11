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
#include <stdio.h>
#include <unistd.h>

static void
connecting(e3_tcp_client_t *tcp_client) {
    if (e3_socket_is_connected(tcp_client->socket)) {
        e3_timer_delete(&tcp_client->timeout_timer);
        e3_event_fire(&tcp_client->connected, 0);
    }
    else if (e3_socket_is_error(tcp_client->socket)) {
        e3_timer_delete(&tcp_client->timeout_timer);
        e3_event_fire(&tcp_client->disconnected, 0);
    }
    else {
        e3_timer_create(&tcp_client->poll_timer, tcp_client->poll_interval,
            (e3_timer_function_t) connecting, tcp_client);
    }
}

static void
connect_timeout(e3_tcp_client_t *tcp_client) {
    e3_timer_delete(&tcp_client->poll_timer);
    e3_event_fire(&tcp_client->timeout, 0);
}

void
e3_tcp_client_create(e3_tcp_client_t *tcp_client, e3_socket_t *socket,
    e3_timer_ticks_t poll_interval) {

    tcp_client->socket = socket;
    tcp_client->poll_interval = poll_interval;
    e3_event_create(&tcp_client->connected);
    e3_event_create(&tcp_client->timeout);
    e3_event_create(&tcp_client->disconnected);
}

void
e3_tcp_client_connect(e3_tcp_client_t *tcp_client, const char *host, int port,
    e3_timer_ticks_t timeout) {

    e3_socket_connect(tcp_client->socket, host, port);

    e3_timer_create(&tcp_client->poll_timer, tcp_client->poll_interval,
        (e3_timer_function_t) connecting, tcp_client);

    e3_timer_create(&tcp_client->timeout_timer, timeout,
        (e3_timer_function_t) connect_timeout, tcp_client);
}

void
e3_tcp_client_delete(e3_tcp_client_t *tcp_client) {
    e3_event_delete(&tcp_client->connected);
    e3_event_delete(&tcp_client->timeout);
    e3_event_delete(&tcp_client->disconnected);
    /*e3_timer_delete(&tcp_client->poll_timer);
    e3_timer_delete(&tcp_client->timeout_timer);*/
}

