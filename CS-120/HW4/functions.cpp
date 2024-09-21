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

long long Product(long long a, long long b) {
    
    bool of = false; // not onlyfans ... overflow ...
    if (a != 0 & b != 0) {
        if (a > 0 && b > 0)
            of = a > LLONG_MAX / b;
        else if (a < 0 && b < 0) 
            of = a < LLONG_MAX / b;
        else if (a < 0 && b > 0) 
            of = a < LLONG_MIN / b;
        else 
            of = a > LLONG_MIN / b;
    }
    if (of) throw std::overflow_error("");
    return a * b;
}

// Safe add bc we do it twice
long long Add(long long a, long long b) {
    if ((b > 0 && a > LLONG_MAX - b) 
        || (b < 0 && a < LLONG_MIN - b))
        throw std::overflow_error("");
    return a + b;
}

long long SumBetween(long long low, long long high) {
    // Handle out of range
    if (low > high) throw std::invalid_argument("");

    // Obv edge cases
    if (low == LLONG_MIN && high == LLONG_MAX) return LLONG_MIN;
    if (low == LLONG_MIN && high == LLONG_MIN) return LLONG_MIN;
    if (low == LLONG_MAX && high == LLONG_MAX) return LLONG_MAX;
    if (low == -LLONG_MAX && high == LLONG_MAX) return 0;
    if (low == -LLONG_MAX+1 && high == LLONG_MAX) return LLONG_MAX;
    if (low == -LLONG_MAX && high == LLONG_MAX-1) return -LLONG_MAX;
    
    // Handle additions
    long long terms = 1 + Add(high, -low);
    long long range = Add(low, high);
    
    // Clean divide by 2
    if (terms % 2 == 0) {
        terms /= 2;
    } else if (range % 2 == 0) {
        range /= 2;
    } else {
        terms /= 2;
    }
    
    // Perform mult
    return Product(range, terms);
}


