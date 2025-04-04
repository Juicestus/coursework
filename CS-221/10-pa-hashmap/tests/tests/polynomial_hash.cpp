#include "executable.h"

TEST(polynomial_hash) {
    polynomial_rolling_hash pHash;
    std::stringstream p_hash_stream(POLYNOMIAL_HASH);
    std::string s_text;
    size_t hash_value;
    std::string temp;

    while (getline(p_hash_stream, s_text, ',') && p_hash_stream >> std::hex >> hash_value && getline(p_hash_stream, temp)) {
        ASSERT_EQ(hash_value, pHash(s_text));
    }
    
}  