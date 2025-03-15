load add.asm,
output-file add.out,
compare-to add.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 1,
set RAM[1] 1,
set RAM[2] 0,
repeat 10 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 1,
set RAM[1] 0,
set RAM[2] 0,
repeat 10 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 1,
set RAM[1] -1,
set RAM[2] 0,
repeat 10 {
	ticktock;
}
output;

set PC 0,
set RAM[0] -3,
set RAM[1] 7,
set RAM[2] 0,
repeat 10 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 45,
set RAM[1] 67,
set RAM[2] 0,
repeat 10 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 1231,
set RAM[1] 3547,
set RAM[2] 0,
repeat 10 {
	ticktock;
}
output;

set PC 0,
set RAM[0] -4,
set RAM[1] -6,
set RAM[2] 0,
repeat 10 {
	ticktock;
}
output;

