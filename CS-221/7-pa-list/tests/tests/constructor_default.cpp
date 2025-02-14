#include "executable.h"

TEST(constructor_default) {
    // uses modified new to catch uninitalized memory
    List<int> * ll = new List<int>();
    
    Memhook mh;

    // The list should not allocate dynamic memory
    // when constructed. This would be a performance
    // headache
    ASSERT_EQ(0ULL, mh.n_allocs());
    ASSERT_EQ(0ULL, ll->size());

    ASSERT_EQ(true,ll->cbegin() == ll->cend());

    delete ll;
}
