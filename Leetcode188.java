public class Leetcode188 {
    class Solution {
        /**
         * 采用全局DP思想，时间复杂度为n^2 * k，可以进一步优化！！！
         * 采用相同的状态方程，但先遍历“交易次数”，再遍历“天数”，从而将z=1...i-1的 遍历过程融入到“每个交易次数j”在遍历“每个交易天数i”的过程中
         * PS：必须先额外计算“交易次数 * 2 >= 总天数”的情况，避免OOM
         * 1.state: globolMaxProfit[i][j]: 前i天内最多执行j次交易的最大利润，不管第i天是否完成交易
         * 2.state transfer:  globolMaxProfit[i][j] =
         * 2.1 第i天不完成交易，globalMaxProfit[i - 1][j]
         * 2.2 第i天完成交易，即第i天必须卖出股票，设z = 1...i - 1，
         * 则可以在第x天完成第j-1次交易，然后在第 z,z+1...i-1 天中选1天买入股票，然后在第i天卖出
         * Max(globalMaxProfit[z][j - 1] + Max(price[i] - price[z,z+1...i-1]))
         * 2.3 转换下2.2的方程，比较下 z,z+1的场景: globalMaxProfit[z][j - 1] <= globalMaxProfit[z + 1][j - 1]
         * 因此如果第z天想共享最优解，那么它的 Max(price[i] - price[z,z+1...i-1]) 必须>= Max(price[i] - price[z+1,z+2...i-1])
         * 而z,z+1的场景下，Max(price[i] - price[z,z+1...i-1])) 的唯一区别，在于z的场景下可以多1个取值 price[i] - price[z]
         * 结论：第z天可能贡献最优解的方式，只有globalMaxProfit[z][j - 1] + price[i] - price[z]
         * 3.initialize: globalMaxProfit[0][0...k] = 0, globalMaxProfit[0...i][0] = 0
         * 4.result: globalMaxProfit[n][k]
         *
         * @param k
         * @param prices
         * @return
         */
//        public int maxProfit(int k, int[] prices) {
//            if (null == prices || 1 >= prices.length || k == 0) {
//                return 0;
//            }
//            if (k >= prices.length / 2) {
//                return quickCalculate(prices);
//            }
//            int[][] globalMaxProfit = new int[prices.length + 1][k + 1];
//            for (int i = 0; i <= prices.length; i++) {
//                globalMaxProfit[i][0] = 0;
//            }
//            for (int i = 0; i <= k; i++) {
//                globalMaxProfit[0][i] = 0;
//            }
//            for (int i = 1; i <= prices.length; i++) {
//                for (int j = 1; j <= k; j++) {
//                    globalMaxProfit[i][j] = globalMaxProfit[i - 1][j];
//                    for (int z = 1; z <= i - 1; z++) {
//                        int candidateMaxProfit = globalMaxProfit[z][j - 1] + prices[i - 1] - prices[z - 1];
//                        globalMaxProfit[i][j] = Math.max(globalMaxProfit[i][j], candidateMaxProfit);
//                    }
//                }
//            }
//            return globalMaxProfit[prices.length][k];
//        }
        private int quickCalculate(int[] prices) {
            int len = prices.length;
            int profitWithInfiniteTrade = 0;
            for (int i = 1; i < len; i++) {
                // as long as there is a price gap, we gain a profit.
                if (prices[i] > prices[i - 1]) {
                    profitWithInfiniteTrade += prices[i] - prices[i - 1];
                }
            }
            return profitWithInfiniteTrade;
        }

        /**
         * 先遍历“交易次数j”，再遍历“交易天数i”，将z=[1,2...i-1]的遍历过程，融合到“交易天数i”的遍历过程中
         * dp[i][j] = max(dp[i - 1][j], price[j - 1] + max(dp[z][j - 1] - price[z - 1]))
         * @param k
         * @param prices
         * @return
         */
        public int maxProfit(int k, int[] prices) {
            if (null == prices || 1 >= prices.length || k == 0) {
                return 0;
            }
            if (k >= prices.length / 2) {
                return quickCalculate(prices);
            }
            int[][] globalMaxProfit = new int[prices.length + 1][k + 1];
            for (int i = 0; i <= prices.length; i++) {
                globalMaxProfit[i][0] = 0;
            }
            for (int i = 0; i <= k; i++) {
                globalMaxProfit[0][i] = 0;
            }
            for (int j = 1; j <= k; j++) {
                int maxDpZMinusPrice = -prices[0];
                // 错误代码：i = 1开始遍历，并将maxDpZMinusPrice初始化为0，这会导致第0天的交易完成后，maxDpZMinusPrice = 0，而不是-prices[0]
                for (int i = 2; i <= prices.length; i++) {
                    // 此时的i-1相当于之前的z
                    globalMaxProfit[i][j] = Math.max(globalMaxProfit[i - 1][j],
                            prices[i - 1] + maxDpZMinusPrice);

                    maxDpZMinusPrice = Math.max(maxDpZMinusPrice, globalMaxProfit[i - 1][j - 1] - prices[i - 1]);
                }
            }
            return globalMaxProfit[prices.length][k];
        }
    }
}
