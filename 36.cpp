#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board){
    	int row,col,num,size,size_1,total_board,board_num;
        vector<char> temp;
        vector<vector<int>> row_visit,col_visit;//存放每行每列对于1-9的访问
        vector<vector<int>> board_visit;//存放每个九宫格对于1-9的访问
        size_1=board.size();
        size=board[0].size();
        if(size_1%3!=0){
        	return false;
        }

        for(int i=0;i<size_1;i++){
        	vector<int> visit(10,0);
        	row_visit.push_back(visit);
        	col_visit.push_back(visit);
        }
        total_board=size_1/3*(size/3);//total_board就是总共的9宫格数目
        for(int i=0;i<total_board;i++){//九宫格的个数下标范围{0,1,2...total_board}
        	vector<int> visit(10,0);
        	board_visit.push_back(visit);
        }

        row=col=board_num=0;
        while(row<size_1){//检测9宫格是否存在重复
        	//cout<<"size is:"<<size_1<<endl;
        	while(col<size){
        		board_num=(row/3)*(size/3)+(col/3);//计算第row+1行，第col+1列位于第几个九宫格。eg: 第0行第2列位于第0个9宫格；第3行第0列位于((3/3*size)+0)个九宫格
           		//cout<<"row is: "<<row<<",,,col is: "<<col<<",,,num: "<<board[row][col]<<endl;
 		       	if(board[row][col]=='.'){
 		       		col++;
 		       	}
 		       	else if(board[row][col]>='0'&&board[row][col]<='9'){
 		       		num=board[row][col]-'0';
 			        //cout<<board_visit[board_num][num]<<",,,"<<row_visit[row][num]<<",,,"<<col_visit[col][num]<<endl;
	        		if(!board_visit[board_num][num] && !row_visit[row][num] && !col_visit[col][num]){
	        			board_visit[board_num][num]=1;
	        			row_visit[row][num]=1;
	        			col_visit[col][num]=1;
	        			col++;
	        		}
	        		else{
	        			//cout<<"111111"<<endl;
	        			return false;
	        		}
 		       	}
 		       	else{
 		       		//cout<<"22222"<<endl;
 		       		return false;
 		       	} 		       	
        	}
        	col=0;
        	row++;
        }
        return true;
    }
};

int main(){
	int res;
    string a[]={".87654321","2........","3........","4........","5........","6........","7........","8........","9........"};
    vector<vector<char>> nums;
    for(int i=0;i<9;i++){
    	vector<char> temp;
    	for(int j=0;j<a[i].size();j++){
    		temp.push_back(a[i][j]);
    	}
   	    nums.push_back(temp);
    }
    
    Solution sol=Solution();
    res=sol.isValidSudoku(nums);
    cout<<res<<endl;
    return 0;
}
