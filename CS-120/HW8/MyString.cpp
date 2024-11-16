#include "MyString.h"


static size_t my_strlen(const char* s) { 
    if (!s) return 0;
    size_t i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

static void my_strncpy(char *dst, const char *src, size_t n) {
    for (size_t i = 0; i < n; i++) dst[i] = src[i];
}

MyString::MyString() : _data(new char[1]), _cap(1) {
    _data[0] = '\0';
}

MyString::MyString(const MyString& other) : _data(nullptr), _cap(0) {
    *this = other;
    std::cout << "CAP IS " << _cap << std::endl;
}


MyString::MyString(const char* str) : _data(nullptr), _cap(0) {
    if (!str) { // if null or empty
        _data = new char[1];
        _data[0] = '\0';
        _cap = 0;
    } else {
        size_t l = my_strlen(str);
        _data = new char[l+1];
        my_strncpy(_data, str, l);
        _data[l] = '\0';
        _cap = l;
    }
    std::cout << "CAP IS " << _cap << std::endl;
}

MyString::~MyString() {
    delete[] _data;
    _data = nullptr;
}

void MyString::resize(size_t n) {
    char* new_data = new char[n + 1]; 
    if (_data) {
        size_t copy_size = n < size() ? n : size();
        my_strncpy(new_data, _data, copy_size); 
        new_data[n] = '\0'; 

        for (size_t i = copy_size; i < n; i++) {
            new_data[i] = '\0';
        }

    } else {
        new_data[0] = '\0';
    }
    delete[] _data;
    _data = new_data;
    _cap = n;
}

size_t MyString::capacity() const {
    return _cap;
}

size_t MyString::size() const {
    return my_strlen(_data);
}

size_t MyString::length() const {
    return size();
}

const char* MyString::data() const {
    return _data;
}

bool MyString::empty() const {
    return size() == 0;
}

const char& MyString::at(size_t pos) const {
    if (pos >= size()) throw std::out_of_range("Index out of bounds.");
    return _data[pos];
}

const char& MyString::front() const {
    return at(0);
}

void MyString::clear() {
    delete[] _data;
    _data = new char[1];
    _data[0] = '\0';
    _cap = 0;
}

size_t MyString::find(const MyString& str, size_t pos) const {
    if (str.size() > size()) return -1;
    if (str.size() == 0) return pos;
    if (str.size() > size() || pos >= size()) return -1;

    for (size_t i = pos; i <= size() - str.size(); i++) {
        bool found = true;
        for (size_t j = 0; j < str.size(); j++) {
            if (at(i+j) != str.at(j)) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}

MyString& MyString::operator = (const MyString& str) {
    if (this == &str) return *this;
    delete[] _data;
    _cap = str._cap;
    _data = new char[_cap + 1];
    my_strncpy(_data, str._data, _cap);
    _data[_cap] = '\0';
    return *this;
}

MyString& MyString::operator += (const MyString& str) {
    size_t new_size = size() + str.size();
    if (new_size > _cap) resize(new_size);
    my_strncpy(_data + size(), str.data(), str.size()); 
    _data[new_size] = '\0';
    return *this;
}

bool operator == (const MyString& lhs, const MyString& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (size_t i = 0; i < lhs.size(); i++) {
        if (lhs.at(i) != rhs.at(i)) return false;
    }
    return true;
}

MyString operator + (const MyString& lhs, const MyString& rhs) {
    MyString ret = MyString();
    ret += lhs;
    ret += rhs;
    return ret;
}

std::ostream& operator << (std::ostream& os, const MyString str) {
    os << str.data();
    return os;
}
