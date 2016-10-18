#include <iostream>
#include <string>
#include <map>
using namespace std;
class Solution {
public:
	//string num[10]={"0","1","2","3","4","5","6","7","8","9"};
	string multiply(string num1, string num2) {
		int i,j,size_1,size_2,number;
		string res;
		size_1=num1.size();
		size_2=num2.size();
		vector<int> temp(size_1+size_2,0);
		/*
		举例：12*21：temp数组依次执行 [0]+=2,[1]+=1,[1]+=4,[2]+=2.得到temp：{0...0,2,5,2}，跳过之前的0就得到了结果
		*/
		for(i=0;i<size_1;i++){
			for(j=0;j<size_2;j++){
				temp[i+j] += (num1[size_1-i-1]-'0')*(num2[size_2-j-1]-'0');
			}
		}

		int flag=0;
		for(i=0;i<temp.size();i++){
			number=temp[i]+flag;
			temp[i]=number%10;
			flag=number/10;
		}

		i=temp.size()-1;
		while(i>=0 && temp[i]==0){
			i--;//跳过前置的0
		}

		if(i<0){
			return "0";
		}
		else{
			while(i>=0){
				res += temp[i]+'0';
				i--;
			}
			return res;
		}
    }
};

    
    /*加法的实现
    string add_str(string s1,string s2){
    	string num[10]={"0","1","2","3","4","5","6","7","8","9"};
    	int i,j,temp,flag,index;
    	string res="";
    	int tempres[100];
    	i=s1.size()-1;
    	j=s2.size()-1;
    	temp=flag=index=0;
    	while(i>=0 || j>=0){
    		if(i>=0 && j>=0){
    			temp=(s1[i]-'0')+(s2[j]-'0')+flag;
    		}
    		else if(j<0){
    			temp=(s1[i]-'0')+flag;
    		}
    		else if(i<0){
    			temp=(s1[j]-'0')+flag;
    		}
    		flag=temp/10;
    		temp%=10;
    		tempres[index++]=temp;
    		i--;
    		j--;
    	}
    	tempres[index]=flag;
    	for(i=index;i>=0;i--){
    		res+=num[tempres[i]];
    	}
    	return res;
    }
    */
};