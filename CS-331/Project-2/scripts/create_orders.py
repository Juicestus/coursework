import random
import csv
import sys
from datetime import datetime, timedelta

# total number of orders to generate
TARGET_ORDERS = 1_000_000              

# starting point for order_time
START_DATE = datetime(2024, 1, 1)   

# number of days to spread across
DAYS = 365                          

# adjust to match rows in p2_employees
EMPLOYEE_COUNT = 5                  

id_to_price = {
    1:  4.50,  2:  4.75,  3:  4.95,  4:  5.25,  5:  5.10,
    6:  4.85,  7:  5.50,  8:  5.75,  9:  4.60, 10: 4.70,
    11: 4.95, 12: 4.90, 13: 5.00, 14: 5.15, 15: 5.20,
    16: 5.30, 17: 4.80, 18: 6.25, 19: 6.50, 20: 6.00
}

base_orders = TARGET_ORDERS // DAYS
extra_orders = TARGET_ORDERS % DAYS
orders_per_day = [base_orders] * DAYS

# distribute the "extra" orders randomly to keep uniform but not identical
for i in random.sample(range(DAYS), extra_orders):
    orders_per_day[i] += 1

order_id = 1
orders_generated = 0

with open("data/p2_transactions.csv", "w", newline="", encoding="utf-8") as ft, \
     open("data/p2_order_items.csv", "w", newline="", encoding="utf-8") as fo, \
     open("data/p2_orders.csv", "w", newline="", encoding="utf-8") as fO:

    trans_writer = csv.writer(ft)
    items_writer = csv.writer(fo)
    orders_writer = csv.writer(fO)

    # headers
    trans_writer.writerow(["order_id", "card_number", "card_expr_m", "card_expr_y", "card_holder"])
    items_writer.writerow(["order_id", "menu_id", "quantity", "total"])
    orders_writer.writerow(["id", "subtotal", "tax", "total", "order_time", "employee_id"])

    for day in range(DAYS):
        currentDaySales = orders_per_day[day]
        order_date = START_DATE + timedelta(days=day)

        for _ in range(currentDaySales):
            # --- Transaction ---
            card_number = "".join([str(random.randint(0, 9)) for _ in range(16)])
            card_expr_m = random.randint(1, 12)
            card_expr_y = random.randint(2025, 2030)
            card_holder = f"Customer_{order_id}"
            trans_writer.writerow([order_id, card_number, card_expr_m, card_expr_y, card_holder])

            # --- Order Items ---
            num_items = random.randint(1, 3)
            chosen_ids = random.sample(list(id_to_price.keys()), num_items)

            subtotal = 0
            for menu_id in chosen_ids:
                quantity = random.randint(1, 4)
                price = id_to_price[menu_id]
                item_total = round(price * quantity, 2)
                subtotal += item_total
                items_writer.writerow([order_id, menu_id, quantity, item_total])

            # --- Totals ---
            tax = round(subtotal * 0.0825, 2)
            total = round(subtotal + tax, 2)

            # --- Order time (random hours/min/sec within the day) ---
            order_time = order_date + timedelta(
                hours=random.randint(8, 21),   # shop open ~8AM–9PM
                minutes=random.randint(0, 59),
                seconds=random.randint(0, 59)
            )
            order_time_str = order_time.strftime("%Y-%m-%d %H:%M:%S")

            # --- Employee ID ---
            employee_id = random.randint(1, EMPLOYEE_COUNT)

            # Write order
            orders_writer.writerow([order_id, subtotal, tax, total, order_time_str, employee_id])

            order_id += 1
            orders_generated += 1

            # --- Progress print ---
            if orders_generated % max(1, (TARGET_ORDERS // 100)) == 0:  # update ~1% increments
                percent = (orders_generated / TARGET_ORDERS) * 100
                sys.stdout.write(f"\rProgress: {percent:5.1f}%")
                sys.stdout.flush()

print("\nCSV files generated: p2_transactions.csv, p2_order_items.csv, p2_orders.csv")

# TRUNCATE TABLE p2_order_items, p2_transactions, p2_orders RESTART IDENTITY CASCADE;