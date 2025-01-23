import java.util.*;

public class Pr0202 {
	public static void sum(int a, int b) {
		System.out.println(a + b);
	}

	public static void main(String[] args) {
		Scanner kb = new Scanner(System.in);
		System.out.printf("Gimme an int: ");
		int a = kb.nextInt();
		System.out.printf("Gimme another int: ");
		int b = kb.nextInt();

		sum(a, b);
	}
}