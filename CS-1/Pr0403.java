public class Pr0403 {
    public static void main(String[] args) {
        double sumOfEvens = 0;
        String allNumbers = "";
        for (int i = 1; i <= 10; i++) {
            double n = MyLibrary.getDouble("Gimme a number: ");
            if (n % 2 == 0)
                sumOfEvens += n;
            allNumbers += n + " ";
        }
        System.out.printf("The list of entered numbers is: %s\n", allNumbers);
        System.out.printf("The sum of the even numbers is: %f\n", sumOfEvens);
    }
}
