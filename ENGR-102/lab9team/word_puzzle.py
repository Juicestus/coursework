# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Justus Languell
# Section:      201
# Assignment:   Lab 7
# Date:         22 Oct 2024
#

def print_puzzle(puzzle):
    ''' Print puzzle as a long division problem. '''
    puzzle = puzzle.split(',')
    for i in range(len(puzzle)):
        if i == 1:
            print(f'{len(puzzle[i].split("|")[1]) * "_": >16}')
        print(f'{puzzle[i]: >16}')
        if i > 1 and i % 2 == 0:
            print(f"{'-'*len(puzzle[i]): >16}")

def get_valid_letters(puzzle):
    letters = puzzle.strip().replace(' ', '').replace(',', '').replace('|', '')
    # set makes O(n) instead of O(n^2), doesnt rly matter bc small string
    used = set()
    found = ""
    for letter in letters:
        if letter not in used:
            used.add(letter)
            found += letter
    return found

def is_valid_guess(vl, ul):
    return len(vl) == len(ul) and set(vl) == set(ul)

def check_user_guess(dividend, quotient, divisor, remainder):
    return dividend == quotient * divisor + remainder

def make_number(target, guess):
    n = 0
    for tc in target:
        for i, gc in enumerate(guess):
            if tc == gc:
                n += i
                n *= 10
                break
    return n // 10

def make_numbers(puzzle, guess):
    parts = puzzle.strip().replace(' ', '').replace('|', ',').split(',')
    return make_number(parts[2], guess), make_number(parts[0], guess), make_number(parts[1], guess), make_number(parts[-1], guess)

def main():
    puzzle = input("Enter a word arithmetic puzzle: ")
    print()
    print_puzzle(puzzle)
    print()
    guess = input("Enter your guess, for example ABCDEFGHIJ: ")
    if not is_valid_guess(get_valid_letters(puzzle), guess):
        print("Your guess should contain exactly 10 unique letters used in the puzzle.")
        return
    
    dividend, quotient, divisor, remainder = make_numbers(puzzle, guess)
    good = check_user_guess(dividend, quotient, divisor, remainder)
    
    if good:
        print("Good job!")
    else:
        print("Try again!")


#def test():
#    print("-- [TEST] get_valid_letters")
#    puzzle = "RUE,EAR | RUMORS,UEII  ,UKTR ,EAR ,KEOS,KAIK,USA"
#    l = get_valid_letters(puzzle)
#    print(l, l == "RUEAMOSIKT")
#
#    print("-- [TEST] is_valid_guess")
#    for s in ['TAKEOURSIM', 'IMAKETOURS', 'IMAKEIMAKE', 'TAKEOUR', 'TAKEOURSIMM', 'TAKEOURSBD']:
#        print(is_valid_guess("RUEAMOSIKT", s))
#
#    print("-- [TEST] make_number")
#    n = make_number("RUE", "TAKEOURSIM")
#    print(n, n == 653)
#
#    print("-- [TEST] make_numbers")
#    t = make_numbers(puzzle, "TAKEOURSIM")
#    print(t)

if __name__ == '__main__':
    main()
