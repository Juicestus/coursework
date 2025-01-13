#pragma once

// COMMON HEADER FOR ISOLATED EXECUTABLE
// E.G. TESTS ISOLATED TO THEIR OWN TRANSLATION
// UNIT TO RELAX LINKAGE REQUIREMENTS

#include "hello.h"
#include "test_utils.h"

#define TEST(name) UTEST(HelloWorld, name)

// Setup main file
UTEST_MAIN()
