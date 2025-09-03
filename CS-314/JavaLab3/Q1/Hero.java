import java.util.ArrayList;
import java.util.List;

public class Hero extends Character
{
	private int armour; // [0 - 100%]

	public Hero(String name, Location location, List<String> carrying, int hearts, int armour) 
	{
		// taking care of items needed for Item
		super(name, location);
		// taking care of abstract items from Character
		super.carrying = new ArrayList<String>();
		super.carrying = carrying; // passed in from constuctor
		super.hearts = hearts;	
		this.armour = armour;
	}
	
	public int getArmour() { return armour; }
	public void setArmour(int armour) { this.armour = armour; } 
	public String getCarrying() { return super.carrying.toString(); }
	public void setCarrying(String thing) { super.carrying = thing; };
	

	@Override
	public String toString() {
		return "Hero [name=" + name + ", armour=" + armour + ", hearts=" + hearts + ", carrying=" + getCarrying()
				+ ", location=" + location + "]";
	}	
	
}
