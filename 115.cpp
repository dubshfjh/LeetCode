一、分析字符串S(长为m)和T(长为n)最长公共子序列的DP算法：

1. 创建1个二维数组dp[m+1][n+1]：dp[i][j]代表字符串S[0...i-1]和T[0...j-1]匹配的最长公共子序列长度
2. 初始化dp[][]内容为0，其中dp[0][0],dp[i][0],dp[0][j]始终保持初值为0
3. i：1 to m；j：1 to n进行循环（状态转移方程如下：）
    (1) if (S[i-1]==T[j-1])：dp[i][j] = dp[i-1][j-1] + 1
    (2) if (S[i-1]!=T[j-1])：选择1，此次放弃S[i-1]，此时dp[i][j] = S[0...i-2] 与 T[0...j-1]公共子序列长度，即dp[i-1][j]
                         选择2：此次放弃T[j-1]，让S[i]去尝试匹配 T[0...j-2]看看是否能生成更长的公共子序列，此时dp[i][j] = S[0...i-1] 与 T[0...j-2]公共内子序列长度，即dp[i][j-1]
        总结：S[i-1] != T[j-1]时，dp[i][j] = max(dp[i-1][j], dp[i][j-1])
4. 循环结束后，dp[m][n]中的数值：最长公共子序列的长度



二、从dp数组中查找最长的公共子序列str（先执行一）
1. i：m to 1 ,j:n to 1
2. if (S[i-1] == T[j-1])，说明S[i-1],T[j-1]被选做了公共子序列中的1个字符，将S[i-1]字符插入到str的头部，i--,j--
3. if (S[i-1] != T[j-1])，比较dp[i-1][j] 与 dp[i][j-1]的大小.
    (1) 如果dp[i-1][j]更大，说明在动态规划匹配S[i]和T[j]时，选择了放弃S[i-1]，直接取值为 S[0...i-2] 与 T[0...j-1]的子序列长度
        所以i--;
    (2) 如果dp[i][j-1]更大，说明在匹配S[i]和T[j]时，选择了放弃T[j-1]，直接取值为 S[0...i-1] 与 T[0...j-2]的子序列长度
        所以j--;
    (3) dp[i-1][j] == dp[i][j-1]，则说明在匹配S[i]和T[j]时，有着放弃S[i]/放弃T[j]两种选择，这两种选择都可以得到最终的最长公共子序列


