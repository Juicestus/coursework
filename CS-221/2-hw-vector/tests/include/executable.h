#pragma once

// COMMON HEADER FOR ISOLATED EXECUTABLE
// E.G. TESTS ISOLATED TO THEIR OWN TRANSLATION
// UNIT TO RELAX LINKAGE REQUIREMENTS

// Include utilities from utest
#include "utest.h"
// Track memory allocations
#include "memhook.h"
// Deterministic type generator
#include "typegen.h"
// Include custom assertions
#include "assertions.h"
// Include source file
#include "Vector.h"

#define TEST(name) UTEST(VECTOR, name)

// Setup main file
UTEST_MAIN()


