public class PrML05 {
	public static String quadRoots(int a, int b, int c) {
		double d = Math.sqrt(b * b - 4 * a * c);
		double x1 = (-b + d) / (2 * a);
		double x2 = (-b - d) / (2 * a);
		return a + " " + b + " " + c + "-->" + x1 + ", " + x2;
	}

	public static void main(String[] args) {
		System.out.println(quadRoots(
				MyLibrary.getInt("Coeficient \"a\":"),
				MyLibrary.getInt("Coeficient \"b\":"),
				MyLibrary.getInt("Coeficient \"c\":")));
	}
}
