#pragma once

#include <string>

struct polynomial_rolling_hash {
    size_t operator() (std::string const & str) const;
};

struct fnv1a_hash {
    size_t operator() (std::string const & str) const;
};
