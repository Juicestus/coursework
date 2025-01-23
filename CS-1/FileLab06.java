import java.util.Scanner;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.File;
import java.io.FileWriter;

public class FileLab06 {

	public static boolean prime(long n) {
    	if (n < 2) return false;
    	if (n == 2 || n == 3) return true;
    	if (n % 2 == 0 || n % 3 == 0) return false;
    	long s = (long) Math.sqrt(n) + 1;
    	for (long i = 6L; i <= s; i += 6)
        	if (n % (i - 1) == 0 || n % (i + 1) == 0) return false;
    	return true;
	}

    public static void main(String[] args) throws IOException {
		Scanner fileReader = new Scanner(new File("../dat/06.dat"));
		
		PrintWriter fileOut = new PrintWriter(new FileWriter("../Primes.dat"));
		
		for (int buffer; fileReader.hasNextInt(); ) {
			buffer = fileReader.nextInt();

			if (prime(buffer))
				fileOut.println(buffer);
		}

		fileOut.close();
    }
}
