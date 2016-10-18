#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//借鉴0-1背包问题的回溯法思想，每个数字可选取多次。个人对结果不重复的理解：只要在回溯的每一层，对每个元素的使用次数(0-n)都只尝试一遍即可


class Solution {
public:
	vector<vector<int>> res;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    	vector<int> temp;
    	sort(candidates.begin(),candidates.end());
        getnumber(0,0,target,temp,candidates);
        reverse(res.begin(),res.end());
        return res;
    }

    void getnumber(int index,int sum,int target,vector<int> temp,vector<int>& candidates){//分析加入0-n个candicates[index]
    	int i,j,exist;//sum存储了对上一个元素的添加次数分析之后，得到的数字之和
    	//cout<<index<<":"<<candidates[index]<<",,,sum:"<<sum<<endl;
    	while(candidates[index]==candidates[index+1]&&index<candidates.size()-1){
    		index++;
    	}
    	if(sum>=target){//因为target是上一层的元素之和，所以当分析到index==size时，不能直接return，而是应该先判断是否==target!!!
    		if(sum==target){
    		    for(i=0;i<temp.size();i++){
    		        cout<<temp[i]<<"...";
    		    }
    		    cout<<endl;
    			res.push_back(temp);
    		}
    		return;
    	}
    	if(index>=candidates.size()){//本段代码必须在if(sum>=target)之后，否则在input:[2,3,6,7],target=7这种情况下，会漏掉[7]这个解
    		return;
    	}
    	else{
    		exist=target-sum;
    		//cout<<"exist: "<<exist<<",,,times: "<<exist/candidates[index]<<endl;
    		for(i=0;i<=exist/candidates[index];i++){
    			if(i==0){
    				getnumber(index+1,sum,target,temp,candidates);
    			}
    			else{
    				temp.push_back(candidates[index]);
    				getnumber(index+1,sum+i*candidates[index],target,temp,candidates);
    			}    			
    		}
    		for(j=0;j<i;j++){
    			temp.pop_back();
    		}
    		return;
    	}
    }
};

int main(){
    int a[]={6,3,1,2,1};
    int target=3;
    vector<vector<int>> res;
    vector<int> num(a,a+5);
    Solution sol=Solution();
    res=sol.combinationSum(num,target);
    for(int i=0;i<res.size();i++){
    	for(int j=0;j<res[i].size();j++){
    		cout<<res[i][j];
    	}
    	cout<<endl;
    }
    return 0;
}
