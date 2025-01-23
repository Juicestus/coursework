public class Pr1005 {
    public static void main(final String[] args) {
        final Integer[][] mat = new Integer[2][3];
        for (int i = 0; i < mat.length; i++)
            for (int j = 0; j < mat[0].length; j++)
                mat[i][j] = MyLibrary.getRandNum(1, 10);

        for (int i = 0; i < mat.length; i++) {
            double sum = 0;
            String output = "";
            for (int j = 0; j < mat[0].length; j++) {
                sum += mat[i][j];
                output += mat[i][j] + " ";
            }
            System.out.print(output);
            System.out.printf("Sum: %f\n", sum);
        }
    } 
}
