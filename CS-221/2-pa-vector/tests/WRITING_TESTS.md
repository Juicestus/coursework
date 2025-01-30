Writing Tests
=============

> This test suite was written by Alex who supports sharing it with the students for download. Accordingly, the documentation is written both for other TAs as well as curious students. Students often contributed suggestions and changes last year - sometimes directly PRing the main repo. I think the transparency and feedback precipitated by our move to a more open model benefits everyone.  

I've spent the last few days working on the new `Vector` assignment test suite and would like to  document my work and share some of the things I learned. I've built up a small library of testing functionality which we can hopefully carry over to new projects.

In the past, we've encountered the following issues with test suites:
1. Lots of internal interdependencies require students to implement a large amount of the behavior before testing it. 
2. Randomization causes tests to fail seemingly without reason. This can be very frustrating for students. Students sometimes just rerun the test suite until it succeeds and the bug persists in the implementation. 
3. Memory leaks were tested on aggregate use and students often have difficulty finding the source of the leak.
4. Many methods were not tested adequately. I routinely witnessed students passing tests with fairly obvious bugs.
5. A lot of code duplication in test cases make maintenance difficult

This new test suite introduces strategies to mitigate these problems.

utest.h
-------

In the past, we've used GoogleTest which shipped with Mimir. GoogleTest supports a large number of features, many of which we didn't utilize. Unfortunately, it requires Python scripts to do code generation. Running these scripts outside a build system is not supported and it only official works with `Bazel` officially although `CMake` is often used. Within `CMake`, it requires each translation unit is linked to their internal library. It would require a lot of adaptation to meet our use case.

