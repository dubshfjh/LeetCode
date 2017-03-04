构建新的字符串 L = (s) + "#" + (reversed s)，然后对 L 执行KMP算法求next数组, next[i]存储L[0...i]的最长公共子串长度(ps:第 28 题中KMP算法的 next[i]数组存储的是s[0...i]的最长公共子串长度-1)
我们只需要关心 next[L.size()-1]这一项，因为它展现了 reversed s 的最长后缀  匹配的  s的最长前缀的子串长度。
令 num = s.size() - next[L.size()-1]，则只需要将 reversed_s 的前 num 个字符添加到 s的前方，即能让新字符串变成回文串
e.g. s = "abc"， reversed_s = "cba"，reversed_s的最长后缀 匹配 s的最长前缀为 "a"，所以num = 3-1 = 2，所以只需要将前2个字符"cb"添加到s之前构成"cbabc"即可构成回文串

本质：取得从s[0]开始的最长回文子串(即s[0...i]与reverse_s[size-i-1...size-1]相匹配)的s_pal，然后在s的左侧对称填充 s - s_pal 的剩余字符即可构成回文串

class Solution {
public:
    string shortestPalindrome(string s) {
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        string L = s + "#" + rev_s;
        int size = L.size();

        vector<int> next(size,0);//next[i]存储L[0...i]的最长公共子串长度，而不是第28题的长度-1
        for(int i=1;i<size;i++){
            int k = next[i-1];
            while(k>0 && L[i] != L[k]){
                k = next[k-1];//此时为next[k-1]!!!!
            }
            if( L[i] == L[k]){
                next[i] = k+1;
            }
            else{
                next[i] = k;
            }
        }
        int num = s.size() - next[size-1];
        return rev_s.substr(0,num)+s;
    }
};