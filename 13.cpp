#include <iostream>
#include <string>
using namespace std;

class Solution{
public:
	int romanToInt(string s){
		int i,res,hash[256],leftsmall;
		for(i=0;i<255;i++){
			hash[i]=-1;
		}
		hash['I']=1;
		hash['V']=5;
		hash['X']=10;
		hash['L']=50;
		hash['C']=100;
		hash['D']=500;
		hash['M']=1000;

		i=res=leftsmall=0;
		while(i<s.size()){
			if(i+1<s.size()){
				if(s[i]=='I'||s[i]=='X'||s[i]=='C'){
					if(hash[s[i]]<hash[s[i+1]]){
						res-=hash[s[i]];
						leftsmall=1;
					}
				}
			}
			if(leftsmall==0){
				//cout<<hash[i]<<endl;
				res+=hash[s[i]];
			}
			leftsmall=0;
			i++;
		}
		//cout<<res<<endl;
		return res;
	}
};


int main(){
    int num=3999;

    Solution sol=Solution();
    sol.intToRoman(num);
    return 0;
}

