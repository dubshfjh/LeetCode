所有的 Major Element 都是基于"抵消"的思想，如果主元素为出现次数 > 1/k 的元素，那么如果遵循原则：维护1个包含"k个不同元素"的候选者序列
1. 如果当前元素 属于 old候选者，则增加该候选者出现次数
2. 如果当前元素未出现过 && 候选者序列.size < k，则该元素为新的候选者
3. 如果候选序列 已经 溢出，则当前元素 负责抵消 所有候选者序列元素 的 1 次出现，当 old 候选者出现次数 被抵消到 0 时，则从序列中移除它
public class Solution {
    /**
     * @param nums: A list of integers
     * @return: The majority number that occurs more than 1/3
     */
    public int majorityNumber(ArrayList<Integer> nums) {
        // write your code
    	//return helpMajorEle(nums, 3);
    	if (nums.size() == 0) {
    	    return Integer.MIN_VALUE;
    	}
    	int[] candidates = new int[3 - 1];
    	int[] count = new int[3 - 1];
    	for (int ele : nums) {
    		if (ele == candidates[0]) { //ele为已出现的0号候选者
    			count[0]++;
    		} else if (ele == candidates[1]) {
    			count[1]++;
    		} else if (count[0] == 0) {
    			count[0] = 1;
    			candidates[0] = ele;
    		} else if (count[1] == 0) {
    			count[1] = 1;
    			candidates[1] = ele;
    		} else {
    			count[0]--;
    			count[1]--;
    		}
    	}

    	//候选者序列中最后剩下的 k - 1 个元素中，就有1个是从早期一直占据了位置的major元素
    	count[0] = count[1] = 0;
    	for (int ele : nums) {
    		if (ele == candidates[0]) {
    			count[0]++;
    		}
    		if (ele == candidates[1]) {
    			count[1]++;
    		}
    	}
    	return (count[0] > count[1]) ? candidates[0] : candidates[1];
    }
    
    private int helpMajorEle(ArrayList<Integer> nums, int k) {
    	Map<Integer, Integer>
    }
}
