load Computer.hdl,
output-file logic.out,
compare-to logic.cmp,
output-list time%S1.3.1 reset%B2.1.2 R0%D1.7.1 R1%D1.7.1 R2%D1.7.1 PC[]%D0.4.0 RAM16K[0]%D1.7.1 RAM16K[1]%D1.7.1 RAM16K[2]%D1.7.1 RAM16K[3]%D1.7.1 RAM16K[4]%D1.7.1;

set RAM16K[0] 9,
set RAM16K[1] 11,
set RAM16K[3] 6,
ROM32K load logic.hack,
output;

repeat 17 {
    tick, tock, output;
}