
// Functions to fetch orders by date, create orders, and generate aggregated reports
const { query } = require('../db');

module.exports = {
  async getOrdersBySingleDate(date) {
    const result = await query(
      `SELECT * FROM p2_orders 
       WHERE order_time::date = $1::date
       ORDER BY id`,
      [date]
    );
    return result.rows;
  },

  async getOrdersByDateRange(start, end) {
    const result = await query(
      `SELECT * FROM p2_orders 
       WHERE order_time::date BETWEEN $1::date AND $2::date
       ORDER BY id`,
      [start, end]
    );
    return result.rows;
  },
  
  async createOrder(order) {
    const { subtotal, tax, total, order_time, employee_id } = order;
    const { rows } = await query(
      `INSERT INTO p2_orders (subtotal, tax, total, order_time, employee_id)
       VALUES ($1, $2, $3, $4, $5)
       RETURNING id`,
      [subtotal, tax, total, order_time, employee_id]
    );
    return rows[0].id;
  },

  async getOrderReport(timeFormat, start, end) {
     const result = await query(`
      SELECT m.drink_name AS drink_name,
        TO_CHAR(o.order_time, '${timeFormat}') AS time_label,
        SUM(oi.quantity) AS total_qty,
        SUM(oi.total) AS total_sales
      FROM p2_order_items oi
      JOIN p2_orders o ON oi.order_id = o.id
      JOIN p2_menu m ON oi.menu_id = m.id
      WHERE o.order_time >= $1 AND o.order_time < $2
      GROUP BY drink_name, time_label
      ORDER BY time_label, drink_name`,
      [start, end]
    );
    return result.rows;
  },

  async getAggregatedOrders(dateFormat, range, dateStr) {
      const result = await query(`
    SELECT TO_CHAR(order_time, '${dateFormat}') AS label, SUM(total) AS total_sales
    FROM p2_orders
    WHERE DATE_TRUNC($1, order_time) = DATE_TRUNC($1, CAST($2 AS DATE))
    GROUP BY label
    ORDER BY MIN(order_time)
    `,
    [range, dateStr]
  );
    return result.rows;
  },

  async getZReport(date) {
    const result = await query(
      `SELECT * FROM p2_zreport WHERE report_date = $1`,
      [date]
    );
    return result.rows;
  },

  async insertZReport({
    report_date,
    total_sales,
    total_returns,
    total_voids,
    total_discards,
    total_cash,
    total_card,
    total_other
  }) {
    const result = await query(
      `
      INSERT INTO p2_zreport
        (report_date, total_sales, total_returns, total_voids, total_discards,
        total_cash, total_card, total_other, generated_at)
      VALUES ($1, $2, $3, $4, $5, $6, $7, $8, NOW())
      RETURNING *;
      `,
      [
        report_date,
        total_sales,
        total_returns,
        total_voids,
        total_discards,
        total_cash,
        total_card,
        total_other
      ]
    );

    return result.rows[0];
  }
  
  // ,

  // async addOrderItem(order_id, item) {
  //   const { menu_id, quantity, total } = item;
  //   await query(
  //     `INSERT INTO p2_order_items (order_id, menu_id, quantity, total)
  //      VALUES ($1, $2, $3, $4)`,
  //     [order_id, menu_id, quantity, total]
  //   );
  // }

}
