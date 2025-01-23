public class Pr0310 {
    /**
     * This method was generated automatically to * order 4
     * doubles and return them as a string with a single space delimiter.
     *
     * @author Justus
     */
    public static String order(double a, double b, double c, double d) {
        if (a <= b && b <= c && c <= d)
            // a ≤ b ≤ c ≤ d
            return a + " " + b + " " + c + " " + d;
        else if (a <= b && b <= d && d <= c)
            // a ≤ b ≤ d ≤ c
            return a + " " + b + " " + d + " " + c;
        else if (a <= c && c <= b && b <= d)
            // a ≤ c ≤ b ≤ d
            return a + " " + c + " " + b + " " + d;
        else if (a <= c && c <= d && d <= b)
            // a ≤ c ≤ d ≤ b
            return a + " " + c + " " + d + " " + b;
        else if (a <= d && d <= c && c <= b)
            // a ≤ d ≤ c ≤ b
            return a + " " + d + " " + c + " " + b;
        else if (a <= d && d <= b && b <= c)
            // a ≤ d ≤ b ≤ c
            return a + " " + d + " " + b + " " + c;
        else if (b <= a && a <= c && c <= d)
            // b ≤ a ≤ c ≤ d
            return b + " " + a + " " + c + " " + d;
        else if (b <= a && a <= d && d <= c)
            // b ≤ a ≤ d ≤ c
            return b + " " + a + " " + d + " " + c;
        else if (b <= c && c <= a && a <= d)
            // b ≤ c ≤ a ≤ d
            return b + " " + c + " " + a + " " + d;
        else if (b <= c && c <= d && d <= a)
            // b ≤ c ≤ d ≤ a
            return b + " " + c + " " + d + " " + a;
        else if (b <= d && d <= c && c <= a)
            // b ≤ d ≤ c ≤ a
            return b + " " + d + " " + c + " " + a;
        else if (b <= d && d <= a && a <= c)
            // b ≤ d ≤ a ≤ c
            return b + " " + d + " " + a + " " + c;
        else if (c <= b && b <= a && a <= d)
            // c ≤ b ≤ a ≤ d
            return c + " " + b + " " + a + " " + d;
        else if (c <= b && b <= d && d <= a)
            // c ≤ b ≤ d ≤ a
            return c + " " + b + " " + d + " " + a;
        else if (c <= a && a <= b && b <= d)
            // c ≤ a ≤ b ≤ d
            return c + " " + a + " " + b + " " + d;
        else if (c <= a && a <= d && d <= b)
            // c ≤ a ≤ d ≤ b
            return c + " " + a + " " + d + " " + b;
        else if (c <= d && d <= a && a <= b)
            // c ≤ d ≤ a ≤ b
            return c + " " + d + " " + a + " " + b;
        else if (c <= d && d <= b && b <= a)
            // c ≤ d ≤ b ≤ a
            return c + " " + d + " " + b + " " + a;
        else if (d <= b && b <= c && c <= a)
            // d ≤ b ≤ c ≤ a
            return d + " " + b + " " + c + " " + a;
        else if (d <= b && b <= a && a <= c)
            // d ≤ b ≤ a ≤ c
            return d + " " + b + " " + a + " " + c;
        else if (d <= c && c <= b && b <= a)
            // d ≤ c ≤ b ≤ a
            return d + " " + c + " " + b + " " + a;
        else if (d <= c && c <= a && a <= b)
            // d ≤ c ≤ a ≤ b
            return d + " " + c + " " + a + " " + b;
        else if (d <= a && a <= c && c <= b)
            // d ≤ a ≤ c ≤ b
            return d + " " + a + " " + c + " " + b;
        else if (d <= a && a <= b && b <= c)
            // d ≤ a ≤ b ≤ c
            return d + " " + a + " " + b + " " + c;
        else
            return "";
    }

    public static void main(String[] args) {
        System.out.println("Enter four numbers!");
        System.out.println(order(MyLibrary.getDouble("Number 1: "),
                MyLibrary.getDouble("Number 2: "),
                MyLibrary.getDouble("Number 3: "),
                MyLibrary.getDouble("Number 4: ")));
    }
}
