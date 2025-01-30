#include "executable.h"
#include <array>
#include "box.h"

TEST(sorts_efficent) {
    Typegen t;

    for(size_t i = 0; i < 50; i++) {
        constexpr size_t SZ = 50; 

        std::array<Box<int>, SZ> arr0;
        std::array<Box<int>, SZ> arr1;
        std::array<Box<int>, SZ> arr2;

        for(size_t i = 0; i < SZ; i++)
            arr0[i] = arr1[i] = arr2[i] = t.get<int>();
        
        Memhook mh;

        sort::bubble(arr0.begin(), arr0.end(), [](Box<int> & i, Box<int> & j) {
            return *i < *j;
        });
        
        sort::insertion(arr1.begin(), arr1.end(), [](Box<int> & i, Box<int> & j) {
            return *i < *j;
        });

        sort::selection(arr2.begin(), arr2.end(), [](Box<int> & i, Box<int> & j) {
            return *i < *j;
        });

        ASSERT_EQ(0ULL, mh.n_allocs());
    }
}
