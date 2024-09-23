# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Justus Languell
#               Alvaro Medina Fundora
# Section:      201
# Assignment:   Lab 5
# Date:         23 Sept 2024
#

import math

# Input
s = float(input("Enter the side length in meters: "))
n = int(input("Enter the number of layers: "))

# Do some loop 
A = 0
l = 0
for i in range(1, n+1):
    t = i * i * s * s
    A += t + 4 * i * s * s
    A -= l
    l = t

print(f"You need {A:.2f} m^2 of gold foil to cover the pyramid")
