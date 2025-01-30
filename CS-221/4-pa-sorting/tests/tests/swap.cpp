#include "executable.h"
#include <vector>
#include "box.h"

TEST(swap) {
    Typegen t;
    for(size_t i = 0; i < 100; ++i) {
        int a_gt;
        Box<int> a {new int};
        int b_gt;
        Box<int> b {new int};

		a_gt = *a = t.get<int>();
		b_gt = *b = t.get<int>();

        {
            Memhook mh;
            sort::swap(a, b);

			if (mh.n_allocs() != 0) {
                std::cerr << "ERROR: Swap is allocating a new value.\n"
                    << "\tDoes your swap use copy or move semantics?\n";
            }
            ASSERT_EQ(0UL, mh.n_allocs());

            if (mh.n_frees() != 0) {
                std::cerr << "ERROR: Swap is freeing (deleting) a value.\n"
                    << "\tShould swap do this?\n";
            }
            ASSERT_EQ(0UL, mh.n_frees());

            if (a_gt != *b) {
                std::cerr << "ERROR: b does not contain the same values that a_gt contains.\n"
                    << "\tDid you swap the values?\n";
            }
            if (b_gt != *a) {
                std::cerr << "ERROR: a does not contain the same values that b_gt contains.\n"
                    << "\tDid you swap the values?\n";
            }

			ASSERT_EQ(a_gt, *b);
			ASSERT_EQ(b_gt, *a);
        }
    }
}
