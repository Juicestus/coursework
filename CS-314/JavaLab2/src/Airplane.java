package src;

public class Airplane extends Vehicle implements Warplane {
    private String flightNumber, company;

    public String country = "NA";

    public String getMotor() { return motor; }
	public void setMotor(String newValue) { motor = newValue; }

    public String getFlightNumber() { return flightNumber; }
    public void setFlightNumber(String newValue) { flightNumber = newValue; }

    public String getCompany() { return company; }
    public void setCompany(String newValue) { company = newValue; }

    public void setCountry(String newValue) { country = newValue; }
    public String getCountry() { return country; }
    public void fireWeapon() { System.out.println("Firing the rocket!!!"); }
}
