# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 12
# Date:         11 Nov 2024

import numpy as np
import matplotlib.pyplot as plt

pt = np.array([0, 1])
mat = np.array([[1.02, 0.095], [-0.095, 1.02]])
xs, ys = [], []

for i in range(250):
    print(pt)
    pt = np.matmul(pt, mat)
    xs.append(pt[0])
    ys.append(pt[1])

plt.figure(figsize=(8, 8))
plt.plot(xs, ys)
plt.title('Elliptical Spiral')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True)
plt.axis('equal')
plt.show()