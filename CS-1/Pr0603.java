public class Pr0603 {

	public static void printIntegerArray(int[] array) {
		System.out.print("[");
		for (int i = 0; i < array.length - 1; i++)
			System.out.printf("%d, ", array[i]);
		System.out.printf("%d]\n", array[array.length - 1]);
	}
 
    public static void main(String[] args) {
		int[] array = new int[20];
		for (int i = 0; i < array.length; i++)
			array[i] = MyLibrary.getRandNum(1, 8);
	
		printIntegerArray(array);
	
		int fives = 0;	
		for (int i = 0; i < array.length; i++)
			if (array[i] == 5) {
				array[i] = 0;
				fives++;
			}

		System.out.printf("Fives: %d\n", fives);

		printIntegerArray(array);
    }
}
