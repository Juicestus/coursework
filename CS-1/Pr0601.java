public class Pr0601 {
    public static void main(String[] args) {
		int[] array = new int[20];
		for (int i = 0; i < array.length; i++)
			array[i] = i + 1;
		for (int i = 0; i < array.length; i++)
			System.out.print(array[i] + " ");
		System.out.println();
		for (int i = array.length - 1; i >= 0; i--)
			System.out.print(array[i] + " ");
		System.out.println();
    }
}
