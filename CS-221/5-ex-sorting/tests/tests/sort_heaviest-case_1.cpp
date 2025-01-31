#include "executable.h"
#include <vector>

TEST(sort_heaviest_1) {
    std::vector<int> v{1,2,3,4,5,6,7,8,9,10,11};
    int comparisons = 0;

    sort_heaviest(v, comparisons);
    ASSERT_EQ(55, comparisons);
    
    for (size_t i = 1; i < v.size(); i++){
        ASSERT_GE(v[i-1], v[i]);
    }
}