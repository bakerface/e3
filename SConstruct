#
# Copyright (c) 2013 - Christopher M. Baker
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

e = Environment()

project_name = ARGUMENTS.get("project-name", "e3")
build_type = ARGUMENTS.get("build-type", "debug")
test_binary = ARGUMENTS.get("test-binary", "test")

e.Append(CPPPATH="include")

e.Append(CCFLAGS="-ansi")
e.Append(CCFLAGS="-ffreestanding")
e.Append(CCFLAGS="-fmessage-length=0")
e.Append(CCFLAGS="-nodefaultlibs")
e.Append(CCFLAGS="-pedantic")
e.Append(CCFLAGS="-pedantic-errors")
e.Append(CCFLAGS="-Waddress")
e.Append(CCFLAGS="-Waggregate-return")
e.Append(CCFLAGS="-Wall")
e.Append(CCFLAGS="-Warray-bounds")
e.Append(CCFLAGS="-Wbad-function-cast")
e.Append(CCFLAGS="-Wcast-align")
e.Append(CCFLAGS="-Wcast-qual")
e.Append(CCFLAGS="-Wchar-subscripts")
e.Append(CCFLAGS="-Wclobbered")
e.Append(CCFLAGS="-Wcomment")
e.Append(CCFLAGS="-Wconversion")
e.Append(CCFLAGS="-Wdeclaration-after-statement")
e.Append(CCFLAGS="-Wdisabled-optimization")
e.Append(CCFLAGS="-Wdouble-promotion")
e.Append(CCFLAGS="-Wempty-body")
e.Append(CCFLAGS="-Wenum-compare")
e.Append(CCFLAGS="-Werror")
e.Append(CCFLAGS="-Wextra")
e.Append(CCFLAGS="-Wfatal-errors")
e.Append(CCFLAGS="-Wfloat-equal")
e.Append(CCFLAGS="-Wformat")
e.Append(CCFLAGS="-Wformat=2")
e.Append(CCFLAGS="-Wformat-nonliteral")
e.Append(CCFLAGS="-Wformat-security")
e.Append(CCFLAGS="-Wformat-y2k")
#e.Append(CCFLAGS="-Wframe-larger-than=")
e.Append(CCFLAGS="-Wignored-qualifiers") 
e.Append(CCFLAGS="-Wimplicit") 
e.Append(CCFLAGS="-Wimplicit-function-declaration")
e.Append(CCFLAGS="-Wimplicit-int") 
e.Append(CCFLAGS="-Winit-self") 
e.Append(CCFLAGS="-Winline")
e.Append(CCFLAGS="-Winvalid-pch")
e.Append(CCFLAGS="-Wjump-misses-init")
#e.Append(CCFLAGS="-Wlarger-than=")
e.Append(CCFLAGS="-Wlogical-op")
e.Append(CCFLAGS="-Wlong-long")
e.Append(CCFLAGS="-Wmain")
e.Append(CCFLAGS="-Wmaybe-uninitialized")
e.Append(CCFLAGS="-Wmissing-braces")
e.Append(CCFLAGS="-Wmissing-declarations")
e.Append(CCFLAGS="-Wmissing-field-initializers")
e.Append(CCFLAGS="-Wmissing-include-dirs") 
e.Append(CCFLAGS="-Wmissing-parameter-type")
e.Append(CCFLAGS="-Wmissing-prototypes") 
e.Append(CCFLAGS="-Wnested-externs") 
e.Append(CCFLAGS="-Wnonnull")
e.Append(CCFLAGS="-Wold-style-declaration") 
e.Append(CCFLAGS="-Wold-style-definition") 
e.Append(CCFLAGS="-Woverlength-strings")
e.Append(CCFLAGS="-Woverride-init") 
e.Append(CCFLAGS="-Wpacked")
e.Append(CCFLAGS="-Wpacked-bitfield-compat")
e.Append(CCFLAGS="-Wpadded")
e.Append(CCFLAGS="-Wparentheses")
e.Append(CCFLAGS="-Wpointer-arith")
e.Append(CCFLAGS="-Wpointer-sign") 
e.Append(CCFLAGS="-Wredundant-decls")
e.Append(CCFLAGS="-Wreturn-type")
e.Append(CCFLAGS="-Wsequence-point")
e.Append(CCFLAGS="-Wshadow")
e.Append(CCFLAGS="-Wsign-compare")
e.Append(CCFLAGS="-Wsign-conversion")
e.Append(CCFLAGS="-Wstack-protector")
#e.Append(CCFLAGS="-Wstack-usage=")
e.Append(CCFLAGS="-Wstrict-aliasing")
e.Append(CCFLAGS="-Wstrict-overflow")
e.Append(CCFLAGS="-Wstrict-prototypes") 
e.Append(CCFLAGS="-Wswitch")
e.Append(CCFLAGS="-Wswitch-default")
e.Append(CCFLAGS="-Wswitch-enum")
e.Append(CCFLAGS="-Wsync-nand") 
e.Append(CCFLAGS="-Wsystem-headers")
#e.Append(CCFLAGS="-Wtraditional")
e.Append(CCFLAGS="-Wtraditional-conversion")
e.Append(CCFLAGS="-Wtrampolines")
e.Append(CCFLAGS="-Wtrigraphs")
e.Append(CCFLAGS="-Wtype-limits")
#e.Append(CCFLAGS="-Wundef")
e.Append(CCFLAGS="-Wuninitialized")
e.Append(CCFLAGS="-Wunknown-pragmas")
e.Append(CCFLAGS="-Wunsafe-loop-optimizations")
e.Append(CCFLAGS="-Wunsuffixed-float-constants")
e.Append(CCFLAGS="-Wunused")
e.Append(CCFLAGS="-Wunused-but-set-parameter")
e.Append(CCFLAGS="-Wunused-but-set-variable")
e.Append(CCFLAGS="-Wunused-function")
e.Append(CCFLAGS="-Wunused-label")
e.Append(CCFLAGS="-Wunused-local-typedefs")
e.Append(CCFLAGS="-Wunused-parameter")
e.Append(CCFLAGS="-Wunused-value")
e.Append(CCFLAGS="-Wunused-variable")
e.Append(CCFLAGS="-Wvariadic-macros")
e.Append(CCFLAGS="-Wvector-operation-performance")
e.Append(CCFLAGS="-Wvla")
e.Append(CCFLAGS="-Wvolatile-register-var")
e.Append(CCFLAGS="-Wwrite-strings")

