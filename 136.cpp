辣鸡运行时间，弃之
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        /*
        if(nums.size()<=1){
            return -1;
        }
        */
        unordered_map<int,int> count;
        for(int i=0;i<nums.size();i++){
            if(count.find(nums[i]) == count.end()){
                count[nums[i]] = 1;
            }
            else{
                count[nums[i]]++;
            }
        }

        for(int i=0;i<nums.size();i++){
            if(count[nums[i]] == 1){
                return nums[i];
            }
        }
        return -1;
    }
};

使用变量res遍历地异或每个数字，由于0^a = a, a^a = 0。对于每个出现了2次的数字a，都有res=...^a^...^a^... = ...^...。遍历异或到最后的结果就是只出现了一次的数字
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        if(nums.size()==0){
            return -1;
        }
        int res = 0;// 0^a = a, a^a = 0；因此对于size-1个出现了2次的数字a，在异或的过程中都会遇到相等数字导致res中a所有位都为0，使得res=...^a^...^a^... = ...^...。异或到最后剩下的就是出现了1次的那个数
        for(int i=0;i<nums.size();i++){
            res ^= nums[i];
        }
        return res;
    }
};