动态规划：dp[i][j]存储从根元素到达元素triangle[i][j]路径的最小sum。状态转移方程为：1.j==0时上层邻居为{j}，dp[i][j] = dp[i-1][j]+triangle[i][j];  2.j==triangle[i].size()时上层邻居为{j-1}，dp[i][j] = dp[i-1][j-1]+triangle[i][j]; 3.0<j<size-1时上层邻居为{j-1.j}，dp[i][j] = min(dp[i-1][j-1],dp[i-1][j])+triangle[i][j];
最后遍历dp[size-1]这一行，本行的最小值就是整个三角形的最小路径。

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int size = triangle.size();
        if(size==0){
            return 0;
        }
        int dp[size][size];
        dp[0][0] = triangle[0][0];
        for(int i=1;i<size;i++){
            for(int j=0;j<=i;j++){
                if(j==0){
                    dp[i][j] = dp[i-1][j]+triangle[i][j];
                }
                else if(j==i){
                    dp[i][j] = dp[i-1][j-1]+triangle[i][j];
                }
                else{
                    dp[i][j] = min(dp[i-1][j-1],dp[i-1][j])+triangle[i][j];
                }
            }
        }
        int res = dp[size-1][0];
        for(int i=1;i<size;i++){
            res = min(res,dp[size-1][i]);
        }
        return res;
    }
};