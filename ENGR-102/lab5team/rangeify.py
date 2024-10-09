def rangeify(d):
    n = {}
    for k, v in d.items():
        low, high = map(int, k.split('-'))
        for i in list(range(low, high+1)):
            n[i] = v
    return n