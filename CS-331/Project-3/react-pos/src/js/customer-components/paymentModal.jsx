import { useRef } from 'react';

export default function PaymentModal({ cartItems, clearCart, createOrder, subtotal, tax, total, setShowPaymentModal, setOrderInProgress, couponDiscount }) {
    const cardNumberRef = useRef(null);
    const cardExpMRef = useRef(null);
    const cardExpYRef = useRef(null);
    const cardHolderRef = useRef(null);

    async function submitOrder() {
        const cardNumber = cardNumberRef.current.value.trim();
        const cardExpM = Number(cardExpMRef.current.value.trim());
        const cardExpY = Number(cardExpYRef.current.value.trim());
        const cardHolder = cardHolderRef.current.value.trim();

        if (!cardNumber || !cardHolder || !cardExpM || !cardExpY) {
            alert("Please fill in all card details.");
            return;
        }

        const order_time = new Date().toISOString();
        
        // 1. Determine the Discount Factor
        // If a coupon is applied, the factor is (1 - discount percentage).
        // If no coupon is applied, couponDiscount will likely be 0, and the factor is 1.
        const discountFactor = 1 - (couponDiscount || 0);

        // 2. Aggregate line items by menuId
        const aggregatedItemsMap = cartItems.reduce((map, item) => {
            const menuId = item.id;
            
            // Calculate item's RAW (undiscounted) total (Qty * Base Price + Customization Cost)
            const itemCustomizationTotal = item.customization?.totalCustomizationPrice ?? 0;
            const itemTotalRaw = (item.price * item.qty) + itemCustomizationTotal; 
            
            // NOTE: We aggregate the raw total first, which is correct for merging line items.
            if (map.has(menuId)) {
                const existing = map.get(menuId);
                existing.quantities += item.qty;
                existing.totalsRaw += itemTotalRaw; // Using a new key to avoid confusion
            } else {
                map.set(menuId, {
                    menu_id: menuId,
                    quantities: item.qty,
                    totalsRaw: itemTotalRaw,
                });
            }
            return map;
        }, new Map()); 

        const menu_ids = [];
        const quantities = [];
        const totalsArr = [];

        // 3. Apply the Discount Factor to the aggregated RAW total
        aggregatedItemsMap.forEach(aggregatedItem => {
            menu_ids.push(aggregatedItem.menu_id);
            quantities.push(aggregatedItem.quantities);
            
            const discountedTotal = aggregatedItem.totalsRaw * discountFactor;
            
            // Push the final DISCOUNTED price, rounded to 2 decimal places
            totalsArr.push(Number(discountedTotal.toFixed(2))); 
        });

        // 4. Package orderData
        const orderData = {
            order_time,
            menu_ids, 
            quantities,
            totals: totalsArr,
            card_number: cardNumber,
            card_expr_m: cardExpM,
            card_expr_y: cardExpY,
            card_holder: cardHolder
        };

        setShowPaymentModal(false);

        try {
            await createOrder(orderData);
            alert("Order submitted!");
            clearCart();
            
            if (setOrderInProgress) {
                setOrderInProgress(false);
            }
        } catch (err) {
            alert("Error submitting order.");
            console.error(err);
            setShowPaymentModal(true); 
        }
    };

    return (
        <div id="orderModal" className="modal-overlay">
            <div className="modal-panel large">
                <h2>Payment Details</h2>

                <div className="modal-body">
                    {/* These totals (subtotal, tax, total) already reflect the discount */}
                    <div className="totals mb">
                        <div className="row"><span>Subtotal</span><strong id="paySubtotal">{subtotal}</strong></div>
                        <div className="row"><span>Tax</span><strong id="payTax">{tax}</strong></div>
                        <div className="row total"><span>Total</span><strong id="payTotal">{total}</strong></div>
                    </div>

                    <div className="card-field">
                        <label>Card Number</label>
                        <input id="cardNumber" className="card-input" placeholder="1234 5678 9012 3456" ref={cardNumberRef} />
                    </div>

                    <div className="card-field">
                        <label>Expiration (MM / YY)</label>
                        <div className="card-row">
                            <input id="cardExpM" className="card-input card-exp-small" placeholder="MM" ref={cardExpMRef} />
                            <input id="cardExpY" className="card-input card-exp-small" placeholder="YY" ref={cardExpYRef} />
                        </div>
                    </div>

                    <div className="card-field">
                        <label>Cardholder Name</label>
                        <input id="cardHolder" className="card-input" placeholder="Name on card" ref={cardHolderRef} />
                    </div>

                </div>

                <div className="modal-footer row gap">
                    <button id="orderCancel" className="btn gap-right" onClick={() => setShowPaymentModal(false)}>Back</button>
                    <button id="orderConfirm" className="btn primary" onClick={submitOrder}>Submit Order</button>
                </div>
            </div>
        </div>
    )
}