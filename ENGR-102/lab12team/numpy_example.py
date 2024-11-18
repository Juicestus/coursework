# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 10
# Date:         18 Nov 2024
#
import numpy as np

A = np.arange(12).reshape(3, 4)
B = np.arange(8).reshape(4, 2)
C = np.arange(6).reshape(2, 3)

# Print matrices
print("A =", A)
print()
print("B =", B)
print()
print("C =", C)

# A * B * C matmul (why is it @!)
D = A @ B @ C
print("D =", D)
print(D)

D_T = D.T
print()
print("D^T =", D_T)

E = np.sqrt(D) / 2
print()
print("E =", E)
