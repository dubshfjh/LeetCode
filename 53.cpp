#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int i,size,pre_sum,temp,res;
        size=nums.size();
        pre_sum=0;//pre_sum存储以nums[i]作为结尾的子数组最大sum
        res=nums[0];
        for(i=0;i<size;i++){//pre_sum=max{pre_sum+nums[i], nums[i]}
        	if(pre_sum>=0){//如果到i之前的pre_sum>=0，则取前者
        		pre_sum+=nums[i];
        	}
        	else{//如果i之前的pre_sum<0，则{nums[i]}即为到i为止的最大和子数组
        		pre_sum=nums[i];
        	}
        	if(pre_sum>=res){//以当前nums[i]为结尾的子数组不一定为整体的最大子数组，但是res=max(pre_sum[0],pre_sum[1],...,pre_sum[size-1])
        		res=pre_sum;
        	}
        }
        return res;
    }
    
};