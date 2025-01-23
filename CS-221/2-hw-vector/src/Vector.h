#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <type_traits> // std::is_same

template <class T>
class Vector {
public:
    class iterator;
private:
    T* array;
    size_t _capacity, _size;

    void grow() { 
        _capacity *= 2;
        if (_capacity == 0) _capacity = 1;
        T* new_arr = new T[_capacity];
        std::move(begin(), end(), iterator(new_arr));
        delete[] array;
        array = new_arr;
    }

public:
    Vector() noexcept { 
        _capacity = 0;
        // array = new T[_capacity];
        array = nullptr;
        _size = 0;
    }

    Vector(size_t count, const T& value) {
        _capacity = count;
        array = new T[_capacity];
        for (int i = 0; i < _capacity; i++) {
            array[i] = value;
        }
        _size = _capacity;
    }

    explicit Vector(size_t count) {
        _capacity = count;
        array = new T[_capacity] {}; // all I had to do was add this >:(
        _size = count;
        // memset(array, 0, sizeof(T) * _capacity); // but this works too!
    }

    Vector(const Vector& other) {
        _capacity = other.capacity();
        _size = other.size();
        array = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            array[i] = other.at(i);
        }
    }

    Vector(Vector&& other) noexcept { 
        array = other.array;
        _capacity = other.capacity();
        _size = other.size();
        other.array = nullptr;
        other._capacity = 0;
        other._size = 0;
    }

    ~Vector() {    
        delete[] array;
        array = nullptr;
        _size = 0;
        _capacity = 0; 
    }

    Vector& operator=(const Vector& other) {
        // if our addr == their addr we are the same and we return 
        // there is no point to delete and reallocate ourselves
        // actually that would cause an issue
        if (this == &other) return *this;

        _capacity = other.capacity();
        _size = other.size();

        // we delete and reallocate 
        delete[] array;
        array = new T[_capacity];
        std::copy(other.array, other.array + _size, array);
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this; // same as above
        delete[] array; // delete and set to the other's array
        array = other.array;
        _capacity = other.capacity();
        _size = other.size();
        other.array = nullptr;
        other._capacity = 0;
        other._size = 0;
        return *this;
    }

    iterator begin() noexcept {
        return iterator(array);
    }
    iterator end() noexcept {
        return iterator(array + _size);
    }

    [[nodiscard]] bool empty() const noexcept { 
        return _size == 0; 
    }
    size_t size() const noexcept { return _size; }
    size_t capacity() const noexcept { return _capacity; }

    T& at(size_t pos) {
        if (pos >= _size) {
            throw std::out_of_range("");
        }
        return array[pos];
    }
    const T& at(size_t pos) const {
        if (pos >= _size) {
            throw std::out_of_range("Out of range error");
        }
        return array[pos]; 
    }

    T& operator[](size_t pos) {
        return at(pos);
    }
    const T& operator[](size_t pos) const { 
        return at(pos);
    }
    T& front() {
        return at(0);
    }
    const T& front() const { return at(0); }
    T& back() { return at(_size - 1); }
    const T& back() const { return at(_size - 1); }

    void push_back(const T& value) { 
        if (_size == _capacity) grow();
        array[_size++] = value;
    }
    void push_back(T&& value) {
        if (_size == _capacity) grow();
        array[_size++] = std::move(value);
    }
    void pop_back() {
        _size--;
    }

    iterator insert(iterator pos, const T& value) {
        int index = pos - begin();
        if (_size == _capacity) grow();
        pos = begin() + index;
        for (iterator p = end(); p > pos; p--) *p = std::move(*(p-1));
        _size++;
        *pos = value;
        return pos;
    }

    iterator insert(iterator pos, T&& value) {
        int index = pos - begin();
        if (_size == _capacity) grow();
        pos = begin() + index;
        for (iterator p = end(); p > pos; p--) *p = std::move(*(p-1));
        _size++;
        *pos = std::move(value);
        return pos;
    }
    iterator insert(iterator pos, size_t count, const T& value) {
        int index = pos - begin();
        while (_capacity < _size + count) grow();
        pos = begin() + index;
        for (iterator p = end(); p > pos; p--)  // holy fucking fuck
            *(p+count-1) = std::move(*(p-1));
        for (int i = 0; i < count; i++)
            *(pos+i) = value;
        _size += count;
        return pos;
    }

    iterator erase(iterator pos) {
        std::move(pos+1, end(), pos);
        _size--;
        return pos;
    }

    iterator erase(iterator first, iterator last) {
        std::move(last, end(), first);
        _size -= (last - first);
        return first;
    }

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


    void clear() noexcept {
        array = new T[_capacity] {};
        _size = 0;
    }
};

// This ensures at compile time that the deduced argument _Iterator is a Vector<T>::iterator
// There is no way we know of to back-substitute template <typename T> for external functions
// because it leads to a non-deduced context
namespace {
    template <typename _Iterator>
    using is_vector_iterator = std::is_same<typename Vector<typename _Iterator::value_type>::iterator, _Iterator>;
}

template <typename _Iterator, bool _enable = is_vector_iterator<_Iterator>::value>
[[nodiscard]] _Iterator operator+(typename _Iterator::difference_type offset, _Iterator const& iterator) noexcept {
    return _Iterator(&*iterator + offset); // deref, then get addr again! -- this iterator bs is fucking dumb
}

#endif
