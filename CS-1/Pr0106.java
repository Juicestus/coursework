import java.util.Scanner;

public class Pr0106 {
	public static void main(String args[]) {
		Scanner kb = new Scanner(System.in);
		System.out.print("Give me an integer: ");
		int a = kb.nextInt();
		System.out.print("Give me another integer: ");
		int b = kb.nextInt();
		System.out.print("Give me one more integer: ");
		int c = kb.nextInt();

		double average = (a + b + c) / 3.0;
		System.out.printf("The average of the three numbers is %.3f\n", average);
	}
}