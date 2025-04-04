#include "executable.h"

TEST(fnv1a_hash) {
    fnv1a_hash fHash;
    std::stringstream f_hash_stream(FNV1A_HASH);
    std::string s_text;
    size_t hash_value;
    std::string temp;

    while (getline(f_hash_stream, s_text, ',') && f_hash_stream >> std::hex >> hash_value && getline(f_hash_stream, temp)) {
        ASSERT_EQ(hash_value, fHash(s_text));
    }
    
}  