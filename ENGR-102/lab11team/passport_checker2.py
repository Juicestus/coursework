# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Justus Languell
# Section:      201
# Assignment:   Lab 11
# Date:         1 Nov 2024
#

# valid entry checks

def check_hcl(s):
    if s[0] != '#' or s.lower() != s: return False
    try:
        _ = int(s[1:], 16)
        return True
    except ValueError:
        return False

def check_pid(s):
    if len(s) != 9: return False
    return True
    #try:
    #    _ = int(s)
    #    return True
    #except ValueError:
    #    return False

def check_cid(s):
    if len(s.replace('0', ' ').lstrip().replace(' ', '0')) != 3: return False
    return True
    #try:
    #    _ = int(s)
    #    return True
    #except ValueError:
    #    return False


ok_eye_colors = set(["amb", "blu", "brn", "gry", "grn", "hzl", "oth"])

ek = {
    "byr": lambda s: len(s) == 4 and int(s) >= 1920 and int(s) <= 2008,
    "eyr": lambda s: len(s) == 4 and int(s) >= 2024 and int(s) <= 2034,
    "hgt": lambda s: (s[-2:] == 'cm' and int(s[:-2]) >= 150 and int(s[:-2]) <= 193) or (s[-2:] == 'im' and int(s[:-2]) >= 59 and int(s[:-2]) <= 76),
    "hcl": check_hcl,
    "ecl": lambda s: s in ok_eye_colors,
    "pid": check_pid,
    "cid": check_cid
    }

def is_valid(raw):
    hk = {}
    nkeys = 0
    for entry in raw.replace('\n', ' ').split(' '):
        key = entry.split(':')[0].strip()
        if key == "iyr": continue
        hk[key] = entry.split(':')[1]
        nkeys += 1
    if nkeys != len(hk): return False 

    for key, f in ek.items():
        if key not in hk or not f(hk[key]):
            return False
    return True

fn = input("Enter the name of the file: ")

valid = []
with open(fn, 'r') as f:
    for i, raw in enumerate(f.read().split('\n\n')):
        if is_valid(raw): 
            valid.append(raw)

with open('valid_passports2.txt', 'w') as f:
    for p in valid:
        f.write(p + '\n\n')

print(f"There are {len(valid)} valid passports")
