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
connecting(e3_tcp_client_t *client) {
    if (e3_socket_is_connected(client->socket)) {
        e3_timer_delete(&client->timeout_timer);
        e3_event_fire(&client->connected, 0);
    }
    else if (e3_socket_is_error(client->socket)) {
        e3_timer_delete(&client->timeout_timer);
        e3_event_fire(&client->disconnected, 0);
    }
    else {
        e3_timer_create(&client->poll_timer, client->poll_interval,
            (e3_timer_function_t) connecting, client);
    }
}

static void
connect_timeout(e3_tcp_client_t *client) {
    e3_timer_delete(&client->poll_timer);
    e3_event_fire(&client->timeout, 0);
}

void
e3_tcp_client_create(e3_tcp_client_t *client, e3_socket_t *socket,
    e3_timer_ticks_t poll_interval) {

    client->socket = socket;
    client->poll_interval = poll_interval;
    e3_event_create(&client->connected);
    e3_event_create(&client->timeout);
    e3_event_create(&client->disconnected);
}

void
e3_tcp_client_connect(e3_tcp_client_t *client, const char *host, int port,
    e3_timer_ticks_t timeout) {

    e3_socket_connect(client->socket, host, port);

    e3_timer_create(&client->poll_timer, client->poll_interval,
        (e3_timer_function_t) connecting, client);

    e3_timer_create(&client->timeout_timer, timeout,
        (e3_timer_function_t) connect_timeout, client);
}

void
e3_tcp_client_delete(e3_tcp_client_t *client) {
    e3_event_delete(&client->connected);
    e3_event_delete(&client->timeout);
    e3_event_delete(&client->disconnected);
    e3_timer_delete(&client->poll_timer);
    e3_timer_delete(&client->timeout_timer);
}

