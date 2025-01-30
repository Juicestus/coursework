#include "executable.h"

TEST(gpa_comp) {
    Typegen t;

    for (size_t test_iter = 0; test_iter < TEST_ITER; ++test_iter) {
        GPAComparator comp;
        Student student_a{t.get<unsigned int>(), t.range<float>(0.0, 4.0), ""};
        Student student_b{t.get<unsigned int>(), t.range<float>(0.0, 4.0), ""};

        if (test_iter == 0)
            student_b = Student{student_b.getID(), student_a.getGPA(), ""};

        if (student_a.getGPA() == student_b.getGPA()) {
            ASSERT_EQ(student_a.getID() < student_b.getID(), comp(student_a, student_b));
            ASSERT_EQ(student_a.getID() > student_b.getID(), comp(student_b, student_a));
            continue;
        }

        ASSERT_EQ(student_a.getGPA() > student_b.getGPA(), comp(student_a, student_b));
        ASSERT_EQ(student_a.getGPA() < student_b.getGPA(), comp(student_b, student_a));
    }
}
