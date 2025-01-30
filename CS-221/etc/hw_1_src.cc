#include <vector>
#include <iostream>

// O(n^2)
bool hw_f1(const std::vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums.size(); j++) {
            if (i == j) continue;
            if ((nums[i] * nums[j]) % 12 == 0)
                return true;
        }
    }
    return false;
}
// O(n)
bool hw_f2(const std::vector<int>& nums) {
    int gm = 0;
    for (const int& num : nums) {
        if (std::max(num, 12) % std::min(num, 12) == 0) {
            if (gm * num >= 12 && (gm * num) % 12 == 0) return true;
            gm = std::max(gm, num);
        }
    }
    return false;
}

int main() {
    #define test(...) { std::vector<int> a{__VA_ARGS__}; std::cout << "[" << #__VA_ARGS__ << "] -> " << hw_f2(a) << "\n"; }

    test(); // 0
    test(12); // 0
    test(1, 12); // 1
    test(1, 6); // 0
    test(2, 6); // 1
    test(1, 3, 6, 5); // 0
    test(6, 1, 4); // 1

}
