public class Pr0442 {
    public static void main(String[] args) {
		int input = MyLibrary.getInt("Input:");
		String buffer = "";
		for (int i = 1; i <= input; i++) {
			for (int j = 1; j <= i; j++)
				buffer = "m" + buffer;
			buffer = "\n" + buffer;
		}
		System.out.println(buffer.substring(1));
    }
}
