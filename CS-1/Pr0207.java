import java.util.*;

public class Pr0207 {
    public static double three(int x) {
        return (int) (Math.sqrt(x) * 1000 + .5) / 1000.;
    }

    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Give me an integer: ");
        int input = kb.nextInt();
        System.out.println(three(input));
    }
}
