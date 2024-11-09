import numpy as np
import matplotlib.pyplot as plt

arr = []
cts = {}
with open("module12quizF24.txt", "r") as f:
    for l in f:
        a = int(l.strip())
        arr.append(a)
        if a not in cts.keys():
            cts[a] = 0
        cts[a] += 1

mode, q = 0, 0
for k, v in cts.items():
    if v > q:
        q = v
        mode = k

# [:,0] col
# [0,:] row

arr = np.array(arr).reshape(10, 10)
print("array is:")
print(arr)
print()

sum_row_7 = sum(arr[7-1,:])
print('sum(', arr[7-1,:], ') =', sum_row_7)
sum_col_5 = sum(arr[:,5-1])
print('sum(', arr[:,5-1], ') =', sum_col_5)
print("mode =", mode)

hidden = "IOUBWRMCLNLIOMAVPETGINERMHRNSFOSPAG"
key = sum_row_7 - sum_col_5 + mode

lines = ["" for i in range(key)]
for i, c in enumerate(hidden):
    lines[i % key] += c

print()
print("message1 is:")
print("".join(lines))

hidden = "RCYVHDOEIHGEAPBMTEISRRLS"
key = 8

lines = ["" for i in range(key)]
for i, c in enumerate(hidden):
    lines[i % key] += c

print()
print("message2 is:")
print("".join(lines))

from math import pi
