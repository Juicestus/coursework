# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 3-2 
# Date:         8 September 2024
#

import math

x = 2 * math.pi
d = int(input("Please enter the number of digits of precision for tau: "))

f = int(x * 10**(d) + .5) / (10**(d))
print(f"The value of tau to {int(d)} digits is: {f:.{d}f}")

