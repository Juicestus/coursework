package src;

import java.util.List;
import java.util.ArrayList;

public class Driver {
    public static void main(String[] args)
    {
        // Vehicle v = new Vehicle();
        // v.setSpeed(100);
        // System.out.printf("%f\n", v.getSpeed());

        boolean flag = false;
        List<Vehicle> vl = new ArrayList<Vehicle>();

        // populate vl on flag
        if (flag) {
            for (int i = 0; i < 3; i++)
            {
                Car c = new Car();
                c.setLicense("" + i);
                c.setSpeed(100 + i * 10);
                c.setMotor("combustion"); // this makes no sense why not only set from constructor?
                vl.add(c);
            }
        } else {
            Airplane a = new Airplane();
            a.setCompany("Southwest");
            a.setFlightNumber("erhmsovhpx");
            a.setSpeed(10000);
            a.setMotor("jet"); 
            vl.add(a);

            Airplane b = new Airplane();
            b.setCompany("Delta");
            b.setFlightNumber("jwrlj3gspn");
            b.setSpeed(20000);
            b.setMotor("jet"); 
            vl.add(b);
                
            ((Warplane)b).fireWeapon();
        }

        // display private members
        for (Vehicle v : vl)
        {
            if (v instanceof Car)
                System.out.printf("Car speed=%f motor=%s license=%s \n", v.getSpeed(), v.getMotor(), ((Car)v).getLicense());
            else {
                System.out.printf("Airplane speed=%f motor=%s flightNumber=%s company=%s \n", v.getSpeed(), v.getMotor(), ((Airplane)v).getFlightNumber(), ((Airplane)v).getCompany());
            }
        }


        
    }
}