PS：下端代码的计算结果有误（猜测是direction[i][j]==4的情况定义不明确），对于求解子序列数目有着更简洁的做法
/*
三、计算公共子序列str的可能个数（先执行一，参考二中的算法计算“迷宫右下角->左上角”的走路方式，一旦到达左上角则 count++）
1. 递归临界条件：如果[i==0 || j==0]，count++，返回上一层
2. if (S[i-1] == T[j-1])，说明S[i-1],T[j-1]被选做了公共子序列中的1个字符，下层递归执行(i-1,j-1)
3. if (S[i-1] != T[j-1])，比较dp[i-1][j] 与 dp[i][j-1]的大小.
    (1) dp[i-1][j] == dp[i][j-1]，则说明在匹配S[i-1]和T[j-1]时，有着放弃S[i-1]/放弃T[j-1]两种选择，下层递归先执行(i-1,j)，然后执行(i,j-1)
    (2) 如果dp[i-1][j]更大，说明在动态规划匹配S[i-1]和T[j-1]时，选择了放弃S[i-1]，下层递归执行(i-1,j)
    (3) 如果dp[i][j-1]更大，说明在匹配S[i-1]和T[j-1]时，选择了放弃T[j-1]，下层递归执行(i,j-1)

PS：为了避免太多次的数值比较，使用方向数组direction[i][j]：取值为1，S[i-1] == T[j-1]；取值为2，dp[i-1][j]更大；取值为3，dp[i][j-1]更大；取值为4，dp[i-1][j]==dp[i][j-1s]
*/
class Solution {
public:
    int count=0;
    int numDistinct(string s, string t) {
        int i,j,m,n;
        m = s.length();
        n = t.length();
        if(m < n || m==0 || n==0){
            return 0;
        }
        int dp[m+1][n+1];
        vector<int> temp(n+1,0);
        vector<vector<int>> direction(m+1,temp);//direction[i][j]：1:[i,j]->[i-1,j-1], 2:[i,j]->[i-1,j] ,3:[i,j]->[i,j-1], 4：[i-1,j],[i,j-1]两方向都得遍历
        // int direction[m+1][n+1];

        for(i=0;i<=m;i++){
            for(j=0;j<=n;j++){
                dp[i][j]=0;
                // direction[i][j]=0;
            }
        }
        //动态规划，求解最长公共子序列的长度
        for(i=1;i<=m;i++){
            for(j=1;j<=n;j++){
                if(s[i-1] == t[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                    direction[i][j] = 1;
                }
                else{
                    if(dp[i-1][j] > dp[i][j-1]){
                        dp[i][j] = dp[i-1][j];
                        direction[i][j] = 2;
                    }
                    else{
                        if(dp[i-1][j] < dp[i][j-1]){
                            dp[i][j] = dp[i][j-1];
                            direction[i][j] = 3;
                        }
                        else{
                            dp[i][j] = dp[i][j-1];//dp[i-1][j]亦可
                            direction[i][j] = 4;
                        }
                    }

                }
            }
        }
        // for(i = 1; i <= m; i++)
        // {
        //      for(j = 1; j <= n; j++)
        //      {
        //          cout << dp[i][j] << " ";
        //      }
        //      cout << endl;
        // }
        if(dp[m][n] < n){
            return 0;
        }

        cal_seqnum(m,n,direction);
        return count;
                
    }

    // void cal_seqnum(int i,int j,vector<vector<int>> direction){
    //     if(i==0 || j==0){
    //         count++;
    //         return;
    //     }
    //     if(direction[i][j] == 1){
    //         cal_seqnum(i-1,j-1,direction);
    //     }
    //     else{
    //         if(direction[i][j] == 2){
    //             cal_seqnum(i-1,j,direction);
    //         }
    //         else{
    //             if(direction[i][j] == 3){
    //                 cal_seqnum(i,j-1,direction);
    //             }
    //             else{
    //                 cal_seqnum(i-1,j,direction);
    //                 cal_seqnum(i,j-1,direction);
    //             }
    //         }
    //     }
    // }
};


给定字符串S和T，S通过删除某些位置的字符得到T的话，就记作一种subSequence
递归代码便于理解，但会超时

class Solution {
public:
    int numDistinct(string S, string T)
    {
        if (S.size() < T.size()) return 0;
        if (S.size() == T.size() && S == T) return 1; // 都为空的时候返回什么呢？？？
        if (S[0] != T[0]){//如果本层递归的S[0]与T[0]不匹配，则只能删除此时的S[0]后，将S[1...m-1]与T匹配
            return numDistinct(S.substr(1), T);
        }
        else{//如果本层递归的S[0]==T[0]，则有2种选择：1.用S[0]匹配掉T[0]，二者都被消耗掉，下层匹配S[1..m-1],T[1...n-1]；2.本次放弃使用S[0]匹配掉T[0]，就当S[0]不存在(即只消耗掉S[0])，下层匹配S[1...m-1]和T[0...n-1]
            return numDistinct(S.substr(1), T.substr(1)) + numDistinct(S.substr(1), T);
        }
    }
};



用dp[i][j]记录S[0...i-1]中T[0...j-1]作为子序列的个数，那么最后目标就是dp[S.size()][T.size()];

初始化，j = 0 时候，dp[i][0] = 1，因为所有的都可以通过删除所有变成空字符，并且只有一种。

递推式子如下：

1. i和j都从1开始，且j不能大于i，因为匹配的长度至少为1开始，j大于i无意义
2. 如果 i == j，那么 dp[i][j] = (S.substr(0, i) == T.substr(0, j)); //即S[0..i-1]与T[0...j-1]是否完全匹配

3. 如果 i != j 分两种情况
　　(1) S[i-1] != T[j-1] 时，只能在S[0...i-2]中尝试寻找T[0...j-1]作为子序列的种数，那么 dp[i][j] = dp[i - 1][j];
　　(2) S[i-1] == T[j-1] 时，那么对于字符T[j-1]有两种选择：选择1. T[j-1]与S[i-1]匹配消耗掉，选择1得到的子序列种数 = S[0...i-2]中T[0...j-2]作为子序列的种数 = dp[i-1][j-1]
        选择2. T[j-1]本次并不与S[i-1]匹配掉，就当作S[i-1]不存在(即只消耗掉S[0])，选择2得到的匹配种数 = S[0...i-2]中T[0...j-1]作为子序列的种数 = dp[i][j-1]
        所以dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];

class Solution {
public:
    int numDistinct(string s, string t){
        int m = s.length();
        int n = t.length();
        if(m < n){
            return 0;
        }
        if(n == 0){//如果t为空，则默认t出现过1次
            return 1;
        }

        int dp[m+1][n+1];
        for(int i=0;i<=m;i++){
            dp[i][0] = 1;
        }

        for(int i=1;i<=m;i++){
            for(int j=1;j<=i && j<=n;j++){
                if(i == j){
                    dp[i][j] = (s.substr(0,i) == t.substr(0,j));
                }
                else{//j限定条件包括j<=i &&ｊ<=n，所以此时i>j
                    if(s[i-1] == t[j-1]){
                        dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                    }
                    else{
                        dp[i][j] = dp[i-1][j];
                    }
                }
            }
        }
        return dp[m][n];
    }
};