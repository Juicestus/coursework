import java.util.*;

public class Pr0701 {
    public static void main(String[] args) {
		ArrayList<Integer> array = new ArrayList<Integer>();
		for (int i = 0; i < 10; i++)
			array.add(MyLibrary.getRandNum(1, 50));
	
		System.out.println(array);

		for (int i = 0, a = 0; i < array.size(); i++)
			if ((a = array.get(i)) % 2 == 0)
				System.out.println(a);


    }
}
