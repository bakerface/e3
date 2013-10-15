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
build_type = ARGUMENTS.get("build-type", "")
test_binary = ARGUMENTS.get("test-binary", "test")

e.Append(CPPPATH=["include"])
e.Append(CCFLAGS=["-Wall", "-Wextra", "-Wconversion", "-Werror"])
e.Append(CCFLAGS=["-ansi", "-pedantic", "-ffreestanding", "-nostdlib"])
e.Clean(test_binary, Glob(".sconsign.dblite"))

if build_type == "":
    e.Append(CCFLAGS=["-g", "-O0", "-fprofile-arcs", "-ftest-coverage"])
    e.Append(LIBS=["gcov"])
    e.Clean(test_binary, Glob("src/*.gcno"))
    e.Clean(test_binary, Glob("src/*.gcda"))
    e.Clean(test_binary, Glob("tests/*.gcno"))
    e.Clean(test_binary, Glob("tests/*.gcda"))
    
    coverage = e.Command("coverage", [], [
        "./" + test_binary,
        "lcov -b . -c -d src -o " + project_name + ".coverage",
        "genhtml -o $TARGET " + project_name + ".coverage"])
        
    complexity = e.Command("complexity", Glob("src/*.c"), [
        "pmccabe -t -v $SOURCES"])
    
    e.Depends(coverage, test_binary)
    e.Depends(complexity, coverage)
    e.Clean(test_binary, project_name + ".coverage")
    e.Clean(test_binary, "coverage")
    e.Program(test_binary, [Glob("src/*.c"), Glob("tests/*.c")])

elif build_type == "release":
    e.Append(CCFLAGS=["-Os"])
    library = e.StaticLibrary(project_name, [Glob("src/*.c")])
    symbols = e.Command("symbols", library, ["nm -S $SOURCE"])

