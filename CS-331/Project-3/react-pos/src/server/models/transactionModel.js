
// Functions used by controllers to create transaction records for an order
const { query } = require('../db');

module.exports = {
  async addTransaction(order_id, { 
    card_number,
    card_expr_m,
    card_expr_y,
    card_holder
  }) {
    try {
      const { rows } = await query(
        `INSERT INTO p2_transactions (
          order_id,
          card_number,
          card_expr_m,
          card_expr_y,
          card_holder
        ) VALUES ($1, $2, $3, $4, $5)
        RETURNING *`,
        [
          order_id,
          card_number,
          card_expr_m,
          card_expr_y,
          card_holder
        ]
      );

      return rows[0];
    } catch (err) {
      console.error("Error adding transaction:", err);
      throw err;
    }
  }
};
