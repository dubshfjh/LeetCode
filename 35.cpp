#include <iostream>
#include <vector>
using namespace std;

用34题中的递归方法思想，试图找到第一个==target的元素下标，此时递归体中的high：最后一个<target的元素；low:第一个>=target的元素
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int size,res;
        size=nums.size();
        if(size==0){
        	return 0;
        }
        res=getIndex(nums,target,0,size-1);
        
        return res;
    }

    int getIndex(vector<int>& nums,int target,int low,int high){
    	int mid;
		if(low>high){
			return low;
		}
		mid=(low+high)/2;
		if(nums[mid]>=target){//如果>=target，则high左移，最终的high是最后一个<target的元素(也是high左移过程中遇到的第一个<target的元素)
			return getIndex(nums,target,low,mid-1);
		}
		else{//如果<target，则low左移，最终的low是第一个>=target的元素，如果target<nums[0]，则low返回0
			return getIndex(nums,target,mid+1,high);
		}
    }
};

int main(){
	int res;
    int a[]={1,3,5,6};
    vector<int> nums(a,a+4);
    
    Solution sol=Solution();
    res=sol.searchInsert(nums,0);
    cout<<res<<endl;
    return 0;
}
