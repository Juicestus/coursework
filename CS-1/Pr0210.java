import java.util.*;

public class Pr0210 {
	public static void halves(String s) {
		int len = s.length();
		int half = (int) (len / 2);
		String h1 = s.substring(0, half);
		String h2 = s.substring(half);
		System.out.printf("String length: %d\n"
				+ "First half of string: %s\n"
				+ "Second half of string: %s\n",
				len, h1, h2);
	}

	public static void main(String[] args) {
		Scanner kb = new Scanner(System.in);
		System.out.print("Give a sentance: ");
		String line = kb.nextLine();

		halves(line);
	}
}
