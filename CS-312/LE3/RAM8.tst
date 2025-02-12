//Test Stimulus File for RAM8 Chip


load RAM8.hdl,
output-file RAM8.out,
compare-to RAM8.cmp,
output-list time%S1.4.1 in%B1.8.1 addr%B2.3.2 wr%B2.1.2 out%B1.8.1;

set in %B00000000,
set addr 0,
set wr 0,
tick,
output;
tock,
output;

set in %B00000001,
set addr 1,
set wr 1,
tick,
output;
tock,
output;

set in %B00000010,
set addr 2,
set wr 1,
tick,
output;
tock,
output;

set in %B00000100,
set addr 3,
set wr 1,
tick,
output;
tock,
output;

set in %B00001000,
set addr 4,
set wr 1,
tick,
output;
tock,
output;

set in %B00010000,
set addr 5,
set wr 1,
tick,
output;
tock,
output;

set in %B00100000,
set addr 6,
set wr 1,
tick,
output;
tock,
output;

set in %B01000000,
set addr 7,
set wr 1,
tick,
output;
tock,
output;

set in %B10000000,
set addr 0,
set wr 1,
tick,
output;
tock,
output;

set addr 1,
set wr 0,
tick,
output;
tock,
output;

set addr 2,
set wr 0,
tick,
output;
tock,
output;

set addr 3,
set wr 0,
tick,
output;
tock,
output;

set addr 4,
set wr 0,
tick,
output;
tock,
output;

set addr 5,
set wr 0,
tick,
output;
tock,
output;

set addr 6,
set wr 0,
tick,
output;
tock,
output;

set addr 7,
set wr 0,
tick,
output;
tock,
output;

set addr 0,
set wr 0,
tick,
output;
tock,
output;

