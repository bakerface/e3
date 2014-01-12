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

#include "e3-tcp-client-test.h"
#include "e3-socket-double.h"
#include <e3-tcp-client.h>

typedef struct test {
    e3_socket_double_t socket;
    e3_tcp_client_t client;
    e3_event_listener_t connect_listener;
    e3_event_listener_t timeout_listener;
    e3_event_listener_t disconnect_listener;
    unsigned int connected;
    unsigned int timeout;
    unsigned int disconnected;
} test_t;

static e3_timer_ticks_t
tick(void) {
    e3_timer_interrupt();
    return e3_timer_tick();
}

static void
connected(test_t *test, void *arg) {
    test->connected++;
    (void) arg;
}

static void
timeout(test_t *test, void *arg) {
    test->timeout++;
    (void) arg;
}

static void
disconnected(test_t *test, void *arg) {
    test->disconnected++;
    (void) arg;
}

void
e3_tcp_client_test(jasmine_t *jasmine) {
    test_t test;

    jasmine_describe(jasmine, "a tcp client") {
        jasmine_before(jasmine) {
            e3_socket_double_create(&test.socket);
            e3_socket_double_set_connected(&test.socket, 0);
            e3_socket_double_set_data_available(&test.socket, 0);
            e3_socket_double_set_error(&test.socket, 0);

            e3_tcp_client_create(&test.client, &test.socket.socket, 0);

            e3_event_listener_create(&test.connect_listener,
                &test.client.connected,
                (e3_event_handler_t) connected, &test);

            e3_event_listener_create(&test.timeout_listener,
                &test.client.timeout,
                (e3_event_handler_t) timeout, &test);

            e3_event_listener_create(&test.disconnect_listener,
                &test.client.disconnected,
                (e3_event_handler_t) disconnected, &test);

            test.connected    = 0;
            test.timeout      = 0;
            test.disconnected = 0;
        }

        jasmine_after(jasmine) {
            e3_event_listener_delete(&test.connect_listener);
            e3_event_listener_delete(&test.timeout_listener);
            e3_event_listener_delete(&test.disconnect_listener);
            e3_tcp_client_delete(&test.client);
            e3_socket_double_delete(&test.socket);
        }

        jasmine_it(jasmine, "can connect before the timeout is reached") {
            e3_tcp_client_connect(&test.client, "localhost", 80, 11);

            while (tick()) {
                e3_socket_double_set_connected(&test.socket, 1);
            }

            jasmine_expect(jasmine, test.connected    == 1);
            jasmine_expect(jasmine, test.timeout      == 0);
            jasmine_expect(jasmine, test.disconnected == 0);
        }

        jasmine_it(jasmine, "can timeout when the while connecting") {
            e3_tcp_client_connect(&test.client, "localhost", 80, 11);

            while (tick());

            jasmine_expect(jasmine, test.connected    == 0);
            jasmine_expect(jasmine, test.timeout      == 1);
            jasmine_expect(jasmine, test.disconnected == 0);
        }

        jasmine_it(jasmine, "can disconnect while connecting") {
            e3_tcp_client_connect(&test.client, "localhost", 80, 11);

            while (tick()) {
                e3_socket_double_set_error(&test.socket, 1);
            }

            jasmine_expect(jasmine, test.connected    == 0);
            jasmine_expect(jasmine, test.timeout      == 0);
            jasmine_expect(jasmine, test.disconnected == 1);
        }
    }
}

