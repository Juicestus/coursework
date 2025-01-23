import java.util.*;

public class Pr0208 {
    public static double biggest(double a, double b) {
        return Math.max(a, b);
    }

    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Give me a number: ");
        double a = kb.nextDouble();
        System.out.print("Give me another number: ");
        double b = kb.nextDouble();
        System.out.println(biggest(a, b));
    }
}
