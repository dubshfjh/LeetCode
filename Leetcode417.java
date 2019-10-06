import org.omg.CORBA.MARSHAL;

import java.util.*;

public class Leetcode417 {
    Solution solution = new Solution();

    class Solution {
        private final int[][] direction = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        /**
         * 采用记忆化搜索的思想
         * @param matrix
         * @return
         */
        public List<List<Integer>> pacificAtlantic(int[][] matrix) {
            List<List<Integer>> result = new ArrayList<>();
            if (null == matrix || 0 == matrix.length || null == matrix[0] || 0 == matrix[0].length) {
                return result;
            }
            boolean[][] reachPacific = new boolean[matrix.length][matrix[0].length];
            boolean[][] reachAtlantic = new boolean[matrix.length][matrix[0].length];
            for (int i = 0; i < matrix.length; i++) {
                // 只从能够到达1个大洋的Point，开始记忆化搜索，本次搜索中每个经过的节点，只要满足高度要求，全部都设置为“能达到1个大洋”
                traverseOnMatrix(matrix, reachPacific, i, 0, Integer.MIN_VALUE);
                traverseOnMatrix(matrix, reachAtlantic, i, matrix[0].length - 1, Integer.MIN_VALUE);
            }

            for (int i = 0; i < matrix[0].length; i++) {
                traverseOnMatrix(matrix, reachPacific, 0, i, Integer.MIN_VALUE);
                traverseOnMatrix(matrix, reachAtlantic, matrix.length - 1, i, Integer.MIN_VALUE);
            }

            for (int i = 0; i < matrix.length; i++) {
                for (int j = 0; j < matrix[0].length; j++) {
                    if (reachAtlantic[i][j] && reachPacific[i][j]) {
                        result.add(Arrays.asList(i, j));
                    }
                }
            }
            return result;
        }

        /**
         * 1.在上下左右的递归搜索中，必须避免“搜索出1个环来”，否则就死循环到Stack OverFlow了，
         * 2. 在设置全局的visit[i][j]为true时，必须保证它就是最终的解了！
         * 所以，使用1个dp[i][j]承载“到达pacific”，“到达Atlantic”两种语义，就很难做到以上2点
         * @param matrix
         * @param reachOneOcean
         * @param i
         * @param j
         * @return
         */
        private void traverseOnMatrix(int[][] matrix, boolean[][] reachOneOcean, int i, int j, int lastHeight) {
            if (i < 0 || i >= matrix.length || j < 0 || j >= matrix[0].length
                    || matrix[i][j] < lastHeight) {
                return;
            }
            // 当[i][j]已被计算过，而且能到达当前大洋时，不应该再次计算当前节点
            // PS：由于搜索的出发点，都是“必然能达到1个大洋”的边缘节点，所以整条搜索路径上计算过的点，reachOneOcean[i][j]都为true
            if (reachOneOcean[i][j]) {
                return;
            }
            reachOneOcean[i][j] = true;
            for (int[] oneDirect : direction) {
                traverseOnMatrix(matrix, reachOneOcean, i + oneDirect[0], j + oneDirect[1], matrix[i][j]);
            }
        }
    }

    public static void main(String[] args) {
        int[][] matrix = {{3,3,3,3,3,3},{3,0,3,3,0,3},{3,3,3,3,3,3}};
        Leetcode417 leetcode417 = new Leetcode417();
        List<List<Integer>> result = leetcode417.solution.pacificAtlantic(matrix);
        return;
    }
}
