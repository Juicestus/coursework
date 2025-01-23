import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Pr0605 {
    public static void main(String[] args) throws IOException {
        File file = new File("../dat/Pr0605.dat");

        // Count ammount of words
        int ammount = 0;
        Scanner fileReader = new Scanner(file);
        for (; fileReader.hasNext(); fileReader.next())
            ammount++;
        
        fileReader.close(); // To avoid resources leak
            
        fileReader = new Scanner(file); // Reset filereader 

        String[] words = new String[ammount]; // Allocate array

        // Fill array
        for (int i = 0; fileReader.hasNext(); i++)
            words[i] = fileReader.next();

        // Find min
        String min = words[0];
        for (int i = 1; i < ammount; i++)
            if (words[i].compareTo(min) < 0)
                min = words[i];

        fileReader.close();

        // Output max to file
        PrintWriter writer = new PrintWriter("../min.dat");
        writer.println(min);
        writer.close();
    }
}
