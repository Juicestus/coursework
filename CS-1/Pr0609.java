public class Pr0609 {
	public static void printIntegerArray(int[] array) {
		System.out.print("[");
		for (int i = 0; i < array.length - 1; i++)
			System.out.printf("%d, ", array[i]);
		System.out.printf("%d]\n", array[array.length - 1]);
	}

	public static int[] generateRandomIntegerArray(int len, int min, int max) {
		int[] array = new int[len];
		for (int i = 0; i < array.length; i++)
			array[i] = MyLibrary.getRandNum(min, max);	
		return array;
	}

	public static int[] bubbleSortIntegerArray(int[] array) {
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
		return array;
	}

    public static void main(String[] args) {
		
		int[] array1 = bubbleSortIntegerArray(generateRandomIntegerArray(10, 1, 16));
		int[] array2 = bubbleSortIntegerArray(generateRandomIntegerArray(10, 1, 16));

		System.out.printf("Array 1: ");
		printIntegerArray(array1);	
		System.out.printf("Array 1: ");
		printIntegerArray(array2);	

		// Assumes array1 and array2 are of the same length

		int[] merge = new int[array1.length + array2.length];
		int indexMerge = 0, index1 = 0, index2 = 0;
		while (indexMerge < merge.length) {
			if (array1[index1] < array2[index2]) {
				merge[indexMerge++] = array1[index1++];
				merge[indexMerge++] = array2[index2++];
			} else {
				merge[indexMerge++] = array2[index2++];
				merge[indexMerge++] = array1[index1++];
			}
		}
		
		System.out.printf("Merged: ");
		printIntegerArray(merge);	
    }
}
