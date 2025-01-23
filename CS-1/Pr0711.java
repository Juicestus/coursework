import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Pr0711 {
    public static void main(String[] args) throws IOException {
        File file = new File("../dat/Pr0711.dat");

        Scanner fileReader = new Scanner(file);
       
        ArrayList<Integer> nums = new ArrayList<Integer>();

        // Fill array
        for (; fileReader.hasNextInt();)
            nums.add(fileReader.nextInt());

        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
            sum += nums.get(i);

        System.out.printf("Sum: %d, Avg: %f\n", sum, sum / (nums.size() + 0.));

        fileReader.close();
    }
}
