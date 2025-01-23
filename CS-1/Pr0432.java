public class Pr0432 {
	public static String prime(int n) {
		for (int i = n; i > 0; i--)
			if (n % i == 0)
				return "" + n + " is not a prime number";
		return "" + n + " is a prime number";
	}

    public static void main(String[] args) {
		System.out.println(prime(MyLibrary.getInt("Number:")));
    }
}
