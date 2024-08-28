# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 2-2 
# Date:         28 August 2024
#

import math

t1 = 12
p1 = (8, 6, 7)
t2 = 85
p2 = (-5, 30, 9)

# Performs a lerp
def lerp(t):
    p = [0, 0, 0]
    for i in range(3):
        m = (p2[i] - p1[i]) / (t2 - t1)
        p[i] = m * (t - t1) + p1[i]   
    return tuple(p)

# Prints point p with pt num n
def printpt(p, n):
    for i, a in enumerate(['x', 'y', 'z']):
        print(f"{a}{n} = {p[i]} m")

# Perform nth lerp on time t
def action(n, t):
    print(f"At time {t} seconds:")
    p = lerp(t)
    printpt(p, n)

# Do the stuff
for i in range(5):
    t = 30.0 + 7.5 * i
    action(i+1, t)
    if t < 60:
        print("-----------------------")
