题目意思是，给定词典的情况下，看看原字符串能不能全部成功地被给定的词典分割。一开始，最自然的想法是，使用递归。提交，超时了。

递归，而且是从单词s的角度将s砍成两段，分析左右两段是否在字典中出现，所以当s较长则必然会超时.
PS：带字典的题目中，只有字典本身的size不会太大，所以不能递归地考虑s的子串是否在字典中出现，而应该每次迭代地考虑字典中每个word是否为s最左侧开始的子串
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        return help_break(0,s.size()-1,s,wordDict);
    }

    bool help_break(int left,int right,string s,unordered_set<string>& wordDict){
        cout<<left<<",,,"<<right<<",,,"<<s.substr(left,right-left+1)<<endl;
        if(wordDict.find(s.substr(left,right-left+1))!=wordDict.end()){
            return true;
        }
        else if(left >= right){
            return false;
        }
        bool could_find = false;
        if(right-left+1 < 3){//必须区分s中长度>=3和<=2的两种情况，如果统一进行分析，则mid = left to right，此时递归将无穷地重复分析(left,left)
            could_find |= (help_break(left,left,s,wordDict) && help_break(right,right,s,wordDict));
        }
        else{
            for(int mid=left+1;mid<=right-1 && !could_find;mid++){//当right-left+1>=3时
                cout<<"mid: "<<mid<<endl;
                could_find = could_find || (help_break(left,mid,s,wordDict) && help_break(mid+1,right,s,wordDict));
            }            
        }
        
        return could_find;
    }
};


查找子串的小改进，每次迭代地考虑字典中每个word是否为s最左侧开始的子串，从而省去递归查找左半部份子串的时间，但仍然超时
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if(s.length()==0){
            return false;
        }
        return help_break(s,wordDict);
    }

    bool help_break(string s, unordered_set<string>& wordDict){
        if(s.length == 0){
            return true;
        }
        bool could_find = false;
        if(s.length()){
            unordered_set<string>::iterator it;
            for(it=wordDict.begin();it!=wordDict.end() && !could_find;it++){
                if(s.find(*it) == 0){//字典当前的word (*it)为s最左侧子串
                    bool right_find;
                    string temp = s.substr((*it).length());//s中{(*it).length,(*it).length+1,...size-1}，即(*it)右侧的子串

                    right_find = right_find && help_break(temp,wordDict)；
                    if(right == false){
                        continue;
                    }
                    could_find = could_find || left_find;
                }
            } 
        }
        return could_find;
    }
};


想想，这个问题其实具有动态规划的特点。比如计算catsanddog的分割方式，那么倒着想如下：
到了最后一个字符g的时候，
如果能在g之前切一刀，也就是说，如果g在词典中以及catsanddo能够成功切分，那么原字符串就可以成功切分。
或者，如果能在og之前切一刀，也就是说，如果og在词典中以及catsandd能够成功切分，那么原字符串就可以成功切分。
或者，如果能在dog之前切一刀，也就是说，如果dog在词典中以及catsand能够成功切分，那么原字符串就可以成功切分。
或者，如果能在ddog之前切一刀，也就是说，如果ddog在词典中以及catsan能够成功切分，那么原字符串就可以成功切分。
或者，如果能在nddog之前切一刀，也就是说，如果nddog在词典中以及catsa能够成功切分，那么原字符串就可以成功切分。
或者，如果能在anddog之前切一刀，也就是说，如果anddog在词典中以及cats能够成功切分，那么原字符串就可以成功切分。
或者，如果能在sanddog之前切一刀，也就是说，如果sanddog在词典中以及cat能够成功切分，那么原字符串就可以成功切分。
或者，如果能在tsanddog之前切一刀，也就是说，如果tsanddog在词典中以及ca能够成功切分，那么原字符串就可以成功切分。
或者，如果能在atsanddog之前切一刀，也就是说，如果atsanddog在词典中以及c能够成功切分，那么原字符串就可以成功切分。
或者，如果能在catsanddog之前切一刀，也就是说，如果catsanddog在词典中以及""能够成功切分，那么原字符串就可以成功切分。

使用一个数组bool word[i] 来记录：从s[0]开始的子串长度为i的时候，能否成功切分(i取值范围必然为[ 0, word.length() ] )
对于每个i=1 to s.length(), 遍历j=i-1 to 0， 状态转移方程为 word[i] = word[i] || (word[j] && wordDict.find(s中[j...i-1]这段子串)!=wordDict.end())
PS: i从1开始遍历到s的长度, j为s中左侧子串的长度，因此j从 i-1 遍历到 0。最后的word[s.length]即为s整体能否切分

class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        vector<bool> word(s.length()+1,false);
        word[0] = true;
        for(int i=1;i<=s.length();i++){
            for(int j=i-1;j>=0;j--){
                if(word[j] && wordDict.find(s.substr(j,i-j)) != wordDict.end()){
                    word[i] = true;
                    break;
                }
            }
        }
        return word[s.length()];
    }
};


result[i]表示s[0...i]是否能够成功切分，因此i=0...length-1；j表示s[0..i]左侧子串的最后一个字符下标，即s[0...j...i]，因此j=0...i-1
再次优化：在对s[0...i]进行切分之前，首先判断s[0...i]整体是否出现在字典中，一旦出现则i++，分析下一个s[0...i]是否能够切分，能减少一定运行时间

class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
        vector<bool> result(s.length(), false);
        for (int i = 0; i < result.size(); ++i) {
            if (dict.find(s.substr(0, i + 1)) != dict.end()) {
                result[i] = true;
                continue;
            }
            for (int j = 0; j < i; ++j) {
                if ((result[j] == true) && (dict.find(s.substr(j + 1, i -j))!= dict.end())) {
                    result[i] = true;
                    break;
                }
            }
        }
        return result[result.size() - 1];
    }
};