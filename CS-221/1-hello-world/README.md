# Setup Hello World
If you have set up your environment correctly, you can download this code, build it, and practice running some test cases. After building it, you should see the program print "Hello, world!" to the console. Since we are TAMU students, we want it to print "Howdy, world!" to
the console.

The starter code for assignments are located under `src/`. In the `hello.cpp` library, we have a function `greeting_message()` which returns a greeting. In the sole test case, we test `greeting_message()` returns `"Howdy, world!"`. Currently, it returns `"Hello, world!"`.

## Steps to Download and Run the Sample Main

1. Download the Code
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-setup-hello-world.git
cd leyk-csce221-setup-hello-world
```
2. Alternatively, "Download as a ZIP" and extract the files. We highly recommend using git because it allows us to distribute
updates to the test cases if an issue is found.
3. Compile the source code located under `src`. 
```
[#] cd src
[#] g++ -Wall -pedantic -std=c++17 -fsanitize=address hello.cpp main.cpp -o main
[#] ./main
Hello, world!
```
Command explanation:
- `g++` : Call g++ compiler
- `-Wall -pedantic` : Enable additional compiler warnings which often indicate errors or poor coding practices
- `-fsanitize=address` : Add memory leak detection (not necessary)
- `-std=c++17` : Use `C++17`
- `hello.cpp main.cpp` : Compile `hello.cpp` and `main.cpp` to create the executable
- `-o main` : Create an executable called `main`

## Run the tests

1. Change to the root of the assignment if you are in src.
```
[#] pwd
/.../leyk-csce221-setup-hello-world/src
[#] cd ..
```

2. You can run all test cases by using `make -C tests` from the root of the assignment. This instructs make to enter the `tests` directory
and run all the test cases. This runs the `howdy_world` test case.
```
[#] make -C tests
make: Entering directory '/home/ta/csce221/year2/setup-hello-world/tests'
make: Entering directory '/home/ta/csce221/year2/setup-hello-world/tests'
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  ../src/hello.cpp -o ../src/hello.o -c
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  rtest/utils/memhook.cpp -o rtest/utils/memhook.o -c
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  rtest/utils/xoshiro256.cpp -o rtest/utils/xoshiro256.o -c
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  rtest/utils/typegen.cpp -o rtest/utils/typegen.o -c
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  rtest/utils/assertions.cpp -o rtest/utils/assertions.o -c
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  tests/howdy_world.cpp ../src/hello.o rtest/utils/memhook.o rtest/utils/xoshiro256.o rtest/utils/typegen.o rtest/utils/assertions.o -o build/howdy_world
[==========] Running 1 test cases.
[ RUN      ] HelloWorld.howdy_world
tests/howdy_world.cpp:5: Failure
  Expected : "Howdy, World!"
    Actual : "Hello, World!"
[  FAILED  ] HelloWorld.howdy_world (10000ns)
[==========] 1 test cases ran.
[  PASSED  ] 0 tests.
[  FAILED  ] 1 tests, listed below:
[  FAILED  ] HelloWorld.howdy_world
make: *** [rtest/makefile:94: run/howdy_world] Error 1
rm rtest/utils/memhook.o rtest/utils/xoshiro256.o rtest/utils/typegen.o ../src/hello.o rtest/utils/assertions.o
make: Leaving directory '/home/ta/csce221/year2/setup-hello-world/tests'
```

3. Alternatively, you can run a single test case using its name: `make -C tests run/howdy_world`
```
make: Entering directory '/home/ta/csce221/year2/setup-hello-world/tests'
[==========] Running 1 test cases.
[ RUN      ] HelloWorld.howdy_world
tests/howdy_world.cpp:5: Failure
  Expected : "Howdy, World!"
    Actual : "Hello, World!"
[  FAILED  ] HelloWorld.howdy_world (11000ns)
[==========] 1 test cases ran.
[  PASSED  ] 0 tests.
[  FAILED  ] 1 tests, listed below:
[  FAILED  ] HelloWorld.howdy_world
make: *** [rtest/makefile:94: run/howdy_world] Error 1
make: Leaving directory '/home/ta/csce221/year2/setup-hello-world/tests'
```

4. Change "Hello, World!" to "Howdy, World!" Now, the test case should pass:
```
[#] make -C tests run/howdy_world
make: Entering directory '/home/ta/csce221/year2/setup-hello-world/tests'
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  ../src/hello.cpp -o ../src/hello.o -c
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  rtest/utils/memhook.cpp -o rtest/utils/memhook.o -c
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  rtest/utils/xoshiro256.cpp -o rtest/utils/xoshiro256.o -c
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  rtest/utils/typegen.cpp -o rtest/utils/typegen.o -c
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  rtest/utils/assertions.cpp -o rtest/utils/assertions.o -c
clang++ -std=c++17 -Wall -pedantic -DDEBUG -g -Irtest/include  -Iinclude -I../src  tests/howdy_world.cpp ../src/hello.o rtest/utils/memhook.o rtest/utils/xoshiro256.o rtest/utils/typegen.o rtest/utils/assertions.o -o build/howdy_world
[==========] Running 1 test cases.
[ RUN      ] HelloWorld.howdy_world
[       OK ] HelloWorld.howdy_world (5000ns)
[==========] 1 test cases ran.
[  PASSED  ] 1 tests.
rm rtest/utils/memhook.o rtest/utils/xoshiro256.o rtest/utils/typegen.o ../src/hello.o rtest/utils/assertions.o
make: Leaving directory '/home/ta/csce221/year2/setup-hello-world/tests'
```

## Submission
Submit `hello.cpp` and `hello.h` to Gradescope.
