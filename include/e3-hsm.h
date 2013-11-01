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

#ifndef E3_HSM_H_
#define E3_HSM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define E3_PERMIT_NONE

#define E3_SIGNAL_AS_VOID(name)
#define E3_STATE_AS_VOID(name, enter, exit, permit)
#define E3_SUBSTATE_AS_VOID(parent, name, enter, exit, permit)
#define E3_PERMIT_AS_VOID(signal, state)

#define E3_SIGNAL_AS_ENUM(name) name,
#define E3_STATE_AS_ENUM(name, enter, exit, permit) E3_STATE_##name,
#define E3_SUBSTATE_AS_ENUM(parent, name, enter, exit, permit) E3_STATE_##name,

#define E3_STATE_AS_ANCESTRY_ENUM(name, enter, exit, permit) \
    E3_ANCESTRY_##name = (1 << E3_STATE_##name),

#define E3_SUBSTATE_AS_ANCESTRY_ENUM(parent, name, enter, exit, permit) \
    E3_ANCESTRY_##name = ((1 << E3_STATE_##name) | E3_ANCESTRY_##parent),

#define E3_STATE_AS_DECLARATION(name, enter, exit, permit) \
    static const e3_hsm_state_t *                          \
    name##_transition(e3_hsm_signal_t signal);             \
    static const e3_hsm_state_t name[1];

#define E3_SUBSTATE_AS_DECLARATION(parent, name, enter, exit, permit) \
    E3_STATE_AS_DECLARATION(name, enter, exit, permit)

#define E3_STATE_AS_FUNCTION(name, enter, exit, permit) \
    const e3_hsm_state_t *                              \
    name##_transition(e3_hsm_signal_t signal) {         \
        (void) name;                                    \
        switch (signal) {                               \
            permit                                      \
            default: break;                             \
        }                                               \
        return 0;                                       \
    }

#define E3_SUBSTATE_AS_FUNCTION(parent, name, enter, exit, permit)  \
    const e3_hsm_state_t *                                          \
    name##_transition(e3_hsm_signal_t signal) {                     \
        (void) name;                                                \
        switch (signal) {                                           \
            permit                                                  \
            default: break;                                         \
        }                                                           \
        return parent##_transition(signal);                         \
    }

#define E3_PERMIT_AS_CASE(signal, state) case signal: return state;

#define E3_STATE_AS_STRUCT(name, enter, exit, permit) \
    static const e3_hsm_state_t name[] = { {          \
        0,                                            \
        E3_ANCESTRY_##name,                           \
        name##_transition,                            \
        (e3_hsm_function_t) enter,                    \
        (e3_hsm_function_t) exit                      \
    } };

#define E3_SUBSTATE_AS_STRUCT(parent, name, enter, exit, permit) \
    static const e3_hsm_state_t name[] = { {                     \
        parent,                                                  \
        E3_ANCESTRY_##name,                                      \
        name##_transition,                                       \
        (e3_hsm_function_t) enter,                               \
        (e3_hsm_function_t) exit                                 \
    } };

#define E3_HSM_DEFINE(HSM)                                          \
    enum {                                                          \
        HSM(E3_SIGNAL_AS_VOID, E3_STATE_AS_ENUM,                    \
            E3_SUBSTATE_AS_ENUM, E3_PERMIT_AS_VOID)                 \
        HSM(E3_SIGNAL_AS_ENUM, E3_STATE_AS_VOID,                    \
            E3_SUBSTATE_AS_VOID, E3_PERMIT_AS_VOID)                 \
        HSM(E3_SIGNAL_AS_VOID, E3_STATE_AS_ANCESTRY_ENUM,           \
            E3_SUBSTATE_AS_ANCESTRY_ENUM, E3_PERMIT_AS_VOID)        \
        E3_END_OF_ENUM_##__LINE__                                   \
    };                                                              \
    HSM(E3_SIGNAL_AS_VOID, E3_STATE_AS_DECLARATION,                 \
        E3_SUBSTATE_AS_DECLARATION, E3_PERMIT_AS_VOID)              \
    HSM(E3_SIGNAL_AS_VOID, E3_STATE_AS_FUNCTION,                    \
        E3_SUBSTATE_AS_FUNCTION, E3_PERMIT_AS_CASE)                 \
    HSM(E3_SIGNAL_AS_VOID, E3_STATE_AS_STRUCT,                      \
        E3_SUBSTATE_AS_STRUCT, E3_PERMIT_AS_VOID)

typedef void (*e3_hsm_function_t)(void *cookie);
typedef unsigned long e3_hsm_signal_t;

typedef struct e3_hsm_state {
    const struct e3_hsm_state * const parent;
    const unsigned long ancestry;
    const struct e3_hsm_state * (*transition)(e3_hsm_signal_t signal);
    const e3_hsm_function_t enter;
    const e3_hsm_function_t exit;
} e3_hsm_state_t;

typedef struct e3_hsm {
    const e3_hsm_state_t *state;
    void *cookie;
} e3_hsm_t;

extern void
e3_hsm_init(e3_hsm_t *hsm, const e3_hsm_state_t * const state, void *cookie);

extern const e3_hsm_state_t *
e3_hsm_dispatch(e3_hsm_t *hsm, e3_hsm_signal_t signal);

#ifdef __cplusplus
}
#endif

#endif /* E3_HSM_H_ */

