import java.util.Scanner;
import java.io.IOException;
import java.io.File;

public class FileLab08 {
    public static void main(String[] args) throws IOException {
		Scanner fileReader = new Scanner(new File("../dat/08.dat"));
				
		for (int n; fileReader.hasNextInt(); ) {
            n = fileReader.nextInt();
            for (String s = ""; s.length() <= n; s += "*")
                System.out.println(s);
        }

    }
}
