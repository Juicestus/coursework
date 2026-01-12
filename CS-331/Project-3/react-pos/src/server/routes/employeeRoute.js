const express = require('express');
const router = express.Router();
const employee = require('../controllers/employeeController');
const listEndpoints = require('express-list-endpoints');
const Table = require('cli-table3');


// List all endpoints
router.get('/', (req, res) => {
  
  if (req.accepts('html')) {  
      const endpoints = listEndpoints(router);

      const table = new Table({
        head: ['Method(s)', 'Path'],
        style: { head: [], border: [] }, // disables colors
      });

      endpoints.forEach(ep => {
        table.push([ep.methods.join(', '), ep.path]);
      });

      res.type('text/plain').send('Available API Routes:\n\n' + table.toString());

    }

  return res.status(200);
});


// --- GET ---
router.get('/menu', employee.getMenu);

// --- POST ---
router.post('/Order', employee.createOrder);

module.exports = router;