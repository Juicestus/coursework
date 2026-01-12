// src/main.jsx
import React from "react";
import { createRoot } from "react-dom/client";
import Home from "./home.jsx"
import ManagerDashboard from "./js/manager.jsx";
import "./styles.css";

const root = createRoot(document.getElementById("root"));
root.render(<Home />);