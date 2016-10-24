/*
之前的代码只分析了当pre向下走到cur时，cur不能往回走这一种情况
在下面的例子中，会出现 1->4->7->8->5->2->1这种使用旧节点的情况，谬误
应该记录已访问节点的下标index = row*col_num + col
1	2	3
4	5	6
7	8	9
递归算法遇到较长的test case出现Time Limit Exceed，需要考虑迭代实现
 */
本算法超时！！！！！只需要在移动时加入判断：下一个节点是否等于next字符即可
class Solution {
public:
	bool existflag;
    bool exist(vector<vector<char>>& board, string word) {
    	int nodenum;
    	string path="";
        existflag=false;
    	nodenum=board.size()*board[0].size();
    	vector<int> visited(nodenum,0);
    	cout<<word.size()<<endl;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                // cout<<"i: "<<i<<",,,j:"<<j<<endl;
                backtrace(board,path,word,i,j,visited);
            }
        }
        return existflag;
    }

    void backtrace(vector<vector<char>>& board,string path,string word,int row,int col,vector<int> visited){
    	int nodeindex,nextindex;
    	int index=path.size();//每次尝试添加与word相匹配的[row][col]节点，再尝试从上，下，左，右添加相邻元素
        
        // if(row==board.size() || col==board[0].size()){
        //     return;
        // }
    	if(board[row][col]==word[index]){
    		path=path+board[row][col];
    		nodeindex = row*board[0].size()+col;
    	    cout<<path.size()<<endl;
    		visited[nodeindex]=1;
    		if(path.size()==word.size()){//必须在添加了本层的适配元素后，再校验，否则当只有1个元素时，无法进行“上/下/左/右”的任何移动，结果错误
	    		existflag=true;
	    		return;
	    	}
    		if(row>0){//如果从pre节点不是朝下走到cur节点 && pre节点未在之前访问过，则本节点可以向(此时向上，将使用2次pre元素，error!)
		    	nextindex = nodeindex-board[0].size();
		    	if(visited[nextindex]==0 && board[row-1][col]==word[index+1]){//只在下一个字符匹配时，进行移动
    				backtrace(board,path,word,row-1,col,visited);
    			}
    		}

    		if(row<board.size()-1){//如果从pre节点不是向上走到cur节点 &&...，则本节点可以朝下走
	    		nextindex = nodeindex+board[0].size();
	    		if(visited[nextindex]==0 && board[row+1][col]==word[index+1]){
	    			backtrace(board,path,word,row+1,col,visited);
	    		}
    		}

    		if(col>0){//如果从pre节点不是向右走到cur节点 &&...，则本节点可以朝左走
    			nextindex=nodeindex-1;
    			if(visited[nextindex]==0 && board[row][col-1]==word[index+1]){
     				backtrace(board,path,word,row,col-1,visited);   				
    			}
    		}
    		if(col<board[row].size()-1){//如果从pre节点不是向左走到cur节点 &&...，则本节点可以朝右走
    			nextindex=nodeindex+1;
    			if(visited[nextindex]==0 && board[row][col+1]==word[index+1]){
     				backtrace(board,path,word,row,col+1,visited);   				
    			}
    		}
    	}
    	else{
    		return;
    	}
    }
};


核心思想如下：1.将已访问节点置为'*'  2.用栈替代递归

用栈记录当前搜索的路径。

栈存放的节点包括4个成员： 字符c, x,y坐标，已遍历方向p。

注意p在回溯法中是非常重要的，用来记录已遍历过的方向（按照上下左右的顺序），不然的话就会出现无限循环的同一节点进栈出栈。

进栈之后的节点置为'*'，以免同一节点多次进栈。

出栈之后的节点恢复为word[wind]。

struct Node{
	char c;//字符
	int x;//行坐标
	int y;//列坐标
	int postion;//下一次尝试的方向,0-up; 1-down; 2-left; 3-right
	Node(char newc,int newx,int newy,int newpos):c(newc),x(newx),y(newy),postion(newpos){}
};

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty() || board[0].size()==0){
        	return false;
        }

        int m=board.size();
        int n=board[0].size();
        for(int i=0;i<m;i++){//从每个[i][j]节点出发，尝试添加其邻居节点
        	for(int j=0;j<n;j++){
        		if(board[i][j] == word[0]){//尝试可能成功的case
        			stack<Node> mystk;
        			Node curNode(word[0],i,j,0);
        			board[curNode.x][curNode.y]='*';
        			mystk.push(curNode);
        			

        			//Node topnode=mystk.top(); Attention：栈的顶部是动态变化的，绝对不能用这个辣鸡topnode变量提前算好，只能够每次使用mystk.top()临时获取
        			//一大堆Wrong Answer都是因为自己脑残到设置了这个变量
        			int wordindex=1;
        			if(wordindex == word.size()){
        				return true;
        			}

        			while(!mystk.empty()){
        				if(mystk.top().postion == 0){//本次向上
        					mystk.top().postion=1;//标记下次应该向下
        					if(mystk.top().x>0 && board[mystk.top().x-1][mystk.top().y] == word[wordindex]){
            				// 	cout<<"Up,";
        						Node nextnode(word[wordindex],mystk.top().x-1,mystk.top().y,0);
        						mystk.push(nextnode);
        						board[nextnode.x][nextnode.y]='*';//'*'不可能再与word中的任何字符匹配了，保证该节点不会重复进栈
        						wordindex++;
        						if(wordindex == word.size()){
        							return true;
        						}
        						continue;
        					}
        				}

        				if(mystk.top().postion == 1){//本次向下
        					mystk.top().postion=2;//标记下次向左
        					if(mystk.top().x<m-1 && board[mystk.top().x+1][mystk.top().y] == word[wordindex]){
            				// 	cout<<"Down,";
        						Node nextnode(word[wordindex],mystk.top().x+1,mystk.top().y,0);
        						mystk.push(nextnode);
        						board[nextnode.x][nextnode.y]='*';
        						wordindex++;
        						if(wordindex==word.size()){
        							return true;
        						}
        						continue;
        					}
        				}

        				if(mystk.top().postion == 2){//本次向左
        					mystk.top().postion=3;//标记下次向右
        					if(mystk.top().y>0 && board[mystk.top().x][mystk.top().y-1] == word[wordindex]){
            				// 	cout<<"left,";
        						Node nextnode(word[wordindex],mystk.top().x,mystk.top().y-1,0);
        						mystk.push(nextnode);
        						board[nextnode.x][nextnode.y]='*';
        						wordindex++;
        						if(wordindex==word.size()){
        							return true;
        						}
        						continue;
        					}
        				}

        				if(mystk.top().postion == 3){//本次向右
        					mystk.top().postion=4;
        					if(mystk.top().y<n-1 && board[mystk.top().x][mystk.top().y+1] == word[wordindex]){
            				// 	cout<<"right,";
        						Node nextnode(word[wordindex],mystk.top().x,mystk.top().y+1,0);
        						mystk.push(nextnode);
        						board[nextnode.x][nextnode.y]='*';
        						wordindex++;
        						if(wordindex==word.size()){
        							return true;
        						}
        						continue;
        					}
        				}
                        
                        // topnode=mystk.top();
                        // board[topnode.x][topnode.y]=topnode.c;
                        board[mystk.top().x][mystk.top().y] = mystk.top().c;
                        mystk.pop();
                        wordindex--;
        			}
        		}
        	}
        }
        return false;
    }
};