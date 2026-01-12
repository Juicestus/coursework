
// Provides CRUD functions for inventory records
const { query } = require('../db');

module.exports = {
  async getAll() {
    const { rows } = await query('SELECT * FROM p2_inventory');
    return rows;
  },

  async add(data) {
    const { name, unit, quantity, reorder_threshold, unit_cost } = data;
    const { rows } = await query(
      `INSERT INTO p2_inventory (name, unit, quantity, reorder_threshold, unit_cost)
       VALUES ($1, $2, $3, $4, $5)
       RETURNING *`,
      [name, unit, quantity, reorder_threshold, unit_cost]
    );
    return rows[0];
  },

  async update(data) {
    const { id, name, unit, quantity, reorder_threshold, unit_cost } = data;
    await query(
      `UPDATE p2_inventory
       SET name=$1, unit=$2, quantity=$3, reorder_threshold=$4, unit_cost=$5
       WHERE id=$6`,
      [name, unit, quantity, reorder_threshold, unit_cost, id]
    );
  },

  async delete(id) {
    await query('DELETE FROM p2_inventory WHERE id=$1', [id]);
  },
};
