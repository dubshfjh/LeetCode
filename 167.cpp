使用两个指针high和low，high遍历{size-1,size-2...1},low遍历{pre_low...high-1}，pre_low表示last<=上一轮remain的元素(如果存在)。由于[high]依次减小，
    每次需要的remain依次增加，为寻找next remain，low只需要从上一次的pre_low开始遍历直至high-1即可，一旦[low]==remain则存入res中，由于题意暗示unique solution，直接返回res。
    PS：如果上一轮中最后一个<=remain的元素(即[pre_low])>本轮remain，则{pre_low...high-1}全部 > 本轮remain，直接continue进入下一轮寻找更大的remain

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int low,high,size,pre_low;
        vector<int> res;
        size = numbers.size();
        pre_low = 0;//pre_low存储{last<=上一轮remain的元素(如果存在)}.题意暗示只有1个Solution，由于[high]依次减小，因此每次需要的remain依次增加，为寻找next remain，只需要从上一次的pre_low开始遍历即可
        for(high=size-1;high>0;high--){
            int remain = target-numbers[high];
            if(numbers[pre_low] > remain){//如果上一轮的[pre_low]>本轮的remain，则上一轮[pre_low]>本轮remain>=上轮remain，此时{pre_low...high-1}全部大于本轮和上轮的remain。因此只能尝试在下轮寻找更大的remain
                continue;
            }
            for(low=pre_low;low<high && numbers[low]<=remain;low++){
                if(numbers[low] == remain){
                    res.push_back(low+1);
                    res.push_back(high+1);
                    return res;//由于题意暗示只有1个Solution，找到1个Solution后直接return即可，节省时间
                }
                pre_low = low;
            }
        }
        return res;//此时意味着没有解决方案
    }
};