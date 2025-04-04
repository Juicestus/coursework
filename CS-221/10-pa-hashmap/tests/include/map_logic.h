#pragma once
#include "primes.h"

#include <vector>
#include <unordered_map>

template<typename Map>
typename Map::size_type correct_hash(typename Map::key_type const & key) {
    return (typename Map::hasher {})(key);
}

template<typename Map>
typename Map::size_type correct_bucket(typename Map::key_type const & key, typename Map::size_type bucket_count) {
    typename Map::hasher hash {};
    return hash(key) % bucket_count;
}

template<typename K, typename V>
class shadow_map {
    using BktMap = std::unordered_map<K, V>;
    
    std::vector<BktMap> _buckets;
    size_t _size;

    public:

    using iterator = typename BktMap::iterator;
    using value_type = typename BktMap::value_type;
    using size_type = typename BktMap::size_type;

    shadow_map(size_type n)
        : _buckets(next_greater_prime(n))
        , _size(0)
    { }

    std::pair<iterator, bool> insert(const value_type & value) {
        size_type bkt = correct_bucket<UnorderedMap<K, V>>(value.first, _buckets.size());
        auto ret = _buckets[bkt].insert(value);
        if(ret.second) _size++;
        return ret;
    }

    size_type erase(const K & key) {
        size_type bkt = correct_bucket<UnorderedMap<K, V>>(key, _buckets.size());
        size_type erased = _buckets[bkt].erase(key);
        if(erased) _size--;
        return erased;
    }

    iterator begin(size_type n) {
        return _buckets[n].begin();
    }

    iterator end(size_type n) {
        return _buckets[n].end();
    }

    bool contained_in_bucket(const K & key, size_type n) const {
        return _buckets[n].find(key) != _buckets[n].end();
    }

    size_type bucket_size(size_type n) const {
        return _buckets[n].size();
    }

    size_type bucket_count() const {
        return _buckets.size();
    }

    size_type size() const { return _size; }
};