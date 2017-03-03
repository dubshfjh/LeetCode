[88 3 2 99 1 38] ==> [88 99]
[88 3 2 99 1 89] ==> [99 89]，answer并不一定为[0,2...] 或者 [1,3...]其中的一个
当首尾元素能共存时，dp[i] = max(dp[i-1],dp[i-2]+nums[i-1])
当size >= 2时，分别砍去首元素和尾元素，计算两个dp数组，取max(dp1[size-1],dp2[size-1])
class Solution {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if(size == 0){
            return 0;
        }
        int res = 0;//
        vector<int> dp1(size,0),dp2(size,0);
        dp1[1] = nums[0];
        if(size == 1){
            return nums[0];
        }
        for(int i=1;i<size-1;i++){//dp1砍去尾部元素,dp1[i]存储到第i个house为止(即面对nums[i-1])，最大收益
            dp1[i+1] = max(dp1[i], dp1[i-1]+nums[i]);
        }

        dp2[1] = nums[1];
        for(int i=2;i<size;i++){//dp2砍去首部元素,dp2[i]存储到第i+1个house为止(即面对nums[i])，最大收益
            dp2[i] = max(dp2[i-1], dp2[i-2]+nums[i]);
        }

        res = max(dp1[size-1], dp2[size-1]);
        return res;
    }
};