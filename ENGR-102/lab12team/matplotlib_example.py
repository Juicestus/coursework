# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 10
# Date:         18 Nov 2024
#
import matplotlib.pyplot as plt
import numpy as np

# Part 1
x = np.linspace(-2.0, 2.0, 100)
y1 = (1 / (4 * 2)) * x**2  
y2 = (1 / (4 * 6)) * x**2 
plt.figure()
plt.plot(x, y1, label="f=2", linewidth=2.0, color="red")
plt.plot(x, y2, label="f=6", linewidth=6.0, color="blue")
plt.title("Parabola plots with varying focal length")
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.grid()
plt.show()

# Part 2
x = np.linspace(-4.0, 4.0, 25)
y = 2 * x**3 + 3 * x**2 - 11 * x - 6
plt.figure()
plt.plot(x, y, marker="*", linestyle='none', label="Cubic Polynomial", color="gold", markeredgecolor='black')
plt.title("Plot of cubic polynomial")
plt.xlabel("x values")
plt.ylabel("y values")
plt.grid()
plt.show()

# Part 3
x = np.linspace(-2 * np.pi, 2 * np.pi, 100)
sin_y = np.sin(x)
cos_y = np.cos(x)

plt.figure()
plt.title("Plot of cos(x) and sin(x)")
plt.subplot(2, 1, 1)
plt.plot(x, cos_y, label="cos(x)", color="red")
plt.xlabel("x")
plt.ylabel("y=cos(x)")
plt.grid()
plt.legend()

plt.subplot(2, 1, 2)
plt.plot(x, sin_y, label="sin(x)", color="blue")
plt.xlabel("x")
plt.ylabel("y=sin(x)")
plt.grid()
plt.legend()

plt.tight_layout()
plt.show()
