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

############ Part A ############
def inp(x):
    return input(f"Enter True or False for {x}: ") in ["T", "t", "True"]

a = inp("a")
b = inp("b")
c = inp("c")

############ Part B ############
print("a and b and c:", a and b and c)
print("a or b or c:", (a or b) or c)

############ Part C ############
print("XOR:", (a or b) and not (a and b))

############ Part D ############
print("Odd number:", 
      (a and not(b or c)) or
      (b and not(a or c)) or
      (c and not (a or b)) or
      (a and b and c))
