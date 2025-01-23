import java.util.Scanner;

public class Pr0107 {
	public static void main(String args[]) {
		Scanner kb = new Scanner(System.in);
		System.out.print("Give me a number: ");
		double numberA = kb.nextFloat();
		kb.nextLine();
		System.out.print("Give me another number: ");
		double numberB = kb.nextFloat();
		kb.nextLine();
		System.out.print("Give me a short phrase: ");
		String shortPhrase = kb.nextLine();

		double avg = (numberA + numberB) / 2.0;
		System.out.printf("The average is %.3f and your phrase is \"", avg);
		System.out.println(shortPhrase + "\".");
	}
}
