public class Pr0441 {
    public static void main(String[] args) {
		int input = MyLibrary.getInt("Input:");
		for (int i = 1; i <= input; i++) {
			for (int j = 1; j <= i; j++)
				System.out.print("m");
			System.out.println("");
		}
    }
}
