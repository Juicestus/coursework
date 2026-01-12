
// Used for inserting individual order items associated with an order
const { query } = require('../db');

module.exports = {
  async addOrderItem(order_id, item) {
    const { menu_id, quantity, total, customization } = item;
    await query(
      `INSERT INTO p2_order_items (order_id, menu_id, quantity, total, customization)
       VALUES ($1, $2, $3, $4, $5)`,
      [order_id, menu_id, quantity, total, customization]
    );
  },
  async getOrderItemsByOrderId(orderId) {
    const result = await query(
      `SELECT oi.menu_id, m.drink_name, oi.quantity, oi.total
      FROM p2_order_items oi
      JOIN p2_menu m ON oi.menu_id = m.id
      WHERE oi.order_id = $1`,
      [orderId]
    );
    return result.rows;
  }
};
