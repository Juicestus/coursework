import { useEffect, useState, useRef } from "react";
import { fetchMenu, createOrder, getCouponCode } from "./customer-pages/menu.jsx";
import { API_BASE } from "./apibase.js";

import CustomizationModal from "./customer-components/customizationModal.jsx";
import MenuDisplay from "./customer-components/menuDisplay.jsx";
import Cart from "./customer-components/cart.jsx";
import Weather from "./customer-components/weather.jsx";
import ReviewModal from "./customer-components/reviewModal.jsx";
import PaymentModal from "./customer-components/paymentModal.jsx";
import LanguageSelectorDropdown from "./customer-components/languageSelector.jsx";


export const CUSTOMER_BASE_URL = `${API_BASE}/customer`;

export default function Customer() {

  // PAGE STATE — controls which "screen" is visible
  const [page, setPage] = useState("menu");
  // menu | customization | review | payment

  // --------------------------
  //   NORMAL CUSTOMER STATE
  // --------------------------
  const [menuItems, setMenuItems] = useState([]);
  const [cartItems, setCartItems] = useState([]);
  const [currentMenuItem, setCurrentMenuItem] = useState(null);
  const [customizationSubtotals, setCustomizationSubtotals] = useState([]);
  const [selectedCategory, setSelectedCategory] = useState("Milk Tea");

  const [subtotal, setSubtotal] = useState("$0.00");
  const [tax, setTax] = useState("$0.00");
  const [total, setTotal] = useState("$0.00");

  const money = (n) => `$${Number(n).toFixed(2)}`;

  const [couponDiscount, setCouponDiscount] = useState(0); 
  const [couponApplied, setCouponApplied] = useState(false);
  const [flatDiscount, setFlatDiscount] = useState(0);
  const [wheelUsed, setWheelUsed] = useState(false);

  const TAX_RATE = 0.0825;

  // --------------------------
  //   FETCH MENU ON START
  // --------------------------
  useEffect(() => {
    async function load() {
      const data = await fetchMenu();
      setMenuItems(data);
    }
    load();
  }, []);

  // --------------------------
  //   UPDATE TOTALS
  // --------------------------
  useEffect(() => {
    let sub = 0;

    cartItems.forEach(item => {
      const price = Number(item.price) || 0;
      const qty = Number(item.qty) || 1;
      sub += price * qty;
      sub += item.customization.totalCustomizationPrice;
    });

    let discounted = sub;

    if (couponApplied && couponDiscount > 0) {
      discounted = discounted * (1 - couponDiscount);
    }

    if (wheelUsed && flatDiscount > 0) {
      discounted = Math.max(0, discounted - flatDiscount);
    }

    const taxVal = discounted * TAX_RATE;

    setSubtotal(money(discounted));
    setTax(money(taxVal));
    setTotal(money(discounted + taxVal));

  }, [cartItems, customizationSubtotals, couponApplied, couponDiscount, wheelUsed, flatDiscount]);

  // --------------------------
  //   CART OPERATIONS
  // --------------------------
  async function addItem(itemToAddID, customizations) {
    const baseItem = menuItems.find(it => it.id === itemToAddID);

    setCartItems(prev => {
      const newCustomizationStr = JSON.stringify(customizations);

      const matchIdx = prev.findIndex(it => {
        if (it.id === itemToAddID) {
          return JSON.stringify(it.customization) === newCustomizationStr;
        }
        return false;
      });

      if (matchIdx !== -1) {
        return prev.map((it, idx) =>
          idx === matchIdx ? { ...it, qty: it.qty + 1 } : it
        );
      }

      const newItem = {
        cardID: Date.now().toString() + Math.random().toFixed(4),
        ...baseItem,
        qty: 1,
        customization: customizations
      };

      return [...prev, newItem];
    });

    // After adding an item → return user to MENU PAGE
    setPage("menu");
  }

  function increaseQty(id) {
    setCartItems(prev =>
      prev.map(it => it.cardID === id ? { ...it, qty: it.qty + 1 } : it)
    );
  }

  function decreaseQty(id) {
    setCartItems(prev =>
      prev
        .map(it => it.cardID === id ? { ...it, qty: it.qty - 1 } : it)
        .filter(it => it.qty > 0)
    );
  }

  function clearCart() {
    setCartItems([]);
  }

  // --------------------------
  //   COUPON APPLY
  // --------------------------
  async function applyCoupon(code) {
    if (couponApplied) return alert("A coupon is already applied.");

    try {
      const pct = await getCouponCode(code);

      if (pct > 0) {
        setCouponDiscount(pct);
        setCouponApplied(true);
        alert(`Coupon applied! ${pct * 100}% off`);
        return true;
      }

      alert("Invalid coupon.");
      return false;
    } catch {
      alert("Invalid coupon.");
      return false;
    }
  }

  // --------------------------
  //   WHEEL
  // --------------------------
  async function spinWheel() {
    if (wheelUsed) return alert("Already spun this visit.");

    try {
      const r = await fetch(CUSTOMER_BASE_URL + "/spin-wheel", {
        method: "POST",
        credentials: "include"
      });
      const data = await r.json();

      if (!data || data.ok === false) {
        alert(data?.message ?? "Wheel unavailable.");
        return;
      }

      setWheelUsed(true);

      if (data.type === "percent") {
        setCouponDiscount(data.value);
        setCouponApplied(true);
        alert(`You won ${data.value * 100}% off!`);
      } else if (data.type === "amount") {
        setFlatDiscount(data.value);
        alert(`You won $${data.value.toFixed(2)} off!`);
      } else {
        alert(data?.message ?? "Sip happens!");
      }

    } catch {
      alert("Error spinning wheel.");
    }
  }

  // --------------------------
  //   PAGE RENDERING
  // --------------------------
  return (
    <>
      <LanguageSelectorDropdown />

    <header>
      <h1 className="globalhead">Customer Kiosk</h1>
    </header>

      {page === "menu" && (
        <main className="wrap grid-2">
        <MenuDisplay
          menuItems={menuItems}
          money={money}
          setCurrentMenuItem={setCurrentMenuItem}
          setShowCustomizationModal={() => setPage("customization")}
          selectedCategory={selectedCategory}
          setSelectedCategory={setSelectedCategory}
        />

          <div className="cart-stack">
            <Weather />
            <Cart 
              cartItems={cartItems}
              money={money}
              increaseQty={increaseQty}
              decreaseQty={decreaseQty}
              subtotal={subtotal}
              tax={tax}
              total={total}
              openReview={() => setPage("review")}
              clearCart={clearCart}
            />
          </div>
        </main>
      )}

      {page === "customization" && (
        <CustomizationModal
          menuItemID={currentMenuItem}
          addItem={addItem}
          setShowCustomizationModal={() => setPage("menu")}
          setCustomizationSubtotals={setCustomizationSubtotals}
        />
      )}

      {page === "review" && (
        <ReviewModal
          cartItems={cartItems}
          money={money}
          setShowReviewModal={() => setPage("menu")}
          setShowPaymentModal={() => setPage("payment")}
          couponApplied={couponApplied}
          couponDiscount={couponDiscount}
          applyCoupon={applyCoupon}
          spinWheel={spinWheel}
          wheelUsed={wheelUsed}
          subtotal={subtotal}
          tax={tax}
          total={total}
        />
      )}

      {page === "payment" && (
        <PaymentModal
          cartItems={cartItems}
          clearCart={clearCart}
          createOrder={createOrder}
          subtotal={subtotal}
          tax={tax}
          total={total}
          setShowPaymentModal={() => setPage("review")}
          setOrderInProgress={() => setPage("menu")}
          couponDiscount={couponDiscount}
        />
      )}
    </>
  );
}
