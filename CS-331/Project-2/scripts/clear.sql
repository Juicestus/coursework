/*=============================================================================

    Clear the database

=============================================================================*/

-- Delete all data from tables in reverse order of dependencies

-- Delete order items
DELETE FROM p2_order_items;

-- Delete transactions
DELETE FROM p2_transactions;

-- Delete orders
DELETE FROM p2_orders;

-- Delete menu-inventory relationships
DELETE FROM p2_menu_inventory;

-- Delete menu items
DELETE FROM p2_menu;

-- Delete inventory
DELETE FROM p2_inventory;

-- Delete employees
DELETE FROM p2_employees;

-- Optional: Reset sequences if you have any
-- ALTER SEQUENCE p2_employees_id_seq RESTART WITH 1;
-- ALTER SEQUENCE p2_inventory_id_seq RESTART WITH 1;
-- ALTER SEQUENCE p2_menu_id_seq RESTART WITH 1;
-- ALTER SEQUENCE p2_orders_id_seq RESTART WITH 1;