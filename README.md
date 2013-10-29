# E3
E3 is a minimalistic freestanding architecture intended to jump-start bare-metal embedded C projects.
The goal of E3 is to provide a portable C framework with a tiny footprint.

## Testing
The test suite is integrated into the build system.
To run the tests, simply clone the repository and run make as follows:

~~~
git clone https://github.com/bakerface/e3.git
cd e3
make
~~~

There are additional build targets that you may specify.
A few examples are:

- 'archive' to create a static library of the source
- 'complexity' to print the cyclomatic complexity statistics
- 'coverage' to run the tests and generate code coverage statistics

## Coding guidelines
- All source code should be as portable and strict as possible.
- All source code should use (4) spaces instead of tabs.
- A single line of source must be 80 columns wide or less.
- Function modifiers and return types must be line separated from the function name and arguments.
- There must be 100% line, function, and branch coverage.
- No function may have a complexity higher than 3.
- If a function or object can be simplified, it should be.
- If ROM can be reduced, it should be.
- If RAM can be reduced, it must be.
- Functions and variables should be declared as static unless required to be global.
