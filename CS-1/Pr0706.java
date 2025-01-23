import java.util.*;

public class Pr0706 {
    public static void main(String[] args) {
		ArrayList<String> array = new ArrayList<String>();
		for (int i = 0; i < 10; i++) {
			String word = "";
			int len =  MyLibrary.getRandNum(3, 10);
			for (int j = 0; j < len; j++)
				word += (char)MyLibrary.getRandNum('a', 'z');
			array.add(word);

		}
		System.out.println(array);
		String biggest = array.get(0);
		String shortest = array.get(0);
		for (int i = 1; i < array.size(); i++) {
			String a = array.get(i);
			if (a.length() > biggest.length())
				biggest = a;
			if (a.length() < shortest.length())
				shortest = a;
		}
		System.out.println(biggest);
		System.out.println(shortest);
    }
}
