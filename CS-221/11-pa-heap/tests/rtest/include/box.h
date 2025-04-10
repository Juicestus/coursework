#pragma once

#include <utility>
#include <ostream>

/*
    This is a dumb container for a pointer
    which is meant to mock memory allocation 
    logic for proper move/copy semantics. I
    got tired fighting COW / SSO with std::string.

    Works like you would expect:
    {
        Box<int> b1 = 4;
        Box<int> b2 = b1; // copy
        Box<int> b3 = std::move(b1); // move
    } // free, free
*/

template<typename T>
class Box {
    T * _ptr;

    public:

    Box() noexcept : _ptr { nullptr } {}
    ~Box() { delete _ptr; }
    Box(T const & obj) : _ptr {new T} { *_ptr = obj;} 
    Box(T && obj) : _ptr {new T} { *_ptr = std::move(obj); }
    explicit Box(T * ptr) : _ptr {ptr} {}
    Box(Box<T> const & other) : _ptr{nullptr} {
        if(other._ptr) {
            _ptr = new T;
            *_ptr = *other._ptr;
        }
    }
    Box(Box<T> && other) : _ptr { other._ptr } { other._ptr = nullptr; }

    Box<T> & operator=(Box<T> const & other) {
        if(&other == this)
            return *this;
        
        delete _ptr;
        _ptr = nullptr;
        if(other._ptr) {
            _ptr = new T;
            *_ptr = *other._ptr;
        }

        return *this;
    }

    Box<T> & operator=(Box<T> && other) {
        if(&other == this)
            return *this;

        delete _ptr;
        _ptr = other._ptr;
        other._ptr = nullptr;


        return *this;
    }

    T & operator *() noexcept { return *_ptr; }
    T const & operator *() const noexcept { return *_ptr; }
    T * operator->() { return _ptr; }
    T const * operator->() const noexcept { return _ptr; }
    operator bool() { return _ptr != nullptr; }

    bool operator !=(Box<T> const & other) const { return *_ptr != *other; }
    bool operator ==(Box<T> const & other) const { return *_ptr == *other; }
    bool operator <(Box<T> const & other) const { return *_ptr < *other._ptr; }
    bool operator >(Box<T> const & other) const { return *_ptr > *other._ptr; }
    bool operator <=(Box<T> const & other) const { return *_ptr <= *other._ptr; }
    bool operator >=(Box<T> const & other) const { return *_ptr >= *other._ptr; }

    template<typename TT>
    friend std::ostream & operator<<(std::ostream & o, Box<TT> const & box);
};

template<typename T>
std::ostream & operator<<(std::ostream & o, Box<T> const & box) {
    return o << "BOX [" << (*box._ptr) << "]" << std::endl;
}

namespace std {
    template<typename T>
    void swap(Box<T> const & lhs, Box<T> const & rhs) {
        Box<T> t = std::move(lhs);
        lhs = std::move(rhs);
        rhs = std::move(t);
    }

    template<typename T>
    struct hash<Box<T>> {
        std::hash<T> _hash;

        size_t operator()(const Box<T> & box) const noexcept {
            return _hash((*box));
        }
    };
}
