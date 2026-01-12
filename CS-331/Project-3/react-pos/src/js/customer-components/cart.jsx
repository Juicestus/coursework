import { useState } from "react";
import CartBody from "./cartBody";

export default function Cart({ openReview, cartItems, money, increaseQty, decreaseQty, subtotal, tax, total, clearCart }) {

    function handleCheckoutClick() {
        if ( cartItems.length === 0 ) {
            alert("Your cart is empty.")
        }
        else {
            openReview();
        }
    }

    return (
        <aside className="panel" aria-labelledby="cartHeading">
            <div id="cartHeadingBox">
                <h2 id="cartHeading">Your Cart</h2>
            </div>

            <div className="cart-table-wrap">
                <table className="cart-table">
                    <colgroup>
                        <col style={{ width: "52%" }} /> 
                        <col style={{ width: "8%" }} /> 
                        <col style={{ width: "8%" }} /> 
                        <col style={{ width: "8%" }} /> 
                        <col style={{ width: "24%" }} />
                    </colgroup>
                    <tbody id="cartItems"><CartBody cartItems={cartItems} money={money} increaseQty={increaseQty} decreaseQty={decreaseQty} /></tbody>
                </table>
            </div>

            <div className="totals">
                <div className="row gap-md"><span>Subtotal</span><strong data-no-translate id="subtotal">{`${subtotal}`}</strong></div>
                <div className="row gap-sm"><span>Tax</span><strong data-no-translate id="tax">{`${tax}`}</strong></div>
                <div className="row gap-sm total"><span>Total</span><strong data-no-translate id="total">{`${total}`}</strong></div>
            </div>

            <div className="row gap-lg">
                <button id="clearCart" className="btn" onClick={() => clearCart()}>Clear</button>
                <button id="checkout" className="btn primary" onClick={() => handleCheckoutClick()}>Checkout</button>
            </div>
        </aside>
    );
}