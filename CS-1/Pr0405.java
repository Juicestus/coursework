public class Pr0405 {
    public static void main(String[] args) {
        int n = MyLibrary.getInt("How many numbers do you want to generate?:");
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            int r = MyLibrary.getRandNum(1, 20);
            System.out.printf("Random number %d: %d\n", i, r);
            sum += r;
        }
        System.out.printf("The sum of the numbers is: %d\n", sum);
        System.out.printf("The average of the numbers is: %f\n", sum / (double) n);
    }
}
