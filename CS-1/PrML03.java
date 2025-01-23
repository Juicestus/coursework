public class PrML03 {
	public static int range(int a, int b) {
		return (b - a) / 2 + a;
	}

	public static void main(String[] args) {
		int lo = MyLibrary.getInt("Gimme a number");
		int hi = MyLibrary.getInt("Gimme another number");
		System.out.println(range(lo, hi));
	}
}
