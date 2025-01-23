import java.util.*;
public class Pr0710 {
    public static void main(String[] args) {
		ArrayList<Integer> array1 = new ArrayList<Integer>();
		for (int i = 0; i < 10; i++)
			array1.add(MyLibrary.getRandNum(1, 25));

		ArrayList<Integer> array2 = new ArrayList<Integer>();
		for (int i = 0; i < 10; i++)
			array2.add(MyLibrary.getRandNum(1, 25));

		System.out.print("Array 1: ");
		System.out.println(array1);

		System.out.print("Array 2: ");
		System.out.println(array2);

		ArrayList<Integer> merge = new ArrayList<Integer>();

		for (int i = 0; i < array1.size(); i++)
			merge.add(array1.get(i));
		for (int i = 0; i < array2.size(); i++)
			merge.add(array2.get(i));

		for (int x = 0; x < merge.size(); x++)
			for (int i = 0; i < merge.size() - x - 1; i++)
				if (merge.get(i).compareTo(merge.get(i+1)) > 0) {
					int temp = merge.get(i);
					merge.set(i, merge.get(i+1));
					merge.set(i+1, temp);
				}


		System.out.print("Merged: ");
		System.out.println(merge);
    }
}
