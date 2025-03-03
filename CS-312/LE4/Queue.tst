load Queue.hdl,
output-file Queue.out,
compare-to Queue.cmp,
output-list time%S1.4.1 Q0%D1.2.1 Q1%D1.2.1 Q2%D1.2.1 REQ%D1.3.1 CMPL%D1.4.1 D0%D1.2.1 D1%D1.2.1 D2%D1.2.1 QREQ%D1.4.1 STALL%D1.5.1;

output;

// No Input
set REQ 0,
set CMPL 0,
tick,
output;
tock,
output;

// Fill Queue to STALL
set REQ 1,
set CMPL 0,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
tick,
output;
tock,
output;

// Empty Queue
set REQ 0,
set CMPL 1,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
tick,
output;
tock,
output;

// Fill Queue to STALL
set REQ 1,
set CMPL 1,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
tick,
output;
tock,
output;

// One Item Through
set REQ 1,
set CMPL 0,
tick,
output;
tock,
output;
set REQ 0,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
set CMPL 1,
tick,
output;
tock,
output;

set REQ 1,
set CMPL 1,
tick,
output;
tock,
output;
set REQ 0,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
tick,
output;
tock,
output;

// Push two items through
set REQ 1,
set CMPL 0,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
set REQ 0,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
set CMPL 1,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
tick,
output;
tock,
output;

set REQ 1,
set CMPL 1,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
set REQ 0,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
tick,
output;
tock,
output;

// Push two items through with a gap
set REQ 1,
set CMPL 0,
tick,
output;
tock,
output;
set REQ 0,
tick,
output;
tock,
output;
set REQ 1,
tick,
output;
tock,
output;
set REQ 0,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
set CMPL 1,
tick,
output;
tock,
output;
tick,
output;
tock,
output;

set REQ 1,
set CMPL 1,
tick,
output;
tock,
output;
set REQ 0,
tick,
output;
tock,
output;
set REQ 1,
tick,
output;
tock,
output;
set REQ 0,
tick,
output;
tock,
output;
tick,
output;
tock,
output;
tick,
output;
tock,
output;