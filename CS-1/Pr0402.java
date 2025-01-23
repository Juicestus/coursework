public class Pr0402 {
    public static void main(String[] args) {
        double sum = 0;
        for (int i = 1; i <= 5; i++)
            sum += MyLibrary.getDouble("Gimme a number: ");
        System.out.printf("The sum of the numbers is: %f\n", sum);
    }
}
