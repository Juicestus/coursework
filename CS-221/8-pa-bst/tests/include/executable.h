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
// Order here is important
// The student header BinarySearchTree.h allows
// overrides in tree_asserts.h
#include "BinarySearchTree.h"
#include "tree_asserts.h"

#define TEST(name) UTEST(BinarySearchTree, name)

size_t constexpr TEST_ITER = 100;
size_t constexpr EVILBOX_TEST_ITER = 1;

// Setup main file
UTEST_MAIN()
