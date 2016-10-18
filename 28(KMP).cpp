算法详解参见笔记本
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int str_len,pattern_len,str_i,pattern_j;
        str_len=haystack.size();
        pattern_len=needle.size();
        vector<int> next(pattern_len,-1);
        if(needle.compare("")==0){//如果pattern为""，则认为母串的第0位为""
            return 0;
        }
        if(haystack.compare("")==0){//此时pattern不为"",如果母串为""，则认为母串不匹配模式串
            return -1;
        }
        getNext(needle,next,pattern_len);

        str_i=pattern_j=0;
        while(str_i<str_len&&pattern_j<pattern_len){
            if(haystack[str_i]==needle[pattern_j]){
                str_i++;
                pattern_j++;
            }
            else{
                if(pattern_j==0){
                    str_i++;
                }
                else{
                    pattern_j=next[pattern_j-1]+1;
                }
            }
        }
        return (pattern_j==pattern_len)?(str_i-pattern_len):-1;
  }

    void getNext(string pattern,vector<int>& next,int len){
        next[0]=-1;
        int j,k;
        for(j=1;j<len;j++){
            k=next[j-1];
            while(k>=0&&pattern[k+1]!=pattern[j]){
                k=next[k];
            }
            if(pattern[k+1]==pattern[j]){
                next[j]=k+1;
            }
            else{
                next[j]=-1;
            }
        }
    }
};

int main(){
    int res;
    string target="";
    string pattern="";
    Solution sol=Solution();
    res=sol.strStr(target,pattern);
    cout<<res<<endl;
    return 0;
}
