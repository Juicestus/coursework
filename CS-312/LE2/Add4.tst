//Test stimulus file for Add4


load Add4.hdl,
output-file Add4.out,
compare-to Add4.cmp,
output-list a%B1.4.1 b%B1.4.1 c%B1.1.1 out%B1.4.1 carry%B3.1.3;

set a %B0001,
set b %B0001,
set c %B0,
eval,
output;

set a %B0001,
set b %B0001,
set c %B1,
eval,
output;

set a %B0000,
set b %B1111,
set c %B0,
eval,
output;

set a %B0000,
set b %B1111,
set c %B1,
eval,
output;

set a %B1010,
set b %B0101,
set c %B0,
eval,
output;

set a %B1010,
set b %B0101,
set c %B1,
eval,
output;

set a %B0110,
set b %B1001,
set c %B0,
eval,
output;

set a %B1101,
set b %B0101,
set c %B0,
eval,
output;

set a %B1010,
set b %B0011,
set c %B0,
eval,
output;

set a %B1010,
set b %B0011,
set c %B1,
eval,
output;

set a %B1111,
set b %B1111,
set c %B0,
eval,
output;
