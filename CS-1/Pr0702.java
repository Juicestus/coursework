import java.util.*;

public class Pr0702 {
    public static void main(String[] args) {
		ArrayList<Integer> array = new ArrayList<Integer>();
		for (int i = 0; i < 20; i++)
			array.add(MyLibrary.getRandNum(1, 10));
	
		int n = MyLibrary.getInt("Give me a number between 1 and 10"), count = 0;

		for (int i = 0; i < array.size(); i++)
			if (array.get(i) == n) count++;

		System.out.printf("The number %d was found %d times\n", n, count);


    }
}
