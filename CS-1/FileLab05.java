import java.util.Scanner;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.File;
import java.io.FileWriter;

public class FileLab05 {
    public static void main(String[] args) throws IOException {
		Scanner fileReader = new Scanner(new File("../dat/05.dat"));
		
		PrintWriter fileOut = new PrintWriter(new FileWriter("../Odds.dat"));
		
		for (int buffer; fileReader.hasNextInt(); )
			if ((buffer = fileReader.nextInt()) % 2 == 1)
				fileOut.println(buffer);

		fileOut.close();
    }
}
