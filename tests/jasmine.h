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

#ifndef JASMINE_H_
#define JASMINE_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define JASMINE_STATE_BEFORE   0
#define JASMINE_STATE_IT       1
#define JASMINE_STATE_AFTER    2
#define JASMINE_STATE_FINISHED 3

#define JASMINE_GROUP_FAILED   0
#define JASMINE_GROUP_PASSED   1
#define JASMINE_GROUP_IGNORED  2

#define jasmine_init(jasmine) do { \
    (jasmine)->state = JASMINE_STATE_BEFORE; \
    (jasmine)->group = JASMINE_GROUP_IGNORED; \
    (jasmine)->current = 0; \
    (jasmine)->last = 0; \
    (jasmine)->passed = 0; \
    (jasmine)->failed = 0; \
    (jasmine)->ignored = 0; \
    (jasmine)->expects = 0; \
    (jasmine)->reason = 0; \
} while (0)

#define jasmine_describe(jasmine, what) \
    for ((jasmine)->state = JASMINE_STATE_BEFORE, \
            (jasmine)->current = 0, \
            (jasmine)->last = 0, \
            puts(what); \
        (JASMINE_STATE_FINISHED == (jasmine)->state) ? (puts(""), 0) : 1; )

#define jasmine_before(jasmine) \
    for (; JASMINE_STATE_BEFORE == (jasmine)->state; \
        (jasmine)->state = JASMINE_STATE_IT)

#define jasmine_it(jasmine, should) \
    for ((jasmine)->group = JASMINE_GROUP_IGNORED, \
            (jasmine)->last = (unsigned short) ((jasmine)->last < __LINE__ \
            ? __LINE__ : (jasmine)->last); \
        JASMINE_STATE_IT == (jasmine)->state \
            && (jasmine)->current < __LINE__ \
            && (__LINE__ == ((jasmine)->current = __LINE__)); \
        (jasmine)->state = JASMINE_STATE_AFTER, \
            ((jasmine)->group == JASMINE_GROUP_IGNORED \
            ? ((jasmine)->ignored++, \
                puts(" ! " should), JASMINE_GROUP_IGNORED) \
            : ((jasmine)->group == JASMINE_GROUP_PASSED \
                ? ((jasmine)->passed++, \
                    puts(" ✓ " should), JASMINE_GROUP_PASSED) \
                : ((jasmine)->failed++, \
                    printf(" ✗ " should ": expected %s\r\n", \
                        (jasmine)->reason), JASMINE_GROUP_FAILED))))

#define jasmine_after(jasmine) \
    for (; JASMINE_STATE_AFTER == (jasmine)->state; \
        (jasmine)->state = ((jasmine)->current == (jasmine)->last) \
            ? JASMINE_STATE_FINISHED : JASMINE_STATE_BEFORE)

#define jasmine_expect(jasmine, condition) \
    if (!(condition)) { \
        (jasmine)->expects++; \
        (jasmine)->group = JASMINE_GROUP_FAILED; \
        (jasmine)->reason = #condition; \
        continue; \
    } \
    else { \
        (jasmine)->group = JASMINE_GROUP_PASSED; \
        (jasmine)->expects++; \
    }

typedef struct jasmine {
    const char *reason;
    unsigned short state;
    unsigned short group;
    unsigned short current;
    unsigned short last;
    unsigned short passed;
    unsigned short failed;
    unsigned short ignored;
    unsigned short expects;
} jasmine_t;

#ifdef __cplusplus
}
#endif

#endif /* JASMINE_H_ */

