import java.util.Scanner;

public class Pr0506 {
	public static String prime(int n) {
		if (n == 1) return "1 is unity";
		for (int i = n / 2; i > 1; i--)
			if (n % i == 0)
				return "" + n + " is composite";
		return "" + n + " is prime";
	}

    public static void main(String[] args) {
		Scanner chopper = new Scanner(MyLibrary.getLine("In:"));  
        while (chopper.hasNextInt())
			System.out.println(prime(chopper.nextInt()));
    }
}
