# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 8 
# Date:         22 Oct 2024
#

import math

# obungus obgunus 1
def parta(rs, rh):    
    return ((4 * math.pi) / 3) * ((rs ** 2 - rh ** 2) ** (3 / 2))

# obungus obgunus 2
def partb(n):
    if n % 2 == 1: 
        return False
    else:
        for start in range(2, n, 2):
            total = 0
            used = []
            for curr in range(start, n, 2):
                total += curr
                used.append(curr)
                if total == n:
                    return used
    return False



# obungus obgunus 3
def partc(char, name, company, email):
    big = len(name)
    if len(company) > len(name):
        big = len(company)
    if len(email) > len(company) and len(email) > len(name):
        big = len(email)
    field = big + 4
    return f'{char * (field + 2)}\n{char}{name:^{field}}{char}\n{char}{company:^{field}}{char}\n{char}{email:^{field}}{char}\n{char * (field + 2)}'

# obungus obgunus 4
def partd(l):
    l.sort()
    medv = 0
    if (len(l) % 2 == 1):
        medv = l[len(l) // 2]
    else:
        med1 = l[len(l) // 2]
        med2 = l[len(l) // 2 - 1]
        medv = (med1 + med2) / 2
    return l[0], medv, l[-1]

# obungus obgunus 5
def parte(times, dist):
    return [ (dist[i + 1] - dist[i]) / (times[i + 1] - times[i]) for i in range(len(times) - 1)]

# obungus obgunus 6
def partf(l):
    for i in l:
        d = 2028 - i
        if d in l:
            return d * i
    return False

# obungus obgunus 7
def partg(x, tol):
    val = 0
    n = 1
    while True:
        term = (2 / ((2 * n) - 1)) * (x ** ((2 * n) - 1))
        if abs(term) < tol:
            break
        val += term
        n += 1
    return val


# obungus obgunus 23
# obungus obgunus 245
# obungus obgunus 267643
# obungus obgunus 25674
# obungus obgunus 2452
# obungus obgunus 245
