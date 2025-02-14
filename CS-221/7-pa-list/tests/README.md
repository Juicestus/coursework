Lists - Comprehensive Test Suite
====================================

This is the test suite for the third assignment - List. The test suite contains TODO tests and is meant to be comprehensive and to test the full distribution of behavior. It tests for both correctness and efficiency. In particular, it ensures that students don't preform unnecessary memory allocations and properly employ move semantics. This can be critical in applications with performance constrains.

In the design of the test suite, each test utilized as few methods from student code as possible. Each test creates a separate executable. This allows students to test frequently and get feedback quickly. Often, a baseline set of methods is needed to ensure the sorted vector is in the correct state. 

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

### Students

1. Download the project from `git`
2. Run `make -k run-all`
3. Run `make clean` to clean up

### TAs


The TAs can setup the project using:
```
make -f ta-makefile CXX=clang++
```

It will clone the `sample-submission` using `ssh`. To use `http` do the following:

```
make -f ta-makefile CXX=clang++ http
```

This downloads the solution from the sample-solution repo (default target). This is a live repo and you can commit directly back to the `sample-solution` repo. The `sample-solution` command (from above) will also create a file `ta_config` with make setting for TAs. For instance, can use `CXX` to set the compiler in a persistent way without editing the `makefile`. If you have a usecase, add more persistent settings!

Then, use run `make run/${TEST}` to run the test for the file `${TEST}.cpp`. 

Once finished, you can clean up with:
```
make -f ta-makefile clean
```

This will remove the `ta_config` and `sample-solution` repo.

### Tips:
- If you have a multi-core computer (which you probably do unless you're living in the early 2000s), you can run tests in parallel using `make -k run-all -j32`. Here I used `32` because I have `16` cores. If you have hyperthreading, you generally want to use `2 * (cores)`.
- You can just build the test (without running them) using `make -k`.
- You can debug the tests since they compile with debugging by default
- Clean up with `make clean`.
- Compile a specific test with `make build/some_test`. The name of the test is the same as the name of the executable or the `cpp` file without the `cpp` extension.
- Run a specific test with `make run/some_test`.

Tests
-----

Tests are located under `tests/`. You may view them or add your own debugging statements.
