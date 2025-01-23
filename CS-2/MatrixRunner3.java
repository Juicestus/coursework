public class MatrixRunner3 {
    public static void main(final String[] args)
    {
        final int[][] matNums = new int[][]
        {
            {0, 6, 3, 7},
            {4, 5, 9, 0},
            {-2, 15, 1, 2}
        };

        final int[][] testCases = new int[][] 
        {
            {3, 2},
            {6, 28},
            {1, 0}
        };

        for (final int[] testCase : testCases) {
            final int result = sumCount(matNums, testCase[0]);
            final boolean passed = result == testCase[1];
            System.out.printf("f(%d) = %d %s %d [%s]\n", 
                    testCase[0], result, passed ? "==" : "!=", testCase[1], passed ? "PASS" : "FAIL");
        }
    }    

    public static int sumCount(final int[][] matNums, int n) {
        int sum = 0;
        for (int col = 0; col < matNums[0].length; col++) {
            final boolean down = col % 2 == 0;
            for (int row = down ? 0 : matNums.length - 1;
                    (down ? row < matNums.length : row >= 0) && n-- > 0;
                    row += down ? 1 : -1) 
                sum += matNums[row][col];
        }
        return sum;
    }
} 