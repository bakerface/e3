/*
 * Copyright (c) 2013 - Christopher Baker - Confidential - All Rights Reserved
 *
 */

#include "e3-timer-test.h"
#include "../include/e3.h"

typedef struct test_cookie {
    e3_timer_t timers[2];
    unsigned int counter;
} test_cookie_t;

static void increment(test_cookie_t *cookie) {
    cookie->counter++;
}

static void triple(test_cookie_t *cookie) {
    cookie->counter *= 3;
}

static void reschedule(test_cookie_t *cookie) {
    cookie->counter++;
    e3_timer_create(cookie->timers, 0, (e3_timer_function_t) reschedule, cookie);
}

void
e3_timer_test(jasmine_t *jasmine) {
    test_cookie_t cookie;

    jasmine_describe(jasmine, "the system timer") {
        jasmine_before(jasmine) {
            cookie.counter = 0;
        }

        jasmine_after(jasmine) {
        
        }

        jasmine_it(jasmine, "can tick without any timers created") {
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 0);
        }
        
        jasmine_it(jasmine, "does not require an interrupt for a zero tick") {
            e3_timer_create(cookie.timers, 0,
                (e3_timer_function_t) increment, &cookie);

            jasmine_expect(jasmine, cookie.counter == 0);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 1);
        }
        
        jasmine_it(jasmine, "can have multiple timers with the same ticks") {
            e3_timer_create(cookie.timers, 0,
                (e3_timer_function_t) increment, &cookie);
                
            e3_timer_create(cookie.timers + 1, 0,
                (e3_timer_function_t) increment, &cookie);
                
            jasmine_expect(jasmine, cookie.counter == 0);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 2);
        }
        
        jasmine_it(jasmine, "can delete a timer") {
            e3_timer_create(cookie.timers, 0,
                (e3_timer_function_t) triple, &cookie);
                
            e3_timer_create(cookie.timers + 1,
                0, (e3_timer_function_t) increment, &cookie);
                
            jasmine_expect(jasmine, cookie.counter == 0);
            e3_timer_delete(cookie.timers);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 1);
        }
        
        jasmine_it(jasmine, "can tick faster than the interrupt") {
            e3_timer_create(cookie.timers, 1,
                (e3_timer_function_t) increment, &cookie);
                
            jasmine_expect(jasmine, cookie.counter == 0);
            jasmine_expect(jasmine, e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 0);
            jasmine_expect(jasmine, e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 0);
            e3_timer_interrupt();
            jasmine_expect(jasmine, cookie.counter == 0);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 1);
        }
        
        jasmine_it(jasmine, "can tick slower than the interrupt") {
            e3_timer_create(cookie.timers, 2,
                (e3_timer_function_t) triple, &cookie);
                
            e3_timer_create(cookie.timers + 1, 1,
                (e3_timer_function_t) increment, &cookie);
                
            jasmine_expect(jasmine, cookie.counter == 0);
            e3_timer_interrupt();
            e3_timer_interrupt();
            e3_timer_interrupt();
            e3_timer_interrupt();
            jasmine_expect(jasmine, cookie.counter == 0);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 3);
        }
        
        jasmine_it(jasmine, "can create a timer within a timer function") {
            e3_timer_create(cookie.timers, 0,
                (e3_timer_function_t) reschedule, &cookie);
                
            jasmine_expect(jasmine, cookie.counter == 0);
            jasmine_expect(jasmine, e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 1);
            jasmine_expect(jasmine, e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 2);
            e3_timer_delete(cookie.timers);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, cookie.counter == 2);
        }
    }
}

