
// Provides CRUD functions for employee records
const { query } = require('../db');

module.exports = {
  async getAll() {
    const { rows } = await query('SELECT * FROM p2_coupons');
    return rows;
  },
  async getOne(code) {
    const { rows } = await query('SELECT * FROM p2_coupons WHERE code=$1', [code]);
    return rows;
  },
};
