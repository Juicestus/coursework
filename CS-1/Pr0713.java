import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Pr0713 {

    public static void main(String[] args) throws IOException {
        File file = new File("../dat/Pr0713.dat");

        Scanner fileReader = new Scanner(file);
       
        ArrayList<Integer> nums = new ArrayList<Integer>();

        for (; fileReader.hasNextInt();)
            nums.add(fileReader.nextInt());

        for (int i = 0, n; i < nums.size(); i++) {
            System.out.printf("%d:", n = nums.get(i));
            for (int j = 1; j <= n / 2.; j++)
                if (n % j == 0)
                    System.out.printf(" %d", j);
            System.out.println();
        }

        fileReader.close();
    }
}
