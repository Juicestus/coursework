import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Pr0604 {
    public static void main(String[] args) throws IOException {
        File file = new File("../dat/Pr0604.dat");

        // Count ammount of numbers
        int ammount = 0;
        Scanner fileReader = new Scanner(file);
        for (; fileReader.hasNextInt(); fileReader.nextInt())
            ammount++;
        
        fileReader.close(); // To avoid resources leak
            
        fileReader = new Scanner(file); // Reset filereader 

        int[] numbers = new int[ammount]; // Allocate array

        // Fill array
        for (int i = 0; fileReader.hasNextInt(); i++)
            numbers[i] = fileReader.nextInt();

        // Find max
        int max = numbers[0];
        for (int i = 1; i < ammount; i++)
            if (numbers[i] > max)
                max = numbers[i];

        fileReader.close();

        // Output max to file
        PrintWriter writer = new PrintWriter("../max.dat");
        writer.println(max);
        writer.close();
    }
}
