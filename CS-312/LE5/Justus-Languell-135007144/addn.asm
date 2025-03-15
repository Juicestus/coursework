//addn.asm

//NAME: Justus Languell
//UIN: 135007144

//This asm computes the sum of n numbers
//Assuming RAM[0] stores the value n (how many numbers to sum)
//and the numbers are stored in consecutive addresses starting at address 1.
//The result will be stored in RAM[0], overwriting the original value of n.
//It may be useful to use variables when solving this problem.
//Write your code below.
///////////////////////////////////////////////////////////////////////////////

@sum
M = 0

(iter)
    @0
    A=M     // go to addr 
    D=M     
    @sum
    D=D+M
    M=D
    @0
    M=M-1
    D=M
    @iter
    D ; JGT

@sum
D=M
@0
M=D

