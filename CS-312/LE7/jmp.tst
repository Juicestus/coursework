load Computer.hdl,
output-file jmp.out,
compare-to jmp.cmp,
output-list time%S1.3.1 reset%B2.1.2 R0%D1.7.1 R1%D1.7.1 R2%D1.7.1 PC[]%D0.4.0;

ROM32K load jmp.hack,
output;

repeat 50 {
    tick, tock, output;
}