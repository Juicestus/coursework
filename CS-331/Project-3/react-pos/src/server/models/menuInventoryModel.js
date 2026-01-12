
// Maps menu items to inventory ingredients
const { query } = require('../db');

module.exports = {
  async getAll() {
    const { rows } = await query('SELECT * FROM p2_menu_inventory');
    return rows;
  },

  async getProductUsage(range, date) {
    let intervalLiteral = null;
    switch ((range || "").trim()) {
      case "day": intervalLiteral = "1 day"; break;
      case "week": intervalLiteral = "1 week"; break;
      case "month": intervalLiteral = "1 month"; break;
      case "year": intervalLiteral = "1 year"; break;
      default: intervalLiteral = null; break;
    }

    let result;
    if (!intervalLiteral) {
      result = await query(
        `SELECT SUM(oi.quantity) AS quantity_used,
                m.drink_name AS item_name,
                SUM(oi.quantity * m.price) AS estimated_cost
         FROM p2_orders o
         INNER JOIN p2_order_items oi ON o.id = oi.order_id
         INNER JOIN p2_menu m ON m.id = oi.menu_id
         WHERE DATE(o.order_time) = $1
         GROUP BY m.drink_name
         ORDER BY quantity_used DESC`,
        [date]
      );
    } else {
      result = await query(
        `SELECT SUM(oi.quantity) AS quantity_used,
                m.drink_name AS item_name,
                SUM(oi.quantity * m.price) AS estimated_cost
         FROM p2_orders o
         INNER JOIN p2_order_items oi ON o.id = oi.order_id
         INNER JOIN p2_menu m ON m.id = oi.menu_id
         WHERE o.order_time >= CAST($1 AS TIMESTAMP) - INTERVAL '${intervalLiteral}'
         GROUP BY m.drink_name
         ORDER BY quantity_used DESC`,
        [date]
      );
    }

    return result.rows;
  }
};

