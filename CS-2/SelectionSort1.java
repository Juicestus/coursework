import java.util.Arrays;

public class SelectionSort1 {

    public static void main(final String[] args) {
        final int[] array = {0, 17, 12, 15, 2, 5, 4, 19 , 18, 20, 11, 13};
        System.out.println(Arrays.toString(array));
        selectionSort(array);
        System.out.println(Arrays.toString(array));
    }

    public static void selectionSort(final int[] array) {
        for (int i = 0; i < array.length; i++) {
            int min = i;
            for (int j = i + 1; j < array.length; j++)
                if (array[j] < array[min])
                    min = j;
            final int temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
}