public class Pr0434 {
	public static boolean palindrome2(int n) {
		if (n < 0 || (n  % 10 == 0 && n != 0)) return false;

		int r = 0;
		for (; n > r; ) {
			r = r * 10 + n % 10;
			n /= 10;
		}
		
		return n == r || n == r / 10;
	}


    public static void main(String[] args) {
		System.out.println(palindrome2(MyLibrary.getInt("int")));
    }
}
