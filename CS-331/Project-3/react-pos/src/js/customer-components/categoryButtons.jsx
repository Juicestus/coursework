export default function CategoryButtons({ setSelectedCategory }) {
    return (
        <div className="category-buttons">
            <button className="btn " onClick={() => setSelectedCategory('Milk Tea')}>Milk Tea</button>
            <button className="btn " onClick={() => setSelectedCategory('Fruit Tea')}>Fruit Tea</button>
            <button className="btn " onClick={() => setSelectedCategory('Smoothie')}>Smoothie</button>
            <button className="btn " onClick={() => setSelectedCategory('Slush')}>Slush</button>
            <button className="btn " onClick={() => setSelectedCategory('Specialty')}>Specialty</button>
        </div>
    )
}