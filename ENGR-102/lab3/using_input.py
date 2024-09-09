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

def numinput(x): 
      a = float(input(x))
      print()
      return a

print("This program calculates the Reynolds number given velocity, length, and viscosity")
# Calculate Reynolds number and output it given 
mu =   numinput("Please enter the velocity (m/s): ")    # m/s
L = numinput("Please enter the length (m): ")   # m
v = numinput("Please enter the viscosity (m^2/s): ")  # mm/s
print("Reynolds number is", round((mu * L) / v))
print()
print("This program calculates the wavelength given distance and angle")
# Calculate a wavelength and output it given 
d = numinput("Please enter the distance (nm): ") # nm
theta = numinput("Please enter the angle (degrees): ") # deg
print(f"Wavelength is", f"{round(2 * d * math.sin(theta * deg2rad), 4):.4f}", "nm")
print()
print("This program calculates the production rate given time, initial rate, and decline rate")
# Calculate the production rate using the arps
# equation given 
t = numinput("Please enter the time (days): ")    # days
qi = numinput("Please enter the initial rate (barrels/day): ")  # barrels/d
Di = numinput("Please enter the decline rate (1/day): ")      # 1/day
b = 0.8 
print("Production rate is", f"{round(qi / ((1 + b * Di * t) ** (1/b)), 2):.2f}", "barrels/day")
print()
print("This program calculates the change of velocity given initial mass, final mass, and exhaust velocity")
# Calculate the velocity of a fighter jet using
# the Tsiolkovsky rocket equation given 
m0 = numinput("Please enter the initial mass (kg): ") # kg
mf = numinput("Please enter the final mass (kg): ") # kg
ve = numinput("Please enter the exhaust velocity (m/s): ")  # m/s
print("Change of velocity is", f"{round(ve * (math.log(m0/mf)), 1):.1f}", "m/s")
