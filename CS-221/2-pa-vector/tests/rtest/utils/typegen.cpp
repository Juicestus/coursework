#include "typegen.h"

using uchar = unsigned char;

Typegen::charset operator|(Typegen::charset const & lhs, Typegen::charset const & rhs) {
    return static_cast<Typegen::charset>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

struct char_range {
    Typegen::charset c;
    uchar start;
    uchar end; // not inclusive
};

static char_range const char_ranges[] = {
    { Typegen::ASCII_NULL,        0x00, 0x01 },
    { Typegen::ASCII_CONTROL,     0x01, 0x20 },
    { Typegen::ASCII_SYMBOLS,     0x20, 0x30 },
    { Typegen::ASCII_NUMERIC,     0x30, 0x3A },
    { Typegen::ASCII_SYMBOLS,     0x3A, 0x41 },
    { Typegen::ASCII_UPPER_ALPHA, 0x41, 0x58 },
    { Typegen::ASCII_SYMBOLS,     0x5B, 0x61 },
    { Typegen::ASCII_LOWER_ALPHA, 0x61, 0x7B },
    { Typegen::ASCII_SYMBOLS,     0x7B, 0x7F },
    { Typegen::ASCII_CONTROL,     0x7F, 0x80 }
};

#define LEN(x) (sizeof(x)/sizeof(*x))

char Typegen::_get_char(charset sets) {
    char symbols = 0;
    for(char_range const & r : char_ranges) {
        if(sets & r.c)
            symbols += r.end - r.start;
    }

    char sample = rand() % symbols;
    char offset = 0;
    for(char_range const & r : char_ranges) {
        if(sets & r.c) {
            char len = r.end - r.start;

            if(offset + len > sample) {
                return r.start + (sample - offset);
            }

            offset += len;
        }
    }

    return 0;
}