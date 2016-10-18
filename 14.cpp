#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int i,j,endflag;
        string res="";
        char temp;
        endflag=j=0;
		if(strs.empty()){
			return "";
		}
		else if(strs.size()==1){//分析strs只有1个字符串的情况，此时虽然下方的遍历也可以输出结果，但是这样更节省时间
			return strs[0];
		}
        while(endflag==0){
        	for(i=0;i<strs.size();i++){//初版代码从i=1开始遍历，没考虑str[0]长度最短的情况，但是C++中字符串末尾为'\0'(strs[0][size]='\0')，所以姑且没报错
				//cout<<strs[0][j]<<endl;//应完善为从i=0开始遍历，这样也会考虑分析到strs[0]是否到达最后一个字符的情况
        		if(j<strs[i].size()){
        			if(strs[i][j]!=strs[0][j]){
        				break;
        			}
        		}
        		else{
        			break;
        		}
        		
        	}
        	if(i==strs.size()){
        		res+=strs[0][j];
        		j++;
        	}
        	else{//strs[i][j]!=strs[0][j]||j==strs[i].size()，此时最长公共前缀不应该加上strs[0][j]，所以匹配该结束了!
        		endflag=1;
        	}
        }
		//cout<<res<<",,,"<<endl;
        return res;
    }
};

int main(){
    vector<string> strs;

    Solution sol=Solution();
    str.push_back("a");
    str.push_back("ab");
    str.push_back("ac");
    sol.intToRoman(num);
    return 0;
}

