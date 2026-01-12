import { useEffect, useState } from "react";
import Table from "../manager-components/table";
import DatePicker from "../manager-components/datepicker.jsx";
import { MANAGER_BASE_URL } from "../manager.jsx";

export default function OrdersPage() {

  useEffect(() => {
    document.title = "Manager - Orders Page";
  }, []);

  const [ orderItems , setOrderItems ] = useState([]);
  const [ date , setDate] = useState("2024-10-25");
  const [loading, setLoading] = useState(false);


    const ORDER_HEADERS = [
      { display: "Order ID", key: "id" },
      { display: "Subtotal", key: "subtotal" },
      { display: "Tax", key: "tax" },
      { display: "Total", key: "total"},
      { display: "Order Time", key: "order_time"},
    ];

  // Fetches order data from backend when component is mounted and stores it for use inside the table
  useEffect(() => {
    async function getOrders() {
      setLoading(true);
      try {
        const response = await fetch(`${MANAGER_BASE_URL}/orders?date=${encodeURIComponent(date)}`, {credentials: 'include'});
        const data = await response.json()
        setOrderItems(data);                           
      } catch (err) {
        console.error("Error fetching orders:", err);
      } finally {
        setLoading(false);
      }
    }
    getOrders();
  }, [date]); 

  // Returns table containing stored order data
  return (
    <div style={{ padding: "1rem" }}>
      <h1>Orders by Date</h1>

      {/* Date Picker */}
      <DatePicker id="Order-datepicker" label="Select Date: " value={date} onChange={setDate} />

      {/* Optional Loading Indicator */}
      {loading && <p>Loading orders...</p>}

      {/* Orders Table */}
      <Table headers={ORDER_HEADERS} data={orderItems} />
    </div>
  );
}