长度为n的nums数组中存放了{0...n}这个序列的n个数字，每个数字只出现1次，因此利用"合法取值时 index为该元素的位置取 negative法"
1. 遍历整个数组
	1.1 if 0<=abs(nums[i])<=n-1，则 设置 nums[ abs(nums[i]) ] 取反
	1.2 if abs(nums[i] == n)， 则 设置 nExist = true
2. 再遍历1次数组，如果nums[j] > 0，则说明 j 从未在 nums中出现过；
3. 如果每个元素都 <=0，则当 nExist==true时，说明 nums[0] = 0；当 nExist == false 时，n 未出现过

public class Solution {
    /**    
     * @param nums: an array of integers
     * @return: an integer
     */
    public int findMissing(int[] nums) {
        // write your code here
    	if (nums.length == 0) {
    		return 0;
    	}
    	boolean nExist = false;
    	for (int i = 0; i < nums.length; i++) {
    		int index = Math.abs(nums[i]);
    		if (index == nums.length) {
    			nExist = true;
    		} else {
    			nums[index] = -nums[index];
    		}
    	}

    	for (int i = 0; i < nums.length; i++) {
    		if (nums[i] > 0) {
    			return i;
    		}
    	}

    	if (!nExist) {
    		return nums.length;
    	} else {
    		return 0;
    	}
    }
}