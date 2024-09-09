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

def printresult(shape, side, area):
    '''Print the result of the calculation'''
    print(f'A {shape} with side {side:.2f} has area {area:.3f}')

def area(n, s):
    if n == 4: return s*s
    return (n*s*s)/(4*math.tan(math.pi/n))

side = float(input("Please enter the side length: "))
print()

# this is so dumb
printresult("triangle", side, round(area(3, side), 3))
printresult("square", side, round(area(4, side), 3))
printresult("pentagon", side, round(area(5, side), 3))
printresult("hexagon", side, round(area(6, side), 3))
printresult("dodecagon", side, round(area(12, side), 3))
