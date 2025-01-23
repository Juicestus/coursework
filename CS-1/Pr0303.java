public class Pr0303 {
    public static boolean vowel(String s) {
        // If we add all these up, any vowels that are not in the string will add -1.
        // If we get less than or equal to -6, there are no vowels.
        // The string has vowels if the sum is greater than -6.
        // I get this kindof missed the mark bc we expect only 1 character to be in the
        // strring,
        // but I thought of this and thought it was too clever to not put lol.
        return (s.indexOf("a") + s.indexOf("e") + s.indexOf("i") + s.indexOf("o")
                + s.indexOf("u") + s.indexOf("y")) > -6;
    }

    public static void main(String[] args) {
        if (vowel(MyLibrary.getWord("Give me a letter (or word for that matter)")))
            System.out.println("There is a vowel in the character/word.");
        else
            System.out.println("There is no vowel in the character/word.");
    }
}
