#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int i;
        map<int,int> numcount;
        vector<int> temp;
        for(i=0;i<nums.size();i++){
            if(numcount.count(nums[i])==0){
                numcount.insert(pair<int,int>(nums[i],1));
            }
            else{
                numcount[nums[i]]+=1;
            }
        }
        sort(nums.begin(),nums.end());
        backtrace(temp,nums,numcount,0);
        return res;
    }

    void backtrace(vector<int>& temp,vector<int> nums,map<int,int> numcount,int index){
        int i,temp_num;
        if(index==nums.size()){
            res.push_back(temp);
        }
        i=0;
        while(i<nums.size()){
            temp_num=numcount[nums[i]];
            if(numcount[nums[i]]>0){
                temp.push_back(nums[i]);
                numcount[nums[i]]--;
                backtrace(temp,nums,numcount,index+1);
                
                temp.pop_back();
                numcount[nums[i]]++;
                i++;
                while(nums[i]==nums[i-1]){
                    cout<<i<<endl;
                    i++;
                }
            }
            else{
                i++;
            }
        }
    }
};