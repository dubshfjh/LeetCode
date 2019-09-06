class Solution {
    public int rob(int[] nums) {
        if (null == nums || 0 == nums.length) {
            return 0;
        }
        // localProfit[i]：必然以nums[i - 1]结尾时，最大的局部利润
        int[] localProfit = new int[nums.length + 1];
        int[] globalProfit = new int[nums.length + 1];
        localProfit[0] = globalProfit[0] = 0;
        localProfit[1] = globalProfit[1] = nums[0];
        for (int i = 2; i <= nums.length; i++) {
            localProfit[i] = globalProfit[i - 2] + nums[i - 1];
            globalProfit[i] = Math.max(globalProfit[i - 1], localProfit[i]);
        }
        return globalProfit[nums.length];
    }
}