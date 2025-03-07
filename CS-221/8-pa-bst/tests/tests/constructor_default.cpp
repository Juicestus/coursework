#include "executable.h"
#include "EvilBox.h"

TEST(constructor_default) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {

        using IITree = BinarySearchTree<int, int>;

        {
            char BST_MEM[sizeof(IITree)];
            memset(BST_MEM, 0xEE, sizeof(BST_MEM));
            IITree * tree = new (BST_MEM) IITree;

            IITree::const_pointer ptr = &tree->root();
            ASSERT_EQ_(nullptr, ptr, 
                "The binary search tree should be initalized to nullptr"
            );
            ASSERT_EQ(0ULL, tree->size());

            tree->~IITree();
        }

        Memhook mh;
        IITree * tree = new IITree;

        ASSERT_EQ(0ULL, tree->size());
        ASSERT_EQ(1ULL, mh.n_allocs());

        delete tree;
    }
}

TEST(constructor_default_evilbox) {
    Typegen t;

    for(size_t i = 0; i < EVILBOX_TEST_ITER; i++) {

        using IITree = BinarySearchTree<EvilBox<int>, int, EvilBox<int>::Comparator<>>;

        {
            char BST_MEM[sizeof(IITree)];
            memset(BST_MEM, 0xEE, sizeof(BST_MEM));
            IITree * tree = new (BST_MEM) IITree;

            IITree::const_pointer ptr = &tree->root();
            ASSERT_EQ_(nullptr, ptr, 
                "The binary search tree should be initalized to nullptr"
            );
            ASSERT_EQ(0ULL, tree->size());

            tree->~IITree();
        }

        Memhook mh;
        IITree * tree = new IITree;

        ASSERT_EQ(0ULL, tree->size());
        ASSERT_EQ(1ULL, mh.n_allocs());

        delete tree;
    }
}
