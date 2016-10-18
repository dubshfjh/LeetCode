#include <iostream>
#include <vector>
#include <string>
using namespace std;
//题意比较晦涩：n=1,str=1；n=2时，分析n=1的字符串"1"，得到str=11(1个1)；n=3时，分析"11"，得到str="21"(2个1)

class Solution {
public:
    string countAndSay(int n) {
    	int i,j,count;
    	string temp,res;
    	string num[]={"0","1","2","3","4","5","6","7","8","9"};
    	res="1";//初始化数字1对应的字符串
    	if(n<=0){
    		return NULL;
    	}
    	for(i=2;i<=n;i++){
			temp="";
    		for(j=0;j<res.size();j++){
				count=1;
    			while(res[j]==res[j+1]&&j<res.size()-1){	
    				j++;
    				count++;
    			}
    			temp=temp+num[count]+res[j];
				//cout<<i<<"..."<<temp<<endl;
    		}
			res=temp;
			//cout<<i<<"..."<<res<<endl;
    	}
        return res;
    }
};

int main(){
    int num=10;
    string res;
    Solution sol=Solution();
    res=sol.countAndSay(num);
    cout<<res<<endl;
    return 0;
}
