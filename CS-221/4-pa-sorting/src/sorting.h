#pragma once

#include <functional> // std::less
#include <iterator> // std::iterator_traits

namespace sort {

	// This is C++ magic which will allows our function
	// to default to using a < b if the comparator arg
	// is unspecified. It uses defines std::less<T>
	// for the iterator's value_type.
	//
	// For example: if you have a vector<float>, the 
	// iterator's value type will be float. std::less 
	// will select the < for sorting floats as the 
	// default comparator.
	template<typename RandomIter>
	using less_for_iter = std::less<typename std::iterator_traits<RandomIter>::value_type>;

	/* Efficiently swap two items - use this to implement your sorts */
	template<typename T>
	void swap(T & a, T & b) noexcept { 
		std::swap(a, b);
	 }

#define at(X) *(begin + difference_type(X))

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void bubble(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		using _it             = std::iterator_traits<RandomIter>;
		using difference_type = typename _it::difference_type;
        int n = end - begin;
        for (int i = 0; i < n-1; i++) {
            bool sorted = true;
            for (int j = 0; j < n - i - 1; j++) {
                if (!comp(at(j), at(j+1))) {
                    swap(at(j), at(j+1));
                    sorted = false;
                }
            }
            if (sorted) break;
        }
	}


	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void insertion(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
        using _it             = std::iterator_traits<RandomIter>;
		using difference_type = typename _it::difference_type;
        int n = end - begin;
        for (int i = 1; i < n; i++) {
            for (int j = i; j > 0 && comp(at(j), at(j-1)); j--) {
                swap(at(j), at(j-1)); 
            }
        }
   }

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void selection(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
        using _it             = std::iterator_traits<RandomIter>;
		using difference_type = typename _it::difference_type;
        int n = end-begin;
        size_t heaviest;
        for (int i = 0; i < n-1; i++) {
            heaviest = i;
            for (int j = i+1; j < n; j++) {
                if (comp(at(j), at(heaviest))) {
                    heaviest = j;
                }
            }
            swap(at(heaviest), at(i));
        }
    }
}
