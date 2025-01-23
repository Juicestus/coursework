public class Pr0309 {
    public static String order(double a, double b, double c) {
        // a ≤ b ≤ c
        if (a <= b && b <= c)
            return "" + a + b + c;
        // a ≤ c ≤ b
        else if (a <= c && c <= a)
            return "" + a + c + b;
        // b ≤ a ≤ c
        else if (b <= a && a <= c)
            return "" + b + a + c;
        // b ≤ c ≤ a
        else if (b <= c && c <= a)
            return "" + b + c + a;
        // c ≤ a ≤ b
        else if (c <= a && a <= b)
            return "" + c + a + b;
        // c ≤ b ≤ a
        else if (c <= b && b <= a)
            return "" + c + b + a;

        return "If you are seeing this message, something is very, very wrong";
    }

    public static void main(String[] args) {
        System.out.println(order(
                MyLibrary.getDouble("Gimme a number"),
                MyLibrary.getDouble("Gimme another number"),
                MyLibrary.getDouble("Gimme a third number")));
    }
}
