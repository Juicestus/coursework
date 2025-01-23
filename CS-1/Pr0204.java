import java.util.*;

public class Pr0204 {
    public static double avg(double a, double b, double c) {
        return (int) (((a + b + c) / 3.) * 1000 + .5) / 1000.;
    }

    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Give me an integer: ");
        double a = kb.nextInt();
        System.out.print("Give me another integer: ");
        double b = kb.nextInt();
        System.out.print("Give me a final integer: ");
        double c = kb.nextInt();
        System.out.println(avg(a, b, c));

    }
}