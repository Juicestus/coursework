#include <cstddef>     // size_t
#include <functional>  // std::hash
#include <ios>
#include <iostream>
#include <utility>  // std::pair

#include "primes.h"


template<typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class UnorderedMap
{
public:
    using key_type = Key;
    using mapped_type = T;
    using const_mapped_type = const T;
    using hasher = Hash;
    using key_equal = Pred;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

private:
    struct HashNode
    {
        HashNode* next;
        value_type val;

        HashNode(HashNode* next = nullptr) : next{next}
        {
        }
        HashNode(const value_type& val, HashNode* next = nullptr) : next{next}, val(val)
        {
        }
        HashNode(value_type&& val, HashNode* next = nullptr) : next{next}, val(std::move(val))
        {
        }
    };

    size_type _bucket_count;
    HashNode** _buckets;
    HashNode* _head;
    size_type _size;

    Hash _hash;
    key_equal _equal;

    static size_type _range_hash(size_type hash_code, size_type bucket_count)
    {
        return hash_code % bucket_count;
    }

public:
    template<typename pointer_type, typename reference_type, typename _value_type> class basic_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = _value_type;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        const UnorderedMap* _map;
        HashNode* _ptr;

        explicit basic_iterator(UnorderedMap const* map, HashNode* ptr) noexcept : _map(map), _ptr(ptr)
        {
        }

    public:
        basic_iterator() : _map(nullptr), _ptr(nullptr)
        {
        }
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        ~basic_iterator() = default;
        basic_iterator& operator=(const basic_iterator&) = default;
        basic_iterator& operator=(basic_iterator&&) = default;

        reference operator*() const
        {
            return _ptr->val;
        }
        pointer operator->() const
        {
            return &_ptr->val;
        }

        basic_iterator& operator++()
        {
            if (_ptr->next != nullptr)
            {
                _ptr = _ptr->next;
                return *this;
            }
            size_type bucket = _map->_bucket(_ptr->val.first) + 1;
            while (bucket < _map->_bucket_count && _map->_buckets[bucket] == nullptr) ++bucket;

            _ptr = (bucket < _map->_bucket_count) ? _map->_buckets[bucket] : nullptr;
            return *this;
        }

        basic_iterator operator++(int)
        {
            basic_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const basic_iterator& other) const noexcept
        {
            return _ptr == other._ptr && _map == other._map;
        }

        bool operator!=(const basic_iterator& other) const noexcept
        {
            return !(*this == other);
        }
    };

    using iterator = basic_iterator<pointer, reference, value_type>;
    using const_iterator = basic_iterator<const_pointer, const_reference, const value_type>;

    class local_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const key_type, mapped_type>;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        HashNode* _node;
        explicit local_iterator(HashNode* node) noexcept : _node(node)
        {
        }

    public:
        local_iterator() : _node(nullptr)
        {
        }
        local_iterator(const local_iterator&) = default;
        local_iterator(local_iterator&&) = default;
        ~local_iterator() = default;
        local_iterator& operator=(const local_iterator&) = default;
        local_iterator& operator=(local_iterator&&) = default;

        reference operator*() const
        {
            return _node->val;
        }
        pointer operator->() const
        {
            return &_node->val;
        }

        local_iterator& operator++()
        {
            if (_node != nullptr) _node = _node->next;
            return *this;
        }

        local_iterator operator++(int)
        {
            local_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const local_iterator& other) const noexcept
        {
            return _node == other._node;
        }

        bool operator!=(const local_iterator& other) const noexcept
        {
            return !(*this == other);
        }
    };

private:
    size_type _bucket(size_t code) const
    {
        return _range_hash(code, _bucket_count);
    }
    size_type _bucket(const Key& key) const
    {
        return _bucket(_hash(key));
    }
    size_type _bucket(const value_type& val) const
    {
        return _bucket(val.first);
    }

    HashNode* _find(size_type code, size_type bucket, const Key& key)
    {
        for (HashNode* curr = _buckets[bucket]; curr; curr = curr->next)
        {
            if (_equal(curr->val.first, key)) return curr;
        }
        return nullptr;
    }

    HashNode* _find(const Key& key)
    {
        size_type code = _hash(key);
        return _find(code, _bucket(code), key);
    }

    HashNode* _insert_into_bucket(size_type bucket, const value_type& value)
    {
        HashNode* node = new HashNode(value, _buckets[bucket]);
        _buckets[bucket] = node;
        if (_head == nullptr) _head = node;
        return node;
    }

    HashNode* _insert_into_bucket(size_type bucket, value_type&& value)
    {
        HashNode* node = new HashNode(std::move(value), _buckets[bucket]);
        _buckets[bucket] = node;
        if (_head == nullptr) _head = node;
        return node;
    }

