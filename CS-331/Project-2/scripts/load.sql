/*=============================================================================

    Load the database

=============================================================================*/

-- Load employees
\copy p2_employees(id, name, role, schedule ) FROM 'data/p2_employees.csv' CSV HEADER;

-- Load inventory
\copy p2_inventory(id,name,unit,quantity,reorder_threshold,unit_cost) FROM 'data/p2_inventory.csv' CSV HEADER;

-- Load menu items
\copy p2_menu(id,drink_name,price,category,picture_url,tea_type,milk_type) FROM 'data/p2_menu.csv' CSV HEADER;

-- Load menu-inventory relationships
\copy p2_menu_inventory(menu_id, inventory_id, quantity) FROM 'data/p2_menu_inventory.csv' CSV HEADER;

-- Load orders (with explicit id)
\copy p2_orders(id, subtotal, tax, total, order_time, employee_id) FROM 'data/p2_orders.csv' CSV HEADER;

-- Load transactions
\copy p2_transactions(order_id, card_number, card_expr_m, card_expr_y, card_holder) FROM 'data/p2_transactions.csv' CSV HEADER;

-- Load order items
\copy p2_order_items(order_id, menu_id, quantity, total) FROM 'data/p2_order_items.csv' CSV HEADER;