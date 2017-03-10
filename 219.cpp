使用一个map记录(nums[i],i)的映射关系，对于每个元素[i]都检查 map[nums[i]]-i 是否<=k，然后将map中nums[i]这个数值的最新下标update为i

结合 推广到 |i-j|<=k, |nums[i]-nums[j]|<=t 的问题上，思想应该转换：设置一个set<long long> window有序地存储数组中所有元素
    对于每个元素[i]：保持window中只存放[i-k...i-1]这k个元素，当window.size()>k时，从set中erase nums[i-k-1]
    2.寻找它在set中的最小上界upper，检查是否满足(upper!=window.end() && *upper<=nums[i]+t)
    3.寻找它在set中的最大下界lower,当upper!=window.begin()时,lower=upper-1，检查是否满足(low!=window.end() && *lower>=nums[i]+t)
    4.在set中插入nums[i]

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int,int> index;
        for(int i=0;i<nums.size();i++){
            if(index.find(nums[i]) != index.end()){
                if(i - index[nums[i]] <= k){
                    return true;
                }
            }
            index[nums[i]] = i;
        }
        return false;
    }
};