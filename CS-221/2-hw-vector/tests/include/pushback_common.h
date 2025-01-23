#pragma once
#include <cstddef>

struct Memstate {
    size_t idx;
    size_t n_allocs;
    size_t n_frees;
    size_t capacity;
};

static const Memstate state[] = {
    // IDX  ALLOCS FREES CAPACITY
    {  0,   0,     0,    0      },
    {  1,   1,     0,    1      },
    {  2,   2,     1,    2      },
    {  3,   3,     2,    4      },
    {  5,   4,     3,    8      },
    {  9,   5,     4,    16     },
    { 17,   6,     5,    32     },
    { 32,   0,     0,    0      }
};

static const size_t n = sizeof(state) / sizeof(*state);
static const size_t last_idx = state[n - 1].idx;
