export default function OrderModal() {
    return (
         <div id="orderModal" className="modal-overlay hidden">
          <div className="modal-panel large">
            <h2>Payment Details</h2>

            <div className="modal-body">

              <div className="totals mb">
                <div className="row"><span>Subtotal</span><strong id="paySubtotal">$0.00</strong></div>
                <div className="row"><span>Tax</span><strong id="payTax">$0.00</strong></div>
                <div className="row total"><span>Total</span><strong id="payTotal">$0.00</strong></div>
              </div>

              <div className="card-field">
                <label>Card Number</label>
                <input id="cardNumber" className="card-input" placeholder="1234 5678 9012 3456" />
              </div>

              <div className="card-field">
                <label>Expiration (MM / YY)</label>
                <div className="card-row">
                  <input id="cardExpM" className="card-input card-exp-small" placeholder="MM" />
                  <input id="cardExpY" className="card-input card-exp-small" placeholder="YY" />
                </div>
              </div>

              <div className="card-field">
                <label>Cardholder Name</label>
                <input id="cardHolder" className="card-input" placeholder="Name on card" />
              </div>

            </div>

            <div className="modal-footer row gap">
              <button id="orderCancel" className="btn gap-right">Back</button>
              <button id="orderConfirm" className="btn primary">Submit Order</button>
            </div>
          </div>
        </div>
    )
}