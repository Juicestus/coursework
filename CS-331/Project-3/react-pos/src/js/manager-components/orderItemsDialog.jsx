import React, { useEffect, useRef } from "react";
import "./managerStyles.css";

export default function OrderItemsDialog({ order, items, onClose }) {
  const dialogRef = useRef(null);
  const closeButtonRef = useRef(null);

  // Move focus into dialog when it opens
  useEffect(() => {
    if (order && dialogRef.current) {
      dialogRef.current.focus();
    }
  }, [order]);

  // Trap focus inside dialog
  const handleKeyDown = (e) => {
    if (e.key === "Escape") {
      onClose();
    }
    if (e.key === "Tab" && dialogRef.current) {
      const focusableElements = dialogRef.current.querySelectorAll(
        'button, [href], input, select, textarea, [tabindex]:not([tabindex="-1"])'
      );
      const first = focusableElements[0];
      const last = focusableElements[focusableElements.length - 1];

      if (e.shiftKey && document.activeElement === first) {
        e.preventDefault();
        last.focus();
      } else if (!e.shiftKey && document.activeElement === last) {
        e.preventDefault();
        first.focus();
      }
    }
  };

  // ✅ Hooks are always called, but rendering is conditional
  if (!order) return null;

  return (
    <div className="dialog-overlay">
      <div
        className="dialog-box"
        role="dialog"
        aria-modal="true"
        aria-labelledby="order-dialog-title"
        ref={dialogRef}
        tabIndex={-1}
        onKeyDown={handleKeyDown}
      >
        <h3 id="order-dialog-title">Order #{order.id} Details</h3>
        <p><strong>Employee:</strong> {order.employee_id}</p>
        <p><strong>Subtotal:</strong> ${order.subtotal}</p>
        <p><strong>Tax:</strong> ${order.tax}</p>
        <p><strong>Total:</strong> ${order.total}</p>
        <p><strong>Order Time:</strong> {new Date(order.order_time).toLocaleString()}</p>

        <h4>Items</h4>
        <ul>
          {items.map((item, idx) => (
            <li key={idx}>
              {item.drink_name} — {item.quantity} × ${item.total}
            </li>
          ))}
        </ul>

        <div style={{ marginTop: "1rem", textAlign: "right" }}>
          <button
            onClick={onClose}
            aria-label="Close order details dialog"
            ref={closeButtonRef}
          >
            Close
          </button>
        </div>
      </div>
    </div>
  );
}