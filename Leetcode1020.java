public class Leetcode1020 {
    static class Solution {
        public int numEnclaves(int[][] A) {
            if (null == A || 0 == A.length || 0 == A[0].length) {
                return 0;
            }
            int rowSize = A.length;
            int colSize = A[0].length;
            int[][] visit = new int[A.length][];
            for (int i = 0; i < rowSize; i++) {
                visit[i] = new int[colSize];
            }
            // 遍历第1行和最后1行
            for (int i = 0; i < colSize; i++) {
                dfsFromOnePoint(A, visit, 0, i);
                dfsFromOnePoint(A, visit, rowSize - 1, i);
            }
            // 遍历第1列和最后1列
            for (int i = 0; i < rowSize; i++) {
                dfsFromOnePoint(A, visit, i, 0);
                dfsFromOnePoint(A, visit, i, colSize - 1);
            }
            // 计算不能从边界访问的"1"的数目
            int enclaveNum = 0;
            for (int i = 1; i < rowSize - 1; i++) {
                for (int j = 1; j < colSize - 1; j++) {
                    if (A[i][j] == 1 && visit[i][j] == 0) {
                        enclaveNum++;
                    }
                }
            }
            return enclaveNum;
        }

        public void dfsFromOnePoint(int[][] A, int[][] visit, int rowId, int colId) {
            if (rowId < 0 || rowId >= A.length || colId <0 || colId >= A[0].length) {
                return;
            }
            if (visit[rowId][colId] == 1 || A[rowId][colId] == 0) {
                return;
            }
            visit[rowId][colId] = 1;
            // 上，下，左，右 4个方向遍历
            dfsFromOnePoint(A, visit, rowId - 1, colId);
            dfsFromOnePoint(A, visit, rowId + 1, colId);
            dfsFromOnePoint(A, visit, rowId, colId - 1);
            dfsFromOnePoint(A, visit, rowId, colId + 1);
        }
    }

    public static void main(String[] args) {
        int[][] A = {{0,0,0,1,1,1,0,1,0,0},{1,1,0,0,0,1,0,1,1,1},{0,0,0,1,1,1,0,1,0,0},{0,1,1,0,0,0,1,0,1,0},{0,1,1,1,1,1,0,0,1,0},{0,0,1,0,1,1,1,1,0,1},{0,1,1,0,0,0,1,1,1,1},{0,0,1,0,0,1,0,1,0,1},{1,0,1,0,1,1,0,0,0,0},{0,0,0,0,1,1,0,0,0,1}};
        Solution solution = new Solution();
        int result = solution.numEnclaves(A);
        System.out.println("result is " + result);
    }
}
