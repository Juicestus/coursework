public class Pr1003 {
    public static void main(final String[] args) { 
        // Am using the class so I can use my generic method
        final Integer[][] mat = new Integer[5][5];
        for (int i = 0; i < mat.length; i++)
            for (int j = 0; j < mat[0].length; j++)
                mat[i][j] = MyLibrary.getRandNum(2, 26);
        System.out.println(MyLibrary.<Integer>matrixToString(mat));
        for (int i = 0; i < mat.length; i++)
            for (int j = 0; j < mat[0].length; j++) 
                if (mat[i][j] % 2 == 0) mat[i][j] = 0;
        System.out.println(MyLibrary.<Integer>matrixToString(mat));
    }
}
