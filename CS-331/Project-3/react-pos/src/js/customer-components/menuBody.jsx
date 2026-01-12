import React from "react"

export default function MenuBody({ itemsByCategory, categoriesToRender, money, setShowCustomizationModal, setCurrentMenuItem }) {

    function openCustomization(menuItem) {
      setShowCustomizationModal(true);
      setCurrentMenuItem(menuItem);
    }
    
    return (
        <>
            {categoriesToRender.map(categoryName => (
                itemsByCategory.get(categoryName)?.length > 0 && (
                    <React.Fragment key={categoryName}>
                        {/* <h3 className="menu-category-heading">{categoryName}</h3> */}
                        
                        {itemsByCategory.get(categoryName).map(item => (
                            <button 
                                key={item.id} // Use item.id as the key
                                className="card"
                                aria-label={`${item.drink_name} ${money(item.price)}`} 
                                type="button"
                                onClick={() => openCustomization(item.id)}
                            >
                                <img 
                                    className="card-img" 
                                    src={item.image_url || `/images/drink${item.id}.jpg`} 
                                    alt={item.drink_name} 
                                    onError={(e) => {
                                        e.target.onerror = null;
                                        e.target.src = '/images/placeholder.png';
                                    }}
                                />
                                <div className="card-body">
                                    <div className="card-name">{item.drink_name}</div>
                                    <div className="card-price">{money(item.price)}</div>
                                </div>
                            </button>
                        ))}
                    </React.Fragment>
                )
            ))}
        </>
    )
}