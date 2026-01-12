const express = require('express');
const router = express.Router();
const manager = require('../controllers/managerController');
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

  return res.status(200)
});

// --- GET ---

router.get('/menu', manager.getMenu);
router.get('/employee', manager.getEmployees);
router.get('/inventory', manager.getInventory);
router.get('/menu_inventory', manager.getMenuInventory);
router.get('/orders', manager.getOrders);
router.get('/order_items', manager.getOrderItems);
router.get('/order_report', manager.getOrderReport);
router.get('/product_usage', manager.getProductUsage);
router.get('/x_report', manager.getXReport);
router.get('/z_report', manager.getZReport);

// --- POST ---

router.post('/menu/add', manager.addMenu);
router.post('/employee/add', manager.addEmployee);
router.post('/inventory/add', manager.addInventory);
router.post('/z_report/add', manager.addZReport);

// --- PUT ---

router.post('/menu/update', manager.updateMenu);
router.post('/employee/update', manager.updateEmployee);
router.post('/inventory/update', manager.updateInventory);

// --- DELETE ---

router.post('/menu/del', manager.deleteMenu);
router.post('/employee/del', manager.delEmployee);
router.post('/inventory/del', manager.delInventory);

module.exports = router;
