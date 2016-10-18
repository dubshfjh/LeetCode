#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int i,j,size,cur_reach,nextstart,maxdis;
        i=cur_reach=0;
        size=nums.size();
        while(i<=cur_reach && cur_reach<size){//cur_reach记录了之前每轮节点最远延伸范围的max值
        	if(cur_reach>=size-1){
        		return true;
        	}
        	if(nums[i]==0){//在分析上一步的i时，在[i+1,...,curReach]这个范围内，找到的最远延伸点[nextstart]取值也为0
        		return false;
        	}
        	if(cur_reach <= i+nums[i]){//尝试更新当前的curReach，这时必须是"<="而非"<"，以应对上一轮中选取了新节点的情况
        		cur_reach=i+nums[i];
        	}

        	nextstart=i+1;//nextstart：应该取能达到范围之内的延伸最远的点
        	maxdis=0;
        	for(j=i+1;j<=cur_reach && j<size;j++){
        		if(j+nums[j] > maxdis){//maxdis存放了本轮节点的最远延伸范围
        			nextstart=j;
        			maxdis=j+nums[j];
        		}
        	}
        	i=nextstart;
        }
        return false;
    }
};

class Solution {
public:
    bool canJump(vector<int>& nums) {
    	int i,distance,nextdis,size;
    	size=nums.size();
    	distance=nums[0];
    	while(distance<size-1){
    		nextdis = distance;
    		while(i<size && i<=distance){
    			nextdis=max(nextdis,i+nums[i]);
    			i++;
    		}

    		if(nextdis<=distance){
    			return false;
    		}
    		distance=nextdis;
    	}
    	return true;
    }
};
