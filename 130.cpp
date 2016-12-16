算法超时！！！这是因为当遇到符号'X'时也执行了递归，完全没有意义，连200*200的测试用例都超时

思想（其实根本没理解题意）：设置一个2维bool数组，用于保存每个格子是否处于“被包围”状态。递归地遵循“右移到本行末尾，下移到下一行的开头”的顺序移动分析每个格子。
如果格子为'X'：则包围状态设置为“false”；如果格子为'O'：如果格子处于边界则包围状态设置为“false”，否则包围状态设置为"左邻居被包围 && 右邻居被包围 && 上邻居被包围 && 下邻居被包围"。当（格子为"O"&&被包围）时更新格子为'O'

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        vector<bool> temp(board.size(),true);
        vector<vector<bool>> surrounded(board.size(),temp);
        check(0,0,board,surrounded);
    }

    void check(int row,int col,vector<vector<char>>& board, vector<vector<bool>>& surrounded){
        cout<<row<<",,,"<<col<<",,,";

        bool is_surrounded = true;
        if(row == board.size() && col==0){//棋盘外的格子为未被包围状态，如果到达该格子的邻居为'O'，则该'O'没被包围
            return;
        }

        if(col < board.size()-1){
            check(row,col+1,board,surrounded);
        }
        else if(col == board.size()-1){
            check(row+1,0,board,surrounded);
        }
        if(board[row][col] == 'X'){
            return;
        }
        if(row == board.size()-1 || col == board.size()-1){
            surrounded[row][col] == false;
            return;
        }

        if(row > 0){
            is_surrounded = is_surrounded && surrounded[row-1][col];
        }
        if(row < board.size()-1){
            is_surrounded = is_surrounded && surrounded[row+1][col];
        }
        if(col > 0){
            is_surrounded = is_surrounded && surrounded[row][col-1];
        }
        if(col < board.size()-1){
            is_surrounded = is_surrounded && surrounded[row][col+1];
        }
        surrounded[row][col] = is_surrounded;

        if(is_surrounded){
            board[row][col]='X';
        }
        return;
    }
};


核心思想：只有边界上'O'的位置，以及与遍历'O'相连组成的片区不会被'X'包围。

因此先对边界上的'O'遍历之后暂存为'*'。

非'*'的'O'即被'X'包围了,需要被修改为'X'。
先给一种递归实现的dfs供参考，简洁很多，但是在leetcode中由于栈溢出会显示Runtime Error

void dfs(vector<vector<char>> &board, int i, int j, int m, int n){//从边界的'O'开始分析，首先将边界'O'置为'*'，再分析'*'的上/下/左/右四个邻居中存在的'O'，并递归修改邻居
    board[i][j] = '*';
    if(i > 0 && board[i-1][j] == 'O')   // up
        dfs(board, i-1, j, m, n);
    if(i < m-1 && board[i+1][j] == 'O') // down
        dfs(board, i+1, j, m, n);
    if(j > 0 && board[i][j-1] == 'O')   // left
        dfs(board, i, j-1, m, n);
    if(j < n-1 && board[i][j+1] == 'O') // right
        dfs(board, i, j+1, m, n);
}



Solution 1:用栈实现DFS

struct Pos{
    int row;
    int col;
    Pos(int newrow,int newcol): row(newrow),col(newcol) {}
};

class Solution{
public:
    void solve(vector<vector<char>> &board){
        if(board.empty() || board[0].empty()){
            return;
        }
        int row_num = board.size();
        int col_num = board[0].size();
        for(int i=0;i<row_num;i++){
            for(int j=0;j<col_num;j++){
                if(board[i][j] == 'O'){
                    if(i==0 || i==length-1 || j==0 || j==width-1){
                        dfs(board,i,j,length,width);
                    }   
                }   
            }
        }

        for(int i=0;i<row_num;i++){
            for(int j=0;j<col_num;j++){
                if(board[i][j]=='*'){
                    board[i][j] = 'O';
                }
                else if(board[i][j]=='O'){
                    board[i][j] = 'X';
                }
            }
        }
        return;
    }
    
