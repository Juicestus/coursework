#include "executable.h"
#include <vector>

TEST(sort_heaviest_2) {
    std::vector<int> v{11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    int comparisons = 0;
    
    sort_heaviest(v, comparisons);
    ASSERT_EQ(105, comparisons);
    
    for(size_t i = 1; i < v.size(); i++){
        ASSERT_GE(v[i-1], v[i]);
    }
}
