// For assignment
#include <stdexcept>
#include <climits>

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
    if (low/4 + high/4 > LLONG_MAX || low/4 + high/4 < LLONG_MIN) 
        throw std::invalid_argument("Invalid!");
    
    return ( (high-low+1) * (low+high) ) / 2;
}

long long Product(long long a, long long b) {
    //double x = ((a+0.0) / LLONG_MAX) * ((b+0.0) / LLONG_MAX) * LLONG_MAX;
    //if (x >= 1 || x < -1) throw std::overflow_error("");
    //return a * b;
    double r = (a+0.0) * (b+0.0);
    if (r >= LLONG_MAX || r < LLONG_MIN) throw std::overflow_error("");
    return (long long)r;
}
