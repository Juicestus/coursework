#include "executable.h"
#include <vector>

TEST(sort_heaviest_4) {
    std::vector<int> v{11,10,9,8,7,6,5,4,3,2,1};
    int comparisons = 0;

    sort_heaviest(v, comparisons);
    ASSERT_EQ(55, comparisons);

    for(size_t i = 1; i < v.size(); i++){
        ASSERT_GE(v[i-1], v[i]);
    }
}