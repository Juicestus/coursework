# Implicit tuple
b = 3, 4, 5
print(b[0])

# Func modify list value
def f(x):
    x[2] = 2
    x[:] = [4, 5, 6]
    
a = [1, 2, 3]
f(a)
print(a)

# Tuple slice and add
t1 = (1, 2, 3)
t2 = (5, 6)
t3 = t1[:2] + t2
print(t3)

# Which of these creates:
# [[ 1, 2, 3]
#  [ 4, 5, 6]
#  [ 7, 8, 9]]
import numpy as np

# a = np.arange(1, 9).reshape(3, 3) #1..8
b = np.arange(9).reshape(3, 3) # 0..8
c = np.arange(1, 10).reshape(3, 3)
d = np.linspace(1, 9, 2)#.reshape(3, 3)

# print('(A) =', a)
print('(B) =', b)
print('(C) =', c)
print('(D) =', d)

