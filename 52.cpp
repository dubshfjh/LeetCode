#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int res=0;
    int totalNQueens(int n){
    	vector<int> cur;
    	backtrace(cur,0,n);
    	return res;
    }

    void backtrace(vector<int> cur,int row,int n){
    	if(row==n){
    		res++;
    	}
    	for(int i=0;i<n;i++){
    		cur.push_back(i);
    		if(check(cur)){
    			backtrace(cur,row+1,n);
    		}
    		cur.pop_back();
    	}
    }

    bool check(vector<int> cur){
    	int size=cur.size();
    	int location=cur[size-1];
    	for(int row=0;row<size-1;row++){
    		if(cur[row]==location){
    			return false;
    		}
    		if(abs(cur[row]-location) == abs(row-size+1)){
    			return false;
    		}
    	}
    	return true;
    }
};