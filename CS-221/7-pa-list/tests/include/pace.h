#pragma once

#include <iterator>

template<typename BiIter, typename ConstIter>
BiIter pace(BiIter it, size_t amount, bool & reversed, ConstIter begin, ConstIter end) {
    if(begin == end)
        return it;

    if(it == end)
        it--;
    
    auto _it = it;

    if(it == begin && ++_it == end)
        return it;
    
    while(amount--) {
        _it = it;

        if(_it == begin && reversed) reversed = false;
        else if(++_it == end && !reversed) reversed = true;

        if(reversed) it--;
        else it++;
    }

    return it;
}

template<typename Container>
typename Container::const_iterator pace(const Container & ll, typename Container::const_iterator it, size_t amount, bool & reversed) {
    return pace(it, amount, reversed, std::cbegin(ll), std::cend(ll));
}

template<typename Container>
typename Container::iterator pace(const Container & ll, typename Container::iterator it, size_t amount, bool & reversed) {
    return pace(it, amount, reversed, std::cbegin(ll), std::cend(ll));
}
