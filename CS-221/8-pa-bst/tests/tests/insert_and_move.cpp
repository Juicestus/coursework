#include "generate_tree_data.h"
#include "executable.h"
#include "box.h"

TEST(insert_and_move) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        int lower = t.range(0, 250);
        int upper = lower + t.range(1, 250);

        depth_list<int> dlist = generate_tree_data(t, lower, upper);

        std::vector<int> gt(dlist.size());
        t.fill(gt.begin(), gt.end());

        std::vector<int> gt_overwrite(dlist.size());
        t.fill(gt_overwrite.begin(), gt_overwrite.end());

        std::vector<Box<int>> boxes(dlist.size());
        std::vector<Box<int>> boxes_overwrite(dlist.size());

        for(size_t i = 0; i < dlist.size(); i++)
            boxes[i] = gt[i];

        for(size_t i = 0; i < dlist.size(); i++)
            boxes_overwrite[i] = gt_overwrite[i];

        {
            BinarySearchTree<int, Box<int>> tree;
            size_t expected_sz = 0;
            for(auto & [key, depth] : dlist) {

                {
                    Memhook mh;

                    tree.insert({key, std::move(boxes[expected_sz])});
                    ASSERT_EQ(1ULL, mh.n_allocs());
                }

                ASSERT_VALUE_IN_TREE(Box { gt[expected_sz] }, tree, key);

                {
                    Memhook mh;
                    tree.insert({key, std::move(boxes_overwrite[expected_sz])});
                    ASSERT_EQ(0ULL, mh.n_allocs());
                }

                ASSERT_VALUE_IN_TREE(Box { gt_overwrite[expected_sz] } , tree, key);

                ASSERT_EQ(++expected_sz, tree.size());
            }


        }
    }
}
