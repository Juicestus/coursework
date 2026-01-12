import { useRef } from "react";
import ReviewBody from "./reviewBody";

export default function ReviewModal(
    {   cartItems, 
        money, 
        setShowReviewModal, 
        setShowPaymentModal, 
        couponApplied, 
        couponDiscount,
        applyCoupon,
        spinWheel,
        wheelUsed,
        subtotal,
        tax,
        total 
     }) {

    
    const couponInputRef = useRef(null);
    
    function handleApplyCoupon() {
        const code = couponInputRef.current.value.trim();
        if (code) {
            applyCoupon(code);
        } else {
            alert("Please enter a coupon code.");
        }
    }

    function handleCheckout() {
        setShowReviewModal(false);
        setShowPaymentModal(true);
    }

    return (
        <div id="reviewModal" className="modal-overlay">
            <div className="modal-panel large">
                <h2>Review Your Order</h2>

                <div className="modal-body">
                    <div className="coupon-row row gap" style={{ marginBottom: "12px" }}>
                        <input 
                            id="couponInput" 
                            className="card-input" 
                            placeholder={couponApplied ? `Coupon Applied: ${couponDiscount * 100}% off` : "Enter coupon code…"}
                            ref={couponInputRef} 
                            disabled={couponApplied}
                        />
                        <button 
                            id="applyCouponBtn" 
                            className="btn" 
                            onClick={handleApplyCoupon}
                            disabled={couponApplied} 
                        >
                            {couponApplied ? "Applied" : "Apply"}
                        </button>
                        <button
                            type="button"
                            className="btn secondary"
                            onClick={spinWheel}
                            disabled={wheelUsed}
                        >
                            {wheelUsed ? "Wheel Used" : "Spin for Mystery Discount"}
                        </button>
                    </div>
                    
                    <table className="cart-table review-table">
                        <thead>
                            <tr>
                                <th>Item</th>
                                <th>Qty</th>
                                <th>Price</th>
                            </tr>
                        </thead>
                        <tbody><ReviewBody cartItems={cartItems} money={money}/></tbody>
                    </table>

                    <div id="reviewTotals" className="totals mb">
                        <div className="row"><span>Subtotal</span><strong id="revSubtotal">{subtotal}</strong></div>
                        {couponApplied && (
                             <div className="row discount">
                                <span>Discount ({couponDiscount * 100}%)</span>
                                <strong>Applied</strong> 
                            </div>
                        )}
                        <div className="row"><span>Tax</span><strong id="revTax">{tax}</strong></div>
                        <div className="row total"><span>Total</span><strong id="revTotal">{total}</strong></div>
                    </div>

                </div>

                <div className="modal-footer row gap">
                    <button id="reviewCancel" className="btn gap-right" onClick={() => setShowReviewModal(false)}>Cancel</button>
                    <button id="reviewConfirm" className="btn primary" onClick={handleCheckout}>Confirm</button>
                </div>
            </div>
        </div>
    );
}