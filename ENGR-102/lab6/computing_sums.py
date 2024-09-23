# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 6
# Date:         23 Sept 2024

l = int(input("Enter an integer: "))
h = int(input("Enter another integer: "))

# i did this in 120
#s = round((h-l+1) * (h+l) * 0.5)
s = 0
for i in range(l , h+1):
    s += i
print(f"The sum of all integers from {l} to {h} is {s}")
