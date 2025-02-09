//Test stimulus file for Add6 


load Add6.hdl,
output-file Add6.out,
compare-to Add6.cmp,
output-list a%B1.6.1 b%B1.6.1 out%B1.6.1 carry%B3.1.3;

set a %B000001,
set b %B000001,
eval,
output;

set a %B000000,
set b %B111111,
eval,
output;

set a %B101010,
set b %B010101,
eval,
output;

set a %B001100,
set b %B110011,
eval,
output;

set a %B010010,
set b %B011001,
eval,
output;

set a %B110010,
set b %B011001,
eval,
output;

set a %B111111,
set b %B111111,
eval,
output;
