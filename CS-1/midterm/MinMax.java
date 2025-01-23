
public class MinMax {
	public static void main(String[] args) {
		final int a = 5;
		for (double i = 3; i <= 7; i += .5) 
			// If one of the params is floating point, 
			// the return value will be floating point
			System.out.println(Math.max(a, i));

	}
}
