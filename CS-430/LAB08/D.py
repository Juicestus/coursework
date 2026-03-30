n = int(input())

a = {}

par = [0] * 1000

def find(i):
    if par[i] == i:
        return i
    return find(par[i])

def unite(i, j):
    ir = find(i)
    jr = find(j)
    par[ir] = jr

r = {}

for i in range(n):
    l = [int(x) for x in input().split()]
    i+=1
    a[i] = l[1:]
    for j in a[i]:
        if j not in r:
            r[j] = []
        r[j].append(i)
'''
for R, NS in r.items():
    coms = itertools.combinations(NS, 2)
    for com in coms:
        a = com[0]
        b = com[1]
        if find(a) == find(b):
            continue
        else:
'''

for v, nbrs in a.items():
    for nbr in nbrs:
        if find(v) == find(nbr):
            continue
        else:
            unite(v, nbr)



