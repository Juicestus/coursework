#include "box.h"
#include "executable.h"

#include <unordered_map>

TEST(destructor_and_inserts) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {

        // With copy insert tests
        size_t n_pairs = t.range(400ul);
        size_t n = t.range(1000ull);

        std::vector<std::pair<double, double>> copy_pairs(n_pairs);
        t.fill(copy_pairs.begin(), copy_pairs.end());

        {
            Memhook mh;
            {
                UnorderedMap<double, double> map(n);

                for(auto const & pair: copy_pairs) {
                    std::pair<const double, double> to_insert(pair);
                    map.insert(to_insert);
                }

                mh.disable();
                ASSERT_EQ_(mh.n_allocs(), map.size() + 1, "Make sure the copy insert is implemented");
                mh.enable();
            }

            // Ensure everything that is allocated is deleted
            mh.disable();
            ASSERT_EQ_(mh.n_allocs(), mh.n_frees(), "Destructor does not deallocate enough");
        }

        // With move insert tests
        std::vector<std::pair<int, int>> move_pairs(n_pairs);
        t.fill_unique(move_pairs.begin(), move_pairs.end());

        std::vector<std::pair<int, Box<int>>> boxes(n_pairs);
        std::vector<std::pair<int, Box<int>>> cpy_boxes(n_pairs);

        for(size_t i = 0; i < move_pairs.size(); i++) {
            auto const & [key, val] = move_pairs[i];

            boxes[i] = std::make_pair(key, Box<int>(val));
            cpy_boxes[i] = std::make_pair(key, Box<int>(val));
        }

        {
            Memhook mh;
            {
                UnorderedMap<int, Box<int>> map(n);
            
                for(size_t i = 0; i < move_pairs.size(); i++) {
                    map.insert(std::move(cpy_boxes[i]));
                }

                mh.disable();
                ASSERT_EQ_(mh.n_allocs(), map.size() + 1, "Make sure the move insert is implemented");
                mh.enable();
            }

            // Ensure everything that is allocated is deleted
            mh.disable();
            ASSERT_EQ_(2*mh.n_allocs()-1, mh.n_frees(), "Destructor does not deallocate enough");
        }
    }
}
