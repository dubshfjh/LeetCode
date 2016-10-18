#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int i,row,col,layer;
        vector<int> temp(n,0);
        vector<vector<int>> res(n,temp);
        i=1;
        layer=0;
        while(layer<(n+1)/2){
        	//top-left-->top-right
        	row=layer;
        	for(col=layer;col<n-layer;col++){//只要没进入最后一层，则这次移动必然存在
        		res[row][col]=i;
        		i++;
        	}

        	//top-right-->bottom-right
        	col=n-layer-1;
        	for(row=layer+1;row<n-layer;row++){
        		res[row][col]=i;
        		i++;
        	}

        	//bottom-right-->bottom-left
        	if(n-layer-1 > layer){//检测上一步是否真正地进行了下移(即画出本层的第1个新列)
        		row=n-layer-1;
        		for(col=n-layer-1-1;col>=layer;col--){
        			res[row][col]=i;
        			i++;
        		}
        	}

        	//bottom-left-->top-left
        	if(n-layer-1 > layer){//检测上一步是否真正地进行了左移(即画出本层的第2个新行)
        		col=layer;
        		for(row=n-layer-1-1;row>layer;row--){
        			res[row][col]=i;
        			i++;
        		}
        	}//由于最后一层中的bottom-left-->top-left已经没有未访问过的元素(即必然不会再移动)，所以不需要再额外判断该步是否未移动
        	layer++;
        }
        return res;
    }
};