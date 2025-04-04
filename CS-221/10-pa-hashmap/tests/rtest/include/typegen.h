#pragma once

#include <iostream>
#include <type_traits>
#include <string>
#include <unordered_set>
#include <utility>
#include <iterator>

#include "xoshiro256.h"

/*
    Years of tedious research has shown
    that the inital seed 0x12345678 generates
    the most random numbers
    - Alex
*/
#define DEFAULT_SEED 0x12345678
#define DEFAULT_STRING_LEN 10

class Typegen {

    xoshiro256 rand;

    public:

    enum charset {
        ASCII_UPPER_ALPHA   = (1 << 0),
        ASCII_LOWER_ALPHA   = (1 << 1),
        ASCII_NUMERIC       = (1 << 2),
        ASCII_SYMBOLS       = (1 << 3),
        ASCII_CONTROL       = (1 << 4),
        ASCII_NULL          = (1 << 5),
        ASCII_ALPHA         = (ASCII_UPPER_ALPHA | ASCII_LOWER_ALPHA),
        ASCII_ALPHA_NUMERIC = (ASCII_ALPHA | ASCII_NUMERIC),
        ASCII_VISABLE       = (ASCII_ALPHA_NUMERIC | ASCII_SYMBOLS),
        ASCII_NONTERMINAL   = (ASCII_VISABLE | ASCII_CONTROL),
        ASCII_ALL           = (ASCII_NONTERMINAL | ASCII_NULL)
    };

    private:

    char _get_char(charset c);

    public:


    Typegen(uint64_t seed = DEFAULT_SEED)
        : rand(seed)
    { }

    /*
        Some C++ gobbledygook which will try down casting
        to extract the lower n-bits if the template type is
        integral (integer in nature)
    */
    template<
        typename Integral,
        typename std::enable_if<
            std::is_integral<Integral>{} 
            && !std::is_same<Integral, bool>{}
            && !std::is_same<Integral, char>{},
            Integral
        >::type = true
    >
    // typename std::enable_if<std::is_integral<T>::value, T>::type
    Integral get() { return static_cast<Integral>(rand()); }

    /*
        Scoped template specification doesn't work in GCC.
        This is a work around.
        
        https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85282
    */
    template<typename T>
    typename std::enable_if<std::is_same<T, char>::value, T>::type
    get(charset C = ASCII_VISABLE) { return _get_char(C); }

    template<
        typename Boolean,
        typename std::enable_if<std::is_same<Boolean, bool>::value, Boolean>::type = true
    >
    Boolean get() {
        return rand() % 2 == 0;
    }

    template<
        typename Floating,
        typename std::enable_if<
            std::is_floating_point<Floating>{},
            bool
        >::type = true
    >
    Floating get() {
        return unit<Floating>();
    }
    
    template<
        typename Boolean,
        typename Floating,
        typename std::enable_if<
            std::is_same<Boolean, bool>{} && std::is_floating_point<Floating>{},
            bool
        >::type = true
    >
    Boolean get(Floating p) { return unit<Floating>() < p; }

    /*
        Fill an iterator with optional arguements passed to the random
        generation methods.

        Example:

        std::vector<std::string> vec(26, "");
        Typegen t;
        size_t const STRING_LEN = 100;
        // Here the string length arguement is optional
        // All arguements are forwarded to the equivalent
        // get method.
        t.fill(vec.begin(), vec.end(), STRING_LEN);
    */
    template<typename Iterator, typename ...Args>
    Iterator fill(Iterator begin, Iterator end, Args&&... args) {
        for(Iterator it = begin; it != end; it++)
            *it = get<typename std::iterator_traits<Iterator>::value_type>(std::forward<Args>(args)...);
        
        return begin;
    }

    template<typename RandIter, typename ...Args>
    RandIter shuffle(RandIter begin, RandIter end, Args&&... args) {
        size_t idx;
        for(RandIter it = begin; it != end; it++) {
            idx = range<size_t>(end - begin);
            std::swap(*it, begin[idx]);
        }
        return begin;
    }

    template<
        typename Iterator,
        typename Hash = std::hash<typename std::iterator_traits<Iterator>::value_type>,
        typename KeyEqual = std::equal_to<typename std::iterator_traits<Iterator>::value_type>,
        typename ...Args
    >
    Iterator fill_unique(Iterator begin, Iterator end, Args&&... args) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;

        std::unordered_set<value_type, Hash, KeyEqual> set;

        for(Iterator it = begin; it != end; it++) {
            value_type v;
            
            do
                v = get<value_type>(std::forward<Args>(args)...);
            while(set.end() != set.find(v));

            *it = v;
            set.insert(v);
        }

        return begin;
    }

    /*
        Simple one element sampling:

        static std::array dates {
            "Aug",
            "Sept",
            "Oct",
            "Nov",
            "Dec"
        };

        std::cout << t.sample(dates.begin(), dates.end()); // "Aug"
    */
    template<typename Iterator>
    typename std::iterator_traits<Iterator>::value_type
    sample(Iterator begin, Iterator end) {
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        difference_type dist = rand() % std::distance(begin, end);
        Iterator it = begin;
        while(dist--)
            it++;
        return *it;
    }
    
    template<typename T>
    typename std::enable_if<std::is_same<T, std::string>::value, T>::type
    get(size_t len = DEFAULT_STRING_LEN, charset c = ASCII_VISABLE) {
        std::string str(len, 0);

        for(size_t i = 0; i < len; i++)
            str[i] = _get_char(c);

        return str;
    }

    template<typename T>
    typename std::enable_if<std::is_same<T, 
        std::pair<typename T::first_type, typename T::second_type>>::value,
    T>::type
    get() {
        T pair;

        pair.first = get<typename T::first_type>();
        pair.second = get<typename T::second_type>();

        return pair;
    }

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    nonzero() { 
        T r;
        while(!(r = static_cast<T>(rand())));
        return r;
    }

    /*
        Generate a value in the interval [low, high)
    */
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    range(T low, T high) {
        return low + (rand() % static_cast<uint64_t>(high - low));
    }

    template<typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    range(T low, T high) {
        return (high - low) * unit<T>() + low;
    }

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    range(T high) {
        return range(static_cast<T>(0), high);
    }

    /*
        Generate a floating point number in the unit interval [0, 1)
    */
    template<typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    unit() {
        if(std::is_same<T, double>::value) {
            return static_cast<double>((rand() >> 11) * 0x1.0p-53);
        } else if(std::is_same<T, float>::value) {
            return static_cast<float>((rand() >> 43) * 0x1.0p-21);
        }

        return 0;
    }

};

Typegen::charset operator|(Typegen::charset const & lhs, Typegen::charset const & rhs);
