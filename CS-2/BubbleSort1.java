import java.util.Arrays;

public class BubbleSort1 {

    public static void main(final String[] args) {
        final int[] array = {0, 17, 12, 15, 2, 5, 4, 19 , 18, 20, 11, 13};
        System.out.println(Arrays.toString(array));
        bubbleSort(array);
        System.out.println(Arrays.toString(array));
    }

    public static void bubbleSort(final int[] array) {
        boolean sorted = false;
        for (int i = 0; i < array.length - 1 && !sorted; i++) {
            sorted = true;
            for (int j = 0; j < array.length - i - 1; j++)
                if (array[j] > array[j + 1]) {
                    final int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    sorted = false;
                }
        }
    }
}