import java.util.Scanner;

public class Pr0501 {
    public static void main(String[] args) {
		String input = MyLibrary.getLine("In:");
		Scanner chopper = new Scanner(input);
		double sum = 0, n = 0;
		for ( ; chopper.hasNextDouble(); n++)
			sum += chopper.nextDouble();
		System.out.printf("Sum: %f, Avg: %f\n", sum, sum / n);
    }
}
