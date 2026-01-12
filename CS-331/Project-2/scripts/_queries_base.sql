


-------- ADDITIONAL QUERIES --------

/*
  6. Low Inventory Alert
    -- Which inventory items are below a restocking threshold?
    -- Pseudocode: select inventory items where quantity < threshold
    -- Example: "Tapioca pearls are below restocking level with only 3 units left"
*/
SELECT * FROM p2_inventory
WHERE quantity < restock_threshold;


/*
  7. Restocking Recommendation
    -- Based on recent usage, how much of ecah inventory item should be reordered?
    -- Pseudocode: calculate average dauly usage for past N days, compare to current quantity
    -- Example: "Recommend ordering 50 units of black tea base to cover next 7 days"
*/
CREATE VIEW menu_item_counts_7d AS
SELECT oi.menu_id AS menu_id,
    SUM(oi.quantity) AS item_count
FROM p2_orders o
JOIN p2_order_items oi ON o.id = oi.order_id
WHERE o.order_time >= CURRENT_DATE - INTERVAL '7 days'
GROUP BY oi.menu_id;

CREATE VIEW inventory_usage_7d AS
SELECT mi.inventory_id,
    SUM(mi.quantity * mc.item_count) AS units_used
FROM menu_item_counts_7d mc
JOIN p2_menu_inventory mi ON mc.menu_id = mi.menu_id
GROUP BY mi.inventory_id;

SELECT i.id AS inventory_id,
    i.name,
    i.quantity AS current_qty,
    u.units_used AS projected_weekly_usage,
    (u.units_used - i.quantity) AS recommended_reorder
FROM p2_inventory i
JOIN inventory_usage_7d u ON i.id = u.inventory_id
WHERE u.units_used > i.quantity;


/*
  8. Inventory Usage by Menu Item
    -- How many units of each inventory item are used by a specific menu item?
    -- Pseudocode: join menu --> menu_inventory --> inventory, count usage per item
    -- Example: "Matcha Milk Tea uses 1 unit of matcha powder and 2 units of milk"
*/
SELECT m.drink_name AS menu_item,
       i.name AS inventory_item,
       mi.quantity AS units_used_per_order
FROM p2_menu_inventory mi
JOIN p2_menu m ON mi.menu_id = m.id
JOIN p2_inventory i ON mi.inventory_id = i.id
ORDER BY m.drink_name, i.name;

/*
  9. Menu Item Profitability
    -- What is the profit margin for each menu item based on ingredient cost and price?
    -- Pseudocode: sum ingredient cost from inventory, subtract from menu price
    -- Example: "Thai Tea has a profit margin of $2.45"
*/
SELECT m.drink_name,
    m.price,
    ROUND(SUM(mi.quantity * i.unit_cost), 2) AS ingredient_cost,
    ROUND(m.price - SUM(mi.quantity * i.unit_cost), 2) AS profit_margin
FROM p2_menu m
JOIN p2_menu_inventory mi ON m.id = mi.menu_id
JOIN p2_inventory i ON mi.inventory_id = i.id
GROUP BY m.id, m.drink_name, m.price
ORDER BY profit_margin DESC;



/*
  10. Menu Items Never Ordered
    -- Which menu items have never been ordered?
    -- Pseudocode: select menu items where id not in order_items
    -- Example: "Lychee Slush has never been ordered"
*/
SELECT m.id AS menu_id,
    m.drink_name
FROM p2_menu m
LEFT JOIN p2_order_items oi ON m.id = oi.menu_id
WHERE oi.menu_id IS NULL;


/*
  11. Inventory Items Never Used
    -- Which inventory items are not linked to any menu item?
    -- Pseudocode: select inventory items where id not in menu_inventory
    -- Example: "Taro powder is not used in any menu item"
*/
SELECT i.id AS inventory_id,
       i.name AS inventory_name
FROM p2_inventory i
LEFT JOIN p2_menu_inventory mi ON i.id = mi.inventory_id
WHERE mi.inventory_id IS NULL;


/*
  12. Order Volume by Day of Week
    -- Which day of the week consistently has the most orders?
    -- Pseudocode: count of orders grouped by weekday
    -- Example: "Saturday has the highest order volume with 9,876 orders"
*/
SELECT TO_CHAR(order_time, 'Day') AS weekday,
    COUNT(*) AS total_orders
FROM p2_orders
GROUP BY TO_CHAR(order_time, 'Day')
ORDER BY COUNT(*) DESC;


/*
  13. Hourly Revenue Trends by Weekday
    -- What are the average hourly sales for each weekday?
    -- Pseudocode: gruop by weekday and hour, avg of total
    -- Example: "Fridays at 3pm average $123 in sales"
*/
SELECT TRIM(TO_CHAR(order_time, 'Day')) AS weekday,
       EXTRACT(HOUR FROM order_time) AS hour,
       ROUND(AVG(total), 2) AS avg_hourly_revenue,
       COUNT(*) AS order_count
FROM p2_orders
GROUP BY weekday, hour
ORDER BY weekday, hour;


/*
  14. Top 3 Sellers Per Week
    -- What are the top 3 most ordered menu items each week?
    -- Pseudocode: count of menu_id grouped by week, rank by count, filter top 3
    -- Example: "Week 18: 1) Thai Tea, 2) Matcha Milk Tea, 3) Mango Slush"
*/
CREATE VIEW weekly_item_counts AS
SELECT EXTRACT(WEEK FROM o.order_time) AS week_number,
    m.drink_name,
    SUM(oi.quantity) AS total_quantity,
    RANK() OVER (
        PARTITION BY EXTRACT(WEEK FROM o.order_time)
        ORDER BY SUM(oi.quantity) DESC
    ) AS rank
FROM p2_ordres o,
JOIN p2_order_items oi ON o.id = oi.order_id
JOIN p2_menu m ON oi.menu_id = m.id
GROUP BY week_number, m.drink_name;

SELECT week_number,
    drink_name,
    total_quantity,
    rank
FROM weekly_item_counts
WHERE rank <= 3
ORDER BY rank;


/*
  15. Employee Performance Summary
    -- How many orders did each employee handle, and what was the total revenue?
    -- Pseudocode: group orders by employee_id, count, and sum
    -- Example: "Jordan handled 123 orders totaling $4,321 this month"
*/
SELECT e.id AS employee_id,
       e.name AS employee_name,
       COUNT(o.id) AS orders_handled,
       SUM(o.total), 2 AS total_revenue
FROM p2_employees e
JOIN p2_orders o ON e.id = o.employee_id
GROUP BY e.id, e.name
ORDER BY total_revenue DESC;