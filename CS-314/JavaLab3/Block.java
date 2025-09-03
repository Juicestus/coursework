
public class Block extends Item
{
	protected int density;

	public Block(String name, Location location, int density) {
		super(name, location);
		this.density = density;
	}

	public int getDensity() { return density; }
	public void setDensity(int density) { this.density = density; }

	@Override
	public String toString() {
		return "Block [name=" + name + ", density=" + density + ", location=" + location + "]";
	}
	
	
}
