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

#include "e3-timer-test.h"
#include <e3-timer.h>

typedef struct test {
    e3_timer_t timer_1;
    e3_timer_t timer_2;
    unsigned int counter;
} test_t;

static void
increment(test_t *test) {
    test->counter++;
}

static void
triple(test_t *test) {
    test->counter *= 3;
}

static void
reschedule(test_t *test) {
    test->counter++;

    e3_timer_create(&test->timer_1, 0,
        (e3_timer_function_t) reschedule, test);
}

void
e3_timer_test(jasmine_t *jasmine) {
    test_t test;

    jasmine_describe(jasmine, "the system timer") {
        jasmine_before(jasmine) {
            test.counter = 0;
        }

        jasmine_after(jasmine) {

        }

        jasmine_it(jasmine, "can tick without any timers created") {
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 0);
        }

        jasmine_it(jasmine, "does not require an interrupt for a zero tick") {
            e3_timer_create(&test.timer_1, 0,
                (e3_timer_function_t) increment, &test);

            jasmine_expect(jasmine, test.counter == 0);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 1);
        }

        jasmine_it(jasmine, "can have multiple timers with the same ticks") {
            e3_timer_create(&test.timer_1, 0,
                (e3_timer_function_t) increment, &test);

            e3_timer_create(&test.timer_2, 0,
                (e3_timer_function_t) increment, &test);

            jasmine_expect(jasmine, test.counter == 0);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 2);
        }

        jasmine_it(jasmine, "will ignore invalid timer functions") {
            e3_timer_create(&test.timer_1, 0, 0, 0);
            jasmine_expect(jasmine, test.counter == 0);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 0);
        }

        jasmine_it(jasmine, "can delete a timer that has been created") {
            e3_timer_create(&test.timer_1, 0,
                (e3_timer_function_t) triple, &test);

            e3_timer_create(&test.timer_2, 0,
                (e3_timer_function_t) increment, &test);

            jasmine_expect(jasmine, test.counter == 0);
            e3_timer_delete(&test.timer_1);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 1);
        }

        jasmine_it(jasmine, "can delete a timer that has not been created") {
            e3_timer_delete(&test.timer_1);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 0);
        }

        jasmine_it(jasmine, "can tick faster than the interrupt") {
            e3_timer_create(&test.timer_1, 1,
                (e3_timer_function_t) increment, &test);

            jasmine_expect(jasmine, test.counter == 0);
            jasmine_expect(jasmine, e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 0);
            jasmine_expect(jasmine, e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 0);
            e3_timer_interrupt();
            jasmine_expect(jasmine, test.counter == 0);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 1);
        }

        jasmine_it(jasmine, "can tick slower than the interrupt") {
            e3_timer_create(&test.timer_1, 2,
                (e3_timer_function_t) triple, &test);

            e3_timer_create(&test.timer_2, 1,
                (e3_timer_function_t) increment, &test);

            jasmine_expect(jasmine, test.counter == 0);
            e3_timer_interrupt();
            e3_timer_interrupt();
            e3_timer_interrupt();
            e3_timer_interrupt();
            jasmine_expect(jasmine, test.counter == 0);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 3);
        }

        jasmine_it(jasmine, "can create a timer within a timer function") {
            e3_timer_create(&test.timer_1, 0,
                (e3_timer_function_t) reschedule, &test);

            jasmine_expect(jasmine, test.counter == 0);
            jasmine_expect(jasmine, e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 1);
            jasmine_expect(jasmine, e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 2);
            e3_timer_delete(&test.timer_1);
            jasmine_expect(jasmine, !e3_timer_tick());
            jasmine_expect(jasmine, test.counter == 2);
        }
    }
}

