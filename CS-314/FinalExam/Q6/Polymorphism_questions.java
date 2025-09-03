import java.util.ArrayList;

//Finish this parking lot file using OOP principles,


class ParkingLot{
	protected ArrayList<ParkingSpot> parkingSpots =  new ArrayList<ParkingSpot>(); 
	
	public void addNewSpot(ParkingSpot s) {
		parkingSpots.add(s);
	}
	
	public boolean fillFirstAvailableEmptySpot(Vehicle v) {
		//Q3: needs to be implemented
		//checks the first empty spot if it can fill Vehicle v by it's size,
		//then fills that spot via ParkVehicle().
		//returns true on success. False otherwise, even if other parking spots are empty.
		for (int i = 0; i < parkingSpots.size(); i++)
		{
			if (parkingSpots.get(i).checkIfVehicleFits(v) && !parkingSpots.get(i).isFull())
			{
				parkingSpots.get(i).ParkVehicle(v);
				return true;
			}
		}
		return false;
	}
	
	public boolean check_all_spots_full() {
		//Q4: needs to be implemented, returns true if all spots are full, false otherwise
		for (int i = 0; i < parkingSpots.size(); i++)
		{
			if (!parkingSpots.get(i).isFull())
			{
				return false;
			}
		}
		return true;	
	}
	
}

class ParkingSpot 
{ 
   private Vehicle vehicle; 
   private int spotSize; 
   private boolean full;
   
   public ParkingSpot(int spotSize) 
   {this.spotSize = spotSize;
   full = false;} 
 
   public void ParkVehicle(Vehicle v) {
	  this.vehicle = v;
	  this.full = true;
   }
   
   public int getSpotSize() {
   	return spotSize;
   }
   
   public boolean isFull() {
	   return full;
   }
   
   public boolean checkIfVehicleFits(Vehicle v) {
	   //Q2: needs to be implemented, checks if Vehicle v can fit in this Parking Spot by size.
	   return v.getSize() <= spotSize;
   }
 
} 

//Q1: Vehicle, car, motorcycle, and bus classes need to be implemented
//Car is size 4, motorcycle is size 2, bus is size 4
//Vehicle should have an abstract getsize method
  
abstract class Vehicle {
	abstract int getSize();	

}

class Car extends Vehicle {
	public int getSize() { return 4; }
}
class Bus extends Vehicle {
	public int getSize() { return 4; }
}
class Motorcycle extends Vehicle {
	public int getSize() { return 2; }
}
