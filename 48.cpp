#include <iostream>
#include <vector>
using namespace std;
本人思路：居然用了辅助变量...真心zz
本质上就是将matrix的第i列进行reverse后，作为新矩阵的第i行
matrix中==>col:0...n-1；对于每个col取值,row:0...n-1
新temp中==>row:0...n-1：对于每个row取值,col:0...n-1

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int row,col,size;
        size=matrix.size();
        vector<vector<int>> temp;
        
        for(col=0;col<size;col++){
	      	vector<int> newrow;
        	for(row=size-1;row>=0;row--){
        		newrow.push_back(matrix[row][col]);
        	}
        	temp.push_back(newrow);
        }
        
        matrix.clear();
        matrix.assign(temp.begin(),temp.end());
    }
};

便捷思路：通过两个步骤的元素交换可实现目标：
1.按照主对角线，将对称元素交换(即行列交换)
2.按照列，将对称列元素全部交换(即对新matrix每行元素的reverse)
即可达到，使得二维矩阵，本地旋转90个角度。

class Solution{
public:
	void rotate(vector<vector<int>>& matrix){
		int i,j,size;
		size=matrix.size();
		if(size==0){
			return;
		}
		//沿着主对角线交换元素
		for(i=0;i<size;i++){
			for(j=0;j<=i;j++){
				swap(matrix[i][j],matrix[j][i]);
			}
		}
		//对每一行的元素进行reverse
		for(k=0;k<size;k++){
			for(i=0,j=size-1;i<j;i++,j--){
				swap(matrix[k][i],matrix[k][j]);
			}
		}
		
	}
}