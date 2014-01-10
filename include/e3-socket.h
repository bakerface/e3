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

#ifndef E3_SOCKET_H_
#define E3_SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum e3_socket_flags {
    E3_SOCKET_FLAGS_READ  = 1,
    E3_SOCKET_FLAGS_WRITE = 2,
    E3_SOCKET_FLAGS_ERROR = 4
} e3_socket_flags_t;

typedef struct e3_socket_interface e3_socket_interface_t;

typedef struct e3_socket {
    const e3_socket_interface_t *interface;
} e3_socket_t;

struct e3_socket_interface {
    void (*connect)(e3_socket_t *socket, const char *host, int port);
    e3_socket_flags_t (*poll)(e3_socket_t *socket);
};

#define e3_socket_create(_socket, _interface) \
    (_socket)->interface = (_interface)

#define e3_socket_connect(_socket, _host, _port) \
    (_socket)->interface->connect(_socket, _host, _port)
    
#define e3_socket_poll(_socket) \
    (_socket)->interface->poll(_socket)

#define e3_socket_delete(_socket)

#ifdef __cplusplus
}
#endif

#endif /* E3_SOCKET_H_ */

