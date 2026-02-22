M = 10000000000000000000000000000
n, m = map(int, input().split())
f = input()
for i in range(n):
    c, a, b = map(str, input().split())
    if a in G:
        G[a].append(c)
    else:
        G[a] = [child]
    if b in G:
        G[b].append(c)
    else:
        G[b] = [child]
    B = {}
    Q = deque()
    Q.append((founder, M))
    while (len(Q) > 0):
        v = Q.popleft()
        if v[0] in B:
            B[v[0]] += v[1]
        else:
            B[v[0]] = v[1]

        if v[0] in G:
            for c in G[v[0]]:
                Q.append((c, v[1]/2))
h = input()
b = 0 if 


