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

#include "e3-socket-test.h"
#include <e3-socket.h>

typedef struct test {
    e3_socket_t socket;
    unsigned int connect;
} test_t;

static void
test_connect(e3_socket_t *socket, const char *host, int port) {
    (void) host;
    (void) port;

    ((test_t *) socket)->connect++;
}

static const e3_socket_interface_t SOCKET_INTERFACE[] = { {
    test_connect
} };

void
e3_socket_test(jasmine_t *jasmine) {
    test_t test;

    jasmine_describe(jasmine, "a socket") {
        jasmine_before(jasmine) {
            e3_socket_create(&test.socket, SOCKET_INTERFACE);
            test.connect = 0;
        }

        jasmine_after(jasmine) {
            e3_socket_delete(&test.socket);
        }

        jasmine_it(jasmine, "can connect to host name and port") {
            e3_socket_connect(&test.socket, "localhost", 80);
            jasmine_expect(jasmine, test.connect == 1);
        }
    }
}

