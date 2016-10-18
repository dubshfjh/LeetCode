class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        vector<int> row(obstacleGrid[0].size(),0);//障碍点的dp[i][j]仍然保持默认值0即可，因为不可能存在穿过该障碍点的路径
        vector<vector<int>> dp(obstacleGrid.size(),row);
        if(obstacleGrid.size()==0 || obstacleGrid[0][0]==1){
        	return 0;
        }

        dp[0][0]=1;
        for(int i=0;i<obstacleGrid.size();i++){
        	for(int j=0;i<obstacleGrid[i].size();j++){
        		if(obstacleGrid[i][j]==0){
        			if(i>0 && j>0){
        				dp[i][j]=dp[i-1][j]+dp[i][j-1];
        			}
        			else if(i>0){
        				dp[i][j]=dp[i-1][j];
        			}
        			else if(j>0){
        				dp[i][j]=dp[i][j-1];
        			}
        		}
        	}
        }
        return dp[i-1][j-1];
    }
};