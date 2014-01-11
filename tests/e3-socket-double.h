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

#ifndef E3_SOCKET_DOUBLE_H_
#define E3_SOCKET_DOUBLE_H_

#include <e3-socket.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct e3_socket_double {
    e3_socket_t socket;
    const char *host;
    int port;
    int is_connected;
    int is_data_available;
    int is_error;
} e3_socket_double_t;

extern e3_socket_interface_t E3_SOCKET_DOUBLE[1];

#define e3_socket_double_create(_socket) \
    e3_socket_create(&(_socket)->socket, E3_SOCKET_DOUBLE)

#define e3_socket_double_set_host(_socket, _value) \
    (_socket)->host = (_value)

#define e3_socket_double_set_port(_socket, _value) \
    (_socket)->port = (_value)

#define e3_socket_double_set_connected(_socket, _value) \
    (_socket)->is_connected = (_value)

#define e3_socket_double_set_data_available(_socket, _value) \
    (_socket)->is_data_available = (_value)

#define e3_socket_double_set_error(_socket, _value) \
    (_socket)->is_error = (_value)

#define e3_socket_double_delete(_socket) \
    e3_socket_delete(&(_socket)->socket)

#ifdef __cplusplus
}
#endif

#endif /* E3_SOCKET_DOUBLE_H_ */

