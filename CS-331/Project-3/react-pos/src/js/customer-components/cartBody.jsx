export default function CartBody({ cartItems, money, increaseQty, decreaseQty }) {
    if (!cartItems) { return <></>};

    function capitalize(str) {
        if (!str) return "";
        return str.charAt(0).toUpperCase() + str.slice(1).toLowerCase();
    }

    const defaults = {
        size: "Regular",
        sugar: "Regular",
        ice: "Regular",
        boba: "Regular",
        milk: "Whole" // future default
        // toppings: no default
    };


    function getCustomizationList(customization) {
        console.log(customization);
        if (!customization) {
            return;
        }
        const customizationSummary = [];

        Object.entries(customization).forEach(([key, values]) => {
            if (key === 'totalCustomizationPrice') {
                return; 
            }

            // Special case: Toppings
            if (key.toLowerCase() === "toppings") {
                // values here should be an array of {adjustment, price}
                if (Array.isArray(values) && values.length > 0) {
                    if (values.length === 1) {
                        const topping = values[0];
                        const numNotZero = Number(topping.price) > 0;
                        customizationSummary.push(
                            `${capitalize(key)}: ${topping.adjustment} ${
                            numNotZero ? ` - $${topping.price}` : ""
                            }`
                        );
                    } else {
                        customizationSummary.push(`${capitalize(key)}:`);
                        customizationSummary.push(
                            <ul key="toppings-list">
                            {values.map((topping, idx) => {
                                const numNotZero = Number(topping.price) > 0;
                                return (
                                <li key={idx}>
                                    {topping.adjustment} {numNotZero ? ` - $${topping.price}` : ""}
                                </li>
                                );
                            })}
                            </ul>
                        );
                    }
                }
            } else {
                // Normal single‑select groups
                if (values.adjustment) {
                    // Skip if this adjustment matches the default for this group
                    const defaultAdj = defaults[key.toLowerCase()];
                    if (defaultAdj && values.adjustment.toLowerCase() === defaultAdj.toLowerCase()) {
                        return; // don’t display default
                    }

                    const numNotZero = Number(values.price) > 0;
                    customizationSummary.push(
                        `${capitalize(key)}: ${values.adjustment} ${
                            numNotZero ? ` - $${values.price}` : ""
                        }`
                    );
                    customizationSummary.push('\n');
                }
            }
        });

        return customizationSummary ;
    }

    return (
        <>
        {cartItems.map(item => (
            <tr key={`${item.id}:${item.name}:${item.adjustment}`}>
                <td><div className="customization-container">{item.drink_name}<div className="customization">{getCustomizationList(item.customization)}</div></div></td>

                <td className="td-btn">
                    <button 
                        className="btn sm"
                        type="button" 
                        onClick={() => decreaseQty(item.cardID)}>-</button>
                </td>

                <td className="td-qty">
                    {item.qty}
                </td>

                <td className="td-btn">
                    <button 
                        className="btn sm"
                        type="button" 
                        onClick={() => increaseQty(item.cardID)}>+</button>
                </td>

                <td>{money(item.price * item.qty + Number(item.customization.totalCustomizationPrice))}</td>

                <td className={"td-custom"}><br />{}</td>
            </tr>
            ))
        }
        </>
    )
}