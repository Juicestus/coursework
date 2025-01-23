public class Pr0443 {
    public static void main(String[] args) {
		int input = MyLibrary.getInt("Input:");
		for (int i = 1; i <= input; i++) {
			for (int j = 1; j <= input; j++)
				// I know we havent learned this, but its
				// just a short if/else statment
				System.out.print(input - i >= j ? " " : "m"); 
			System.out.println("");
		}
    }
}
