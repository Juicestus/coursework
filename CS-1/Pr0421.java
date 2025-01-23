public class Pr0421 {
    public static void main(String[] args) {
		String s = "";
		char c;
		do {
			c = MyLibrary.getWord("Letter: ").charAt(0);
			if (s.indexOf(c) == -1) s += c;
		} while (c != 'e');

		System.out.println("Number: " + s.length());
		System.out.println("Letters: " + s);

    }
}
