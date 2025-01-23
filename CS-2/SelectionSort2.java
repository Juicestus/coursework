import java.util.Arrays;

public class SelectionSort2 {

    public static void main(final String[] args) {
        final String[] array = {"dog", "cat", "bird", "Hippo", "rat", "java", "Bedrock", "Console", "Nether"};
        System.out.println(Arrays.toString(array));
        selectionSort(array);
        System.out.println(Arrays.toString(array));
    }

    public static void selectionSort(final String[] array) {
        for (int i = 0; i < array.length; i++) {
            int min = i;
            for (int j = i + 1; j < array.length; j++)
                if (array[j].compareToIgnoreCase(array[min]) < 0)
                    min = j;
            final String temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
}