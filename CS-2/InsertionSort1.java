import java.util.Arrays;

public class InsertionSort1 {

    public static void main(final String[] args) {
        final int[] array = {0, 17, 12, 15, 2, 5, 4, 19 , 18, 20, 11, 13};
        System.out.println(Arrays.toString(array));
        insertionSort(array);
        System.out.println(Arrays.toString(array));
    }

    public static void insertionSort(final int[] array) {
        for (int i = 1; i < array.length; i++) {
            if (array[i] < array[i - 1]) {
                final int temp = array[i];
                int j = i;
                for (; j > 0 && array[j - 1] > temp; j--)
                    array[j] = array[j - 1];
                array[j] = temp;
            }
        }
    }
}