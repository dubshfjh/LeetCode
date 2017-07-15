Subsets 问题(必须使用分支限界法)
1. 当所有元素的 (整体Sum & 1) == 0时，dfs遍历每个subset，如果有一个subset的和 == (整体Sum/2)，则返回true；
2. 当整体Sum为奇数时直接返回false
3. 当subset的和 > (整体sum/2)时，剪枝!!!
public class Solution {
    /**
     * @param nums a non-empty array only positive integers
     * @return return true if can partition or false
     */
    private boolean exist = false;
    public boolean canPartition(int[] nums) {
        // Write your code here
        if (nums.length <= 1) {
        	return nums.length == 0;
        }
        int target = 0;
        for (int num : nums) {
        	target += num;
        }
        if ((target & 1) != 0) { //当元素的总和 为 奇数时，必然得不到 two equal subsets
        	return false;
        } else {
        	target >>= 1;
	        Arrays.sort(nums);
	        helpPartition(nums, 0, 0, target);
	        return exist;
        }
    }

    private void helpPartition(int[] nums, int start, int subsetSum, int target) { //此时的subset 不一定要unique！
    	if (exist || subsetSum > target) { //必须剪枝，否则会超时
    		return;
    	} else if (start > 0 && subsetSum == target) { //本层递归需要分析的开始元素就是 [start], 但是为了避免target==0时： 还没开始分析任何元素(即start==0，因为每一层递归必然选择1个元素，只有第1层递归中start==0)时，就认为得到了target地情况，于是将 sum==target && start > 0 作为判断条件
    	    exist = true;
    		return;
    	} else {
    		for (int i = start; i < nums.length; i++) {
	    		if (i > start && nums[i] == nums[i - 1]) {
	    			continue;
	    		}
	    		helpPartition(nums, i + 1, subsetSum + nums[i], target);
	    	}
    	}
    }
}