class Solution {
    /**
     * 当房子连成1个圆圈时，nums[0]和nums[n - 1]必然不能并存，因此只需要分割成2段
     * Max(maxProfit(nums[0]...nums[n-2]), maxProfit(nums[1]...nums[n-1]))
     * @param nums
     * @return
     */
    public int rob(int[] nums) {
        if (null == nums || 0 == nums.length) {
            return 0;
        }
        if (1 == nums.length) {
            return nums[0];
        }
        int[] globalProfit = new int[nums.length + 1];
        globalProfit[0] = 0;
        globalProfit[1] = nums[0];
        int maxProfit = globalProfit[1];
        // 因为下方是从globalProfit[2]开始计算，所以必须在循环之前就考虑globalProfit[1]
        for (int i = 2; i <= nums.length - 1; i++) {
            // maxProfit(nums[0]...nums[n-2])
            globalProfit[i] = Math.max(globalProfit[i - 1], globalProfit[i - 2] + nums[i - 1]);
            maxProfit = Math.max(maxProfit, globalProfit[i]);
        }
        globalProfit[0] = globalProfit[1] = 0;
        globalProfit[2] = nums[1];
        // 因为下方是从globalProfit[3]开始计算，所以必须在循环之前就考虑globalProfit[2]
        maxProfit = Math.max(maxProfit, globalProfit[2]);
        for (int i = 3; i <= nums.length; i++) {
            // maxProfit(nums[1]...nums[n-1]))，此时每个glbalProfit[i]与 nums[0...n-2]场景下的glbalProfit[i]不相同！
            globalProfit[i] = Math.max(globalProfit[i - 1], globalProfit[i - 2] + nums[i - 1]);
            maxProfit = Math.max(maxProfit, globalProfit[i]);
        }
        return maxProfit;
    }
}