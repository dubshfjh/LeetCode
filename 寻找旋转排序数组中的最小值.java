1. start...max,min...end, we should find the only peek
2. min...max, there doesn't exist any peek && [0] < [1]
3. max...min, there doesn't exist any peek && [0] > [1]

In any situation, the goal is "find the first element(with min index) that is <= [length - 1]"
while (start + 1 < end)
1. [mid] < target: start...max,min...mid...end(target), the MIN is leftside of [mid]
2. [mid] > target: start...mid...max...min...end, the MIN is rightside of [mid]
3. [mid] == target: As the goal is find the most left, so we should still move the right bound

public class Solution {
    /**
     * @param nums: a rotated sorted array
     * @return: the minimum number in the array
     */
    public int findMin(int[] nums) {
        // write your code here
        int length = nums.length;
    	if (length <= 1) {
    		return (length == 0) ? Integer.MAX_VALUE : nums[0];
    	}
    	int start = 0;
    	int end = length - 1;
    	// find the first element(with min index) that is <= [length - 1]
    	int target = nums[length - 1];
    	while (start + 1 < end) {
    		int mid = start + ((end - start) >> 1);
    		if (nums[mid] > target) { //start...mid...max...min...end, the MIN is rightside of [mid]
    			start = mid; 
    		} else { //start...max,min...mid...end(target), the MIN is leftside of [mid]
    			end = mid; //[mid] == target, as we wanna most left element, we should still move the right bound
    		}
    	} 
    	if (nums[start] < nums[end]) {
    		return nums[start];
    	} else {
    		return nums[end];
    	}
    	/*
    	while (start + 1 < end) {
    	    System.out.println(start + ",," + end);
    		int mid = start + ((end - start) >> 1);
    		// because start: {0...end - 1}, so the middle is {0...length - 1}
    		if (nums[mid] < nums[mid + 1] && (mid == 0 || nums[mid] < nums[mid - 1])) {
    			return nums[mid];
    		} else if (nums[mid] < nums[mid + 1] && (mid == 0 || nums[mid] > nums[mid - 1])) {
    			end = mid;
    		} else if (nums[mid] > nums[mid + 1] && (mid == 0 || nums[mid] < nums[mid - 1])) {
    			start = mid;
    		} else { // left or right are both OK
    			start = mid;
    		}
    		// we must use [i-1],[i],[i+1] to check if sequence increases
    		// if (nums[mid] < nums[mid + 1]) { // increasing sequence, the peek is at mid or leftside
    		// 	end = mid;
    		// } else { //decreasing sequence, the peek is at mid or rightSide
    		// 	start = mid;
    		// }
    	}
    	return Math.min(nums[start], nums[end]);
    	*/
    }
}