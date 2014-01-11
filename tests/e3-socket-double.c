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

#include "e3-socket-double.h"

static void
connect(e3_socket_t *socket, const char *host, int port) {
    ((e3_socket_double_t *) socket)->host = host;
    ((e3_socket_double_t *) socket)->port = port;
}

static int
is_connected(e3_socket_t *socket) {
    return ((e3_socket_double_t *) socket)->is_connected;
}

static int
is_data_available(e3_socket_t *socket) {
    return ((e3_socket_double_t *) socket)->is_data_available;
}

static int
is_error(e3_socket_t *socket) {
    return ((e3_socket_double_t *) socket)->is_error;
}

e3_socket_interface_t E3_SOCKET_DOUBLE[1] = { {
    connect,
    is_connected,
    is_data_available,
    is_error
} };

