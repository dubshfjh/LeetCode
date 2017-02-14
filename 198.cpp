动态规划：设计数组dp[size+1]，dp[i]存储到达第[i]天的最高盗窃金钱数:dp[i] = max(dp[i-1],dp[i-2]+nums[i-1])
在第i天有2种选择，1：第i天不盗窃, dp[i]=dp[i-1]；2.第i天盗窃,dp[i] = dp[i-2]+nums[i-1]
class Solution {
public:
    int rob(vector<int>& nums) {
        int size,res;
        size = nums.size();
        int dp[size+1];
        dp[0] = 0;//增加一个dummy space，用来处理(size==0的情况 and 统一化dp[2]的计算方法)
        if(size >= 1){
            dp[1] = nums[0];
            for(int i=2;i<=size;i++){
                //cout<<nums[i-1]<<endl;
                dp[i] = max(dp[i-1],dp[i-2]+nums[i-1]);
            }            
        }
        return dp[size];
    }
};