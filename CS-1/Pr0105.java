import java.util.Scanner;

public class Pr0105 {
	public static void main(String[] args) {
		Scanner kb = new Scanner(System.in);
		System.out.print("Gimme a noun: ");
		String noun = kb.next();
		kb.nextLine();
		System.out.print("Gimme a verb: ");
		String verb = kb.next();
		kb.nextLine();
		System.out.print("Gimme a color: ");
		String color = kb.next();
		kb.nextLine();
		System.out.print("Gimme a phrase: ");
		String phrase = kb.nextLine();

		System.out.printf("A " + color + " bear sat on the toilet and "
				+ verb + " a " + noun + ". When the bear finished"
				+ " he yelled out and proclaimed \"" + phrase + "\"\n");
	}
}