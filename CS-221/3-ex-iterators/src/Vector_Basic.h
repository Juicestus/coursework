#ifndef VECTOR_BASIC_H
#define VECTOR_BASIC_H

#include <vector>
#include <cstddef> // size_t

template <class T>
class Vector_Basic {
public:
    class iterator;
private:
    T* array;
    size_t _capacity, _size;
public:
    // Can create a vector from an std::vector
    // DO NOT MODIFY THIS FUNCTION
    Vector_Basic(const std::vector<T>& v): array(new T[v.capacity()]), _capacity(v.capacity()), _size(0) {
        for (const auto& elem: v) {
            array[_size] = elem;
            _size++;
        }
    }

    // Should return an iterator pointing to the first element
    iterator begin() noexcept { return iterator(array); }

    // Should return an iterator pointing past the last element of the container
    // This is because you want to stop when you reach end
    iterator end() noexcept { return iterator(array + _size); }

    // Iterator class for the Vector_Basic
    // It is essentially a pointer defined for the type with memory safety
class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Points to some element in the vector (or nullptr)
        T* _ptr;

    public:
        iterator() { _ptr = nullptr; }
        explicit iterator(T* ptr) { _ptr = ptr; }

        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept { return *_ptr; }
        [[nodiscard]] pointer operator->() const noexcept { return _ptr; } // ?

        // Prefix Increment: ++a
        iterator& operator++() noexcept {
            _ptr++;
            return *this;
        }
        // Postfix Increment: a++
        iterator operator++(int) noexcept { return iterator(_ptr++); }
        // Prefix Decrement: --a
        iterator& operator--() noexcept { 
            --_ptr; 
            return *this; 
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept { return iterator(_ptr--); }

        iterator& operator+=(difference_type offset) noexcept { 
            _ptr += offset; 
            return *this;
        }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept { 
            return iterator(_ptr + offset);
        }
        
        iterator& operator-=(difference_type offset) noexcept { 
            _ptr -= offset; 
            return *this;
        }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept { return iterator(_ptr - offset); }
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept { return _ptr - rhs._ptr; }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept {
            return *(_ptr + offset);
        } 

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept { return _ptr == rhs._ptr; }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept { return _ptr != rhs._ptr; }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept { return _ptr < rhs._ptr; }
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept { return _ptr > rhs._ptr; }
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept { return _ptr <= rhs._ptr; }
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept { return _ptr >= rhs._ptr; }
    };
};

#endif
