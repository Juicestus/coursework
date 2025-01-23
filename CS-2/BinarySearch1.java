public class BinarySearch1 {

    public static void main(final String[] args) {
        final int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        final int key = 5;
        final int result = binarySearch(array, key);
        System.out.println(result);
        System.out.println(array[result]);
        System.out.println(array[result] == key);
    }

    public static int binarySearch(final int[] array, final int key) {
        for (int low = 0, high = array.length - 1; low <= high; ) {
            final int mid = (low + high) / 2;
            if (key < array[mid])
                high = mid - 1;
            else if (key > array[mid])
                low = mid + 1;
            else
                return mid;
        }
        return -1;
    }
}