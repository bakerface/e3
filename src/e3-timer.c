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

#include <e3-timer.h>

static e3_timer_t *timers = 0;
static e3_timer_ticks_t pending_ticks = 0;

void
e3_timer_interrupt(void) {
    pending_ticks++;
}

e3_timer_ticks_t
e3_timer_tick(void) {
    e3_timer_ticks_t ticks;
    e3_timer_t *current;
    e3_timer_t *next;

    ticks = pending_ticks;
    pending_ticks = 0;

    current = timers;
    timers = 0;

    while (current) {
        next = current->next;

        if (current->ticks > ticks) {
            current->next = timers;
            timers = current;
            current->ticks -= ticks;
        }
        else if (current->function) {
            current->function(current->cookie);
        }

        current = next;
    }

    return (timers != 0);
}

void
e3_timer_create(e3_timer_t *timer, e3_timer_ticks_t ticks,
    e3_timer_function_t function, void *cookie) {

    timer->next = timers;
    timers = timer;

    timer->ticks = ticks;
    timer->function = function;
    timer->cookie = cookie;
}

void
e3_timer_delete(e3_timer_t *timer) {
    e3_timer_t *current;
    e3_timer_t *next;

    timer->function = 0;
    current = timers;
    timers = 0;

    while (current) {
        next = current->next;

        if (current != timer) {
            current->next = timers;
            timers = current;
        }

        current = next;
    }
}

