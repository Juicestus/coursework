import { useEffect, useState } from "react";
import Chart from "../manager-components/chart.jsx";
import Table from "../manager-components/table.jsx";
import DatePicker from "../manager-components/datepicker.jsx";
import { MANAGER_BASE_URL } from "../manager";

export default function XReportPage() {
  useEffect(() => {
    document.title = "Manager - X Report Page";
  }, []);

  const [reportDate, setReportDate] = useState("");
  const [chartData, setChartData] = useState([]);
  const [tableData, setTableData] = useState([]);

  const XREPORT_HEADERS = [
    { display: "Hour", key: "label" },
    { display: "Sales", key: "total_sales" },
    { display: "Returns", key: "returns" },
    { display: "Voids", key: "voids" },
    { display: "Discards", key: "discards" },
    { display: "Cash", key: "cash" },
    { display: "Card", key: "card" },
    { display: "Other", key: "other" }
  ];

  // Set default date to today on first load
  useEffect(() => {
    const today = new Date().toISOString().split("T")[0];
    setReportDate(today);
  }, []);

  // Fetch chart and table data when reportDate changes
  useEffect(() => {
    if (!reportDate) return;

    const url = `${MANAGER_BASE_URL}/x_report?range=day&dateStr=${encodeURIComponent(
      reportDate
    )}&dateFormat=HH12 AM`;

    fetch(url, { credentials: "include" })
      .then((res) => {
        if (!res.ok) throw new Error(`HTTP error ${res.status}`);
        return res.json();
      })
      .then((data) => {
        // Chart expects x/y pairs
        const series = data.map((record) => ({
          x: record.label,
          y: record.total_sales,
        }));
        setChartData(series);

        // // Table expects array of objects
        // setTableData(Array.isArray(data) ? data : []);
        // Table: normalize to include all fields
      const normalized = data.map((record) => ({
        label: record.label,
        total_sales: record.total_sales, // optional if you want a separate "Sales" column
        returns: 0,
        voids: 0,
        discards: 0,
        cash: 0,
        card: record.total_sales, // put all totals here
        other: 0,
      }));
      setTableData(normalized);
      })
      .catch((err) => {
        console.error("X Report fetch failed:", err);
        setChartData([]);
        setTableData([]);
      });
  }, [reportDate]);

  return (
    <div style={{ marginLeft: "20px"}}>
      <h1>X Report</h1>

      {/* Date Picker */}
      <div style={{ marginBottom: "1rem" }}>
        <DatePicker id="x-report-datepicker" label="Report Date: " value={reportDate} onChange={setReportDate} />
      </div>

      {/* Chart */}
      <Chart title="Sales per Hour" xaxis="x" yaxis="y" data={chartData} yRangePadding={1000} xLabel="Hour" yLabel="Revenue ($)"/>

      {/* Table */}
      <Table headers={XREPORT_HEADERS} data={tableData} caption="X Report Table"/>
    </div>
  );
}