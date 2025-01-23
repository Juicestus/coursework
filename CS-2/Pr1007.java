public class Pr1007 {
    // Mutates the matrix in place, hence matrix parameter
    // not marked as final
    public static <T> void shiftMatrix(T[][] matrix) {
        T last = matrix[matrix.length - 1][matrix[matrix.length - 1].length - 1];
        for (int i = 0; i < matrix.length; i++)
            for (int j = 0; j < matrix[0].length; j++) {       
                final T temp = matrix[i][j];
                matrix[i][j] = last;
                last = temp;
            }
    }
    public static void main(final String[] args)  {
        final Integer[][] mat = new Integer[4][4];
        for (int i = 0; i < mat.length; i++)
            for (int j = 0; j < mat[0].length; j++)
                mat[i][j] = MyLibrary.getRandNum(1, 9);

        System.out.println("Random:");
        System.out.println(MyLibrary.matrixToString(mat));
        shiftMatrix(mat); // Mutated in place
        System.out.println("\nShifted:");
        System.out.println(MyLibrary.matrixToString(mat));
    }
}
