from bisect import bisect_left, bisect_right

n = (int(input()))
cards = [int(x) for x in input().split()]
cards = sorted(cards)
q = int(input())
for i in range(q):
    k = input().split()
    l = int(k[0])
    r = int(k[1])

    i = bisect_left(cards, l)
    j = bisect_right(cards, r)
    print(j-i)


