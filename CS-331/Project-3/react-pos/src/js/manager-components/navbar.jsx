import React from "react";
import { useNavigate, useLocation } from "react-router-dom";
import { useState } from "react";
import "../../styles.css";

export default function Navbar() {
  const navigate = useNavigate();
  const location = useLocation();
  const [showChart, setShowChart] = useState(false);
  const [chartData, setChartData] = useState([]);
  const [tableHeaders, setTableHeaders] = useState([]);
  const [tableItems, setTableItems] = useState([]);

  // Define nav items with attributes
  const navItems = [
    { path: "/", label: "Back to Home", aria: "Back to Home", chart: false, special: "home" },
    { path: "/menu", label: "Menu", aria: "Go to Menu Editor page", chart: false },
    { path: "/employees", label: "Employees", aria: "Go to Employees Editor page", chart: false },
    { path: "/inventory", label: "Inventory", aria: "Go to Inventory Editor page", chart: false },
    // { path: "/orders", label: "Orders", aria: "Go to Orders page", chart: false },
    { path: "/order-trends", label: "Order Trends", aria: "View Order Trends page", chart: true },
    // { path: "/restock", label: "Restock", aria: "Go to Inventory Restock page", chart: false },
    { path: "/product-usage", label: "Product Usage", aria: "Go to Product Usage page", chart: true },
    { path: "/sales-report", label: "Sales Report", aria: "Go to Sales Report page", chart: true },
    // { path: "/x-report", label: "X-Report", aria: "Go to X Report page", chart: true },
    { path: "/z-report", label: "X & Z Report", aria: "Go to X and Z Report page", chart: true },
  ];

  return (
    <div className="page-container">
      <nav className="navbar" aria-label="Manager navigation bar">
        <ul className="nav-list">
          {navItems.map(item => (
            <li key={item.path}>
              <button
                className="nav-btn"
                onClick={() => {
                  if (item.special === "home") {
                    window.location.pathname = "/";
                  } else {
                    navigate(item.path);
                    setShowChart(item.chart);
                  }
                }}
                aria-label={item.aria}
                aria-current={location.pathname === item.path ? "page" : undefined}
              >
                {item.label}
              </button>
            </li>
          ))}
        </ul>
      </nav>
    </div>
  );
}