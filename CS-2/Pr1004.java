public class Pr1004 {
    public static void main(final String[] args) {
        final Integer[][] mat = new Integer[5][5];
        for (int i = 0; i < mat.length; i++)
            for (int j = 0; j < mat[0].length; j++)
                mat[i][j] = MyLibrary.getRandNum(2, 26);
        double sum = 0;
        for (int i = 0; i < mat.length; i++)
            for (int j = 0; j < mat[0].length; j++) 
                sum += mat[i][j];
        final double avg = sum / (mat[0].length * mat.length);
        System.out.printf("Sum: %f, Avg: %f\n", sum, avg);
    }

}