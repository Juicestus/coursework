Vectors - Comprehensive Test Suite
==================================

> This test suite was written by Alex who supports sharing it with the students for download. Accordingly, the documentation is written both for other TAs as well as curious students. Students often contributed suggestions and changes last year - sometimes directly PRing the main repo. I think the transparency and feedback precipitated by our move to a more open model benefits everyone.  

This is the test suite for the first assignment - Vectors. The test suite contains 34 tests and is meant to be comprehensive and to test the full distribution of behavior. It tests for both correctness and efficiency. In particular, it ensures that students don't preform unnecessary memory allocations and properly employ move semantics. This can be critical in applications with performance constrains.

In the design of the test suite, each test utilized as few methods from student code as possible. Each test creates a separate executable. This allows students to test frequently and get feedback quickly. Often, a baseline set of methods is needed to ensure the vector is in
the correct state. 

The methods frequently utilized include:
```
Vector();
Vector(size_t count);
~Vector();
size_t size() const noexcept;
size_t capacity() const noexcept;
T& operator[](size_t pos);
const T& operator[](size_t pos);
```

These methods should be fairly easy to implement. Tests to not require the (more) complex logic such as the vector reallocation, move semantics, and iterators unless the tests are explicitly testing that component.

Layout
------

The layout of the test suite is shown below:

```
.
├── assignment-include - Contains assignment specific utility headers
├── assignment-utils - Contains assignment specific utilities
├── build - Contains compiled binaries
├── include - Contains portable library header files
├── makefile
├── README.md
├── submission - Student files
├── tests - Contains the tests, each file is a test
└── utils - Contains portable utilities
```

The "portable" `include` and `utils` directories contains library utilities designed to be portable between different assignment test suites.

Building the Test Suite Locally
-------------------------------

Running the assignment locally is optional. It allows you to compile binaries with debugging and potentially test more efficiently.

1. Download the project from `git`
2. Run `make setup-build`
    - OR: make a `submission` directory under `tests` in the project root. Copy all source files into `submission`
    - OR TAs: run `make setup-build USE_SUBMISSION=SAMPLE_SUBMISSION` to use the sample submission
3. Run `make -k run-all`
4. Run `make clean` to clean up
    - OR TAs: Run `make clean-all` to remove the sample solution (make sure you have committed anything before running this command)

### Tips:
- If you have a multi-core computer (which you probably do unless you're living in the early 2000s), you can run tests in parallel using `make -k run-all -j32`. Here I used `32` because I have `16` cores. If you have hyperthreading, you generally want to use `2 * (cores)`. 
- You can just build the test (without running them) using `make -k`.
- To debug, you can run `make debug`. Then, you can attach to the binary using `gdb` with `gdb ./build/some_test`.
- Clean up with `make clean`.
- Compile a specific test with `make build/some_test`. The name of the test is the same as the name of the executable or the `cpp` file without the `cpp` extension.
- Run a specific test with `make run/some_test`.

Tests
-----

Tests are located under `tests/` Tests prefixed with `iterator_` involve the implementation of the iterator. Likewise tests prefix with `datum_` involve the COVID data tracking.
