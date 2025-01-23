import java.util.*;

public class Pr0211 {
    public static String pig(String w) {
        return w.substring(1) + w.charAt(0) + "ay";
    }

    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Give a word: ");
        String word = kb.next();
        System.out.printf("Pig latin: %s\n",
                pig(word));
    }
}
