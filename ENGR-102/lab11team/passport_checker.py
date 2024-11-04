# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Justus Languell
# Section:      201
# Assignment:   Lab 11
# Date:         1 Nov 2024
#

ek = ["byr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"]

def is_valid(raw):
    hk = set()
    nkeys = 0
    for entry in raw.replace('\n', ' ').split(' '):
        key = entry.split(':')[0].strip()
        if key == "iyr": continue
        hk.add(key)
        #value = entry.split(':')[1]
        nkeys += 1
    if nkeys != len(hk): return False 

    for key in ek:
        if key not in hk:
            return False
    return True

fn = input("Enter the name of the file: ")

valid = []
with open(fn, 'r') as f:
    for i, raw in enumerate(f.read().split('\n\n')):
        if is_valid(raw): 
            valid.append(raw)

with open('valid_passports.txt', 'w') as f:
    for p in valid:
        f.write(p + '\n\n')

print(f"There are {len(valid)} valid passports")
