//Test Stimulus for Inc16 chip

load Inc16.hdl,
output-file Inc16.out,
compare-to Inc16.cmp,
output-list in%B1.16.1 out%B1.16.1;

set in %B0000000000000000,  
eval,
output;

set in %B1111111111111111,  
eval,
output;

set in %B0000000000000101,  
eval,
output;

set in %B1111111111111011,  
eval,
output;
