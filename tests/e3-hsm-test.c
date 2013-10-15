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

#include "e3-hsm-test.h"
#include <e3.h>

#define PHONE_HSM(SIGNAL, STATE, SUBSTATE, PERMIT)             \
    SIGNAL(PICK_UP)                                            \
    SIGNAL(DIAL)                                               \
    SIGNAL(ANSWER)                                             \
    SIGNAL(MISS_CALL)                                          \
    SIGNAL(BEEP)                                               \
    SIGNAL(HANG_UP)                                            \
    STATE(IDLE, idle_enter, idle_exit,                         \
        PERMIT(PICK_UP, DIALTONE))                             \
    STATE(BUSY, busy_enter, busy_exit,                         \
        PERMIT(HANG_UP, IDLE))                                 \
    SUBSTATE(BUSY, DIALTONE, dialtone_enter, dialtone_exit,    \
        PERMIT(DIAL, RINGING))                                 \
    SUBSTATE(BUSY, RINGING, ringing_enter, ringing_exit,       \
        PERMIT(ANSWER, TALKING)                                \
        PERMIT(MISS_CALL, VOICEMAIL))                          \
    SUBSTATE(BUSY, TALKING, talking_enter, talking_exit,       \
        PERMIT(BEEP, TALKING))                                 \
    SUBSTATE(BUSY, VOICEMAIL, voicemail_enter, voicemail_exit, \
        E3_PERMIT_NONE)

typedef struct phone {
    e3_hsm_t hsm;
    unsigned char idle_entered;
    unsigned char idle_exited;
    unsigned char busy_entered;
    unsigned char busy_exited;
    unsigned char dialtone_entered;
    unsigned char dialtone_exited;
    unsigned char ringing_entered;
    unsigned char ringing_exited;
    unsigned char talking_entered;
    unsigned char talking_exited;
    unsigned char voicemail_entered;
    unsigned char voicemail_exited;
} phone_t;

static void
idle_enter(phone_t *phone) {
    phone->idle_entered++;
}

static void
idle_exit(phone_t *phone) {
    phone->idle_exited++;
}

static void
busy_enter(phone_t *phone) {
    phone->busy_entered++;
}

static void
busy_exit(phone_t *phone) {
    phone->busy_exited++;
}

static void
dialtone_enter(phone_t *phone) {
    phone->dialtone_entered++;
}

static void
dialtone_exit(phone_t *phone) {
    phone->dialtone_exited++;
}

static void
ringing_enter(phone_t *phone) {
    phone->ringing_entered++;
}

static void
ringing_exit(phone_t *phone) {
    phone->ringing_exited++;
}

static void
talking_enter(phone_t *phone) {
    phone->talking_entered++;
}

static void
talking_exit(phone_t *phone) {
    phone->talking_exited++;
}

static void
voicemail_enter(phone_t *phone) {
    phone->voicemail_entered++;
}

static void
voicemail_exit(phone_t *phone) {
    phone->voicemail_exited++;
}

E3_HSM_DEFINE(PHONE_HSM)

