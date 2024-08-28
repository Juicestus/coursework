# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 2-3
# Date:         28 August 2024
#

# print 1
x = 1
z = 0
z += x
print(z)

# print 28
y = 10
x += 1
x += 1
x += 1
y += x
x = 1
x += 1
y *= x
z = 0
z += y
print(z)

# print 102
y += x
y += x
y += x
x += 1
y *= x
z = 0
z += y
print(z)

# print 1000000000000
y = 10
x = y
y *= x
y *= x
y *= x
y *= x
y *= x
y *= x
y *= x
y *= x
y *= x
y *= x
y *= x
z = 0
z += y
print(z)

# print 8675
z = 0

x = 1   
x += 1
x += 1
x += 1
x += 1
z += x

y = 10
x += 1
x += 1
y *= x
z += y


y = 10
x = y
y *= x
x = 1
x += 1
x += 1
x += 1
x += 1
x += 1
y *= x
z += y

y = 10
x = y
y *= x
y *= x
x = 1
x += 1
x += 1
x += 1
x += 1
x += 1
x += 1
x += 1
y *= x
z += y

print(z)
