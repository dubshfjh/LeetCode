#include <iostream>
#include <vector>
using namespce std;

对于每一层（记为层i），以(i,i)位置出发，向右到达(i,n-1-i)，向下到达(m-1-i,n-1-i)，向左到达(m-1-i,i)，再向上回到起点。
所有层次遍历完成后，即得到所求数组
注意：i==m-1-i 或者 i==n-1-i时，不要来回重复遍历。
在进行了"top--right"-->"bottom--right"之后，需要检测(m-i-1 > i)是否成立，若不成立则说明本次根本没有移动；若成立则执行下次移动："bottom--right"-->"bottom--left"
在进行了"bottom--right"-->"bottom--left"之后，需要检测(n-i-1 > i)是否成立，若不成立则说明本次根本没有移动；若成立则执行"bottom--left"-->"top--left"

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int i,j,m,n,layer;
        vector<int> res;
        m=matrix.size();
        if(m==0){
            return res;
        }
        n=matrix[0].size();
        layer=(min(m,n)+1)/2;
        
        for(i=0;i<layer;i++){//遍历每一层螺旋
        	//row固定为i,"top--left"-->"top-->right"
        	for(j=i;j<n-i;j++){
        		res.push_back(matrix[i][j]);
        	}

        	//col固定为n-i-1,"top--right"-->"bottom-->right"
        	for(j=i+1;j<m-i;j++){
        		res.push_back(matrix[j][n-i-1]);
        	}

        	//row固定为m-i-1,"bottom--right"-->"bottom--left"
        	if(m-i-1 > i){//检测previous 向下移动是否真正改变了行位置
        		for(j=n-i-1-1;j>=i;j--){
        			res.push_back(matrix[m-i-1][j]);
        		}
        	}

        	//col固定为i,"bottom--left"-->"top--left"
        	if(n-i-1 > i){//检测previous 向左移动是否真正改变了列位置
        		for(j=m-i-1-1;j>i;j--){
        			res.push_back(matrix[j][i]);
        		}
        	}
        }
        return res;
    }
};