e.Clean(test_binary, ".sconsign.dblite")

if build_type == "debug":
    e.Append(CCFLAGS="-fprofile-arcs")
    e.Append(CCFLAGS="-ftest-coverage")
    e.Append(CCFLAGS="-g")
    e.Append(CCFLAGS="-O0")
    e.Append(LIBS="gcov")
    e.Clean(test_binary, Glob("src/*.gcno"))
    e.Clean(test_binary, Glob("src/*.gcda"))
    e.Clean(test_binary, Glob("tests/*.gcno"))
    e.Clean(test_binary, Glob("tests/*.gcda"))
    
    coverage = e.Command("coverage", [], [
        "./" + test_binary,
        "lcov -b . -c -d src -o " + project_name + ".coverage",
        "genhtml -o $TARGET " + project_name + ".coverage"])
        
    complexity = e.Command("complexity", Glob("src/*.c"),
        "pmccabe -t -v $SOURCES")
    
    e.Depends(coverage, test_binary)
    e.Depends(complexity, coverage)
    e.Clean(test_binary, project_name + ".coverage")
    e.Clean(test_binary, "coverage")
    e.Program(test_binary, [Glob("src/*.c"), Glob("tests/*.c")])

elif build_type == "release":
    e.Append(CCFLAGS="-nostdinc")
    e.Append(CCFLAGS="-Os")
    e.Append(LINKFLAGS="-nostartfiles")
    e.Append(LINKFLAGS="-nostdlib")
    library = e.StaticLibrary(project_name, [Glob("src/*.c")])
    symbols = e.Command("symbols", library, "nm -S $SOURCE")

