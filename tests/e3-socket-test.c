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
#include "e3-socket-double.h"
#include <e3-socket.h>

void
e3_socket_test(jasmine_t *jasmine) {
    e3_socket_double_t test;

    jasmine_describe(jasmine, "a socket") {
        jasmine_before(jasmine) {
            e3_socket_double_create(&test);
        }

        jasmine_after(jasmine) {
            e3_socket_double_delete(&test);
        }

        jasmine_it(jasmine, "can connect to host name and port") {
            e3_socket_connect(&test.socket, "localhost", 80);
            
            e3_socket_double_set_connected(&test, 0);
            jasmine_expect(jasmine, !e3_socket_is_connected(&test.socket));
            
            e3_socket_double_set_connected(&test, 1);
            jasmine_expect(jasmine, e3_socket_is_connected(&test.socket));
        }
        
        jasmine_it(jasmine, "can checking for available data") {
            jasmine_expect(jasmine, e3_socket_is_data_available(&test.socket));
            
            e3_socket_double_set_data_available(&test, 0);
            jasmine_expect(jasmine, !e3_socket_is_data_available(&test.socket));
            
            e3_socket_double_set_data_available(&test, 1);
            jasmine_expect(jasmine, e3_socket_is_data_available(&test.socket));
        }
    }
}

