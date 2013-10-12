# E3
E3 is a minimalistic freestanding architecture intended to jump-start bare-metal embedded C projects.
The goal of E3 is to do for ANSI C what Boost does for C++, but with a tiny footprint.

## Testing
To run the tests, you will need to install scons.
Scons is a replacement for make that takes a lot of the pain out of build scripts.

~~~ sh
git clone https://github.com/bakerface/e3.git
cd e3
scons
~~~

## Development guidelines
- All development must be test-driven.
- There must be 100% line, function, and branch coverage.
- No function may have a complexity higher than 3.
- If a function or object can be simplified, it should be.
- If ROM can be reduced, it should be.
- If RAM can be reduced, it must be.
- Functions and variables should be declared as static unless required to be global.
