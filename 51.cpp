#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
所有的Queen不能共存于同一行/同一列/同一斜线
算法思想：回溯法，每次在一行中选择1个位置放置Queen，若合法(列合法，斜线合法)则放置下一列；若不合法则直接回溯
使用vector<int> 存放Queen在每行中的列位置，再转换成vector<string>即可
class Solution {
public:
	vector<vector<int>> queen_pos;
    vector<vector<string>> solveNQueens(int n) {
    	vector<int> cur;
    	vector<vector<string>> res;
    	backtrace(0,n,cur);
    	convert(queen_pos,res,n);
    	return res;
    }

    void backtrace(int row,int n,vector<int> cur){//为第i行的Queen选择位置
    	if(row==n){
    		queen_pos.push_back(cur);
    	}
    	for(int i=0;i<n;i++){
    		cur.push_back(i);
    		if(check(cur)){//如果第row行在第j列放置的Queen位置合法，则放置下一行
    			backtrace(row+1,n,cur);
    		}
    		cur.pop_back();//reset本行对于Queen的放置
    	}
    }

    bool check(vector<int> cur){//cur[i]存放第i+1行中Queen的位置
    	int size=cur.size();
    	int location=cur[size-1];
    	for(int row=0;row<size-1;row++){//row遍历之前的0...size-2行中的Queen位置
    		if(cur[row]==location){//校验row处的Queen是否与location上的Queen处于同一列
    			return false;
    		}
    		//检测row处的Queen是否与location的Queen位于同一斜线上
    		//如果在斜线上，则|location-cur[row]| == |size-1-row|(位于同一斜线：即从size-1开始，每往上走一行，Queen或向左或向右偏移一格)
    		else if(abs(cur[row]-location) == abs(row-size+1)){
    			return false;
    		}
    	}
    	return true;
    }

    void convert(vector<vector<int>>& queen_pos,vector<vector<string>>& res,int n){
    	int i,j,k;
    	string row_str;
    	vector<string> temp;
    	for(i=0;i<queen_pos.size();i++){
    		temp.clear();
    		for(j=0;j<queen_pos[i].size();j++){
    			row_str="";
    			for(k=0;k<n;k++){
    				if(k==queen_pos[i][j]){
    					row_str+="Q";
    				}
    				else{
    					row_str+=".";
    				}
    			}
    			temp.push_back(row_str);
    		}
    		res.push_back(temp);
    	}
    }
};