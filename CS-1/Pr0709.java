import java.util.*;
public class Pr0709 {
    public static void main(String[] args) {
		ArrayList<Integer> array = new ArrayList<Integer>();

		for (int i = 0; i < 10; i++)
			array.add(MyLibrary.getRandNum(1, 10));

		System.out.println(array);

		int forRemoval = MyLibrary.getInt("What number should I remove?");

		for (int i = 0; i < array.size(); i++)
			if (array.get(i) == forRemoval)
				array.remove(i--);

		System.out.println(array);
    }
}
