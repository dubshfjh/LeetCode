#include <iostream>
#include <vector>
#include <map>
using namespace std;

算法错误，当输入为[1,2]时，容器中水的高度应该可以达到1
/*
class Solution {
public:
    int maxArea(vector<int>& height) {
        int i,temparea,temp;
        map<int,int> lastindex;
        for(i=0;i<height.size();i++){
        	if(lastindex.count(height[i])==0){
        		lastindex.insert(pair<int,int>(height,i));
        	}
        	else{
        		lastindex[height[i]]=i;
        	}
        }
        temparea=0;
        for(i=0;i<height.size();i++){
        	temp=height[i]*(lastindex[height[i]]-i);
        	if(temp>temparea){
        		temparea=temp;
        		cout<<temp<<endl;
        	}
        }
        return temparea;
    }
};
*/
没必要引入中间节点，这样会再次增加运行时间！！！
本次思想：寻找每个height[i]可能构成的最大面积，然后取最大值
/*
class Solution {
public:
    int maxArea(vector<int>& height) {
        int i,temparea,temp,left,right;
        temparea=0;
        for(i=0;i<height.size();i++){
        	left=0;
        	right=height.size()-1;
        	while(height[left]<height[i]&&left<i){
        		left++;
        	}
        	while(height[right]<height[i]&&right>i){
        		right++;
        	}
        	temp=max(height[i]*(i-left),height[i]*(right-i));
        	temparea=max(temparea,temp);
        }
        return temparea;
    }
};
*/


直接判断所有left和right构成的容器面积，每次只需寻找可能更大的面积即可
class Solution {
public:
    int maxArea(vector<int>& height) {
        int i,temparea,temp,left,right;
        temparea=0;
        left=0;
        right=height.size()-1;
        while(left!=right){
        	temparea=max(temparea,(right-left)*min(height[left],height[right]));
        	if(height[left]<height[right]){//左侧容器边较低，此时不管右侧边的长度是多少，容器体积最大值都不会超过目前的值
        		left++;//left右移，试图找到更的的容器
        	}
        	else{
        		right--;
        	}
        }
        return temparea;
    }
};