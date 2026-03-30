n = int(input())

a = [0] * 1000000
for i in range(1, 75):
    for j in range(1, 75):
        k = i * i * i + j * j * j
        #if k == 91: print(i, j)
        a[k] += 1
while n > 0:
    if a[n] > 2:
        print(n)
        exit(0)
    n -= 1
print('none')
