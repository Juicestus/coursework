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

deg2rad = math.pi / 180

# Calculate Reynolds number and output it given 
mu = 9      # m/s
L = 0.875   # m
v = 0.0015  # mm/s
print("Reynolds number is", (mu * L) / v)
      #(9 * 0.875) / 0.0015)

# Calculate a wavelength and output it given 
d = 0.028   # nm
theta = 35  # deg
print("Wavelength is", 2 * d * math.sin(35 * deg2rad), "nm")
      #2 * 0.028 * math.sin(35 * (pi/180)), "nm")

# Calculate the production rate using the arps
# equation given 
t = 10      # days
qi = 100    # barrels/d
Di = 2      # 1/day
b = 0.8     # ratio
print("Production rate is", qi / ((1 + b * Di * t) ** (1/b)), "barrels/day")
      #100 / ((1 + 0.8 * 2 * 10) ** (1/0.8))

# Calculate the velocity of a fighter jet using
# the Tsiolkovsky rocket equation given 
m0 = 11000  # kg
mf = 8300   # kg
ve = 2028   # m/s
print("Change of velocity is", ve * (math.log(m0/mf)), "m/s")
      #2028 * (math.log(11000/8300)), "m/s")
