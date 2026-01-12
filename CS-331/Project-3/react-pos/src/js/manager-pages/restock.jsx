import React, { useState, useEffect } from "react";
import Table from "../manager-components/table.jsx";
import RestockInputPanel from "../manager-components/restockInputPanel.jsx"
import RestockOrderPanel from "../manager-components/restockOrdersPanel.jsx"
import { MANAGER_BASE_URL } from "../manager.jsx";

export default function InventoryRestockPage() {
    useEffect(() => {
        document.title = "Manager - Inventory Restock Page";
    }, []);
    
    const [inventoryData, setInventoryData] = useState([]);
    const [restockList, setRestockList] = useState([]);
    const [selectedItem, setSelectedItem] = useState(null);
    const [amount, setAmount] = useState("");
    const [errorMessage, setErrorMessage] = useState("");
    const [totalCost, setTotalCost] = useState(0);

    const INVENTORY_HEADERS = [
        { display: "Name", key: "name" },
        { display: "Unit", key: "unit" },
        { display: "Quantity", key: "quantity" },
        { display: "Reorder Threshold", key: "reorder_threshold" },
        {
        display: "Status",
        key: "status",
        render: (row) => {
            const quantity = parseFloat(row.quantity);
            const threshold = parseFloat(row.reorder_threshold);
            return quantity < threshold ? "❌ Low Stock" : "✅ Sufficient";
        }

            
        },
    ];

    useEffect(() => {
        fetchInventoryData();
    }, []);

    async function fetchInventoryData() {
        try {
        const response = await fetch(`${MANAGER_BASE_URL}/inventory`, {credentials: 'include'});
        const data = await response.json();
        setInventoryData(data);
        } catch (err) {
        console.error("Error loading inventory:", err);
        }
    }

    useEffect(() => {
        const total = restockList.reduce((sum, r) => sum + r.totalCost, 0);
        setTotalCost(total);
    }, [restockList]);

    // Function to add the item to the order list when "Add to Order" is pushed
    function handleAddItem(item, addedAmount) {
        const unitCost = parseFloat(item.unit_cost);
        const addedCost = addedAmount * unitCost;

        const existing = restockList.find(r => r.id === item.id);

        if (existing) {
            const updated = restockList.map(r =>
            r.id === item.id
                ? {
                    ...r,
                    amount: r.amount + addedAmount,
                    totalCost: r.totalCost + addedCost,
                }
                : r
            );
            setRestockList(updated);
        } else {
            setRestockList([
            ...restockList,
            {
                id: item.id,
                name: item.name,
                unit: item.unit,
                amount: addedAmount,
                totalCost: addedCost,
            },
            ]);
        }
    }

    // Function to place the order and update inventory items
    function handlePlaceOrder() {
        if (restockList.length === 0) {
            alert("Restock order is empty.");
            return;
        }

        const confirmed = window.confirm(`Confirm restock order for total cost: $${totalCost.toFixed(2)}?`);
        if (!confirmed) return;

        const updatedItems = restockList.map(r => {
            const original = inventoryData.find(i => i.id === r.id);
            return {
            ...original,
            quantity: original.quantity + r.amount,
            };
        });

        Promise.all(updatedItems.map(item =>
            fetch(`${MANAGER_BASE_URL}/inventory/update`, {
                method: "PUT",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({
                id: item.id,
                name: item.name,
                unit: item.unit,
                quantity: item.quantity,
                reorder_threshold: item.reorder_threshold,
                unit_cost: item.unit_cost
            })})
            )).then(() => {
                alert("Restock order placed successfully.");
                setRestockList([]);
                fetchInventoryData();
            }).catch(err => {
                console.error("Error placing order:", err);
                alert("Failed to place restock order.");
        });
    }

    return (
        <div style={{ marginLeft: "20px"}}>
            <h1>Current Inventory Levels</h1>
            <Table headers={INVENTORY_HEADERS} data={inventoryData} />

            {/* Restock Input + Order Summary*/}
            <h2>Create Restock Order</h2>
            <div style={{ display: "flex", gap: "2rem", marginTop: "2rem" }}>
                <RestockInputPanel inventoryData={inventoryData} onAddItem={handleAddItem} />
                <RestockOrderPanel restockList={restockList} onPlaceOrder={handlePlaceOrder} />
            </div>
        </div>
    );
}