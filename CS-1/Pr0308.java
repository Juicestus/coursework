public class Pr0308 {
    public static boolean three(double a, double b, double c) {
        return a % 2 == 1 && b % 2 == 1 && c % 2 == 1;
    }

    public static void main(String[] args) {
        System.out.println(three(
                MyLibrary.getDouble("Gimme a number"),
                MyLibrary.getDouble("Gimme another number"),
                MyLibrary.getDouble("Gimme one last number")));
    }
}
