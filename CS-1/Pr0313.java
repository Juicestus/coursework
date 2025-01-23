public class Pr0313 {
	public static int oddZero(double n) {
		int ones = (int) n % 10;
		int tens = (int) Math.floor((n % 100) / 10);
		int hunds = (int) Math.floor(n / 100);

		if (n % 2 == 0)
			return hunds * 10000 + tens * 100 + ones;
		return ones * 100 + tens * 10 + hunds;
	}

	public static void main(String[] args) {
		System.out.println(oddZero(
				MyLibrary.getDouble("Give me a 3 digit number: ")));
	}
}
