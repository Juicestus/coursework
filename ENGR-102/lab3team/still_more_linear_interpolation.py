# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
#               Alvaro Medina Fundora
# Section:      201
# Assignment:   Lab 3
# Date:         28 August 2024
#

import math

def inputpt(ts):
    p = [0, 0, 0]
    for i, a in enumerate(['x', 'y', 'z']):
        p[i] = float(input(f"Enter the {a} position of the object at time {ts}: "))
    return tuple(p)

t1 = float(input("Enter time 1: "))
p1 = inputpt(1)
t2 = float(input("Enter time 2: "))
p2 = inputpt(2)

# Performs a lerp
def lerp(t):
    p = [0, 0, 0]
    for i in range(3):
        m = (p2[i] - p1[i]) / (t2 - t1)
        p[i] = m * (t - t1) + p1[i]   
    return tuple(p)

# Convert pt to str
def strpt(p):
    s = "("
    for i, a in enumerate(['x', 'y', 'z']):
        s += f"{p[i]:.3f}, "
    return s[:-2] + ")"

# Perform nth lerp on time t
def action(t):
    p = lerp(t)
    print(f"At time {t:.2f} seconds the object is at {strpt(p)}")

print()
i = t1
stp = (t2-t1)/4
while i <= t2:
    action(i)
    i += stp
