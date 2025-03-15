load addn.asm,
output-file addn.out,
compare-to addn.cmp,
output-list RAM[0]%D2.6.2;// RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[3]%D2.6.2 RAM[4]%D2.6.2;

set PC 0,
set RAM[0] 2,
set RAM[1] 1,
set RAM[2] 1,
set RAM[3] 0,
set RAM[4] 0,
repeat 100 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 1,
set RAM[1] 3,
set RAM[2] 0,
set RAM[3] 0,
set RAM[4] 0,
repeat 100 {
	ticktock;
}
output;
set PC 0,
set RAM[0] 3,
set RAM[1] 4,
set RAM[2] 5,
set RAM[3] 3,
set RAM[4] 0,
repeat 100 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 2,
set RAM[1] 1,
set RAM[2] 1,
set RAM[3] 1,
set RAM[4] 0,
repeat 100 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 0,
set RAM[1] 1,
set RAM[2] 2,
set RAM[3] 3,
set RAM[4] 4,
repeat 100 {
	ticktock;
}
output;