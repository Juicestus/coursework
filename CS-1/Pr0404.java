public class Pr0404 {
    public static void main(String[] args) {
        int n = MyLibrary.getInt("Gimme a number: ");
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++)
                System.out.print("#");
            System.out.println();
        }
    }
}
