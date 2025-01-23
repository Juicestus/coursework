public class Pr0304 {
    public static String numbers(String s) {
        if (s.length() % 2 == 0)
            return s.substring(0, s.length() / 2);
        else
            return s.substring(s.length() / 2);
    }

    public static void main(String[] args) {
        System.out.println(numbers(
                MyLibrary.getLine("Giv me a sentance")));
    }
}
