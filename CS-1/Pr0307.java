public class Pr0307 {
    public static boolean three(double a, double b, double c) {
        if (a % 2 == 1)
            if (b % 2 == 1)
                if (c % 2 == 1)
                    return true;
        return false;
    }

    public static void main(String[] args) {
        System.out.println(three(
                MyLibrary.getDouble("Gimme a number"),
                MyLibrary.getDouble("Gimme another number"),
                MyLibrary.getDouble("Gimme one last number")));
    }
}