public:
    explicit UnorderedMap(size_type bucket_count, const Hash& hash = Hash{}, const key_equal& equal = key_equal{})
        : _bucket_count(next_greater_prime(bucket_count == 0 ? 1 : bucket_count)),
          _buckets(new HashNode* [_bucket_count] {}), _head(nullptr), _size(0), _hash(hash), _equal(equal)
    {
    }

    ~UnorderedMap()
    {
        clear();
        delete[] _buckets;
    }

    UnorderedMap(const UnorderedMap& other)
        : _bucket_count(other._bucket_count), _buckets(new HashNode* [_bucket_count] {}), _head(nullptr), _size(0),
          _hash(other._hash), _equal(other._equal)
    {
        for (size_t i = 0; i < _bucket_count; ++i)
        {
            for (HashNode* node = other._buckets[i]; node; node = node->next)
            {
                HashNode* new_node = new HashNode(node->val, _buckets[i]);
                _buckets[i] = new_node;
                if (_head == nullptr) _head = new_node;
                ++_size;
            }
        }
    }

    UnorderedMap(UnorderedMap&& other) noexcept
        : _bucket_count(other._bucket_count), _buckets(other._buckets), _head(other._head), _size(other._size),
          _hash(std::move(other._hash)), _equal(std::move(other._equal))
    {
        other._buckets = new HashNode*[other._bucket_count]{};
        other._head = nullptr;
        other._size = 0;
    }

    UnorderedMap& operator=(const UnorderedMap& other)
    {
        if (this == &other) return *this;
        clear();
        delete[] _buckets;

        _bucket_count = other._bucket_count;
        _buckets = new HashNode* [_bucket_count] {};
        _head = nullptr;
        _size = 0;
        _hash = other._hash;
        _equal = other._equal;

        for (size_t i = 0; i < _bucket_count; ++i)
        {
            for (HashNode* node = other._buckets[i]; node; node = node->next)
            {
                HashNode* new_node = new HashNode(node->val, _buckets[i]);
                _buckets[i] = new_node;
                if (_head == nullptr) _head = new_node;
                ++_size;
            }
        }
        return *this;
    }

    UnorderedMap& operator=(UnorderedMap&& other) noexcept 
    {
        if (this == &other) return *this;

        clear();
        delete[] _buckets;

        _bucket_count = other._bucket_count;
        _buckets = other._buckets;
        _head = other._head;
        _size = other._size;
        _hash = std::move(other._hash);
        _equal = std::move(other._equal);

        other._buckets = new HashNode*[other._bucket_count]{};
        other._head = nullptr;
        other._size = 0;

        return *this;
    }

    void clear() noexcept
    {
        for (size_t i = 0; i < _bucket_count; ++i)
        {
            HashNode* node = _buckets[i];
            while (node)
            {
                HashNode* next = node->next;
                delete node;
                node = next;
            }
            _buckets[i] = nullptr;
        }
        _size = 0;
        _head = nullptr;
    }

    size_type size() const noexcept
    {
        return _size;
    }
    bool empty() const noexcept
    {
        return _size == 0;
    }
    size_type bucket_count() const noexcept
    {
        return _bucket_count;
    }

    iterator begin()
    {
        for (size_t i = 0; i < _bucket_count; i++)
        {
            if (_buckets[i] != nullptr) return iterator(this, _buckets[i]);
        }
        return end();
    }

    iterator end()
    {
        return iterator(this, nullptr);
    }

    const_iterator cbegin() const
    {
        for (size_t i = 0; i < _bucket_count; i++)
        {
            if (_buckets[i] != nullptr) return const_iterator(this, _buckets[i]);
        }
        return cend();
    }

    const_iterator cend() const
    {
        return const_iterator(this, nullptr);
    }

    local_iterator begin(size_type n)
    {
        return local_iterator(_buckets[n]);
    }
    local_iterator end(size_type n)
    {
        return local_iterator(nullptr);
    }

    size_type bucket(const Key& key) const
    {
        return _bucket(key);
    }

    size_type bucket_size(size_type n)
    {
        size_type count = 0;
        for (HashNode* node = _buckets[n]; node; node = node->next) count++;
        return count;
    }

    float load_factor() const
    {
        return ((double)_size) / ((double)_bucket_count);
    }

    std::pair<iterator, bool> insert(value_type&& value)
    {
        size_t code = _hash(value.first);
        size_t bucket = _bucket(code);

        if (_find(code, bucket, value.first))
        {
            return std::make_pair(iterator(this, _find(code, bucket, value.first)), false);
        }

        HashNode* node = _insert_into_bucket(bucket, std::move(value));
        _size++;
        return std::make_pair(iterator(this, node), true);
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        size_t code = _hash(value.first);
        size_t bucket = _bucket(code);

        if (_find(code, bucket, value.first))
        {
            return std::make_pair(iterator(this, _find(code, bucket, value.first)), false);
        }

        HashNode* node = _insert_into_bucket(bucket, value);
        _size++;
        return std::make_pair(iterator(this, node), true);
    }

    iterator find(const Key& key)
    {
        if (HashNode* node = _find(key)) return iterator(this, node);
        return end();
    }

    T& operator[](const Key& key)
    {
        return insert(std::make_pair(key, mapped_type{})).first->second;
    }

    iterator erase(iterator pos)
    {
        HashNode* node = pos._ptr;
        size_type bucket = _bucket(node->val.first);

        if (_buckets[bucket] == node) { _buckets[bucket] = node->next; }
        else
        {
            HashNode* prev = _buckets[bucket];
            while (prev->next != node) prev = prev->next;
            prev->next = node->next;
        }

        iterator next = ++pos;
        delete node;
        _size--;
        return next;
    }

    size_type erase(const Key& key)
    {
        iterator it = find(key);
        if (it == end()) return 0;
        erase(it);
        return 1;
    }

    template<typename KK, typename VV> friend void print_map(const UnorderedMap<KK, VV>& map, std::ostream& os);
};

template<typename K, typename V> void print_map(const UnorderedMap<K, V>& map, std::ostream& os = std::cout)
{
    using size_type = typename UnorderedMap<K, V>::size_type;
    using HashNode = typename UnorderedMap<K, V>::HashNode;

    for (size_type bucket = 0; bucket < map.bucket_count(); ++bucket)
    {
        os << bucket << ": ";
        for (HashNode const* node = map._buckets[bucket]; node; node = node->next)
        {
            os << "(" << node->val.first << ", " << node->val.second << ") ";
        }
        os << "\n";
    }
}
