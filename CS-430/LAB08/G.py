t = int(input())
while t>0:
    m = {}
    n = int(input())
    while n>0:
        l = input()
        l = l.split()
        k = l[0]
        v = int(l[1])
        if k not in m.keys():
            m[k] = 0
        m[k] += v
        n-=1
    a = []
    for k, v in m.items():
        a.append((k, v))
    a = sorted(a, key=lambda x: (-x[1], x[0]))
    print(len(a))
    for k, v in a:
        print(k, v)

    t-=1


