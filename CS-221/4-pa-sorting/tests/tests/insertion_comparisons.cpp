#include "executable.h"
#include "memorize.h"
#include <algorithm>
#include <vector>

TEST(insertion_comparisons) {
    Typegen t;

    for(size_t sz = 0; sz < 800; sz++) {
        std::vector<double> vec(sz);
        std::vector<double> gt(sz);

        t.fill(vec.begin(), vec.end());
        std::copy(vec.begin(), vec.end(), gt.begin());

        size_t comparisons = 0;

        sort::insertion(vec.begin(), vec.end(), [&comparisons](double & i, double & j) {
            comparisons++;
            return i > j;
        });

        std::sort(gt.begin(), gt.end(), [](double & i, double & j) { return i > j; });

        bool equal = std::equal(vec.begin(), vec.end(), gt.begin());
        if (!equal) {
            std::cerr << "ERROR: Vector is not sorted!\n"
                    << "\tAre you using the Comparator comp?\n";
            if (sz < 30) {
                std::cerr << "\tYour Vector: " << vec
                        << "\n\tCorrect Vector: " << gt << '\n';
            } else {
                std::cerr << "\tVectors are too large to print.\n";
            }
        }
        ASSERT_TRUE(equal);
        
        if (comparisons < memorize::insertion_comparisons[sz] - memorize::insertion_error(sz)) {
            std::cerr << "ERROR: Comparisons (" << comparisons << ") is fewer than expected.\n"
                    << "\tDid you implement Insertion Sort?" << std::endl;
        } else if (memorize::insertion_comparisons[sz] + memorize::insertion_error(sz) < comparisons) {
            std::cerr << "ERROR: Comparisons (" << comparisons << ") is greater than expected.\n"
                    << "\tYou should make your algorithm more efficient." << std::endl;
        }
        ASSERT_NEAR(memorize::insertion_comparisons[sz], comparisons, memorize::insertion_error(sz));
    }
}
