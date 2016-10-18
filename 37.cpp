#include <iostream>
#include <vector>
#include <string>
using namespace std; 
//采用回溯法，结合36中的行访问数组，列已访问数组和9宫格已访问数组
class Solution {
public:
	vector<vector<char>> temp_board;
    void solveSudoku(vector<vector<char>>& board) {
    	int row,col,num,size_1,size_2,board_num,total_board;
    	size_1=board.size();
        size_2=board[0].size();

    	vector<int> temp(10,0);

        vector<vector<int>> row_visit(size_1,temp);
        vector<vector<int>> col_visit(size_2,temp);

        total_board=(size_1/3*size_2/3);//3行3列：1个；3行6列：2个；6行3列：2个....
        vector<vector<int>> board_visit(total_board,temp);

        for(row=0;row<size_1;row++){
        	for(col=0;col<size_2;col++){
        		if(board[row][col]>='0' && board[row][col]<='9'){
        			num=board[row][col]-'0';
        			row_visit[row][num]=1;
        			col_visit[col][num]=1;
        			board_num=(row/3*size_2/3)+col/3;
        			board_visit[board_num][num]=1;
        		}
        		
        	}
        }

        fillboard(0,0,board,row_visit,col_visit,board_visit);
        board.clear();//清洗原棋盘，这很重要
        for(int i=0;i<temp_board.size();i++){
        	board.push_back(temp_board[i]);
        }
        //board.assign(temp_board.begin(),temp_board.end());

    }

    void fillboard(int row,int col,vector<vector<char>>& board,vector<vector<int>>& row_visit,vector<vector<int>>& col_visit,vector<vector<int>>& board_visit){
    	int size_1,size_2;
    	vector<int> valid;
    	size_1=board.size();
        size_2=board[0].size();
		//cout<<row<<",,,"<<col<<endl;
    	if(row==size_1&&col==0){//当递归运行到第row+1行第0列时，递归终止，记录当前棋盘
    		temp_board.clear();
    		for(int i=0;i<size_1;i++){
    			temp_board.push_back(board[i]);
    			for(int j=0;j<size_2;j++){
    				cout<<board[i][j];
    			}
    			cout<<endl;
    		}
    		
    		return;
    	}
    	if(board[row][col]=='.'){//只对当前尚未填数字的空格分析
    		valid=valid_num(row,col,board,row_visit,col_visit,board_visit);//获取当前空格的可填数
	    	if(valid.size()>0){
	    		for(int i=0;i<valid.size();i++){
    				board[row][col]=valid[i]+'0';
    				//cout<<board[row][col]<<endl;
	    			if(col==size_2-1){//如果为本行的最后一个格子，则下次填写第row+1行的第0个格子
	    				fillboard(row+1,0,board,row_visit,col_visit,board_visit);
	    			}
	    			else{//无需换到下一行时，直接填写第col+1个格子
	    				fillboard(row,col+1,board,row_visit,col_visit,board_visit);
	    			}
	    		}
	    		board[row][col]='.';//回溯到上一个格子时，将当前格子的数字重置为空
	    		return;
	    	}
	    	else{//如果本格子无可填数，则直接回溯！！！
	    	    //cout<<"lalalalalalalalalalallllllllllllllllllllll"<<endl;
	    		return;
	    	}
    	} 
    	else if(board[row][col]>='0'&&board[row][col]<='9'){//如果当前格子并不为空(即初始board在本格子已经填写了数字)，则直接填写下一个格子
    	    if(col==size_2-1){//之前脑残了，根本没对非空格字分析，直接GG
    	        fillboard(row+1,0,board,row_visit,col_visit,board_visit);
    	    }
    	    else{
    	        fillboard(row,col+1,board,row_visit,col_visit,board_visit);
    	    }
    	}
    }

    vector<int> valid_num(int row,int col,vector<vector<char>>& board,vector<vector<int>>& row_visit,vector<vector<int>>& col_visit,vector<vector<int>>& board_visit){
    	int i,j,num,size_1,size_2,board_num,row_limit,col_limit;
    	vector<int> res;
        //cout<<row<<",,,"<<col<<endl;
    	size_1=board.size();
        size_2=board[0].size();
    	board_num=(row/3)*(size_2/3)+col/3;
        //cout<<board_num<<endl;
    	vector<int> temp(10,0);//因为每次分析同一个格子的可填数时，在它之前的格子中的数字是动态变化的，
    						  //所以每次都需要更新行已访问数字、列已访问数字和9宫格已访问数字
        //直接row_visit[row]=temp也行
        row_visit[row].assign(temp.begin(),temp.end());
        col_visit[col].assign(temp.begin(),temp.end());
        board_visit[board_num].assign(temp.begin(),temp.end());

    	for(i=0;i<size_2;i++){//更新第row行的访问数据
    		if(board[row][i]>='0' && board[row][i]<='9'){
    			num=board[row][i]-'0';
    			row_visit[row][num]=1;
    		}
    	}
		// for(i=0;i<row_visit[row].size();i++){
  //           if(!row_visit[row][i]){
  //               cout<<i<<"..row..";
  //           }
  //       }
  //       cout<<endl;

		
    	for(i=0;i<size_1;i++){//更新第col列的访问数据
    		if(board[i][col]>='0' && board[i][col]<='9'){
    			num=board[i][col]-'0';
    			col_visit[col][num]=1;
    		}
    	}
        // for(i=0;i<col_visit[col].size();i++){
        //     if(!col_visit[col][i]){
        //         cout<<i<<"..col..";
        //     }
        // }
        // cout<<endl;
        
    	row_limit=(row/3)*3;//当前9宫格行范围：row_limit  --  row_limit+2
    	col_limit=(col/3)*3;//当前9宫格列范围：col_limit  --  col_limit+2
    	for(i=row_limit;i<row_limit+3;i++){//更新board[row][col]所属九宫格的访问数据
    		for(j=col_limit;j<col_limit+3;j++){
    			if(board[i][j]>='0' && board[i][j]<='9'){
    				num=board[i][j]-'0';
    				board_visit[board_num][num]=1;
    			}
    		}
    	}
	
	    	// for(i=0;i<board_visit[board_num].size();i++){
	    	//     if(!board_visit[board_num][i]){
	    	//         cout<<i<<",,,";
	    	//     }
	    	// }
	    	// cout<<endl;
    	
    	for(int i=1;i<=9;i++){
    		if(!row_visit[row][i] && !col_visit[col][i] &&!board_visit[board_num][i]){
    		    //cout<<i;
    			res.push_back(i);
    		}
    	}
		//cout<<endl;
    	return res;
    }
};