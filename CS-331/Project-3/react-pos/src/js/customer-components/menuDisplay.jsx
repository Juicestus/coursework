import { useState, useEffect, useMemo } from "react";
import MenuBody from "./menuBody";
import CategoryButtons from "../customer-components/categoryButtons.jsx";
import { translateBatch } from "../customer-pages/menu.jsx";

export default function MenuDisplay({
    menuItems,
    money,
    setShowCustomizationModal,
    setCurrentMenuItem,
    selectedCategory,
    setSelectedCategory
}) {

    const [filteredMenuItems, setFilteredMenuItems] = useState([...menuItems]);
    const [translatedMenuItems, setTranslatedMenuItems] = useState([]);

    const categoryOrder = ['Milk Tea', 'Fruit Tea', 'Smoothie', 'Slush', 'Specialty'];
    const [translatedCategories, setTranslatedCategories] = useState({});

    useEffect(() => {
        async function translateCats() {
            const lang = localStorage.getItem("lang") || "en";

            // English → identity labels
            if (lang === "en") {
                const identity = {};
                categoryOrder.forEach(cat => identity[cat] = cat);
                setTranslatedCategories(identity);
                return;
            }

            const translated = await translateBatch(categoryOrder, lang);

            const mapping = {};
            categoryOrder.forEach((cat, i) => {
                mapping[cat] = translated[i] || cat;
            });

            setTranslatedCategories(mapping);
        }

        translateCats();
    }, [selectedCategory]);


    // ---------------------------------------------
    // 1. Translate drink names whenever menu loads,
    //    language changes, or category changes
    // ---------------------------------------------
    useEffect(() => {
        async function runTranslation() {
            const lang = localStorage.getItem("lang") || "en";

            // English → no translation needed
            if (lang === "en") {
                setTranslatedMenuItems(menuItems);
                setFilteredMenuItems(menuItems);
                return;
            }

            // Translate ALL drink names
            const names = menuItems.map(item => item.drink_name);
            const translated = await translateBatch(names, lang);

            const updated = menuItems.map((item, i) => ({
                ...item,
                drink_name: translated[i] || item.drink_name
            }));

            setTranslatedMenuItems(updated);
            setFilteredMenuItems(updated);
        }

        runTranslation();
    }, [menuItems, selectedCategory]);
    // category change triggers translation of visible list


    // ---------------------------------------------
    // 2. Filtering logic uses the translated names
    // ---------------------------------------------
    function filterItems(search) {
        const lower = search.toLowerCase();

        const results = translatedMenuItems.filter(item =>
            item.drink_name.toLowerCase().includes(lower)
        );

        setFilteredMenuItems(results);
    }


    // ---------------------------------------------
    // 3. Categorization based on filtered translated items
    // ---------------------------------------------
    const categorizedMenu = useMemo(() => {
        const itemsByCategory = new Map();

        filteredMenuItems.forEach(it => {
            const cat = it.category || "Other";
            if (!itemsByCategory.has(cat)) itemsByCategory.set(cat, []);
            itemsByCategory.get(cat).push(it);
        });

        const categoriesToRender = [
            ...categoryOrder.filter(cat => itemsByCategory.has(cat) && cat === selectedCategory),
            ...Array.from(itemsByCategory.keys()).filter(
                cat => !categoryOrder.includes(cat) && cat === selectedCategory
            )
        ];

        return { itemsByCategory, categoriesToRender };
    }, [filteredMenuItems, selectedCategory]);


    // ---------------------------------------------
    // Render
    // ---------------------------------------------
    return (
        <div>
            <div className="toolbar">
                <button
                    id="backBtn"
                    className="btn gap-right"
                    onClick={() => { window.location.pathname = '/' }}
                >
                    Back
                </button>

                <label htmlFor="search" className="sr-only">Search menu</label>
                <input
                    id="search"
                    className="search-input"
                    type="search"
                    placeholder="Search drinks…"
                    onChange={(e) => filterItems(e.target.value)}
                />
            </div>

            <CategoryButtons setSelectedCategory={setSelectedCategory} />
            {/* <h3 className="menu-category-heading">{selectedCategory}</h3> */}
            <h2 className="menu-category-heading">
                {translatedCategories[selectedCategory] || selectedCategory}
            </h2>

            <div id="menuGrid" className="grid-cards" aria-live="polite">
                <MenuBody
                    itemsByCategory={categorizedMenu.itemsByCategory}
                    categoriesToRender={categorizedMenu.categoriesToRender}
                    money={money}
                    setShowCustomizationModal={setShowCustomizationModal}
                    setCurrentMenuItem={setCurrentMenuItem}
                />
            </div>
        </div>
    );
}
