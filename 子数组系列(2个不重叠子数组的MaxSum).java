利用 StockSell 2次交易 && 前缀和数组的思想，本题为：子数组系列(最大子数组差)的简化
每个元素 [i] 都可以作为 两端不连续区间的分隔符，设 leftMaxSum[i] 为 {0..i} 这段区间的 maxSubArrSum；rightMaxSum[i] 为 {i...n-1 } 这段区间的 maxSubArrSum
public class Solution {
    /**
     * @param nums: A list of integers
     * @return: An integer denotes the sum of max two non-overlapping subarrays
     */
    public int maxTwoSubArrays(ArrayList<Integer> nums) {
        // write your code
        if (nums.size() == 0) {
        	return 0;
        }

        int length = nums.size();
        //正向遍历寻找 leftMaxSum
        int[] leftMaxSum = new int[length];
        int leftMax = Integer.MIN_VALUE;
        int curSum = 0;
        int preMinSum = 0;

        for (int i = 0; i < length; i++) {
        	curSum += nums.get(i);
        	leftMax = Math.max(leftMax, curSum - preMinSum);
        	preMinSum = Math.min(preMinSum, curSum);

        	leftMaxSum[i] = leftMax;
        }


        //反向遍历寻找 rightMaxSum
        int[] rightMaxSum = new int[length];
        int rightMax = Integer.MIN_VALUE;
        curSum = 0;
        int afterMinSum = 0;

        for (int i = length - 1; i >= 0; i--) {
        	curSum += nums.get(i);
        	rightMax = Math.max(rightMax, curSum - afterMinSum);
        	afterMinSum = Math.min(afterMinSum, curSum);

        	rightMaxSum[i] = rightMax;
        }

        int globalRes = Integer.MIN_VALUE;
        for (int i = 0; i < length - 1; i++) {
        	globalRes = Math.max(globalRes, leftMaxSum[i] + rightMaxSum[i + 1]);
        }
        return globalRes;
    }
}