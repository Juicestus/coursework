# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Justus Languell
#               Alvaro Medina Fundora
# Section:      201
# Assignment:   Lab 3
# Date:         27 Aug 2024
#

import math

# Function to print the conversion
def conv(x, f, l, c, m=0):
    print(f"{x:.2f} {f} is equivalent to {x*c+m:.2f} {l}")

x = float(input("Please enter the quantity to be converted: "))

conv(x, "pounds force", "newtons", 4.44822)
conv(x, "meters", "feet", 3.28084)
conv(x, "atmospheres", "kilopascals", 101.325)
conv(x, "watts", "BTU per hour", 3.412141633)
conv(x, "liters per second", "US gallons per minute", 
     15.850323140625)
     #15.850372483753)
conv(x, "degrees Celsius", "degrees Fahrenheit", 9/5, m=32)
