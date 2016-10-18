class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
    	int i,j;
        vector<int> row(grid[0].size(),0);
        vector<vector<int>> dp(grid.size(),row);//dp[i][j]存储路径到达(i,j)点时的最小sum
        if(grid.size()==0 || grid[0].size()==0){
        	return 0;
        }
        dp[0][0]=grid[0][0];
        for(i=0;i<grid.size();i++){
        	for(j=0;j<grid[i].size();j++){
        		if(i>0 && j>0){
        			dp[i][j]=min(dp[i-1][j],dp[i][j-1])+grid[i][j];//选择上方or左方节点中sum最小的一个，加上grid[i][j]即为当前最小的sum
        		}
        		else if(i>0){
        			dp[i][j]=dp[i-1][j]+grid[i][j];
        		}
        		else if(j>0){
        			dp[i][j]=dp[i][j-1]+grid[i][j];
        		}
        	}
        }
        return dp[i-1][j-1];
    }
};