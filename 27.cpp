#include <iostream>
#include <vector>
using namespace std;
弱智的leetcode认为这段代码没有返回nums!!!但实际上测试过了：结果没问题，只是leetcode不愿意检测
原因：leetcode坚持认为只有nums中的元素被赋值过，才会检测它的前left个元素的值，而下面的做法对前index个元素都进行了赋值，所以有效...
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left,right,temp;//left：数组中==val的元素下标，即后一个需要被覆盖的元素，right：遇到的前一个!=val的元素，即第一个需要左移的元素
        left=0;
        right=nums.size()-1;
        if(nums.size()==0){
        	return 0;
        }
        if(left==right){
        	if(nums[0]==val){
        		nums.erase(nums.begin());
        		return 0;
        	}
        	return 1;
        }
        while(left<right){
        	while(nums[left]!=val&&left<right){
        		left++;//left右移到后一个==val的元素，即需要被覆盖的元素
        	}
        	while(nums[right]==val&&right>left){
        		right--;//right左移到前一个!=val的元素，即需要左移的元素
        	}
        	temp=nums[left];
        	nums[left]=nums[right];
        	nums[right]=temp;
        }
        return left;
    }
};


class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int length = nums.size();
        int index=0;
        if(length==0){
        	return index;
        }
        for(int i=0; i<length; i++){
            if(nums[i]!=val){
                 nums[index++] = nums[i];
            }
        }
        return index;
    }
};