void
e3_hsm_test(jasmine_t *jasmine) {
    phone_t phone;
    
    jasmine_describe(jasmine, "a hierarchical state machine") {
        jasmine_before(jasmine) {
            phone.idle_entered = 0;
            phone.idle_exited = 0;
            phone.busy_entered = 0;
            phone.busy_exited = 0;
            phone.dialtone_entered = 0;
            phone.dialtone_exited = 0;
            phone.ringing_entered = 0;
            phone.ringing_exited = 0;
            phone.talking_entered = 0;
            phone.talking_exited = 0;
            phone.voicemail_entered = 0;
            phone.voicemail_exited = 0;
        }

        jasmine_after(jasmine) {
        
        }

        jasmine_it(jasmine, "can initialize to a child state") {
            e3_hsm_init(&phone.hsm, VOICEMAIL, &phone);
            
            jasmine_expect(jasmine, phone.idle_entered == 0);
            jasmine_expect(jasmine, phone.idle_exited == 0);
            jasmine_expect(jasmine, phone.busy_entered == 1);
            jasmine_expect(jasmine, phone.busy_exited == 0);
            jasmine_expect(jasmine, phone.dialtone_entered == 0);
            jasmine_expect(jasmine, phone.dialtone_exited == 0);
            jasmine_expect(jasmine, phone.ringing_entered == 0);
            jasmine_expect(jasmine, phone.ringing_exited == 0);
            jasmine_expect(jasmine, phone.talking_entered == 0);
            jasmine_expect(jasmine, phone.talking_exited == 0);
            jasmine_expect(jasmine, phone.voicemail_entered == 1);
            jasmine_expect(jasmine, phone.voicemail_exited == 0);
        }
        
        jasmine_it(jasmine, "can initialize to a parent state") {
            e3_hsm_init(&phone.hsm, IDLE, &phone);
            
            jasmine_expect(jasmine, phone.idle_entered == 1);
            jasmine_expect(jasmine, phone.idle_exited == 0);
            jasmine_expect(jasmine, phone.busy_entered == 0);
            jasmine_expect(jasmine, phone.busy_exited == 0);
            jasmine_expect(jasmine, phone.dialtone_entered == 0);
            jasmine_expect(jasmine, phone.dialtone_exited == 0);
            jasmine_expect(jasmine, phone.ringing_entered == 0);
            jasmine_expect(jasmine, phone.ringing_exited == 0);
            jasmine_expect(jasmine, phone.talking_entered == 0);
            jasmine_expect(jasmine, phone.talking_exited == 0);
            jasmine_expect(jasmine, phone.voicemail_entered == 0);
            jasmine_expect(jasmine, phone.voicemail_exited == 0);
        }
    
        jasmine_it(jasmine, "can transition to a substate") {
            jasmine_expect(jasmine,
                e3_hsm_dispatch(&phone.hsm, PICK_UP) == DIALTONE);
                
            jasmine_expect(jasmine, phone.idle_entered == 0);
            jasmine_expect(jasmine, phone.idle_exited == 1);
            jasmine_expect(jasmine, phone.busy_entered == 1);
            jasmine_expect(jasmine, phone.busy_exited == 0);
            jasmine_expect(jasmine, phone.dialtone_entered == 1);
            jasmine_expect(jasmine, phone.dialtone_exited == 0);
            jasmine_expect(jasmine, phone.ringing_entered == 0);
            jasmine_expect(jasmine, phone.ringing_exited == 0);
            jasmine_expect(jasmine, phone.talking_entered == 0);
            jasmine_expect(jasmine, phone.talking_exited == 0);
            jasmine_expect(jasmine, phone.voicemail_entered == 0);
            jasmine_expect(jasmine, phone.voicemail_exited == 0);
        }
    
        jasmine_it(jasmine, "cannot transition if a signal is undefined") {
            jasmine_expect(jasmine,
                !e3_hsm_dispatch(&phone.hsm, PICK_UP));
            
            jasmine_expect(jasmine, phone.idle_entered == 0);
            jasmine_expect(jasmine, phone.idle_exited == 0);
            jasmine_expect(jasmine, phone.busy_entered == 0);
            jasmine_expect(jasmine, phone.busy_exited == 0);
            jasmine_expect(jasmine, phone.dialtone_entered == 0);
            jasmine_expect(jasmine, phone.dialtone_exited == 0);
            jasmine_expect(jasmine, phone.ringing_entered == 0);
            jasmine_expect(jasmine, phone.ringing_exited == 0);
            jasmine_expect(jasmine, phone.talking_entered == 0);
            jasmine_expect(jasmine, phone.talking_exited == 0);
            jasmine_expect(jasmine, phone.voicemail_entered == 0);
            jasmine_expect(jasmine, phone.voicemail_exited == 0);
        }
    
        jasmine_it(jasmine, "can transition to a sibling state") {
            jasmine_expect(jasmine,
                e3_hsm_dispatch(&phone.hsm, DIAL) == RINGING);
                
            jasmine_expect(jasmine, phone.idle_entered == 0);
            jasmine_expect(jasmine, phone.idle_exited == 0);
            jasmine_expect(jasmine, phone.busy_entered == 0);
            jasmine_expect(jasmine, phone.busy_exited == 0);
            jasmine_expect(jasmine, phone.dialtone_entered == 0);
            jasmine_expect(jasmine, phone.dialtone_exited == 1);
            jasmine_expect(jasmine, phone.ringing_entered == 1);
            jasmine_expect(jasmine, phone.ringing_exited == 0);
            jasmine_expect(jasmine, phone.talking_entered == 0);
            jasmine_expect(jasmine, phone.talking_exited == 0);
            jasmine_expect(jasmine, phone.voicemail_entered == 0);
            jasmine_expect(jasmine, phone.voicemail_exited == 0);
        }
        
        jasmine_it(jasmine, "invokes entry and exit when changing states") {
            jasmine_expect(jasmine,
                e3_hsm_dispatch(&phone.hsm, ANSWER) == TALKING);
                
            jasmine_expect(jasmine, phone.idle_entered == 0);
            jasmine_expect(jasmine, phone.idle_exited == 0);
            jasmine_expect(jasmine, phone.busy_entered == 0);
            jasmine_expect(jasmine, phone.busy_exited == 0);
            jasmine_expect(jasmine, phone.dialtone_entered == 0);
            jasmine_expect(jasmine, phone.dialtone_exited == 0);
            jasmine_expect(jasmine, phone.ringing_entered == 0);
            jasmine_expect(jasmine, phone.ringing_exited == 1);
            jasmine_expect(jasmine, phone.talking_entered == 1);
            jasmine_expect(jasmine, phone.talking_exited == 0);
            jasmine_expect(jasmine, phone.voicemail_entered == 0);
            jasmine_expect(jasmine, phone.voicemail_exited == 0);
        }
        
        jasmine_it(jasmine, "does not invoke when not changing states") {
            jasmine_expect(jasmine,
                e3_hsm_dispatch(&phone.hsm, BEEP) == TALKING);
                
            jasmine_expect(jasmine, phone.idle_entered == 0);
            jasmine_expect(jasmine, phone.idle_exited == 0);
            jasmine_expect(jasmine, phone.busy_entered == 0);
            jasmine_expect(jasmine, phone.busy_exited == 0);
            jasmine_expect(jasmine, phone.dialtone_entered == 0);
            jasmine_expect(jasmine, phone.dialtone_exited == 0);
            jasmine_expect(jasmine, phone.ringing_entered == 0);
            jasmine_expect(jasmine, phone.ringing_exited == 0);
            jasmine_expect(jasmine, phone.talking_entered == 0);
            jasmine_expect(jasmine, phone.talking_exited == 0);
            jasmine_expect(jasmine, phone.voicemail_entered == 0);
            jasmine_expect(jasmine, phone.voicemail_exited == 0);
        }
        
        jasmine_it(jasmine, "inherits signals from parent states") {
            jasmine_expect(jasmine,
                e3_hsm_dispatch(&phone.hsm, HANG_UP) == IDLE);
                
            jasmine_expect(jasmine, phone.idle_entered == 1);
            jasmine_expect(jasmine, phone.idle_exited == 0);
            jasmine_expect(jasmine, phone.busy_entered == 0);
            jasmine_expect(jasmine, phone.busy_exited == 1);
            jasmine_expect(jasmine, phone.dialtone_entered == 0);
            jasmine_expect(jasmine, phone.dialtone_exited == 0);
            jasmine_expect(jasmine, phone.ringing_entered == 0);
            jasmine_expect(jasmine, phone.ringing_exited == 0);
            jasmine_expect(jasmine, phone.talking_entered == 0);
            jasmine_expect(jasmine, phone.talking_exited == 1);
            jasmine_expect(jasmine, phone.voicemail_entered == 0);
            jasmine_expect(jasmine, phone.voicemail_exited == 0);
        }
    }
}

