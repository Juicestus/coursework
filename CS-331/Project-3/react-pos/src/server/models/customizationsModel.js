const { query } = require('../db');

module.exports = {
    async getCustomizations(menuItemID) {
        console.log("Query Menu ID: " + menuItemID);
        const { rows } = await query('SELECT name, adjustment, price FROM customizations WHERE menu_id = $1', [menuItemID]);
        return rows;
    }
};