/*
[[0,1,0,1],[1,1,1,1],[0,1,34,5],[5,2,1,5]]
[[0,0,0,0],[0,1,0,1],[0,0,0,0],[0,2,0,5]]
*/
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int i,j,m,n;
        m=matrix.size();
        if(m>0){
            n=matrix[0].size();
            vector<int> row_visit(m,0);
            vector<int> col_visit(n,0);
            for(i=0;i<m;i++){
            	for(j=0;j<n;j++){
            		if(matrix[i][j]==0){
            			row_visit[i]=1;//记录本行需要置0
            			col_visit[j]=1;//记录本列需要置0
            		}
            	}
            }
    		
		    vector<int> exist_row;//exist_row记录在置行为0时未被修改的行数，从而在置某i列为0时只对那些未被set 0 的行操作，
            for(i=0;i<m;i++){//当出现大量的0时，可以避免对节点多次置0
            	if(row_visit[i]==1){
            		for(j=0;j<n;j++){
            			matrix[i][j]=0;
            		}
            	}
            	else{
            		exist_row.push_back(i);
            	}
            }
    		

            for(i=0;i<n;i++){
            	if(col_visit[i]==1){
        			for(j=0;j<exist_row.size();j++){
        				matrix[exist_row[j]][i]=0;
        			}
            	}
            }
        }
    }
};


Constant Space:
常数空间的话，第一可以考虑是不是固定数量的几个变量能搞定；否则可以考虑是不是问题本身已经提供了足够的空间。
这道题属于后者，就是利用矩阵的第一行和第一列来作为辅助空间使用。不用开辟新的存储空间。方法就是：
1.先确定第一行和第一列是否需要清零
即，看看第一行中是否有0，记下来。也同时记下来第一列中有没有0。因为循环结束后若matrix[0][i]==0，则意味着第i+1列中存在某个为0的元素，因此没有变量
记录第0行本身是否需要清零

2.扫描剩下的矩阵元素，如果遇到了0，就将对应的第一行和第一列上的元素赋值为0
这里不用担心会将本来第一行或第一列的1改成了0，因为这些值最后注定要成为0的，比如matrix[i][j]==0，那么matrix[i][0]处在第i行，matrix[0][j]处于第j列，最后都要设置为0的。

3.根据第一行和第一列的信息，已经可以将剩下的矩阵元素赋值为结果所需的值了即，拿第一行为例，如果扫描到一个0，就将这一列都清0.

4.根据1中确定的状态，处理第一行和第一列。
如果最开始得到的第一行中有0的话，就整行清零。同理对列进行处理。

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
    	int i,j,row,col;
    	row=matrix.size();
    	if(row==0){
    		return;
    	}
    	col=matrix[0].size();
    	if(col==0){
    		return;
    	}

    	bool first_row_zero,first_col_zero;
    	for(i=0;i<col;i++){
    		if(matrix[0][i]==0){
    			first_row_zero=true;
    			break;
    		}
    	}

    	for(i=0;i<row;i++){
    		if(matrix[i][0]==0){
    			first_col_zero=true;
    			break;
    		}
    	}

    	for(i=1;i<row;i++){
    		for(j=1;j<col;j++){
    			if(matrix[i][j]==0){
    				matrix[0][j]=0;//设置同列第0行的元素为0，记录应清零第j列
    				matrix[i][0]=0;//设置同行第0列的元素为0，记录应清零第i行
    			}
    		}
    	}
    	/* 存在更优化的清空第i列和第i行的做法
    	for(i=0;i<col;i++){
    		if(matrix[0][i]==0){//清零第i列
    			for(j=1;j<row;j++){
    				matrix[j][i]=0;
    			}
    		}
    	}

    	for(i=0;i<row;i++){
    		if(matrix[i][0]==0){//清零第i行
    			for(j=1;j<col;j++){
    				matrix[i][j]=0;
    			}
    		}
    	}
    	*/
    
    	for(i=1;i<row;i++){
    		for(j=1;j<col;j++){
    			if(matrix[0][j]==0 || matrix[i][0]==0){//如果位于第0行同列的元素为0 or位于第0列同行的元素为0，则设置本元素为0
    				matrix[i][j]=0;
    			}
    		}
    	}

    	if(first_row_zero){
    		for(i=0;i<col;i++){
    			matrix[0][i]=0;
    		}
    	}

    	if(first_col_zero){
    		for(i=0;i<row;i++){
    			matrix[i][0]=0;
    		}
    	}
    }
};