#include <iostream>
#include "sort_heaviest.h"

#define PRINTVEC(V) { for (int i = 0; i < V.size(); i++) { std::cout << V[i] << " "; } std::cout << "\n"; }

int main() {
    int comparisons = 0;

    std::vector<int> v1{1,2,3,4,5,6,7,8,9,10};
    sort_heaviest(v1, comparisons);
    PRINTVEC(v1);
    std::cout << "# of Comparisons for v1: " << comparisons << std::endl;

    comparisons = 0;
    std::vector<int> v{10,9,8,7,6,5,4,3,2,1};
    sort_heaviest(v, comparisons);
    PRINTVEC(v);
    std::cout << "# of Comparisons for v: " << comparisons << std::endl;

}
