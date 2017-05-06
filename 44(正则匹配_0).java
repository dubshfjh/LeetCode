The original post has DP 2d array index from high to low, which is not quite intuitive.

Below is another 2D dp solution. Ideal is identical.

dp[i][j] denotes whether s[0....i-1] matches p[0.....j-1],

First, we need to initialize dp[i][0], i= [1,m]. All the dp[i][0] should be false because p has nothing in it.

Then, initialize dp[0][j], j = [1, n]. In this case, s has nothing, to get dp[0][j] = true, p must be '*', '*', '**',etc. Once p.charAt(j-1) != '*', all the dp[0][j] afterwards will be false.

Then start the typical DP loop.

Though this solution is clear and easy to understand. It is not good enough in the interview. it takes O(mn) time and O(mn) space.

public class Solution {
    public boolean isMatch(String s, String p) {
        int len1 = s.length(),len2 = p.length();
        boolean[][] dp = new boolean[len1+1][len2+1];//dp[i][j]：s[0...i-1]与 模式串p[0...j-1]是否匹配
        dp[0][0] = true;
        //初始化s[0...len1-1]与P空串""的匹配
        for(int i=1;i<=len1;i++){
            dp[i][0] = false;
        }

        //初始化s空串""与P[0...len2-1]的匹配,一旦p[j-1]!="*"，则dp[0][j,j+1....len2-1] = false
        for(int j=1;j<=len2;j++){
            if(p.charAt(j-1) == '*'){
                dp[0][j] = true;
            }
            else{
                break;
            }
        }

        for(int i=1;i<=len1;i++){
            for(int j=1;j<=len2;j++){
                if(p.charAt(j-1) != '*'){//此时要求 s[i-1]==p[j-1] or p[j-1]=='?'
                    dp[i][j] = dp[i-1][j-1] && ((s.charAt(i-1) == p.charAt(j-1))||(p.charAt(j-1) == '?'));
                }
                else{//p[j-1]为"*"，一、若*充当1-多个字符，则用这个*抵消掉s[i-1](由于*可能抵消了s[i-2...0]，所以抵消掉s[i-2]的不一定是p[j-2]，仍然可能是p[j-1],因此取dp[i-1][j]，而不是dp[i-1][j-1]
                //二、若*充当0个字符，则取dp[i][j-1]
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                }
            }
        }

        return dp[len1][len2];
        
    }
}