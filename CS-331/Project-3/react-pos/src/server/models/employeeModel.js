
// Provides CRUD functions for employee records
const { query } = require('../db');

module.exports = {
  async getAll() {
    const { rows } = await query('SELECT * FROM p2_employees');
    return rows;
  },

  async add(data) {
    const { name, role, schedule } = data;
    const { rows } = await query(
      `INSERT INTO p2_employees (name, role, schedule)
       VALUES ($1, $2, $3)
       RETURNING *`,
      [name, role, schedule]
    );
    return rows[0];
  },

  async update(data) {
    const { id, name, role, schedule } = data;
    await query(
      `UPDATE p2_employees SET name=$1, role=$2, schedule=$3 WHERE id=$4`,
      [name, role, schedule, id]
    );
  },

  async delete(id) {
    await query('DELETE FROM p2_employees WHERE id=$1', [id]);
  },
};
