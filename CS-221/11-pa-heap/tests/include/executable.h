#pragma once

// COMMON HEADER FOR ISOLATED EXECUTABLE
// E.G. TESTS ISOLATED TO THEIR OWN TRANSLATION
// UNIT TO RELAX LINKAGE REQUIREMENTS

// Include utilities from utest
#include "utest.h"
// Include custom insertions
#include "assertions.h"
// Track memory allocations
#include "memhook.h"
// Deterministic type generator
#include "typegen.h"
#include "PriorityQueue.h"


#define TEST(name) UTEST(PriorityQueue, name)

size_t constexpr TEST_ITER = 1000;

// Setup main file
UTEST_MAIN()