[`utest.h`](https://github.com/sheredom/utest.h) fits out use case a lot better. It is a header only unit testing library. It doesn't require code generation (beyond the preprocessor) and is trivial to integrate into custom scripts.

A simple unit test
-------------------

In order to minimize the internal interdependencies at link time, I create one translation unit per test case. I have a header `executable.h` which sets up the `main` automatically. It also includes common dependencies (e.g. student code, `utest`, and other custom utilities. I also define a macro `TEST` which automatically fills in the name of the suite. A basic test would look something like this:

```C++
#include "executable.h"

TEST(some_test) {
    ASSERT_EQ(wanted, got);
}
```

Notes:
- The `wanted`, `got` order is important since `utest` will print this information when it reports a failure
- The assertion macros cannot be called outside `UTEST` blocks. If needed, you can define macros with assertions which you use within a testcase. I would recommend against this: when a failure occurs, the line number is the only indication of which assertion failed and macros obscure this information if they contain multiple assertions.
- I added  `ASSERT_THROWS(statement, exception)` to `executable.h`

Type Generation
----------------

I wrote a custom type generator which:
1. Is deterministic (even across architectures with consistent word sizes / type widths)
2. Templated to generate a variety of random types
3. Is pseudorandom and is automatically initialized with a seed
4. Achieves state-of-the-art speed

This makes writing tests which try a number of random combinations trivial. Repetition has a lot of benefits including (1) polluting the stack to catch memory corruption (2) testing novel combinations to catch edge cases in the code and (3) testing memory handling over multiple free/delete cycles. Typegen makes this trivial.

Here is an example:
```C++
Typegen t; // All state for the PRNG is stored inside the object
        // Declare it outside the loop to generate a new sequence
        // for each iteration
for(size_t z = 0; z < 100; z++) {
    /* Integrel types */
    int  a = t.get<int>();     // any integer
    unsigned long b = t.get<unsigned long>(); // any unsigned long
    
    /* Booleans */
    bool c = t.get<bool>(); // true/false with 50:50 odds
    bool d = t.get<bool>(0.2); // true with 20:80 odds
    
    /* Ranges */
    int e = t.range<int>(1, 5); // any numbers in [1,5)
    size_t f = t.range<size_t>(10); // any number in [0,10)
    float g = t.range<float>(0.2, 0.9); // any number in [0.2, 0.9)
    
    /* Nonzero */
    int h = t.nonzero<int>(); // any nonzero integer
    
    /* Unit interval */
    double i = t.unit<double>(); // [0, 1) 
    
    /* Characters */
    char j = t.get<char>();          // any visable character (e.g. not control)
    char k = t.get<char>(Typegen::ASCII_ALPHA_NUMERIC); // sample from the alpha numeric chars
    char l = t.get<char>(Typegen::ASCII_UPPER_ALPHA | Typegen::ASCII_SYMBOLS); // upper case or symbols
    
    /* Strings */
    std::string m = t.get<std::string>(); // string of length 10 and of all visible characters
    std::string n = t.get<std::string>(50); // string of length 50 and of all visible characters
    std::string o = t.get<std::string>(50, Typegen::ASCII_UPPER_ALPHA); // string of length 50 and the upper case alphabet
    
    /* Iterators */
    // fill a vector with 100 integers
    std::vector<int> p(100, 0);
    t.fill(p.begin(), p.end());
    // fill a vector with 100 strings each of length 5 sampled
    // from lower case letters 
    std::vector<std::string> q(100, "");
    t.fill(q.begin(), q.end(), 5, Typegen::ASCII_LOWER_ALPHA);
    
    /* Sampling from iterators */
    static std::array dates {
        "Aug",
        "Sept",
        "Oct",
        "Nov",
        "Dec"
    };

    // sample one element from the above array
    std::string r = t.sample(dates.begin(), dates.end());
} 
```

See the header file for the full character set, implementation details, and a few more examples.

Memory Testing
--------------

### Valgrind and Address Sanitizer

The second objective is to test memory allocation in a robust way. In the past, we've run `valgrind` on sample mains which exercise a lot of functionality at once. `valgrind` checks if all memory which is allocated is freed. `ASan` or `Address Sanitizer` does something similar. While `valgrind` using the `LD_PRELOAD` trick to inject symbols into the binary, `ASan` is compiled in. `ASan` is faster and available on more platforms. But, it's not as robust as `valgrind`. Both also check for writes outside allocated buffers which is a nice feature.

### Memhooks

As part of this test suite, I attempted a programmatic approach to memory testing in order to be able to test more deliberately. By counting allocations and frees, we can test more completely. For example, we can test if `std::move` is being used appropriately. This lead to the development of `Memhook`s.

Memhooks can be used to test for allocations and frees. They are easy to use.

```C++
{
    Memhook mh;

    int * i = new int;

    std::cout << mh.n_allocs() << std::endl; // 1
    std::cout << mh.n_frees()  << std::endl; // 0

    delete i;

    std::cout << mh.n_frees() << std::endl; // 1
} // Memhook is destroyed and stops listening
```

You can track allocations, frees, block sizes, and the sequences in which allocations occur.

The documentation for memhooks is located in the header file `memhook.h`.

It's worth noting that it can't be used with `valgrind` or Address Sanitizer. I may be able to make it compatible with address sanitizer. This would provide bounds checking for buffers.

#### Boxes

In order to ensure move semantics are implemented properly within an studnet's ADT, it is useful to have a object which implements move semantics properly for mocking purposes. Boxes are dumb wrappers for a pointer which does this. For example:

```C++
template<typename T>
void swap(T & l, T & r) {
    T tmp = std::move(r);
    r = std::move(l);
    l = std::move(tmp);
}

template<typename T>
void naive_swap(T & l, T & r) {
    T tmp = r;
    r = l;
    l = r;
}

int main() {
    Box<int> b1 = 4;
    Box<int> b2 = 8;

    {
        Memhook mh;
        
        swap(b1, b2);
        
        std::cout << mh.n_allocs() << std::endl; // 0

        naive_swap(b1, b2);

        std::cout << mh.n_allocs() << std::endl; // 3
    }
}
```

Boxes can be dereferenced to obtain the internal values. I created boxes because STL containers are platform dependant are heavily optimized to avoid allocations. For example `std::string`s are allocated on the stack if they are shorter than a predefined size. This is called "Short String Optimization" or SSO. Some versions of the STL also implements strings as copy-on-write. This means that the copy operator / constructor don't allocate memory until on of the copies is modified. Athough, this behavior is on its way out since it was actually found to penalize the majority of strings for the benefit of the minority.

Project Layout and Make
-----------------------

The test suite is automated using `make`. The basics of the project layout and methods for building the tests are described in the `README`. The build process has been heavily automated. The project structure was designed to be easy to built upon and to act as a base for our future suites.

- The `assignment-include` and `assignment-utils` are meant to contain helpers specific to testing a particular assignment. The headers are included automatically and globed as prerequisites (so they will rebuild if you make a change). Objects need to be added to the `ASSIGNMENT_OBJS` list in the makefile.
- The `include` and `utils` represent utilities that are not specific to one test suite. `include` is automatically included. If you add `cpp` files to `utils`, add them to the `UTILS_OBJS` list.
- `tests` are globed and compiled automatically. The makefile expects each file in the `tests` folder contains a `main`. If you include `executable.h`, the main will be set up automatically. The name of the associated binary is the name of the `cpp` file without the extension. All binaries are placed in `build/`
- The `submission/` folder contains the students code. All headers are included automatically. All `cpp` files are globed, compiled as objects, and included when compiling files in `tests/`.

Summary of commands:

| Command                  | Description                              |
---------------------------|-------------------------------------------
| `make run-all`           | run all tests                            |
| `make list`              | list all tests                           |
| `make run/{TEST_NAME}`   | run the test with the given `{TEST_NAME}`|
| `make build/{TEST_NAME}` | build the test with the given name       |
| `make all`               | build all tests                          |
| `make debug`             | rebuild the tests with debugging symbols |

> To my understanding, some of the assignments are being ported to `cmake`. (I believe the motivation is to gain better support with windows compilers that don't play well with the command line.) Test suites using the `makefile` can be run either through `WSL` or windows make ports. If someone wants to invest the time in creating a `cmake` file, it might be helpful to some students who want to run the tests offline.

Gradescope
----------
At the time of writing, the tests have not been integrated into Gradescope. Although this should be trivial since each binary returns the proper status code. To use them with Gradescope, we should just need to install `make` and run `make run/some_test` for each test. Make will exit with status code `2` if a failure occurs (either during compilation or runtime.)
