
// Controller for manager-only routes, providing CRUD operations for menu items and inventory. Also provides employee and sales/order endpoints.
const menuModel = require('../models/menuModel');
const employeeModel = require('../models/employeeModel');
const inventoryModel = require('../models/inventoryModel');
const menuInventoryModel = require('../models/menuInventoryModel');
const orderModel = require('../models/orderModel');
const orderItemModel = require('../models/orderItemModel')

module.exports = {
  // --- Menu ---
  async getMenu(req, res) {
    try {
      res.json(await menuModel.getAll());
    } catch (err) {
      console.error('Error fetching menu:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async addMenu(req, res) {
    const required = ['drink_name', 'price', 'category', 'picture_url'];
    if (!required.every(k => req.body[k] != null)) return res.status(400).json({ error: 'Missing required fields' });
    try {
      res.json(await menuModel.add(req.body));
    } catch (err) {
      console.error('Error adding menu:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async updateMenu(req, res) {
    if (!req.body.id) return res.status(400).json({ error: 'Missing id' });
    try {
      await menuModel.update(req.body);
      res.json({ message: 'Menu item updated successfully' });
    } catch (err) {
      console.error('Error updating menu:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async deleteMenu(req, res) {
    if (!req.body.id) return res.status(400).json({ error: 'Missing id' });
    try {
      await menuModel.delete(req.body.id);
      res.json({ message: 'Menu item deleted successfully' });
    } catch (err) {
      console.error('Error deleting menu:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },
  // --- Employee ---
  async getEmployees(req, res) {
    try {
      const employees = await employeeModel.getAll();
      res.json(employees);
    } catch (err) {
      console.error('Error fetching employees:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async addEmployee(req, res) {
    const { name, role, schedule } = req.body;

    if (name == null || role == null || schedule == null) {
      return res.status(400).json({
        error: 'Missing required fields: name, role, schedule'
      });
    }

    try {
      const newEmployee = await employeeModel.add({ name, role, schedule });
      res.status(201).json(newEmployee);
    } catch (err) {
      console.error('Error adding employee:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async updateEmployee(req, res) {
    const { id, name, role, schedule } = req.body;

    if (!id) return res.status(400).json({ error: 'Missing id' });

    if (!name || role == null || schedule == null) {
      return res.status(400).json({
        error: 'Missing required fields: name, role, schedule'
      });
    }

    try {
      await employeeModel.update({ id, name, role, schedule });
      res.json({ message: 'Employee updated successfully' });
    } catch (err) {
      console.error('Error updating employee:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async delEmployee(req, res) {
    const { id } = req.body;

    if (!id) return res.status(400).json({ error: 'Missing id' });

    try {
      await employeeModel.delete(id);
      res.json({ message: 'Employee deleted successfully' });
    } catch (err) {
      console.error('Error deleting employee:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  // --- Order ---
   async getOrders(req, res) {
    const { date } = req.query;

    // Validate date param
    if (!date) {
      return res.status(400).json({ error: 'Missing required field: date' });
    }

    try {
      let orders;

      if (Array.isArray(date)) {
        // Must contain exactly 2 dates
        if (date.length !== 2) {
          return res.status(400).json({ error: 'Date range must contain exactly two dates' });
        }

        orders = await orderModel.getOrdersByDateRange(date[0], date[1]);
      } else {
        orders = await orderModel.getOrdersBySingleDate(date);
      }

      res.json(orders);
    } catch (err) {
      console.error('Error fetching orders:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async getOrderItems(req, res) {
    const { id } = req.query;

    if (!id) {
      return res.status(400).json({ error: "Missing required query parameter: id" });
    }

    try {
      const items = await orderItemModel.getOrderItemsByOrderId(id);
      res.json(items);
    } catch (err) {
      console.error("Error fetching order items:", err);
      res.status(500).json({ error: "Internal server error" });
    }
  },

  async getOrderReport(req, res) {
    const { interval, start, end } = req.query;

    let dateStart = Date.parse(start);
    let dateEnd = Date.parse(end);
    if ( isNaN(dateStart) || isNaN(dateEnd) ) {
      res.status(400).json({ error: 'start or end date are invalid dateStrings' });
    }
    if ( dateStart > dateEnd ) {
      res.status(400).json({ error: 'start date is greater than end date' });
    }

    let timeFormat;
   switch (interval.toLowerCase()) {
      case "hour": timeFormat = "YYYY-MM-DD HH24:00"; break;
      case "day": timeFormat = "YYYY-MM-DD"; break;
      case "week": timeFormat = "IYYY-IW"; break;
      case "month": timeFormat ="YYYY-MM"; break;
      default: timeFormat = "YYYY-MM-DD";
    }

    try {
      report = await orderModel.getOrderReport(timeFormat, start, end);

      res.json(report);
    } catch (err) {
      console.error('Error fetching sales report:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

 async getXReport(req, res) {
  try {
    const { range, dateStr, dateFormat } = req.query;

    if (!range || !dateStr || !dateFormat) {
      return res.status(400).json({ error: 'Missing required parameters: range, dateStr, or dateFormat' });
    }

    const result = await orderModel.getAggregatedOrders(dateFormat, range, dateStr);

    return res.json(result);
  } catch (error) {
    console.error('Error fetching X report:', error);
    return res.status(500).json({ error: 'Internal server error' });
  }
},

  async getZReport(req, res) {
    try {
      const { date } = req.query;
      if (!date) {
        return res.status(400).json({ error: 'Missing required parameter: date' });
      }

      const result = await orderModel.getZReport(date);
      return res.json(result);
    } catch (error) {
      console.error('Error fetching Z report:', error);
      return res.status(500).json({ error: 'Internal server error' });
    }
  },

  async addZReport(req, res) {
    try {
      const {
        report_date,
        total_sales,
        total_returns,
        total_voids,
        total_discards,
        total_cash,
        total_card,
        total_other
      } = req.body;

      if (!report_date) {
        return res.status(400).json({ error: "Missing required parameter: report_date" });
      }

      const result = await orderModel.insertZReport({
        report_date,
        total_sales,
        total_returns,
        total_voids,
        total_discards,
        total_cash,
        total_card,
        total_other
      });

      return res.json(result);
    } catch (error) {
      console.error("Error adding Z report:", error);
      return res.status(500).json({ error: "Internal server error" });
    }
  },

  // --- Inventory ---
  async getMenuInventory(req, res) {
    try {
      const data = await menuInventoryModel.getAll();
      res.json(data);
    } catch (err) {
      console.error('Error fetching menu_inventory:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async getInventory(req, res) {
    try {
      const items = await inventoryModel.getAll();
      res.json(items);
    } catch (err) {
      console.error('Error fetching inventory:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async addInventory(req, res) {
    const { name, unit, quantity, reorder_threshold, unit_cost } = req.body;

    // Validate fields
    if (name == null || unit == null || quantity == null || reorder_threshold == null || unit_cost == null){
      return res.status(400).json({
        error: 'Missing required fields: name, unit, quantity, reorder_threshold, unit_cost'
      });
    }

    try {
      const newItem = await inventoryModel.add({
        name,
        unit,
        quantity,
        reorder_threshold,
        unit_cost,
      });
      res.status(201).json(newItem);
    } catch (err) {
      console.error('Error adding inventory item:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async updateInventory(req, res) {
    const { id, name, unit, quantity, reorder_threshold, unit_cost } = req.body;

    // Validate required fields
    if (id == null) {
      return res.status(400).json({ error: 'Missing id' });
    }

    if (!name || !unit || quantity == null || reorder_threshold == null || unit_cost == null) {
      return res.status(400).json({
        error: 'Missing required fields: name, unit, quantity, reorder_threshold, unit_cost'
      });
    }

    try {
      await inventoryModel.update({
        id,
        name,
        unit,
        quantity,
        reorder_threshold,
        unit_cost,
      });
      res.json({ message: 'Inventory item updated successfully' });
    } catch (err) {
      console.error('Error updating inventory item:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async delInventory(req, res) {
    const { id } = req.body;

    if (!id) {
      return res.status(400).json({ error: 'Missing id' });
    }

    try {
      await inventoryModel.delete(id);
      res.json({ message: 'Inventory item deleted successfully' });
    } catch (err) {
      console.error('Error deleting inventory item:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async getProductUsage(req, res) {
    try {
      const { range, date } = req.query;
      const data = await menuInventoryModel.getProductUsage(range, date);
      res.json(data);
    } catch (err) {
      console.error('Error fetching product usage:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  }
};

