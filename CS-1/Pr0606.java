public class Pr0606 {
	public static void printIntegerArray(int[] array) {
		System.out.print("[");
		for (int i = 0; i < array.length - 1; i++)
			System.out.printf("%d, ", array[i]);
		System.out.printf("%d]\n", array[array.length - 1]);
	}
    public static void main(String[] args) {
		int[] array = new int[10];
		for (int i = 0; i < array.length; i++)
			array[i] = MyLibrary.getRandNum(1, 16);

		printIntegerArray(array);	
		
		while (true) {
			boolean sorted = true;
			for (int i = 1; i < array.length; i++)
				if (array[i - 1] > array[i]) {
					sorted = false;
					int swap = array[i];
					array[i] = array[i - 1];
					array[i - 1] = swap;
				}
			if (sorted) break;
		}

		printIntegerArray(array);	
    }
}
