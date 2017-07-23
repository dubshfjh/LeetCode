执行2次交易问题的分解：每个 [i] 都可以作为 1 个 两次交易的分隔符，在 {0...i} 区间内 完成first交易；在 {i...n-1}区间内完成second交易
ps：i 只是作为 two transactions 的分隔符，不一定要在 [i] 处卖出!!!
1. 最大利润 : for i = 0 to n - 1：MAX(元素[i]作为分隔符的 左MAX收益 + 右MAX收益)
2. 但是如果为每个 i 完整地执行 1 次 {0...i} 最大收益 & {i+1...n-1} 最大收益，则需要重复地计算 MIN{0...i} & MAX{i...n-1}
3.1 采用"局部打小抄"的思路，for i = 0...n-1：记录 {0...i}这段左侧区间的maxprofitLeft，当已知 {0...i-1}段的结果时，只需要
	像"1次交易"的思路一样，利用preMin 尝试更新 maxprofitLeft[i]，然后尝试更新 preMin
3.2 for i = n-1...0，利用{i+1...n-1}的结果，首先利用 afterMax 尝试更新 maxProfitRight[i]，然后尝试更新 afterMax

4. 整体最大收益： MAX(maxprofitLeft[i] + maxProfitRight[i])

"区分 子数组系列(最大子数组差)"，使得不重叠子数组 A,B 的差 Maximize) 这一问题的解为： Max（leftMinSum[i] - rightMaxSum[i + 1] 

原因：股票可以在第 i 天执行 买入 or 卖出的操作，但是 不重叠的子数组 A，B 中元素 [i] 只能被选择 1 次，
 (

class Solution {
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    public int maxProfit(int[] prices) {
        // write your code here
        if (prices.length <= 1) {
        	return 0;
        }

        int[] maxprofitLeft = new int[prices.length]; //{0...i-1}区间内完成1次交易的最大收益，不一定要在[i]处卖出
        int preMin = prices[0];
        maxprofitLeft[0] = 0;
        for (int i = 1; i < prices.length; i++) {
        	maxprofitLeft[i] = Math.max(maxprofitLeft[i - 1], prices[i] - preMin);
        	preMin = Math.min(preMin, prices[i]);
        }

        int[] maxProfitRight = new int[prices.length];
        int afterMax = prices[prices.length - 1];
        maxProfitRight[prices.length - 1] = 0;
        for (int i = prices.length - 2; i >= 0; i--) { //{i...n-1}区间内完成1次交易的最大收益，不一定要在[i]处卖出
        	maxProfitRight[i] = Math.max(maxProfitRight[i + 1], afterMax - prices[i]);
        	afterMax = Math.max(afterMax, prices[i]);
        }

        int maxProfit = 0;
        for (int i = 0; i < prices.length; i++) {
        	maxProfit = Math.max(maxProfit, maxprofitLeft[i] + maxProfitRight[i]);
        }
        return maxProfit;
    }
};