/*
 * Copyright (c) 2013 - Christopher Baker - Confidential - All Rights Reserved
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

typedef struct jasmine {
    unsigned char state;
    unsigned char group;
    unsigned short current;
    unsigned short last;
    unsigned short passed;
    unsigned short failed;
    unsigned short ignored;
    unsigned short expects;
    const char *reason;
} jasmine_t;

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

#ifdef __cplusplus
}
#endif

#endif /* JASMINE_H_ */

