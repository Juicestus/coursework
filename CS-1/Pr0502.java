import java.util.Scanner;

public class Pr0502 {
    public static void main(String[] args) {
		Scanner chopper = new Scanner(MyLibrary.getLine("Input:"));
		double sum = 0;
		int n = chopper.nextInt();
		for (int i = 1; i <= n; i++)
			sum += chopper.nextDouble();
		System.out.printf("Sum: %f, Avg: %f\n", sum, sum / n);
    }
}
