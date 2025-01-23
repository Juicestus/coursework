public class Pr0413 {
	public static String splice(String a, String b) {
		int i = 0;
		String ret = "";
		while (i < a.length())
			ret += "" + a.charAt(i) + b.charAt(i++);
		return ret;
	}

    public static void main(String[] args) {
		String one = MyLibrary.getWord("Give me a word");
		String two = MyLibrary.getWord("Give me another word with the same  length");

		if (one.length() != two.length()) {
			System.out.println("They must be the same length");
			return;
		}
	
		System.out.println(splice(one, two));
    }
}
