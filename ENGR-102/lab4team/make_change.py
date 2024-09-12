# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Justus Languell
#               Alvaro Medina Fundora
# Section:      201
# Assignment:   Lab 4
# Date:         27 Aug 2024
#

import math

# Input
payed = float(input("How much did you pay? "))
cost = float(input("How much did it cost? "))
change = payed - cost
print(f"You received ${change:.2f} in change. That is...")

# Coin has properties
class Coin:
    def __init__(self, s, p, v):
        self.singular = s
        self.plural = p
        self.value = v
    def name(self, n):
        return self.singular if n == 1 else self.plural

# All the coins
coins = [
    Coin("quarter", "quarters", 25),
    Coin("dime", "dimes", 10),
    Coin("nickel", "nickels", 5),
    Coin("penny", "pennies", 1)
]

# Calculate
change = round(change * 100)
for coin in coins:
    if change < coin.value: continue
    n = change // coin.value
    change %= coin.value
    name = coin.name(n)
    print(f"{n} {name}")

