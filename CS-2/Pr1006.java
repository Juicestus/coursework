public class Pr1006 {
    public static void main(final String[] args) {
        final Integer[][] mat = new Integer[2][3];
        for (int i = 0; i < mat.length; i++)
            for (int j = 0; j < mat[0].length; j++)
                mat[i][j] = MyLibrary.getRandNum(1, 10);

        final int[] columnSums = new int[mat[0].length];
        for (int i = 0; i < mat.length; i++) {
            String output = "";
            for (int j = 0; j < mat[0].length; j++) {
                output += mat[i][j] + " ";
                columnSums[j] += mat[i][j];
            }
            System.out.println(output);
        }

        for (int i = 0; i < columnSums.length; i++)
            System.out.print(columnSums[i] + " ");
        System.out.println();
    } 
}
