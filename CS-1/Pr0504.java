import java.util.Scanner;

public class Pr0504 {
    public static void main(String[] args) {
		String backwards = "";
		Scanner chopper = new Scanner(MyLibrary.getLine("Input:"));
		while (chopper.hasNext()) backwards = chopper.next() + " " + backwards;
		System.out.println(backwards);
    }
}
