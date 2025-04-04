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
#include "UnorderedMap.h"
#include "hash_functions.h"
#include "map_assertions.h"
#include "map_logic.h"
#include "hash_codes.h"

#define TEST(name) UTEST(UnorderedMap, name)

size_t constexpr TEST_ITER = 100;

/* for pair generation */
template<typename K, typename V>
struct std::hash<std::pair<K, V>> {
  std::hash<K> _k_hash;
  std::hash<V> _v_hash;

  size_t operator()(const std::pair<K, V>& pair) const noexcept {
    return _k_hash(pair.first) ^ _v_hash(pair.second);
  }
};

// Setup main file
UTEST_MAIN()
