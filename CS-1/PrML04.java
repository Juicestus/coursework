public class PrML04 {
	public static double avg(int a, int b, int c) {
		return MyLibrary.round((a + b + c) / 3., 5);
	}

	public static void main(String[] args) {
		System.out.println(avg(
				MyLibrary.getInt("Gimme a number"),
				MyLibrary.getInt("Gimme another number"),
				MyLibrary.getInt("Gimme one last number")));
	}
}
