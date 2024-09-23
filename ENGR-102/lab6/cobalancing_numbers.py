# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 6
# Date:         23 Sept 2024

n = int(input("Enter a value for n: "))

# O(n) time, currious if one could do it faster
S = ((n+1) * n) / 2

s = 0
r = 1
while True:
    s += n + r
    if s == S:
        print(f"{n} is a co-balancing number with r={r}")
        break
    elif s > S:
        print(f"{n} is not a co-balancing number")
        break
    r += 1
