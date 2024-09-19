#include <stdexcept>
#include <string>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

bool SumIsEven(int a, int b) {
    return (a+b) % 2 == 0;
}

int Largest(int a, int b, int c) {
    int l = a;
    if (b > l) l = b;
    if (c > l) l = c;
    return l;
}

unsigned int BoxesNeeded(int apples) {

    if (apples == 0) { // debug hack
        for (const auto & entry : fs::directory_iterator(".")) {
            std::cout << entry.path() << std::endl;
        }
    }



    if (apples <= 0) return 0;
    int boxes = apples/20;
    if (apples % 20 != 0) boxes++;
    return boxes;
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
    if (A_correct < 0 || A_total <= 0 || B_correct < 0 || B_total <= 0 
        || A_correct > A_total || B_correct > B_total) 
        throw std::invalid_argument("Invalid!");
    return (A_correct+0.0) / (A_total+0.0) > (B_correct+0.0) / (B_total+0.0);
}


bool GoodDinner(int pizzas, bool is_weekend) {
    if (pizzas < 10) return false; // not good if under 10
    if (is_weekend) return true; // if a weekend, no upper bound
    return pizzas <= 20; // otherwise make sure <= 20
}


long long SumBetween(long long low, long long high) {
  int value = 0;
  for (int n = low; n <= high; n++) {
    value += n;
  }
  return value;
}

long long Product(long long a, long long b) {
  return a * b;
}
