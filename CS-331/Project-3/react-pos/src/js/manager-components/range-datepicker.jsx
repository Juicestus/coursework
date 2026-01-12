import React from "react";
import DatePicker from "./datepicker.jsx";
import "./managerStyles.css";

function RangeButton({ label, value, viewRange, setViewRange }) {
  const isActive = viewRange === value;
  return (
    <button
      onClick={() => setViewRange(value)}
      className={`range-btn ${isActive ? "active" : ""}`}
      aria-pressed={isActive}
    >
      {label}
    </button>
  );
}

export default function RangeDateToolbar({ selectedDate, setSelectedDate, viewRange, setViewRange }) {
  return (
    <div style={{ display: "flex", gap: ".5rem", marginBottom: "1rem", alignItems: "center" }}>
      <RangeButton label="Day" value="day" viewRange={viewRange} setViewRange={setViewRange} />
      <RangeButton label="Week" value="week" viewRange={viewRange} setViewRange={setViewRange} />
      <RangeButton label="Month" value="month" viewRange={viewRange} setViewRange={setViewRange} />
      <RangeButton label="Year" value="year" viewRange={viewRange} setViewRange={setViewRange} />
      <DatePicker
        id="range-datepicker"  
        value={selectedDate}
        onChange={setSelectedDate}
      />
    </div>
  );
}