    因为把宽度和长度写反了，导致没通过 4*6 棋盘的测试用例，而且代码仍然是错误的！！！！第2个dfs逻辑更为清晰
    test case:["XOXOXOOOXO","XOOXXXOOOX","OOOOOOOOXX","OOOOOOXOOX","OOXXOXXOOO","XOOXXXOXXO","XOXOOXXOXO","XXOXXOXOOX","OOOOXOXOXO","XXOXXXXOOO"]
    注意区分：第2个dfs中并没有一次性地将一个方向的全部'O'元素全部push入栈，而是选择了每push一个'O'邻居入stack，就直接结束本节点的分析，开始分析栈顶元素(即新加入的'O')的上下左右四个邻居，将第一个为'O'的new neighbor入栈，然后再次分析栈顶
    所以第一个dfs中始终使用 cur 记录最新分析的元素，而且每次都使用 while()走完一个方向；第二个dfs则必须保持住cur，使用up,down,left,right分别记录四个方向的最新元素，而且每次都只使用 if()走一步，而且真正走出一步后还需要continue

    // void dfs(vector<vector<char>> &board,int i,int j,int width,int length){
    //     stack<Pos*> my_stk;
    //     Pos *cell = new Pos(i,j);
    //     my_stk.push(cell);
    //     while(!my_stk.empty()){
    //         Pos *cur = my_stk.top();
    //         board[cur->row][cur->col] = '*';
    //         while(cur->row > 0 && board[cur->row-1][cur->col]=='O'){//up，先向上走到'O'的尽头，将每个'O'入栈，然后对栈顶的元素依次分析上下左右四个方向
    //             cur = new Pos(cur->row-1,cur->col);
    //             board[cur->row][cur->col] = '*';
    //             my_stk.push(cur);
    //         }
    //         while(cur->row < width-1 && board[cur->row+1][cur->col]=='O'){//down，再向下走到'O'的尽头，将每个'O'入栈，然后对栈顶的元素依次分析上下左右四个方向
    //             cur = new Pos(cur->row+1,cur->col);
    //             board[cur->row][cur->col] = '*';
    //             my_stk.push(cur);
    //         }
    //         while(cur->col > 0 && board[cur->row][cur->col-1]=='O'){//left，接着向左走到'O'的尽头，将每个'O'入栈，然后对栈顶的元素依次分析上下左右四个方向
    //             cur = new Pos(cur->row,cur->col-1);
    //             board[cur->row][cur->col] = '*';
    //             my_stk.push(cur);
    //         }
    //         while(cur->col < length-1 && board[cur->row][cur->col+1]=='O'){//down，接着向下走到'O'的尽头，将每个'O'入栈，然后对栈顶的元素依次分析上下左右四个方向
    //             cur = new Pos(cur->row,cur->col+1);
    //             board[cur->row][cur->col] = '*';
    //             my_stk.push(cur);
    //         }
    //         my_stk.pop();
    //     }
    // }
    
    void dfs(vector<vector<char>> &board,int i,int j,int row_num,int col_num){
        stack<Pos*> my_stk;
        Pos *cell = new Pos(i,j);
        my_stk.push(cell);
        board[i][j] = '*';
        while(!my_stk.empty()){
            Pos *cur = my_stk.top();
            if(cur->row > 0 && board[cur->row-1][cur->col]=='O'){//up，先向上走一步'O'，在将上邻居'O'入栈后，结束本节点的分析，开始对栈顶的元素依次分析上下左右四个方向，
                Pos *up = new Pos(cur->row-1,cur->col);
                board[up->row][up->col] = '*';
                my_stk.push(up);
                continue;
            }
            if(cur->row < row_num-1 && board[cur->row+1][cur->col]=='O'){//down，再向下走一步'O'，在将下邻居'O'入栈后，结束本节点的分析，开始对栈顶的元素依次分析上下左右四个方向，
                Pos *down = new Pos(cur->row+1,cur->col);
                board[down->row][down->col] = '*';
                my_stk.push(down);
                continue;
            }
            if(cur->col > 0 && board[cur->row][cur->col-1]=='O'){//left，接着向左走到'O'的尽头，将每个'O'入栈，然后对栈顶的元素依次分析上下左右四个方向
                Pos *left = new Pos(cur->row,cur->col-1);
                board[left->row][left->col] = '*';
                my_stk.push(left);
                continue;
            }
            if(cur->col < col_num-1 && board[cur->row][cur->col+1]=='O'){//down，接着向下走到'O'的尽头，将每个'O'入栈，然后对栈顶的元素依次分析上下左右四个方向
                Pos *right = new Pos(cur->row,cur->col+1);
                board[right->row][right->col] = '*';
                my_stk.push(right);
                continue;
            }
            my_stk.pop();
        }
    }      
};