对于元素nums[i]，它的正确下标为trueIndex = nums[i]-1，若nums[trueIndex]>0，将它反转为 -nums[trueIndex] 这个负数；若nums[trueIndex]<0，则说明 nums[i]之前出现过了，记录abs(nums[i])

public class Solution {
    public int findDuplicate(int[] nums) {
        int res = -1;
        for(int i=0;i<nums.length;i++){
            int trueIndex = Math.abs(nums[i]) - 1;
            if(nums[trueIndex] > 0){
                nums[trueIndex] = -nums[trueIndex];
            }
            else if(res < 0){
                res = Math.abs(nums[i]);
            }
            /*
            else{
                res = Math.abs(nums[i]);
            }
            */
        }
        return res;
    }
}