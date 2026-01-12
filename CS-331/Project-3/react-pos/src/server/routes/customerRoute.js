const express = require('express');
const router = express.Router();
const customer = require('../controllers/customerController');
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

// --- Trans ---
router.get('/translate', customer.translateText)

// --- GET ---
router.get('/menu', customer.getMenu);

router.get('/weather', customer.getWeather);

router.get('/customizations', customer.getCustomizations);

router.get('/coupon', customer.getCouponCodes);

router.post('/spin-wheel', customer.spinWheel);

// --- POST ---
router.post('/order', customer.createOrder);

module.exports = router;