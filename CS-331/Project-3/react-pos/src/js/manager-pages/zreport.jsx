import { useEffect, useState } from "react";
import Chart from "../manager-components/chart.jsx";
import Table from "../manager-components/table.jsx";
import DatePicker from "../manager-components/datepicker.jsx";
import { MANAGER_BASE_URL } from "../manager";

export default function ZReportPage() {
  useEffect(() => {
    document.title = "Manager - X and Z Report Page";
  }, []);

  const [reportDate, setReportDate] = useState("");
  const [chartData, setChartData] = useState([]);
  const [tableData, setTableData] = useState([]);
  const [zReportDone, setZReportDone] = useState(false);
  const [statusMessage, setStatusMessage] = useState("");

  const XREPORT_HEADERS = [
    { display: "Hour", key: "label" },
    { display: "Sales", key: "sales" },
    { display: "Returns", key: "returns" },
    { display: "Voids", key: "voids" },
    { display: "Discards", key: "discards" },
    { display: "Cash", key: "cash" },
    { display: "Card", key: "card" },
    { display: "Other", key: "other" }
  ];

  useEffect(() => {
    const today = new Date().toISOString().split("T")[0];
    setReportDate(today);
  }, []);

  useEffect(() => {
    if (!reportDate) return;

    fetch(`${MANAGER_BASE_URL}/z_report?date=${reportDate}`, { credentials: "include" })
      .then(res => res.json())
      .then(data => {
        setZReportDone(Array.isArray(data) && data.length > 0);
        loadXReportData(reportDate);
      })
      .catch(err => {
        console.error("Z-report check failed:", err);
        setZReportDone(false);
        loadXReportData(reportDate);
      });
  }, [reportDate]);

  function loadXReportData(date) {
    fetch(`${MANAGER_BASE_URL}/x_report?range=day&dateStr=${date}&dateFormat=HH12 AM`, { credentials: "include" })
      .then(res => res.json())
      .then(data => {
        const series = data.map(record => ({ x: record.label, y: record.total_sales }));
        setChartData(series);

        const normalized = data.map(record => ({
          label: record.label,
          sales: record.total_sales,
          returns: 0,
          voids: 0,
          discards: 0,
          cash: 0,
          card: record.total_sales,
          other: 0
        }));
        setTableData(normalized);
      })
      .catch(err => console.error("X-report fetch failed:", err));
  }

  function generateZReport() {
    const now = new Date();
    const todayStr = now.toISOString().split("T")[0];
    if (reportDate === todayStr && now.getHours() < 21) {
      if (!window.confirm("It’s before 9:00 PM. Generating a Z-Report may cause incomplete totals. Continue?")) {
        return;
      }
    }

    const totals = tableData.reduce(
      (acc, row) => {
        acc.total_sales += Number(row.sales) || 0;
        acc.total_returns += Number(row.returns) || 0;
        acc.total_voids += Number(row.voids) || 0;
        acc.total_discards += Number(row.discards) || 0;
        acc.total_cash += Number(row.cash) || 0;
        acc.total_card += Number(row.card) || 0;
        acc.total_other += Number(row.other) || 0;
        return acc;
      },
      {
        total_sales: 0,
        total_returns: 0,
        total_voids: 0,
        total_discards: 0,
        total_cash: 0,
        total_card: 0,
        total_other: 0
      }
    );

    fetch(`${MANAGER_BASE_URL}/z_report/add`, {
      method: "POST",
      credentials: "include",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ report_date: reportDate, ...totals })
    })
      .then(res => res.json())
      .then(() => {
        setZReportDone(true);
        setStatusMessage(`Z-Report generated for ${reportDate}`);
      })
      .catch(err => console.error("Z-report generation failed:", err));
  }

  return (
    <main role="main" style={{ marginLeft: "20px" }} aria-labelledby="xz-report-title">
      <h1 id="xz-report-title">X & Z Report</h1>

      <div style={{ marginBottom: "1rem" }}>
        <DatePicker
          id="X-and-z-report-datepicker"
          label="Report Date: "
          value={reportDate}
          onChange={setReportDate}
        />
      </div>

      {/* Chart */}
      <h2 id="x-report-chart-title" className="sr-only">X Report Chart</h2>
      <Chart
        chartTitle="Sales per Hour"
        xaxis="x"
        yaxis="y"
        data={chartData}
        yRangePadding={1000}
        xLabel="Hour"
        yLabel="Revenue ($)"
        aria-labelledby="x-report-chart-title"
        aria-label="Chart showing hourly sales revenue"
      />

      {/* Table */}
      <h2 id="x-report-table-title">X Report Data</h2>
      <Table
        headers={XREPORT_HEADERS}
        data={tableData}
        caption="X Report Table"
        aria-labelledby="x-report-table-title"
      />

      {/* Status message */}
      {statusMessage && (
        <p role="status" aria-live="polite" style={{ marginTop: "1rem", color: "green" }}>
          {statusMessage}
        </p>
      )}

      {/* Button */}
      <button
        onClick={generateZReport}
        disabled={zReportDone}
        aria-label={zReportDone ? "Z Report already finalized" : "Generate Z Report"}
      >
        {zReportDone ? "Z Report Finalized" : "Generate Z Report"}
      </button>
    </main>
  );
}