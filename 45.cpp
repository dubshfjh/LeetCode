#include <iostream>
#include <vector>
#include <algorrithm>
using namespace std; 

贪心法：每次都选择能够延伸到最远范围的点作为nextstart，然后分析该点所能到达范围内的最远延伸点
//curReach:从nums[0]开始进行了length次跳跃后，能够达到的最大范围

class Solution {
public:
    int jump(vector<int>& nums) {
	    int nextstart,maxdis;
    	int i,j,length,size,curReach;
    	i=curReach=length=0;
    	size=nums.size();
    	if(size<=1){
    		return 0;
    	}
    	while(i<=curReach && curReach<=size-1){//curReach记录了之前每轮节点最远延伸范围的max值
    		if(curReach>=size-1){
    			return length;
    		}
    		if(nums[i]==0){//在分析上一步的i时，在[i+1,...,curReach]这个范围内，找到的最远延伸点取值也为0
    			return -1;
    		}
    		if(curReach<=i+nums[i]){//尝试更新当前的curReach，这时必须是"<="而非"<"，以应对上一轮中选取了新节点的情况
    			curReach=i+nums[i];
	            length++;
    		}
    		nextstart=i+1;//nextstart：应该取能达到范围之内的延伸最远的点
    		maxdis=0;
    		for(j=i+1;j<=curReach;j++){//maxdis存放了本轮节点的最远延伸范围
    			if(maxdis<j+nums[j]){
    				nextstart=j;
    				maxdis=j+nums[j];
    			}
    		}

    		i=nextstart;
    	}
    	return length;
    }
  
};

class Solution{
public:
	int jump(vector<int>& nums){
		int i,j,size,step,distance,nextdis;
		size=nums.size();
		distance=nums[0];
		i=step=0;
		while(distance<size-1){//本层的distance:上一层的i所能延伸的最长距离，如果从上一层再跳一次就可以>=size，则结果应该为step+1
			step++;
			nextdis=distance;
			while(i<size && i<=distance){
				nextdis=max(nextdis,nums[i]+i);
				i++;
			}

			if(nextdis<=distance){
				return -1;
			}
			distance=nextdis;
		}
		return step+1;
	}
};