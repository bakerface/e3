#
# Copyright (c) 2013, 2014 - Christopher M. Baker
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#
#

CC       := gcc
CCTARGET := libe3.a
CCTEST   := test
CCFILES  := $(wildcard src/*.c)
CCTFILES := $(wildcard tests/*.c)

SRCFILES := $(wildcard include/*.h) \
            $(wildcard src/*.c) \
            $(wildcard tests/*.h) \
            $(wildcard tests/*.c)

CCFLAGS  := -ansi \
            -ffreestanding \
            -fmessage-length=0 \
            -nodefaultlibs \
            -pedantic \
            -pedantic-errors \
            -Waddress \
            -Waggregate-return \
            -Wall \
            -Warray-bounds \
            -Wbad-function-cast \
            -Wcast-align \
            -Wcast-qual \
            -Wchar-subscripts \
            -Wclobbered \
            -Wcomment \
            -Wconversion \
            -Wdeclaration-after-statement \
            -Wdisabled-optimization \
            -Wdouble-promotion \
            -Wempty-body \
            -Wenum-compare \
            -Werror \
            -Wextra \
            -Wfatal-errors \
            -Wfloat-equal \
            -Wformat \
            -Wformat=2 \
            -Wformat-nonliteral \
            -Wformat-security \
            -Wformat-y2k \
            -Wignored-qualifiers \
            -Wimplicit \
            -Wimplicit-function-declaration \
            -Wimplicit-int \
            -Winit-self \
            -Winline \
            -Winvalid-pch \
            -Wjump-misses-init \
            -Wlogical-op \
            -Wlong-long \
            -Wmain \
            -Wmaybe-uninitialized \
            -Wmissing-braces \
            -Wmissing-declarations \
            -Wmissing-field-initializers \
            -Wmissing-include-dirs \
            -Wmissing-parameter-type \
            -Wmissing-prototypes \
            -Wnested-externs \
            -Wnonnull \
            -Wold-style-declaration \
            -Wold-style-definition \
            -Woverlength-strings \
            -Woverride-init \
            -Wpacked \
            -Wpacked-bitfield-compat \
            -Wpadded \
            -Wparentheses \
            -Wpointer-arith \
            -Wpointer-sign \
            -Wredundant-decls \
            -Wreturn-type \
            -Wsequence-point \
            -Wshadow \
            -Wsign-compare \
            -Wsign-conversion \
            -Wstack-protector \
            -Wstrict-aliasing \
            -Wstrict-overflow \
            -Wstrict-prototypes \
            -Wswitch \
            -Wswitch-default \
            -Wswitch-enum \
            -Wsync-nand \
            -Wsystem-headers \
            -Wtraditional-conversion \
            -Wtrampolines \
            -Wtrigraphs \
            -Wtype-limits \
            -Wuninitialized \
            -Wunknown-pragmas \
            -Wunsafe-loop-optimizations \
            -Wunsuffixed-float-constants \
            -Wunused \
            -Wunused-but-set-parameter \
            -Wunused-but-set-variable \
            -Wunused-function \
            -Wunused-label \
            -Wunused-local-typedefs \
            -Wunused-parameter \
            -Wunused-value \
            -Wunused-variable \
            -Wvariadic-macros \
            -Wvector-operation-performance \
            -Wvla \
            -Wvolatile-register-var \
            -Wwrite-strings

CCTFLAGS := $(CCFLAGS) \
            -fprofile-arcs \
            -ftest-coverage \
            -g \
            -O0

CCPATH   := -Iinclude

CCOBJS   := $(CCFILES:.c=.o)
CCTOBJS  := $(CCFILES:.c=.to) \
            $(CCTFILES:.c=.o)

CCTCOV   := $(CCTEST).cov
GCOVOBJS := $(CCFILES:.c=.gcno) $(CCFILES:.c=.gcda)
LIBS     := -lgcov

TYPE_FILE  := $(shell echo $(type) | tr ' ' '-')
TYPE_VAR   := $(shell echo $(type) | tr ' ' '_')
TYPE_MACRO := $(shell echo $(TYPE_VAR) | tr 'a-z' 'A-Z')

.PHONY: all
all: coverage

.PHONY: clean
clean:
	@rm -f $(CCTARGET) $(CCOBJS) $(CCTEST) $(CCTOBJS) $(CCTCOV) $(GCOVOBJS)
	@rm -rf coverage

.PHONY: archive
archive: $(CCTARGET)

coverage: $(CCTCOV)
	@genhtml -o $@ $< >/dev/null

.PHONY: complexity
complexity: $(CCFILES)
	@pmccabe -v -c $^

.PHONY: size
size: $(CCTARGET)
	@size $<

.PHONY: tidy
tidy: $(SRCFILES)
	@sed -i 's/\s*$$/'"`echo \\\r`/" $^

.PHONY: template
template:
	@echo include/e3-$(TYPE_FILE).h
	@cp templates/include.h include/e3-$(TYPE_FILE).h
	
	@echo src/e3-$(TYPE_FILE).c
	@cp templates/source.c src/e3-$(TYPE_FILE).c
	
	@echo tests/e3-$(TYPE_FILE)-test.h
	@cp templates/test.h tests/e3-$(TYPE_FILE)-test.h
	
	@echo tests/e3-$(TYPE_FILE)-test.c
	@cp templates/test.c tests/e3-$(TYPE_FILE)-test.c
	
	@sed -i 's/##FILE##/$(TYPE_FILE)/g' \
		include/e3-$(TYPE_FILE).h \
		src/e3-$(TYPE_FILE).c \
		tests/e3-$(TYPE_FILE)-test.h \
		tests/e3-$(TYPE_FILE)-test.c
		
	@sed -i 's/##VAR##/$(TYPE_VAR)/g' \
		include/e3-$(TYPE_FILE).h \
		src/e3-$(TYPE_FILE).c \
		tests/e3-$(TYPE_FILE)-test.h \
		tests/e3-$(TYPE_FILE)-test.c
	    
	@sed -i 's/##MACRO##/$(TYPE_MACRO)/g' \
		include/e3-$(TYPE_FILE).h \
		src/e3-$(TYPE_FILE).c \
		tests/e3-$(TYPE_FILE)-test.h \
		tests/e3-$(TYPE_FILE)-test.c
		
	@sed -i 's/##TYPE##/$(type)/g' \
		include/e3-$(TYPE_FILE).h \
		src/e3-$(TYPE_FILE).c \
		tests/e3-$(TYPE_FILE)-test.h \
		tests/e3-$(TYPE_FILE)-test.c
	
	@echo tests/e3-test.c
	@sed -i '/#include "jasmine.h"/i#include "e3-$(TYPE_FILE)-test.h"'"`echo \\\r`" tests/e3-test.c
	    
	@sed -i '/'"`cat tests/e3-test.c | grep '_test(' | tail -1`"'/a\ \ \ \ e3_$(TYPE_VAR)_test(&jasmine);'"`echo \\\r`" tests/e3-test.c

%.o: %.c
	@echo CC $@
	@$(CC) -o $@ -c $(CCFLAGS) $(CCPATH) $<

%.to: %.c
	@echo CC $@
	@$(CC) -o $@ -c $(CCTFLAGS) $(CCPATH) $<

$(CCTCOV): $(CCTEST)
	@./$<
	@lcov -b . -d . -c -o $@ >/dev/null

$(CCTEST): $(CCTOBJS)
	@$(CC) -o $@ $^ $(LIBS)

$(CCTARGET): $(CCOBJS)
	@echo AR $@
	@ar rc $@ $^
	@ranlib $@

