public class Pr0444 {
	public static void main(String[] args) {
		int input = MyLibrary.getInt("Input:");
		for (int i = input / 2; i >= 0; i--) {
			for (int j = 1; j <= i; j++)
				System.out.print(" ");
			for (int j = 1; j <= input - i * 2; j++)
				System.out.print("m");
			for (int j = 1; j <= i; j++)
				System.out.print(" ");
			System.out.println("");
		}
    }
}
