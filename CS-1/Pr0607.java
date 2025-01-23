public class Pr0607 {
	public static void printIntegerArray(int[] array) {
		System.out.print("[");
		for (int i = 0; i < array.length - 1; i++)
			System.out.printf("%d, ", array[i]);
		System.out.printf("%d]\n", array[array.length - 1]);
	}
    public static void main(String[] args) {
		int[] array = new int[15];
		for (int i = 0; i < array.length; i++)
			array[i] = MyLibrary.getRandNum(1, 5);

		printIntegerArray(array);	

		int[] buffer = new int[15];
		int front = 0, back = array.length - 1;
		for (int i = array.length - 1; i >= 0; i--)
			if (array[i] != 3)
				buffer[back--] = array[i];
			else
				buffer[front++] = 3;

		printIntegerArray(buffer);	
    }
}
