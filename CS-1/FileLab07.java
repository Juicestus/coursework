import java.util.Scanner;
import java.io.IOException;
import java.io.File;

public class FileLab07 {
    public static void main(String[] args) throws IOException {
		Scanner fileReader = new Scanner(new File("../dat/07.dat"));
		fileReader.nextLine();
		
		for (Scanner lineReader; fileReader.hasNextLine(); ) {
			lineReader = new Scanner(fileReader.nextLine());
            String maxWord = "", wordBuffer;
			while (lineReader.hasNext()) {
                wordBuffer = lineReader.next();
                if (wordBuffer.length() > maxWord.length())
                    maxWord = wordBuffer;
            }
			System.out.println(maxWord);
		}
    }
}
