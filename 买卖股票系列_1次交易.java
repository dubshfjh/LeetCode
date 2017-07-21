将大问题分解为小问题：
1. 只能进行1次交易的最大收益为 for i = 0 to n-1 : MAX(第i天卖出得到的收益) 
2. 第i天卖出得到的收益 = prices[i] - MIN(prices[0...i-1])
public class Solution {
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    public int maxProfit(int[] prices) {
        // write your code here
        if (prices.length == 0) {
        	return 0;
        }
        int preMinprice = prices[0];
        int maxProfit = 0;
        for (int i = 1; i < prices.length; i++) { //如果只有第0天，则最大收益就是初值0
        	maxProfit = Math.max(maxProfit, prices[i] - preMinprice);
        	preMinprice = Math.min(preMinprice, prices[i]);
        }
        return maxProfit;
    }
}