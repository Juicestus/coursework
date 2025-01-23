import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class Pr0608 {
    public static void printStringArray(String[] array) {
		System.out.print("[");
		for (int i = 0; i < array.length - 1; i++)
			System.out.printf("%s, ", array[i]);
		System.out.printf("%s]\n", array[array.length - 1]);
	}
    public static void main(String[] args) throws IOException {
        File file = new File("../dat/Pr0608.dat");

        // Count ammount of words
        // Yes, I know this lab is only 8, but this is best practice
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

            while (true) {
                boolean sorted = true;
                for (int i = 1; i < words.length; i++)
                    if (words[i].compareTo(words[i - 1]) < 0) {
                        sorted = false;
                        String swap = words[i];
                        words[i] = words[i - 1];
                        words[i - 1] = swap;
                    }
                if (sorted) break;
            }

        printStringArray(words);

        fileReader.close();
    }
}
