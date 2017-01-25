Given a sorted integer array where the range of elements are [0, 99] inclusive, return its missing ranges.
For example, given [0, 1, 3, 50, 75], return [“2”, “4->49”, “51->74”, “76->99”]
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
遇到的坑：
    当lower为INT_MIN时，low初始化为lower-1时就overflow了，

思想：
    我们应该设定low存储：上一个已经获取了的数字(但初始化low为lower,此时low仍必然<=nums[i])，
    然后从i=1开始分析：(low+1 == num[i]：low = num[i])；(low+2 == nums[i]：push("low+1"),low = nums[i])；(low+2 < nums[i]：push("low+1->nums[i]-1"),low=nums[i])

class Solution {
public:
    string int_str(int num){
        stringstream newstr;
        newstr<<num;
        return newstr.str();
    }

    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        int low = lower;//low：上一个已经获取了的数字(or 前一个区间的上界)
        vector<string> res;
        for(int i=i;i<nums.size();i++){//为了防止overflow，必须初始化low为lower(而非lower-1)，然后从i=1开始遍历
            if(low+1 == nums[i]){// low始终 <= nums[i]-1，因为low从lower-1开始根据nums[i]右移，而且lower <= nums[i] <=upper
                low++;//此时已经获取了[lower...low]，nums右侧又出现了low+1，这两个数字间没有missing range
            }
            else{
                if(low+2 == nums[i]){//此时前方已经获取了[lower...low],后方又出现了low+2,此时missing range仅为low+1这个数字
                    res.push_back(int_str(low+1));
                    low = nums[i];//经过nums[i]后，已获取连续区间的上界为nums[i]
                }
                else{//nums[i] > low+2，此时缺失区间为[low+1...nums[i]-1]这段
                    string temp = int_str(low+1)+"->"+int_str(nums[i]-1);
                    res.push_back(temp);
                    low = nums[i];
                }
            }
        }

        if(low < upper){
            if(low+1 == upper){
                res.push_back(int_str(upper));
            }
            else{//upper > low+2，此时缺失区间为[low+1...upper]这段
                string temp = int_str(low+1)+"->"+int_str(upper);
                res.push_back(temp);
            }
        }
        return res;
    }
};

int main(){
    int a[]={0,1,3,50,51,54,58,75,89,99};
    vector<int> num(a,a+10);
    vector<string> res;
    int lower = 0;
    int upper = 99;
    Solution sol=Solution();
    res = sol.findMissingRanges(num,lower,upper);
    for(int i=0;i<res.size();i++){
        cout<<res[i]<<endl;
    }
    return 0;
}
