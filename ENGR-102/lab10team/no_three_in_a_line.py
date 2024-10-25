# By submitting thI assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on thI assignment."
#
# Names:        Justus Languell
# Section:      201
# Assignment:   Lab 7
# Date:         22 Oct 2024
#

def no_three_in_line(n):
    I = {k: 0 for k in range(n)}
    J = {k: 0 for k in range(n)}
    pts = set()
    for i in range(n):
        for j in range(n):
            if I[i] >= 2: continue
            if J[j] >= 2: continue
            I[i] += 1 
            J[j] += 1 
            pts.add((i, j))
    if n % 2 == 1:
        pts.remove((n-2, n-2))
    pts.add((n-1, n-2))
    pts.add((n-2, n-1))
    return list(pts)

def print_board(n, p):
    for i in range(n):
        a = ""
        for j in range(n):
            if (i, j) in p:
                a += "O "
            else:
                a += ". "
        print(a)
            

for i in range(3, 8):
    print(f'- {i}')
    print_board(i, no_three_in_line(i))
