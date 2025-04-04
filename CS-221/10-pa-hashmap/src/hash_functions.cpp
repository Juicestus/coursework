#include "hash_functions.h"

size_t polynomial_rolling_hash::operator() (std::string const & str) const {
    size_t b = 19, m = 3298534883309ul;
    size_t hash = 0, p = 1;
    for (char c : str) {
        hash += c * p;
        p = (p * b) % m;
    }
    return hash;
}

size_t fnv1a_hash::operator() (std::string const & str) const {
    size_t hash = 0xCBF29CE484222325;
    size_t prime = 0x00000100000001B3;
    for (char c : str) {
        hash ^= c;
        hash *= prime;
    }
    return hash;
}
