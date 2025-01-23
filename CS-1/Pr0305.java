public class Pr0305 {
    public static String alpha(String s) {
        String garf = "Garfield";
        if (s.toLowerCase().compareTo(garf.toLowerCase()) > 0)
            return garf + s;
        else
            return s + garf;
    }

    public static void main(String[] args) {
        System.out.println(alpha(
                MyLibrary.getLine("Gimme a word")));
    }
}
