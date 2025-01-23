import java.util.Scanner;

public class Pr0505 {
    public static void main(String[] args) {
		String input = MyLibrary.getLine("In:");  
        Scanner chopper = new Scanner(input);  
		double min = Integer.MAX_VALUE, max = Integer.MIN_VALUE, current;
        while (chopper.hasNextDouble()) {
			current = chopper.nextDouble();
			min = Math.min(min, current);
			max = Math.max(max, current);
		}
		System.out.printf("Min: %f, Max: %f\n", min, max);
    }
}
