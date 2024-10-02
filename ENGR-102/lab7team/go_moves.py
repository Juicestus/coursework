# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Justus Languell
#               Alvaro Medina Fundora
# Section:      201
# Assignment:   Lab 7
# Date:         30 Sept 2024
#

import math

B = chr(9675)
W = chr(9679)

r = list(range(1, 10))

board = [ ['.' for i in range(9)] for i in range(9) ]
n = 0
while True:
    print("  " + "".join([str(a) for a in r]))
    for i, row in enumerate(board):
        print(str(i+1) + " " + "".join(row))

    if n % 2 == 0:
        print("Its white's turn")
    else:
        print("Its blacks's turn")
    inp = input("Input x, y position, or print quit to exit: ")
    if inp == "quit": 
        break
    s = inp.split(',')
    x = int(s[0].strip())
    y = int(s[1].strip())
    if x not in r or y not in r:
        print("Invalid range")
        continue
    if board[y-1][x-1] != '.':
        print("That spot is taken")
        continue
    if n % 2 == 0:
        board[y-1][x-1] = W
    else:
        board[y-1][x-1] = B
    n += 1
    
   

