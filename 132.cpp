思想正确，但是最坏的时间复杂度为O(n^n)，导致超时 
test case 为aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

动态规划：dp[i][j]存储{s[i]...s[j]}分割为回文集合的最小刀数。dp[i][j]转移方程为：如果s[i..j]为回文串，则分割刀数为0；
否则必须对s[i..j]割1刀变成{s[i...k],s[k+1...j]}，dp[i][j] = 分割i,j为左右子串的1刀 + 分割左子串的最小刀数 + 分割有子串的最小刀数

首先初始化dp[i][i] = 0;
for i = size-1 to 0:
    for j = i+1 to size-1:
        if(s[i,,,j]为回文) 
            dp[i][j] = 0;
        else
          for k = i to j-1:
            dp[i][j] = 1+min{dp[i][k]+dp[k+1][j]}

class Solution {
public:
    int minCut(string s) {
        if(s.size()<=1){
            return 0;
        }
        vector<int> temp(s.size(),0);
        vector<vector<int>> dp(s.size(),temp);
        for(int i=s.size()-1;i>=0;i--){
            for(int j=i+1;j<s.size();j++){
                if(!isPalindrome(s,i,j)){
                    int temp = INT_MAX;
                    for(int k=i;k<=j-1;k++){
                        temp = min(temp,dp[i][k]+dp[k+1][j]);
                    }
                    dp[i][j] = temp+1;
                }
                else{
                    dp[i][j] = 0;
                }
            }
        }
        return dp[0][s.size()-1];
    }

private:
    bool isPalindrome(string s,int left,int right){
        while(left < right){
            if(s[left] != s[right]){
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};

从后往前构造二维数组isPalin，用于存储已经确定的回文子串。isPalin[i][j]==true代表s[i,...,j]是回文串。

在构造isPalin的同时使用动态规划计算从后往前的最小切分数，记录在min数组中。min[i]代表s[i,...,n-1]的最小切分数。

（上述两步分开做会使得代价翻倍，容易TLE）

关键步骤：

1、min[i]初始化为min[i+1]+1，即初始化s[i]与s[i+1...size-1]之间需要切一刀(如果[i..j]不为回文串，则1+min[i+1]就是最佳解决方案)。这里考虑边界问题，因此min数组设为n+1长度。

2、从i到n-1中间如果存在位置j，同时满足：(1)s[i,...,j]为回文串;(2)1+min[j+1] < min[i]。则更新min[i] = 1+min[j+1]，

也就是说一刀切在j的后面&&对[j+1...size-1]最优切法  比此时[i...size-1]的临时最优切法要好要好。
class Solution {
public:
    int minCut(string s) {
        int size = s.size();
        vector<vector<bool>> isPalin(size,vector<bool>(size,false));
        vector<int> min_cut(size+1,-1);

        for(int i=0;i<size;i++){
            isPalin[i][i] = true;
        }

        for(int i=size-1;i>=0;i--){
            min_cut[i] = min_cut[i+1]+1;//初始化[i...size-1]的最小刀数为 1+[i+1...size-1]的最小刀数
            for(int j=i+1;j<size;j++){
                if(s[i] == s[j]){
                    if(j == i+1 || isPalin[i+1][j-1] == true){//s[i]==s[j]==>[i,j(i+1)]为回文 || s[i]==s[j]&&[i+1,...,j-1]为palin ==> [i,i+1,...,j]为回文
                        isPalin[i][j] = true;
                        if(j == size-1){
                            min_cut[i] = 0;//[i,i+1...,size-1]整体为回文，需要切0刀
                        }
                        else{
                            if(1+min_cut[j+1] < min_cut[i]){//对于[i,i+1,...,size-1]，在j处切1刀变成[i...j]和[j+1...size-1]；如果 1+[j+1...size-1]最小刀数 < 此时[i...size-1]最小刀数
                                min_cut[i] = 1+min_cut[j+1];//更新[i,...,size-1]的最小刀数
                            }
                        }
                    }
                }
            }
        }

        return min_cut[0];
    }    
};