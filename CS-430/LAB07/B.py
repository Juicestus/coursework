n = int(input())
arr = []
for _ in range(n):
    arr.append(float(input()))

multiples = []
buy = -1
i = 0
while i < n - 1:
    while i < n - 1 and arr[i] >= arr[i+1]:
        i += 1
        buy = arr[i]

    while i < n - 1 and arr[i] <= arr[i+1]:
        i += 1
        sell = arr[i]
if sell > buy:
    multiples.append((buy, sell / buy))

print(multiples)

currProduct = 100
for buy, multiple in multiples:
    shares = min(currProduct // buy, 100000)
    pur = shares * buy
    currProduct -= pur
    currProduct += pur * multiple 

print(int(currProduct))
