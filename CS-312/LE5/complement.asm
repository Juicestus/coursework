//complement.asm

//NAME: Justus Languell
//UIN: 135007144

//This asm checks whether two numbers a and b are complements;
//that is, each bit active in a is inactive b, and vice-versa.
//Other ways of saying this are:
// (a & b) = 0 and (a | b) = 0b111..., where & is bitwise AND and | is bitwise OR
// (a + b) = -1
// and any other technique you come up with is ok, as long as it functions properly.
//The two numbers are given in RAM[0] and RAM[1]
//and the result will be stored to RAM[2].
//The result should be 1 if a and b are complements,
//and 0 if they are not.
//Write your code below.
///////////////////////////////////////////////////////////////////////////////
@2
M=1

@0
D=M
@1
D=D+M
D=D+1

@end
D; JEQ

@2
M=0

(end)

