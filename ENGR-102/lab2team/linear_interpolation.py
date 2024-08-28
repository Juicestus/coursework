# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Justus Languell
#               Alvaro Medina Fundora
#               Brian Zhuo
#               James Crawford
# Section:      201
# Assignment:   Lab 2
# Date:         27 Aug 2024
#

import math

# Constant measurements
t1 = 10
p1 = 2028
t2 = t1 + 45
p2 = 23028
r = 6745
c = 2 * math.pi * r

print("Part 1:")    

t = 25                  # Input time = 25
m = (p2-p1)/(t2-t1)     # Calc. slope
p = m * (t - t1) + p1   # Interpolate for position
p %= c                  # Convert to distance past HOU

print(f"For t = {t} minutes, the position p = {p} kilometers")

print("Part 2:")    

t = 300                 # Input time = 300
m = (p2-p1)/(t2-t1)     # Calc. slope
p = m * (t - t1) + p1   # Interpolate for position
p %= c                  # Convert to distance past HOU

print(f"For t = {t} minutes, the position p = {p} kilometers")
