#pragma once

/*
    Retrieves the next prime > size via a lookup table.

    Scales with O(log(n)) where n is the size of the lookup
    table. (E.g. it uses binary search.)

    Practically very fast.
*/
size_t next_greater_prime(size_t size);