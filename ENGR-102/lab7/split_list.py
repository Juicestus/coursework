# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 6
# Date:         23 Sept 2024

def main():
    # O(n), could prob make better tho
    a = [int(i) for i in input("Enter numbers: ").split()]
    ls = a[0]
    rs = 0
    for n in a[1:]: 
        rs += n
    for i in range(1, len(a)):
        if ls == rs:
            print(f"Left: {a[0:i]}")
            print(f"Right: {a[i:]}")
            print(f"Both sum to {ls}")
            return
        ls += a[i]
        rs -= a[i]
    print("Cannot split evenly")
    
main()


