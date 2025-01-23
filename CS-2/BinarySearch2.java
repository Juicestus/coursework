public class BinarySearch2 {

    public static void main(final String[] args) {
        final String[] array = {"apple", "banana", "carrot", "egg", "fruit", "grape", "lemon", "lime", "melon", "orange"}; 
        final String key = "fruit";
        final int result = binarySearch(array, key);
        System.out.println(result);
        System.out.println(array[result]);
        System.out.println(array[result] == key);
    }

    public static int binarySearch(final String[] array, final String key) {
        for (int low = 0, high = array.length - 1; low <= high; ) {
            final int mid = (low + high) / 2;
            final int comp = key.compareTo(array[mid]);
            if (comp > 0)
                high = mid - 1;
            else if (comp < 0)
                low = mid + 1;
            else
                return mid;
        }
        return -1;
    }
}