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

#include <e3-hsm.h>

#define INVALID_STATE 0
#define ANCESTRY_NONE 0UL

static void
enter(e3_hsm_t *hsm, const e3_hsm_state_t * const state) {
    if (hsm->state != state) {
        enter(hsm, state->parent);
        hsm->state = state;
        hsm->state->enter(hsm);
    }
}

static void
leave(e3_hsm_t *hsm, unsigned long ancestry) {
    while (hsm->state && hsm->state->ancestry != ancestry) {
        hsm->state->exit(hsm);
        hsm->state = hsm->state->parent;
    }
}

void
e3_hsm_create(e3_hsm_t *hsm, const e3_hsm_state_t * const state) {
    hsm->state = INVALID_STATE;
    enter(hsm, state);
}

const e3_hsm_state_t *
e3_hsm_dispatch(e3_hsm_t *hsm, e3_hsm_signal_t signal) {
    const e3_hsm_state_t *to;
    
    to = hsm->state->transition(signal);

    if (to) {
        leave(hsm, hsm->state->ancestry & to->ancestry);
        enter(hsm, to);
    }

    return to;
}

void
e3_hsm_delete(e3_hsm_t *hsm) {
    leave(hsm, ANCESTRY_NONE);
}
