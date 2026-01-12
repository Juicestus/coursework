
// Provides CRUD functions for the menu
const { query } = require('../db');

module.exports = {
  async getAll() {
    const { rows } = await query('SELECT * FROM p2_menu ORDER BY id');
    return rows;
  },

  async add(data) {
    const { drink_name, price, category, picture_url, tea_type = null, milk_type = null } = data;
    const { rows } = await query(
      `INSERT INTO p2_menu (drink_name, price, category, picture_url, tea_type, milk_type)
       VALUES ($1, $2, $3, $4, $5, $6)
       RETURNING *`,
      [drink_name, price, category, picture_url, tea_type, milk_type]
    );
    return rows[0];
  },

  async update(data) {
    const { id, drink_name, price, category, picture_url, tea_type = null, milk_type = null } = data;
    await query(
      `UPDATE p2_menu
       SET drink_name=$1, price=$2, category=$3, picture_url=$4, tea_type=$5, milk_type=$6
       WHERE id=$7`,
      [drink_name, price, category, picture_url, tea_type, milk_type, id]
    );
  },

  async delete(id) {
    await query('DELETE FROM p2_menu WHERE id=$1', [id]);
  },
};
