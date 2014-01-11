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

#include "e3-event-test.h"
#include <e3-event.h>

typedef struct test {
    e3_event_t e;
    e3_event_listener_t a;
    e3_event_listener_t b;
    int count;
} test_t;

static void
callback(void *cookie, void *args) {
    int amount = (int) cookie;
    test_t *test = (test_t *) args;
    test->count += amount;
}

void
e3_event_test(jasmine_t *jasmine) {
    test_t test;

    jasmine_describe(jasmine, "an event") {
        jasmine_before(jasmine) {
            e3_event_create(&test.e);
            test.count = 0;
        }

        jasmine_after(jasmine) {
            e3_event_delete(&test.e);
        }

        jasmine_it(jasmine, "can have no listeners") {
            e3_event_fire(&test.e, 0);
            jasmine_expect(jasmine, test.count == 0);
        }

        jasmine_it(jasmine, "can have a single listener") {
            e3_event_listener_create(&test.a, &test.e, callback, (void *) 1);
            e3_event_fire(&test.e, &test);
            jasmine_expect(jasmine, test.count == 1);
        }

        jasmine_it(jasmine, "can have multiple listeners") {
            e3_event_listener_create(&test.a, &test.e, callback, (void *) 1);
            e3_event_listener_create(&test.b, &test.e, callback, (void *) 2);
            e3_event_fire(&test.e, &test);
            jasmine_expect(jasmine, test.count == 3);
        }

        jasmine_it(jasmine, "will ignore invalid listeners") {
            e3_event_listener_create(&test.a, &test.e, 0, 0);
            e3_event_fire(&test.e, &test);
            jasmine_expect(jasmine, test.count == 0);
        }

        jasmine_it(jasmine, "can fire multiple times") {
            e3_event_listener_create(&test.a, &test.e, callback, (void *) 1);
            e3_event_listener_create(&test.b, &test.e, callback, (void *) 2);
            e3_event_fire(&test.e, &test);
            jasmine_expect(jasmine, test.count == 3);
            e3_event_fire(&test.e, &test);
            jasmine_expect(jasmine, test.count == 6);
        }

        jasmine_it(jasmine, "can delete a listener") {
            e3_event_listener_create(&test.a, &test.e, callback, (void *) 1);
            e3_event_listener_create(&test.b, &test.e, callback, (void *) 2);
            e3_event_fire(&test.e, &test);
            jasmine_expect(jasmine, test.count == 3);
            e3_event_listener_delete(&test.b);
            e3_event_fire(&test.e, &test);
            jasmine_expect(jasmine, test.count == 4);
        }

        jasmine_it(jasmine, "cannot fire once deleted") {
            e3_event_listener_create(&test.a, &test.e, callback, (void *) 1);
            e3_event_listener_create(&test.b, &test.e, callback, (void *) 2);
            e3_event_fire(&test.e, &test);
            jasmine_expect(jasmine, test.count == 3);
            e3_event_delete(&test.e);
            e3_event_fire(&test.e, &test);
            jasmine_expect(jasmine, test.count == 3);
        }
    }
}

