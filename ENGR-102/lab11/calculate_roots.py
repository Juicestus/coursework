# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 4
# Date:         12 Sept 2024

import math

def inp(x):
    return float(input(f"Please enter the coefficient {x}: "))

def R(l):
    n = len(l)
    if n == 2:
        return f"The roots are x = {l[0]} and x = {l[1]}"
    else:
        return f"The root is x = {l[0]}"

def main():
    a = inp("A")
    b = inp("B")
    c = inp("C")

    if a == 0:
        if b == 0 and c != 0: 
            return "You entered an invalid combination of coefficients!"
        x = -c/b
        return R([x])


    d = b*b - 4*a*c
    if d > 0:
        d = math.sqrt(d)
        x1 = (-b + d) / (2 * a)
        x2 = (-b - d) / (2 * a)
        return R([x1, x2])

    if d == 0:
        x = (-b + d) / (2 * a)
        r = f"x = {x}"
        return R([x])

    else:
        d = math.sqrt(-d)
        l = -b / (2 * a) # real
        i = d / (2 * a)
        return R([f"{l} + {i}i", f"{l} - {i}i"])

print(main())
