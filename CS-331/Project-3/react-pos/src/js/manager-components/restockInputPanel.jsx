import React, { useState, useEffect } from "react";

//Displays panel which allows user to select an item from inventory and add a selected amount of stock to cart
export default function RestockInputPanel({ inventoryData, onAddItem }) {
  const [selectedItem, setSelectedItem] = useState(null);
  const [amount, setAmount] = useState("");
  const [errorMessage, setErrorMessage] = useState("");

  function handleAdd() {
    setErrorMessage("");

    if (!selectedItem) {
      setErrorMessage("Please select an item.");
      return;
    }

    const parsedAmount = parseInt(amount);
    if (isNaN(parsedAmount) || parsedAmount <= 0) {
      setErrorMessage("Amount must be a positive number.");
      return;
    }

    onAddItem(selectedItem, parsedAmount);
    setAmount("");
    setSelectedItem(null);
  }

  return (
    <div style={{ border: "1px solid #ccc", borderRadius: "5px", padding: "1rem", width: "350px" }}>
      <h3>Add Item for Restock</h3>

      {/* Item Dropdown */}
      <div style={{ marginBottom: "1rem" }}>
        <label>Item: </label>
        <select
          value={selectedItem?.id || ""}
          onChange={(e) => {
            const item = inventoryData.find(i => i.id === parseInt(e.target.value));
            setSelectedItem(item || null);
          }}
        >
          <option value="">Select Item</option>
          {inventoryData.map(item => (
            <option key={item.id} value={item.id}>{item.name}</option>
          ))}
        </select>
      </div>

      {/* Amount Input */}
      <div style={{ marginBottom: "1rem" }}>
        <label>Amount: </label>
        <input
          type="number"
          value={amount}
          onChange={(e) => setAmount(e.target.value)}
          placeholder="Enter amount"
          style={{ width: "100px" }}
        />
        <span style={{ marginLeft: "0.5rem" }}>{selectedItem?.unit || ""}</span>
      </div>

      {/* Error Message */}
      {errorMessage && (
        <div style={{ color: "red", fontWeight: "bold", marginBottom: "1rem" }}>
          {errorMessage}
        </div>
      )}

      {/* Add Button */}
      <div style={{ textAlign: "right" }}>
        <button onClick={handleAdd}>Add to Order</button>
      </div>
    </div>
  );
}