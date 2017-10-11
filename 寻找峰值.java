二分法的本质：一段连续区间 ==> 循环砍掉不可能产生Solution的一半 ==> 两个端点 ==> 判断两个端点
对于每个可能成为peak的元素 nums[i] : 1 <= i <= n - 2 
1. 大于左侧 && 大于右侧，[i]为peak，直接返回[i]
2. 大于左侧 && 小于右侧，peak必然在[i]的右侧，因此直接砍掉"左半区间"
3. 小于左侧 && 大于右侧，peak必然在[i]的左侧
4. 小于左侧 && 小于右侧，[i]为谷值，此时左侧和右侧都有可能找到peak，因此任意砍掉"左半/右半区间"
public class Solution {
    /*
     * @param A: An integers array.
     * @return: return any of peek positions.
     */
    public int findPeak(int[] A) {
        // write your code here
        if (A == null || A.length < 3) {
        	return Integer.MIN_VALUE;
        }

        int start = 0;
        int end = A.length - 1;
        while (start + 1 < end) {
        	int mid = start + ((end - start) >> 1);
        	if (largerThanLeft(A, mid) && largerThanRight(A, mid)) {
        		return mid;
        	} else if (largerThanLeft(A, mid) && lessThanRight(A, mid)) {
        		start = mid;
        	} else if (lessThanLeft(A, mid) && lessThanRight(A, mid)) {
        		start = mid;
        	} else {
        		end = mid;
        	}
        }

        if (A[start] > A[end]) {
        	return start;
        } else {
        	return end;
        }
    }

    private boolean	largerThanLeft(int[] nums, int i) {
    	return i == 1 || nums[i] > nums[i - 1];
    }

    private boolean lessThanLeft(int[] nums, int i) {
    	return i > 1 && nums[i] < nums[i - 1];
    }

    private boolean largerThanRight(int[] nums, int i) {
    	return i == nums.length - 2 || nums[i] > nums[i + 1];
    }

    private boolean lessThanRight(int[] nums, int i) {
    	return i < nums.length - 2 && nums[i] < nums[i + 1];
    }
}