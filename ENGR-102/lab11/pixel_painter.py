# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 11
# Date:         4 Nov 2024

infn = input("Enter the filename: ")
ofn = infn.replace(".csv", ".txt")

c = input("Enter a character: ")

inf = open(infn, "r")
of = open(ofn, "w")

for l in inf:
    for i, n in enumerate(l.split(",")):
        of.write( (c if i % 2 == 1 else ' ') * int(n) )
    of.write("\n")
inf.close()
of.close()

print(f"{ofn} created!")

# Obungus!
        