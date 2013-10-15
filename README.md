# E3
E3 is a minimalistic freestanding architecture intended to jump-start bare-metal embedded C projects.
The goal of E3 is to provide a portable C framework with a tiny footprint.

## Testing
To run the tests, you will need to install scons.
Scons is a replacement for make that takes a lot of the pain out of build scripts.

~~~ bash
git clone https://github.com/bakerface/e3.git
cd e3
scons
~~~

## Coding guidelines
- All source code should be as portable and strict as possible.
- All source code should use (4) spaces instead of tabs.
- Function modifiers and return types must be line separated from the function name and arguments.
- There must be 100% line, function, and branch coverage.
- No function may have a complexity higher than 3.
- If a function or object can be simplified, it should be.
- If ROM can be reduced, it should be.
- If RAM can be reduced, it must be.
- Functions and variables should be declared as static unless required to be global.
