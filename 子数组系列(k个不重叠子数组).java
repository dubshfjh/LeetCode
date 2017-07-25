思路跑偏了！
/*
子数组{i + 1, i + 2 ... j}  等价于  preSum[j] - preSum[i]，其中preSum为前缀和数组，preSum[i] = [0] + ... + [i]
因此 k 个不重叠子数组 的MaxSum问题  等价于  StockSell问题中，恰好执行 k 次交易 的 MaxProfit问题
任意子数组[i + 1...j]的Sum  等价于  StockSell问题中 price[j] - price[i]的Profit 
public class Solution {

    public int maxSubArray(int[] nums, int k) {
        // write your code here
        if (nums.length == 0 || k == 0) {
        	return 0;
        }
        int length = nums.length;
        int[] preSum = new int[];
        preSum[0] = nums[0];
        for (int i = 1; i < length; i++) {
        	preSum[i] = preSum[i - 1] + nums[i];
        }
        return helpStockSell(preSum, k, length);
    }

    private int helpStockSell(int[] preSum, int k, int length) {
    	int[][] maxProfit = new int[length][k + 1];
    	maxProfit[0][0] = preSum[0];
    	for (int i = 1; i <= k; i++) {
    		maxProfit[0][i] = Integer.MIN_VALUE;
    	}
    	for (int i = 1; i < length; i++) {
    		maxProfit[i][0] = 0;
    	}

    	for (int day = 1; day < length; day++) {
    		for (int num = 1; num <= k; num++) {
    			maxProfit[day][num] = maxProfit[day - 1][num];
    			int tempMax = Integer.MIN_VALUE;
    			for (int preday  = 0; preday < day; preday++) {
    				tempMax = Math.max(tempMax, maxProfit[preday][num - 1] - preSum[preday]);
    			}
    			maxProfit[day][num] = Math.max(maxProfit[day][num], tempMax);
    		}
    	}
    	return maxProfit[length - 1][k];
    }
}
*/


划分类DP问题，设置 全局最优解 & 局部最优解 两个DP数组
local[num][day]：在第day天时，执行num次交易(即选择num个子数组) 的局部最优解
global[num][day]：前day天执行num次交易的全局最优解(不一定要在第i天交易)

踩到的坑：
1.local[num][day] = Math.max(nums[day - 1] + local[num][day - 1], nums[day - 1] + global[num - 1][day - 1]); 
  逻辑错误，由于local[0][1] = MIN, 当nums[0] = -1 时, nums[0] + local[1][0] = -1 + MIN = MAX，
  而nums[0] + glocal[1][0] = -1 + 0 = -1，于是 global[1][1] = MAX
2. 正确逻辑：local[num][day] = nums[day - 1] + Math.max(local[num][day - 1], global[num - 1][day - 1]);
public class Solution {
    /**
     * @param nums: A list of integers
     * @param k: An integer denote to find k non-overlapping subarrays
     * @return: An integer denote the sum of max k non-overlapping subarrays
     */
    public int maxSubArray(int[] nums, int k) {
        // write your code here
        if (nums.length < k) {
        	return 0;
        }
        int length = nums.length;
        int[][] local = new int[k + 1][length + 1]; //dummy
        int[][] global = new int[k + 1][length + 1];

        local[0][0] = 0;
        for (int num = 1; num <= k; num++) {
        	local[num][num - 1] = Integer.MIN_VALUE; //在 num - 1 天之前执行 num 次交易不合法
        	//换句话说：长度<= num - 1 的数组，不能够分割为 num 个subArray
        	for (int day = num; day <= length; day++) {
        // 		local[num][day] = Math.max(nums[day - 1] + local[num][day - 1], nums[day - 1] + global[num - 1][day - 1]); 逻辑错误，由于local[0][1] = MIN, 当nums[0] = -1 时,
        // nums[0] + local[1][0] = -1 + MIN = MAX，而nums[0] + glocal[1][0] = -1 + 0 = -1，
        // 于是 global[1][1] = MAX
                local[num][day] = nums[day - 1] + Math.max(local[num][day - 1], global[num - 1][day - 1]);
        	   // System.out.println(num+",,"+day+",,"+local[num][day]);
        		//到第day天的局部最优解必须 选择 [day - 1]：
        		//1. 第day - 1天也是分割点：第 day 天的价值 + 在第 day - 1 天分割为 num - 1 个子数组的局部最优解，只需要把last子数组的右边界包含 [day - 1]
        		//2. 第day - 1天并不是分割点：第 day 天的价值 + (在前 day - 1 天 的全局最优解)
        		
        		if (day == num) { //此时必须将 前 day 个元素 分割为 num 个子数组，因此必须在第 day 天执行交易
        			global[num][day] = local[num][day];
        		} else { //此时 第day天 不一定需要交易
        			global[num][day] = Math.max(global[num][day - 1], local[num][day]);
        		}
        	}
        }
        return global[k][length];
    }
}
