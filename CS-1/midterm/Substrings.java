public class Substrings {
	public static void main(String[] args) {
		final String digits = "0123456789";
		System.out.println(digits.substring(0, 5));
		System.out.println(digits.substring(5));

		try {
			System.out.println(digits.substring(5, 100));
		} catch (Throwable e) {
			System.out.println("Out of bounds throws error");
		} 
		
		try {
			System.out.println(digits.substring(100));
		} catch (Throwable e) {
			System.out.println("Out of bounds throws error");
		}
	}
}


