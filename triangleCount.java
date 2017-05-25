import java.util.*;
对撞指针优化算法，本质上就是要证明 不需要扫描"多余状态"
初始化left=左边界；right=右边界
if([left],[right] 满足条件)
    right--/left++;
    do something;
else if([left],[right] 不满足某个条件)
    left++/right--;// {不满足某个条件}时的left++ ==> {满足条件}时的right--
    do something
else
    do something
    left++ or right--
//找出合理的三角形数，设 [i]>=[j]>=[k]
//则三角形的要求1：[i]+[j]>[k]；[i]+[k]>[j] 必然满足
//只需要找到 [j]+[k] > [i]的组合数即可，题目转化为 TwoSum的变种题
public class Main{
    int countTriangle(int[] nums){
        Arrays.sort(nums);
        int res = 0;
        for(int i=0;i<nums.length;i++){
            int target = nums[i];
            int right = i-1, left = 0;
            while(left < right){//双指针TwoSum2的模板：O(n)
                if(nums[left]+nums[right] > target){
                    res += (right - left);
                    right--;
                }
                else{
                    left++;
                }
            }
            /* 这个解法仍然是O(n^2)
            for(int j=0;j<i;j++){
                for(int k=0;k<j;k++){
                    if(nums[j]+nums[k] > target){
                        res += j-k;
                        break;
                    }
                    else{
                        continue;
                    }
                }
            }
            */
        }
        return res;
    }

    int TwoSum2(int[] nums,int target){
        int left = 0,right = nums.length-1;
        int res = 0;
        while(left < right){
            if(nums[left] + nums[right] > target){
                res += (right - left);
                right--;
            }
            else{
                left++;
            }
        }
    }
}