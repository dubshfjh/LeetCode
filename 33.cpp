#include <iostream>
#include <vector>
using namespace std;

太过复杂，不需要精确的计算出max_index和min_index，只需要middle和max_index,min_index的关系即可，下方有简单的做法

class Solution {
public:
    int search(vector<int>& nums, int target) {//旋转后的排序数组主要为 {nums[0]<...<nums[i]<max}{min<nums[j]<...<nums[size-1]}
    	int i,j,size,max_index,min_index,low,high,middle;//如果存在min(即max!=size-1)，则nums[size-1]为最接近nums[0]而且小于它的数
    	size=nums.size();
		if(size==0){
    		return -1;
    	}
		else if(size==1){
			return (nums[0]==target)?0:-1;
		}
    	low=0;
    	high=size-1;
    	min_index=max_index=(low+high)/2;
    	if(nums[max_index]>=nums[high]){//说明初值位于{0...max}段，而且max_index!=size-1
    		while(max_index<size-1&&nums[max_index]<nums[max_index+1]){
    			max_index++;
				cout<<"index:"<<max_index<<endl;
    		}
    		//如果max_index==size-1,则到最后一个元素为止都不存在left>right的情况，此时max_index就为size-1
    	}
    	else{//说明初值位于{min...size-1}段；或者max_index==size-1&&初值位于{0...max}段
    		while(min_index>0&&nums[min_index]>nums[min_index-1]){
    			min_index--;
				//cout<<"index:"<<min_index<<endl;
    		}
    		max_index=min_index-1;
    		if(max_index<0){
    			max_index=size-1;
    			min_index=0;
    		}
    	}//如果min_index==1，则到第2个元素为止都是right>left(ps:{nums[0]...max}段至少有一个元素)，则此时min_index=1,max_index=0;
    	cout<<max_index<<",,,"<<min_index<<endl;
    	if(target>=nums[0]){//target位于{0...max}段
    		high=max_index;
    	}
    	else{//target位于{min...size-1}段，或者max_index==size-1时，位于{0...max}段，即{0...size-1}段
    		if(max_index==size-1){
    			high=max_index;
    		}
    		else{
    			low=min_index;
    		}
    	}
    	while(low<high){
    		middle=(low+high)/2;
			//cout<<"low: "<<low<<"  high:"<<high<<endl;
			//cout<<"middle is :"<<middle<<endl;
			if(nums[middle]==target){
				return middle;
			}
			else if(nums[middle]<target){
				low=middle+1;
			}
			else{
				high=middle-1;
			}
    	}
    	return -1;
    }
};


class Solution {
public:
    int search(vector<int>& nums, int target){
    	int low,high,middle;
    	low=0;
    	high=size-1;
    	while(low<=high){
    		middle=(low+high)/2;
    		if(nums[middle]==target){
    			return middle;
    		}
    		if(nums[low]>nums[middle]){//middle位于{min...size-1}段:{low...max min...middle...high}
    			if(target>=nums[low] || target<=nums[middle]){//{low...target_1...max min ... target_2...middle...high}
    				high=middle-1;//high左移
    			}
    			else{//nums[low]>target>nums[middle]  {low...max min ... middle...target...high}
    				low=middle+1;//low右移
    			}
    		}
    		else{//middle位于{0...max}段 {low...middle...max min...high}
    			if(target>=nums[low]&&target<=nums[middle]){//{low...target...middle...max min...high}
    				high=middle-1;//high左移
    			}
    			else{//target>nums[middle] || target<nums[low]  {low....middle...target_1...max min...target...high}
    				low=middle+1;//low右移
    			}
    		}
    	}
    	return -1;
    }
};
int main(){
	int res;
    int a[]={0,1,2,4,5,6,7};
    vector<int> nums(a,a+7);
    
    Solution sol=Solution();
    res=sol.search(nums,2);
	cout<<res<<endl;
    return 0;
}
