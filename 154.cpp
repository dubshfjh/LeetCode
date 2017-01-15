强行分析，蛮力到不忍直视。。。
class Solution {
public:
    int findMin(vector<int>& nums) {
        int size = nums.size();
        if(size == 0){
            return INT_MIN;
        }
        else if(size == 1){//min和max为同一个元素
            return nums[0];
        }
        else{//同时存在min，max两个元素，但二者可能取值相等
            if(nums[0] < nums[size-1]){//{min....max} 而且 min!=max
                return nums[0];
            }
            else if(nums[0] > nums[size-1]){//{0...max...min...size-1} 而且 min!=max(因为[0]!=[size-1]说明并不是每2个元素相等)
                for(int i=1;i<size;i++){//找出first递减的元素[i]
                    if(nums[i] < nums[i-1]){
                        return nums[i];
                    }
                }
                return INT_MIN;
            }
            else{//[0] == [size-1]，此时min可能等于max。对于{min...max}而言，则一定满足min==max。对于{min...max...min}/{max...max,min...max}/{else...max...min...else}而言，如果min==max，则找不到使得[i]<[i-1]的元素；如果min != max，则能找到[i]<[i-1]的元素
                for(int i=1;i<size;i++){
                    if(nums[i] < nums[i-1]){//{0...max,min...size-1} 中 min<max的情况
                        return nums[i];
                    }
                }
                return nums[0];//{min...max} plus {0...max,min...size-1} 中 min==max的情况
            }
        }
    }
};

采用二分搜索获取到min。此时存在[min...max],[0...max,min...size-1],[max...max,min...max],[min...min...max...min]等多种情况，不一定严格递增了！！！

在"无重复元素的数组中"可以因为[start]<[end]而提前跳出循环，但这段语句只是减少了运行时间而已，并没有减少时间复杂度，所以模板代码并没有这段
"分析子数组[start,end]，if(nums[start] < nums[end])，则说明[start...end]这段子数组没有发生旋转，子数组为[min...max]"

if(nums[start] > nums[end])，子数组属于[start...max,min...end],则计算出中间元素[mid]，为了避免下标的overflow，mid = low+(high-low)/2。
    "比较[mid] 与 [start]的大小关系，当二者相等导致无法判断mid在min的左侧/右侧时，需要将下界start++右移"
        如果[mid]>[start]，则说明旋转发生在mid分割子数组的第2部分，即mid处于{start..mid...max,min...end}，而且[mid]不可能为min，因此start右移到mid+1
        如果[mid]<[start]，则说明旋转发生在mid分割子数组的第1部分，即mid处于{start...max,min...mid...end}，由于[mid]可能为min，因此end左移到mid
        如果[mid]==[start]，则存在mid位于min左侧，mid位于min右侧，mid就是min三种情况，无法判断mid的位置，此时需要将下界start++ 

    "如果比较[mid] 与 [end]的大小关系，当二者相等导致无法判断mid的位置时，需要将上界end--"
    
class Solution {
public:
    int findMin(vector<int>& nums) {
        int start = 0;
        int end = nums.size()-1;

        while(start < end){
            if(nums[start] < nums[end]){
                return nums[start];
            }

            //int mid = (start+end)/2;
            int mid = start + (end - start)/2;//PS：由于二分搜索的BUG，当start和end接近INT_MAX时，直接计算(start+end)/2会导致overflow产生负数
            if(nums[mid] > nums[start]){
                start = mid+1;
            }
            else if(nums[mid] < nums[start]){
                end = mid;
            }
            else{
                start++;
            }
        }

        return nums[start];
    }
};