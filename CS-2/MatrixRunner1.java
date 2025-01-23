public class MatrixRunner1 {
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
            {3, 9},
            {5, 16},
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
        for (int row = 0; row < matNums.length; row++) {
            final boolean right = row % 2 == 0;
            for (int col = right ? 0 : matNums[row].length - 1;
                    (right ? col < matNums[row].length : col >= 0) && n-- > 0;
                    col += right ? 1 : -1) 
                sum += matNums[row][col];
        }
        return sum;
    }
} 