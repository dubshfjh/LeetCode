import java.util.Arrays;

public class Leetcode322 {
    class Solution {
        public int coinChange(int[] coins, int amount) {
            if (0 == amount || null == coins || 0 == coins.length) {
                return 0;
            }
            Arrays.sort(coins);
            // state: leastCoin[i] 为凑齐i面额的最少硬币数
            // state transform: leastCoin[i] = 1 + min(leastCoin[i - coin[j]]), if (i >= coin[j]) && 初始值 != leastCoin[i - coin[j]]
            // result: leastCoin[amount]
            // initialize: leastCoin[0] = 0
            int[] leastCoin = new int[amount + 1];
            Arrays.fill(leastCoin, Integer.MAX_VALUE);
            leastCoin[0] = 0;
            for (int i = 1; i <= amount; i++) {
                for (int j = 0; j < coins.length && coins[j] <= i; j++) {
                    if (Integer.MAX_VALUE != leastCoin[i - coins[j]]) {
                        leastCoin[i] = Math.min(leastCoin[i], 1 + leastCoin[i - coins[j]]);
                    }
                }
            }
            return Integer.MAX_VALUE == leastCoin[amount] ? -1 : leastCoin[amount];
        }
    }
}
