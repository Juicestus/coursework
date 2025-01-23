public class Pr0438 {
    public static void main(String[] args) {
		String word = MyLibrary.getWord("input:");
		String buffer = "";
		for (int i = 0; i < word.length(); i++) {
			System.out.println(buffer + word.charAt(i));
			buffer += " ";
		}
    }
}
