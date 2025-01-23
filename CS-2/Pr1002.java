public class Pr1002 {
    public static void main(final String[] args) {
        final int size = MyLibrary.getInt("Enter number of rows and columns:");
        final int[][] mat = new int[size][size];

        for (int i = 0; i < mat.length; i++)
            for (int j = 0; j < mat[0].length; j++)
                if (i + j == size - 1) mat[i][j] = 1;

        for (int i = 0; i < mat.length; i++) {
            for (int j = 0; j < mat[0].length; j++)
                System.out.print(mat[i][j] + " ");
            System.out.println();
        }
    }
}
