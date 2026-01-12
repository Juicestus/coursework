import { BrowserRouter, Route, Routes, Navigate } from "react-router-dom";
import Navbar from "./manager-components/navbar.jsx";
import MenuPage from "./manager-pages/menu.jsx";
import EmployeePage from "./manager-pages/employees.jsx";
import InventoryPage from "./manager-pages/inventory.jsx";
import OrdersPage from "./manager-pages/orders.jsx";
import SalesReportPage from "./manager-pages/sales-report.jsx";
import SalesTrendsPage from "./manager-pages/sales-trends.jsx";
import ProductUsagePage from "./manager-pages/product-usage.jsx";
import InventoryRestockPage from "./manager-pages/restock.jsx";
import XReportPage from "./manager-pages/xreport.jsx";
import ZReportPage from "./manager-pages/zreport.jsx";
import { API_BASE } from "./apibase.js";

export const MANAGER_BASE_URL = `${API_BASE}/manager`;

export default function Manager() {

  // Renders appropriate page when Navbar updates the URL
  return (
    <div>
      <BrowserRouter>
      <a href="#main-content" className="skip-link">Skip to main content</a>
        <Navbar />  
        <main id="main-content">    
         <Routes>
          <Route path="/" element={<Navigate to="/menu" replace />} />
          <Route path="/menu" element={<MenuPage />} />
          <Route path="/employees" element={<EmployeePage />} />
          <Route path="/inventory" element={<InventoryPage />} />
          <Route path="/orders" element={<OrdersPage />} />
          <Route path="/order-trends" element={<SalesTrendsPage />} />
          <Route path="/restock" element={<InventoryRestockPage />} />
          <Route path="/product-usage" element={<ProductUsagePage />} />
          <Route path="/sales-report" element={<SalesReportPage />} />
          <Route path="/x-report" element={<XReportPage />} />
          <Route path="/z-report" element={<ZReportPage />} />
        </Routes>
        </main> 
      </BrowserRouter>
    </div>
  );
}
