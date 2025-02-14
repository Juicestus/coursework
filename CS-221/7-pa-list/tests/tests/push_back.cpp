#include "executable.h"
#include "box.h"

#include <vector>

TEST(push_back) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {

        const size_t n = t.range(0x999ULL);
        std::vector<int> gt(n);
        t.fill(gt.begin(), gt.end());

        {
            // uses modified new to catch uninitialized memory
            List<int> * ll = new List<int>();

            Memhook mh;

            for(size_t i = 0; i < n; i++)
                ll->push_back(gt[i]);

            // Ensure nodes have been allocated
            ASSERT_EQ(n, mh.n_allocs());
            ASSERT_EQ(n, ll->size());

            auto it = ll->cbegin();
            size_t j = 0;
            for(; it != ll->cend(); it++)
                ASSERT_EQ(gt[j++], *it);

            while(it != ll->cbegin())
                ASSERT_EQ(gt[--j], *(--it));

            delete ll;

            // Allocated memory should be freed
            ASSERT_EQ(n, mh.n_scoped_frees());
        }

        {
            // uses modified new to catch uninitialized memory
            List<Box<int>> * ll = new List<Box<int>>();

            std::vector<Box<int>> boxes(n);
            for(size_t i = 0; i < n; i++)
                boxes[i] = gt[i];

            Memhook mh;

            for(size_t i = 0; i < n; i++)
                ll->push_back(std::move(boxes[i]));

            // Ensure nodes have been allocated
            // Allocations shouldn't occur for other
            // memory
            ASSERT_EQ(n, mh.n_allocs());
            ASSERT_EQ(n, ll->size());

            auto it = ll->cbegin();
            size_t j = 0;
            // Iterate forward through the groundtruth vector to ensure
            // all values match the values in the student vector. Failing
            // this condition suggests incorrect values exist in the dynamic
            // array or the iterator is not functioning correctly.
            for(; it != ll->cend(); it++)
                ASSERT_EQ(gt[j++], **it);

            // Do the same in reverse to ensure reverse iterator works
            while(it != ll->cbegin())
                ASSERT_EQ(gt[--j], **(--it));

            delete ll;

            // Allocated memory should be freed
            ASSERT_EQ(n, mh.n_scoped_frees());
            ASSERT_EQ(2 * n + 1, mh.n_frees());
        }
    }
    
}
