const { Pool } = require('pg');
require('dotenv').config({path:'.env'});


const useSSL = String(process.env.PGSSL || '').toLowerCase();
const ssl =
    useSSL === 'true' || useSSL === 'require'
        ? { rejectUnauthorized: false }
        : false;

const pool = new Pool({
  user: process.env.PSQL_USER,
  host: process.env.PSQL_HOST,
  database: process.env.PSQL_DATABASE,
  password: process.env.PSQL_PASSWORD,
  //port: process.env.PSQL_PORT,
  //ssl: { rejectUnauthorized: false },
  port: process.env.PGPORT ? Number(process.env.PGPORT) : 5432, ssl
});

async function query(text, params) {
    return pool.query(text, params);
}

module.exports = { query };