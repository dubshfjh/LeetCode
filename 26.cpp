#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i,index,num;//i:遍历nums元素的真实下标；index：去重复后不同数字的当前个数-1(即在nums中的下标)
        i=index=0;
        if(nums.size()<=1){
        	return nums.size();
        }
        for(i=0;i<nums.size();i++){
			while(nums[i]==nums[i+1]){//跳出循环后，nums[i]中的i：最后一个取值为nums[i]的元素下标
        		i++;
        	}
        	nums[index++]=nums[i];//不重复数++，并在nums的(不重复数-1)这一下标存储值
        }
        return index;
    }
};


int main(){
	int a[]={1,1,1,1,2,3};
	vector<int> nums(a,a+6);
	Solution sol=Solution();
	sol.removeDuplicates(nums);
	return 0;
}
