#include "executable.h"
#include <set>

TEST(known_order) {
    Typegen t;

    for (size_t test_iter = 0; test_iter < TEST_ITER; ++test_iter) {
        size_t n = t.range(1ul << 10ul);
        std::list<Student> students;
        std::list<Student*> order;
        std::set<unsigned int> ids;
        for (size_t i = 0; i < n; ++i) {
            unsigned int id = t.get<unsigned int>();
            if (!ids.insert(id).second) {
                --i;
                continue;
            }
            students.push_back(Student(id, t.range(0.0, 4.0), ""));
            order.push_back(&*--students.end());
        }

        KnownOrderComparator comp{order};

        size_t idx_a = t.range<size_t>(0, n);
        size_t idx_b = t.range<size_t>(0, n);

        if (test_iter == 0)
            idx_a = idx_b;

        Student student_a, student_b;
        {
            auto it = students.begin();
            for (size_t i = 0; i < idx_a; ++i, ++it);
            student_a = *it;
            it = students.begin();
            for (size_t i = 0; i < idx_b; ++i, ++it);
            student_b = *it;
        }

        if (idx_a == idx_b)
            ASSERT_FALSE(comp(student_a, student_b));

        ASSERT_EQ(idx_a < idx_b, comp(student_a, student_b));
        ASSERT_EQ(idx_a > idx_b, comp(student_b, student_a));
    }
}
