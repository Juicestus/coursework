#include "executable.h"
#include <algorithm>
#include <vector>

TEST(selection_sort) {
    Typegen t;

    for(size_t sz = 0; sz < 800; sz++) {
        std::vector<int> vec(sz);
        std::vector<int> gt(sz);

        t.fill(vec.begin(), vec.end());
        std::copy(vec.begin(), vec.end(), gt.begin());

        sort::selection(vec.begin(), vec.end());
        std::sort(gt.begin(), gt.end());

        bool equal = std::equal(vec.begin(), vec.end(), gt.begin());
        if (!equal) {
            std::cerr << "ERROR: Vector is not sorted!\n";
            if (sz < 30) {
                std::cerr << "\tYour Vector: " << vec
                        << "\n\tCorrect Vector: " << gt << '\n';
            } else {
                std::cerr << "\tVectors are too large to print.\n";
            }
        }
        ASSERT_TRUE(equal);
    }
}
