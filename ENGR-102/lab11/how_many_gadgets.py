# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 4
# Date:         12 Sept 2024

# A function so that handling err input is easy
def main():
    d = float(input("Please enter a positive value for day: "))
    if d < 0:
        print("You entered an invalid number!")
        return 
     
    g = 0
    g += 10 * min(d, 10)
    g += min(max(d-10, 0), 50-10) * ((min(d, 50) + 11) / 2)
    g += min(max(d-50, 0), 100-50) * 50
    print(f"The sum total number of gadgets produced on day {round(d)} is {round(g)}")

main()


