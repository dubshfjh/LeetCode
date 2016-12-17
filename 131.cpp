class Solution {
public:
    map<char,vector<int>> ch_index;
    vector<vector<string>> res;

    bool is_palin(int start,int end,string s){
        while(start < end){
            if(s[start] != s[end]){
                return false;
            }
            start++;
            end--;
        }
        return true;
    }

    vector<vector<string>> partition(string s) {
        if(s.size()==0){
            return res;
        }
        for(int i=0;i<s.size();i++){//首先使用map记录字符{'a'...'z'}出现的全部位置，从而加速palin字符串的查找，但目前的代码只利用率第一个字母的全部位置，导致耗时很长
            if(ch_index.count(s[i]) == 0){
                vector<int> index(1,i);
                ch_index.insert(pair<char,vector<int>>(s[i],index));
            }
            else{
                ch_index[s[i]].push_back(i);
            }
        }
        vector<string> temp;
        my_partition(s,0,s.size()-1,temp);
        return res;
    }

    void my_partition(string s,int left,int right,vector<string> temp){//递归寻找{left,left+1,...,right}这段子串中的全部palin
        if(left > right){//必须得是>，而非>=，否则对于“最后一个字母单独作为palin时，会少记录最后一个palin”
            res.push_back(temp);
            return;
        }
        int i=0;
        while(ch_index[s[left]][i] < left){//对于s[left]出现的全部位置，只有处于left之后的某个/某些j，才可能构成{s[left]...s[j]}这个新的palin
            i++;
        }
        for(;i<ch_index[s[left]].size();i++){//分析每个left之后的位置j上的"相同字母"
            if(is_palin(left,ch_index[s[left]][i],s)){//如果s[left]..s[j]为palin，则用temp记录这一段回文子串，再次寻找{j+1,right}上的回文子串
                string palin = s.substr(left,ch_index[s[left]][i]-left+1);
                temp.push_back(palin);
                my_partition(s,ch_index[s[left]][i]+1,right,temp);
                temp.pop_back();//分析下一个j是否构成了s[i]..s[j]这个palin之前，需要将本层找到的前一个palin移除
            }
        }
    }

};


放弃使用map，直接把字符串s分为前后两个字串 str1, str2；如果str1是回文，加入partition，然后递归str2. S:{str1,str2}

递归分析每层[start,size-1]这段子串中的palindrome：分析每一层从start开始的全部子串str1:{s[start],s[start,start+1],...,s[start,...,size-1]}，如果str1是回文，则在回文串路径中记录str1，然后递归分析str1右侧的子串str2

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string> > partition(string s) {
        vector<string> path;
        vector<vector<string> > result;
        int size = s.size();
        if(size <= 0){
            return result;
        }//if
        Partition(s,size,0,path,result);
        return result;
    }
private:
    // s源字符串 size 源字符串长度 start 分割点
    // path中间结果 result 最终结果
    void Partition(string str,int size,int start,vector<string> &path,vector<vector<string>> &result){
        // 终止条件
        if(start == size){
            result.push_back(path);
            return;
        }//if
        string substr;
        // 分割字符串
        for(int i = start;i < size;++i){
            substr = str.substr(start,i-start+1);
            // 判断是否是回文串
            if(IsPalindrome(substr)){
                path.push_back(substr);
                Partition(str,size,i+1,path,result);
                path.pop_back();
            }//if
        }//for
    }
    // 判断字符串是否是回文串
    bool IsPalindrome(string str){
        int size = str.size();
        if(size == 0){
            return false;
        }//if
        int left = 0;
        int right = size - 1;
        while(left < right) {
            if(str[left] != str[right]) {
                return false;
            }//if
            left++;
            right--;
        }//while
        return true;
    }
};