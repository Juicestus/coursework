public class Pr0436 {
    public static void main(String[] args) {
		int n = MyLibrary.getInt("input:");
		for (String b = "*"; b.length() <= n; b += "*")
			System.out.println(b);
    }
}
