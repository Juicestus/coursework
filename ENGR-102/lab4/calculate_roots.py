# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 4
# Date:         12 Sept 2024

def inp(x):
    return float(input("Please enter the coefficient {x}: "))

def main():
    a = inp("A")
    b = inp("B")
    c = inp("C")

    r = []

    
    d = b*b - 4*a*c
    if d < 0:


    if a == 0:
        x = -c/b
        r.append(x)

    if a == 0 and b == 0 and c != 0:
        print("You entered an invalid combination of coefficients!")
        return 
    

    

main()
