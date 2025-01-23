import java.io.*;
import java.util.*;

public class FileLab02 {
    public static void main(String[] args) throws IOException {
		
		Scanner fileReader = new Scanner(new File("../dat/02.dat"));
		int sum = 0;
		while (fileReader.hasNextInt())
			sum += fileReader.nextInt();
		System.out.println(sum);

    }
}
