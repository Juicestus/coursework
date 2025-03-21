load mult.asm,
output-file mult.out,
compare-to mult.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 3,
set RAM[1] 4,
repeat 50 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 8,
set RAM[1] 3,
repeat 50 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 9,
set RAM[1] 1,
repeat 50 {
	ticktock;
}
output;
