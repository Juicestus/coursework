# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 6
# Date:         23 Sept 2024

a = int(input("Enter an integer: "))
b = int(input("Enter another integer: "))

# this is retarded
for i in range(1, 101):
    s = ""
    s += "Howdy" * int(i % a == 0)
    s += " " * int(i % a == 0 and i % b == 0)
    s += "Whoop" * int(i % b == 0)
    s += str(i) * int(i % a != 0 and i % b != 0)
    print(s)
