import java.util.*;

public class Pr0209 {
	public static String removeFirst(char c, String s) {
		return s.substring(0, s.indexOf(c)) + s.substring(s.indexOf(c) + 1);
	}

	public static void main(String[] args) {
		Scanner kb = new Scanner(System.in);
		System.out.print("Give a string with at least 3 capital F's: ");
		String line = kb.nextLine();

		line = removeFirst('F', line);
		line = removeFirst('F', line);
		line = removeFirst('F', line);
		System.out.println("FFF" + line);
	}
}
