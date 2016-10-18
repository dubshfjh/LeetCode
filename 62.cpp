#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> row(n,0);
        vector<vector<int>> dp(m,row);//dp[i][j]记录了到达(i,j)的路径数目
        if(m==0 || n==0){
        	return 0;
        }
        dp[0][0]=1;
        for(int i=0;i<m;i++){
        	for(int j=0;j<n;j++){
        		if(i>0 && j>0){
        			dp[i][j]=dp[i-1][j]+dp[i][j-1];//到达(i,j)的路径数目= 到达(i-1,j)的路径数目(每条向下一次到达(i,j)) + 到达(i,j-1)的路径数目(每条向右一次到达(i,j))
        		}
        		else if(i>0){
        			dp[i][j]=dp[i-1][j];//到达第0列所有元素的路径都只有从(0,0)不断向下这一条
        		}
        		else if(j>0){
        			dp[i][j]=dp[i][j-1];//到达第0行所有元素的路径都只有从(0,0)不断向右这一条
        		}
        	}
        }
        return dp[m-1][n-1];
    }
};