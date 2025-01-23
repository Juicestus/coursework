import java.util.Scanner;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.File;
import java.io.FileWriter;

public class FileLab03 {
    public static void main(String[] args) throws IOException {
		Scanner fileReader = new Scanner(new File("../dat/03.dat"));
		fileReader.nextLine();
		
		PrintWriter fileOut = new PrintWriter(new FileWriter("../RowSum.dat"));

		for (Scanner lineReader; fileReader.hasNextLine(); ) {
			lineReader = new Scanner(fileReader.nextLine());
			int rowSum = 0;
			while (lineReader.hasNextInt())
				rowSum += lineReader.nextInt();
			fileOut.println(rowSum);
		}

		fileOut.close();


    }
}
