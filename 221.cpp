动态规划：dp[i,j]存储以(i,j)为终结点的最大平方数，以下图矩阵为例：如果a[2][2]的最大平方数要取3，
    则它在上邻居、左邻居和左上邻居的dp值都必须==2。类比到最大平方数试图取4...n的情况也是如此：要求3个邻居的dp取n-1
1  1   1
1 '1' '1'
1  '1' 1
    如果三个方向的邻居dp不相等，则取三个方向邻居dp的最小值temp，另外两个方向的邻居至少能提供以该邻居作为右下角的size temp 1 square
    因此dp[i][j] = temp+1
总结：当三个方向邻居dp都相等时(设取值为n)，则dp[i][j]=n+1；如果不都相等，则dp[i][j]= 1+min(左邻居dp,上邻居dp,左上邻居dp)
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int res = 0;
        int row = matrix.size();
        if(row == 0){
            return 0;
        }
        int col = matrix[0].size();
        if(col == 0){
            return 0;
        }
        vector<vector<int>> dp(row,vector<int>(col,0));
        for(int i=0;i<col;i++){
            dp[0][i] = (matrix[0][i] == '1');
            res = max(res,dp[0][i]);

        }
        for(int i=1;i<row;i++){
            dp[i][0] = (matrix[i][0] == '1');
            res = max(res,dp[i][0]);

        }
        for(int i=1;i<row;i++){
            for(int j=1;j<col;j++){
                if(matrix[i][j] == '1'){
                    if(dp[i-1][j] == dp[i][j-1] && dp[i-1][j] == dp[i-1][j-1]){
                        dp[i][j] = dp[i-1][j] + 1;
                    }
                    else{
                        int temp = min(dp[i-1][j],dp[i][j-1]);
                        dp[i][j] = 1+min(temp,dp[i-1][j-1]);
                    }
                    res = max(res,dp[i][j]);
                }
            }
        }
        return res*res;
    }
};