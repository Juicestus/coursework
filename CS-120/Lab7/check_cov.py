s = """ACDLPEFLPFHLPFGLPFHLPILPCFHPJLPDMPJPJNOPEFPJLPJPEFNPFNOPINPJLP

""".replace('\n', '')

alf = "ABCDEFGHIJKLMNOP"

for a in alf:
    if a not in s:
        print('not covered: ', a)
    else:
        print('covered: ', a)
        
    