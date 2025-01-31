#include "executable.h"
#include <vector>

TEST(sort_heaviest_5) {
    std::vector<int> v;
    int comparisons = 0;
    srand(time(0));
    int number = rand()%15;

    if(number <= 5){
        number=8;
    }

    number = 15;
    
    for (int i = 0; i < number; i++){
        v.push_back(rand()%20);
    }

    sort_heaviest(v, comparisons);
    int form_comp = (number-1)*number/2;
    ASSERT_EQ(form_comp, comparisons);
    
    for (size_t i = 1; i < v.size(); i++){
        ASSERT_GE(v[i-1], v[i]);
    }
}