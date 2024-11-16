/**
 * MyString.h -- limited implementation of std::string
 */

#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <iostream>
#include <stdexcept>

class MyString {
private:

    char* _data;
    size_t _cap;

public:
    MyString();
    MyString(const MyString& other);
    MyString(const char* str);
    ~MyString();

    void resize(size_t n);
    size_t capacity() const;
    size_t size() const;
    size_t length() const;
    const char* data() const;
    bool empty() const;
    const char& front() const;
    const char& at(size_t pos) const;
    void clear();
    size_t find(const MyString& str, size_t pos = 0) const;

    MyString& operator = (const MyString& str);
    MyString& operator += (const MyString& str);
};

bool operator == (const MyString& lhs, const MyString& rhs);
MyString operator + (const MyString& lhs, const MyString& rhs);
std::ostream& operator << (std::ostream& os, const MyString str);

#endif
