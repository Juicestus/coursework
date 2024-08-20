# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 1-2 
# Date:         19 August 2024
#

from math import *

# Calculate Reynolds number and output it given 
# mu = 9m/s, L = 0.875m, and v = 0.0015mm/s
print("Reynolds number is", (9 * 0.875) / 0.0015)

# Calculate a wavelength and output it given 
# d = 0.028nm and theta = 35deg
print("Wavelength is", 2 * 0.028 * sin(35 * (pi/180)), "nm")

# Calculate the production rate using the arps
# equation given t = 10days, qi = 100barrels/d, 
# Di = 2/day, b = 0.8
print("Production rate is", 100 / ((1 + 0.8 * 2 * 10) ** (1/0.8)), "barrels/day")

# Calculate the velocity of a fighter jet using
# the Tsiolkovsky rocket equation given m0 = 11000kg, 
# mf = 8300kg, and ve = 2028m/s
print("Change of velocity is", 2028 * (log(11000/8300)), "m/s")
