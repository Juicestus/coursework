load Computer.hdl,
output-file shift.out,
compare-to shift.cmp,
output-list time%S1.3.1 reset%B2.1.2 R0%D1.7.1 R1%D1.7.1 R2%D1.7.1 PC[]%D0.4.0 RAM16K[4]%D1.7.1 RAM16K[8192]%D1.10.1;

ROM32K load shift.hack,
output;

repeat 33 {
    tick, tock, output;
}