import java.util.*;

public class Pr0705 {
    public static void main(String[] args) {
		ArrayList<Integer> array = new ArrayList<Integer>();
		for (int i = 0; i < 10; i++)
			array.add(MyLibrary.getRandNum(1, 50));
		System.out.println(array);
		int biggest = array.get(0);
		for (int a = 0, i = 1; i < array.size(); i++)
			if ((a = array.get(i)) > biggest)
				biggest = a;
		System.out.println(biggest);
    }
}
