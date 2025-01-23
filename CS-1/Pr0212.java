import java.util.*;

public class Pr0212 {
    public static String unPig(String w) {
        return w.charAt(w.length() - 3) + w.substring(0, w.length() - 3);
    }

    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Give a pig latin word: ");
        String word = kb.next();
        System.out.printf("English: %s\n", unPig(word));
    }
}
