/*
 * Copyright (c) 2013 - Christopher Baker - Confidential - All Rights Reserved
 *
 */

#include "e3-timer-test.h"
#include "e3-hsm-test.h"
#include "jasmine.h"

int main(void) {
    jasmine_t jasmine;
    jasmine_init(&jasmine);

    e3_timer_test(&jasmine);
    e3_hsm_test(&jasmine);

    printf("jasmine: %u passed, %u failed, %u ignored, %u expects\r\n",
        jasmine.passed, jasmine.failed, jasmine.ignored, jasmine.expects);

    return jasmine.failed;
}

