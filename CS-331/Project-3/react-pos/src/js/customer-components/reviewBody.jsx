export default function ReviewBody({ cartItems, money}) {

    function getCustomizationList(customization) {
        if (!customization) {
            return;
        }
        const customizationSummary = [];

        Object.entries(customization).forEach(([key, values]) => {
            if (key === 'totalCustomizationPrice') {
                return; 
            }
            if (values.adjustment) {
                const numNotZero = Number(values.price) > 0;
                customizationSummary.push(`${key}: ${values.adjustment} ${numNotZero ? ` - $${values.price}` : ''}`);
                customizationSummary.push('\n')
            }
        })

        return customizationSummary ;
    }
    return (
       <>
            {cartItems.map(item => (
                <tr key={item.id}>
                    <td><div className="customization-container">{item.drink_name}<div className="customization">{getCustomizationList(item.customization)}</div></div></td>
                    <td>{item.qty}</td>
                    <td>{money(item.price * item.qty + item.customization.totalCustomizationPrice)}</td>
                </tr>
            ))}
        </>
    )
}