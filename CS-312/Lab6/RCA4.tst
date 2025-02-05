//RCA4.tst

load RCA4.hdl,
output-file RCA4.out,
compare-to RCA4.cmp,
output-list a%B1.4.1 b%B1.4.1 sum%B1.4.1 cout%B3.1.3;

set a %B0000,
set b %B0000,
eval,
output;

set a %B1111,
set b %B1111,
eval,
output;

set a %B0000,
set b %B1111,
eval,
output;

set a %B1010,
set b %B0101,
eval,
output;

set a %B0011,
set b %B1100,
eval,
output;

set a %B0001,
set b %B0001,
eval,
output;

set a %B0010,
set b %B0010,
eval,
output;

set a %B0100,
set b %B0100,
eval,
output;

set a %B1000,
set b %B1000,
eval,
output;
