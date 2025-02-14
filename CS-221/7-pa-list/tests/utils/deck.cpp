#include "deck.h"
#include <iostream>
#include "typegen.h"

int rand221() {
    static Typegen t(RAND221_SEED);
    return t.get<int>();
}