# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Justus Languell
#               Alvaro Medina Fundora
# Section:      201
# Assignment:   Lab 4
# Date:         27 Aug 2024
#

import math

# Input

def inp(c):
    return int(input(f"Please enter the coefficient {c}: "))

coefs = [("x^2", inp("A")), ("x", inp("B")), ("", inp("C"))]

eq = ""
for x, coef in coefs:
    if coef == 0: continue
    sign = '+' if coef > 0 else '-'
    coef = abs(coef)
    coefstr = str(coef) if len(x) == 0 or coef != 1 else ""
    eq += f"{sign} {coefstr}{x} "
eq += "= 0"
if eq[:2] == "+ ": eq = eq[2:]
print("The quadratic equation is", eq)
