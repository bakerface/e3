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
  - [e3_timer_interrupt](#void-e3_timer_interruptvoid)
  - [e3_timer_tick](#e3_timer_ticks_t-e3_timer_tickvoid)

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

### *void e3_timer_interrupt(void)*
This function increments the internal system timer by one clock tick. *Please note that this function should be called from a timer interrupt service routine at a predefined interval.*

``` c
static void
timer_isr(void) {
    e3_timer_interrupt();
}
```

### *e3_timer_ticks_t e3_timer_tick(void)*
This function uses the internal system timer to determine which (if any) timers have expired. If a timer has expired, the timer function is invoked and the timer is deleted. This function will return the idle time (in ticks) before the next timer is expected to expire, or zero if there are no timers scheduled. *Please note that this function should not be called from an interrupt service routine since there are no guarentees for its execution time. This function should be invoked at a predefined interval in the application.*

``` c
static int
main(void) {
    while (e3_timer_tick()) {
        puts("there are still timers pending");
    }
    
    puts("all timers have expired");
    return 0;
}
```
