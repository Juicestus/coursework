import { useEffect, useState, useRef } from "react";
import { fetchMenu, createOrder, getCouponCode } from "./customer-pages/menu.jsx";
import { API_BASE } from "./apibase.js";
import CustomizationModal from "./customer-components/customizationModal.jsx";
import MenuDisplay from "./employee-components/menuDisplay.jsx";
import Cart from "./customer-components/cart.jsx";
import ReviewModal from "./customer-components/reviewModal.jsx";
import OrderModal from "./customer-components/orderModal.jsx";
import PaymentModal from "./employee-components/paymentModal.jsx";
import CategoryButtons from "./customer-components/categoryButtons.jsx";

export const CUSTOMER_BASE_URL = `${API_BASE}/customer`;

export default function Customer() {

  const [ menuItems, setMenuItems ] = useState([]);
  const [ cartItems, setCartItems] = useState([]);
  const [ showCustomizationModal, setShowCustomizationModal ] = useState(false);
  const [ showReviewModal, setShowReviewModal ] = useState(false);
  const [ showPaymentModal, setShowPaymentModal ] = useState(false);
  const [ currentMenuItem, setCurrentMenuItem ] = useState(null);
  const [ customizationSubtotals, setCustomizationSubtotals ] = useState([]);
  const [ subtotal, setSubtotal ] = useState(0.00);
  const [ tax, setTax ] = useState(0.00);
  const [ total, setTotal ] = useState(0.00);

  const money = (n) => `$${Number(n).toFixed(2)}`;

  // Coupon state
  const [couponDiscount, setCouponDiscount] = useState(0); // like 0.15 = 15%
  const [couponApplied, setCouponApplied] = useState(false);

  // Category filter state
  const categoryOrder = ['Milk Tea', 'Fruit Tea', 'Smoothie', 'Slush', 'Specialty'];
  const [ selectedCategory, setSelectedCategory ] = useState('Milk Tea');

  // Persistent cart (critical fix)
  const cartRef = useRef(new Map());
  const cart = cartRef.current;

  // Fetch menu on mount
  useEffect(() => {
    async function loadMenuOnStart() {
      const data = await fetchMenu();
      setMenuItems(data);
    }
    loadMenuOnStart();
  }, []);


  // =========================
  // MAIN DOM EFFECT
  // =========================
  useEffect(() => {
    const TAX_RATE = 0.0825; 

    let sub = 0;

    cartItems.forEach(item => {
      const price = Number(item?.price) || 0;
      const qty = Number(item?.qty) || 1;
      sub += price * qty;
      sub += item.customization.totalCustomizationPrice;
    });

    let discountedSub = sub;
    if (couponApplied && couponDiscount > 0) {
        discountedSub = sub * (1 - couponDiscount);
    }

    const newSubtotal = money(discountedSub);
    const newTax = money(discountedSub * TAX_RATE);
    const newTotal = money(discountedSub + discountedSub * TAX_RATE);

    setSubtotal(newSubtotal);
    setTax(newTax);
    setTotal(newTotal);
  }, [cartItems, customizationSubtotals, couponApplied, couponDiscount]);

  function addItem(itemToAddID, customizations) {
   setCartItems(previousCartItems => {
      const baseItem = menuItems.find(item => item.id === itemToAddID);
      const newCustomizationString = JSON.stringify(customizations);
      const existingItemIndex = previousCartItems.findIndex(item => {
      if (item.id === itemToAddID) {
        const existingCustomizationString = JSON.stringify(item.customization);
        return existingCustomizationString === newCustomizationString;
      }
      return false;
      });

      if (existingItemIndex !== -1) {
        return previousCartItems.map((item, index) => {
          if (index === existingItemIndex) {
              return { ...item, qty: item.qty + 1 };
          }
          return item;
        });

      } 
      else {
        const newItem = { 
          cardID: Date.now().toString() + Math.random().toFixed(4), 
          ...baseItem, 
          qty: 1, 
          customization: customizations 
        };
        return [...previousCartItems, newItem];
      }
    });
  }

  function openReview() {
    // Prevent opening if cart is empty
    if (cartItems.length === 0) {
      alert("Your cart is empty!");
      return;
    }
    setShowReviewModal(true);
  }

  function increaseQty(itemCardID) {
    setCartItems(oldCartItems => {
      return oldCartItems.map(item => {
          if (item.cardID === itemCardID) { 
              return { ...item, qty: item.qty + 1 };
          }
          return item;
      })
    })
  }

  function decreaseQty(itemCardID) { // Now accepts the unique instance ID
    setCartItems(oldCartItems => {
      const newCartItems = oldCartItems.map(item => {
          if (item.cardID === itemCardID) { 
              return { ...item, qty: item.qty - 1 };
          }
          return item;
      })
      const filteredItems = newCartItems.filter(item => item.qty > 0);
      return filteredItems;
    })
  }

  function clearCart() {
    setCartItems([]);
  }

  async function applyCoupon(code) {
    if (couponApplied) {
      alert("A coupon is already applied.");
      return false;
    }

    try {
      const pct = await getCouponCode(code);
      if (pct && pct > 0) {
        setCouponDiscount(pct);
        setCouponApplied(true);
        alert(`Coupon applied! ${pct * 100}% off`);
        return true;
      } else {
        alert("Invalid coupon code.");
        return false;
      }
    } catch (err) {
      console.error(err);
      alert("Invalid coupon code.");
      return false;
    }
  };

 // =====================
  // JSX Render
  // =====================
  return (
    <>
      <main className="wrap grid-2">
        {/* <CategoryButtons setSelectedCategory={setSelectedCategory}/>  */}
        {/* <MenuDisplay menuItems={menuItems} money={money} setShowCustomizationModal={setShowCustomizationModal} setCurrentMenuItem={setCurrentMenuItem} selectedCategory={selectedCategory}/> */}
        <MenuDisplay
          menuItems={menuItems}
          money={money}
          setShowCustomizationModal={setShowCustomizationModal}
          setCurrentMenuItem={setCurrentMenuItem}
          selectedCategory={selectedCategory}
          setSelectedCategory={setSelectedCategory}
        />
        <Cart openReview={openReview} setCartItems={setCartItems} cartItems={cartItems} money={money} increaseQty={increaseQty} decreaseQty={decreaseQty} subtotal={subtotal} tax={tax} total={total} />
        {showCustomizationModal && 
          <CustomizationModal 
            menuItemID={currentMenuItem} 
            addItem={addItem}
            setShowCustomizationModal={setShowCustomizationModal}
            setCustomizationSubtotals={setCustomizationSubtotals}
          />}

        {showReviewModal && 
        <ReviewModal 
          cartItems={cartItems} 
          money={money} 
          setShowReviewModal={setShowReviewModal} 
          setShowPaymentModal={setShowPaymentModal}
          couponApplied={couponApplied}
          couponDiscount={couponDiscount}
          applyCoupon={applyCoupon} 
          subtotal={subtotal} 
          tax={tax} 
          total={total} 
          />}

        <OrderModal />

        {showPaymentModal && 
          <PaymentModal 
            cartItems={cartItems} 
            clearCart={clearCart} 
            createOrder={createOrder} 
            subtotal={subtotal} 
            tax={tax} 
            total={total} 
            setShowPaymentModal={setShowPaymentModal}
          />}
       
      </main>
    </>
  );
}