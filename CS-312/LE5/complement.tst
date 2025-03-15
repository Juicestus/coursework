load complement.asm,
output-file complement.out,
compare-to complement.cmp,
output-list RAM[0]%B2.16.2 RAM[1]%B2.16.2 RAM[2]%B3.1.3;

set PC 0,
set RAM[0] %B0000000000000000,
set RAM[1] %B0000000000000000,
set RAM[2] 0,
repeat 20 {
	ticktock;
}
output;

set PC 0,
set RAM[0] %B0011101000110010,
set RAM[1] %B1100010111001101,
set RAM[2] 0,
repeat 20 {
	ticktock;
}
output;

set PC 0,
set RAM[0] %B0111000001010010,
set RAM[1] %B1000111000101101,
set RAM[2] 0,
repeat 20 {
	ticktock;
}
output;

set PC 0,
set RAM[0] %B0111000001010010,
set RAM[1] %B1000111111101101,
set RAM[2] 0,
repeat 20 {
	ticktock;
}
output;

set PC 0,
set RAM[0] %B0101010101010101,
set RAM[1] %B1010101010101010,
set RAM[2] 0,
repeat 20 {
	ticktock;
}
output;

set PC 0,
set RAM[0] %B0101010101010101,
set RAM[1] %B0101010101010101,
set RAM[2] 0,
repeat 20 {
	ticktock;
}
output;

set PC 0,
set RAM[0] %B1010101010101010,
set RAM[1] %B1010101010101010,
set RAM[2] 0,
repeat 20 {
	ticktock;
}
output;

set PC 0,
set RAM[0] %B0000000000000000,
set RAM[1] %B1111111111111111,
set RAM[2] 0,
repeat 20 {
	ticktock;
}
output;