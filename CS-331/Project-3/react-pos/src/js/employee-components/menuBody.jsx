export default function MenuBody({ itemsByCategory, categoriesToRender, money, setShowCustomizationModal, setCurrentMenuItem }) {

    function openCustomization(menuItem) {
      setShowCustomizationModal(true);
      setCurrentMenuItem(menuItem);
    }
    
    return (
        <>
            {categoriesToRender.map(categoryName => (
                itemsByCategory.get(categoryName)?.length > 0 && (
                    <>
                        {/* <h3 className="menu-category-heading">{categoryName}</h3> */}
                        
                        {itemsByCategory.get(categoryName).map(item => (
                            <button 
                                key={item.id} // Use item.id as the key
                                className="card"
                                aria-label={`${item.drink_name} ${money(item.price)}`} 
                                type="button"
                                onClick={() => openCustomization(item.id)}>
                                <div className="card-body">
                                    <div className="card-name">{item.drink_name}</div>
                                    <div className="card-price">{money(item.price)}</div>
                                </div>
                            </button>
                        ))}
                    </>
                )
            ))}
        </>
    )
}