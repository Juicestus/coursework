public class Pr0306 {
    public static boolean vowels(String s) {
        for (char c : new char[] { 'a', 'e', 'i', 'o', 'u' })
            if (s.indexOf(c) != -1)
                return true;
        return false;
    }

    public static void main(String[] args) {
        System.out.println(vowels(MyLibrary.getLine("Gimme a word")));
    }
}
