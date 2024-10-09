# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 7
# Date:         8 Oct 2024

from math import log10

pts = [(1.3, 1000), (5, 7000), (30, 1.5e6), (120, 2.5e4), (1200, 1.5e6)]

# funky function 1
# funky function 1
# funky function 1
# funky function 1
# funky function 1
# funky function 1
# funky function 1
# funky function 1
# funky function 1
# funky function 1
# funky function 1
def interp(x):
    for i in range(len(pts)-1):
        x0 = pts[i][0]
        y0 = pts[i][1]
        x1 = pts[i+1][0]
        y1 = pts[i+1][1]
        if x0 <= x and x1 > x:
            m = log10(y1/y0) / log10(x1/x0)
            y = y0 * ((x/x0) ** m)
            return y
    return None


T = float(input("Enter the excess temperature: "))
q = interp(T)
if q is None:
    print("Surface heat flux is not available")
else:
    q = round(q)
    print(f"The surface heat flux is approximately {q} W/m^2")
