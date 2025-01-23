public class Pr0437 {
    public static void main(String[] args) {
		int max = MyLibrary.getInt("input:");
		String buffer = "";
		for (String line = "*"; line.length() <= max; line += "*")
			buffer = line + "\n" + buffer;
		System.out.println(buffer);
    }
}
