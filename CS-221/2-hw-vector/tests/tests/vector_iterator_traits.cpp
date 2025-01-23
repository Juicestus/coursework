#include "executable.h"

#include <type_traits>
#include <iterator>

#define ASSERT_TYPE_CONSITANCY(T)           \
    do {                                    \
        using iter = typename Vector<T>::iterator;   \
        ASSERT_TRUE((std::is_same<          \
            iter::iterator_category,        \
            std::random_access_iterator_tag \
        >::value));                         \
        ASSERT_TRUE((std::is_same<          \
            iter::value_type,               \
            T                               \
        >::value));                         \
        ASSERT_TRUE((std::is_same<          \
            iter::difference_type,          \
            ptrdiff_t                       \
        >::value));                         \
        ASSERT_TRUE((std::is_same<          \
            iter::pointer,                  \
            T*                              \
        >::value));                         \
        ASSERT_TRUE((std::is_same<          \
            iter::reference,                \
            T&                              \
        >::value));                         \
    } while(0)

TEST(iterator_traits) {
    ASSERT_TYPE_CONSITANCY(int);
    ASSERT_TYPE_CONSITANCY(double);
    ASSERT_TYPE_CONSITANCY(double*);
}