/*
 * Copyright (c) 2013 - Christopher Baker - Confidential - All Rights Reserved
 *
 */

#ifndef E3_TIMER_H_
#define E3_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long e3_timer_ticks_t;
typedef void (*e3_timer_function_t)(void *cookie);

typedef struct e3_timer {
    struct e3_timer *next;
    e3_timer_ticks_t ticks;
    e3_timer_function_t function;
    void *cookie;
} e3_timer_t;

extern void
e3_timer_interrupt(void);

extern e3_timer_ticks_t
e3_timer_tick(void);

extern void
e3_timer_create(e3_timer_t *timer,
    e3_timer_ticks_t ticks, e3_timer_function_t function, void *cookie);

extern void
e3_timer_delete(e3_timer_t *timer);

#ifdef __cplusplus
}
#endif

#endif /* E3_TIMER_H_ */

