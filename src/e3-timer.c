/*
 * Copyright (c) 2013 - Christopher Baker - Confidential - All Rights Reserved
 *
 */

#include "../include/e3.h"

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
        else {
            current->function(current->cookie);
        }

        current = next;
    }

    return (timers != 0);
}

void
e3_timer_create(e3_timer_t *timer,
    e3_timer_ticks_t ticks, e3_timer_function_t function, void *cookie) {

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

