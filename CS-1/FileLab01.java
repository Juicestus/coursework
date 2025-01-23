import java.io.*;
import java.util.*;

public class FileLab01 {
    public static void main(String[] args) throws IOException {
		
		Scanner fileReader = new Scanner(new File("../dat/01.dat"));

		while (fileReader.hasNextLine())
			System.out.println(fileReader.nextLine());

    }
}
