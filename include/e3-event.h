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

#ifndef E3_EVENT_H_
#define E3_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*e3_event_handler_t)(void *hint, void *args);
typedef struct e3_event e3_event_t;

typedef struct e3_event_listener {
    struct e3_event_listener *next;
    e3_event_t *event;
    e3_event_handler_t function;
    void *cookie;
} e3_event_listener_t;

struct e3_event {
    e3_event_listener_t *listeners;
};

extern void
e3_event_create(e3_event_t *event);

extern void
e3_event_delete(e3_event_t *event);

extern void
e3_event_fire(e3_event_t *event, void *args);

extern void
e3_event_listener_create(e3_event_listener_t *listener, e3_event_t *event,
    e3_event_handler_t function, void *cookie);

extern void
e3_event_listener_delete(e3_event_listener_t *listener);

#ifdef __cplusplus
}
#endif

#endif /* E3_EVENT_H_ */

