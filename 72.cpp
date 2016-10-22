http://blog.csdn.net/feliciafay/article/details/17502919
动态规划思想，dp[i][j]存储了word1的0-i位与word2的0-j位得到的最小距离，显然dp[0][i]=i,dp[j][0]=j;dp[word1.size()][word2.size()]即为最终解
状态转移方程见72.jpg.
PS:Stanford公开课中认为修改算2次操作，但leetcode认为修改，增加，删除统一为1次操作
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1=word1.size()+1;//dp数组为len1行，len2列
        int len2=word2.size()+1;

        int **dp=new int*[len1];
        if(!dp){
        	return 0;
        }

        for(int i=0;i<len1;i++){
        	dp[i]=new int[len2];
        	if(!dp[i]){
        		return 0;
        	}
        }

        for(int i=0;i<len1;i++){
        	dp[i][0]=i;
        }

        for(int j=0;j<len2;j++){
        	dp[0][j]=j;
        }

        for(int i=1;i<len1;i++){
        	for(int j=1;j<len2;j++){
        		int temp1,temp2;
        		if(word1[i-1] == word2[j-1]){//注意这里下标容易写错。一开始写成了if(word[i]==word2[j])  
        			temp1=dp[i-1][j-1]+0;//由dp[i-1][j-1]保持原状即可
        		}
        		else{
        			temp1=dp[i-1][j-1]+1;//首先得到dp[i-1][j-1]情况，然后修改一次word[i-1]即可
        		}
        		temp2=min((dp[i-1][j]+1),(dp[i][j-1]+1));//通过dp[i-1][j]和dp[i][j-1]的情况，删除或者增加一次节点即得到dp[i][j]
        		dp[i][j]=min(temp1,temp2);

        	}
        }

        return dp[len1-1][len2-1];
    }
};