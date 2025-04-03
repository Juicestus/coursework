load Computer.hdl,
output-file subtract.out,
compare-to subtract.cmp,
output-list time%S1.3.1 reset%B2.1.2 R0%D1.7.1 R1%D1.7.1 R2%D1.7.1 PC[]%D0.4.0 RAM16K[0]%D1.7.1;

ROM32K load subtract.hack,
output;

repeat 10 {
    tick, tock, output;
}