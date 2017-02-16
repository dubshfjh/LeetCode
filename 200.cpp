//增加dummy row和dummy col来统一计算，island[i][j]标识grid[i-1][j-1]是否已处于陆地
["11000101","11000010","00100110","00011011"]
思想：遍历分析每个'1'的grid[i][j]：1. 初始化全局bool变量oldisland为false,将[i][j]标记为'.'来区分该点是否已经遍历过，联合oldisland和二维数组grid_no[][]标记grid_no[i][j]=res，从而区分新大陆和旧大陆
2. 从[i][j]出发分析上，下，左，右四个方向的邻居节点：1)如果邻居为'1'(则该邻居为尚未被访问的陆地节点)，则递归分析该邻居节点；
    2)如果邻居为'.' && grid_no[邻居]!=res，即邻居为大陆&&邻居为旧大陆，因此从本轮的出发点开始的所有节点都处于旧大陆，标记oldisland=true
3. 执行完[i][j]的markdot标记旧大陆过程后，如果从[i][j]延伸的所有'1'都没有接触old大陆节点，即oldisland=false，则res++
class Solution {
public:
    int res = 0;//res表示当前轮的‘1’处于第res块陆地，用于区分新大陆和旧大陆
    bool oldisland;
    int numIslands(vector<vector<char>>& grid) {
        int row,col;
        row = grid.size();
        if(row == 0){
            return 0;
        }
        col = grid[0].size();
        if(col == 0){
            return 0;
        }
        // vector<vector<bool>> island(row+1,vector<bool>(col+1,false));
        vector<vector<int>> island_no(row,vector<int>(col,-1));
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(grid[i][j] == '1'){//如果当前位置为'1'，则说明当前位置为新大陆
                    // cout<<"lalala:"<<i<<",,"<<j<<endl;

                    oldisland = false;
                    markdot(grid,island_no,i,j);//将从[i][j]出发能延伸的整块大陆(即相连的'1')标记为'.'，代表已经被访问的大陆
                    if(!oldisland){//如果本次出发mark的大陆未与已访问大陆相连，则res++
                        res++;
                    }
                }
            }
        }
        return res;
    }

    void markdot(vector<vector<char>>& grid,vector<vector<int>>& island_no,int i,int j){
        if(i == grid.size() || j == grid[0].size()){
            return;
        }
        grid[i][j] = '.';//标记本点为已访问的大陆
        island_no[i][j] = res;
        // cout<<i<<",,,"<<j<<"..."<<oldisland<<endl;
        if(i > 0){//向上走一步，如果上邻居为已访问陆地('.')而且上邻居的island_no != 当前大陆编号res，则标记本大陆为oldisland；如果上邻居为新大陆('1')，则递归mark上邻居；如果上邻居为'0'，则分析当前节点的下邻居...
            if(grid[i-1][j] == '1'){//
                markdot(grid,island_no,i-1,j);
            }
            else if(grid[i-1][j] == '.' && island_no[i-1][j]!=res){
                oldisland = true;
                return;
            }
        }
        if(i < grid.size()-1){
            if(grid[i+1][j] == '1'){
                markdot(grid,island_no,i+1,j);
            }
            else if(grid[i+1][j] == '.' && island_no[i+1][j]!=res){
                oldisland = true;
                return;
            }
        }
        if(j > 0){
            if(grid[i][j-1] == '1'){
                markdot(grid,island_no,i,j-1);
            }
            else if(grid[i][j-1] == '.' && island_no[i][j-1]!=res){
                oldisland = true;
                return;
            }
        }
        if(j < grid[0].size()-1){
            if(grid[i][j+1] == '1'){
                markdot(grid,island_no,i,j+1);
            }
            else if(grid[i][j+1] == '.' && island_no[i][j+1]!=res){
                oldisland = true;
                return;
            }
        }
    }
};
