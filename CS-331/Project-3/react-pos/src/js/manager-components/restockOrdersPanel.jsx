import React, { useState, useEffect } from "react";
import Table from "../manager-components/table.jsx"

//Displays a panel which contains the quantity and price of selected items for restocking order
export default function RestockOrderPanel({ restockList, onPlaceOrder }) {
  const totalCost = restockList.reduce((sum, item) => sum + item.totalCost, 0).toFixed(2);

  const RESTOCK_HEADERS = [
    { display: "Item", key: "name" },
    { display: "Qty", key: "amount" },
    { display: "Unit", key: "unit" },
    {
      display: "Cost",
      key: "totalCost",
      render: (row) => `$${row.totalCost.toFixed(2)}`
    }
  ];

  return (
    <div style={{ border: "1px solid #ccc", borderRadius: "5px", padding: "1rem", flex: 1 }}>
      <h3>Restock Order Items</h3>
      <div style={{ padding: "2rem", width:"100%"}}>
        <Table headers={RESTOCK_HEADERS} data={restockList} />
      </div>
      

      <hr style={{ margin: "1rem 0" }} />

      <div style={{ display: "flex", justifyContent: "space-between", fontWeight: "bold", fontSize: "14pt" }}>
        <span>Order Total (Estimate):</span>
        <span>${totalCost}</span>
      </div>

      <div style={{ textAlign: "right", marginTop: "1rem" }}>
        <button
          style={{ backgroundColor: "#4CAF50", color: "white", padding: "0.5rem 1rem" }}
          onClick={onPlaceOrder}
        >
          Place Restock Order
        </button>
      </div>
    </div>
  );
}