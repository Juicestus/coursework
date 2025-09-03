
public abstract class Item 
{
	protected String name;
	protected Location location;
	
	public Item(String name, Location location) {
		this.name = name;
		this.location = location;
	}

	public String getName() { return name; }
	public Location getLocation() { return location; }
	public void setName(String name) { this.name = name; }
	public void setLocation(Location location) { this.location = location; }

	@Override
	public String toString() {
		return "Item [name=" + name + ", location=" + location + ", getName()=" + getName() + 
				", getLocation()=" + getLocation() + ",  toString()=" + super.toString() + "]";
	}

}
