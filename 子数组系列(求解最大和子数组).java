所有的SubArray问题的本质：利用前缀 Sum or 前缀乘积，将求解最优的 "连续区间{i,i+1....,j}" 来转换为 股票买卖问题中的 求解最优的 "两个端点 i,j "问题
1. 思想：设前缀和数组为 preSum，则 [i] + [i + 1] + ... +[j] = preSum[j] - preSum[i]， 因此 Max{[i] + [i + 1] + ... +[j]} = Max(preSum[j] - preSum[i])
2. 股票买卖问题(1次交易)的最优解 : for i = 0...n - 1，Max{在第 [i] 天卖出股票的最大利益}

踩到的坑：在转换为股票买卖问题后，subArraySum 与 股票Sell 问题有 "细节不同"！！！！！！
1. 股票问题中的maxProfit是0，即当 Max([j] - [i]) < 0时，可以选择 不进行任何交易
	因此，当preSum只有1个元素时，股票问题 (初始化preMin = [0]) 不会进入 for(int i = 1;...)

2. 但是 subarray问题中子数组必须包含 >=1 个元素， 必须执行1次交易，选择处 i,j 两个端点！！
	因此，subarray问题必须初始化 preMin 为 0 这个dummy价格，并且修改 for 循环为 for (int i = 0;...)

3. 必须初始化maxProfit 为 Integer.MIN_VALUE

public class Solution {
    /**
     * @param nums: A list of integers
     * @return: A integer indicate the sum of max subarray
     */
    public int maxSubArray(int[] nums) {
        // write your code
        if (nums.length == 0) {
        	return 0;
        } else {
            int[] preSum = new int[nums.length];
            preSum[0] = nums[0];
            for (int i = 1; i < nums.length; i++) {
            	preSum[i] = preSum[i - 1] + nums[i];
            }
            return helpStockSell(preSum);
        }
    }

    private int helpStockSell(int[] preSum) {
    //  int maxProfit = 0;
    // 	int preMin = preSum[0];
    	int maxProfit = Integer.MIN_VALUE;
        int preMin = 0; //dummy Zero！
    	for (int i = 0; i < preSum.length; i++) {
    		maxProfit = Math.max(maxProfit, preSum[i] - preMin);
    		preMin = Math.min(preMin, preSum[i]);
    	}
    	return maxProfit;
    }
}