



# in programming
# - value -> int, str, float, bool
#   COPY
# - reference -> list, dict, tuple
#   SAME ONE


a = [1, 2]

def f(x):
    x[0] = 6
    print(x)
    x = [2, 3] # assign
    print(x)
   
def m():
    a = [5]
    f(a)
    print(a)

m()