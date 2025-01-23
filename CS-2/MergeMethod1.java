import java.util.Arrays;

public class MergeMethod1 {

    public static void main(final String[] args) {
        int [] array1 = { 0, 2, 5, 12 , 17 , 19 };
        int [] array2 = {4, 5, 8, 8, 8, 16, 21, 25, 31};
        final int[] result = mergeMethod(array1, array2);
        System.out.println(Arrays.toString(result));
    }

    public static int[] mergeMethod(final int[] array1, final int[] array2) {
        int a = 0, b = 0, c = 0;
        final int[] result = new int[array1.length + array2.length];
        while (a < array1.length && b < array2.length)
            result[c++] = array1[a] < array2[b] ? array1[a++] : array2[b++];
        while (a < array1.length)
            result[c++] = array1[a++];
        while (b < array2.length)
            result[c++] = array2[b++];
        return result;
    }
}