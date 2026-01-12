import React, { useState, useEffect } from "react";
import DatePicker from "../manager-components/datepicker.jsx";
import Chart from "../manager-components/chart.jsx";
import Table from "../manager-components/table.jsx";
import VirtuosoTable from "../manager-components/tableVirtuoso.jsx";
import OrderItemsDialog from "../manager-components/orderItemsDialog.jsx";
import RangeDateToolBar from "../manager-components/range-datepicker.jsx";
import { MANAGER_BASE_URL } from "../manager.jsx";

export default function SalesTrendsPage() {
  useEffect(() => {
    document.title = "Manager - Order Trends Page";
  }, []);

  const [selectedDate, setSelectedDate] = useState("");
  const [viewRange, setViewRange] = useState("day");
  const [salesData, setSalesData] = useState([]);
  const [orderData, setOrderData] = useState([]);
  const [loading, setLoading] = useState(false);
  const [xLabel, setXLabel] = useState("Hour of Day");
  const [selectedOrder, setSelectedOrder] = useState(null);
  const [orderItems, setOrderItems] = useState([]);

  const SALES_TRENDS_HEADERS = [
    { display: xLabel, key: "label" },
    { display: "Total Sales", key: "total_sales" },
  ];
  const ORDER_HEADERS = [
    { display: "ID", key: "id" },
    { display: "Subtotal", key: "subtotal" },
    { display: "Tax", key: "tax" },
    { display: "Total", key: "total" },
    { display: "Order Time", key: "order_time" },
    { display: "Employee ID", key: "employee_id" },
  ];

  useEffect(() => {
    async function fetchData() {
      if (selectedDate && viewRange) {
        setLoading(true);
        try {
          await Promise.all([
            getSalesData(viewRange, selectedDate),
            getOrderData(viewRange, selectedDate),
          ]);
        } catch (err) {
          console.error("Error fetching data:", err);
        } finally {
          setLoading(false);
        }
      }
    }
    fetchData();
  }, [selectedDate, viewRange]);

  async function getSalesData(range, date) {
    try {
      let dateFormat;
      switch (range) {
        case "day":
          dateFormat = "HH24";
          setXLabel("Hour of Day");
          break;
        case "week":
          dateFormat = "Dy";
          setXLabel("Day of Week");
          break;
        case "month":
          dateFormat = "DD";
          setXLabel("Day of Month");
          break;
        case "year":
          dateFormat = "Mon";
          setXLabel("Month");
          break;
        default:
          dateFormat = "YYYY-MM-DD";
          setXLabel("Date");
      }
      const response = await fetch(
        `${MANAGER_BASE_URL}/x_report?range=${encodeURIComponent(range)}&dateStr=${encodeURIComponent(date)}&dateFormat=${encodeURIComponent(dateFormat)}`,
        { credentials: "include" }
      );
      const data = await response.json();
      setSalesData(data);
    } catch (err) {
      console.error("Error fetching sales data:", err);
    }
  }

  async function getOrderData(range, date) {
    try {
      const response = await fetch(
        `${MANAGER_BASE_URL}/orders?date=${encodeURIComponent(date)}`,
        { credentials: "include" }
      );
      const data = await response.json();
      setOrderData(data);
    } catch (err) {
      console.error("Error fetching order data:", err);
    }
  }

  async function getOrderItems(orderId) {
    try {
      const response = await fetch(
        `${MANAGER_BASE_URL}/order_items?id=${orderId}`,
        { credentials: "include" }
      );
      const data = await response.json();
      setOrderItems(data);
    } catch (err) {
      console.error("Error fetching order items:", err);
    }
  }

  return (
    <main role="main" style={{ marginLeft: "20px" }} aria-labelledby="order-trends-title">
      <h1 id="order-trends-title">Order Trends</h1>

      {/* Range and Date Selection */}
      <RangeDateToolBar
        selectedDate={selectedDate}
        setSelectedDate={setSelectedDate}
        viewRange={viewRange}
        setViewRange={setViewRange}
      />

      {/* Loading Indicator */}
      {loading && (
        <p role="status" aria-live="polite">
          Loading orders...
        </p>
      )}

      {/* Chart + Side Table */}
      <div
        style={{ display: "flex", gap: "2rem", alignItems: "flex-start" }}
        aria-labelledby="order-trends-chart-title"
      >
        <div style={{ flex: 1 }}>
          <h2 id="order-trends-chart-title" className="sr-only">
            Order Trends Chart
          </h2>
          <Chart
            chartTitle="Order Trends Over Time"
            xaxis="label"
            yaxis="total_sales"
            data={salesData}
            xLabel={xLabel}
            yLabel="Total Sales ($)"
            aria-label="Line chart showing order trends over time"
          />
        </div>
        <div style={{ flex: 1 }}>
          <VirtuosoTable
            headers={SALES_TRENDS_HEADERS}
            data={salesData}
            height={250}
            caption="Order Trends Data Points Table"
          />
        </div>
      </div>

      {/* Order History Table */}
      <h2 style={{ marginTop: "2rem" }} id="order-history-title">
        Order History
      </h2>
      <VirtuosoTable
        headers={ORDER_HEADERS}
        data={orderData}
        height={400}
        caption="Order History Table"
        aria-labelledby="order-history-title"
        onRowDoubleClick={(order) => {
          setSelectedOrder(order);
          getOrderItems(order.id);
        }}
      />

      {/* Dialog pop-up (for order items) */}
      <OrderItemsDialog
        order={selectedOrder}
        items={orderItems}
        onClose={() => setSelectedOrder(null)}
      />
    </main>
  );
}