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
// Include source file
#include "sorting.h"

#include <list>
#include <vector>
#include "Student.h"

#define TEST(name) UTEST(SORT, name)

// Globally defined TEST_ITER for strenuousness
size_t constexpr TEST_ITER = 10;

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& vec) {
    o << '[';
    for (const T& e : vec) {
        o << e;
        if (&e != &vec.back()) {
            o << ", ";
        }
    }
    return o << ']';
}

// Setup main file
UTEST_MAIN()


