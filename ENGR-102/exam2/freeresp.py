# Load file teams.csv (look at the format)
# * Note that a team may or may not have a mascot
# 
# Analyze the data and print the following:
# - how many total teams
# - how many teams with touchdowns > 10
# - how many teams have no mascot
#
# Then:
# - create a text file "sad_no_mascot.txt"
# - write f"{team} is sad and has no mascot\n"


infile = open('teams.csv', 'r')
outfile = open('sad.txt', 'w')

i = 0
nteam = 0
n10d = 0
nsad = 0
for line in infile:
    if i == 0: 
        i += 1
        continue
        
    data = line.split(',')
    if int(data[2]) > 10:
        n10d += 1
    if data[3] == "":
        nsad += 1
        outfile.write(f'{data[0]} is sad\n')
        # remember write needs a newline^^^^
    nteam += 1
    
print('nteams = ', nteam)
print('n10d = ', n10d)
print('nsad = ', nsad)
    
infile.close()
outfile.close()
 
        
    
    


# given numbers and a formula, solve for something in the formula
import math

def fric(us, uk, W, theta): # could be strings or smtn
    try:
        us = float(us)
        uk = float(uk)
        W = float(W)
        theta = float(theta)
    except:
        print("..")
        return False

    N = W*math.cos(theta * (math.pi/180))
    return us * N, uk * N
