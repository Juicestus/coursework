public class Pr0602 {
    public static void main(String[] args) {
		int[] array = new int[20];
		for (int i = 0; i < array.length; i++)
			array[i] = MyLibrary.getRandNum(1, 20);
		
		int sum = 0;
		for (int i = 0; i < array.length; i++)
			sum += array[i];
	
		System.out.printf("Sum: %d, Avg: %f\n", sum, sum / (0. + array.length));	
    }
}
