# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 6
# Date:         23 Sept 2024

X = input("What is your name? ")

v = ['a', 'e', 'i', 'o', 'u']

def y(X):
    if X[0].lower() in v:
        return X[0].lower() + X[1:]
    for i in range(1, len(X)):
        if X[i] in v:
            return X[i:]
    return "" # if this happens then something bad

Y = y(X)

print("""(X), (X), Bo-B(Y)
Banana-Fana Fo-F(Y)
Me Mi Mo-M(Y)
(X)!""".replace("(X)", X).replace("(Y)", Y))
