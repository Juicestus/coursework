import java.util.*;

public class Pr0205 {
    public static int square(int n) {
        return n * n;
    }

    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Give me an integer: ");
        int number = kb.nextInt();
        System.out.println(square(number));
    }
}
