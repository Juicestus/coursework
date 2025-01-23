import java.util.*;

public class Pr0203 {

	public static void fName(String first, String last) {
		System.out.println(first + " " + last);
	}

	public static void main(String[] args) {
		Scanner kb = new Scanner(System.in);
		System.out.printf("Gimme ur first name: ");
		String first = kb.nextLine();
		System.out.printf("Gimme ur last name: ");
		String last = kb.nextLine();

		fName(first, last);
	}
}