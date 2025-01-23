import java.lang.reflect.Array;
import java.util.Scanner;
import java.lang.reflect.ParameterizedType;

/**
 * Utility library for Computer Science AP in Java.
 *
 * @author Steven Smith
 * @author Justus Languell
 */
public final class MyLibrary {
	
	private final static Scanner kb = new Scanner(System.in);

	/**
	 * Private constructor makes class static as no instances
	 * can be created
	 */
	private MyLibrary() {
	}

	/**
	 * This method will return an integer (long) in the range [1,n]
	 *
	 * @param n The maximum value to generate
	 *
	 * @return The randomly generated number
	 */
	public static long getRandNum(final int n) {
		return (long) (Math.random() * n) + 1;
	}

	/**
	 * This method will return an integer in the range [lo,hi]
	 *
	 * @param lo The lower bound of numbers to generate
	 * @param hi The upper bound of numbers to generate
	 *
	 * @return The randomly generated number
	 */
	public static int getRandNum(final int lo, final int hi) {
		return (int) (Math.random() * (hi - lo + 1)) + lo;
	}

	/**
	 * Gets an integer from console providing the user with a prompt
	 *
	 * @param prompt The prompt to give the user
	 *
	 * @return The integer from the user
	 */
	public static int getInt(final String prompt) {
		System.out.print(prompt + "  ");
		return kb.nextInt();
	}

	/**
	 * Gets a double from console providing the user with a prompt
	 *
	 * @param prompt The prompt to give the user
	 *
	 * @return The double from the user
	 */
	public static double getDouble(final String prompt) {
		System.out.print(prompt + "  ");
		return kb.nextDouble();
	}

	/**
	 * Gets a single word (string) from console providing the user with a prompt
	 *
	 * @param prompt The prompt to give the user
	 *
	 * @return The word from the user
	 */
	public static String getWord(final String prompt) {
		System.out.print(prompt + "  ");
		return kb.next();
	}

	/**
	 * Gets a sentance (string) from console providing the user with a prompt
	 *
	 * @param prompt The prompt to give the user
	 *
	 * @return The sentance from the user
	 */
	public static String getLine(final String prompt) {
		System.out.print(prompt + "  ");
		return kb.nextLine();
	}

	/**
	 * Round number "num" to the ammount of decimal places "dec"
	 *
	 * @param num Number to round
	 * @param dec Decimal places to round to
	 *
	 * @return The rounded number
	 */
	public static double round(final double num, final long dec) {
		return (int) Math.round((num * Math.pow(10, dec))) / Math.pow(10, dec);
	}
	
	/**
	 * A println function similar to that in Python
	 *
	 * @param params The items to print
	 */
	public static void println(final Object... args) {
		StringBuilder sb = new StringBuilder();
		for (Object arg : args) sb.append(arg.toString());
		System.out.println(sb);
	}

	/**
	 * Check if an integer (long) is prime or not
	 * 
	 * @param params The number to check for prime
	 * 
	 * @return If the numbers if prime or not
	 */
	public static boolean prime(final long n) {
    	if (n == 2 || n == 3) return true;
    	if (n < 2 || n % 2 == 0 || n % 3 == 0) return false;
    	for (long i = 6L; i <= ((long) Math.sqrt(n) + 1); i += 6)
        	if (n % (i - 1) == 0 || n % (i + 1) == 0) return false;
    	return true;
	}

	public static <T> String matrixToString(final T[][] matrix) {
		final StringBuilder sb = new StringBuilder();
		int longest = -1, len;
		for (final T[] row : matrix)
			for (final T item : row)
				if ((len = item.toString().length()) > longest) longest = len;
		for (final T[] row : matrix) {
			for (final T item : row) {
				sb.append(item.toString());
				for (int i = item.toString().length(); i <= longest; i++)
					sb.append(" ");
			}
			sb.append("\n");
		}
		final String str = sb.toString();
		return str.substring(0, str.length() - 1);
	}
}
