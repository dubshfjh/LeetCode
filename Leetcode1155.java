public class Leetcode1155 {
    class Solution {
        private static final int MOD = 1000000007;

        /**
         * ways[n][k]：在必须选出n个数字时，凑出k这个数字的解法数目，由于第n个数字必须选，所以
         * ways[n][k] = ways[n - 1][k - 1] + ... + ways[n - 1][k - f]，它不能再加上ways[n - 1][k]，因为第n个数字必须选
         * @param d
         * @param f
         * @param target
         * @return
         */
        public int numRollsToTarget(int d, int f, int target) {
            if (d * f < target || 0 >= target) {
                return 0;
            }
            // 前n件物品，凑出重量target的方法数
            int[][] ways = new int[d][target + 1];
            for (int i = 1; i <= f && i <= target; i++) {
                ways[0][i] = 1;
            }
            for (int i = 1; i < d; i++) {
                for (int j = 1; j <= target; j++) {
                    // 由于第i个数字必须选，所以不能用前i-1个数字凑出j
                    // ways[i][j] = ways[i - 1][j] % MOD;
                    if ((1.0 * j / f) <= (i + 1)) {
                        for (int k = 1; k <= f && 0 <= j - k; k++) {
                            ways[i][j] = (ways[i][j] + ways[i - 1][j - k]) % MOD;
                        }
                    }
                }
            }
            return ways[d - 1][target];
        }
    }
}
