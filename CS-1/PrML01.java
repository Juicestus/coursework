public class PrML01 {
    public static String cut(String s) {
        int i = s.indexOf(' ');
        String w = s.substring(i + 1);
        s = s.substring(0, i - 1);
        int half = s.length() / 2;
        return s.substring(0, half + 1) + w + s.substring(half);
    }

    public static void main(String[] args) {
        System.out.println(cut(MyLibrary.getLine("Gimme a sentance: ")));
    }
}
