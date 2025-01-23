import java.util.*;
public class Pr0707 {

	public static boolean isAscending(ArrayList<Integer> list) {
		for (int i = 1; i < list.size(); i++)
			if (list.get(i - 1) > list.get(i)) return false;
		return true;
	}

	public static boolean isDescending(ArrayList<Integer> list) {
		for (int i = 1; i < list.size(); i++)
			if (list.get(i - 1) < list.get(i)) return false;
		return true;
	}

    public static void main(String[] args) {
		int[] array = { 1,2,3,4,5,6,7,8,9,10 };
		//int[] array = { 1,2,3,4,5,6,12,8,9,10 };
		//int[] array = {3, 2, 1};
		ArrayList<Integer> list = new ArrayList<Integer>();
		for (int i = 0; i < array.length; i++) 
			list.add(array[i]);

		if (isAscending(list))
			System.out.println("List is ascending");
		else if (isDescending(list))
			System.out.println("List is descending");
		else
			System.out.println("List is neither");
    }
}
