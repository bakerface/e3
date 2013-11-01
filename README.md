# README
E3 is a minimalistic freestanding architecture intended to jump-start bare-metal embedded C projects.
The goal of E3 is to provide a portable C framework with a tiny footprint.

## Building and testing
The test suite and the build system are coupled in a Makefile.
To clone the project, build it, and run the test suite, run the following commands:

~~~
git clone https://github.com/bakerface/e3.git
cd e3
make
~~~

There are additional build targets that you may specify to make.
A few examples are:

- 'make archive' to create a static library of the source
- 'make complexity' to print the cyclomatic complexity statistics
- 'make coverage' to run the tests and generate code coverage statistics (default)

## Guidelines

### Minimalism and simplicity
- If a function or object can be simplified, it should be.
- If ROM can be reduced, it should be.
- If RAM can be reduced, it must be.

### Style and formatting
- Source code must use (4) spaces instead of tabs.
- A single line of source must be 80 columns wide or less.
- Function modifiers and return types must be line separated from the function name and arguments.

### Portability and maintainability
- Source code should be as portable and strict as possible.
- There must be 100% line, function, and branch coverage.
- All functions must have a complexity less than four.
- Functions and variables should be declared as static unless required to be global.


