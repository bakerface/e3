/*
 * Copyright (c) 2013 - Christopher M. Baker
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

#ifndef E3_TIMER_H_
#define E3_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long e3_timer_ticks_t;
typedef void (*e3_timer_function_t)(void *cookie);

typedef struct e3_timer {
    struct e3_timer *next;
    e3_timer_ticks_t ticks;
    e3_timer_function_t function;
    void *cookie;
} e3_timer_t;

extern void
e3_timer_interrupt(void);

extern e3_timer_ticks_t
e3_timer_tick(void);

extern void
e3_timer_create(e3_timer_t *timer, e3_timer_ticks_t ticks,
    e3_timer_function_t function, void *cookie);

extern void
e3_timer_delete(e3_timer_t *timer);

#ifdef __cplusplus
}
#endif

#endif /* E3_TIMER_H_ */

