#pragma once

#include "map_logic.h"

template<typename K, typename V>
std::ostream & _assert_pairs_in_correct_buckets(
    std::ostream & o,
    const shadow_map<K, V> & shadow_map,
    UnorderedMap<K, V> & map
) {
    using local_iter = typename UnorderedMap<K, V>::local_iterator;

    size_t bucket_count = map.bucket_count();
    size_t expected_bucket_count = shadow_map.bucket_count();
    if(expected_bucket_count != bucket_count) {
        return o << "Unordered Map has wrong bucket count. Expected: " <<
            expected_bucket_count << " got "  << bucket_count << std::endl;
    }

    for(size_t bucket = 0; bucket < shadow_map.bucket_count(); bucket++) {
        size_t count = 0;

        for(local_iter it = map.begin(bucket); it != map.end(bucket); it++) {
            if(!shadow_map.contained_in_bucket(it->first, bucket)) {
                return (
                    o << "Could not find key " << it->first << " in bucket " 
                    << bucket << std::endl
                );
            }
            count++;
        }

        size_t bucket_size = shadow_map.bucket_size(bucket);
        if(bucket_size != count) {
            return o << "Incorrect count in bucket " 
                << bucket << " wanted " << count << " got " 
                << bucket_size << std::endl;
        }
    }

    return o;
}

#define ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(shadow_map, map) \
    MK_ASSERT(_assert_pairs_in_correct_buckets, shadow_map, map)
