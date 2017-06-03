class Solution {
    public int maxProduct(int[] nums) {//abs(nums[i]) >= 1，所以每个数字nums[i]对以i为结尾的子数组MAX乘积/MIN乘积是起贡献的
        //都说了nums至少有1个数字，所以不需要判断nums.length==0的边界情况
        int n = nums.length;
        int dpMax[] = new int[n+1];//记录以[i]为结尾的，以任意字符开始的子数组MaxProduct，因此为 max(nums[i],最小乘积*nums[i], 最大乘积*nums[i])
        int dpMin[] = new int[n+1];//记录仪[i]为结尾的，以任意字符开始的子数组MinProduct，因此为 min(nums[i],最小乘积*nums[i], 最大乘积*nums[i])
        dpMax[0] = dpMin[0] = 1;
        for(int i=0;i<n;i++){
            int tempMax = Math.max(dpMax[i]*nums[i],dpMin[i]*nums[i]);
            int tempMin = Math.min(dpMax[i]*nums[i],dpMin[i]*nums[i]);

            dpMax[i+1] = Math.max(nums[i], tempMax);
            dpMin[i+1] = Math.min(nums[i], tempMin);
            // System.out.println(nums[i]+" : "+tempMin+"  "+tempMax);
        }
        int res = dpMax[1];
        for(int i=1;i<n;i++){
            res = Math.max(res,dpMax[i+1]);
        }
        return res;
    }
}