class Solution {
public:
    int findPeakElement(vector<int>& nums) {//利用只存在1 peak的题意，递增序列和递减序列的交点就是peak(本题中只存在1个这样的交点)
        int i,res;
        int size = nums.size();
        for(i=1;i<size;i++){//从[0]开始寻找递增序列，
            if(nums[i] < nums[i-1]){//遇到first < 左邻居[i-1]的元素[i]，则[i-1]处于递增序列&&[i-1]>[i]，此时[i-1]为peak
                break;
            }
        }
        if(i == size){//此时说明{1...size-1}全部>左邻居，则{0...size-1}全部处于递增序列，则[size-1]为peak
            res = size-1;
        }
        else{//{1...i-1}全部>左邻居，则{0...i-1}处于递增序列&&[i-1]>[i]
            res = i-1;
        }
        return res;
    }
};

//针对存在多个peak个题再写一个版本
//解决多个peak的问题(通过了自己随意构建的test case，未设计边界测试)
class Solution {
public:
    int findPeakElement(vector<int>& nums) {//NULL到[0]为递增，[n-1]到NULL为递减,每个递增序列和递减序列的交点都是peak(本题中只存在1个这样的交点)
        int i,res;
        int size = nums.size();
        vector<int> peaks;
        i = 1;
        if(size == 1){
            return 0;
        }
        while(i<size){
            // cout<<i<<",,,"<<nums[i]<<endl;
            if(nums[i] > nums[i-1]){//对于递增序列直接跳过，但是最后一个元素右侧默认有个递减序列，所以[size-1]处于递增序列，则它也是个peak
                if(i == size-1){
                    peaks.push_back(i);
                }
                i++;
                continue;
            }
            else if(nums[i] < nums[i-1]){//此时，[i-1]为递增序列的last元素
                peaks.push_back(i-1);
                //跳过整个递减序列
                while(i<size-1 && nums[i] > nums[i+1]){//进入循环前,{i-1,i}为递减序列，跳出循环后，[i]是递减序列的最后1个元素
                    i++;
                }
                i++;//i再右移一次，变成递增序列的first元素
            }
            
        }
        for(int j=0;j<peaks.size();j++){
            cout<<nums[peaks[j]]<<endl;
        }

        return peaks[0];
    }
};
