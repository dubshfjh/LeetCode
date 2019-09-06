public class Leetcode931 {
    class Solution {
        public int minFallingPathSum(int[][] A) {
            if (null == A || 0 == A.length || 0 == A[0].length) {
                return 0;
            }
            int rowNum = A.length;
            int colNum = A[0].length;
            int[][] minPathSum = new int[2][colNum];
            for (int i = 0; i < colNum; i++) {
                minPathSum[0][i] = A[0][i];
            }
            for (int i = 1; i < rowNum; i++) {
                for (int j = 0; j < colNum; j++) {
                    minPathSum[i % 2][j] = minPathSum[(i - 1) % 2][j] + A[i][j];
                    if (j < colNum - 1) {
                        minPathSum[i % 2][j] = Math.min(minPathSum[i % 2][j], minPathSum[(i - 1) % 2][j + 1] + A[i][j]);
                    }
                    if (j > 0) {
                        minPathSum[i % 2][j] = Math.min(minPathSum[i % 2][j], minPathSum[(i - 1) % 2][j - 1] + A[i][j]);
                    }
                }
            }
            int result = Integer.MAX_VALUE;
            for (int i = 0; i < colNum; i++) {
                result = Math.min(result, minPathSum[(rowNum - 1) % 2][i]);
            }
            return result;
        }
    }
}
