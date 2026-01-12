import { useEffect, useState } from "react";
import { fetchMenu } from "./customer-pages/menu";

export default function Menu() {
    const [ menuItems, setMenuItems ] = useState([]);

    useEffect(() => {
        async function loadMenuOnStart() {
          const data = await fetchMenu();
          setMenuItems(data);
        }
        loadMenuOnStart();
      }, []);

    const groupByCategory = (items) => {
        // Use a Map or an object to hold the categorized data
        const grouped = new Map();
        items.forEach(item => {
            const category = item.category || 'Other'; // Handle items without a category
            if (!grouped.has(category)) {
                grouped.set(category, []);
            }
            grouped.get(category).push(item);
        });
        return grouped;
    };

    const categorizedMenu = groupByCategory(menuItems);
    
    // Define a rendering order for categories (optional but recommended)
    const categoryOrder = ['Milk Tea', 'Fruit Tea', 'Smoothie', 'Slush', 'Specialty'];
    
    // Create the final list of categories to iterate over
    const categoriesToRender = [
        ...categoryOrder.filter(cat => categorizedMenu.has(cat)),
        ...Array.from(categorizedMenu.keys()).filter(cat => !categoryOrder.includes(cat))
    ];

    return (
        <>
            <button className="btn" style={{marginTop: "20px", marginLeft: "20px"}}onClick={() => { window.location.pathname = '/'}}>Back</button>
            <img className="logo" src="images/placeholder.png" />
            <div className="menu-categories-container">
                {categoriesToRender.map(category => (
                    <div key={category} className="menu-section">
                        
                        {/* Category Heading */}
                        <h2 className="category-heading">{category}</h2>
                        
                        {/* Grid for items within this category */}
                        <div className="menu-grid">
                            {categorizedMenu.get(category).map(item => (
                                <div key={item.id} className="menu-item">
                                    {/* Removed image tag as per request, just displaying text data */}
                                    <div className="item-details">
                                        <div className="item-name">{item.drink_name}</div>
                                        <div className="item-price">{`$ ${item.price}`}</div>
                                    </div>
                                </div>
                            ))}
                        </div>
                    </div>
                ))}
            </div>
        </>
    );
}