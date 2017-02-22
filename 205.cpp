HashTable，直接使用两个map记录s[i]和t[i]前一次出现的位置，只有每个s[i]和t[i]的pre_position。使用下标i遍历s和t：1. 如果s[i]和t[i]之前都没出现过，则直接记录当前位置；
2. 如果s[i]和t[i]之前都已经出现过，则比较map中s[i]和t[i]的pre_pos是否相等：如果不相等则s,t不能相互转化，如果相等则更新s[i]和t[i]的pre_pos
3. 如果s[i]和t[i]一个之前出现过，一个为新字母，则s,t不能相互转化
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        map<char,int> s_prepos,t_prepos;
        map<char,int>::iterator it_s,it_t;//使用map记录s[i]和t[i]上一次出现的位置，只有每个s[i]和t[i]的pre_position都相等时，s和t才满足isomorphic
        for(int i=0;i<s.length();i++){
            it_s = s_prepos.find(s[i]);
            it_t = t_prepos.find(t[i]);
            if(it_s == s_prepos.end() && it_t == t_prepos.end()){//如果s[i]和t[i]之前都没出现过，则直接记录当前位置
                s_prepos[s[i]] = t_prepos[t[i]] = i;
            }
            else if(it_s != s_prepos.end() && it_t != t_prepos.end()){//如果s[i]和t[i]之前都已经出现过，则比较map中s[i]和t[i]的pre_pos是否相等：如果不相等则s,t不能相互转化，如果相等则更新s[i]和t[i]的pre_pos
                if(s_prepos[s[i]] != t_prepos[t[i]]){
                    return false;
                }
                s_prepos[s[i]] = t_prepos[t[i]] = i;
            }
            else{//如果s[i]和t[i]一个之前出现过，一个为新字母，则s,t不能相互转化
                return false;
            }
        }
        return true;
    }
};

仍为HashTable，map需要多次判断s[i]/t[i]之前是否出现过，find函数使用次数太多了，改用int数组实现hash表，将每个字符的pre_pos初始化为-1，
这样对于当前Isomorphic的两种情况："1. s[i]和t[i]之前都没出现过 2. s[i]和t[i]之前都已经出现过，而且二者的pre_pos都相等" 统一归类为 s_prepos[s[i]] == t_prepos[t[i]]
从而 不满足Isomorphic的两种情况："1. s[i]和t[i]一个之前出现过，一个为新字母  2. s[i]和t[i]之前都已经出现过，而且二者pre_pos不相等"  统一归类为 s_prepos[s[i]] != t_prepos[t[i]]
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        vector<int> s_prepos(256,-1),t_prepos(256,-1);
        for(int i=0;i<s.length();i++){
            if(s_prepos[s[i]] != t_prepos[t[i]]){
                return false;
            }
            s_prepos[s[i]] = t_prepos[t[i]] = i;
        }
        return true;
    }
};