import React from "react";

export default function DatePicker({ label, value, onChange, disabled = false, id = "datepicker" }) {
  return (
    <div className="datepicker-container">
      {label && (
        <label className="datepicker-label" htmlFor={id}>
          {label}
        </label>
      )}
      <input
        id={id}
        type="date"
        value={value}
        onChange={(e) => onChange(e.target.value)}
        disabled={disabled}
      />
    </div>
  );
}
