import java.util.Scanner;

public class Pr0104 {
	public static void main(String[] args) {
		double PI = 3.14;
		System.out.printf("Crcle Area and Circumference Calculator\n");
		Scanner kb = new Scanner(System.in);
		System.out.printf("Diameter: ");
		double diameter = kb.nextDouble();

		double circum = diameter * PI;
		double area = (diameter / 2) * (diameter / 2) * PI;
		System.out.printf("The area of the circle is %.2f and the circumference is %.2f\n",
				area, circum);
		kb.close();
	}
}