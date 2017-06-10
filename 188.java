 这种题目就是纯粹的01背包问题
    dp[t][i]代表前i天中,背包容量为t(交易次数<=t)时的maxProfit。选择1：不在第i天卖出，将所有的容量t都交付给dp[i-1]：dp[i-1][t] (注意：别写成错误的dp[i][t-1]！！！)
    选择2：在第i+1天卖出，但此时不能直接加上第i天的价格，因为我们肯定需要在第0...i-1天中选择某个第j天卖出，于是前i天的最大利润为：max(dp[t-1][j] - prices[j]) + prices[i]  for j = 0 to i-1 ；


public class Solution {
    public int maxProfit(int k, int[] prices) {
        int n = prices.length;
        if(n == 0 || k <= 0){
            return 0;
        }
        if(k >= n/2){//此时可进行的交易次数k >= max(递增区间个数)
            return NoBetterProfit(prices);
        }

        int[][] dp = new int[k + 1][n];
        //由于dp[t][i] 依赖于 使得dp[t-1][j]-prices[j] 最大化的j。为了避免对每个i都分析0...i-1，只需要使用一个变量tempMax记录到i之前的 
        //max{dp[t-1][j] - prices[j]} j=0...i-1，然后基于dp[t][i-1]和tempMax得到dp[t][i]
        for(int t = 1; t <= k; t++) {
            int tempMax = dp[t][0] - prices[0];
            for(int i = 1; i < n; i++) {//t的循环必须在外侧，此时的dp[t][i-1]必须是前第i-1天进行t次交易的整体最优解
                dp[t][i] = Math.max(dp[t][i-1], tempMax + prices[i]);
                tempMax = Math.max(tempMax, dp[t-1][i] - prices[i]);
                //tempMax = Math.max(tempMax, dp[t][i]-prices[i]); 注意是tempMax = {dp[t-1][j]-prices[j]}，它代表：在前i-1天进行了t-1次交易后，选择在第i天买入后的maxprofit。
                //所以计算完dp[t][i]后，是根据dp[t-1][i] 来尝试更新tempMax，而不是根据(dp[t][i]-prices[i])来计算 在前i天执行了t次交易后，选择在第i天买入的maxprofit
            }
        }
        
        return dp[k][n-1];
    }
    
    
    int NoBetterProfit(int[] prices){
        int bestprofit = 0;
        for(int i = 1; i < prices.length; i++){//因为此时k次交易一定能覆盖所有递增区间，所以只需要将每个元素之间的positive价格差累加即可
            if(prices[i] > prices[i-1]){// as long as there is a price gap, we gain a profit.
                bestprofit += (prices[i] - prices[i-1]);//ps:这并不代表一定从[i-1]买入,[i]卖出。我们会主动选择在 每个递增区间的左侧min买入，右侧max卖出
            }
        }
        return bestprofit;
    }
}