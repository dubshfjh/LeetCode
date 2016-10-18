#include <iostream>
#include <vector>
using namespace std;

逻辑较为复杂，根本不需要找到middle再进行分析，下附真正的解法
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        int low,high,middle,temp;
        low=0;
        high=nums.size()-1;
        while(low<=high){
            middle=(low+high)/2;
            if(nums[middle]==target){
                break;
            }
            else if(nums[middle]<target){
                low=middle+1;
            }
            else{
                high=middle-1;
            }
        }
        if(low>high){
            res.push_back(-1);
            res.push_back(-1);
            return res;
        }
        low=0;
        temp=high=middle;
        //寻找左半段：{0...temp}段中的第一个取值为target的临界元素，但由于只尝试将high左移，若初始情况low=high=0，则high=-1会导致越界
        while(low<=high){
            middle=(low+high)/2;
            //cout<<"low1: "<<low<<" high1: "<<high<<endl;
            //cout<<middle<<" aaaaa "<<nums[middle]<<endl;
            if(nums[middle]<target){//如果[middle]<target，则临界元素在{middle+1...high}段中
                low=middle+1;//low右移
                if(nums[low]==target){//若low为临界元素
                    //cout<<"low1: "<<low<<endl;
                    res.push_back(low);
                    break;
                }
            }
            else if(nums[middle]==target){//如果middle==target，则临界元素在{low...middle-1}段中
                if(middle==0){//如果middle==0，则middle已经到达最左元素，此时high不能再左移去寻找前一个==target的元素
                    res.push_back(middle);
                    break;
                }
                else{
                    high=middle-1;//high左移
                    if(nums[high]<target){
                        //cout<<"middle1: "<<middle<<endl;
                        res.push_back(middle);
                        break;
                    }
                }               
            }
        }

        
        low=temp;
        high=nums.size()-1;
        
        while(low<=high){
            middle=(low+high)/2;
            //cout<<"low2: "<<low<<" high2: "<<high<<endl;
            //cout<<middle<<" bbbbbb "<<nums[middle]<<endl;
            if(nums[middle]>target){
                high=middle-1;
                if(nums[high]==target){
                    //cout<<"high2: "<<high<<endl;
                    res.push_back(high);
                    break;
                }
            }
            else if(nums[middle]==target){
                if(middle==nums.size()-1){//middle已经达到最后一个元素，此时high不能再右移去寻找下一个==target的元素
                    res.push_back(middle);
                    break;
                }
                else{
                    low=middle+1;
                    if(nums[low]>target){
                        //cout<<"middle2: "<<middle<<endl;
                        res.push_back(middle);
                        break;
                    }
                }
                
            }
        }      
        return res;
    }
};


class Solution {
    private:
        int binarySearchLow(vector<int>& nums, int target, int begin, int end)
        {
            if(begin > end) 
                return begin;//返回的是begin!!!此时end是第1个<target的元素,begin是第1个>=target的元素，结束循环时begin=end+1
            int mid = begin + (end - begin) / 2;
            if(nums[mid] < target)//如果[mid]<target，则begin右移
                return binarySearchLow(nums, target, mid + 1, end);
            else 
                return binarySearchLow(nums, target, begin, mid - 1);//如果[mid]>=target，则end左移
        }
        int binarySearchUp(vector<int>& nums, int target, int begin, int end)
        {
            if(begin > end) 
                return end;//返回end!!!!此时end是第1个<=target的元素，begin是第1个>target的数，begin=end+1
            int mid = begin + (end - begin) / 2;
            if(nums[mid] > target) 
                return binarySearchUp(nums, target, begin, mid - 1);//如果[mid]>target，end左移
            else 
                return binarySearchUp(nums, target, mid + 1, end);//如果[mid]<=target，则begin右移
        }
    public:
        vector<int> searchRange(vector<int>& nums, int target) {
            vector<int> res(2, -1);
            if(nums.empty()) return res;
            int high = binarySearchUp(nums, target, 0, nums.size() -1);
            int low = binarySearchLow(nums, target, 0, nums.size() - 1);
            if(high >= low)
            {
                res[0] = low;
                res[1] = high;
                return res;
            }
            return res;
        }
};

int main(){
	vector<int> res;
    int a[]={0,1,2};
    vector<int> nums(a,a+3);
    
    Solution sol=Solution();
    res=sol.searchRange(nums,2);
    for(int i=0;i<res.size();i++){
    	cout<<res<<endl;
    }
    return 0;
}
