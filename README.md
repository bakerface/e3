# E3

E3 is a minimalistic freestanding architecture intended to jump-start bare-metal embedded C projects. The goal of E3 is to provide a portable C framework with a tiny footprint.

## Table of Contents

- [Installation](#installation)
- [Getting the source](#getting-the-source)
- [Running the tests](#running-the-tests)
- [Checking code coverage](#checking-code-coverage)
- [Checking code complexity](#checking-code-complexity)
- [Creating an archive](#creating-an-archive)
- [Timer API](#timer-api)
  - [e3_timer_interrupt](#e3_timer_interrupt)
  - [e3_timer_tick](#e3_timer_tick)
  - [e3_timer_create](#e3_timer_create)
  - [e3_timer_delete](#e3_timer_delete)
  - [Timer example](#timer-example)
- [Hierarchical State Machine API](#hierarchical-state-machine-api)
  - [E3_HSM_DEFINE](#e3_hsm_define)
  - [e3_hsm_create](#e3_hsm_create)
  - [e3_hsm_dispatch](#e3_hsm_dispatch)
  - [e3_hsm_delete](#e3_hsm_delete)
  - [Sleep example](#sleep-example)

## Getting the source
To download the latest source, clone the GIT repository:

```
git clone https://github.com/bakerface/e3.git
```

This will create a directory named *e3* in your working directory.

## Running the tests
To execute the unit tests, run the following:

```
make
```

This will execute each test and print the test statistics to your console window.

## Checking code coverage
To generate code coverage statistics, run the following:

```
make coverage
```

This will generate a directory named *coverage* containing the code coverage statistics in HTML format. Simply open *index.html* in a web browser to view the coverage statistics. *Please note that each function must have 100% line, function, and branch coverage in order to be pushed to the repository.*

## Checking code complexity
To generate code complexity metrics, run the following:

```
make complexity
```

This will dump a table to your console window showing cyclomatic complexity and other useful statistics for each function. *Please note that each function must have a cyclomatic complexity less than five in order to be pushed to the repository.*

## Creating an archive
To generate a static archive of the code, run the following:

```
make archive
```

This will create a file named *libe3.a* in the working directory.

## Timer API
Below is the documentation for each of the timer functions, as well as a few examples showing how to use them.

### e3_timer_interrupt
This function increments the internal system timer by one clock tick. *Please note that this function should be called from a timer interrupt service routine at a predefined interval.*

### e3_timer_tick
This function uses the internal system timer to determine which (if any) timers have expired. If a timer has expired, the timer function is invoked and the timer is deleted. This function will return the idle time (in clock ticks) before the next timer is expected to expire, or zero if there are no timers scheduled. *Please note that this function should not be called from an interrupt service routine since there are no guarentees for its execution time. This function should be invoked at a predefined interval in the application.*

| Return           | Description                                       |
|:-----------------|:--------------------------------------------------|
| e3_timer_ticks_t | The idle time, or zero if no timers are scheduled |

### e3_timer_create
This function creates a timer that schedules a function to be called after the specified number of clock ticks has passed. *Please note that these are one-shot timers, which will be deleted automatically after they expire. To reschedule a timer, re-create the timer from within the timer function.*

| Parameter                    | Description                                                  |
|:-----------------------------|:-------------------------------------------------------------|
| e3_timer_t *timer            | The timer to create                                          |
| e3_timer_ticks_t ticks       | The number of clock ticks to wait before called the function |
| e3_timer_function_t function | The function to invoke                                       |
| void *cookie                 | The user-defined function argument                           |

### e3_timer_delete
This function deletes a previously created timer, preventing the timer function from being called.

| Parameter          | Description                                 |
|:-------------------|:--------------------------------------------|
| e3_timer_t *timer  | The timer to delete                         |

### Timer Example
Below is an example showing how to create and use timers.

``` c
#include <stdio.h>
#include <e3-timer.h>

static void
timer_isr(void) {
    e3_timer_interrupt();
}

static void
say(void *cookie) {
    puts((const char *) cookie);
}

static int
main(void) {
    e3_timer_t first, second;
    
    e3_timer_create(&first, 10, say, "this will never be called");
    e3_timer_delete(&first);
    
    e3_timer_create(&first, 20, say, "this will be called first");
    e3_timer_create(&second, 30, say, "this will be called second");

    while (e3_timer_tick()) {
        puts("there are still timers pending");
    }
    
    puts("all timers have expired");
    return 0;
}
```

## Hierarchical State Machine API
Below is the documentation for each of the hierarchical state machine functions, as well as a few examples showing how to use them.

### E3_HSM_DEFINE
This macro defines the structure of a hierarchical state machine in read-only memory.

| Parameter   | Description                                                    |
|:------------|:---------------------------------------------------------------|
| #define HSM | The macro containing the hierarchical state machine definition |

### e3_hsm_create
This function creates a new instance of a hierarchical state machine and transitions to the specified initial state.

| Parameter                          | Description                              |
|:-----------------------------------|:-----------------------------------------|
| hsm_t *hsm                         | The hierarchical state machine to create |
| const e3_hsm_state_t * const state | The initial state                        |

### e3_hsm_dispatch

This function dispatches the specified signal to the hierarchical state machine. If the signal was permitted for the current state, the hierarchical state machine transitions to, and returns, the destination state. If the signal was not permitted, then there is no state transition and NULL is returned. *Please note that when transitioning from one state to another, the least common ancestor of the two states is calculated. The exit function for each state is called in reverse order until the least common ancestor is reached, then the entrance function for each state is called in order until the destination state is reached.*

| Parameter              | Description                                |
|:-----------------------|:-------------------------------------------|
| e3_hsm_t *hsm          | The hierarchical state machine             |
| e3_hsm_signal_t signal | The signal to dispatch                     |

| Return                 | Description                                    |
|:-----------------------|:-----------------------------------------------|
| const e3_hsm_state_t * | The destination state or NULL if not permitted |

### e3_hsm_delete
This function deletes an instance of a hierarchical state machine and transitions out of the current state.


### Sleep Example
Below is an example showing how to define and use a hierarchical state machine.

``` c
#include <stdio.h>
#include <e3-hsm.h>

#define SLEEP_HSM(SIGNAL, STATE, SUBSTATE, PERMIT)             \
    SIGNAL(NOISE)                                              \
    SIGNAL(WHISPER)                                            \
    SIGNAL(SCREAM)                                             \
    STATE(AWAKE, awake_enter, awake_exit,                      \
        PERMIT(WHISPER, NODDING)                               \
        PERMIT(SCREAM,  AWAKE)                                 \
        PERMIT(SILENCE, NODDING))                              \
    SUBSTATE(AWAKE, NODDING, nodding_enter, nodding_exit,      \
        PERMIT(SILENCE, SLEEPING))                             \
    STATE(SLEEPING, sleeping_enter, sleeping_exit,             \
        PERMIT(WHISPER, SLEEPING)                              \
        PERMIT(SCREAM,  AWAKE)                                 \
        PERMIT(SILENCE, SNORING))                              \
    SUBSTATE(SLEEPING, SNORING, snoring_enter, snoring_exit,   \
        E3_PERMIT_NONE)

static void
awake_enter(e3_hsm_t *hsm) {
    puts("awake entered");
}

static void
awake_exit(e3_hsm_t *hsm) {
    puts("awake exited");
}

static void
nodding_enter(e3_hsm_t *hsm) {
    puts("nodding entered");
}

static void
nodding_exit(e3_hsm_t *hsm) {
    puts("nodding exited");
}

static void
sleeping_enter(e3_hsm_t *hsm) {
    puts("sleeping entered");
}

static void
sleeping_exit(e3_hsm_t *hsm) {
    puts("sleeping exited");
}

static void
snoring_enter(e3_hsm_t *hsm) {
    puts("snoring entered");
}

static void
snoring_exit(e3_hsm_t *hsm) {
    puts("snoring exited");
}

E3_HSM_DEFINE(SLEEP_HSM)

static int
main(void) {
    e3_hsm_t hsm;
    
    e3_hsm_create(&hsm, AWAKE);
    e3_hsm_dispatch(&hsm, WHISPER);
    e3_hsm_dispatch(&hsm, SILENCE);
    e3_hsm_dispatch(&hsm, SILENCE);
    e3_hsm_dispatch(&hsm, SCREAM);
    e3_hsm_delete(&hsm);
    
    return 0;
}
```
