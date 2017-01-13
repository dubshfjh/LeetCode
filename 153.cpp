"蛮力强行分析"
类比 leetcode 33,81 中的 rotated array
由于本题的数组中没有重复元素，则旋转排序数组有三种情况
 1.[0...max,min,...size-1]，此时[0] > [size-1]，数组: [0] 递增到max, 递减到min, 递增到[size-1]，所以只需要找到first [i]<[i-1]的[i]即为min
 2.[min...max]，此时 [0] < [size-1]，只需要将[0]返回即可
 3.[min]，此时 [0] == [size-1]，即数组中只有1个元素同时作为min和max，只需将nums[0]返回即可
 
class Solution {
public:
    int findMin(vector<int>& nums) {
        int size = nums.size();
        if(size == 0){
            return INT_MIN;
        }
        else{
            if(nums[0] == nums[size-1]){//[min]
                return nums[0];
            }
            else if(nums[0] < nums[size-1]){//[min...max]
                return nums[0];
            }
            else{//[0...max,min...size-1]，而且[0] > [size-1]
                for(int i=1;i<size;i++){
                    if(nums[i] < nums[i-1]){
                        return nums[i];
                    }
                }
                return INT_MIN;
            }
        }
    }
};


采用二分搜索获取到min。[min...max]这种情况整体递增，[0...max,min...size-1]这种情况从[0]递增到max，然后max递减到min，最后min递增到max
分析子数组[start,end]，if(nums[start] < nums[end])，则说明[start...end]这段子数组没有发生旋转，子数组为[min...max]
if(nums[start] > nums[end])，子数组属于[start...max,min...end],则计算出中间元素[mid]，
        如果[mid]>=[start]，则说明旋转发生在mid分割子数组的第2部分，即mid处于{start..mid...max,min...end}，而且[mid]不可能为min，因此start右移到mid+1
        如果[mid]<[start]，则说明旋转发生在mid分割子数组的第1部分，即mid处于{start...max,min...mid...end}，由于[mid]可能为min，因此end左移到mid
//所谓的处于旋转段的子数组，就是不满足原本的升序排列的子数组

class Solution {
public:
    int findMin(vector<int>& nums) {
        int start = 0;
        int end = nums.size()-1;

        while(start < end){
            if(nums[start] < nums[end]){
                return nums[start];
            }

            int mid = (start+end)/2;
            if(nums[mid] >= nums[start]){
                start = mid+1;
            }
            else{
                end = mid;
            }
        }
        return nums[start];
    }
};