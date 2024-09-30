# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 7
# Date:         23 Sept 2024


def n2l4(n):
    return [(n//1000)%10, (n//100)%10, (n//10)%10, n%10]

def l2n4(l):
    return 1000*l[0] + 100*l[1] + 10*l[2] + l[3]

def kiter(n):
    ln = sorted(n2l4(n))
    return l2n4(ln[::-1]) - l2n4(ln)

k = 6174
inp = int(input("Enter a four-digit integer: "))

s = str(inp)
i = 0  # n iters
n = inp
while n != k and n != 0:
    n = kiter(n)
    s += f" > {n}"
    i += 1

print(s)
print(f"{inp} reaches {n} via Kaprekar's routine in {i} iterations")


