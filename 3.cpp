#include <iostream>
#include <string>
#include <map>
using namespace std;

接近O(n^3)，超时！！！
/*
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i,j,len,tempres;
        string tempstr,finalstr;
        len=s.size();
        tempres=0;
        for(i=0;i<len;i++){
            tempstr=s[i];
            for(j=i+1;j<len;j++){
                if(indexof(tempstr,s[j])==1){
                    //cout<<"tempstr is:"<<tempstr<<endl;
                    //cout<<"char is: "<<s[j]<<endl;;
                    tempstr+=s[j];
                }
                else{
                    break;
                }
            }
            if(tempstr.size()>tempres){
                tempres=tempstr.size();
                finalstr=tempstr;
            }
        }
        cout<<"String is: "<<finalstr<<endl;
        cout<<"Length is: "<<tempres<<endl;
        return tempres;
    }
    
    int indexof(string s,char c){
        for(int i=0;i<s.size();i++){
            if(s[i]==c){
                return 0;
            }
        }
        return 1;
    }
};
*/
仍然超时，必须得做到时间复杂度O(n)
/*
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i,j,len,tempnum,templen,tempres;
        map<char,int> visited;
        string tempstr;
        len=s.size();
        tempres=0;
        for(i=0;i<len;i++){
            templen=0;
            visited.clear();
            for(j=i;j<len;j++){
                if(visited.count(s[j])==0){
                    templen++;
                    visited.insert(pair<char,int>(s[j],1));
                }
                else{
                    break;
                }
            }
            if(tempres<templen){
                tempres=templen;
            }
        }
        cout<<"length is: "<<tempres<<endl;
        return tempres;
    }
};
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s){
        int i,start,end,templen;//最长子串的start和end下标
        int hash[256];//hash[char]存储了某字符ASCII码的最后一次出现的下标
        for(i=0;i<255;i++){
            hash[i]=-1;
        }
        start=templen=0;
        for(end=0;end<s.size();end++){
            if(hash[s[end]]!=-1){//如果s[end]这一字符第二次出现了，那么start右移至s[end]最后一次出现的下标+1处
                start=max(start,hash[s[end]]+1);
            }
            templen=max(templen,end-start+1);
            hash[s[end]]=end;//更新s[end]这一字符最后一次出现的下标
        }
        cout<<templen<<endl;
        return templen;
    }
}; 
int main(){
    string s;
    s="abcabcbb";
    Solution sol=Solution();
    sol.lengthOfLongestSubstring(s);
    return 0;
}
