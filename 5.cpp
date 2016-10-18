#include <iostream>
#include <string>
using namespace std;
//动态规划，table[i][j]存储i,j两点是否存在回文子串，如果s[i]==s[j]而且table[i+1][j-1]==1，则i,j之间也是回文子串
//初始化时，如果s[i]==s[i+1]，则table[i][i+1]=1;
class Solution {
public:
    string longestPalindrome(string s) {
    	int i,j,maxlen,len,str_len,begin;
        int table[1000][1000];
        string res="";

        for(i=0;i<1000;i++){
        	for(j=0;j<1000;j++){
        		table[i][j]=-1;
        	}
        	table[i][i]=1;
        }

        begin=0;
        maxlen=1;
        str_len=s.size();
        for(i=0;i<str_len-1;i++){
        	if(s[i]==s[i+1]){
        		table[i][i+1]=1;
        		maxlen=2;
        		begin=i;
        	}
        }

        for(len=3;len<=str_len;len++){
        	for(i=0;str_len-i>len-1;i++){//(str_len-1)-i+1>len-1
        		j=i+len-1;//j-i+1=len
        		if(s[i]==s[j]&&table[i+1][j-1]==1){
        			table[i][j]=1;
        			begin=i;
        			maxlen=len;
        		}
        	}       	
        }
        res=s.substr(begin,maxlen);
        cout<<res<<endl;
        return res;
    }
};

int main(){
	string s;
	s="abcba";
    Solution sol=Solution();
	sol.longestPalindrome(s);
	return 0;
}