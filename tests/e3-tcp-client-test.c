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
    e3_tcp_client_t tcp_client;
} test_t;

void
e3_tcp_client_test(jasmine_t *jasmine) {
    test_t test;

    jasmine_describe(jasmine, "a tcp client") {
        jasmine_before(jasmine) {
            e3_socket_double_create(&test.socket);
            e3_tcp_client_create(&test.tcp_client, &test.socket.socket);
        }

        jasmine_after(jasmine) {
            e3_tcp_client_delete(&test.tcp_client);
            e3_socket_double_delete(&test.socket);
        }

        jasmine_it(jasmine, "can connect before the timeout is reached") {
            e3_tcp_client_connect(&test.tcp_client, "localhost", 80, 0);
        }
    }
}

