public class Pr0401 {
	public static void main(String[] args) {
		String sum = "";
		for (int i = 1; i <= 5; i++)
			sum += MyLibrary.getInt("Gimme a number: ") + " ";
		System.out.println(sum);
	}
}
