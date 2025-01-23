import java.lang.reflect.Array;

public class Pr1008 {
    public static <T> T[][] rotateMatrix(final T[][] matrix) {
        // The following will not compile because we don't know the size of T
        //final T[][] rotated = new T[matrix[0].length][matrix.length];
        // So we use this work around so it compiles
        // final T[][] rotated = (T[][]) new Object[matrix[0].length][matrix.length];
        // But this errors at runtime so we use this work around
        final T[][] rotated = (T[][]) Array.newInstance(matrix[0][0].getClass(), matrix[matrix.length - 1].length, matrix.length);
        // All this to use generics 😈😈😈

        for (int i = 0; i < matrix.length; i++)
            for (int j = 0; j < matrix[0].length; j++)
                rotated[j][i] = matrix[i][j];

        return rotated;
    }

    public static void main(final String[] args) {
        final int n = 4;
        final int m = 2;

        final Character[][] mat = new Character[n][m];
        for (int i = 0; i < mat.length; i++)
            for (int j = 0; j < mat[0].length; j++)
                mat[i][j] = (char) (MyLibrary.getRandNum('A', 'Z'));

        System.out.println("Random:");
        System.out.println(MyLibrary.matrixToString(mat));
        final Character[][] rotated = rotateMatrix(mat);
        System.out.println("\nRotated:");
        System.out.println(MyLibrary.matrixToString(rotated));
    }
}
