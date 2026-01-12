/*=============================================================================

    Queries     
    =======
    Special     1   Weekly Sales History
                2   Realistic Sales History
                3   Peak Sales Day
                4   Menu Item Inventory
                5   Best Of Worst
    Other       7   Restocking Recommendation
                14  Top 3 sellers per week

=============================================================================*/


/*=============================================================================

                                Special Queries                 

=============================================================================*/


/*=============================================================================
  1. Weekly Sales History
    -- Given a specific week, how many orders were placed? 
    -- Pseudocode: select count of orders grouped by week
    -- Note: p2_orders column order-time is a TIMESTAMP type: YYY-MM-DD HH:MM:SS
=============================================================================*/
SELECT EXTRACT(WEEK FROM order_time) AS sales_week, 
    COUNT(*) as order_count
FROM p2_orders
WHERE EXTRACT(WEEK FROM order_time) = 1
GROUP BY sales_week;

/*=============================================================================
  2. Realistic Sales History
    -- Given a specific hour of the day, how many orders were placed and what was
        the total sum of the orders?
    -- Pseudocode: select count of orders, sum of order total grouped by hour
=============================================================================*/
SELECT EXTRACT(HOUR FROM order_time) AS sales_hour, 
    COUNT(*) AS order_count,
    SUM(total) AS total_revenue
FROM p2_orders
GROUP BY sales_hour
ORDER BY sales_hour;


/*=============================================================================
  3. Peak Sales Day
    -- Given a specific day, what was the sum of the top 10 order totals?
    -- Pseudocode: select top 10 sums of order total grouped by day in descending 
        order by order total
=============================================================================*/
CREATE VIEW ranked_daily_orders AS
SELECT DATE(order_time) AS sales_day,
    total,
    RANK() OVER (
        PARTITION BY DATE(order_time) 
        ORDER BY total DESC
    ) AS rank
FROM p2_orders;

CREATE VIEW top_10_orders_per_day AS
SELECT sales_day, total
FROM ranked_daily_orders
WHERE rank <= 10;

SELECT sales_day,
    SUM(total) AS top_10_total
FROM top_10_orders_per_day
WHERE sales_day = '2024-01-01'
GROUP BY sales_day;
-- ORDER BY top_10_total DESC;

/*=============================================================================
  4. Menu Item Inventory
    -- Given a specific menu item, how many items from the inventory does that menu item use?
    -- Pseudocode:  select count of inventory items from inventory and menu grouped by menu item
=============================================================================*/
SELECT m.drink_name,
    COUNT(DISTINCT i.id) AS inventory_item_count
FROM (p2_menu m
INNER JOIN p2_menu_inventory mi ON m.id = mi.menu_id)
INNER JOIN p2_inventory i ON mi.inventory_id = i.id
-- WHERE m.drink_name = 'Classic Black Milk Tea with Boba'
GROUP BY m.drink_name;


/*=============================================================================
  5. Best of the Worst
    -- Given a specific week, what day had the lowest sales, what were the sales 
        numbers, and what was the top seller that day?
=============================================================================*/
-- 1. Daily item counts
CREATE VIEW daily_item_counts AS 
SELECT DATE(o.order_time) AS sales_day,
       oi.menu_id,
       COUNT(*) AS times_ordered
FROM p2_orders o
JOIN p2_order_items oi ON o.id = oi.order_id
GROUP BY DATE(o.order_time), oi.menu_id;

-- 2. Top seller per day
CREATE VIEW top_seller_per_day AS
SELECT d.sales_day,
       m.drink_name,
       d.times_ordered
FROM (
    SELECT sales_day,
           menu_id,
           times_ordered,
           RANK() OVER (
               PARTITION BY sales_day 
               ORDER BY times_ordered DESC
           ) AS rnk
    FROM daily_item_counts
) d
JOIN p2_menu m ON d.menu_id = m.id
WHERE d.rnk = 1;

-- 3. Daily sales (total revenue per day)
CREATE VIEW daily_sales AS
SELECT DATE(o.order_time) AS sales_day,
       EXTRACT(WEEK FROM o.order_time) AS sales_week,
       SUM(o.total) AS total_revenue
FROM p2_orders o
GROUP BY DATE(o.order_time), EXTRACT(WEEK FROM o.order_time);

-- 4. Worst day per week
CREATE VIEW worst_day_per_week AS 
SELECT sales_week, sales_day, total_revenue 
FROM (
    SELECT sales_week,
           sales_day,
           total_revenue,
           RANK() OVER (
               PARTITION BY sales_week
               ORDER BY total_revenue ASC
           ) AS rnk
    FROM daily_sales
) ranked
WHERE rnk = 1;

-- 5. Combine everything
SELECT w.sales_week,
       w.sales_day,
       w.total_revenue,
       t.drink_name AS top_seller,
       t.times_ordered
FROM worst_day_per_week w
JOIN top_seller_per_day t ON w.sales_day = t.sales_day
ORDER BY w.sales_week, w.sales_day;


/*=============================================================================

                                Regular Queries                 

=============================================================================*/


/*=============================================================================
  7. Restocking Recommendation
    -- Based on recent usage, how much of ecah inventory item should be reordered?
    -- Pseudocode: calculate average dauly usage for past N days, compare to current quantity
    -- Example: "Recommend ordering 50 units of black tea base to cover next 7 days"
=============================================================================*/
CREATE OR REPLACE VIEW menu_item_counts_7d AS
SELECT oi.menu_id AS menu_id,
    SUM(oi.quantity) AS item_count
FROM p2_orders o
JOIN p2_order_items oi ON o.id = oi.order_id
WHERE o.order_time >= DATE '2024-01-23' - INTERVAL '7 days'
GROUP BY oi.menu_id;

CREATE OR REPLACE VIEW inventory_usage_7d AS
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



/*=============================================================================
  14. Top 3 Sellers Per Week
    -- What are the top 3 most ordered menu items each week?
    -- Example: "Week 18: 1) Thai Tea, 2) Matcha Milk Tea, 3) Mango Slush"
=============================================================================*/

CREATE VIEW weekly_item_counts AS
SELECT
    EXTRACT(WEEK FROM o.order_time) AS week_number,
    m.drink_name,
    SUM(oi.quantity) AS total_quantity,
    RANK() OVER (
        PARTITION BY EXTRACT(WEEK FROM o.order_time)
        ORDER BY SUM(oi.quantity) DESC
    ) AS rank
FROM p2_orders o
JOIN p2_order_items oi ON o.id = oi.order_id
JOIN p2_menu m ON oi.menu_id = m.id
GROUP BY week_number, m.drink_name;

-- Now select only the top 3 per week
SELECT
    week_number,
    drink_name,
    total_quantity,
    rank
FROM weekly_item_counts
WHERE rank <= 3
ORDER BY week_number, rank;

-- Now select only the top 3 for a given week
SELECT
    week_number,
    drink_name,
    total_quantity,
    rank
FROM weekly_item_counts
WHERE rank <= 3 AND week_number = 18;



/*=============================================================================

                                Regular Queries (v1)

=============================================================================*/

/*
  6. Low Inventory Alert
    -- Which inventory items are below a restocking threshold?
    -- Pseudocode: select inventory items where quantity < threshold
    -- Example: "Tapioca pearls are below restocking level with only 3 units left"
*/
SELECT * FROM p2_inventory
WHERE quantity < restock_threshold;


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