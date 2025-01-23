import java.util.Scanner;

public class Pr0103 {
	public static void main(String[] args) {
		System.out.printf("Triangle Area Calculator\n");
		Scanner kb = new Scanner(System.in);
		System.out.printf("Base: ");
		double base = kb.nextDouble();
		System.out.printf("Height: ");
		double height = kb.nextDouble();
		double area = (base * height) / 2;
		System.out.printf("The area of the triangle is %.2f\n", area);
		kb.close();
	}
}