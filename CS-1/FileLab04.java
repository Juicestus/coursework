import java.util.Scanner;
import java.io.IOException;
import java.io.File;

public class FileLab04 {
    public static void main(String[] args) throws IOException {
		Scanner fileReader = new Scanner(new File("../dat/04.dat"));
		int max = fileReader.nextInt();
		while (fileReader.hasNextInt())
			max = Math.max(max, fileReader.nextInt());
		System.out.println(max);
    }
}
