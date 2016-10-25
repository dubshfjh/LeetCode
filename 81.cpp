允许重复元素，如果A[m]>=A[l], 那么[l,m] 为递增序列的假设就不能成立了，比
如[1,3,1,1,1]。
如果A[m]>=A[l] 不能确定递增，那就把它拆分成两个条件：
• 若A[m]>A[l]，则区间[l,m] 一定递增
• 若A[m]==A[l] 确定不了，那就l++，往下看一步即可。
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        return partition(nums,target,0,nums.size()-1);
    }

    bool partition(vector<int>& nums,int target,int start,int end){
        while(start<=end){
            int mid=(start+end)/2;
            if(nums[mid]==target){
                return true;
            }
            else if(nums[mid] < nums[start]){
                if(target>nums[mid] && target<=nums[end]){
                    start=mid+1;
                }
                else{
                    end=mid-1;
                }
            }
            else if(nums[mid] > nums[start]){
                if(target>=nums[start] && target<nums[mid]){
                    end=mid-1;
                }
                else{
                    start=mid+1;
                }
            }
            else{
                start++;
            }
        }
        return false;
    }
};


下面的代码通过了[1,3,1,1,1],[1,1,3,1],[3,1]这些[low]==[mid]的情况，但是死在了[1,3]上
原因在于当存在重复数字时，max和min太难以界定其范围，low/high/max/min可以任意两辆相等，很难判断mid在左侧还是右侧，暂且弃坑
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int low,high,mid;
        low=0;
        high=nums.size()-1;
        while(low<=high){
            mid=(low+high)/2;
            if(nums[mid] == target){
                return true;
            }
            // cout<<"l:"<<low<<",,,h:"<<high<<",,,m:"<<m<<endl;
            if(nums[low] > nums[mid]){// low...max min..mid..high
                if(target>=nums[low] || target<=nums[mid]){//low...target..max (>=[low]),,, min...target...mid(<=[mid])
                    high=mid-1;
                }
                else{//mid...low...high   :[mid]<target<[low]
                    low=mid+1;
                }
            }
            else if(nums[low] < nums[mid]){//[low]<[mid]时，则mid都在这一段！！！low...mid...max min...high
               if(target>=nums[low] && target<=nums[mid]){//low...target...mid([low]<=target<=[mid])
                    high=mid-1;
                }
                else{//low...mid...target...max(>[mid]) ,,, min...target...high(<[low])
                    low=mid+1;
                }                 
            }
            //当case为[3,1]时，low == mid，此时mid为max，但因为之后不存在>low的元素，所以误认为mid在右半段，但实际上low即为max，它仍在左段
            else{//如果[low]==mid，则可能为[low]..[mid]..max min...[high], [low]...max min [mid]...[high]
                //1,3,1,1,1；1,1,3,1
                    if(target==nums[mid]){
                        return true;
                    }
                    else{
                        int maxindex=low;
                        for(int temp=low;temp<=high;temp++){
                            if(nums[temp] > nums[maxindex]){
                                maxindex=temp;
                            }
                        }
                        if(mid<=maxindex){//mid位于左侧，low...mid...max min...high
                            low=mid+1;
                        }
                        else{//mid位于右侧，low...max min...mid...high
                            high=mid-1;    
                        }
                    }
                }    
            
        }
        return false;
    }
};

