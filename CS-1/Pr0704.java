import java.util.*;

public class Pr0704 {
    public static void main(String[] args) {
		ArrayList<Integer> array = new ArrayList<Integer>();
		for (int i = 0; i < 10; i++)
			array.add(MyLibrary.getRandNum(1, 50));
		int sum = 0;	
		for (int i = 0; i < array.size(); i++)
			sum += array.get(i);
		System.out.println(sum);
    }
}
