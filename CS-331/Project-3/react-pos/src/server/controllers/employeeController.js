
// Controller for cashier/employee routes, providing endpoints used by cashiers to access the menu and create orders
const { query } = require('../db');
const menuModel = require('../models/menuModel');
const orderModel = require('../models/orderModel');
const orderItemModel = require('../models/orderItemModel');
const transactionModel = require('../models/transactionModel');

module.exports = {
  async getMenu(req, res) {
    try {
      res.json(await menuModel.getAll());
    } catch (err) {
      console.error('Error fetching menu:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async createOrder(req, res) {
    const {
      order_time,
      employee_id,
      menu_ids,
      quantities,
      totals,
      customizations,
      card_number,
      card_expr_m,
      card_expr_y,
      card_holder,
    } = req.body;

    // Validate
    if (
      !order_time ||
      !employee_id ||
      !Array.isArray(menu_ids) ||
      !Array.isArray(quantities) ||
      !Array.isArray(totals) ||
      !Array.isArray(customizations) ||
      !card_number ||
      !card_expr_m ||
      !card_expr_y ||
      !card_holder
    ) {
      return res.status(400).json({ error: 'Missing or invalid required fields' });
    }

    if (menu_ids.length !== quantities.length || menu_ids.length !== totals.length !== customizations) {
      return res.status(400).json({ error: 'menu_ids, quantities, totals, customizations must have same length' });
    }

    try {
      await query('BEGIN');

      const subtotal = totals.reduce((acc, x) => acc + x, 0);
      const tax = subtotal * 0.0625;
      const total = subtotal + tax;

      const order_id = await orderModel.createOrder({
        subtotal,
        tax,
        total,
        order_time,
        employee_id,
      });

      for (let i = 0; i < menu_ids.length; i++) {
        await orderItemModel.addOrderItem(order_id, {
          menu_id: menu_ids[i],
          quantity: quantities[i],
          total: totals[i],
          customization: customizations[i],
        });
      }

      await transactionModel.addTransaction(order_id, {
        card_number,
        card_expr_m,
        card_expr_y,
        card_holder,
      });

      await query('COMMIT');
      res.status(201).json({ message: 'Order created', order_id, subtotal, tax, total });
    } catch (err) {
      await query('ROLLBACK');
      console.error('Error creating order:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },
};
