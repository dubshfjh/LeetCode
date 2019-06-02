import java.util.Arrays;

public class Leetcode518 {
    /**
     * 错误解法：combineWays[i] = Sum(combineWays[i - coin[j]])
     * 原因：假设硬币取值为[1,2,5]，那么combineWays[n] != combineWays[n-1] + combineWays[n-2] + combineWays[n-5]
     * 因为 combineWays[n-1] = combineWays[n-2] + combineWays[n-3] + combineWays[n-6]，导致combineWays[n-2]被重复计算了
     * 举例：amount = 7, coins[] = {2, 5}，预期结果是1
     * 按照现在的遍历方式(先遍历amount,再遍历coins)：
         * 1) dp[2] = dp[0]
         * 2)dp[5] = dp[0]
         * 3)dp[7] = dp[2](本轮选择硬币5) + dp[5](本轮选择硬币2) = 2
     * 个人理解：在计算dp[i]的时候，dp[0,1,2...i-1]已经完全算出了结果，设a+b=amount，
     * 则计算dp[amount]时，dp[a]和dp[b]都不再为0，dp[amount] += dp[a]，dp[amount] += dp[b] 将同一组结果计算了2次
    class Solution {
        public int change(int amount, int[] coins) {
            // state: combineWays[i]为凑出i面额的总方法数
            // state transform: combineWays[i] = Sum(combineWays[i - coin[j]]), if i>=coin[j] && 0 != combineWays[i - coin[j]]
            // result: combineWays[amount]
            // initialize: combineWays[0] = 1
            if (0 == amount) {
                return 1;
            }
            if (null == coins || 0 == coins.length) {
                return 0;
            }
            Arrays.sort(coins);
            int[] combineWays = new int[amount + 1];
            combineWays[0] = 1;
            for (int i = 1; i <= amount; i++) {
                for (int j = 0; j < coins.length && coins[j] <= i; j++) {
                    if (0 != combineWays[i - coins[j]]) {
                        combineWays[i] += combineWays[i - coins[j]];
                    }
                }
            }
            return combineWays[amount];
        }
    }
     */

    /**
     * 解法1：先遍历每个硬币，再遍历所有amount
     * 举例：amount = 7, coins[] = {2, 5}，预期结果是1
     * 按照正确的遍历方式(先遍历coins,再遍历amount)：
        1) 遍历硬币2对所有amount的贡献：dp[2] += dp[0], dp[3] += dp[1]，dp[4] += dp[2]，dp[5] += dp[3]，dp[6] += dp[4]，
           dp[7] += dp[5]，但此时dp[5]还是初值0，相当于没累加dp[5]
        2) 遍历硬币5对所有amount的贡献：dp[5] += dp[0]，dp[6] += dp[1]，dp[7] += dp[2]
     * 个人理解：设a + b = amount，a < b，由于dp[amount] = dp[a] 或者 dp[b]，而不是dp[a] + dp[b]，因此要忽略掉其中1个
     * 采用coin面值由小到大遍历的方式：
     * 1) 保证在遍历小面额的硬币a时，执行的dp[amount] += dp[amount - a] = dp[b] = 0，不执行真正的累加操作
     * 2) 而等到遍历大面额的硬币b时，执行的dp[amount] += dp[amount - b] = dp[a]已经有了值，这时仅执行1次真正的累加操作
     */
    class Solution {
        public int change(int amount, int[] coins) {
            if (0 == amount) {
                return 1;
            }
            if (null == coins || 0 == coins.length) {
                return 0;
            }
            Arrays.sort(coins);
            int[] combineWays = new int[amount + 1];
            combineWays[0] = 1;
            for (int i = 0; i < coins.length; i++) {
                for (int j = 1; j <= amount; j++) {
                    if (j >= coins[i]) {
                        combineWays[j] += combineWays[j - coins[i]];
                    }
                }
            }
            return combineWays[amount];
        }
    }


    /**
     * 解法2：为了避免子搜索树重复，换个思想，这是背包问题：
     * backpack[i][j]: 从前i个物品中，拼凑出面额j 的总方法数
     * 在分析backpack[i][0...amount]时，只考虑对物品i选择0,1,2,3,4,5...次，即可避免重复解
     * 1) 物品i选择0次，方法数为backpack[i-1][amount]
     * 2) 物品i选择1,2,3...n次，方法数为backpack[i][amount - coins[i - 1]]，
     *    注意：backpack[i][amount - coins[i - 1]] 已经涵盖了 backpack[i][amount - 2 * coins[i - 1]]，backpack[i][amount - 3 * coins[i - 1]]等所有情况！！！
     * PS：此时先遍历amount，或者先遍历coins，都能得到正确解
     **/
//    class Solution {
//        public int change(int amount, int[] coins) {
//            if (0 == amount) {
//                return 1;
//            }
//            if (null == coins || 0 == coins.length) {
//                return 0;
//            }
//            int[][] backPack = new int[coins.length + 1][amount + 1];
//            for (int i = 1; i <= amount; i++) {
//                backPack[0][i] = 0;
//            }
//            for (int i = 0; i <= coins.length; i++) {
//                // 这样初始化后，backPack[0][0]也等于 1;
//                backPack[i][0] = 1;
//            }
//            for (int i = 1; i <= coins.length; i++) {
//                for (int j = 1; j <= amount; j++) {
//                    // 为了拼凑面额j：第i件物品 选0次
//                    backPack[i][j] = backPack[i - 1][j];
//                    if (j >= coins[i - 1]) {
//                        // 为了拼凑面额j：在前i件物品中，第i件物品 选择1,2...(j/第i枚硬币的面额)次
//                        backPack[i][j] += backPack[i][j - coins[i - 1]];
//                    }
//                }
//            }
//            return backPack[coins.length][amount];
//        }
//    }
}
