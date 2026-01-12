
// Controller for public/customer-facing routes, providng endpoints to fetch the menu and submit customer orders.
const { query } = require('../db');
const menuModel = require('../models/menuModel');
const orderModel = require('../models/orderModel');
const orderItemModel = require('../models/orderItemModel');
const transactionModel = require('../models/transactionModel');
const weatherModel =  require('../models/weatherModel');
const { getCustomizations } = require('../models/customizationsModel');
const customizationsModel = require('../models/customizationsModel');
const couponModel = require('../models/couponModel');

require("dotenv").config({path:'../.env'});
const { TranslationServiceClient } = require("@google-cloud/translate").v3;

const client = new TranslationServiceClient({
  keyFilename: process.env.GOOGLE_APPLICATION_CREDENTIALS,
  projectId: process.env.GOOGLE_PROJECT_ID
});


const projectId = process.env.GOOGLE_PROJECT_ID;

module.exports = {

  async translate(text, target) {
    const request = {
      parent: `projects/${projectId}/locations/global`,
      contents: [text],
      mimeType: "text/plain",
      targetLanguageCode: target,
    };

    const [response] = await client.translateText(request);
    return response.translations[0].translatedText;
  },

  async translateText(req, res) {
    try {
      const { text, target } = req.query;

      if (!text || !target) {
        return res.status(400).json({ error: "Missing 'text' or 'target'" });
      }

      const translated = await module.exports.translate(text, target);
      res.json({ translated });

    } catch (err) {
      console.error("Error translating text:", err);
      res.status(500).json({ error: "Internal server error" });
    }
  },

  async getMenu(req, res) {
    try {
      res.json(await menuModel.getAll());
    } catch (err) {
      console.error('Error fetching menu:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async createOrder(req, res) {
    const {
      order_time,
      menu_ids,
      quantities,
      totals,
      customizations,
      card_number,
      card_expr_m,
      card_expr_y,
      card_holder,
    } = req.body;

    // Validate
    if (
      !order_time ||
      !Array.isArray(menu_ids) ||
      !Array.isArray(quantities) ||
      !Array.isArray(totals) ||
      !Array.isArray(customizations) ||
      !card_number ||
      !card_expr_m ||
      !card_expr_y ||
      !card_holder
    ) {
      return res.status(400).json({ error: 'Missing or invalid required fields' });
    }

    if (menu_ids.length !== quantities.length || menu_ids.length !== totals.length !== customizations.length) {
      return res.status(400).json({ error: 'menu_ids, quantities, totals, customizations must have same length' });
    }

    try {
      await query('BEGIN');

      const employee_id = 999; // customer order
      const subtotal = totals.reduce((acc, x) => acc + x, 0);
      const tax = subtotal * 0.0625;
      const total = subtotal + tax;

      const order_id = await orderModel.createOrder({
        subtotal,
        tax,
        total,
        order_time,
        employee_id,
      });

      for (let i = 0; i < menu_ids.length; i++) {
        await orderItemModel.addOrderItem(order_id, {
          menu_id: menu_ids[i],
          quantity: quantities[i],
          total: totals[i],
          customization: customizations[i],
        });
      }

      await transactionModel.addTransaction(order_id, {
        card_number,
        card_expr_m,
        card_expr_y,
        card_holder,
      });

      await query('COMMIT');
      res.status(201).json({ message: 'Order created', order_id, subtotal, tax, total });
    } catch (err) {
      await query('ROLLBACK');
      console.error('Error creating order:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

  async getWeather(req, res) {
    try {
      const { latitude, longitude } = req.query;

      const lat = Number(latitude);
      const lon = Number(longitude);

      if (isNaN(lat) || isNaN(lon)) {
        return res.status(400).json({ error: "Lat or Lon is not a number" });
      }

      if (lat < -90 || lat > 90) {
        return res.status(400).json({ error: "Lat not on earth" });
      }
      if (lon < -180 || lon > 180) {
        return res.status(400).json({ error: "Lon not on earth" });
      }

      return res.status(200).json( await weatherModel.getWeather(lat, lon));

    } catch (err) {
      console.error("Error fetching weather:", err);
      return res.status(500).json({ error: "Internal server error" });
    }
  },

  async getCustomizations(req, res) {
    try {
      const { menuItemID } = req.query;

      console.log("Controller menu ID: " + menuItemID);

      if (!menuItemID) {
        return res.status(400).json({ error: "Invalid menu ID"})
      }

      return res.json(await customizationsModel.getCustomizations(menuItemID));
    }
    catch (err) {
      console.error("Error fetching customizations:", err);
      return res.status(500).json({ error: "Internal server error" });
    }
  },

  async getCouponCodes(req, res) {
    try {
      const {code} = req.query;
      if (!code) {
        return res.status(400).json({ error: 'Missing coupon code' });
      }
      const data = await couponModel.getOne(code);
      res.json(data);
    } catch (err) {
      console.error('Error fetching menu_inventory:', err);
      res.status(500).json({ error: 'Internal server error' });
    }
  },

    async spinWheel(req, res) {
        try {
            // Use session to limit spins to once per day per browser session
            const today = new Date().toISOString().slice(0, 10); // "YYYY-MM-DD"

            if (!req.session) {
                return res.status(500).json({ ok: false, message: 'Session not available' });
            }

            if (req.session.lastWheelSpinDate === today) {
                return res.status(429).json({
                    ok: false,
                    message: 'You already spun the wheel today. Please come back tomorrow!',
                });
            }

            // Save spin timestamp on session
            req.session.lastWheelSpinDate = today;

            // Define possible rewards
            const rewards = [
                // $1 off
                {
                    type: 'amount',
                    code: 'BUBBLE1',
                    value: 1.0,
                    display: '$1 off your order!',
                },
                // 5% off
                {
                    type: 'percent',
                    code: 'BUBBLE5',
                    value: 0.05,
                    display: '5% off your order!',
                },
                // 10% off
                {
                    type: 'percent',
                    code: 'BUBBLE10',
                    value: 0.10,
                    display: '10% off your order!',
                },
                // 15% off
                {
                    type: 'percent',
                    code: 'BUBBLE15',
                    value: 0.15,
                    display: '15% off your order!',
                },
                // No discount for you
                {
                    type: 'none',
                    message: "Sip happens! No discount this time, but you're still tea-rrific 💛",
                },
            ];

            const prize = rewards[Math.floor(Math.random() * rewards.length)];

            return res.json({
                ok: true,
                ...prize,
            });
        } catch (err) {
            console.error('Error in spinWheel:', err);
            return res.status(500).json({ ok: false, message: 'Internal server error' });
        }
    },
};

