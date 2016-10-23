#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row,col,low,high,mid;
        row=matrix.size();
        if(row==0){
        	return false;
        }
        col=matrix[0].size();
        if(col==0){
        	return false;
        }

        low=0;
        high=row-1;
        while(low<=high){//类比为寻找插入位置的二分搜索
        	mid=(low+high)/2;
        	cout<<low<<",,,"<<high<<",,,"<<matrix[mid][0]<<endl;
        	if(matrix[mid][0]>=target){//如果[mid] >= target，则high左移，因此high将为最后一个<target的数
        		high=mid-1;
        	}
        	else{//[mid] < target，则low右移，因此low将成为第一个 >=target的数
        		low=mid+1;
        	}
        }

        if(low<row && matrix[low][0]==target){
        	return true;
        }
       	else if(high<0){
       		return false;
       	}
       	else{
       		row=high;
       	}

        low=0;
        high=col-1;
        while(low<=high){//试图搜索已存在数字的标准二分搜索
        	mid=(low+high)/2;
        	if(matrix[row][mid]<target){
        		low=mid+1;
        	}
        	else if(matrix[row][mid]>target){
        		high=mid-1;
        	}
        	else{
        		return true;
        	}
        }
        return  false;
    }
};


int main(){
    vector<vector<int>> matrix;

    int a[]={1,3,5,7};
    vector<int> temp(a,a+4);
    matrix.push_back(temp);

    int b[]={10,11,16,20};
    vector<int> temp_1(b,b+4);
    matrix.push_back(temp_1);

    int c[]={23,30,34,50};
    vector<int> temp_2(c,c+4);
    matrix.push_back(temp_2);

    Solution sol=Solution();
    sol.searchMatrix(matrix,6);

    return 0;
}
