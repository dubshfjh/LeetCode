#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int i,j,start,end,size,sum;
        vector<vector<int>> res;
        vector<int> temp;
        size=nums.size();
        if(size<4){
        	return res;
        }
        sort(nums.begin(),nums.end());
        cout<<size<<endl;
        for(i=0;i<size-3;i++){//i右侧至少应该3节点       	
        	for(j=i+1;j<size-2;j++){//j右侧至少应该2节点
        		start=j+1;
        		end=size-1;
        		while(start<end){
        			//cout<<nums[i]<<",,,"<<nums[j]<<nums[start]<<",,,"<<nums[end]<<endl;
        			sum=nums[i]+nums[j]+nums[start]+nums[end];
        			if(sum==target){
        				temp.push_back(nums[i]);
        				temp.push_back(nums[j]);
        				temp.push_back(nums[start]);
        				temp.push_back(nums[end]);
        				res.push_back(temp);

        				temp.clear();

						//cout<<nums[i]<<","<<nums[j]<<","<<nums[start]<<","<<nums[end]<<endl;
						while(start<end&&nums[start]==nums[start+1]){//start移至
							start++;
						}
						while(end>start&&nums[end]==nums[end-1]){
							end--;
						}
						/*
						下方的做法，会将start和end都移到不同的数据上，实际上只需要有一个数不同就是新的组合，这样会漏掉
						很多组合的可能!!!因此只需要让end单独skip到一个新数即可

        				start++;
        				while(start<end&&nums[start]==nums[start-1]){
        					start++;
        				}
        				end--;
        				while(end>start&&nums[end]==nums[end+1]){
        					end--;
        				}
        				*/
        			}
        			if(sum<target){//这里不能使用else if，当target==sum时，会执行else段的逻辑
						
        				start++;
        			}
        			else{//sum>=target时执行，如果是==, 则之前的代码使start和end移到当前数的相等值最后一个index，
        				end--;//end再次--，使得end移至和之前数值不同的第一个index
        			}
        		}
        		while(j<size-2&&nums[j]==nums[j+1]){
        			j++;
        		}
        	}
        	while(i<size-3&&nums[i]==nums[i+1]){
        		i++;
        	}
        }
        return res;
    }
};

int main(){
	int a[]={-448,-448,-447,-402,-400,-385,-374,-372,-368,-359,-313,-303,-289,-281,-272,-213,-211,-189,-186,-181,-170,-156,-122,-117,-108,-107,-100,-97,-52,-22,-8,27,30,36,41,44,58,62,75,80,134,135,140,171,201,207,209,221,222,229,238,245,247,251,251,264,271,347,380,389,396,411,428,434,435,444,460,488,498};
    vector<int> num(a,a+69);
    int target=8934;
    Solution sol=Solution();
    sol.fourSum(num,target);
    return 0;
}
