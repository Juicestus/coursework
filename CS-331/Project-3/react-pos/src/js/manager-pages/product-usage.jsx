import React, { useState, useEffect } from "react";
import DatePicker from "../manager-components/datepicker.jsx";
import Chart from "../manager-components/chart.jsx";
import BarGraph from "../manager-components/barGraph.jsx";
import Table from "../manager-components/table.jsx";
import VirtuosoTable from "../manager-components/tableVirtuoso.jsx";
import RangeDateToolbar from "../manager-components/range-datepicker.jsx";
import { MANAGER_BASE_URL } from "../manager";

export default function ProductUsagePage() {
  useEffect(() => {
    document.title = "Manager - Product Usage Page";
  }, []);

  const [selectedDate, setSelectedDate] = useState("");
  const [viewRange, setViewRange] = useState("day");
  const [usageData, setUsageData] = useState([]);
  const [detailedData, setDetailedData] = useState([]);
  const [yaxis, setYaxis] = useState("quantity_used");

  const USAGE_HEADERS = [
    { display: "Item", key: "item_name" },
    { display: "Quantity Used", key: "quantity_used" },
  ];
  const DETAIL_HEADERS = [
    { display: "Item", key: "item_name" },
    { display: "Quantity Used", key: "quantity_used" },
    { display: "Cost Estimate", key: "estimated_cost" },
  ];

  useEffect(() => {
    if (selectedDate && viewRange) {
      getUsageData(viewRange, selectedDate);
    }
  }, [selectedDate, viewRange]);

  async function getUsageData(range, date) {
    try {
      const response = await fetch(
        `${MANAGER_BASE_URL}/product_usage?range=${encodeURIComponent(range)}&date=${encodeURIComponent(date)}`,
        { credentials: "include" }
      );
      const data = await response.json();
      setUsageData(data);
    } catch (err) {
      console.error("Error fetching usage data:", err);
    }
  }

  const yLabel = yaxis === "quantity_used" ? "Quantity Used" : "Estimated Cost ($)";

  return (
    <main role="main" style={{ marginLeft: "20px" }} aria-labelledby="product-usage-title">
      <h1 id="product-usage-title">Inventory Usage Report</h1>

      {/* Toolbar */}
      <div style={{ display: "flex", gap: "2rem" }}>
        <RangeDateToolbar
          selectedDate={selectedDate}
          setSelectedDate={setSelectedDate}
          viewRange={viewRange}
          setViewRange={setViewRange}
        />
        <label htmlFor="yaxis-select" style={{ position: "absolute", left: "-9999px" }}>
          Select Y-axis metric
        </label>
        <select
          id="yaxis-select"
          value={yaxis}
          onChange={(e) => setYaxis(e.target.value)}
        >
          <option value="quantity_used">Quantity Used</option>
          <option value="estimated_cost">Estimated Cost</option>
        </select>
      </div>

      {/* Chart + Summary Table */}
      <div
        style={{ display: "flex", gap: "2rem", alignItems: "flex-start" }}
        aria-labelledby="product-usage-chart-title"
      >
        <div style={{ flex: 1 }}>
          <h2 id="product-usage-chart-title" className="sr-only">
            Product Usage Chart
          </h2>
          <BarGraph
            chartTitle="Product Usage Chart by Menu Item"
            xaxis="item_name"
            yaxis={yaxis}
            data={usageData}
            xLabel="Menu Item"
            yLabel={yLabel}
            width={1000}
            height={450}
            barColor="#82ca9d"
            aria-label="Bar chart showing product usage by menu item"
          />
        </div>
        {/* Optional summary table */}
        {/* <div style={{ flex: 1 }}>
          <VirtuosoTable
            headers={USAGE_HEADERS}
            data={usageData}
            height={250}
            caption="Product Usage Summary Table"
          />
        </div> */}
      </div>

      {/* Detail Table */}
      <h2 style={{ marginTop: "2rem" }} id="detailed-usage-title">
        Detailed Usage Records
      </h2>
      <VirtuosoTable
        headers={DETAIL_HEADERS}
        data={usageData}
        caption="Detailed Product Usage Table"
        aria-labelledby="detailed-usage-title"
      />
    </main>
  );
}