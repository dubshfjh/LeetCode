#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	vector<vector<int>> res;
    vector<vector<int>> permute(vector<int>& nums) {
        int i;
        map<int,int> visited;
        vector<int> temp;
        for(i=0;i<nums.size();i++){
        	visited.insert(pair<int,int>(nums[i],0));
        }
        backtrace(temp,nums,visited,0);
        return res;
    }

    void backtrace(vector<int>& temp,vector<int> nums,map<int,int> visited,int index){
    	if(index==nums.size()){
    		res.push_back(temp);
    	}
    	for(int i=0;i<nums.size();i++){
    		if(visited[nums[i]]==0){
    			temp.push_back(nums[i]);
    			visited[nums[i]]=1;
    			backtrace(temp,nums,visited,index+1);

    			temp.pop_back();
    			visited[nums[i]]=0;
    		}
    	}

    }
};