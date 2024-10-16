# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 8 team
# Date:         15 Oct 2024
#

# Convert time to 12 hour from 24
def conv12(time):
    parts = time.split(':')
    hour = int(parts[0])
    if hour > 12: 
        hour -= 12
        return str(hour) + ':' + parts[-1] + 'PM'
    if hour == 0:
        hour = 12
        return str(hour) + ':' + parts[-1] + 'AM'
    return time + 'AM'

# Get the time correctly based on 12/24 designation from input
def inputtime():
    time = input("Enter the time: ")
    if input("Choose the clock type (12 or 24): ") == '12':
        time = conv12(time)
    return time

# Get a valid character from input
def inputchar():
    validchars = set(list("abcdeghkmnopqrsuvwxyz@$&*="))
    char = input('Enter your preferred character: ')
    if char != "":
        while char not in validchars:
            char = input('Character not permitted! Try again: ')
    return char

# Generate the ascii text using the map
def generate(time, char, big):
    rows = ["", "", "", "", ""]
    for j, c in enumerate(time):
        for i, r, in enumerate(big[c].replace('.', c if char == "" else char).split('\n')):
            rows[i] += (' ' if j > 0 else '') + r
    return "\n".join(rows)

# Map of the chars
big = {
    '0': """...
. .
. .
. .
...""",
    '1': """ . 
.. 
 . 
 . 
...""",
    '2': """...
  .
...
.  
...""",
    '3': """...
  .
...
  .
...""",
    '4': """. .
. .
...
  .
  .""",
    '5': """...
.  
...
  .
...""",
    '6': """...
.  
...
. .
...""",
    '7': """...
  .
  .
  .
  .""",
    '8': """...
. .
...
. .
...""",
    '9': """...
. .
...
  .
...""",
    ':': """ 
:
 
:
 """,
    'A': ''' A 
A A
AAA
A A
A A''',
    'P': '''PPP
P P
PPP
P  
P  ''',
    'M': '''M   M
MM MM
M M M
M   M
M   M'''
}

# Main program
time = inputtime()
char = inputchar()
print()
output = generate(time, char, big)
print(output)

#poop
#poop
#poop
#poop
#poop
#poop
#poop
#poop
#poop
#poop
