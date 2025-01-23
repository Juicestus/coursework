import java.util.*;

public class Pr0206 {

	public static String sAndP(int a, int b, int c) {
		return "Sum= " + (a + b + c) + " and Product= " + (a * b * c);
	}

	public static void main(String[] args) {
		Scanner kb = new Scanner(System.in);
		System.out.print("Give me an integer: ");
		int a = kb.nextInt();
		System.out.print("Give me another integer: ");
		int b = kb.nextInt();
		System.out.print("Give me a final integer: ");
		int c = kb.nextInt();
		System.out.println(sAndP(a, b, c));
	}
}
