g = []
o = open('sample_filtered.csv', 'w')
with open('sample_cols.csv', 'r') as f:
    for i, l in enumerate(f):
        if i != 0:
            p = l.split(',')
            if any([e == "" for e in p]): continue
        o.write(l)
o.close()
        
