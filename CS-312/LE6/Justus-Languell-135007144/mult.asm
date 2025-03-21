//mult.asm

//NAME: Justus Languell
//UIN: 135007144

//This asm computes the mult of two numbers
//Assuming R0 stores the value n1, R1 stores value n2 
//and the final result is stored in R2.
///////////////////////////////////////////////////////////////////////////////

@1
D=M

@2
M=0

@ctr
M=D

(iter)
    @0
    D=M

    @2
    M=D+M

    @ctr
    M=M-1
    D=M

    @iter
    D ; JGT

    //one try lfg

