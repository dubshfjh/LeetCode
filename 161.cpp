Given two strings S and T, determine if they are both one edit distance apart.


如果两个字符串只有一个编辑距离，则只有两种情况：

1. 如果两个字符串长度差距大于1，肯定不对,editdistacnce>=2
2. 两个字符串一样长的时候，说明有一个替换操作，我们只要看s和t是否只有一个字符不一样就行了
3. 一个字符串比另一个长1，说明有个增加或删除操作，editdistacnce=1要求 对longer字符串删去1个字符后(等价于在shorter中添加1个字符)，longer==shorter
    我们就找到第一个对应位置不一样的那个字符，如果较长字符串在那个字符之后的部分和较短字符串那个字符及之后的部分是一样的，则符合要求

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int s_len,t_len;
        s_len = s.length();
        t_len = t.length();
        if(abs(s_len - t_len) >= 2){//s,t的长度差 > 1，则editdistacnce>=2
            return false;
        }
        else if(s_len - t_len == 1){// s,t长度差为1，则editdistacnce=1要求 对longer字符串删去1个字符后(等价于在shorter中添加1个字符)，longer==shorter
            return isOneDeleted(s,t);
        }
        else if(t_len - s_len == 1){
            return isOneDeleted(t,s);
        }
        else{//s,t长度相等,editdistacnce=1要求 有一个替换操作，我们只要看s和t是否只有一个字符不一样就行了
            return isOneModified(s,t);
        }
    }

    bool isOneDeleted(string longer,string shorter){
        int i;//找到first对应位置不一样的那个字符，如果longer在(那个字符之后的部分)和shorter(那个字符及之后的部分)是一样的，则符合要求
        for(i=0;i<shorter.length();i++){
            if(shorter[i] != longer[i]){
                break;
            }
        }
        if(i<shorter.length()){
            return shorter.substr(i).compare(longer.substr(i+1))；
        }
        else{//shorter的全部字符都与longer的前shorter.length()个字符相等，则只用删除longer的last字符即可
            return true;
        }
    }

    bool isOneModified(string s,string t){
        int i;//找到第一个对应位置不一样的那个字符，如果s和t在那个字符之后的部分相等，则编辑距离为1
        for(i=0;i<s.length();i++){
            if(s[i] != t[i]){
                break;
            }
        }
        if(i<s.length()){
            return s.substr(i+1).compare(t.substr(i+1));
        }
        else{//全部字符都匹配，编辑距离为0
            return false;
        }
    }
};

也可以使用72 Edit Distance题中的算法，完整求解出整个dp[i][j]，dp[i][j]：s的前i个字符与j的前j个字符的编辑距离，即s[0...i-1]与t[0...j-1]的编辑距离。初始化dp(0,0)=0；dp(i,0)=i；dp(0,j)=j;
最后的dp(s_len,t_len)就是s和t的编辑距离

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int s_len,t_len;
        s_len = s.length();
        t_len = t.length();
        vector<int> temp(t_len+1,0);
        vector<vector<int>> dp(s_len+1,temp);

        for(int i=0;i<=s_len;i++){
            dp[i][0] = i;
        }
        for(int j=0;j<=t_len;j++){
            dp[0][j] = j;
        }

        for(int i=1;i<=s_len;i++){
            for(int j=1;j<=t_len;j++){
                dp[i][j] = min(dp[i-1][j]+1, dp[i][j-1]+1);//dp[i-1][j]+1：删除s[i]后，采用s[0...i-1]与t[0...j]的编辑方案；dp[i][j-1]+1：删除t[j]后，采用s[0...i]与t[0...j-1]的编辑方案
                //if(s[i] == t[j]){ 第2次出错了！！！dp[i][j]存储的是editdis(s的前i位,t的前j位)，即(s[0..i-1],t[0..j-1])，因此必须比较s[i-1]和t[j-1]
                if(s[i-1] == t[j-1]){//并不是比较s[i]与t[j]！！！
                    dp[i][j] = min(dp[i][j], dp[i-1][j-1]);//dp[i-1][j-1]：无需修改s[i]，直接采用dp[i-1][j-1]的编辑方案
                }
                else{
                    dp[i][j] = min(dp[i][j], dp[i-1][j-1]+1);//dp[i-1][j-1]+1：将s[i]修改为t[j]后，采用dp[i-1][j-1]的编辑方案
                }
            }
        }

        return dp[s_len][t_len]==1;
    }
};