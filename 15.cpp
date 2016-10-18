#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

代码超时！实际上是因为没考虑输入为空的情况！而且2个map简直浪费到爆炸！
直接排序后，采用跳过相同数字的方式就能避免map的使用
/*
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums){
    	int start,end,temp;
    	map<int,int> num_index,visited;
        vector<int> vec;
        vector<vector<int>> res;
        for(int i=0;i<nums.size();i++){
        	if(num_index.count(nums[i])>0){
        		num_index[nums[i]]=num_index[nums[i]]+1;
        		//cout<<num_index[nums[i]]<<endl;
        	}
        	else{
        		num_index.insert(pair<int,int>(nums[i],1));
        	}
        }
        for(start=0;start<nums.size()-1;start++){
        	end=nums.size()-1;
			while(start<end){
	        	temp=0-nums[start]-nums[end];
	        	if(num_index.count(temp)>0){
	        	    if(visited.count(nums[start])==0||visited.count(nums[end])==0||visited.count(temp)==0){
	        	        if(visited.count(nums[start])==0){
	        	            visited.insert(pair<int,int>(nums[start],1));

	        	        }
	        	        if(visited.count(nums[end])==0){
	        	            visited.insert(pair<int,int>(nums[end],1));
	        	            
	        	        }
	        	        if(visited.count(temp)==0){
	        	            visited.insert(pair<int,int>(temp,1));
	        	            
	        	        }
	        	        if(temp==nums[start]||temp==nums[end]){
	        	            if(num_index[temp]>1){
	        	                vec.clear();	
                    			vec.push_back(nums[start]);
                    			vec.push_back(nums[end]);
                    			vec.push_back(temp);
                    			sort(vec.begin(),vec.end());
                    			res.push_back(vec);
	        	            }
	        	        }
	        	        else{
	        	            vec.clear();	
                			vec.push_back(nums[start]);
                			vec.push_back(nums[end]);
                			vec.push_back(temp);
                			sort(vec.begin(),vec.end());
                			res.push_back(vec);
	        	        }
            			
	        	    }
	        	}
	        	end--;
			}
        }
        return res;
    }
};
*/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums){
    	int i,start,end,sum;
    	sort(nums.begin(),nums.end());
    	vector<vector<int>> res;
    	vector<int> temp;
    	for(i=0;i<nums.size();i++){
    		while(i>0&&i<nums.size()&&nums[i]==nums[i-1]){
    			i++;
    		}
    		start=i+1;
    		end=nums.size()-1;
    		while(start<end){//如果i到达了size-1的位置，则start>end，不会再进入本层循环
    			sum=nums[i]+nums[start]+nums[end];
    			if(sum==0){
    				temp.clear();
    				temp.push_back(nums[i]);
    				temp.push_back(nums[start]);
    				temp.push_back(nums[end]);
    				res.push_back(temp);

    				start++;//start++后必然会切换到不同的数
    				end--;
    				while(start<end&&nums[start]==nums[start-1]){//此时的start-1为上次所取值的最后一个数，右移到本次的最后一个
    					start++;
    				}

    				while(end>start&&nums[end]==nums[end+1]){
    					end--;
    				}
    			}
    			else if(sum<0){
    				start++;
    				while(start<end&&nums[start]==nums[start-1]){//第一次的start-1仍然为导致sum<0的取值，需要skip掉这个值，尝试下一个较大的数
    					start++;
    				}
    			}
    			else{
    				end--;
    				while(end>start&&nums[end]==nums[end+1]){
    					end--;
    				}
    			}
    		}
    	}
    	return res;
    }
};

int main(){
    vector<int> num(-1,0,1,2,-1,-4);

    Solution sol=Solution();
    sol.threeSum(num);
    return 0;
}

