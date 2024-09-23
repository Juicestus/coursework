# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 6
# Date:         23 Sept 2024

# nutty function
a = [int(input("Enter a positive integer: "))]
print(f"The Juggler sequence starting at {a[-1]} is:")
while a[-1] > 1:
    a.append(int(a[-1] ** (0.5 + (a[-1] % 2))))
print(", ".join(map(str, a)))
print(f"It took {len(a)-1} iterations to reach 1")
