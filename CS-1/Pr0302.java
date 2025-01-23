public class Pr0302 {
    public static boolean even(int n) {
        return n % 2 == 0;
    }

    public static void main(String[] args) {
        if (even(MyLibrary.getInt("Give me an int!")))
            System.out.println("even");
        else
            System.out.println("odd");
    }
}
