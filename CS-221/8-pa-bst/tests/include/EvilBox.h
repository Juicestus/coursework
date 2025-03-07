#pragma once

#include <utility>
#include <iostream>

template <typename T>
class EvilBox {
    T* data;
public:
    template <typename C = std::less<T>>
    struct Comparator {
        C _c;
        Comparator() : _c() { }
        bool operator()(const EvilBox& a, const EvilBox& b) const {
            return _c(*a, *b);
        }
    };
    EvilBox() : data(new T{}) {}
    EvilBox(const T& d) : data(new T{d}) {}
    EvilBox(T&& d) : data(new T{std::move(d)}) {}
    EvilBox(const EvilBox& e) : data(new T{*e.data}) {}
    EvilBox(EvilBox&& e) : data(e.data) { e.data = new T{}; }
    ~EvilBox() {
        delete data;
    }
    EvilBox& operator=(const EvilBox& e) {
        if (this == &e)
            return *this;
        *data = *e.data;
        return *this;
    }
    EvilBox& operator=(EvilBox&& e) {
        if (this == &e)
            return *this;
        delete data;
        data = e.data;
        e.data = new T{};
        return *this;
    }
    T& operator*() {
        return *data;
    }
    const T& operator*() const {
        return *data;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, EvilBox<T> e) {
    return os << *e;
}
