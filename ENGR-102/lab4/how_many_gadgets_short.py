# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 4
# Date:         12 Sept 2024

# Almost a one liner just for fun
d = float(input("Please enter a positive value for day: "))
print("You entered an invalid number!" if d < 0 else f"The sum total number of gadgets produced on day {round(d)} is {round(10 * min(d, 10) + min(max(d-10, 0), 50-10) * ((min(d, 50) + 11) / 2) + min(max(d-10, 0), 50-10) * ((min(d, 50) + 11) / 2))}")

