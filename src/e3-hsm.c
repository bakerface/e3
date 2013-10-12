/*
 * Copyright (c) 2013 - Christopher Baker - Confidential - All Rights Reserved
 *
 */

#include "../include/e3.h"

static void
enter(e3_hsm_t *hsm, const e3_hsm_state_t * const state) {
    if (hsm->state != state) {
        enter(hsm, state->parent);
        hsm->state = state;
        hsm->state->enter(hsm->cookie);
    }
}

static void
leave(e3_hsm_t *hsm, unsigned long ancestry) {
    while (hsm->state && hsm->state->ancestry != ancestry) {
        hsm->state->exit(hsm->cookie);
        hsm->state = hsm->state->parent;
    }
}

void
e3_hsm_init(e3_hsm_t *hsm, const e3_hsm_state_t * const state, void *cookie) {
    hsm->state = 0;
    hsm->cookie = cookie;
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

