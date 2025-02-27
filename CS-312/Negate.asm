// Negate the value stored in mem[0]

@0          // A = 0; M = mem[A] = mem[0]
D = M       // load mem[0] to D
D = !D      // negate bits of D
D = D+1     // instr for increment

@1
M = D       // store 
