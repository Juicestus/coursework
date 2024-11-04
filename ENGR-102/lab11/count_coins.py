# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 11
# Date:         4 Nov 2024

instrs = []
with open('game.txt', 'r') as f:
    for l in f:
        _ = l.split(' ')
        instrs.append((_[0].strip(), int(_[1].strip().replace('+', ''))))
    
size = len(instrs) # program size
ctr = 0 # program counter
coins = 0

log = open('coins.txt', 'w')

while ctr < size:
    instr, n = instrs[ctr]
    # print(f'#{ctr} -> {instr}({n})')
    if instr == 'coin':
        coins += n
        log.write(str(n) + '\n')
        ctr += 1
    elif instr == 'jump':
        ctr += n
    else:
        ctr += 1
        
log.close()
        
print(f'Total coins collected: {coins}')
