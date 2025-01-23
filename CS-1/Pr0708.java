import java.util.*;
public class Pr0708 {

    public static void main(String[] args) {
		int[] array = { 1,2,3,5,6,9,10,12,11,8,7,6};

		ArrayList<Integer> list = new ArrayList<Integer>();
		for (int i = 0; i < array.length; i++) 
			list.add(array[i]);

		boolean hasPeaked = false;
		for (int i = 2; i < list.size(); i++)
			if (list.get(i - 2) < list.get(i - 1) 
					&& list.get(i - 1) > list.get(i)) 
				if (!hasPeaked)
					hasPeaked = true;
				else {
					System.out.println("Not a mountain");
					return;
				}
				
		if (hasPeaked)
			System.out.println("Is a mountain");
		else
			System.out.println("Not a mountain");
	}
}
