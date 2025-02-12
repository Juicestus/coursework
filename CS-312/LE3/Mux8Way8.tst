//Test Stimulus File for Mux4Way16 Chip


load Mux8Way8.hdl,
output-file Mux8Way8.out,
compare-to Mux8Way8.cmp,
output-list a%B1.8.1 b%B1.8.1 c%B1.8.1 d%B1.8.1 e%B1.8.1 f%B1.8.1 g%B1.8.1 h%B1.8.1 sel%B2.3.2 out%B1.8.1;

set a 0,
set b 0,
set c 0,
set d 0,
set e 0,
set f 0,
set g 0,
set h 0,
set sel 0,
eval,
output;

set sel 1,
eval,
output;

set sel 2,
eval,
output;

set sel 3,
eval,
output;

set a %B00010010,
set b %B10011000,
set c %B10101010,
set d %B01010101,
set e %B11111111,
set f %B00000000,
set g %B10100000,
set h %B01010000,
set sel 0,
eval,
output;

set sel 1,
eval,
output;

set sel 2,
eval,
output;

set sel 3,
eval,
output;

set sel 4,
eval,
output;

set sel 5,
eval,
output;

set sel 6,
eval,
output;

set sel 7,
eval,
output;
