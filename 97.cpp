动态规划思想：
首先检测s3的长度是否 == s1长度m + s2长度n，若不满足则return false
如果满足，则建立dp[m+1][n+1]，dp[i][j]表示s1的前i位和s2的前j位是否能够交叉成s3的前i+j位
初始化dp[0][0]=true；dp[0][i]=(dp[0][i-1])&&(s2[i-1] == s3[i-1])；dp[i][0]=(dp[i-1][0])&&(s1[i-1] == s3[i-1])

然后计算状态转移方程：dp[i][j] = (dp[i-1][j])&&(s1[i-1]与s3[i+j-1]匹配) || (dp[i][j-1]&&(s2[j-1]==s3[i+j-1]));
也就是dp[i][j] == (之前选择s1[0..i-2]与s2[0...j-1]，本次使用s1[i-1]与s3[i+j-1]匹配) || (之前选择s1[0..i-1]与s2[0...j-2]，本次使用s2[j-1]与s3[i+j-1]匹配)
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int i,j,m,n;
        m=s1.length();
        n=s2.length();
        if(m+n!=s3.length()){
            return false;
        }
        bool dp[m+1][n+1]; //dp[i][j]表示s1的前i位和s2的前j位是否能够交叉成s3的前i+j位

        dp[0][0]=true;
        for(i=1;i<=n;i++){
            dp[0][i]=dp[0][i-1]&&(s2[i-1]==s3[i-1]);//s2的前i-1位匹配 && 第i位匹配
            //cout<<dp[0][i]<<endl;
        }

        for(i=1;i<=m;i++){
            dp[i][0]=dp[i-1][0]&&(s1[i-1]==s3[i-1]);
            //cout<<dp[i][0]<<endl;
        }

        for(i=1;i<=m;i++){
            for(j=1;j<=n;j++){
                dp[i][j]=(dp[i-1][j]&&(s1[i-1]==s3[i+j-1])) || (dp[i][j-1]&&(s2[j-1]==s3[i+j-1]));
            }
        }

        return dp[m][n];
    }
};