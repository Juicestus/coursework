used = set()
n = int(input())
holes = []
for i in range(n):
    for j, c in enumerate(input()):
        if c == '.':
            holes.append((i, j))
if len(holes) != (n*n)/4 or len(holes) == 0:
    print("invalid grille")

else:

    def rorate():
        for i in range(len(holes)):
            I, J = holes[i]
            #print('rot', (i, j), (j, (n-1)-i))
            holes[i] = (J, (n-1)-I)
    def sort():
        holes.sort(key=lambda x: (x[0], x[1]))
    enc = input()
    grid = [[" " for j in range(n)] for i in range(n)]

    #print('holes', holes)
    bad = False
    r = 0
    for i in range(len(enc)):
        k = enc[i]
        if r >= len(holes):
            rorate()
            sort()
            #print('holes', holes)
            r = 0
        I, J = holes[r]
        if (I, J) in used:
            bad = True
            break
        used.add((I, J))

        #print(k, I, J)
        grid[I][J] = k
        r+=1

    if (len(used) != n*n) or bad:
        print("invalid grille")
    else:
        for i in range(n):
            for j in range(n):
                print(grid[i][j], end="")
        print()


