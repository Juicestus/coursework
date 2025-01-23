import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Pr0712 {

    // A static method from my personal Java library
    // I have used this in other labs before
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
        File file = new File("../dat/Pr0712.dat");

        Scanner fileReader = new Scanner(file);
       
        ArrayList<Integer> nums = new ArrayList<Integer>();

        for (; fileReader.hasNextInt();)
            nums.add(fileReader.nextInt());

        for (int i = 0, n; i < nums.size(); i++)
            if (prime(n = nums.get(i)))
                System.out.printf("%d\n", n);

        fileReader.close();
    }
}
