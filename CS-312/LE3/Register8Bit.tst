// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.

load Register8Bit.hdl,
output-file Register8Bit.out,
compare-to Register8Bit.cmp,
output-list time%S1.4.1 in%D1.6.1 load%B2.1.2 out%D1.6.1;

set in 0,
set load 0,
tick,
output;

tock,
output;

set in 0,
set load 1,
tick,
output;

tock,
output;

set in 127,
set load 0,
tick,
output;

tock,
output;

set in 127,
set load 0,
tick,
output;

tock,
output;

set in 255,
set load 1,
tick,
output;

tock,
output;

set in 121,
set load 1,
tick,
output;

tock,
output;

set in 0,
set load 0,
tick,
output;

tock,
output;

set in 0,
set load 1,
tick,
output;

tock,
output;